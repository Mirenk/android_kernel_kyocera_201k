/*
 * This software is contributed or developed by KYOCERA Corporation.
 * (C) 2012 KYOCERA Corporation
 */
/* include/asm/mach-msm/htc_pwrsink.h
 *
 * Copyright (C) 2008 HTC Corporation.
 * Copyright (C) 2007 Google, Inc.
 * Copyright (c) 2011 Code Aurora Forum. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <linux/delay.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <linux/hrtimer.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/workqueue.h>
#include <linux/regulator/consumer.h>
#include "board-8960.h"
#include "timed_output.h"

enum vib_status
{
    VIB_STANDBY,
    VIB_ON,
    VIB_OFF,
};
enum vib_add_time_flag
{
    VIB_ADD_TIME_FLAG_OFF,
    VIB_ADD_TIME_FLAG_ON,
};

//#define DEBUG_VIB_LC898300

#define VIB_DRV_NAME                    "LC898300"
#define VIB_ON_WORK_NUM                 (5)
#define I2C_RETRIES_NUM                 (5)
#define I2C_WRITE_MSG_NUM               (1)
#define I2C_READ_MSG_NUM                (2)
#define VIB_STANDBY_DELAY_TIME          (1000)
#define VIB_TIME_MIN                    (25)
#define VIB_TIME_MAX                    (15000)
#define VIB_REGULATOR_VREG_NAME         "8921_l17"
#define VIB_REGULATOR_CURR_IDLE         (500)
#define VIB_REGULATOR_CURR_NORMAL       (100000)

struct vib_on_work_data
{
    struct work_struct  work_vib_on;
    int                 time;
};
struct lc898300_work_data {
    struct vib_on_work_data vib_on_work_data[VIB_ON_WORK_NUM];
    struct work_struct work_vib_off;
    struct work_struct work_vib_standby;
};
struct lc898300_data_t {
    struct i2c_client *lc898300_i2c_client;
    struct hrtimer vib_off_timer;
    struct hrtimer vib_standby_timer;
    int work_vib_on_pos;
    enum vib_status vib_cur_status;
    enum vib_add_time_flag add_time_flag;
    struct regulator *vib_regulator;
};

static struct mutex vib_mutex;
static u8 write_buf[6] = {0x01, 0x0B, 0x0F, 0x00, 0x40, 0x18};
#ifdef DEBUG_VIB_LC898300
static u8 read_buf[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
#endif /* DEBUG_VIB_LC898300 */
struct lc898300_work_data lc898300_work;
struct lc898300_data_t lc898300_data;

