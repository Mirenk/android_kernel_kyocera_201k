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
#ifndef MIPI_NOVATEK_WXGA_TBL_H
#define MIPI_NOVATEK_WXGA_TBL_H

/* DTYPE_DCS_WRITE */
static char exit_sleep[2]  = {0x11, 0x00};
static char display_on[2]  = {0x29, 0x00};
static char display_off[2] = {0x28, 0x00};
static char enter_sleep[2] = {0x10, 0x00};
static char enter_deep_standby[2] = {0x4F, 0x01};

/* DTYPE_DCS_WRITE1 */
/* DTYPE_GEN_WRITE2 */
static char set_mipi_lane[2] = {0xBA, 0x02}; /* 3lane */
static char mpi_mode[2]      = {0xC2, 0x08}; /* 0x03(VIDEO Mode, GRAM acceces disable)  */
                                             /* 0x08(Command Mode, GRAM acceces enable) */
                                             /* 0x0B(VIDEO Mode, GRAM acceces enable)   */
/* DTYPE_DCS_WRITE1 */
static char cmd1_select[2]    = {0xFF, 0x00};
static char cmd2_select_01[2] = {0xFF, 0x01};
static char cmd2_select_02[2] = {0xFF, 0x02};
static char cmd2_select_04[2] = {0xFF, 0x04};
static char cmd2_select_05[2] = {0xFF, 0x05};
static char cmd2_select_EE[2] = {0xFF, 0xEE};

/* Initial sequence data *//* DTYPE_GEN_WRITE2 */
/* step4_001 = cmd2_select_05 */
static char step4_002[2] = {0xFB, 0x01};
static char step4_003[2] = {0x01, 0x00};
static char step4_004[2] = {0x02, 0x8D};
static char step4_005[2] = {0x03, 0x8E};
static char step4_006[2] = {0x04, 0x8E};
static char step4_007[2] = {0x05, 0x00};
static char step4_008[2] = {0x06, 0x00};
static char step4_009[2] = {0x07, 0x00};
static char step4_010[2] = {0x08, 0x00};
static char step4_011[2] = {0x09, 0x00};
static char step4_012[2] = {0x0A, 0x8E};
static char step4_013[2] = {0x0B, 0x78};
static char step4_014[2] = {0x0D, 0x06};
static char step4_015[2] = {0x0E, 0x19};
static char step4_016[2] = {0x0F, 0x0A};
static char step4_017[2] = {0x10, 0x71};
static char step4_018[2] = {0x14, 0x05};
static char step4_019[2] = {0x16, 0x07};
static char step4_020[2] = {0x17, 0x00};
static char step4_021[2] = {0x19, 0x03};
static char step4_022[2] = {0x1A, 0x00};
static char step4_023[2] = {0x1B, 0xFC};
static char step4_024[2] = {0x1C, 0x00};
static char step4_025[2] = {0x1D, 0x00};
static char step4_026[2] = {0x1E, 0x00};
static char step4_027[2] = {0x1F, 0x00};
static char step4_028[2] = {0x21, 0x00};
static char step4_029[2] = {0x23, 0x4D};
static char step4_030[2] = {0x6C, 0x00};
static char step4_031[2] = {0x6D, 0x00};
static char step4_032[2] = {0x24, 0x45};
static char step4_033[2] = {0x26, 0x55};
static char step4_034[2] = {0x27, 0x55};
static char step4_035[2] = {0x28, 0x00};
static char step4_036[2] = {0x29, 0x52};
static char step4_037[2] = {0x2A, 0xA9};
static char step4_038[2] = {0x2B, 0x12};
static char step4_039[2] = {0x2D, 0x02};
static char step4_040[2] = {0x2F, 0x00};
static char step4_041[2] = {0x32, 0x00};
static char step4_042[2] = {0x33, 0xB8};
static char step4_043[2] = {0x35, 0x16};
static char step4_044[2] = {0x36, 0x00};
static char step4_045[2] = {0x37, 0x09};
static char step4_046[2] = {0x38, 0x00};
static char step4_047[2] = {0x39, 0x00};
static char step4_048[2] = {0x49, 0x00};
static char step4_049[2] = {0x4A, 0x01};
static char step4_050[2] = {0x82, 0x18};
static char step4_051[2] = {0x89, 0x00};
static char step4_052[2] = {0x8D, 0x01};
static char step4_053[2] = {0x8E, 0x64};
static char step4_054[2] = {0x8F, 0x20};
static char step4_055[2] = {0x92, 0x00};
static char step4_056[2] = {0x9E, 0x60};
static char step4_057[2] = {0x9F, 0x6B};
static char step4_058[2] = {0xA2, 0x10};
static char step4_059[2] = {0xA4, 0x05};
static char step4_060[2] = {0xBB, 0x0A};
static char step4_061[2] = {0xBC, 0x0A};
/* step4_062 = cmd1_select */
/* step4_063 = cmd2_select_01 */
static char step4_064[2] = {0xFB, 0x01};
static char step4_065[2] = {0x00, 0x2A};
static char step4_066[2] = {0x01, 0x33};
static char step4_067[2] = {0x02, 0x53};
static char step4_068[2] = {0x71, 0x2C};
static char step4_069[2] = {0x08, 0x26};
static char step4_070[2] = {0x09, 0x86};
static char step4_071[2] = {0x0B, 0xCA};
static char step4_072[2] = {0x0C, 0xCA};
static char step4_073[2] = {0x0D, 0x2F};
static char step4_074[2] = {0x0E, 0x2B};
static char step4_075[2] = {0x0F, 0x0A};
static char step4_076[2] = {0x10, 0x32};
/* static char step4_077[2] = {0x11, 0x86}; */
/* static char step4_078[2] = {0x12, 0x03}; */
static char step4_079[2] = {0x36, 0x73};
static char step4_080[2] = {0x44, 0x00};
static char step4_081[2] = {0x45, 0x80};
static char step4_082[2] = {0x46, 0x00};
/* step4_083-142 = set_gamma_R_P_xxx */
/* step4_143-202 = set_gamma_R_M_xxx */
/* step4_203-214 = set_gamma_G_P_xxx */
/* step4_215 = cmd1_select */
/* step4_216 = cmd2_select_02 */
static char step4_217[2] = {0xFB, 0x01};
/* step4_218-265 = set_gamma_G_P_xxx */
/* step4_266-325 = set_gamma_G_M_xxx */
/* step4_326-385 = set_gamma_B_P_xxx */
/* step4_386-445 = set_gamma_B_M_xxx */
/* step4_446 = cmd1_select */
/* step4_447 = cmd2_select_04 */
static char step4_448[2] = {0xFB, 0x01};
static char step4_449[2] = {0x09, 0x40};
static char step4_450[2] = {0x0A, 0x11};
static char step4_451[2] = {0x05, 0x21};
/* step4_452-455 = cabc_mode_UI_xxx */
/* step4_456-465 = cabc_mode_STILL_xxx */
/* step4_466-475 = cabc_mode_MOVING_xxx */
/* step4_476 = cmd1_select */
/* step4_477 = exit_sleep */

