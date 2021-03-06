/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
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
 */
/*
 * This software is contributed or developed by KYOCERA Corporation.
 * (C) 2012 KYOCERA Corporation
 */

#include "msm_sensor.h"
#include "msm.h"
#include "msm_ispif.h"
#define SENSOR_NAME "imx111"
#define PLATFORM_DRIVER_NAME "msm_camera_imx111"
#define imx111_obj imx111_##obj
#define D_CIT_THRESHOLD 0x1072
#define D_AGCG_THRESHOLD 0x00DF

DEFINE_MUTEX(imx111_mut);
static struct msm_sensor_ctrl_t imx111_s_ctrl;

extern int32_t msm_sensor_enable_i2c_mux(struct msm_camera_i2c_conf *i2c_conf);
extern int32_t msm_sensor_disable_i2c_mux(struct msm_camera_i2c_conf *i2c_conf);

static struct msm_camera_i2c_reg_conf imx111_start_settings[] = {
	{0x0100, 0x01},
};

static struct msm_camera_i2c_reg_conf imx111_stop_settings[] = {
	{0x0100, 0x00},
};

static struct msm_camera_i2c_reg_conf imx111_groupon_settings[] = {
	{0x104, 0x01},
};

static struct msm_camera_i2c_reg_conf imx111_groupoff_settings[] = {
	{0x104, 0x00},
};

//regular prev settings
static struct msm_camera_i2c_reg_conf imx111_prev_settings[] = {
	{0x0305, 0x04},
	{0x0307, 0x79},
	{0x30A4, 0x02},
	{0x303C, 0x4B},
	{0x0340, 0x05},
	{0x0341, 0x48},
	{0x0342, 0x06},
	{0x0343, 0xE0},
	{0x0346, 0x00},
	{0x0347, 0x30},
	{0x034A, 0x09},
	{0x034B, 0xCF},
	{0x034C, 0x06},
	{0x034D, 0x68},
	{0x034E, 0x04},
	{0x034F, 0xD0},
	{0x0381, 0x01},
	{0x0383, 0x01},
	{0x0385, 0x01},
	{0x0387, 0x03},
	{0x3033, 0x87},
	{0x303D, 0x10},
	{0x303E, 0x51},
	{0x3040, 0x08},
	{0x3041, 0x97},
	{0x3048, 0x01},
	{0x304C, 0xB7},
	{0x304D, 0x01},
	{0x3064, 0x10},
	{0x3073, 0x00},
	{0x3074, 0x11},
	{0x3075, 0x11},
	{0x3076, 0x11},
	{0x3077, 0x11},
	{0x3079, 0x00},
	{0x307A, 0x00},
	{0x309B, 0x28},
	{0x309C, 0x13},
	{0x309E, 0x00},
	{0x30A0, 0x14},
	{0x30A1, 0x09},
	{0x30AA, 0x01},
	{0x30B2, 0x05},
	{0x30D5, 0x04},
	{0x3102, 0x08},
	{0x3103, 0x22},
	{0x3104, 0x20},
	{0x3105, 0x00},
	{0x3106, 0x87},
	{0x3107, 0x00},
	{0x3108, 0x03},
	{0x3109, 0x02},
	{0x310A, 0x03},
	{0x315C, 0x3A},
	{0x315D, 0x39},
	{0x316E, 0x3B},
	{0x316F, 0x3A},
	{0x3318, 0x67},
	{0x3348, 0xF1},
};

