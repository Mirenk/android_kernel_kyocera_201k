/*
 * This software is contributed or developed by KYOCERA Corporation.
 * (C) 2012 KYOCERA Corporation
 *
 * drivers/video/msm/disp_ext_board.c
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
#include <linux/mipi_novatek_wxga_ext.h>
#else
#include "mipi_renesas_cm.h"
#endif
#include "mdp4.h"
#include "disp_ext.h"
#ifdef CONFIG_DISP_EXT_BLC
#include <linux/leds-lm3533.h>
#endif /* CONFIG_DISP_EXT_BLC */

#define DETECT_BOARD_NUM 5

#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
static char detect_board_cmd1_select[4]    = { 0xFF, 0x00, DTYPE_DCS_WRITE1, 0x80 };
static char detect_board_mipi_lane_read[4] = { 0xBA, 0x00, DTYPE_DCS_READ  , 0xA0 };
static char maximum_return_seze_set[4] = { 0x01, 0x00, DTYPE_MAX_PKTSIZE  , 0x80 };
#else
static char detect_board_mipi_lane_read[4] = { 0xA1, 0x00, DTYPE_DCS_READ  , 0xA0 };
static char maximum_return_seze_set[4] = { 0x06, 0x00, DTYPE_MAX_PKTSIZE  , 0x80 };
#endif
extern struct device dsi_dev;
static int panel_detection=0;       /* -1:not panel 0:Not test 1:panel found */
static int disp_ext_board_cmd_tx( char *cm , int size ,int time )
{
	char pload[256];
	int video_mode;
	uint32 dsi_ctrl, ctrl;
	uint32_t off;
	uint32_t ReadValue;
	uint32_t count = 0;

	dma_addr_t dmap;
	
	pr_debug("%s:S\n", __func__);
    DISP_LOCAL_LOG_EMERG("DISP disp_ext_board_cmd_tx S\n");

	/* Align pload at 8 byte boundry */
	off = (uint32_t)pload;
	off &= 0x07;
	if (off) {
		off = 8 - off;
	}
	off += (uint32_t)pload;
	memcpy((void *)off, cm, size);
	ctrl = 0;
	dsi_ctrl = MIPI_INP(MIPI_DSI_BASE + 0x0000);
	video_mode = dsi_ctrl & 0x02;                       /* VIDEO_MODE_EN */
	if (video_mode) {
		ctrl = dsi_ctrl | 0x04;                         /* CMD_MODE_EN */
		MIPI_OUTP(MIPI_DSI_BASE + 0x0000, ctrl);
	}
	dmap = dma_map_single(&dsi_dev, (char *)off, size, DMA_TO_DEVICE);
	
	MIPI_OUTP(MIPI_DSI_BASE + 0x0044, dmap);             /* DSI1_DMA_CMD_OFFSET */
	MIPI_OUTP(MIPI_DSI_BASE + 0x0048, size);            /* DSI1_DMA_CMD_LENGTH */
	wmb();
	MIPI_OUTP(MIPI_DSI_BASE + 0x08c, 0x01);             /* trigger */
	wmb();
	udelay(1);

	if( time != 0 ) {
		pr_debug("%s:wait %d ms\n", __func__,time);
		mdelay(time);
	}
	ReadValue = MIPI_INP(MIPI_DSI_BASE + 0x010C) & 0x00000001;
	pr_debug("%s:S MIPI_INP(MIPI_DSI_BASE + 0x010C)=%x\n", __func__,MIPI_INP(MIPI_DSI_BASE + 0x010C));
	if( time != 0 && ReadValue != 0x00000001 ) {
		pr_err("%s:send command timeout(%d ms)\n", __func__,time);
		dma_unmap_single(&dsi_dev, dmap, size, DMA_TO_DEVICE);
		return -1;
	}

	while (ReadValue != 0x00000001) {
		ReadValue = MIPI_INP(MIPI_DSI_BASE + 0x010C) & 0x00000001;
		count++;
		if (count > 0xffff) {
			pr_err("%s:send command timeout__\n", __func__);
			dma_unmap_single(&dsi_dev, dmap, size, DMA_TO_DEVICE);
			return -1;
		}
	}
	mdelay(5);

	MIPI_OUTP(MIPI_DSI_BASE + 0x010C, MIPI_INP(MIPI_DSI_BASE + 0x010C) | 0x01000001);

	if (video_mode) {
		MIPI_OUTP(MIPI_DSI_BASE + 0x0000, dsi_ctrl);    /* restore */
	}
	dma_unmap_single(&dsi_dev, dmap, size, DMA_TO_DEVICE);
	pr_debug("%s:E\n", __func__);
    DISP_LOCAL_LOG_EMERG("DISP disp_ext_board_cmd_tx E\n");
	return 0;
}

