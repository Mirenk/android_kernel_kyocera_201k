/*
 * This software is contributed or developed by KYOCERA Corporation.
 * (C) 2012 KYOCERA Corporation
 *
 * drivers/video/msm/mipi_novatek_wxga.c
 *
 * Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
*/
#include <linux/gpio.h>
#include <linux/regulator/consumer.h>
#include "msm_fb.h"
#include "mipi_dsi.h"
#include "mipi_renesas_cm.h"
#include "mipi_renesas_cm_tbl.h"
#include "mdp.h"
#include "mdp4.h"
#include "mipi_dsi.h"
#ifdef CONFIG_DISP_EXT_BLC
#include <linux/leds-lm3533.h>
#endif /* CONFIG_DISP_EXT_BLC */
#include "disp_ext.h"
static struct mipi_dsi_platform_data *mipi_renesas_cm_pdata;

#define TM_GET_PID(id) (((id) & 0xff00)>>8)

static struct dsi_buf renesas_cm_tx_buf;
static struct dsi_buf renesas_cm_rx_buf;
static int mipi_renesas_cm_lcd_init(void);

extern void mdp4_dsi_refresh_screen_at_once( struct msm_fb_data_type *mfd );

extern struct platform_device msm_mipi_dsi1_device;
static struct regulator *reg_l8, *reg_l2, *reg_lsv5;
static int dsi_boot_on = 0;
static struct msm_fb_data_type *mipi_renesas_cm_mfd;

void mipi_renesas_cm_refresh_exec( struct msm_fb_data_type *mfd )
{
	gpio_set_value(48, 0);
	msleep(5);
	gpio_set_value(48, 1);
	msleep(10);
	mipi_set_tx_power_mode(0);
	mipi_dsi_clk_cfg(1);
	mipi_dsi_cmds_tx(&renesas_cm_tx_buf, renesas_cm_refresh_cmds,
		ARRAY_SIZE(renesas_cm_refresh_cmds));
	mipi_dsi_clk_cfg(0);
}