#define VIB_LOG(md, fmt, ... ) \
printk(md "[VIB]%s(%d): " fmt, __func__, __LINE__, ## __VA_ARGS__)
#ifdef DEBUG_VIB_LC898300
#define VIB_DEBUG_LOG(md, fmt, ... ) \
printk(md "[VIB]%s(%d): " fmt, __func__, __LINE__, ## __VA_ARGS__)
#else
#define VIB_DEBUG_LOG(md, fmt, ... )
#endif /* DEBUG_VIB_LC898300 */

static int lc898300_i2c_write_data(struct i2c_client *client, u8 *buf, u16 len)
{
    int ret = 0;
    int retry = 0;
    struct i2c_msg msg[I2C_WRITE_MSG_NUM];
#ifdef DEBUG_VIB_LC898300
    int i = 0;
#endif /* DEBUG_VIB_LC898300 */

    VIB_DEBUG_LOG(KERN_INFO, "called. len=%d\n", (int)len);
    if (client == NULL || buf == NULL)
    {
        VIB_LOG(KERN_ERR, "client=0x%08x,buf=0x%08x\n",
                (unsigned int)client, (unsigned int)buf);
        return 0;
    }

    VIB_DEBUG_LOG(KERN_INFO, "addr=0x%02x,adapter=0x%08x\n",
                  (unsigned int)client->addr,
                  (unsigned int)client->adapter);

    msg[0].addr = client->addr;
    msg[0].flags = 0;
    msg[0].len = len;
    msg[0].buf = buf;

    do
    {
        ret = i2c_transfer(client->adapter, msg, I2C_WRITE_MSG_NUM);
        VIB_DEBUG_LOG(KERN_INFO, "i2c_transfer(write) ret=%d\n", ret);
    } while ((ret != I2C_WRITE_MSG_NUM) && (++retry < I2C_RETRIES_NUM));

    if (ret != I2C_WRITE_MSG_NUM)
    {
        ret = -1;
        VIB_LOG(KERN_ERR, "i2c write error (try:%d)\n", retry);
    }
    else
    {
        ret = 0;
        VIB_DEBUG_LOG(KERN_INFO, "i2c write success\n");
#ifdef DEBUG_VIB_LC898300
        for (i = 1; i < len; i++)
        {
            VIB_DEBUG_LOG(KERN_INFO, "i2c write reg=0x%02x,value=0x%02x\n",
                          (unsigned int)(*buf + i), (unsigned int)*(buf + i));
        }
#endif /* DEBUG_VIB_LC898300 */
    }

    VIB_DEBUG_LOG(KERN_INFO, "finish. ret=%d\n", ret);
    return ret;
}

#ifdef DEBUG_VIB_LC898300
static int lc898300_i2c_read_data(struct i2c_client *client, u8 reg, u8 *buf, u16 len)
{
    int ret = 0;
    int retry = 0;
    u8 start_reg = 0;
    struct i2c_msg msg[I2C_READ_MSG_NUM];
    int i = 0;

    VIB_DEBUG_LOG(KERN_INFO, "called. reg=0x%02x, len=%d\n", (int)reg, (int)len);
    if (client == NULL || buf == NULL)
    {
        VIB_LOG(KERN_ERR, "client=0x%08x\n",
                (unsigned int)client);
        return 0;
    }

    VIB_DEBUG_LOG(KERN_INFO, "addr=0x%02x,adapter=0x%08x\n",
                  (unsigned int)client->addr,
                  (unsigned int)client->adapter);

    msg[0].addr = client->addr;
    msg[0].flags = 0;
    msg[0].len = 1;
    msg[0].buf = &start_reg;
    start_reg = reg;

    msg[1].addr = client->addr;
    msg[1].flags = I2C_M_RD;
    msg[1].len = len;
    msg[1].buf = buf;

    do
    {
        ret = i2c_transfer(client->adapter, msg, I2C_READ_MSG_NUM);
        VIB_DEBUG_LOG(KERN_INFO, "i2c_transfer(read) reg=0x%02x,ret=%d\n",
                      (unsigned int)reg, ret);
    } while ((ret != I2C_READ_MSG_NUM) && (++retry < I2C_RETRIES_NUM));

    if(ret != I2C_READ_MSG_NUM)
    {
        ret = -1;
        VIB_LOG(KERN_ERR, "i2c read error (try:%d)\n", retry);
    }
    else
    {
        ret = 0;
        VIB_DEBUG_LOG(KERN_INFO, "i2c read success\n");
        for (i = 0; i < len; i++)
        {
            VIB_DEBUG_LOG(KERN_INFO, "i2c read reg=0x%02x,value=0x%02x\n",
                          (unsigned int)(reg + i), (unsigned int)*(buf + i));
        }
    }

    VIB_DEBUG_LOG(KERN_INFO, "finish. ret=%d\n", ret);
    return ret;
}
#endif /* DEBUG_VIB_LC898300 */

static void lc898300_set_vib(enum vib_status status, int time)
{
    enum vib_status cur_status = lc898300_data.vib_cur_status;

    VIB_DEBUG_LOG(KERN_INFO, "called. status=%d,time=%d,cur_status=%d\n",
                              status, time, cur_status);
    mutex_lock(&vib_mutex);

    switch (status) {
        case VIB_ON:
            VIB_DEBUG_LOG(KERN_INFO, "VIB_ON\n");
            if (cur_status == VIB_STANDBY)
            {
                gpio_set_value_cansleep(PM8921_GPIO_PM_TO_SYS(20), 1);
                
                VIB_DEBUG_LOG(KERN_INFO, "udelay(200) start.\n");
                udelay(200);
                VIB_DEBUG_LOG(KERN_INFO, "udelay(200) end.\n");

                lc898300_i2c_write_data(lc898300_data.lc898300_i2c_client,
                                        (u8 *)write_buf,
                                        sizeof(write_buf));

#ifdef DEBUG_VIB_LC898300
                lc898300_i2c_read_data(lc898300_data.lc898300_i2c_client,
                                        0x01,
                                        (u8 *)read_buf,
                                        sizeof(read_buf));
#endif /* DEBUG_VIB_LC898300 */
            }
            else
            {
                VIB_DEBUG_LOG(KERN_INFO, "VIB_ON standby cancel skip.\n");
            }

            if (cur_status != VIB_ON)
            {
                gpio_set_value_cansleep(PM8921_GPIO_PM_TO_SYS(33), 1);
            }
            else
            {
                VIB_DEBUG_LOG(KERN_INFO, "VIB_ON skip.\n");
            }
            VIB_DEBUG_LOG(KERN_INFO, "hrtimer_start(vib_off_timer). time=%d\n", time);
            hrtimer_start(&lc898300_data.vib_off_timer,
                          ktime_set(time / 1000, 
                          (time % 1000) * 1000000),
                          HRTIMER_MODE_REL);
            
            lc898300_data.vib_cur_status = status;
            VIB_DEBUG_LOG(KERN_INFO, "set cur_status=%d\n", lc898300_data.vib_cur_status);
            break;
        case VIB_OFF:
            VIB_DEBUG_LOG(KERN_INFO, "VIB_OFF\n");
            if (cur_status == VIB_ON)
            {
                gpio_set_value_cansleep(PM8921_GPIO_PM_TO_SYS(33), 0);
                lc898300_data.vib_cur_status = status;
                VIB_DEBUG_LOG(KERN_INFO, "set cur_status=%d\n", lc898300_data.vib_cur_status);

                VIB_DEBUG_LOG(KERN_INFO, "hrtimer_start(vib_standby_timer).\n");
                hrtimer_start(&lc898300_data.vib_standby_timer,
                              ktime_set(VIB_STANDBY_DELAY_TIME / 1000, 
                              (VIB_STANDBY_DELAY_TIME % 1000) * 1000000),
                              HRTIMER_MODE_REL);
            }
            else
            {
                VIB_DEBUG_LOG(KERN_INFO, "VIB_OFF skip.\n");
            }
            break;
        case VIB_STANDBY:
            VIB_DEBUG_LOG(KERN_INFO, "VIB_STANDBY\n");
            if (cur_status == VIB_OFF)
            {
                gpio_set_value_cansleep(PM8921_GPIO_PM_TO_SYS(20), 0);
                lc898300_data.vib_cur_status = status;
                VIB_DEBUG_LOG(KERN_INFO, "set cur_status=%d\n", lc898300_data.vib_cur_status);
            }
            else
            {
                VIB_DEBUG_LOG(KERN_INFO, "VIB_STANDBY skip.\n");
            }
            break;
        default:
            VIB_LOG(KERN_ERR, "parameter error. status=%d\n", status);
            break;
    }
    mutex_unlock(&vib_mutex);
    return;
}

static void lc898300_vib_on(struct work_struct *work)
{
    struct vib_on_work_data *work_data = container_of
                                  (work, struct vib_on_work_data, work_vib_on);

    VIB_DEBUG_LOG(KERN_INFO, "called. work=0x%08x\n", (unsigned int)work);
    VIB_DEBUG_LOG(KERN_INFO, "work_data=0x%08x,time=%d\n",
                  (unsigned int)work_data, work_data->time);
    lc898300_set_vib(VIB_ON, work_data->time);
    
    return;
}

static void lc898300_vib_off(struct work_struct *work)
{
    VIB_DEBUG_LOG(KERN_INFO, "called. work=0x%08x\n", (unsigned int)work);
    lc898300_set_vib(VIB_OFF, 0);
    return;
}

static void lc898300_vib_standby(struct work_struct *work)
{
    VIB_DEBUG_LOG(KERN_INFO, "called. work=0x%08x\n", (unsigned int)work);

    lc898300_set_vib(VIB_STANDBY, 0);
    return;
}

static void lc898300_timed_vib_on(struct timed_output_dev *dev, int timeout_val)
{
    int ret = 0;

    VIB_DEBUG_LOG(KERN_INFO, "called. dev=0x%08x, timeout_val=%d\n",
                  (unsigned int)dev, timeout_val);
    lc898300_work.vib_on_work_data[lc898300_data.work_vib_on_pos].time = timeout_val;
    
    ret = schedule_work
          (&(lc898300_work.vib_on_work_data[lc898300_data.work_vib_on_pos].work_vib_on));
    if (ret != 0)
    {
        lc898300_data.work_vib_on_pos++;
        if (lc898300_data.work_vib_on_pos >= VIB_ON_WORK_NUM) {
            lc898300_data.work_vib_on_pos = 0;
        }
        VIB_DEBUG_LOG(KERN_INFO, "schedule_work(). work_vib_on_pos=%d\n",
                      lc898300_data.work_vib_on_pos);
        VIB_DEBUG_LOG(KERN_INFO, "vib_on_work_data[%d].time=%d\n",
                      lc898300_data.work_vib_on_pos,
                      lc898300_work.vib_on_work_data[lc898300_data.work_vib_on_pos].time);
    }
    return;
}

static void lc898300_timed_vib_off(struct timed_output_dev *dev)
{
    int ret = 0;

    VIB_DEBUG_LOG(KERN_INFO, "called. dev=0x%08x\n", (unsigned int)dev);
    ret = schedule_work(&lc898300_work.work_vib_off);
    if  (ret == 0)
    {
        VIB_LOG(KERN_ERR, "schedule_work error. ret=%d\n",ret);
    }
    return;
}

static void lc898300_timed_vib_standby(struct timed_output_dev *dev)
{
    int ret = 0;

    VIB_DEBUG_LOG(KERN_INFO, "called. dev=0x%08x\n", (unsigned int)dev);
    ret = schedule_work(&lc898300_work.work_vib_standby);
    if  (ret == 0)
    {
        VIB_LOG(KERN_ERR, "schedule_work error. ret=%d\n",ret);
    }
    return;
}

static void lc898300_enable(struct timed_output_dev *dev, int value)
{
    VIB_DEBUG_LOG(KERN_INFO, "called. dev=0x%08x,value=%d\n", (unsigned int)dev, value);
    VIB_DEBUG_LOG(KERN_INFO, "add_time_flag=%d\n", lc898300_data.add_time_flag);
    if ((value <= 0) && (lc898300_data.add_time_flag == VIB_ADD_TIME_FLAG_ON))
    {
        VIB_DEBUG_LOG(KERN_INFO, "skip. value=%d,add_time_flag=%d\n",
                      value, lc898300_data.add_time_flag);
        return;
    }

    VIB_DEBUG_LOG(KERN_INFO, "hrtimer_cancel(vib_off_timer)\n");
    hrtimer_cancel(&lc898300_data.vib_off_timer);

    if (value <= 0)
    {
        lc898300_timed_vib_off(dev);
    }
    else
    {
        VIB_DEBUG_LOG(KERN_INFO, "hrtimer_cancel(vib_standby_timer)\n");
        hrtimer_cancel(&lc898300_data.vib_standby_timer);
        if (value < VIB_TIME_MIN)
        {
            value = VIB_TIME_MIN;
            lc898300_data.add_time_flag = VIB_ADD_TIME_FLAG_ON;
            VIB_DEBUG_LOG(KERN_INFO, "set add_time_flag=%d\n", lc898300_data.add_time_flag);
        }
        else
        {
            lc898300_data.add_time_flag = VIB_ADD_TIME_FLAG_OFF;
            VIB_DEBUG_LOG(KERN_INFO, "set add_time_flag=%d\n", lc898300_data.add_time_flag);
        }
        lc898300_timed_vib_on(dev, value);
    }
    return;
}

static int lc898300_get_vib_time(struct timed_output_dev *dev)
{
    int ret = 0;

    VIB_DEBUG_LOG(KERN_INFO, "called. dev=0x%08x\n", (unsigned int)dev);
    mutex_lock(&vib_mutex);

    ret = hrtimer_active(&lc898300_data.vib_off_timer);
    if (ret != 0)
    {
        ktime_t r = hrtimer_get_remaining(&lc898300_data.vib_off_timer);
        struct timeval t = ktime_to_timeval(r);
        mutex_unlock(&vib_mutex);

        return t.tv_sec * 1000 + t.tv_usec / 1000;
    }
    mutex_unlock(&vib_mutex);
    return 0;
}

static enum hrtimer_restart lc898300_off_timer_func(struct hrtimer *timer)
{
    VIB_DEBUG_LOG(KERN_INFO, "called. timer=0x%08x\n", (unsigned int)timer);
    lc898300_data.add_time_flag = VIB_ADD_TIME_FLAG_OFF;
    VIB_DEBUG_LOG(KERN_INFO, "set add_time_flag=%d\n", lc898300_data.add_time_flag);

    lc898300_timed_vib_off(NULL);
    return HRTIMER_NORESTART;
}

static enum hrtimer_restart lc898300_standby_timer_func(struct hrtimer *timer)
{
    VIB_DEBUG_LOG(KERN_INFO, "called. timer=0x%08x\n", (unsigned int)timer);
    lc898300_timed_vib_standby(NULL);
    return HRTIMER_NORESTART;
}

static struct timed_output_dev lc898300_output_dev = {
    .name = "vibrator",
    .get_time = lc898300_get_vib_time,
    .enable = lc898300_enable,
};

static int __devinit lc898300_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    int ret = 0;
    int count = 0;
    bool bret = true;
    
    VIB_DEBUG_LOG(KERN_INFO, "called. id=0x%08x\n", (unsigned int)id);
    lc898300_data.lc898300_i2c_client = client;
    lc898300_data.vib_cur_status = VIB_STANDBY;
    lc898300_data.add_time_flag = VIB_ADD_TIME_FLAG_OFF;
    lc898300_data.vib_regulator = NULL;

    mutex_init(&vib_mutex);

    for (count = 0; count < VIB_ON_WORK_NUM; count++)
    {
        INIT_WORK(&(lc898300_work.vib_on_work_data[count].work_vib_on),
                  lc898300_vib_on);
        lc898300_work.vib_on_work_data[count].time = 0;
    }
    lc898300_data.work_vib_on_pos = 0;
    INIT_WORK(&lc898300_work.work_vib_off, lc898300_vib_off);
    INIT_WORK(&lc898300_work.work_vib_standby, lc898300_vib_standby);

    hrtimer_init(&lc898300_data.vib_off_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    lc898300_data.vib_off_timer.function = lc898300_off_timer_func;
    hrtimer_init(&lc898300_data.vib_standby_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    lc898300_data.vib_standby_timer.function = lc898300_standby_timer_func;

    ret = timed_output_dev_register(&lc898300_output_dev);
    VIB_DEBUG_LOG(KERN_INFO, "timed_output_dev_register() ret=%d\n", ret);
    if (ret != 0)
    {
        VIB_LOG(KERN_ERR, "timed_output_dev_register() ret=%d\n", ret);
        goto probe_dev_register_error;
    }

    bret = gpio_is_valid(PM8921_GPIO_PM_TO_SYS(20));
    if (!bret)
    {
        VIB_LOG(KERN_ERR, "gpio_is_valid error (PM8921_GPIO_PM_TO_SYS(20))\n");
        ret = -ENODEV;
        goto probe_gpio_is_valid_error;
    }

    bret = gpio_is_valid(PM8921_GPIO_PM_TO_SYS(33));
    if (!bret)
    {
        VIB_LOG(KERN_ERR, "gpio_is_valid error (PM8921_GPIO_PM_TO_SYS(33))\n");
        ret = -ENODEV;
        goto probe_gpio_is_valid_error;
    }

    ret = gpio_request(PM8921_GPIO_PM_TO_SYS(20), "LC898300 RST");
    VIB_DEBUG_LOG(KERN_INFO, "gpio_request(PMIC GPIO20) ret=%d\n", ret);
    if (ret != 0)
    {
        VIB_LOG(KERN_ERR, "gpio_request(PMIC GPIO20) ret=%d\n", ret);
        goto probe_gpio_is_valid_error;
    }

    ret = gpio_request(PM8921_GPIO_PM_TO_SYS(33), "LC898300 EN");
    if (ret != 0)
    {
        VIB_LOG(KERN_ERR, "gpio_request(PMIC GPIO33) ret=%d\n", ret);
        goto probe_gpio_request_error;
    }

    VIB_DEBUG_LOG(KERN_INFO, "gpio_request(PMIC GPIO33) ret=%d\n", ret);

    lc898300_data.vib_regulator = regulator_get(NULL, VIB_REGULATOR_VREG_NAME);
    VIB_DEBUG_LOG(KERN_INFO, "regulator_get() called. vib_regulator=0x%08X\n",
                  (u32)lc898300_data.vib_regulator);
    if (lc898300_data.vib_regulator != NULL) {
        ret = regulator_set_optimum_mode(lc898300_data.vib_regulator,
                                         VIB_REGULATOR_CURR_NORMAL);
        VIB_DEBUG_LOG(KERN_INFO, "regulator_set_optimum_mode() called. ret=%d.\n", ret);
        if (ret < 0)
            VIB_LOG(KERN_ERR, "regulator_set_optimum_mode() error. ret=%d\n", ret);
    }
    else {
        VIB_LOG(KERN_ERR, "regulator_get vib_regulator=NULL\n");
    }

    return 0;

probe_gpio_request_error:
    gpio_free(PM8921_GPIO_PM_TO_SYS(20));
probe_gpio_is_valid_error:
    timed_output_dev_unregister(&lc898300_output_dev);
probe_dev_register_error:
    mutex_destroy(&vib_mutex);
    return ret;
}

static int32_t __devexit lc898300_remove(struct i2c_client *pst_client)
{
    int ret = 0;

    if (lc898300_data.vib_regulator != NULL)
        regulator_put(lc898300_data.vib_regulator);

    VIB_DEBUG_LOG(KERN_INFO, "called. pst_client=0x%08x\n", (unsigned int)pst_client);
    gpio_free(PM8921_GPIO_PM_TO_SYS(20));
    gpio_free(PM8921_GPIO_PM_TO_SYS(33));

    timed_output_dev_unregister(&lc898300_output_dev);

    mutex_destroy(&vib_mutex);
    return ret;
}

static int32_t lc898300_suspend(struct i2c_client *pst_client, pm_message_t mesg)
{
    int ret = 0;

    VIB_DEBUG_LOG(KERN_INFO, "called. pst_client=0x%08x,mesg=%d\n",
                  (unsigned int)pst_client, mesg.event);
    if (lc898300_data.vib_regulator != NULL) {
        ret = regulator_set_optimum_mode(lc898300_data.vib_regulator,
                                         VIB_REGULATOR_CURR_IDLE);
        VIB_DEBUG_LOG(KERN_INFO, "regulator_set_optimum_mode() called. ret=%d.\n", ret);
        if (ret < 0)
            VIB_LOG(KERN_ERR, "regulator_set_optimum_mode() error. ret=%d\n", ret);
    }
    VIB_DEBUG_LOG(KERN_INFO, "end.\n");
    return 0;
}

static int32_t lc898300_resume(struct i2c_client *pst_client)
{
    int ret = 0;

    VIB_DEBUG_LOG(KERN_INFO, "called. pst_client=0x%08x\n", (unsigned int)pst_client);
    if (lc898300_data.vib_regulator != NULL) {
        ret = regulator_set_optimum_mode(lc898300_data.vib_regulator,
                                         VIB_REGULATOR_CURR_NORMAL);
        VIB_DEBUG_LOG(KERN_INFO, "regulator_set_optimum_mode() called. ret=%d.\n", ret);
        if (ret < 0)
            VIB_LOG(KERN_ERR, "regulator_set_optimum_mode() error. ret=%d\n", ret);
    }
    VIB_DEBUG_LOG(KERN_INFO, "end.\n");
    return 0;
}

static struct i2c_device_id lc898300_idtable[] = {
    {VIB_DRV_NAME, 0},
    { },
};
MODULE_DEVICE_TABLE(i2c, lc898300_idtable);

static struct i2c_driver lc898300_driver = {
    .driver     = {
        .name   = VIB_DRV_NAME,
        .owner = THIS_MODULE,
    },
    .probe      = lc898300_probe,
    .remove     = __devexit_p(lc898300_remove),
    .suspend    = lc898300_suspend,
    .resume     = lc898300_resume,
    .id_table   = lc898300_idtable,
};

static int __init lc898300_init(void)
{
    int ret = 0;

    VIB_DEBUG_LOG(KERN_INFO, "called.\n");
    ret = i2c_add_driver(&lc898300_driver);
    VIB_DEBUG_LOG(KERN_INFO, "i2c_add_driver() ret=%d\n", ret);
    if (ret != 0)
    {
        VIB_LOG(KERN_ERR, "i2c_add_driver() ret=%d\n", ret);
    }

    return ret;
}

static void __exit lc898300_exit(void)
{
    VIB_DEBUG_LOG(KERN_INFO, "called.\n");
    i2c_del_driver(&lc898300_driver);
    VIB_DEBUG_LOG(KERN_INFO, "i2c_del_driver()\n");

    return;
}

module_init(lc898300_init);
module_exit(lc898300_exit);
MODULE_DESCRIPTION("timed output LC898300 vibrator device");
MODULE_LICENSE("GPL");
