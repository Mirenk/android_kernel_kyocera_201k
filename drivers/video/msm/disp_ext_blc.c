/*
 * This software is contributed or developed by KYOCERA Corporation.
 * (C) 2012 KYOCERA Corporation
 *
 * drivers/video/msm/disp_ext_blc.c
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
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include "msm_fb.h"
#include "mipi_dsi.h"
#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
#include "mipi_novatek_wxga.h"
#else
#include "mipi_renesas_cm.h"
#endif
#include <linux/disp_ext_blc.h>
#include "mdp4.h"
#include "disp_ext.h"

static struct dsi_buf disp_ext_blc_tx_buf;
static struct dsi_buf disp_ext_blc_rx_buf;

static uint8  select_mode=0;
static uint8  select_mode_ctrl=0;
/* cabc select */
#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
static char cmd1_select[2] = {0xFF, 0x00};
static char cabc_change[2] = {0x55, 0x00};
static struct dsi_cmd_desc cabc_mode_select_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd1_select), cmd1_select},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cabc_change), cabc_change},
};
#else
/* .. Manufacture Command Access Protect */
static char config_mcap_enter[2] = {0xB0, 0x04};
static char config_mcap_leave[2] = {0xB0, 0x03};
/* 12. BLC ON : BLC10 */
static char config_blc1_on[21] =
	{0xB8, 0x01, 0x03, 0x03, 0xFF, 0xFF, 0xED,
	 0xED, 0x02, 0x18, 0x90, 0x90, 0x37, 0x5A,
	 0x87, 0xBE, 0xFF, 0x00, 0x00, 0x00, 0x00};
static char config_blc2[5] = {0xB9, 0x00, 0xFF, 0x02, 0x08};
/* 12. BLC OFF */
static char config_blc1_off[2] = {0xB8, 0x00};
static struct dsi_cmd_desc renesas_cm_blc_on_cmds[] = {
	/* 12. BLC ON : BLC10 */
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,
		sizeof(config_mcap_enter),
			config_mcap_enter},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(config_blc1_on),
			config_blc1_on},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(config_blc2),
			config_blc2},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,
		sizeof(config_mcap_leave),
			config_mcap_leave},
};
static struct dsi_cmd_desc renesas_cm_blc_off_cmds[] = {
	/* 12. BLC OFF */
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,
		sizeof(config_mcap_enter),
			config_mcap_enter},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(config_blc1_off),
			config_blc1_off},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,
		sizeof(config_mcap_leave),
			config_mcap_leave},
};
static struct dsi_cmd_desc *cabc_mode_select_cmds;
static int cabc_mode_select_cmds_size;
#endif

uint8 disp_ext_blc_get_select_mode(void)
{
	return select_mode;
}

void disp_ext_blc_set_select_mode(uint8 sw)
{
	select_mode = sw;
}

int disp_ext_blc_mode_select( uint8_t mode )
{
	struct msm_fb_data_type *mfd;

    DISP_LOCAL_LOG_EMERG("DISP mipi_novatek_wxga_cabc_mode_select mode=%d S\n",mode);
#ifdef CONFIG_DISP_EXT_UTIL
	disp_ext_util_mipitx_lock();
	disp_ext_util_disp_local_lock();
#endif /* CONFIG_DISP_EXT_UTIL */
	if( disp_ext_util_get_disp_state() != LOCAL_DISPLAY_ON ) {
#ifdef CONFIG_DISP_EXT_UTIL
		disp_ext_util_disp_local_unlock();
		disp_ext_util_mipitx_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
		pr_err("%s:panel off\n", __func__);
		return -1;
	}

	if( mode > 0x01 ) {
#ifdef CONFIG_DISP_EXT_UTIL
		disp_ext_util_disp_local_unlock();
		disp_ext_util_mipitx_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
		pr_err("%s:parameter err\n", __func__);
		return -1;
	}

	if( select_mode_ctrl == mode ) {
#ifdef CONFIG_DISP_EXT_UTIL
		disp_ext_util_disp_local_unlock();
		disp_ext_util_mipitx_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
		DISP_LOCAL_LOG_EMERG("%s:Request a double. state=%d,req=%d\n",__func__,select_mode_ctrl,mode);
		return 0;
	}

#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
	mfd = mipi_novatek_wxga_get_mfd();
#else
	mfd = mipi_renesas_cm_get_mfd();
#endif
	if( mfd == NULL ) {
#ifdef CONFIG_DISP_EXT_UTIL
		disp_ext_util_disp_local_unlock();
		disp_ext_util_mipitx_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
		pr_err("%s:mfd == NULL\n", __func__);
		return -1;
	}

	select_mode_ctrl=mode;

	msm_fb_pan_lock();
	msm_fb_ioctl_ppp_lock();
	msm_fb_ioctl_lut_lock();
#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
	mdp4_dsi_cmd_dma_busy_wait(mfd);
	mdp4_dsi_blt_dmap_busy_wait(mfd);
	mipi_dsi_mdp_busy_wait(mfd);
#else
	mdp4_dsi_cmd_busy();
	mipi_dsi_mdp_busy_wait();
#endif
	if( mode == 0 ) {
#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
		cabc_change[1] = 0;
#else
		cabc_mode_select_cmds = renesas_cm_blc_off_cmds;
		cabc_mode_select_cmds_size = ARRAY_SIZE(renesas_cm_blc_off_cmds);
#endif
	}
	else {
#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
		cabc_change[1] = select_mode;
#else
		cabc_mode_select_cmds = renesas_cm_blc_on_cmds;
		cabc_mode_select_cmds_size = ARRAY_SIZE(renesas_cm_blc_on_cmds);
#endif
	}
#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
	pr_debug("%s:cabc_change[%d,%d]\n", __func__,cabc_change[0],cabc_change[1]);
	DISP_LOCAL_LOG_EMERG("%s:cabc_change[%d,%d]\n", __func__,cabc_change[0],cabc_change[1]);
#endif
#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
	mipi_dsi_cmds_tx(mfd, &disp_ext_blc_tx_buf,
					cabc_mode_select_cmds,
					ARRAY_SIZE(cabc_mode_select_cmds));
#else
	mipi_set_tx_power_mode(0);
	mipi_dsi_clk_cfg(1);
	mipi_dsi_cmds_tx(&disp_ext_blc_tx_buf,
					cabc_mode_select_cmds,
					cabc_mode_select_cmds_size);
	mipi_dsi_clk_cfg(0);
#endif
	udelay(1);

	msm_fb_ioctl_lut_unlock();
	msm_fb_ioctl_ppp_unlock();
	msm_fb_pan_unlock();
#ifdef CONFIG_DISP_EXT_UTIL
	disp_ext_util_disp_local_unlock();
	disp_ext_util_mipitx_unlock();
#endif /* CONFIG_DISP_EXT_UTIL */
	pr_debug("%s:cabc select\n", __func__);
    DISP_LOCAL_LOG_EMERG("DISP mipi_novatek_wxga_cabc_mode_select E\n");
	return 0;
}

void disp_ext_blc_init(void)
{
	mipi_dsi_buf_alloc(&disp_ext_blc_tx_buf, DSI_BUF_SIZE);
	mipi_dsi_buf_alloc(&disp_ext_blc_rx_buf, DSI_BUF_SIZE);
}
