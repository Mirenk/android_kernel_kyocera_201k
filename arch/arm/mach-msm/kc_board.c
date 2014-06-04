/*
 * This software is contributed or developed by KYOCERA Corporation.
 * (C) 2012 KYOCERA Corporation
 */
/*
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

/*==========================================================================

                     INCLUDE FILES FOR MODULE

==========================================================================*/

#include <linux/gpio.h>
#include <linux/types.h>
#include <linux/module.h>
#include <mach/gpio.h>
#include <mach/kc_board.h>

/*------------------------------------------------------------------------
  Local define
  ------------------------------------------------------------------------*/
/* GPIO Mask Value */
#define     GPIO_MASK_139           0x00000400L
#define     GPIO_MASK_140           0x00000800L
#define     GPIO_MASK_141           0x00001000L

/* Pull_Setting Value */
#define     OEM_PULLDOWN            0x00000001
#define     OEM_NONEPULL            0x00000000

/* Port Value */
#define     HIGH_VALUE              0x01
#define     LOW_VALUE               0x00

/* Port Number */
#define     BOARD_CHECK1_NUM        139
#define     BOARD_CHECK2_NUM        140
#define     BOARD_CHECK3_NUM        141

/* Port Mask Value */
#define     PORT_MASK_LLL           0x00
#define     PORT_MASK_LLH           0x01
#define     PORT_MASK_LHL           0x02
#define     PORT_MASK_LHH           0x03
#define     PORT_MASK_HLL           0x04
#define     PORT_MASK_HLH           0x05
#define     PORT_MASK_HHL           0x06
#define     PORT_MASK_HHH           0x07

/* Set Value for No_pull */
#define BOARD_CHECK1_NO_PULL \
   GPIO_CFG(BOARD_CHECK1_NUM, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA)
#define BOARD_CHECK2_NO_PULL \
   GPIO_CFG(BOARD_CHECK2_NUM, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA)
#define BOARD_CHECK3_NO_PULL \
   GPIO_CFG(BOARD_CHECK3_NUM, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA)

/*------------------------------------------------------------------------
  Local Structure 
  ------------------------------------------------------------------------*/

