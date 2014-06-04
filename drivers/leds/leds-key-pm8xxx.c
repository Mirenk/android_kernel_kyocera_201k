/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * , USA.
 */
/*
 * This software is contributed or developed by KYOCERA Corporation.
 * (C) 2012 KYOCERA Corporation
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/mutex.h>
#include <linux/mfd/pm8xxx/core.h>
#include <linux/mfd/pm8xxx/pwm.h>
#include <linux/leds-pm8xxx.h>
#include "board-8960.h"

//#define DEBUG_PM8921_KEYLED
#define KEYLED_DIAG

#define PM8XXX_KEYLED_DEV_NAME      "pm8xxx_keyled"
#define PM8XXX_KEYLED_CDEV_NAME     "keyledinfo"
#define PM8XXX_KEYLED_NUM           3
#define PM8XXX_KEYLED_ON_WAIT       20

struct pm8xxx_keyled_data {
    struct led_classdev cdev;
    struct work_struct work;
    struct mutex keyled_mutex;
    u32 brightness;
    u32 cur_brightness;
    struct pwm_device *pwm_dev[PM8XXX_KEYLED_NUM];
};

struct pm8xxx_pwm_request {
    int channel;
    char device_name[10];
};

struct pm8xxx_pwm_init_data {
    struct pm8xxx_pwm_request pwm_request_data[PM8XXX_KEYLED_NUM];
    struct pm8xxx_pwm_period pwm_period_data;
};

static struct pm8xxx_pwm_init_data pwm_init_data = {
    {
        { 0, "KEY_LED1" },
        { 1, "KEY_LED2" },
        { 2, "KEY_LED3" },
    },
    {
        .pwm_size       = PM_PWM_SIZE_9BIT,
        .clk            = PM_PWM_CLK_19P2MHZ,
        .pre_div        = PM_PWM_PDIV_2,
        .pre_div_exp    = 0,
    },
};

#define KEYLED_LOG(md, fmt, ...) \
printk(md "[KEYLED]%s(%d): " fmt, __func__, __LINE__, ## __VA_ARGS__)
#ifdef DEBUG_PM8921_KEYLED
#define KEYLED_DEBUG_LOG(md, fmt, ...) \
printk(md "[KEYLED]%s(%d): " fmt, __func__, __LINE__, ## __VA_ARGS__)
#else
#define KEYLED_DEBUG_LOG(md, fmt, ...)
#endif /* DEBUG_PM8921_KEYLED */

#ifdef KEYLED_DIAG
#include <asm/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/ioctl.h>

#define LEDLIGHT        'L'
#define LEDLIGHT_KEYLED_CONFIG_DM       _IOW(LEDLIGHT, 100, T_LEDLIGHT_IOCTL_DM2)
#define LEDLIGHT_KEYLED_ENABLE_DM       _IOW(LEDLIGHT, 101, T_LEDLIGHT_IOCTL_DM2)

typedef struct _t_ledlight_ioctl_dm2 {
    u32 dm_data[14];
}T_LEDLIGHT_IOCTL_DM2;

static struct pm8xxx_keyled_data *gkeyled;
#endif /* KEYLED_DIAG */