/* Gamma settings data *//* DTYPE_GEN_WRITE2 */
/* R+ */
static char set_gamma_R_P_001[2] = {0x75, 0x00};
static char set_gamma_R_P_002[2] = {0x76, 0x10};
static char set_gamma_R_P_003[2] = {0x77, 0x00};
static char set_gamma_R_P_004[2] = {0x78, 0x2A};
static char set_gamma_R_P_005[2] = {0x79, 0x00};
static char set_gamma_R_P_006[2] = {0x7A, 0x5D};
static char set_gamma_R_P_007[2] = {0x7B, 0x00};
static char set_gamma_R_P_008[2] = {0x7C, 0x81};
static char set_gamma_R_P_009[2] = {0x7D, 0x00};
static char set_gamma_R_P_010[2] = {0x7E, 0x99};
static char set_gamma_R_P_011[2] = {0x7F, 0x00};
static char set_gamma_R_P_012[2] = {0x80, 0xAD};
static char set_gamma_R_P_013[2] = {0x81, 0x00};
static char set_gamma_R_P_014[2] = {0x82, 0xBF};
static char set_gamma_R_P_015[2] = {0x83, 0x00};
static char set_gamma_R_P_016[2] = {0x84, 0xCF};
static char set_gamma_R_P_017[2] = {0x85, 0x00};
static char set_gamma_R_P_018[2] = {0x86, 0xDD};
static char set_gamma_R_P_019[2] = {0x87, 0x01};
static char set_gamma_R_P_020[2] = {0x88, 0x0D};
static char set_gamma_R_P_021[2] = {0x89, 0x01};
static char set_gamma_R_P_022[2] = {0x8A, 0x33};
static char set_gamma_R_P_023[2] = {0x8B, 0x01};
static char set_gamma_R_P_024[2] = {0x8C, 0x70};
static char set_gamma_R_P_025[2] = {0x8D, 0x01};
static char set_gamma_R_P_026[2] = {0x8E, 0xA1};
static char set_gamma_R_P_027[2] = {0x8F, 0x01};
static char set_gamma_R_P_028[2] = {0x90, 0xEA};
static char set_gamma_R_P_029[2] = {0x91, 0x02};
static char set_gamma_R_P_030[2] = {0x92, 0x1F};
static char set_gamma_R_P_031[2] = {0x93, 0x02};
static char set_gamma_R_P_032[2] = {0x94, 0x21};
static char set_gamma_R_P_033[2] = {0x95, 0x02};
static char set_gamma_R_P_034[2] = {0x96, 0x50};
static char set_gamma_R_P_035[2] = {0x97, 0x02};
static char set_gamma_R_P_036[2] = {0x98, 0x83};
static char set_gamma_R_P_037[2] = {0x99, 0x02};
static char set_gamma_R_P_038[2] = {0x9A, 0xA4};
static char set_gamma_R_P_039[2] = {0x9B, 0x02};
static char set_gamma_R_P_040[2] = {0x9C, 0xD0};
static char set_gamma_R_P_041[2] = {0x9D, 0x02};
static char set_gamma_R_P_042[2] = {0x9E, 0xF0};
static char set_gamma_R_P_043[2] = {0x9F, 0x03};
static char set_gamma_R_P_044[2] = {0xA0, 0x1A};
static char set_gamma_R_P_045[2] = {0xA2, 0x03};
static char set_gamma_R_P_046[2] = {0xA3, 0x27};
static char set_gamma_R_P_047[2] = {0xA4, 0x03};
static char set_gamma_R_P_048[2] = {0xA5, 0x35};
static char set_gamma_R_P_049[2] = {0xA6, 0x03};
static char set_gamma_R_P_050[2] = {0xA7, 0x44};
static char set_gamma_R_P_051[2] = {0xA9, 0x03};
static char set_gamma_R_P_052[2] = {0xAA, 0x55};
static char set_gamma_R_P_053[2] = {0xAB, 0x03};
static char set_gamma_R_P_054[2] = {0xAC, 0x6A};
static char set_gamma_R_P_055[2] = {0xAD, 0x03};
static char set_gamma_R_P_056[2] = {0xAE, 0x97};
static char set_gamma_R_P_057[2] = {0xAF, 0x03};
static char set_gamma_R_P_058[2] = {0xB0, 0xBB};
static char set_gamma_R_P_059[2] = {0xB1, 0x03};
static char set_gamma_R_P_060[2] = {0xB2, 0xBF};
/* R- */
static char set_gamma_R_M_001[2] = {0xB3, 0x00};
static char set_gamma_R_M_002[2] = {0xB4, 0x77};
static char set_gamma_R_M_003[2] = {0xB5, 0x00};
static char set_gamma_R_M_004[2] = {0xB6, 0x90};
static char set_gamma_R_M_005[2] = {0xB7, 0x00};
static char set_gamma_R_M_006[2] = {0xB8, 0xC2};
static char set_gamma_R_M_007[2] = {0xB9, 0x00};
static char set_gamma_R_M_008[2] = {0xBA, 0xE4};
static char set_gamma_R_M_009[2] = {0xBB, 0x00};
static char set_gamma_R_M_010[2] = {0xBC, 0xFC};
static char set_gamma_R_M_011[2] = {0xBD, 0x01};
static char set_gamma_R_M_012[2] = {0xBE, 0x0F};
static char set_gamma_R_M_013[2] = {0xBF, 0x01};
static char set_gamma_R_M_014[2] = {0xC0, 0x20};
static char set_gamma_R_M_015[2] = {0xC1, 0x01};
static char set_gamma_R_M_016[2] = {0xC2, 0x2E};
static char set_gamma_R_M_017[2] = {0xC3, 0x01};
static char set_gamma_R_M_018[2] = {0xC4, 0x3B};
static char set_gamma_R_M_019[2] = {0xC5, 0x01};
static char set_gamma_R_M_020[2] = {0xC6, 0x68};
static char set_gamma_R_M_021[2] = {0xC7, 0x01};
static char set_gamma_R_M_022[2] = {0xC8, 0x89};
static char set_gamma_R_M_023[2] = {0xC9, 0x01};
static char set_gamma_R_M_024[2] = {0xCA, 0xBE};
static char set_gamma_R_M_025[2] = {0xCB, 0x01};
static char set_gamma_R_M_026[2] = {0xCC, 0xE6};
static char set_gamma_R_M_027[2] = {0xCD, 0x02};
static char set_gamma_R_M_028[2] = {0xCE, 0x24};
static char set_gamma_R_M_029[2] = {0xCF, 0x02};
static char set_gamma_R_M_030[2] = {0xD0, 0x59};
static char set_gamma_R_M_031[2] = {0xD1, 0x02};
static char set_gamma_R_M_032[2] = {0xD2, 0x5B};
static char set_gamma_R_M_033[2] = {0xD3, 0x02};
static char set_gamma_R_M_034[2] = {0xD4, 0x8A};
static char set_gamma_R_M_035[2] = {0xD5, 0x02};
static char set_gamma_R_M_036[2] = {0xD6, 0xBC};
static char set_gamma_R_M_037[2] = {0xD7, 0x02};
static char set_gamma_R_M_038[2] = {0xD8, 0xDD};
static char set_gamma_R_M_039[2] = {0xD9, 0x03};
static char set_gamma_R_M_040[2] = {0xDA, 0x0A};
static char set_gamma_R_M_041[2] = {0xDB, 0x03};
static char set_gamma_R_M_042[2] = {0xDC, 0x2A};
static char set_gamma_R_M_043[2] = {0xDD, 0x03};
static char set_gamma_R_M_044[2] = {0xDE, 0x54};
static char set_gamma_R_M_045[2] = {0xDF, 0x03};
static char set_gamma_R_M_046[2] = {0xE0, 0x61};
static char set_gamma_R_M_047[2] = {0xE1, 0x03};
static char set_gamma_R_M_048[2] = {0xE2, 0x6F};
static char set_gamma_R_M_049[2] = {0xE3, 0x03};
static char set_gamma_R_M_050[2] = {0xE4, 0x7F};
static char set_gamma_R_M_051[2] = {0xE5, 0x03};
static char set_gamma_R_M_052[2] = {0xE6, 0x8F};
static char set_gamma_R_M_053[2] = {0xE7, 0x03};
static char set_gamma_R_M_054[2] = {0xE8, 0xA3};
static char set_gamma_R_M_055[2] = {0xE9, 0x03};
static char set_gamma_R_M_056[2] = {0xEA, 0xD1};
static char set_gamma_R_M_057[2] = {0xEB, 0x03};
static char set_gamma_R_M_058[2] = {0xEC, 0xF5};
static char set_gamma_R_M_059[2] = {0xED, 0x03};
static char set_gamma_R_M_060[2] = {0xEE, 0xF8};
/* G+ */
static char set_gamma_G_P_001[2] = {0xEF, 0x00};
static char set_gamma_G_P_002[2] = {0xF0, 0x81};
static char set_gamma_G_P_003[2] = {0xF1, 0x00};
static char set_gamma_G_P_004[2] = {0xF2, 0x8C};
static char set_gamma_G_P_005[2] = {0xF3, 0x00};
static char set_gamma_G_P_006[2] = {0xF4, 0xA1};
static char set_gamma_G_P_007[2] = {0xF5, 0x00};
static char set_gamma_G_P_008[2] = {0xF6, 0xB4};
static char set_gamma_G_P_009[2] = {0xF7, 0x00};
static char set_gamma_G_P_010[2] = {0xF8, 0xC4};
static char set_gamma_G_P_011[2] = {0xF9, 0x00};
static char set_gamma_G_P_012[2] = {0xFA, 0xD3};
static char set_gamma_G_P_013[2] = {0x00, 0x00};
static char set_gamma_G_P_014[2] = {0x01, 0xE0};
static char set_gamma_G_P_015[2] = {0x02, 0x00};
static char set_gamma_G_P_016[2] = {0x03, 0xED};
static char set_gamma_G_P_017[2] = {0x04, 0x00};
static char set_gamma_G_P_018[2] = {0x05, 0xF8};
static char set_gamma_G_P_019[2] = {0x06, 0x01};
static char set_gamma_G_P_020[2] = {0x07, 0x20};
static char set_gamma_G_P_021[2] = {0x08, 0x01};
static char set_gamma_G_P_022[2] = {0x09, 0x41};
static char set_gamma_G_P_023[2] = {0x0A, 0x01};
static char set_gamma_G_P_024[2] = {0x0B, 0x7A};
static char set_gamma_G_P_025[2] = {0x0C, 0x01};
static char set_gamma_G_P_026[2] = {0x0D, 0xA7};
static char set_gamma_G_P_027[2] = {0x0E, 0x01};
static char set_gamma_G_P_028[2] = {0x0F, 0xEE};
static char set_gamma_G_P_029[2] = {0x10, 0x02};
static char set_gamma_G_P_030[2] = {0x11, 0x20};
static char set_gamma_G_P_031[2] = {0x12, 0x02};
static char set_gamma_G_P_032[2] = {0x13, 0x21};
static char set_gamma_G_P_033[2] = {0x14, 0x02};
static char set_gamma_G_P_034[2] = {0x15, 0x50};
static char set_gamma_G_P_035[2] = {0x16, 0x02};
static char set_gamma_G_P_036[2] = {0x17, 0x83};
static char set_gamma_G_P_037[2] = {0x18, 0x02};
static char set_gamma_G_P_038[2] = {0x19, 0xA4};
static char set_gamma_G_P_039[2] = {0x1A, 0x02};
static char set_gamma_G_P_040[2] = {0x1B, 0xD1};
static char set_gamma_G_P_041[2] = {0x1C, 0x02};
static char set_gamma_G_P_042[2] = {0x1D, 0xF1};
static char set_gamma_G_P_043[2] = {0x1E, 0x03};
static char set_gamma_G_P_044[2] = {0x1F, 0x19};
static char set_gamma_G_P_045[2] = {0x20, 0x03};
static char set_gamma_G_P_046[2] = {0x21, 0x23};
static char set_gamma_G_P_047[2] = {0x22, 0x03};
static char set_gamma_G_P_048[2] = {0x23, 0x2A};
static char set_gamma_G_P_049[2] = {0x24, 0x03};
static char set_gamma_G_P_050[2] = {0x25, 0x3F};
static char set_gamma_G_P_051[2] = {0x26, 0x03};
static char set_gamma_G_P_052[2] = {0x27, 0x5E};
static char set_gamma_G_P_053[2] = {0x28, 0x03};
static char set_gamma_G_P_054[2] = {0x29, 0x79};
static char set_gamma_G_P_055[2] = {0x2A, 0x03};
static char set_gamma_G_P_056[2] = {0x2B, 0xB2};
static char set_gamma_G_P_057[2] = {0x2D, 0x03};
static char set_gamma_G_P_058[2] = {0x2F, 0xD2};
static char set_gamma_G_P_059[2] = {0x30, 0x03};
static char set_gamma_G_P_060[2] = {0x31, 0xD5};
/* G- */
static char set_gamma_G_M_001[2] = {0x32, 0x00};
static char set_gamma_G_M_002[2] = {0x33, 0xE8};
static char set_gamma_G_M_003[2] = {0x34, 0x00};
static char set_gamma_G_M_004[2] = {0x35, 0xF2};
static char set_gamma_G_M_005[2] = {0x36, 0x01};
static char set_gamma_G_M_006[2] = {0x37, 0x06};
static char set_gamma_G_M_007[2] = {0x38, 0x01};
static char set_gamma_G_M_008[2] = {0x39, 0x18};
static char set_gamma_G_M_009[2] = {0x3A, 0x01};
static char set_gamma_G_M_010[2] = {0x3B, 0x27};
static char set_gamma_G_M_011[2] = {0x3D, 0x01};
static char set_gamma_G_M_012[2] = {0x3F, 0x35};
static char set_gamma_G_M_013[2] = {0x40, 0x01};
static char set_gamma_G_M_014[2] = {0x41, 0x41};
static char set_gamma_G_M_015[2] = {0x42, 0x01};
static char set_gamma_G_M_016[2] = {0x43, 0x4C};
static char set_gamma_G_M_017[2] = {0x44, 0x01};
static char set_gamma_G_M_018[2] = {0x45, 0x56};
static char set_gamma_G_M_019[2] = {0x46, 0x01};
static char set_gamma_G_M_020[2] = {0x47, 0x7A};
static char set_gamma_G_M_021[2] = {0x48, 0x01};
static char set_gamma_G_M_022[2] = {0x49, 0x97};
static char set_gamma_G_M_023[2] = {0x4A, 0x01};
static char set_gamma_G_M_024[2] = {0x4B, 0xC7};
static char set_gamma_G_M_025[2] = {0x4C, 0x01};
static char set_gamma_G_M_026[2] = {0x4D, 0xEA};
static char set_gamma_G_M_027[2] = {0x4E, 0x02};
static char set_gamma_G_M_028[2] = {0x4F, 0x26};
static char set_gamma_G_M_029[2] = {0x50, 0x02};
static char set_gamma_G_M_030[2] = {0x51, 0x5A};
static char set_gamma_G_M_031[2] = {0x52, 0x02};
static char set_gamma_G_M_032[2] = {0x53, 0x5B};
static char set_gamma_G_M_033[2] = {0x54, 0x02};
static char set_gamma_G_M_034[2] = {0x55, 0x8A};
static char set_gamma_G_M_035[2] = {0x56, 0x02};
static char set_gamma_G_M_036[2] = {0x58, 0xBD};
static char set_gamma_G_M_037[2] = {0x59, 0x02};
static char set_gamma_G_M_038[2] = {0x5A, 0xDE};
static char set_gamma_G_M_039[2] = {0x5B, 0x03};
static char set_gamma_G_M_040[2] = {0x5C, 0x0B};
static char set_gamma_G_M_041[2] = {0x5D, 0x03};
static char set_gamma_G_M_042[2] = {0x5E, 0x2B};
static char set_gamma_G_M_043[2] = {0x5F, 0x03};
static char set_gamma_G_M_044[2] = {0x60, 0x53};
static char set_gamma_G_M_045[2] = {0x61, 0x03};
static char set_gamma_G_M_046[2] = {0x62, 0x5C};
static char set_gamma_G_M_047[2] = {0x63, 0x03};
static char set_gamma_G_M_048[2] = {0x64, 0x64};
static char set_gamma_G_M_049[2] = {0x65, 0x03};
static char set_gamma_G_M_050[2] = {0x66, 0x78};
static char set_gamma_G_M_051[2] = {0x67, 0x03};
static char set_gamma_G_M_052[2] = {0x68, 0x97};
static char set_gamma_G_M_053[2] = {0x69, 0x03};
static char set_gamma_G_M_054[2] = {0x6A, 0xB3};
static char set_gamma_G_M_055[2] = {0x6B, 0x03};
static char set_gamma_G_M_056[2] = {0x6C, 0xEC};
static char set_gamma_G_M_057[2] = {0x6D, 0x03};
static char set_gamma_G_M_058[2] = {0x6E, 0xFF};
static char set_gamma_G_M_059[2] = {0x6F, 0x03};
static char set_gamma_G_M_060[2] = {0x70, 0xFF};
/* B+ */
static char set_gamma_B_P_001[2] = {0x71, 0x01};
static char set_gamma_B_P_002[2] = {0x72, 0x03};
static char set_gamma_B_P_003[2] = {0x73, 0x01};
static char set_gamma_B_P_004[2] = {0x74, 0x06};
static char set_gamma_B_P_005[2] = {0x75, 0x01};
static char set_gamma_B_P_006[2] = {0x76, 0x0B};
static char set_gamma_B_P_007[2] = {0x77, 0x01};
static char set_gamma_B_P_008[2] = {0x78, 0x12};
static char set_gamma_B_P_009[2] = {0x79, 0x01};
static char set_gamma_B_P_010[2] = {0x7A, 0x1A};
static char set_gamma_B_P_011[2] = {0x7B, 0x01};
static char set_gamma_B_P_012[2] = {0x7C, 0x23};
static char set_gamma_B_P_013[2] = {0x7D, 0x01};
static char set_gamma_B_P_014[2] = {0x7E, 0x2B};
static char set_gamma_B_P_015[2] = {0x7F, 0x01};
static char set_gamma_B_P_016[2] = {0x80, 0x33};
static char set_gamma_B_P_017[2] = {0x81, 0x01};
static char set_gamma_B_P_018[2] = {0x82, 0x3A};
static char set_gamma_B_P_019[2] = {0x83, 0x01};
static char set_gamma_B_P_020[2] = {0x84, 0x56};
static char set_gamma_B_P_021[2] = {0x85, 0x01};
static char set_gamma_B_P_022[2] = {0x86, 0x70};
static char set_gamma_B_P_023[2] = {0x87, 0x01};
static char set_gamma_B_P_024[2] = {0x88, 0x9B};
static char set_gamma_B_P_025[2] = {0x89, 0x01};
static char set_gamma_B_P_026[2] = {0x8A, 0xBD};
static char set_gamma_B_P_027[2] = {0x8B, 0x01};
static char set_gamma_B_P_028[2] = {0x8C, 0xFA};
static char set_gamma_B_P_029[2] = {0x8D, 0x02};
static char set_gamma_B_P_030[2] = {0x8E, 0x2B};
static char set_gamma_B_P_031[2] = {0x8F, 0x02};
static char set_gamma_B_P_032[2] = {0x90, 0x2C};
static char set_gamma_B_P_033[2] = {0x91, 0x02};
static char set_gamma_B_P_034[2] = {0x92, 0x58};
static char set_gamma_B_P_035[2] = {0x93, 0x02};
static char set_gamma_B_P_036[2] = {0x94, 0x87};
static char set_gamma_B_P_037[2] = {0x95, 0x02};
static char set_gamma_B_P_038[2] = {0x96, 0xA8};
static char set_gamma_B_P_039[2] = {0x97, 0x02};
static char set_gamma_B_P_040[2] = {0x98, 0xD3};
static char set_gamma_B_P_041[2] = {0x99, 0x02};
static char set_gamma_B_P_042[2] = {0x9A, 0xEF};
static char set_gamma_B_P_043[2] = {0x9B, 0x03};
static char set_gamma_B_P_044[2] = {0x9C, 0x0E};
static char set_gamma_B_P_045[2] = {0x9D, 0x03};
static char set_gamma_B_P_046[2] = {0x9E, 0x16};
static char set_gamma_B_P_047[2] = {0x9F, 0x03};
static char set_gamma_B_P_048[2] = {0xA0, 0x1D};
static char set_gamma_B_P_049[2] = {0xA2, 0x03};
static char set_gamma_B_P_050[2] = {0xA3, 0x22};
static char set_gamma_B_P_051[2] = {0xA4, 0x03};
static char set_gamma_B_P_052[2] = {0xA5, 0x30};
static char set_gamma_B_P_053[2] = {0xA6, 0x03};
static char set_gamma_B_P_054[2] = {0xA7, 0x33};
static char set_gamma_B_P_055[2] = {0xA9, 0x03};
static char set_gamma_B_P_056[2] = {0xAA, 0x34};
static char set_gamma_B_P_057[2] = {0xAB, 0x03};
static char set_gamma_B_P_058[2] = {0xAC, 0x35};
static char set_gamma_B_P_059[2] = {0xAD, 0x03};
static char set_gamma_B_P_060[2] = {0xAE, 0x35};
/* B- */
static char set_gamma_B_M_001[2] = {0xAF, 0x01};
static char set_gamma_B_M_002[2] = {0xB0, 0x69};
static char set_gamma_B_M_003[2] = {0xB1, 0x01};
static char set_gamma_B_M_004[2] = {0xB2, 0x6C};
static char set_gamma_B_M_005[2] = {0xB3, 0x01};
static char set_gamma_B_M_006[2] = {0xB4, 0x70};
static char set_gamma_B_M_007[2] = {0xB5, 0x01};
static char set_gamma_B_M_008[2] = {0xB6, 0x75};
static char set_gamma_B_M_009[2] = {0xB7, 0x01};
static char set_gamma_B_M_010[2] = {0xB8, 0x7D};
static char set_gamma_B_M_011[2] = {0xB9, 0x01};
static char set_gamma_B_M_012[2] = {0xBA, 0x84};
static char set_gamma_B_M_013[2] = {0xBB, 0x01};
static char set_gamma_B_M_014[2] = {0xBC, 0x8B};
static char set_gamma_B_M_015[2] = {0xBD, 0x01};
static char set_gamma_B_M_016[2] = {0xBE, 0x92};
static char set_gamma_B_M_017[2] = {0xBF, 0x01};
static char set_gamma_B_M_018[2] = {0xC0, 0x99};
static char set_gamma_B_M_019[2] = {0xC1, 0x01};
static char set_gamma_B_M_020[2] = {0xC2, 0xB0};
static char set_gamma_B_M_021[2] = {0xC3, 0x01};
static char set_gamma_B_M_022[2] = {0xC4, 0xC6};
static char set_gamma_B_M_023[2] = {0xC5, 0x01};
static char set_gamma_B_M_024[2] = {0xC6, 0xE9};
static char set_gamma_B_M_025[2] = {0xC7, 0x02};
static char set_gamma_B_M_026[2] = {0xC8, 0x03};
static char set_gamma_B_M_027[2] = {0xC9, 0x02};
static char set_gamma_B_M_028[2] = {0xCA, 0x34};
static char set_gamma_B_M_029[2] = {0xCB, 0x02};
static char set_gamma_B_M_030[2] = {0xCC, 0x64};
static char set_gamma_B_M_031[2] = {0xCD, 0x02};
static char set_gamma_B_M_032[2] = {0xCE, 0x66};
static char set_gamma_B_M_033[2] = {0xCF, 0x02};
static char set_gamma_B_M_034[2] = {0xD0, 0x92};
static char set_gamma_B_M_035[2] = {0xD1, 0x02};
static char set_gamma_B_M_036[2] = {0xD2, 0xC1};
static char set_gamma_B_M_037[2] = {0xD3, 0x02};
static char set_gamma_B_M_038[2] = {0xD4, 0xE2};
static char set_gamma_B_M_039[2] = {0xD5, 0x03};
static char set_gamma_B_M_040[2] = {0xD6, 0x0D};
static char set_gamma_B_M_041[2] = {0xD7, 0x03};
static char set_gamma_B_M_042[2] = {0xD8, 0x29};
static char set_gamma_B_M_043[2] = {0xD9, 0x03};
static char set_gamma_B_M_044[2] = {0xDA, 0x48};
static char set_gamma_B_M_045[2] = {0xDB, 0x03};
static char set_gamma_B_M_046[2] = {0xDC, 0x50};
static char set_gamma_B_M_047[2] = {0xDD, 0x03};
static char set_gamma_B_M_048[2] = {0xDE, 0x56};
static char set_gamma_B_M_049[2] = {0xDF, 0x03};
static char set_gamma_B_M_050[2] = {0xE0, 0x5C};
static char set_gamma_B_M_051[2] = {0xE1, 0x03};
static char set_gamma_B_M_052[2] = {0xE2, 0x6A};
static char set_gamma_B_M_053[2] = {0xE3, 0x03};
static char set_gamma_B_M_054[2] = {0xE4, 0x6C};
static char set_gamma_B_M_055[2] = {0xE5, 0x03};
static char set_gamma_B_M_056[2] = {0xE6, 0x6E};
static char set_gamma_B_M_057[2] = {0xE7, 0x03};
static char set_gamma_B_M_058[2] = {0xE8, 0x6E};
static char set_gamma_B_M_059[2] = {0xE9, 0x03};
static char set_gamma_B_M_060[2] = {0xEA, 0x6E};