static struct msm_camera_i2c_reg_conf imx111_snap_settings[] = {
	{0x0305, 0x04},
	{0x0307, 0x79},
	{0x30A4, 0x02},
	{0x303C, 0x4B},
	{0x0340, 0x0A},
	{0x0341, 0xFE},
	{0x0342, 0x0D},
	{0x0343, 0x70},
	{0x0346, 0x00},
	{0x0347, 0x30},
	{0x034A, 0x09},
	{0x034B, 0xCF},
	{0x034C, 0x0C},
	{0x034D, 0xD0},
	{0x034E, 0x09},
	{0x034F, 0xA0},
	{0x0381, 0x01},
	{0x0383, 0x01},
	{0x0385, 0x01},
	{0x0387, 0x01},
	{0x3033, 0x00},
	{0x303D, 0x00},
	{0x303E, 0x41},
	{0x3040, 0x08},
	{0x3041, 0x97},
	{0x3048, 0x00},
	{0x304C, 0x57},
	{0x304D, 0x03},
	{0x3064, 0x12},
	{0x3073, 0x00},
	{0x3074, 0x11},
	{0x3075, 0x11},
	{0x3076, 0x11},
	{0x3077, 0x11},
	{0x3079, 0x00},
	{0x307A, 0x00},
	{0x309B, 0x20},
	{0x309C, 0x13},
	{0x309E, 0x00},
	{0x30A0, 0x14},
	{0x30A1, 0x08},
	{0x30AA, 0x03},
	{0x30B2, 0x07},
	{0x30D5, 0x00},
	{0x3102, 0x10},
	{0x3103, 0x44},
	{0x3104, 0x40},
	{0x3105, 0x00},
	{0x3106, 0x0D},
	{0x3107, 0x01},
	{0x3108, 0x09},
	{0x3109, 0x08},
	{0x310A, 0x0F},
	{0x315C, 0x5D},
	{0x315D, 0x5C},
	{0x316E, 0x5E},
	{0x316F, 0x5D},
	{0x3318, 0x62},
	{0x3348, 0xE0},
};
static struct msm_camera_i2c_reg_conf imx111_fullhd_settings[] = {
	{0x0305, 0x04},
	{0x0307, 0x79},
	{0x30A4, 0x02},
	{0x303C, 0x4B},
	{0x0340, 0x05},
	{0x0341, 0x50},
	{0x0342, 0x0D},
	{0x0343, 0xAC},
	{0x0346, 0x00},
	{0x0347, 0x30},
	{0x034A, 0x09},
	{0x034B, 0xCF},
	{0x034C, 0x0C},
	{0x034D, 0xD0},
	{0x034E, 0x05},
	{0x034F, 0x1E},
	{0x0381, 0x01},
	{0x0383, 0x01},
	{0x0385, 0x01},
	{0x0387, 0x01},
	{0x3033, 0x00},
	{0x303D, 0x10},
	{0x303E, 0x41},
	{0x3040, 0x08},
	{0x3041, 0x93},
	{0x3048, 0x00},
	{0x304C, 0x67},
	{0x304D, 0x03},
	{0x3064, 0x12},
	{0x3073, 0xE0},
	{0x3074, 0x12},
	{0x3075, 0x12},
	{0x3076, 0x12},
	{0x3077, 0x12},
	{0x3079, 0x2A},
	{0x307A, 0x0A},
	{0x309B, 0x60},
	{0x309C, 0x13},
	{0x309E, 0x04},
	{0x30A0, 0x15},
	{0x30A1, 0x08},
	{0x30AA, 0x03},
	{0x30B2, 0x03},
	{0x30D5, 0x00},
	{0x3102, 0x08},
	{0x3103, 0x1D},
	{0x3104, 0x1E},
	{0x3105, 0x00},
	{0x3106, 0x74},
	{0x3107, 0x00},
	{0x3108, 0x03},
	{0x3109, 0x02},
	{0x310A, 0x03},
	{0x315C, 0x37},
	{0x315D, 0x36},
	{0x316E, 0x38},
	{0x316F, 0x37},
	{0x3318, 0x62},
	{0x3348, 0xE0},
};

static struct msm_camera_i2c_reg_conf imx111_recommend_settings[] = {
	{0x0101, 0x03},
	{0x3080, 0x50},
	{0x3087, 0x53},
	{0x309D, 0x94},
	{0x30B1, 0x03},
	{0x30C6, 0x00},
	{0x30C7, 0x00},
	{0x3115, 0x0B},
	{0x3118, 0x30},
	{0x311D, 0x25},
	{0x3121, 0x0A},
	{0x3212, 0xF2},
	{0x3213, 0x0F},
	{0x3215, 0x0F},
	{0x3217, 0x0B},
	{0x3219, 0x0B},
	{0x321B, 0x0D},
	{0x321D, 0x0D},
	{0x32AA, 0x11},
	{0x3032, 0x40},
};