int mipi_renesas_cm_panel_power( int on )
{
	int rc;
	local_disp_state_enum disp_state;

	disp_state = disp_ext_util_get_disp_state();

	DISP_LOCAL_LOG_EMERG("%s start:state=%d req=%d\n", __func__,disp_state, on);

	if (on == 1) {
		if(disp_state == LOCAL_DISPLAY_OFF){
			DISP_LOCAL_LOG_EMERG("%s: set_optimum_mode:L8 - High current\n",__func__);
			rc = regulator_set_optimum_mode(reg_l8, 70000);
			if (rc < 0) {
				pr_err("set_optimum_mode l8 failed, rc=%d\n", rc);
			}
			DISP_LOCAL_LOG_EMERG("%s: set_optimum_mode:L2 High current\n",__func__);
			rc = regulator_set_optimum_mode(reg_l2, 40000);
			if (rc < 0) {
				pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
			}
			gpio_set_value(48, 0);
			msleep(5);
			gpio_set_value(48, 1);
			msleep(10);	
			DISP_LOCAL_LOG_EMERG("%s:end\n",__func__);
			return 0;
		}
		if(disp_state > LOCAL_DISPLAY_POWER_OFF) {
			DISP_LOCAL_LOG_EMERG("%s:end Double call of power supply ON\n",__func__);
			return 0;
		}
	}
	else {
		if(disp_state == LOCAL_DISPLAY_ON){
			DISP_LOCAL_LOG_EMERG("%s: set_optimum_mode:L8 Low current\n",__func__);
			rc = regulator_set_optimum_mode(reg_l8, 100);
			if (rc < 0) {
				pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
			}
			DISP_LOCAL_LOG_EMERG("%s: set_optimum_mode:L2 Low current\n",__func__);
			rc = regulator_set_optimum_mode(reg_l2, 100);
			if (rc < 0) {
				pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
			}
			DISP_LOCAL_LOG_EMERG("%s:end\n",__func__);
			return 0;
		}
		if(disp_state < LOCAL_DISPLAY_POWER_ON) {
			DISP_LOCAL_LOG_EMERG("%s:end Double call of power supply OFF\n",__func__);
			return 0;
		}
	}

	if (disp_state == LOCAL_DISPLAY_DEF) {
		reg_lsv5 = regulator_get(&msm_mipi_dsi1_device.dev,
				"dsi_vddio");
		if (IS_ERR(reg_lsv5)) {
			pr_err("could not get 8921_lvs5, rc = %ld\n",
				PTR_ERR(reg_lsv5));
			goto panel_power_err;
		}
		reg_l8 = regulator_get(&msm_mipi_dsi1_device.dev,
				"dsi_vdc");
		if (IS_ERR(reg_l8)) {
			pr_err("could not get 8921_l8, rc = %ld\n",
				PTR_ERR(reg_l8));
			goto panel_power_err;
		}
		reg_l2 = regulator_get(&msm_mipi_dsi1_device.dev,
				"dsi_vdda");
		if (IS_ERR(reg_l2)) {
			pr_err("could not get 8921_l2, rc = %ld\n",
				PTR_ERR(reg_l2));
			goto panel_power_err;
		}
		rc = regulator_set_voltage(reg_l8, 2800000, 2800000);
		if (rc) {
			pr_err("set_voltage l8 failed, rc=%d\n", rc);
			goto panel_power_err;
		}
		rc = regulator_set_voltage(reg_l2, 1200000, 1200000);
		if (rc) {
			pr_err("set_voltage l2 failed, rc=%d\n", rc);
			goto panel_power_err;
		}
		rc = gpio_request(48, "disp_rst_n");
		if (rc) {
			pr_err("request gpio 48 failed, rc=%d\n", rc);
			goto panel_power_err;
		}
		if (gpio_get_value(48) == 1) {
			pr_info("%s already power on\n", __func__);
			dsi_boot_on = 1;
		}
		disp_ext_util_set_disp_state(LOCAL_DISPLAY_POWER_OFF);
	}

	if (on)
	{
		rc = regulator_set_optimum_mode(reg_l8, 70000);
		if (rc < 0) {
			pr_err("set_optimum_mode l8 failed, rc=%d\n", rc);
			goto panel_power_err;
		}
		rc = regulator_set_optimum_mode(reg_l2, 40000);
		if (rc < 0) {
			pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
			goto panel_power_err;
		}

		if (!dsi_boot_on) {
			gpio_set_value(48, 0);
			msleep(5);
		}
		// VLCDIO(PM8921 LVS5) ON
		rc = regulator_enable(reg_lsv5);
		if (rc) {
			pr_err("enable 8921_lvs5 failed, rc=%d\n", rc);
			goto panel_power_err;
		}

		if (!dsi_boot_on) {
			msleep(5);
		}

		// VLCD(PM8921 L8) ON
		rc = regulator_enable(reg_l8);
		if (rc) {
			pr_err("enable l8 failed, rc=%d\n", rc);
			goto panel_power_err;
		}

		if (!dsi_boot_on) {
			msleep(5);
			gpio_set_value(48, 1);
		}

		rc = regulator_enable(reg_l2);
		if (rc) {
			pr_err("enable l2 failed, rc=%d\n", rc);
			goto panel_power_err;
		}

		if (!dsi_boot_on) {
			msleep(10);
		}
		disp_ext_util_set_disp_state(LOCAL_DISPLAY_POWER_ON);
	}
	else
	{
		disp_ext_util_set_disp_state(LOCAL_DISPLAY_POWER_OFF);
		/* release HW reset */  
		gpio_set_value(48, 0);

		rc = regulator_disable(reg_l2);
		if (rc) {
			pr_err("disable reg_l2 failed, rc=%d\n", rc);
			goto panel_power_err;
		}
		msleep(5);

		// VLCD(PM8921 L8) OFF
		rc = regulator_disable(reg_l8);
		if (rc) {
			pr_err("disable reg_l8 failed, rc=%d\n", rc);
			goto panel_power_err;
		}
		msleep(100);
		// VLCDIO(PM8921 LVS5) OFF
		rc = regulator_disable(reg_lsv5);
		if (rc) {
			pr_err("disable 8921_lvs5 failed, rc=%d\n", rc);
			goto panel_power_err;
		}
		rc = regulator_set_optimum_mode(reg_l2, 100);
		if (rc < 0) {
			pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
			goto panel_power_err;
		}
		rc = regulator_set_optimum_mode(reg_l8, 100);
		if (rc < 0) {
			pr_err("set_optimum_mode l8 failed, rc=%d\n", rc);
			goto panel_power_err;
		}
	}
	DISP_LOCAL_LOG_EMERG("%s:end\n", __func__);

	return 0;

panel_power_err:
	DISP_LOCAL_LOG_EMERG("%s:err end\n", __func__);
	return -ENODEV;
}

