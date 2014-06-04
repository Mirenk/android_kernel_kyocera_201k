/*********************************************************************
 * 
 * This software is contributed or developed by KYOCERA Corporation.
 * (C) 2012 KYOCERA Corporation
 * 
 *********************************************************************/
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/* define SD Host Interface LSI Index enumerate */
/* include/linux/mmc/sdhub.h */

#ifndef _SDHUB_H_
#define _SDHUB_H_

struct mmc_host *mmc_get_host(void);
void sdhub_poweron(struct mmc_host *host);
void sdhub_poweroff(struct mmc_host *host);
int init_sdhub(struct mmc_host *host, unsigned int width);

#endif /* _SDHUB_H */


