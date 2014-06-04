/*
 * This software is contributed or developed by KYOCERA Corporation.
 * (C) 2012 KYOCERA Corporation
 */
/*
 * Copyright (c) 2011 Yamaha Corporation
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <linux/yas.h>

static int
yas_init(void)
{
	return YAS_ERROR_ERROR;
}

static int
yas_term(void)
{
	return YAS_ERROR_ERROR;
}

static int
yas_get_delay(void)
{
	return YAS_ERROR_ERROR;
}

static int
yas_set_delay(int delay)
{
	(void) delay;
	return YAS_ERROR_ERROR;
}

static int
yas_get_enable(void)
{
	return YAS_ERROR_ERROR;
}

static int
yas_set_enable(int enable)
{
	(void) enable;
	return YAS_ERROR_ERROR;
}

static int
yas_get_position(void)
{
	return YAS_ERROR_ERROR;
}

static int
yas_set_position(int position)
{
	(void) position;
	return YAS_ERROR_ERROR;
}

static int
yas_measure(struct yas_gyro_data *data, int num)
{
	(void) data;
	(void) num;
	return YAS_ERROR_ERROR;
}

static void
yas_interrupt_handler(void)
{
}

int yas_gyro_driver_init(struct yas_gyro_driver *f, int interrupt)
{
	struct yas_gyro_driver_callback *cbk;

	/* Check parameter */
	if (f == NULL)
		return YAS_ERROR_ARG;

	cbk = &f->callback;
	if (cbk->device_open == NULL ||
	    cbk->device_close == NULL ||
	    cbk->device_write == NULL ||
	    cbk->device_read == NULL ||
	    cbk->msleep == NULL) {
		return YAS_ERROR_ARG;
	}
	if (interrupt) {
		interrupt = 1;
		if (cbk->interrupt_enable == NULL ||
		    cbk->interrupt_disable == NULL ||
		    cbk->interrupt_notify == NULL) {
			return YAS_ERROR_ARG;
		}
	}

	/* Set driver interface */
	f->init = yas_init;
	f->term = yas_term;
	f->get_delay = yas_get_delay;
	f->set_delay = yas_set_delay;
	f->get_enable = yas_get_enable;
	f->set_enable = yas_set_enable;
	f->get_position = yas_get_position;
	f->set_position = yas_set_position;
	f->measure = yas_measure;
	if (interrupt)
		f->interrupt_handler = yas_interrupt_handler;
	else
		f->interrupt_handler = NULL;

	return YAS_NO_ERROR;
}
