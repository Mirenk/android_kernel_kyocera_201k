/*
 * This software is contributed or developed by KYOCERA Corporation.
 * (C) 2012 KYOCERA Corporation
 *
 * drivers/video/msm/mipi_novatek_wxga_tbl.h
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
#ifndef MIPI_RENESAS_CM_TBL_H
#define MIPI_RENESAS_CM_TBL_H

#define RENESAS_CMD_WVGA_DELAY 0
#define RENESAS_CMD_WVGA_READ_DELAY 5
#define RENESAS_CMD_WVGA_SLEEP_OFF_DELAY 150
#define RENESAS_CMD_WVGA_SLEEP_ON_DELAY 75
#define RENESAS_CMD_WVGA_STANDBY_ON_DELAY 5

/* 3. exit_sleep_mode */
static char config_set_column_address[5] = 
	{0x2A, 0x00, 0x00, 0x01, 0xDF};
static char config_set_page_address[5] = 
	{0x2B, 0x00, 0x00, 0x03, 0x1F};
static char config_set_address_mode[2] = {0x36, 0x00};
static char config_set_pixel_fomat[2] = {0x3A, 0x77};
static char config_exit_sleep_mode[2] = {0x11, 0x00};

/* 9. set_tear_on */
static char config_set_tear_on[2] = {0x35, 0x00};

/* 12. BLC ON : BLC10 */
static char config_blc1_on[21] =
	{0xB8, 0x01, 0x03, 0x03, 0xFF, 0xFF, 0xED,
	 0xED, 0x02, 0x18, 0x90, 0x90, 0x37, 0x5A,
	 0x87, 0xBE, 0xFF, 0x00, 0x00, 0x00, 0x00};
static char config_blc2[5] = {0xB9, 0x00, 0xFF, 0x02, 0x08};


#ifdef RENESAS_DEVICE_WS0
/* 99. set_NVM */
static char config_pds2[16] = {	0xC1, 0x43, 0x31, 0x00,
								0x21, 0x21, 0x32, 0x12,
								0x28, 0x44, 0x14, 0xA5,
								0x0F, 0x58, 0x21, 0x01};
#endif

/* 5. set_display_on */
static char config_set_display_on[2] = {0x29, 0x00};

/* 6. set_display_off */
static char config_set_display_off[2] = {0x28, 0x00};

/* 12. BLC OFF */
static char config_blc1_off[2] = {0xB8, 0x00};

/* 10. set_tear_off */
static char config_set_tear_off[2] = {0x34, 0x00};

/* 4. enter_sleep_mode */
static char config_enter_sleep_mode[2] = {0x10, 0x00};

/* 7. Enter Deep Standby */
static char config_lpmc[2] = {0xB1, 0x01};

/* .. Manufacture Command Access Protect */
static char config_mcap_enter[2] = {0xB0, 0x04};
static char config_mcap_leave[2] = {0xB0, 0x03};

/* 13. Refresh */
static char config_set_tear_scanline[3] = 
	{0x44, 0x00, 0x00};

/* Power On/Resume Sequence */
static struct dsi_cmd_desc renesas_cm_display_on_th_cmds[] = {
	/* 3. exit_sleep_mode */
	{DTYPE_DCS_LWRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_column_address),
			config_set_column_address},
	{DTYPE_DCS_LWRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_page_address),
			config_set_page_address},
	{DTYPE_DCS_WRITE1, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_address_mode),
			config_set_address_mode},
	{DTYPE_DCS_WRITE1, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_pixel_fomat),
			config_set_pixel_fomat},
	{DTYPE_DCS_WRITE, 1, 0, 0, RENESAS_CMD_WVGA_SLEEP_OFF_DELAY,
		sizeof(config_exit_sleep_mode),
			config_exit_sleep_mode},
	/* 9. set_tear_on */
	{DTYPE_DCS_WRITE1, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_tear_on),
			config_set_tear_on},
	/* 12. BLC ON : BLC10 */
	{DTYPE_GEN_WRITE2, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_mcap_enter),
			config_mcap_enter},
	{DTYPE_GEN_LWRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_blc1_on),
			config_blc1_on},
	{DTYPE_GEN_LWRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_blc2),
			config_blc2},
#ifdef RENESAS_DEVICE_WS0
	{DTYPE_GEN_LWRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_pds2),
			config_pds2},
#endif
	{DTYPE_GEN_WRITE2, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_mcap_leave),
			config_mcap_leave},
};

static struct dsi_cmd_desc renesas_cm_display_on_bh_cmds[] = {
	/* 5. set_display_on */
	{DTYPE_DCS_WRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_display_on),
			config_set_display_on},
};


/* Deep Standby Sequence */
static struct dsi_cmd_desc renesas_cm_display_off_th_cmds[] = {
	/* 6. set_display_off */
	{DTYPE_DCS_WRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_display_off),
			config_set_display_off},
	/* 12. BLC OFF */
	{DTYPE_GEN_WRITE2, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_mcap_enter),
			config_mcap_enter},
	{DTYPE_GEN_LWRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_blc1_off),
			config_blc1_off},
	{DTYPE_GEN_WRITE2, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_mcap_leave),
			config_mcap_leave},
	/* 10. set_tear_off */
	{DTYPE_DCS_WRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_tear_off),
			config_set_tear_off},
	/* 4. enter_sleep_mode */
	{DTYPE_DCS_WRITE, 1, 0, 0, RENESAS_CMD_WVGA_SLEEP_ON_DELAY,
		sizeof(config_enter_sleep_mode),
			config_enter_sleep_mode},
};

static struct dsi_cmd_desc renesas_cm_display_off_bh_cmds[] = {
	/* 7. Enter Deep Standby */
	{DTYPE_GEN_WRITE2, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_mcap_enter),
			config_mcap_enter},
	{DTYPE_GEN_WRITE2, 1, 0, 0, RENESAS_CMD_WVGA_STANDBY_ON_DELAY,
		sizeof(config_lpmc),
			config_lpmc},
};

static struct dsi_cmd_desc renesas_cm_refresh_cmds[] = {
	{DTYPE_DCS_LWRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_column_address),
			config_set_column_address},
	{DTYPE_DCS_LWRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_page_address),
			config_set_page_address},
	{DTYPE_DCS_WRITE1, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_tear_on),
			config_set_tear_on},
	{DTYPE_DCS_WRITE1, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_address_mode),
			config_set_address_mode},
	{DTYPE_DCS_WRITE1, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_pixel_fomat),
			config_set_pixel_fomat},
	{DTYPE_DCS_LWRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_tear_scanline),
			config_set_tear_scanline},
	{DTYPE_DCS_WRITE, 1, 0, 0, RENESAS_CMD_WVGA_SLEEP_OFF_DELAY,
		sizeof(config_exit_sleep_mode),
			config_exit_sleep_mode},
	{DTYPE_GEN_WRITE2, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_mcap_enter),
			config_mcap_enter},
	{DTYPE_GEN_LWRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_blc1_on),
			config_blc1_on},
	{DTYPE_GEN_LWRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_blc2),
			config_blc2},
	{DTYPE_GEN_WRITE2, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_mcap_leave),
			config_mcap_leave},
	{DTYPE_DCS_WRITE, 1, 0, 0, RENESAS_CMD_WVGA_DELAY,
		sizeof(config_set_display_on),
			config_set_display_on},
};

#endif  /* MIPI_RENESAS_CM_TBL_H */