static void pm8xxx_keyled_set
(struct pm8xxx_keyled_data *keyled, u32 brightness) {
    int i = 0;
    int rc = 0;
    u32 reg_value;
    u32 set_value[3];
    u32 cur_value[3];

    KEYLED_DEBUG_LOG(KERN_INFO, "called. brightness=0x%08X\n",
                                             (u32)brightness);
    KEYLED_DEBUG_LOG(KERN_INFO, "cur_brightness(pre)=0x%08X\n",
                                       keyled->cur_brightness);

    if ((brightness != 0) && (keyled->cur_brightness == 0)) {
        KEYLED_DEBUG_LOG(KERN_INFO, "gpio_set_value_cansleep(PMIC_GPIO5,1).\n");
    gpio_set_value_cansleep(PM8921_GPIO_PM_TO_SYS(5), 1);
        KEYLED_DEBUG_LOG(KERN_INFO, "udelay(%d) start.\n",
                                   PM8XXX_KEYLED_ON_WAIT);
    udelay(PM8XXX_KEYLED_ON_WAIT);
        KEYLED_DEBUG_LOG(KERN_INFO, "udelay(%d) end.\n",
                                 PM8XXX_KEYLED_ON_WAIT);
    }

    set_value[0] = (brightness & 0x00FF0000) >> 16;
    set_value[1] = (brightness & 0x0000FF00) >> 8;
    set_value[2] = (brightness & 0x000000FF);
    cur_value[0] = (keyled->cur_brightness & 0x00FF0000) >> 16;
    cur_value[1] = (keyled->cur_brightness & 0x0000FF00) >> 8;
    cur_value[2] = (keyled->cur_brightness & 0x000000FF);

    for (i = 0; i < PM8XXX_KEYLED_NUM; i++) {
        KEYLED_DEBUG_LOG(KERN_INFO, "set_value[%d]=0x%02X,cur_value[%d]=0x%02X"
                                       "\n", i, set_value[i], i, cur_value[i]);
        if (set_value[i] != cur_value[i]) {
            reg_value = set_value[i] << 1;
            KEYLED_DEBUG_LOG(KERN_INFO, "reg_value[%d]=0x%04X\n", i, reg_value);
            rc = pm8xxx_pwm_config_pwm_value(keyled->pwm_dev[i], reg_value);
            KEYLED_DEBUG_LOG(KERN_INFO, "pwm_config_pwm_value[%d] called. "
                                                          "rc=%d\n", i, rc);
        if (rc < 0) {
                KEYLED_LOG(KERN_ERR, "pm8xxx_pwm_config_pwm_value[%d] error. "
                                                             "rc=%d\n",i, rc);
            }
        }
        else {
            KEYLED_DEBUG_LOG(KERN_INFO, "pm8xxx_pwm_config_pwm_value[%d] skip."
                                                                      "\n" ,i);
        }
    }

    for (i = 0; i < PM8XXX_KEYLED_NUM; i++) {
        if (set_value[i] != 0) {
            if (cur_value[i] == 0) {
        rc = pwm_enable(keyled->pwm_dev[i]);
                KEYLED_DEBUG_LOG(KERN_INFO, "pwm_enable[%d] called. rc=%d\n", i
                                                                         , rc);
        if (rc < 0) {
                    KEYLED_LOG(KERN_ERR, "pwm_enable[%d] error. rc=%d\n", i
                                                                     , rc);
        }
    }
            else {
                KEYLED_DEBUG_LOG(KERN_INFO, "pwm_enable[%d] skip.\n",i);
            }
        }
        else {
            if (cur_value[i] != 0) {
        pwm_disable(keyled->pwm_dev[i]);
        KEYLED_DEBUG_LOG(KERN_INFO, "pwm_disable[%d] called.\n", i);
    }
            else {
                KEYLED_DEBUG_LOG(KERN_INFO, "pwm_disable[%d] skip.\n",i);
            }
        }
    }

    if ((brightness == 0) && (keyled->cur_brightness != 0)) {
        KEYLED_DEBUG_LOG(KERN_INFO, "gpio_set_value_cansleep(PMIC_GPIO5,0).\n");
    gpio_set_value_cansleep(PM8921_GPIO_PM_TO_SYS(5), 0);
    }
    keyled->cur_brightness = brightness;
    KEYLED_DEBUG_LOG(KERN_INFO, "cur_brightness=0x%08X\n",
                                  keyled->cur_brightness);
    
    KEYLED_DEBUG_LOG(KERN_INFO, "end.\n");
}

static void pm8xxx_keyled_set_work(struct work_struct *work) {
    struct pm8xxx_keyled_data *keyled;

    KEYLED_DEBUG_LOG(KERN_INFO, "called.\n");
    keyled = container_of(work, struct pm8xxx_keyled_data, work);

    KEYLED_DEBUG_LOG(KERN_INFO, "keyled=0x%08X\n", (u32)keyled);
    mutex_lock(&keyled->keyled_mutex);
    KEYLED_DEBUG_LOG(KERN_INFO, "brightness=0x%08X\n", keyled->brightness);
    pm8xxx_keyled_set(keyled, keyled->brightness);
    mutex_unlock(&keyled->keyled_mutex);
    KEYLED_DEBUG_LOG(KERN_INFO, "end.\n");
}