static struct v4l2_subdev_info imx111_subdev_info[] = {
	{
	.code   = V4L2_MBUS_FMT_SBGGR10_1X10,
	.colorspace = V4L2_COLORSPACE_JPEG,
	.fmt    = 1,
	.order    = 0,
	},
	/* more can be supported, to be added later */
};

static struct msm_camera_i2c_conf_array imx111_init_conf[] = {
	{&imx111_recommend_settings[0],
	ARRAY_SIZE(imx111_recommend_settings), 0, MSM_CAMERA_I2C_BYTE_DATA}
};

static struct msm_camera_i2c_conf_array imx111_confs[] = {
	{&imx111_snap_settings[0],
	ARRAY_SIZE(imx111_snap_settings), 0, MSM_CAMERA_I2C_BYTE_DATA},
	{&imx111_prev_settings[0],
	ARRAY_SIZE(imx111_prev_settings), 0, MSM_CAMERA_I2C_BYTE_DATA},
	{&imx111_fullhd_settings[0],
	ARRAY_SIZE(imx111_fullhd_settings), 0, MSM_CAMERA_I2C_BYTE_DATA},
};

static struct msm_sensor_output_info_t imx111_dimensions[] = {
	{
		/* 15 fps */
		.x_output = 0x0CD0, /* 3280 */
		.y_output = 0x9A0, /* 2464 */
		.line_length_pclk = 0xD70,
		.frame_length_lines = 0xAFE,
		.vt_pixel_clk = 145202400,
		.op_pixel_clk = 363000000,
		.binning_factor = 1,
	},
	{
		/* 30 fps preview */
		.x_output = 0x668, /* 1640 */
		.y_output = 0x4D0, /* 1232 */
		.line_length_pclk = 0x6E0, /* 1760 */
		.frame_length_lines = 0x548, /* 1352 */
		.vt_pixel_clk = 72575360,
		.op_pixel_clk = 181500000,
		.binning_factor = 1,
	},
	{
		/* 30 fps FullHD preview */
		.x_output = 0xCD0, /* 3280 */
		.y_output = 0x51E, /* 1310 */
		.line_length_pclk = 0xDAC, /*3500 */
		.frame_length_lines = 0x550, /* 1360 */
		.vt_pixel_clk = 145180000,
		.op_pixel_clk = 181500000,
		.binning_factor = 1,
	},
};

static struct msm_camera_csid_vc_cfg imx111_cid_cfg[] = {
	{0, CSI_RAW10, CSI_DECODE_10BIT},
	{1, CSI_EMBED_DATA, CSI_DECODE_8BIT},
	{2, CSI_RESERVED_DATA_0, CSI_DECODE_8BIT},
};

static struct msm_camera_csi2_params imx111_csi_params = {
	.csid_params = {
		.lane_cnt = 2,
		.lut_params = {
			.num_cid = ARRAY_SIZE(imx111_cid_cfg),
			.vc_cfg = imx111_cid_cfg,
		},
	},
	.csiphy_params = {
		.lane_cnt = 2,
		.settle_cnt = 0x18,
	},
};

static struct msm_camera_csi2_params *imx111_csi_params_array[] = {
	&imx111_csi_params,
	&imx111_csi_params,
	&imx111_csi_params,
};

static struct msm_sensor_output_reg_addr_t imx111_reg_addr = {
	.x_output = 0x34C,
	.y_output = 0x34E,
	.line_length_pclk = 0x342,
	.frame_length_lines = 0x340,
};

static struct msm_sensor_id_info_t imx111_id_info = {
	.sensor_id_reg_addr = 0x0,
	.sensor_id = 0x0111,
};

static struct msm_sensor_exp_gain_info_t imx111_exp_gain_info = {
	.coarse_int_time_addr = 0x202,
	.global_gain_addr = 0x204,
	.vert_offset = 5,
};