int mipi_renesas_cm_lcd_on_exec(struct msm_fb_data_type *mfd)
{
	struct fb_info *fbi;
	local_disp_state_enum disp_state;
	int is_boot;
	pr_debug("%s:start\n", __func__);
    DISP_LOCAL_LOG_EMERG("DISP mipi_novatek_wxga_lcd_on_exec S\n");

#ifdef CONFIG_DISP_EXT_UTIL
	disp_ext_util_disp_local_lock();
#endif /* CONFIG_DISP_EXT_UTIL */
	disp_state = disp_ext_util_get_disp_state();
	if (disp_state == LOCAL_DISPLAY_ON) {
#ifdef CONFIG_DISP_EXT_UTIL
		disp_ext_util_disp_local_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
		DISP_LOCAL_LOG_EMERG("DISP mipi_novatek_wxga_lcd_on_exec disp_state(%d) E\n",disp_state);
		return 0;
	}
	mdp4_dsi_cmd_busy();
	mipi_dsi_mdp_busy_wait();
	if (TM_GET_PID(mfd->panel.id) == MIPI_DSI_PANEL_WVGA) {
		/* panel power on */
		if ( mipi_renesas_cm_panel_power( 1 ) ) {
#ifdef CONFIG_DISP_EXT_UTIL
			disp_ext_util_disp_local_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
			return -ENODEV;
		}
		is_boot = (disp_ext_board_get_panel_detect() == 0) ? 1 : 0;

#ifdef CONFIG_DISP_EXT_BOARD
		if( disp_ext_board_detect_board(mfd) == -1 ) {
			mipi_renesas_cm_panel_power( 0 );
			pr_err("%s:disp_ext_board_detect_board err:\n", __func__);
#ifdef CONFIG_DISP_EXT_UTIL
			disp_ext_util_disp_local_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
			return 0;
		}
#endif /* CONFIG_DISP_EXT_BOARD */

		fbi = mfd->fbi;
		memset(fbi->screen_base, 0x00, fbi->fix.smem_len);
		pr_debug("%s:Frame buffer clear addr=%#X size=%d\n", __func__,(uint)fbi->screen_base,fbi->fix.smem_len);
		clean_and_invalidate_caches((unsigned long)fbi->screen_base,
			(unsigned long)fbi->fix.smem_len,
			(unsigned long)fbi->fix.smem_start);

		if (is_boot) {
			if(disp_ext_board_get_panel_detect() == 1) {
				config_set_page_address[2] = 0x40;
				config_set_page_address[4] = 0x5F;
				config_set_address_mode[1] = 0xC0;
			}
		}

		mdp4_dsi_clock_mod();

		if (!(is_boot && dsi_boot_on)) {
			/* Initial sequence */
			mipi_set_tx_power_mode(0);
			mipi_dsi_clk_cfg(1);
			mipi_dsi_cmds_tx(&renesas_cm_tx_buf,
				renesas_cm_display_on_th_cmds,
				ARRAY_SIZE(renesas_cm_display_on_th_cmds));
			/* Clear screen */
			mdp4_dsi_refresh_screen_at_once( mfd );
			/* Initial sequence, display-on */
			mipi_set_tx_power_mode(0);
			mipi_dsi_cmds_tx(&renesas_cm_tx_buf,
				renesas_cm_display_on_bh_cmds,
				ARRAY_SIZE(renesas_cm_display_on_bh_cmds));
			mipi_dsi_clk_cfg(0);
		} else {
			pr_info("%s skip initalize\n", __func__);
		}
		
		disp_ext_util_set_disp_state(LOCAL_DISPLAY_ON);
#ifdef CONFIG_DISP_EXT_REFRESH
		disp_ext_reflesh_set_sw(0);
		disp_ext_refresh_te_monitor_timer_release();
		disp_ext_reflesh_before_te_run_count_init();
#endif /* CONFIG_DISP_EXT_REFRESH */
	}
	else {
#ifdef CONFIG_DISP_EXT_UTIL
		disp_ext_util_disp_local_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
		pr_err("%s:err end\n", __func__);
		return -EINVAL;
	}

#ifdef CONFIG_DISP_EXT_UTIL
	disp_ext_util_disp_local_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
	pr_debug("%s:end\n", __func__);
    DISP_LOCAL_LOG_EMERG("DISP mipi_novatek_wxga_lcd_on_exec E\n");
	return 0;
}

static int mipi_renesas_cm_lcd_on(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;
  
	pr_debug("%s:start\n", __func__);
    DISP_LOCAL_LOG_EMERG("DISP mipi_novatek_wxga_lcd_on\n");

	mfd = platform_get_drvdata(pdev);
	pr_info("%s\n", __func__);
	mipi_renesas_cm_mfd = mfd;

	if (!mfd) {
		return -ENODEV;
	}
	if (mfd->key != MFD_KEY) {
		return -EINVAL;
	}

	return mipi_renesas_cm_lcd_on_exec(mfd);
}