static void pm8xxx_keyled_bset
(struct led_classdev *led_cdev, enum led_brightness brightness) {
    int rc = 0;
    struct pm8xxx_keyled_data *keyled;
    u32 value = 0;

    KEYLED_DEBUG_LOG(KERN_INFO, "called. brightness=%d(0x%08X)\n",
                                          brightness, brightness);
    keyled = container_of(led_cdev, struct pm8xxx_keyled_data, cdev);
    KEYLED_DEBUG_LOG(KERN_INFO, "keyled=0x%08X\n", (u32)keyled);
    value = (u32)brightness & 0x00FFFFFF;
    KEYLED_DEBUG_LOG(KERN_INFO, "brightness=0x%08X\n", value);
        keyled->brightness = value;
        rc = schedule_work(&keyled->work);
        KEYLED_DEBUG_LOG(KERN_INFO, "schedule_work called. rc=%d\n", rc);
        if (rc == 0) {
            KEYLED_LOG(KERN_ERR, "schedule_work error. rc=%d\n", rc);
        }
    KEYLED_DEBUG_LOG(KERN_INFO, "end.\n");
}

static enum led_brightness pm8xxx_keyled_bget(struct led_classdev *led_cdev) {
    struct pm8xxx_keyled_data *keyled;
    KEYLED_DEBUG_LOG(KERN_INFO, "called.\n");
    keyled = container_of(led_cdev, struct pm8xxx_keyled_data, cdev);
    KEYLED_DEBUG_LOG(KERN_INFO, "keyled=0x%08X\n", (u32)keyled);
    KEYLED_DEBUG_LOG(KERN_INFO, "end. brightness=0x%08X\n",
                                  (u32)keyled->brightness);
    return keyled->brightness;
}

#ifdef KEYLED_DIAG
static s32 pm8xxx_keyled_open(struct inode* inode, struct file* filp)
{
    KEYLED_DEBUG_LOG(KERN_INFO, "called.\n");
    KEYLED_DEBUG_LOG(KERN_INFO, "end.\n");
    return 0;
}

static s32 pm8xxx_keyled_release(struct inode* inode, struct file* filp)
{
    KEYLED_DEBUG_LOG(KERN_INFO, "called.\n");
    KEYLED_DEBUG_LOG(KERN_INFO, "end.\n");
    return 0;
}

static int pm8xxx_keyled_diag_config(T_LEDLIGHT_IOCTL_DM2 *st_ioctl_dm2) {
    int rc = 0;
    u8 pwm_id = 0;
    struct pm8xxx_pwm_period pwm_period_data;
    int pwm_value = 0;

    KEYLED_DEBUG_LOG(KERN_INFO, "called.\n");
    pwm_id = (u8)st_ioctl_dm2->dm_data[0];
    pwm_period_data.pwm_size = (enum pm_pwm_size)st_ioctl_dm2->dm_data[1];
    pwm_period_data.clk = (enum pm_pwm_clk)st_ioctl_dm2->dm_data[2];
    pwm_period_data.pre_div = (enum pm_pwm_pre_div)st_ioctl_dm2->dm_data[3];
    pwm_period_data.pre_div_exp = (int)st_ioctl_dm2->dm_data[4];
    pwm_value = (int)st_ioctl_dm2->dm_data[5];

    rc = pm8xxx_pwm_config_period(gkeyled->pwm_dev[pwm_id],
                     &pwm_period_data);
    KEYLED_DEBUG_LOG(KERN_ERR, "pm8xxx_pwm_config_period[%d] called. rc=%d,"
                   "pwm_size=%d,clk=%d,pre_div=%d,pre_div_exp=%d\n", pwm_id,
                          rc, pwm_period_data.pwm_size, pwm_period_data.clk,
                      pwm_period_data.pre_div, pwm_period_data.pre_div_exp);
    if (rc < 0) {
        KEYLED_LOG(KERN_ERR, "pm8xxx_pwm_config_period error. rc=%d\n", rc);
        goto pwm_error;
    }

    rc = pm8xxx_pwm_config_pwm_value(gkeyled->pwm_dev[pwm_id], pwm_value);
    KEYLED_DEBUG_LOG(KERN_INFO, "pwm_config_pwm_value[%d] called. "
                     "rc=%d,value=0x%0X\n", pwm_id, rc, pwm_value);
    if (rc < 0) {
        KEYLED_LOG(KERN_ERR, "pm8xxx_pwm_config_pwm_value error. "
                                  "pwm_id=%d,rc=%d\n",pwm_id, rc);
        goto pwm_error;
    }

pwm_error:
    KEYLED_DEBUG_LOG(KERN_INFO, "end. rc=%d\n", rc);
    return rc;
}