static struct msm_cam_clk_info cam_clk_info[] = {
	{"cam_clk", MSM_SENSOR_MCLK_24HZ},
};

static uint32_t imx111_g_coase_integration_time = 0;
static uint32_t imx111_g_coase_integration_time_store = 0;
static uint16_t imx111_g_analogue_gain_code_global = 0;

int32_t msm_sensor_imx111_power_up(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;
	struct msm_camera_sensor_info *data = s_ctrl->sensordata;
	CDBG("%s: %d\n", __func__, __LINE__);
	s_ctrl->reg_ptr = kzalloc(sizeof(struct regulator *)
			* data->sensor_platform_info->num_vreg, GFP_KERNEL);
	if (!s_ctrl->reg_ptr) {
		pr_err("%s: could not allocate mem for regulators\n",
			__func__);
		return -ENOMEM;
	}

	rc = msm_camera_request_gpio_table(data, 1);
	if (rc < 0) {
		pr_err("%s: request gpio failed\n", __func__);
		goto request_gpio_failed;
	}

	rc = msm_camera_config_vreg(&s_ctrl->sensor_i2c_client->client->dev,
			s_ctrl->sensordata->sensor_platform_info->cam_vreg,
			s_ctrl->sensordata->sensor_platform_info->num_vreg,
			s_ctrl->reg_ptr, 1);
	if (rc < 0) {
		pr_err("%s: regulator on failed\n", __func__);
		goto config_vreg_failed;
	}

	rc = msm_camera_enable_vreg(&s_ctrl->sensor_i2c_client->client->dev,
			s_ctrl->sensordata->sensor_platform_info->cam_vreg,
			s_ctrl->sensordata->sensor_platform_info->num_vreg,
			s_ctrl->reg_ptr, 1);
	if (rc < 0) {
		pr_err("%s: enable regulator failed\n", __func__);
		goto enable_vreg_failed;
	}

	/* wait 10ms */
	usleep_range(10000,10000);

	rc = msm_camera_config_gpio_table(data, 1);
	if (rc < 0) {
		pr_err("%s: config gpio failed\n", __func__);
		goto config_gpio_failed;
	}

	if (s_ctrl->clk_rate != 0)
		cam_clk_info->clk_rate = s_ctrl->clk_rate;

	rc = msm_cam_clk_enable(&s_ctrl->sensor_i2c_client->client->dev,
		cam_clk_info, &s_ctrl->cam_clk, ARRAY_SIZE(cam_clk_info), 1);
	if (rc < 0) {
		pr_err("%s: clk enable failed\n", __func__);
		goto enable_clk_failed;
	}

	/* 20ms wait */
	usleep_range(20000, 20000);

	if (data->sensor_platform_info->ext_power_ctrl != NULL)
		data->sensor_platform_info->ext_power_ctrl(1);

	if (data->sensor_platform_info->i2c_conf &&
		data->sensor_platform_info->i2c_conf->use_i2c_mux)
		msm_sensor_enable_i2c_mux(data->sensor_platform_info->i2c_conf);

	return rc;
enable_clk_failed:
		msm_camera_config_gpio_table(data, 0);
config_gpio_failed:
	msm_camera_enable_vreg(&s_ctrl->sensor_i2c_client->client->dev,
			s_ctrl->sensordata->sensor_platform_info->cam_vreg,
			s_ctrl->sensordata->sensor_platform_info->num_vreg,
			s_ctrl->reg_ptr, 0);

enable_vreg_failed:
	msm_camera_config_vreg(&s_ctrl->sensor_i2c_client->client->dev,
		s_ctrl->sensordata->sensor_platform_info->cam_vreg,
		s_ctrl->sensordata->sensor_platform_info->num_vreg,
		s_ctrl->reg_ptr, 0);
config_vreg_failed:
	msm_camera_request_gpio_table(data, 0);
request_gpio_failed:
	kfree(s_ctrl->reg_ptr);
	return rc;
}