/* Calibration mode data *//* DTYPE_GEN_WRITE2 */
/* UI */
static char cabc_mode_UI_001[2] = {0x13, 0xFF};
static char cabc_mode_UI_002[2] = {0x14, 0xEC};
static char cabc_mode_UI_003[2] = {0x15, 0xE7};
static char cabc_mode_UI_004[2] = {0x16, 0xDF};
/* Still */
static char cabc_mode_STILL_001[2] = {0x17, 0xF3};
static char cabc_mode_STILL_002[2] = {0x18, 0xD9};
static char cabc_mode_STILL_003[2] = {0x19, 0xCC};
static char cabc_mode_STILL_004[2] = {0x1A, 0xC0};
static char cabc_mode_STILL_005[2] = {0x1B, 0xB3};
static char cabc_mode_STILL_006[2] = {0x1C, 0xA6};
static char cabc_mode_STILL_007[2] = {0x1D, 0x99};
static char cabc_mode_STILL_008[2] = {0x1E, 0x99};
static char cabc_mode_STILL_009[2] = {0x1F, 0x99};
static char cabc_mode_STILL_010[2] = {0x20, 0x95};
/* Moving */
static char cabc_mode_MOVING_001[2] = {0x21, 0xF3};
static char cabc_mode_MOVING_002[2] = {0x22, 0xD9};
static char cabc_mode_MOVING_003[2] = {0x23, 0xCC};
static char cabc_mode_MOVING_004[2] = {0x24, 0xC0};
static char cabc_mode_MOVING_005[2] = {0x25, 0xB3};
static char cabc_mode_MOVING_006[2] = {0x26, 0xA6};
static char cabc_mode_MOVING_007[2] = {0x27, 0x99};
static char cabc_mode_MOVING_008[2] = {0x28, 0x99};
static char cabc_mode_MOVING_009[2] = {0x29, 0x99};
static char cabc_mode_MOVING_010[2] = {0x2A, 0x95};