static int pm8xxx_keyled_diag_set(T_LEDLIGHT_IOCTL_DM2 *st_ioctl_dm2) {
    int rc = 0;
    u8 pwm_id = 0;
    u8 enable = 0;

    KEYLED_DEBUG_LOG(KERN_INFO, "called.\n");
    pwm_id = (u8)st_ioctl_dm2->dm_data[0];
    enable = (u8)st_ioctl_dm2->dm_data[1];

    if (enable) {
        udelay(PM8XXX_KEYLED_ON_WAIT);
        rc = pwm_enable(gkeyled->pwm_dev[pwm_id]);
        KEYLED_DEBUG_LOG(KERN_INFO, "pwm_enable[%d] called. rc=%d\n", pwm_id
                                                                      , rc);
        if (rc < 0) {
            KEYLED_LOG(KERN_ERR, "pwm_enable error. pwm_id=%d,rc=%d\n", pwm_id
                                                                        , rc);
            goto pwm_error;
        }
    }
    else {
        pwm_disable(gkeyled->pwm_dev[pwm_id]);
        KEYLED_DEBUG_LOG(KERN_INFO, "pwm_disable[%d] called.\n", pwm_id);
    }

pwm_error:
    KEYLED_DEBUG_LOG(KERN_INFO, "end. rc=%d\n", rc);
    return rc;
}

static
long pm8xxx_keyled_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;
    int ret = 0;
    T_LEDLIGHT_IOCTL_DM2 st_ioctl_dm2;

    KEYLED_DEBUG_LOG(KERN_INFO, "called.\n");
    switch (cmd) {
    case LEDLIGHT_KEYLED_CONFIG_DM:
        KEYLED_DEBUG_LOG(KERN_INFO, "LEDLIGHT_KEYLED_CONFIG_DM\n");
        ret = copy_from_user(&st_ioctl_dm2,
                             argp,
                             sizeof(T_LEDLIGHT_IOCTL_DM2));
        if (ret) {
            KEYLED_LOG(KERN_ERR, "error : st_ioctl_dm2(cmd = "
                              "LEDLIGHT_KEYLED_CONFIG_DM)\n");
            return -EFAULT;
        }
        ret = pm8xxx_keyled_diag_config(&st_ioctl_dm2);
        if (ret < 0) {
            return -EFAULT;
        }
        break;
    case LEDLIGHT_KEYLED_ENABLE_DM:
        KEYLED_DEBUG_LOG(KERN_INFO, "LEDLIGHT_KEYLED_ENABLE_DM\n");
        ret = copy_from_user(&st_ioctl_dm2,
                             argp,
                             sizeof(T_LEDLIGHT_IOCTL_DM2));
        if (ret) {
            KEYLED_LOG(KERN_ERR, "error : st_ioctl_dm2(cmd = "
                              "LEDLIGHT_KEYLED_ENABLE_DM)\n");
            return -EFAULT;
        }
        ret = pm8xxx_keyled_diag_set(&st_ioctl_dm2);
        if (ret < 0) {
            return -EFAULT;
        }
        break;
    default:
        KEYLED_DEBUG_LOG(KERN_INFO, "default\n");
        return -ENOTTY;
    }
    KEYLED_DEBUG_LOG(KERN_INFO, "end.\n");
    return 0;
}

static struct file_operations keyled_fops = {
        .owner          = THIS_MODULE,
        .open           = pm8xxx_keyled_open,
        .release        = pm8xxx_keyled_release,
        .unlocked_ioctl = pm8xxx_keyled_ioctl,
};

static struct miscdevice keyled_device = {
        .minor = MISC_DYNAMIC_MINOR,
        .name  = "leds-keyled",
        .fops  = &keyled_fops,
};
#endif /* KEYLED_DIAG */