int32_t msm_sensor_imx111_power_down(struct msm_sensor_ctrl_t *s_ctrl)
{
	struct msm_camera_sensor_info *data = s_ctrl->sensordata;
	CDBG("%s\n", __func__);
	if (data->sensor_platform_info->i2c_conf &&
		data->sensor_platform_info->i2c_conf->use_i2c_mux)
		msm_sensor_disable_i2c_mux(
			data->sensor_platform_info->i2c_conf);

	if (data->sensor_platform_info->ext_power_ctrl != NULL)
		data->sensor_platform_info->ext_power_ctrl(0);
	msm_cam_clk_enable(&s_ctrl->sensor_i2c_client->client->dev,
		cam_clk_info, &s_ctrl->cam_clk, ARRAY_SIZE(cam_clk_info), 0);
	msm_camera_config_gpio_table(data, 0);
	/* 1ms wait */
	usleep_range(1000, 1000);
	msm_camera_enable_vreg(&s_ctrl->sensor_i2c_client->client->dev,
		s_ctrl->sensordata->sensor_platform_info->cam_vreg,
		s_ctrl->sensordata->sensor_platform_info->num_vreg,
		s_ctrl->reg_ptr, 0);
	msm_camera_config_vreg(&s_ctrl->sensor_i2c_client->client->dev,
		s_ctrl->sensordata->sensor_platform_info->cam_vreg,
		s_ctrl->sensordata->sensor_platform_info->num_vreg,
		s_ctrl->reg_ptr, 0);
	gpio_set_value_cansleep(55, 0);
	msm_camera_request_gpio_table(data, 0);
	kfree(s_ctrl->reg_ptr);
	return 0;
}

void imx111_sensor_stop_stream(struct msm_sensor_ctrl_t *s_ctrl)
{
	CDBG("%s E\n", __func__);
	msm_sensor_stop_stream(s_ctrl);
    msleep(70);
	CDBG("%s X\n", __func__);
}

int32_t imx111_sensor_write_exp_gain1(struct msm_sensor_ctrl_t *s_ctrl,
		uint16_t gain, uint32_t line)
{

	CDBG("%s: E gain %d line %d \n", __func__,gain ,line);

/* update value */
imx111_g_coase_integration_time = line;
imx111_g_analogue_gain_code_global = gain;

    msm_sensor_write_exp_gain1(s_ctrl, gain, line);

	CDBG("%s: X \n", __func__);

	return 0;
}

static int32_t msm_sensor_imx111_set_note_takepic(struct msm_sensor_ctrl_t *s_ctrl)
{

	CDBG("%s: E\n", __func__);

    imx111_g_coase_integration_time_store = imx111_g_coase_integration_time;

	CDBG("%s: X \n", __func__);

	return 0;
}

static int32_t msm_sensor_imx111_get_exp_time(struct msm_sensor_ctrl_t *s_ctrl, uint32_t *exposure_time)
{
	CDBG("%s: E\n", __func__);

    *exposure_time = (2471 * imx111_g_coase_integration_time_store) / 100000;

	CDBG("%s: X \n", __func__);
	return 0;
}

static int32_t msm_sensor_imx111_get_is_flash(struct msm_sensor_ctrl_t *s_ctrl, uint8_t *is_flash)
{
	CDBG("%s: E\n", __func__);
  if(imx111_g_coase_integration_time_store >= D_CIT_THRESHOLD && imx111_g_analogue_gain_code_global>=D_AGCG_THRESHOLD)
  {
    *is_flash = 1;
  }
  else
  {
    *is_flash = 0;
  }

	CDBG("%s: X flash %d \n", __func__, *is_flash);
	return 0;
}


static const struct i2c_device_id imx111_i2c_id[] = {
	{SENSOR_NAME, (kernel_ulong_t)&imx111_s_ctrl},
	{ }
};

static struct i2c_driver imx111_i2c_driver = {
	.id_table = imx111_i2c_id,
	.probe  = msm_sensor_i2c_probe,
	.driver = {
		.name = SENSOR_NAME,
	},
};

static struct msm_camera_i2c_client imx111_sensor_i2c_client = {
	.addr_type = MSM_CAMERA_I2C_WORD_ADDR,
};

static int __init msm_sensor_init_module(void)
{
	return i2c_add_driver(&imx111_i2c_driver);
}