/* Panel timing setting data */
/* panel_timing_setting_001 = cmd2_select_05 */
static char panel_timing_setting_002[2] = {0xFB, 0x01};
static char panel_timing_setting_003[2] = {0x28, 0x01};
static char panel_timing_setting_004[2] = {0x2F, 0x02};

/* maker_setting data */
/* maker_set_step_001 = cmd2_select_EE */
static char maker_set_step_002[2] = {0x26, 0x08};
static char maker_set_step_003[2] = {0x26, 0x00};
/* maker_set_step_004 = cmd1_select */

/* end maker_setting data */
/* end_maker_set_step_001 = cmd2_select_EE */
static char end_maker_set_step_002[2] = {0x12, 0x50};
static char end_maker_set_step_003[2] = {0x13, 0x02};
static char end_maker_set_step_004[2] = {0x6A, 0x60};
/* end_maker_set_step_005 = cmd1_select */

/* display direction data */
/* static char display_direction_001[2] = {0x36, 0xC0};*/
static char display_direction_001[2] = {0x36, 0xD4};

/* Calibration setting data *//* DTYPE_GEN_WRITE2 */
static char cabc_set_001[2] = {0x51, 0xFF};
static char cabc_set_002[2] = {0x53, 0x2C};
static char cabc_set_003[2] = {0x5E, 0x06};