int mipi_renesas_cm_lcd_off_exec(struct msm_fb_data_type *mfd)
{
	pr_debug("%s:start\n", __func__);
    DISP_LOCAL_LOG_EMERG("DISP mipi_novatek_wxga_lcd_off_exec S\n");

#ifdef CONFIG_DISP_EXT_UTIL
	disp_ext_util_disp_local_lock();
#endif /* CONFIG_DISP_EXT_UTIL */
	if (disp_ext_util_get_disp_state() != LOCAL_DISPLAY_ON) {
#ifdef CONFIG_DISP_EXT_UTIL
		disp_ext_util_disp_local_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
		DISP_LOCAL_LOG_EMERG("DISP mipi_novatek_wxga_lcd_off_exec disp_state(%d) E\n",disp_ext_util_get_disp_state());
		return 0;
	}
	mdp4_dsi_cmd_busy();
	mipi_dsi_mdp_busy_wait();
	mdp4_dsi_clock_mod();
#ifdef CONFIG_DISP_EXT_REFRESH
	disp_ext_refresh_te_monitor_timer_release();
#endif /* CONFIG_DISP_EXT_REFRESH */

	mipi_set_tx_power_mode(0);
	mipi_dsi_clk_cfg(1);
	mipi_dsi_cmds_tx(&renesas_cm_tx_buf, renesas_cm_display_off_th_cmds,
			ARRAY_SIZE(renesas_cm_display_off_th_cmds));
	/* LowSpeed */
	mipi_set_tx_power_mode(1);
	mipi_dsi_cmds_tx(&renesas_cm_tx_buf, renesas_cm_display_off_bh_cmds,
			ARRAY_SIZE(renesas_cm_display_off_bh_cmds));
	mipi_dsi_clk_cfg(0);

	mipi_renesas_cm_panel_power(0);

	disp_ext_util_set_disp_state(LOCAL_DISPLAY_OFF);
	disp_ext_reflesh_set_sw(0);
#ifdef CONFIG_DISP_EXT_UTIL
	disp_ext_util_disp_local_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
	pr_debug("%s:end\n", __func__);
    DISP_LOCAL_LOG_EMERG("DISP mipi_novatek_wxga_lcd_off_exec E\n");
	return 0;
}

static int mipi_renesas_cm_lcd_off(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;

	pr_debug("%s:start\n", __func__);
    DISP_LOCAL_LOG_EMERG("DISP mipi_novatek_wxga_lcd_off\n");

	mfd = platform_get_drvdata(pdev);

	if (!mfd) {
		return -ENODEV;
	}
	if (mfd->key != MFD_KEY) {
		return -EINVAL;
	}

	pr_info("%s\n", __func__);
	return mipi_renesas_cm_lcd_off_exec(mfd);
}

static void mipi_renesas_cm_shutdown(struct platform_device *pdev)
{
	pr_debug("%s:ST\n", __func__);
    DISP_LOCAL_LOG_EMERG("DISP mipi_renesas_cm_shutdown S\n");

#ifdef CONFIG_DISP_EXT_BLC
	(void)light_led_cabc_set(LIGHT_MAIN_WLED_CABC_OFF);
#endif /* CONFIG_DISP_EXT_BLC */

#ifdef CONFIG_DISP_EXT_UTIL
	disp_ext_util_mipitx_lock();
#endif /* CONFIG_DISP_EXT_UTIL */
	if (disp_ext_util_get_disp_state() == LOCAL_DISPLAY_POWER_OFF) {
		pr_debug("%s() Display shutdown Now\n", __func__);
		DISP_LOCAL_LOG_EMERG("%s() Display shutdown Now\n", __func__);
#ifdef CONFIG_DISP_EXT_UTIL
		disp_ext_util_mipitx_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
		return;
	}

	if( mipi_renesas_cm_mfd != NULL ) {
		if( disp_ext_util_get_disp_state() == LOCAL_DISPLAY_ON){
			pr_debug("%s() Display deepstandby \n", __func__);
			DISP_LOCAL_LOG_EMERG("%s() Display deepstandby \n", __func__);
			mipi_renesas_cm_lcd_off_exec(mipi_renesas_cm_mfd);
		}
	}

#ifdef CONFIG_DISP_UTIL_DSI_CLK_OFF
	disp_ext_util_dsi_clk_off();
#endif /*CONFIG_DISP_UTIL_DSI_CLK_OFF*/

	pr_debug("%s() Display power off \n", __func__);
	DISP_LOCAL_LOG_EMERG("%s() Display power off \n", __func__);
#ifdef CONFIG_DISP_EXT_UTIL
	disp_ext_util_disp_local_lock();
#endif /* CONFIG_DISP_EXT_UTIL */
	mipi_renesas_cm_panel_power( 0 );
#ifdef CONFIG_DISP_EXT_UTIL
	disp_ext_util_disp_local_unlock();
	disp_ext_util_mipitx_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */

	pr_debug("%s() ED\n", __func__);
    DISP_LOCAL_LOG_EMERG("DISP mipi_renesas_cm_shutdown E\n");
}