static struct v4l2_subdev_core_ops imx111_subdev_core_ops = {
	.ioctl = msm_sensor_subdev_ioctl,
	.s_power = msm_sensor_power,
};
static struct v4l2_subdev_video_ops imx111_subdev_video_ops = {
	.enum_mbus_fmt = msm_sensor_v4l2_enum_fmt,
};

static struct v4l2_subdev_ops imx111_subdev_ops = {
	.core = &imx111_subdev_core_ops,
	.video  = &imx111_subdev_video_ops,
};

static struct msm_sensor_fn_t imx111_func_tbl = {
	.sensor_start_stream = msm_sensor_start_stream,
	.sensor_stop_stream = imx111_sensor_stop_stream,
	.sensor_group_hold_on = msm_sensor_group_hold_on,
	.sensor_group_hold_off = msm_sensor_group_hold_off,
	.sensor_set_fps = msm_sensor_set_fps,
	.sensor_write_exp_gain = imx111_sensor_write_exp_gain1,
	.sensor_write_snapshot_exp_gain = imx111_sensor_write_exp_gain1,
	.sensor_setting = msm_sensor_setting,
	.sensor_set_sensor_mode = msm_sensor_set_sensor_mode,
	.sensor_mode_init = msm_sensor_mode_init,
	.sensor_get_output_info = msm_sensor_get_output_info,
	.sensor_config = msm_sensor_config,
	.sensor_power_up = msm_sensor_imx111_power_up,
	.sensor_power_down = msm_sensor_imx111_power_down,
	.sensor_adjust_frame_lines = msm_sensor_adjust_frame_lines,
	.sensor_set_note_takepic = msm_sensor_imx111_set_note_takepic,
	.sensor_get_exposure_time  = msm_sensor_imx111_get_exp_time,
	.sensor_get_is_flash = msm_sensor_imx111_get_is_flash,
	.sensor_get_csi_params = msm_sensor_get_csi_params,
};

static struct msm_sensor_reg_t imx111_regs = {
	.default_data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.start_stream_conf = imx111_start_settings,
	.start_stream_conf_size = ARRAY_SIZE(imx111_start_settings),
	.stop_stream_conf = imx111_stop_settings,
	.stop_stream_conf_size = ARRAY_SIZE(imx111_stop_settings),
	.group_hold_on_conf = imx111_groupon_settings,
	.group_hold_on_conf_size = ARRAY_SIZE(imx111_groupon_settings),
	.group_hold_off_conf = imx111_groupoff_settings,
	.group_hold_off_conf_size =
		ARRAY_SIZE(imx111_groupoff_settings),
	.init_settings = &imx111_init_conf[0],
	.init_size = ARRAY_SIZE(imx111_init_conf),
	.mode_settings = &imx111_confs[0],
	.output_settings = &imx111_dimensions[0],
	.num_conf = ARRAY_SIZE(imx111_confs),
};

static struct msm_sensor_ctrl_t imx111_s_ctrl = {
	.msm_sensor_reg = &imx111_regs,
	.sensor_i2c_client = &imx111_sensor_i2c_client,
	.sensor_i2c_addr = 0x34,
	.sensor_output_reg_addr = &imx111_reg_addr,
	.sensor_id_info = &imx111_id_info,
	.sensor_exp_gain_info = &imx111_exp_gain_info,
	.cam_mode = MSM_SENSOR_MODE_INVALID,
	.csi_params = &imx111_csi_params_array[0],
	.msm_sensor_mutex = &imx111_mut,
	.sensor_i2c_driver = &imx111_i2c_driver,
	.sensor_v4l2_subdev_info = imx111_subdev_info,
	.sensor_v4l2_subdev_info_size = ARRAY_SIZE(imx111_subdev_info),
	.sensor_v4l2_subdev_ops = &imx111_subdev_ops,
	.func_tbl = &imx111_func_tbl,
};

module_init(msm_sensor_init_module);
MODULE_DESCRIPTION("Sony 8MP Bayer sensor driver");
MODULE_LICENSE("GPL v2");