/* Tearing Effect data *//* DTYPE_GEN_WRITE2 */
static char te_effect_001[2] = {0x35, 0x00};

/* Tearing Effect data *//* DTYPE_GEN_WRITE2 */
static char select_cabc[2] = {0x55, 0x01};  /* 0x03 Moving Mode  */
                                            /* 0x02 Still Mode */
                                            /* 0x01 UI Mode */
                                            /* 0x00 CABC OFF */

/*
  ---------------------------------------------------------------------
*/

/* maker_setting */
static struct dsi_cmd_desc novatek_wxga_maker_setting_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd2_select_EE), cmd2_select_EE},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 2,  sizeof(maker_set_step_002), maker_set_step_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(maker_set_step_003), maker_set_step_003},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd1_select), cmd1_select}
};

/* initializeÅ` */
static struct dsi_cmd_desc novatek_wxga_initialize_cmds[] = {
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_mipi_lane), set_mipi_lane},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(mpi_mode), mpi_mode},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd2_select_05), cmd2_select_05},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_002), step4_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_003), step4_003},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_004), step4_004},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_005), step4_005},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_006), step4_006},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_007), step4_007},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_008), step4_008},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_009), step4_009},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_010), step4_010},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_011), step4_011},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_012), step4_012},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_013), step4_013},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_014), step4_014},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_015), step4_015},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_016), step4_016},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_017), step4_017},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_018), step4_018},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_019), step4_019},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_020), step4_020},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_021), step4_021},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_022), step4_022},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_023), step4_023},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_024), step4_024},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_025), step4_025},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_026), step4_026},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_027), step4_027},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_028), step4_028},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_029), step4_029},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_030), step4_030},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_031), step4_031},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_032), step4_032},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_033), step4_033},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_034), step4_034},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_035), step4_035},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_036), step4_036},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_037), step4_037},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_038), step4_038},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_039), step4_039},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_040), step4_040},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_041), step4_041},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_042), step4_042},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_043), step4_043},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_044), step4_044},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_045), step4_045},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_046), step4_046},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_047), step4_047},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_048), step4_048},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_049), step4_049},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_050), step4_050},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_051), step4_051},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_052), step4_052},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_053), step4_053},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_054), step4_054},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_055), step4_055},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_056), step4_056},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_057), step4_057},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_058), step4_058},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_059), step4_059},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_060), step4_060},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_061), step4_061},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd1_select), cmd1_select},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd2_select_01), cmd2_select_01},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_064), step4_064},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_065), step4_065},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_066), step4_066},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_067), step4_067},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_068), step4_068},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_069), step4_069},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_070), step4_070},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_071), step4_071},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_072), step4_072},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_073), step4_073},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_074), step4_074},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_075), step4_075},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_076), step4_076},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_079), step4_079},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_080), step4_080},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_081), step4_081},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_082), step4_082},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_001), set_gamma_R_P_001},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_002), set_gamma_R_P_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_003), set_gamma_R_P_003},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_004), set_gamma_R_P_004},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_005), set_gamma_R_P_005},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_006), set_gamma_R_P_006},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_007), set_gamma_R_P_007},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_008), set_gamma_R_P_008},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_009), set_gamma_R_P_009},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_010), set_gamma_R_P_010},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_011), set_gamma_R_P_011},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_012), set_gamma_R_P_012},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_013), set_gamma_R_P_013},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_014), set_gamma_R_P_014},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_015), set_gamma_R_P_015},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_016), set_gamma_R_P_016},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_017), set_gamma_R_P_017},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_018), set_gamma_R_P_018},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_019), set_gamma_R_P_019},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_020), set_gamma_R_P_020},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_021), set_gamma_R_P_021},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_022), set_gamma_R_P_022},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_023), set_gamma_R_P_023},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_024), set_gamma_R_P_024},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_025), set_gamma_R_P_025},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_026), set_gamma_R_P_026},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_027), set_gamma_R_P_027},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_028), set_gamma_R_P_028},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_029), set_gamma_R_P_029},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_030), set_gamma_R_P_030},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_031), set_gamma_R_P_031},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_032), set_gamma_R_P_032},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_033), set_gamma_R_P_033},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_034), set_gamma_R_P_034},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_035), set_gamma_R_P_035},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_036), set_gamma_R_P_036},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_037), set_gamma_R_P_037},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_038), set_gamma_R_P_038},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_039), set_gamma_R_P_039},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_040), set_gamma_R_P_040},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_041), set_gamma_R_P_041},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_042), set_gamma_R_P_042},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_043), set_gamma_R_P_043},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_044), set_gamma_R_P_044},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_045), set_gamma_R_P_045},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_046), set_gamma_R_P_046},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_047), set_gamma_R_P_047},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_048), set_gamma_R_P_048},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_049), set_gamma_R_P_049},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_050), set_gamma_R_P_050},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_051), set_gamma_R_P_051},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_052), set_gamma_R_P_052},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_053), set_gamma_R_P_053},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_054), set_gamma_R_P_054},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_055), set_gamma_R_P_055},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_056), set_gamma_R_P_056},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_057), set_gamma_R_P_057},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_058), set_gamma_R_P_058},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_059), set_gamma_R_P_059},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_P_060), set_gamma_R_P_060},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_001), set_gamma_R_M_001},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_002), set_gamma_R_M_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_003), set_gamma_R_M_003},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_004), set_gamma_R_M_004},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_005), set_gamma_R_M_005},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_006), set_gamma_R_M_006},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_007), set_gamma_R_M_007},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_008), set_gamma_R_M_008},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_009), set_gamma_R_M_009},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_010), set_gamma_R_M_010},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_011), set_gamma_R_M_011},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_012), set_gamma_R_M_012},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_013), set_gamma_R_M_013},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_014), set_gamma_R_M_014},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_015), set_gamma_R_M_015},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_016), set_gamma_R_M_016},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_017), set_gamma_R_M_017},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_018), set_gamma_R_M_018},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_019), set_gamma_R_M_019},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_020), set_gamma_R_M_020},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_021), set_gamma_R_M_021},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_022), set_gamma_R_M_022},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_023), set_gamma_R_M_023},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_024), set_gamma_R_M_024},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_025), set_gamma_R_M_025},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_026), set_gamma_R_M_026},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_027), set_gamma_R_M_027},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_028), set_gamma_R_M_028},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_029), set_gamma_R_M_029},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_030), set_gamma_R_M_030},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_031), set_gamma_R_M_031},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_032), set_gamma_R_M_032},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_033), set_gamma_R_M_033},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_034), set_gamma_R_M_034},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_035), set_gamma_R_M_035},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_036), set_gamma_R_M_036},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_037), set_gamma_R_M_037},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_038), set_gamma_R_M_038},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_039), set_gamma_R_M_039},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_040), set_gamma_R_M_040},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_041), set_gamma_R_M_041},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_042), set_gamma_R_M_042},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_043), set_gamma_R_M_043},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_044), set_gamma_R_M_044},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_045), set_gamma_R_M_045},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_046), set_gamma_R_M_046},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_047), set_gamma_R_M_047},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_048), set_gamma_R_M_048},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_049), set_gamma_R_M_049},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_050), set_gamma_R_M_050},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_051), set_gamma_R_M_051},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_052), set_gamma_R_M_052},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_053), set_gamma_R_M_053},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_054), set_gamma_R_M_054},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_055), set_gamma_R_M_055},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_056), set_gamma_R_M_056},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_057), set_gamma_R_M_057},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_058), set_gamma_R_M_058},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_059), set_gamma_R_M_059},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_R_M_060), set_gamma_R_M_060},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_001), set_gamma_G_P_001},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_002), set_gamma_G_P_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_003), set_gamma_G_P_003},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_004), set_gamma_G_P_004},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_005), set_gamma_G_P_005},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_006), set_gamma_G_P_006},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_007), set_gamma_G_P_007},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_008), set_gamma_G_P_008},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_009), set_gamma_G_P_009},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_010), set_gamma_G_P_010},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_011), set_gamma_G_P_011},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_012), set_gamma_G_P_012},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd1_select), cmd1_select},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd2_select_02), cmd2_select_02},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(step4_217), step4_217},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_013), set_gamma_G_P_013},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_014), set_gamma_G_P_014},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_015), set_gamma_G_P_015},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_016), set_gamma_G_P_016},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_017), set_gamma_G_P_017},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_018), set_gamma_G_P_018},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_019), set_gamma_G_P_019},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_020), set_gamma_G_P_020},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_021), set_gamma_G_P_021},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_022), set_gamma_G_P_022},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_023), set_gamma_G_P_023},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_024), set_gamma_G_P_024},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_025), set_gamma_G_P_025},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_026), set_gamma_G_P_026},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_027), set_gamma_G_P_027},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_028), set_gamma_G_P_028},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_029), set_gamma_G_P_029},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_030), set_gamma_G_P_030},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_031), set_gamma_G_P_031},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_032), set_gamma_G_P_032},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_033), set_gamma_G_P_033},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_034), set_gamma_G_P_034},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_035), set_gamma_G_P_035},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_036), set_gamma_G_P_036},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_037), set_gamma_G_P_037},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_038), set_gamma_G_P_038},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_039), set_gamma_G_P_039},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_040), set_gamma_G_P_040},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_041), set_gamma_G_P_041},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_042), set_gamma_G_P_042},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_043), set_gamma_G_P_043},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_044), set_gamma_G_P_044},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_045), set_gamma_G_P_045},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_046), set_gamma_G_P_046},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_047), set_gamma_G_P_047},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_048), set_gamma_G_P_048},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_049), set_gamma_G_P_049},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_050), set_gamma_G_P_050},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_051), set_gamma_G_P_051},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_052), set_gamma_G_P_052},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_053), set_gamma_G_P_053},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_054), set_gamma_G_P_054},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_055), set_gamma_G_P_055},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_056), set_gamma_G_P_056},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_057), set_gamma_G_P_057},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_058), set_gamma_G_P_058},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_059), set_gamma_G_P_059},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_P_060), set_gamma_G_P_060},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_001), set_gamma_G_M_001},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_002), set_gamma_G_M_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_003), set_gamma_G_M_003},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_004), set_gamma_G_M_004},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_005), set_gamma_G_M_005},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_006), set_gamma_G_M_006},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_007), set_gamma_G_M_007},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_008), set_gamma_G_M_008},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_009), set_gamma_G_M_009},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_010), set_gamma_G_M_010},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_011), set_gamma_G_M_011},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_012), set_gamma_G_M_012},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_013), set_gamma_G_M_013},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_014), set_gamma_G_M_014},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_015), set_gamma_G_M_015},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_016), set_gamma_G_M_016},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_017), set_gamma_G_M_017},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_018), set_gamma_G_M_018},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_019), set_gamma_G_M_019},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_020), set_gamma_G_M_020},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_021), set_gamma_G_M_021},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_022), set_gamma_G_M_022},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_023), set_gamma_G_M_023},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_024), set_gamma_G_M_024},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_025), set_gamma_G_M_025},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_026), set_gamma_G_M_026},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_027), set_gamma_G_M_027},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_028), set_gamma_G_M_028},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_029), set_gamma_G_M_029},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_030), set_gamma_G_M_030},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_031), set_gamma_G_M_031},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_032), set_gamma_G_M_032},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_033), set_gamma_G_M_033},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_034), set_gamma_G_M_034},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_035), set_gamma_G_M_035},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_036), set_gamma_G_M_036},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_037), set_gamma_G_M_037},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_038), set_gamma_G_M_038},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_039), set_gamma_G_M_039},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_040), set_gamma_G_M_040},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_041), set_gamma_G_M_041},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_042), set_gamma_G_M_042},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_043), set_gamma_G_M_043},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_044), set_gamma_G_M_044},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_045), set_gamma_G_M_045},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_046), set_gamma_G_M_046},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_047), set_gamma_G_M_047},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_048), set_gamma_G_M_048},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_049), set_gamma_G_M_049},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_050), set_gamma_G_M_050},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_051), set_gamma_G_M_051},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_052), set_gamma_G_M_052},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_053), set_gamma_G_M_053},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_054), set_gamma_G_M_054},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_055), set_gamma_G_M_055},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_056), set_gamma_G_M_056},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_057), set_gamma_G_M_057},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_058), set_gamma_G_M_058},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_059), set_gamma_G_M_059},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_G_M_060), set_gamma_G_M_060},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_001), set_gamma_B_P_001},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_002), set_gamma_B_P_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_003), set_gamma_B_P_003},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_004), set_gamma_B_P_004},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_005), set_gamma_B_P_005},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_006), set_gamma_B_P_006},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_007), set_gamma_B_P_007},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_008), set_gamma_B_P_008},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_009), set_gamma_B_P_009},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_010), set_gamma_B_P_010},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_011), set_gamma_B_P_011},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_012), set_gamma_B_P_012},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_013), set_gamma_B_P_013},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_014), set_gamma_B_P_014},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_015), set_gamma_B_P_015},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_016), set_gamma_B_P_016},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_017), set_gamma_B_P_017},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_018), set_gamma_B_P_018},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_019), set_gamma_B_P_019},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_020), set_gamma_B_P_020},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_021), set_gamma_B_P_021},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_022), set_gamma_B_P_022},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_023), set_gamma_B_P_023},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_024), set_gamma_B_P_024},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_025), set_gamma_B_P_025},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_026), set_gamma_B_P_026},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_027), set_gamma_B_P_027},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_028), set_gamma_B_P_028},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_029), set_gamma_B_P_029},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_030), set_gamma_B_P_030},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_031), set_gamma_B_P_031},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_032), set_gamma_B_P_032},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_033), set_gamma_B_P_033},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_034), set_gamma_B_P_034},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_035), set_gamma_B_P_035},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_036), set_gamma_B_P_036},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_037), set_gamma_B_P_037},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_038), set_gamma_B_P_038},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_039), set_gamma_B_P_039},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_040), set_gamma_B_P_040},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_041), set_gamma_B_P_041},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_042), set_gamma_B_P_042},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_043), set_gamma_B_P_043},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_044), set_gamma_B_P_044},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_045), set_gamma_B_P_045},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_046), set_gamma_B_P_046},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_047), set_gamma_B_P_047},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_048), set_gamma_B_P_048},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_049), set_gamma_B_P_049},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_050), set_gamma_B_P_050},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_051), set_gamma_B_P_051},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_052), set_gamma_B_P_052},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_053), set_gamma_B_P_053},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_054), set_gamma_B_P_054},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_055), set_gamma_B_P_055},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_056), set_gamma_B_P_056},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_057), set_gamma_B_P_057},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_058), set_gamma_B_P_058},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_059), set_gamma_B_P_059},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_P_060), set_gamma_B_P_060},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_001), set_gamma_B_M_001},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_002), set_gamma_B_M_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_003), set_gamma_B_M_003},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_004), set_gamma_B_M_004},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_005), set_gamma_B_M_005},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_006), set_gamma_B_M_006},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_007), set_gamma_B_M_007},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_008), set_gamma_B_M_008},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_009), set_gamma_B_M_009},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_010), set_gamma_B_M_010},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_011), set_gamma_B_M_011},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_012), set_gamma_B_M_012},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_013), set_gamma_B_M_013},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_014), set_gamma_B_M_014},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_015), set_gamma_B_M_015},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_016), set_gamma_B_M_016},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_017), set_gamma_B_M_017},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_018), set_gamma_B_M_018},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_019), set_gamma_B_M_019},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_020), set_gamma_B_M_020},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_021), set_gamma_B_M_021},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_022), set_gamma_B_M_022},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_023), set_gamma_B_M_023},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_024), set_gamma_B_M_024},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_025), set_gamma_B_M_025},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_026), set_gamma_B_M_026},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_027), set_gamma_B_M_027},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_028), set_gamma_B_M_028},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_029), set_gamma_B_M_029},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_030), set_gamma_B_M_030},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_031), set_gamma_B_M_031},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_032), set_gamma_B_M_032},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_033), set_gamma_B_M_033},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_034), set_gamma_B_M_034},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_035), set_gamma_B_M_035},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_036), set_gamma_B_M_036},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_037), set_gamma_B_M_037},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_038), set_gamma_B_M_038},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_039), set_gamma_B_M_039},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_040), set_gamma_B_M_040},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_041), set_gamma_B_M_041},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_042), set_gamma_B_M_042},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_043), set_gamma_B_M_043},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_044), set_gamma_B_M_044},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_045), set_gamma_B_M_045},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_046), set_gamma_B_M_046},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_047), set_gamma_B_M_047},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_048), set_gamma_B_M_048},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_049), set_gamma_B_M_049},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_050), set_gamma_B_M_050},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_051), set_gamma_B_M_051},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_052), set_gamma_B_M_052},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_053), set_gamma_B_M_053},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_054), set_gamma_B_M_054},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_055), set_gamma_B_M_055},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_056), set_gamma_B_M_056},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_057), set_gamma_B_M_057},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_058), set_gamma_B_M_058},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_059), set_gamma_B_M_059},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(set_gamma_B_M_060), set_gamma_B_M_060},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd1_select), cmd1_select},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd2_select_04), cmd2_select_04},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_448), step4_448},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_449), step4_449},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_450), step4_450},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(step4_451), step4_451},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_UI_001), cabc_mode_UI_001},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_UI_002), cabc_mode_UI_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_UI_003), cabc_mode_UI_003},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_UI_004), cabc_mode_UI_004},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_STILL_001), cabc_mode_STILL_001},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_STILL_002), cabc_mode_STILL_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_STILL_003), cabc_mode_STILL_003},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_STILL_004), cabc_mode_STILL_004},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_STILL_005), cabc_mode_STILL_005},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_STILL_006), cabc_mode_STILL_006},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_STILL_007), cabc_mode_STILL_007},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_STILL_008), cabc_mode_STILL_008},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_STILL_009), cabc_mode_STILL_009},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_STILL_010), cabc_mode_STILL_010},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_MOVING_001), cabc_mode_MOVING_001},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_MOVING_002), cabc_mode_MOVING_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_MOVING_003), cabc_mode_MOVING_003},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_MOVING_004), cabc_mode_MOVING_004},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_MOVING_005), cabc_mode_MOVING_005},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_MOVING_006), cabc_mode_MOVING_006},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_MOVING_007), cabc_mode_MOVING_007},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_MOVING_008), cabc_mode_MOVING_008},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_MOVING_009), cabc_mode_MOVING_009},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(cabc_mode_MOVING_010), cabc_mode_MOVING_010},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd2_select_05), cmd2_select_05},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(panel_timing_setting_002), panel_timing_setting_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(panel_timing_setting_003), panel_timing_setting_003},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(panel_timing_setting_004), panel_timing_setting_004},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd1_select), cmd1_select},
	{DTYPE_DCS_WRITE, 1, 0, 0, 0, sizeof(exit_sleep), exit_sleep},
};