int disp_ext_board_detect_board(struct msm_fb_data_type *mfd)
{
	int i;
	int ret = 0;
	int panel_found;
#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
	uint32_t data;
#else
	uint32_t data[2];
#endif

    DISP_LOCAL_LOG_EMERG("DISP disp_ext_board_detect_board S\n");

	if( panel_detection != 0 ) {
		pr_debug("%s:panel Checked\n", __func__);
		DISP_LOCAL_LOG_EMERG("%s:panel Checked\n", __func__);
		return panel_detection;
	}
	mipi_dsi_op_mode_config(DSI_CMD_MODE);

#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
	/* cmd1 select */
	ret = disp_ext_board_cmd_tx( detect_board_cmd1_select, sizeof(detect_board_cmd1_select), 0 );
	if ( ret != 0 ) {
		pr_err("%s:command send err1\n", __func__);
		mipi_dsi_op_mode_config(mfd->panel_info.mipi.mode);
		light_led_disp_set(LIGHT_MAIN_WLED_LCD_DIS);

		panel_detection = -1;
		return panel_detection;
	}
#endif

#ifdef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
	mipi_dsi_clk_cfg(1);
#endif
	panel_found = 0;
	for( i = 0 ; i < DETECT_BOARD_NUM ; i++ ) {
		/* MIPI_DSI_MRPS, Maximum Return Packet Size */
		if (!mfd->panel_info.mipi.no_max_pkt_size) {
			disp_ext_board_cmd_tx( maximum_return_seze_set , sizeof(maximum_return_seze_set), 0 );
		}
		ret = disp_ext_board_cmd_tx( detect_board_mipi_lane_read , sizeof(detect_board_mipi_lane_read), 5 );
		if ( ret != 0 ) {
			pr_err("%s:ack no receive\n", __func__);
			mipi_dsi_op_mode_config(mfd->panel_info.mipi.mode);
			light_led_disp_set(LIGHT_MAIN_WLED_LCD_DIS);
			panel_detection = -1;
			return panel_detection;
		}
#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
	    data = (uint32)MIPI_INP(MIPI_DSI_BASE + 0x68);

	    if( ((data >> 16) & 0xFF) == 0x02 ) {
			panel_found = 1;
			break;
		}
#else
		data[0] = (uint32)MIPI_INP(MIPI_DSI_BASE + 0x6C);
		data[1] = (uint32)MIPI_INP(MIPI_DSI_BASE + 0x68);
		data[1] &= 0xffff0000;
		pr_info("%s: device code=%04x %04x\n",
			 __func__,
			data[0],
			data[1]
			);

		if ( (data[0] == 0x01010101)&&(data[1] == 0x00ff0000) ) {
			panel_found = 1;
			break;
		}
		else if ( (data[0] == 0x02020202)&&(data[1] == 0x00ff0000) ) {
			panel_found = 2;
			break;
		}
#endif
	}
#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
	if( panel_found != 1 ) {
#else
	mipi_dsi_clk_cfg(0);
	if( panel_found != 1 && panel_found != 2) {
#endif
		pr_debug("%s:panel not found\n", __func__);
		DISP_LOCAL_LOG_EMERG("%s:panel not found 2\n", __func__);
		mipi_dsi_op_mode_config(mfd->panel_info.mipi.mode);
		light_led_disp_set(LIGHT_MAIN_WLED_LCD_DIS);
		panel_detection = -1;
		return panel_detection;
	}
	pr_debug("%s:panel found\n", __func__);
	DISP_LOCAL_LOG_EMERG("%s:panel found\n", __func__);
	mipi_dsi_op_mode_config(mfd->panel_info.mipi.mode);
	light_led_disp_set(LIGHT_MAIN_WLED_LCD_EN);
	

    DISP_LOCAL_LOG_EMERG("DISP disp_ext_board_detect_board E\n");
#ifndef CONFIG_FB_MSM_MIPI_DSI_RENESAS_CM
	panel_detection = 1;
#else
	panel_detection = panel_found;
#endif
	return panel_detection;
}

int disp_ext_board_get_panel_detect(void)
{
    return panel_detection;
}