#ifdef CONFIG_PM
static int pm8xxx_keyled_suspend(struct device *dev)
{
    KEYLED_DEBUG_LOG(KERN_INFO, "called.\n");
    KEYLED_DEBUG_LOG(KERN_INFO, "end.\n");
    return 0;
}

static const struct dev_pm_ops pm8xxx_keyled_pm_ops = {
    .suspend = pm8xxx_keyled_suspend,
};
#endif

static int __devinit pm8xxx_keyled_probe(struct platform_device *pdev)
{
    int i = 0;
    int rc = 0;
    struct pm8xxx_keyled_data *keyled;
    
    KEYLED_DEBUG_LOG(KERN_INFO, "called.\n");

    keyled = kzalloc(sizeof(*keyled), GFP_KERNEL);
    if (!keyled) {
        KEYLED_LOG(KERN_ERR, "kzalloc error. keyled=NULL\n");
        rc = -ENOMEM;
        goto kzalloc_error;
    }
    KEYLED_DEBUG_LOG(KERN_INFO, "keyled=0x%08X\n", (u32)keyled);

    keyled->cdev.name = PM8XXX_KEYLED_CDEV_NAME;
    keyled->cdev.brightness = 0;
    keyled->cdev.max_brightness = 0x00FFFFFF,
    keyled->cdev.brightness_set = pm8xxx_keyled_bset;
    keyled->cdev.brightness_get = pm8xxx_keyled_bget;
    keyled->brightness = 0;
    keyled->cur_brightness = 0;
    for (i = 0; i < PM8XXX_KEYLED_NUM; i++) keyled->pwm_dev[i] = NULL;

    mutex_init(&keyled->keyled_mutex);
    INIT_WORK(&keyled->work, pm8xxx_keyled_set_work);

    if (!gpio_is_valid(PM8921_GPIO_PM_TO_SYS(5)))
    {
        KEYLED_LOG(KERN_ERR, "gpio_is_valid error.\n");
        rc = -EINVAL;
        goto gpio_is_valid_error;
    }

    rc = gpio_request(PM8921_GPIO_PM_TO_SYS(5), "VKEYLED_ON");
    KEYLED_DEBUG_LOG(KERN_INFO, "gpio_request called. rc=%d\n", rc);
    if (rc < 0) {
        KEYLED_LOG(KERN_ERR, "gpio_request error. rc=%d\n", rc);
        goto gpio_request_error;
    }
    
    for (i = 0; i < PM8XXX_KEYLED_NUM; i++) {
        KEYLED_DEBUG_LOG(KERN_ERR, "pwm_request[%d] channel=%d,"
               "device_name=%s\n", i, pwm_init_data.pwm_request_data[i].channel,
                                 pwm_init_data.pwm_request_data[i].device_name);
        keyled->pwm_dev[i] = pwm_request(
                                      pwm_init_data.pwm_request_data[i].channel,
                         (char *)pwm_init_data.pwm_request_data[i].device_name);
        if (IS_ERR_OR_NULL(keyled->pwm_dev[i])) {
            rc = PTR_ERR(keyled->pwm_dev[i]);
            KEYLED_LOG(KERN_ERR, "pwm_request error. pwm_channel[%d]=%d "
               "error_code=%d\n", i, pwm_init_data.pwm_request_data[i].channel,
                                                                           rc);
            keyled->pwm_dev[i] = NULL;
            goto pwm_error;
        }

        rc = pwm_config(keyled->pwm_dev[i], 0, 1000000/18750);
        KEYLED_DEBUG_LOG(KERN_INFO, "pwm_config called. rc=%d\n", rc);
        if (rc < 0) {
            KEYLED_LOG(KERN_ERR, "pwm_config error. rc=%d\n", rc);
            goto pwm_error;
        }

        rc = pm8xxx_pwm_config_period(keyled->pwm_dev[i],
                         &pwm_init_data.pwm_period_data);
        KEYLED_DEBUG_LOG(KERN_ERR, "pm8xxx_pwm_config_period[%d] called. rc=%d,"
                        "pwm_size=%d,clk=%d,pre_div=%d,pre_div_exp=%d\n", i, rc, 
                                         pwm_init_data.pwm_period_data.pwm_size,
                                              pwm_init_data.pwm_period_data.clk,
                                          pwm_init_data.pwm_period_data.pre_div,
                                     pwm_init_data.pwm_period_data.pre_div_exp);
        if (rc < 0) {
            KEYLED_LOG(KERN_ERR, "pm8xxx_pwm_config_period error. rc=%d\n", rc);
            goto pwm_error;
        }
    }

    rc = led_classdev_register(&pdev->dev, &keyled->cdev);
    KEYLED_DEBUG_LOG(KERN_INFO, "led_classdev_register called. rc=%d\n", rc);
    if (rc < 0) {
        KEYLED_LOG(KERN_ERR, "led_classdev_register error. rc=%d\n", rc);
        goto pwm_error;
    }

    platform_set_drvdata(pdev, keyled);

#ifdef KEYLED_DIAG
    gkeyled = keyled;
    misc_register(&keyled_device);
#endif /* KEYLED_DIAG */

    KEYLED_DEBUG_LOG(KERN_INFO, "end. rc=%d\n", rc);
    return rc;
    
pwm_error:
    for (i = 0; i < PM8XXX_KEYLED_NUM; i++) {
        if (keyled->pwm_dev[i]) {
            pwm_free(keyled->pwm_dev[i]);
            KEYLED_DEBUG_LOG(KERN_INFO, "pwm_free[%d] called.\n", i);
        }
    }
    gpio_free(PM8921_GPIO_PM_TO_SYS(5));
gpio_request_error:
gpio_is_valid_error:
    kfree(keyled);
    mutex_destroy(&keyled->keyled_mutex);
kzalloc_error:
    return rc;
}