static void mipi_renesas_cm_set_backlight(struct msm_fb_data_type *mfd)
{
	pr_debug("No Support %s: back light level %d\n", __func__, mfd->bl_level);
}

static int __devinit mipi_renesas_cm_lcd_probe(struct platform_device *pdev)
{
	if (pdev->id == 0) {
		mipi_renesas_cm_pdata = pdev->dev.platform_data;
		return 0;
	}

	if (mipi_renesas_cm_pdata == NULL) {
		pr_err("%s.invalid platform data.\n", __func__);
		return -ENODEV;
	}

	mipi_renesas_cm_panel_power(1);
	msm_fb_add_device(pdev);

	return 0;
}

static struct platform_driver this_driver = {
	.probe  = mipi_renesas_cm_lcd_probe,
	.shutdown = mipi_renesas_cm_shutdown,
	.driver = {
		.name   = "mipi_renesas_cm",
	},
};

static struct msm_fb_panel_data renesas_cm_panel_data = {
	.on		= mipi_renesas_cm_lcd_on,
	.off		= mipi_renesas_cm_lcd_off,
	.set_backlight  = mipi_renesas_cm_set_backlight,
#ifdef CONFIG_DISP_EXT_UTIL
#ifdef CONFIG_DISP_EXT_PROPERTY
	.set_nv		= disp_ext_util_set_kcjprop,
#endif /* CONFIG_DISP_EXT_PROPERTY */
#endif /* CONFIG_DISP_EXT_UTIL */
#ifdef CONFIG_DISP_EXT_REFRESH
	.refresh	= disp_ext_refresh_seq,
#endif /* CONFIG_DISP_EXT_REFRESH */
};

static int ch_used[3];
int mipi_renesas_cm_device_register(struct msm_panel_info *pinfo,
					u32 channel, u32 panel)
{
	struct platform_device *pdev = NULL;
	int ret;

	if ((channel >= 3) || ch_used[channel]) {
		return -ENODEV;
	}

	ch_used[channel] = TRUE;

	ret = mipi_renesas_cm_lcd_init();
	if (ret) {
		pr_err("mipi_renesas_cm_lcd_init() failed with ret %u\n", ret);
		return ret;
	}

	pdev = platform_device_alloc("mipi_renesas_cm", (panel << 8)|channel);
	if (!pdev) {
		return -ENOMEM;
	}

	renesas_cm_panel_data.panel_info = *pinfo;

	ret = platform_device_add_data(pdev, &renesas_cm_panel_data,
		sizeof(renesas_cm_panel_data));
	if (ret) {
		pr_err("%s: platform_device_add_data failed!\n", __func__);
		goto err_device_put;
	}

	ret = platform_device_add(pdev);
	if (ret) {
		pr_err("%s: platform_device_register failed!\n", __func__);
		goto err_device_put;
	}

#ifdef CONFIG_DISP_EXT_REFRESH
	disp_ext_refresh_set_te_monitor_init();
#endif /* CONFIG_DISP_EXT_REFRESH */

	return 0;

err_device_put:
	platform_device_put(pdev);
	return ret;
}

static int mipi_renesas_cm_lcd_init(void)
{
	mipi_dsi_buf_alloc(&renesas_cm_tx_buf, DSI_BUF_SIZE);
	mipi_dsi_buf_alloc(&renesas_cm_rx_buf, DSI_BUF_SIZE);
#ifdef CONFIG_DISP_EXT_REFRESH
	disp_ext_reflesh_init();
#endif /* CONFIG_DISP_EXT_REFRESH */
#ifdef CONFIG_DISP_EXT_BLC
	disp_ext_blc_init();
#endif /* CONFIG_DISP_EXT_BLC */
	mipi_renesas_cm_mfd = NULL;

	return platform_driver_register(&this_driver);
}

struct msm_fb_data_type *mipi_renesas_cm_get_mfd(void)
{
	return mipi_renesas_cm_mfd;
}
