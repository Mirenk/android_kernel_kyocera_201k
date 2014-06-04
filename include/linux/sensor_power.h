/*
 * This software is contributed or developed by KYOCERA Corporation.
 * (C) 2012 KYOCERA Corporation
 */
#ifndef SENSOR_POWER_H
#define SENSOR_POWER_H

enum sensor_index{
	SENSOR_INDEX_ACC,
	SENSOR_INDEX_MAG,
	SENSOR_INDEX_GYRO,
	SENSOR_INDEX_ORI,
	SENSOR_INDEX_APDS,
	SENSOR_INDEX_DEVICE_MAX,
};

typedef void (*kc_sensor_power_func)(void);

struct sensor_power_callback {
    kc_sensor_power_func power_on;
    kc_sensor_power_func power_off;
};

extern void sensor_power_on(enum sensor_index id);
extern void sensor_power_off(enum sensor_index id);
extern void sensor_power_reset(enum sensor_index id);
extern int32_t sensor_power_reg_cbfunc(struct sensor_power_callback* cb);
extern int32_t sensor_power_unreg_cbfunc(struct sensor_power_callback* cb);

#endif