static int __devexit pm8xxx_keyled_remove(struct platform_device *pdev)
{
    int i = 0;
    struct pm8xxx_keyled_data *keyled = platform_get_drvdata(pdev);

    KEYLED_DEBUG_LOG(KERN_INFO, "called.\n");
#ifdef KEYLED_DIAG
    misc_deregister(&keyled_device);
#endif /* KEYLED_DIAG */
    cancel_work_sync(&keyled->work);
    platform_set_drvdata(pdev, NULL);
    led_classdev_unregister(&keyled->cdev);
    for (i = 0; i < PM8XXX_KEYLED_NUM; i++) {
        if (keyled->pwm_dev[i]) {
            pwm_free(keyled->pwm_dev[i]);
            KEYLED_DEBUG_LOG(KERN_INFO, "pwm_free[%d] called.\n", i);
        }
    }
    gpio_free(PM8921_GPIO_PM_TO_SYS(5));
    mutex_destroy(&keyled->keyled_mutex);
    kfree(keyled);
    KEYLED_DEBUG_LOG(KERN_INFO, "end.\n");
    return 0;
}

static struct platform_driver pm8xxx_keyled_driver = {
    .probe      = pm8xxx_keyled_probe,
    .remove     = __devexit_p(pm8xxx_keyled_remove),
    .driver     = {
        .name   = PM8XXX_KEYLED_DEV_NAME,
        .owner  = THIS_MODULE,
#ifdef CONFIG_PM
        .pm     = &pm8xxx_keyled_pm_ops,
#endif
    },
};

static int __init pm8xxx_keyled_init(void)
{
    int rc = 0;
    KEYLED_DEBUG_LOG(KERN_INFO, "called.\n");
    rc = platform_driver_register(&pm8xxx_keyled_driver);
    KEYLED_DEBUG_LOG(KERN_INFO, "platform_driver_register called. rc=%d\n", rc);
    if (rc < 0)
        KEYLED_LOG(KERN_ERR, "platform_driver_register error. rc=%d\n", rc);
    KEYLED_DEBUG_LOG(KERN_INFO, "end. rc=%d\n", rc);
    return rc;
}
module_init(pm8xxx_keyled_init);

static void __exit pm8xxx_keyled_exit(void)
{
    KEYLED_DEBUG_LOG(KERN_INFO, "called.\n");
    platform_driver_unregister(&pm8xxx_keyled_driver);
    KEYLED_DEBUG_LOG(KERN_INFO, "end.\n");
}
module_exit(pm8xxx_keyled_exit);

MODULE_AUTHOR("KYOCERA Corporation");
MODULE_DESCRIPTION("pm8xxx keyled driver");
MODULE_LICENSE("GPL");