/* end maker_setting */
static struct dsi_cmd_desc novatek_wxga_maker_setting_cmds2[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd2_select_EE), cmd2_select_EE},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(end_maker_set_step_002), end_maker_set_step_002},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(end_maker_set_step_003), end_maker_set_step_003},
	{DTYPE_GEN_WRITE2, 1, 0, 0, 0,  sizeof(end_maker_set_step_004), end_maker_set_step_004},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cmd1_select), cmd1_select},
};

/* CABC Setting */
static struct dsi_cmd_desc novatek_wxga_cabc_setting_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cabc_set_001), cabc_set_001},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cabc_set_002), cabc_set_002},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(cabc_set_003), cabc_set_003},
};

/* display direction */
static struct dsi_cmd_desc novatek_wxga_display_direction_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,  sizeof(display_direction_001), display_direction_001},
};

static struct dsi_cmd_desc novatek_wxga_display_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,   sizeof(te_effect_001), te_effect_001},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,   sizeof(select_cabc), select_cabc},
	{DTYPE_DCS_WRITE, 1, 0, 0, 0,   sizeof(display_on), display_on},
};

static struct dsi_cmd_desc novatek_wxga_display_off_cmds[] = {
	{DTYPE_DCS_WRITE, 1, 0, 0, 0,   sizeof(display_off), display_off},
};
static struct dsi_cmd_desc novatek_wxga_display_off_cmds2[] = {
	{DTYPE_DCS_WRITE, 1, 0, 0, 0, sizeof(enter_sleep), enter_sleep},
};
static struct dsi_cmd_desc novatek_wxga_display_off_cmds3[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(enter_deep_standby), enter_deep_standby},
};
#endif  /* MIPI_NOVATEK_WXGA_TBL_H */