static uint32_t kc_board_cfg[] = {
   GPIO_CFG(BOARD_CHECK1_NUM, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
   GPIO_CFG(BOARD_CHECK2_NUM, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
   GPIO_CFG(BOARD_CHECK3_NUM, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
};

/*------------------------------------------------------------------------
  Local Variable
  ------------------------------------------------------------------------*/
static oem_board_type _board_type = OEM_BOARD_WS2_TYPE;

/*===========================================================================

  FUNCTION OEM_board_judgement()

  DESCRIPTION
    Judge board type.

  PARAMETERS
    None.

  RETURN VALUE
    None.

  SIDE EFFECTS
    None.

===========================================================================*/
void OEM_board_judgement(void)
{
  int _value_139,_value_140,_value_141=LOW_VALUE;
  int num, result=0;
  uint8_t               _port_mask=0;
  
  /* Initialize GPIO139 and GPIO140 and GPIO141 */
  result = gpio_request( BOARD_CHECK1_NUM, "board_check1" );
  
  if( result != 0 )
  {
     printk( KERN_ERR "OEM_board_judgement() : gpio_request() Failed PORT=%d",
                                                             BOARD_CHECK1_NUM );
  }
  
  result = gpio_request( BOARD_CHECK2_NUM, "board_check2" );
  
  if( result != 0 )
  {
     printk( KERN_ERR "OEM_board_judgement() : gpio_request() Failed PORT=%d",
                                                             BOARD_CHECK2_NUM );
  }
  
  result = gpio_request( BOARD_CHECK3_NUM, "board_check3" );
  
  if( result != 0 )
  {
     printk( KERN_ERR "OEM_board_judgement() : gpio_request() Failed PORT=%d",
                                                             BOARD_CHECK3_NUM );
  }
  
  /* Set Config for GPIO139 and GPIO140 and GPIO141 */
  for( num=0 ; num < ARRAY_SIZE(kc_board_cfg); num++ )
  {
     result = gpio_tlmm_config( kc_board_cfg[num], GPIO_CFG_ENABLE);
     
     if( result != 0 )
     {
        printk( KERN_ERR "OEM_board_judgement() : Initialized num=%d Error", num );
     }
  }
  
  /* Read GPIO139, GPIO140, GPIO141 */
  _value_139 = gpio_get_value( BOARD_CHECK1_NUM );
  _value_140 = gpio_get_value( BOARD_CHECK2_NUM );
  _value_141 = gpio_get_value( BOARD_CHECK3_NUM );
  
  /* Port Mask Set */
  _port_mask = ((uint8_t)_value_139 | ((uint8_t)_value_140 << 1 ) | ((uint8_t)_value_141 << 2 ));
  
  /* Board Type Judge */
  switch( _port_mask ){
    /* GPIO139=Low GPIO140=Low GPIO141=Low */
    case PORT_MASK_LLL:
        /* For MP */
        _board_type = OEM_BOARD_MP_TYPE;

       /* No Process */
       break;
    /* GPIO139=High GPIO140=Low GPIO141=Low */
    case PORT_MASK_LLH:
        /* For RESERVED BAD condition !!!! */
// Not fixed        _board_type = OEM_BOARD_RESERVE4_TYPE;

       /* Set GPIO139 Non-Pull */
       gpio_tlmm_config( BOARD_CHECK1_NO_PULL, GPIO_CFG_ENABLE );
       break;
    /* GPIO139=Low GPIO140=High GPIO141=Low */
    case PORT_MASK_LHL:
        /* For PP2 */
        _board_type = OEM_BOARD_PP2_TYPE;

  /* Set GPIO140 Non-Pull */
       gpio_tlmm_config( BOARD_CHECK2_NO_PULL, GPIO_CFG_ENABLE );
       break;
    /* GPIO139=High GPIO140=High GPIO141=Low */
    case PORT_MASK_LHH:
        /* For RESERVED BAD Condition */
// Not fixed        _board_type = OEM_BOARD_RESERVE2_TYPE;

       /* Set GPIO139 Non-Pull */
       gpio_tlmm_config( BOARD_CHECK1_NO_PULL, GPIO_CFG_ENABLE );
       /* Set GPIO140 Non-Pull */
       gpio_tlmm_config( BOARD_CHECK2_NO_PULL, GPIO_CFG_ENABLE );
       break;
    /* GPIO139=Low GPIO140=Low GPIO141=High */
    case PORT_MASK_HLL:
       /* For PP1 */
       _board_type = OEM_BOARD_PP1_TYPE;

       /* Set GPIO141 Non-Pull */
       gpio_tlmm_config( BOARD_CHECK3_NO_PULL, GPIO_CFG_ENABLE );
       break;
    /* GPIO139=High GPIO140=Low GPIO141=High */
    case PORT_MASK_HLH:
       /* For WS2-1 */
       _board_type = OEM_BOARD_WS2_TYPE;

       /* Set GPIO139 Non-Pull */
       gpio_tlmm_config( BOARD_CHECK1_NO_PULL, GPIO_CFG_ENABLE );
       /* Set GPIO141 Non-Pull */
       gpio_tlmm_config( BOARD_CHECK3_NO_PULL, GPIO_CFG_ENABLE );
       break;
    /* GPIO139=Low GPIO140=High GPIO141=High */
    case PORT_MASK_HHL:
       /* For WS1 */
       _board_type = OEM_BOARD_WS1_TYPE;
       
       /* Set GPIO140 Non-Pull */
       gpio_tlmm_config( BOARD_CHECK2_NO_PULL, GPIO_CFG_ENABLE );
       /* Set GPIO141 Non-Pull */
       gpio_tlmm_config( BOARD_CHECK3_NO_PULL, GPIO_CFG_ENABLE );
       break;
    /* GPIO139=High GPIO140=High GPIO141=High */
    case PORT_MASK_HHH:
       /* For WS0 */
       _board_type = OEM_BOARD_WS0_TYPE;
       
       /* Set GPIO139 Non-Pull */
       gpio_tlmm_config( BOARD_CHECK1_NO_PULL, GPIO_CFG_ENABLE );
       /* Set GPIO140 Non-Pull */
       gpio_tlmm_config( BOARD_CHECK2_NO_PULL, GPIO_CFG_ENABLE );
       /* Set GPIO141 Non-Pull */
       gpio_tlmm_config( BOARD_CHECK3_NO_PULL, GPIO_CFG_ENABLE );
       break;
    default:
       break;
  }
}

/*===========================================================================

  FUNCTION OEM_get_board()

  DESCRIPTION
    get type

  PARAMETERS
    None.

  RETURN VALUE
    oem_board_type : Board Type

  SIDE EFFECTS
    None.

===========================================================================*/
oem_board_type OEM_get_board(void)
{
  return( _board_type );
}
EXPORT_SYMBOL(OEM_get_board);

