/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#include <linux/string.h>
#ifdef BUILD_UBOOT
#include <asm/arch/mt6573_gpio.h>
#else
#include <mach/mt6573_gpio.h>
#endif
#include "lcm_drv.h"


// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (800)
#define FRAME_HEIGHT (480)


// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

static __inline void send_ctrl_cmd(unsigned int cmd)
{
    unsigned char temp1 = (unsigned char)((cmd >> 8) & 0xFF);
    unsigned char temp2 = (unsigned char)(cmd & 0xFF);

    lcm_util.send_data(0x2000 | temp1);
    lcm_util.send_data(0x0000 | temp2);
}

static __inline void send_data_cmd(unsigned int data)
{
    lcm_util.send_data(0x0004 | data);
}

static __inline void set_lcm_register(unsigned int regIndex,
                                      unsigned int regData)
{
    send_ctrl_cmd(regIndex);
    send_data_cmd(regData);
}

static void init_lcm_registers(void)
{
/*    send_ctrl_cmd(0x1100);

    MDELAY(200);

    send_ctrl_cmd(0xC000); send_data_cmd(0x86);
    send_ctrl_cmd(0xC001); send_data_cmd(0x00);
    send_ctrl_cmd(0xC002); send_data_cmd(0x86);
    send_ctrl_cmd(0xC003); send_data_cmd(0x00);
    send_ctrl_cmd(0xC100); send_data_cmd(0x45);
    send_ctrl_cmd(0xC200); send_data_cmd(0x21);
    send_ctrl_cmd(0xC202); send_data_cmd(0x02);
    send_ctrl_cmd(0xB600); send_data_cmd(0x30);
    send_ctrl_cmd(0xB602); send_data_cmd(0x30);
    send_ctrl_cmd(0xC700); send_data_cmd(0x8F);
    send_ctrl_cmd(0xE000); send_data_cmd(0x0E);
    send_ctrl_cmd(0xE001); send_data_cmd(0x14);
    
    send_ctrl_cmd(0xE002); send_data_cmd(0x29);
    send_ctrl_cmd(0xE003); send_data_cmd(0x3A);
    send_ctrl_cmd(0xE004); send_data_cmd(0x1D);
    send_ctrl_cmd(0xE005); send_data_cmd(0x30);
    send_ctrl_cmd(0xE006); send_data_cmd(0x61);
    send_ctrl_cmd(0xE007); send_data_cmd(0x3D);
    send_ctrl_cmd(0xE008); send_data_cmd(0x22);
    send_ctrl_cmd(0xE009); send_data_cmd(0x2A);
    send_ctrl_cmd(0xE00A); send_data_cmd(0x87);
    send_ctrl_cmd(0xE00B); send_data_cmd(0x16);
    send_ctrl_cmd(0xE00C); send_data_cmd(0x3B);
    send_ctrl_cmd(0xE00D); send_data_cmd(0x4C);
    send_ctrl_cmd(0xE00E); send_data_cmd(0x78);
    send_ctrl_cmd(0xE00F); send_data_cmd(0x96);
    send_ctrl_cmd(0xE010); send_data_cmd(0x4A);
    send_ctrl_cmd(0xE011); send_data_cmd(0x4D);
    send_ctrl_cmd(0xE100); send_data_cmd(0x0E);
    send_ctrl_cmd(0xE101); send_data_cmd(0x14);
    send_ctrl_cmd(0xE102); send_data_cmd(0x29);
    send_ctrl_cmd(0xE103); send_data_cmd(0x3A);
    send_ctrl_cmd(0xE104); send_data_cmd(0x1D);
    send_ctrl_cmd(0xE105); send_data_cmd(0x30);
    send_ctrl_cmd(0xE106); send_data_cmd(0x61);
    send_ctrl_cmd(0xE107); send_data_cmd(0x3F);
    send_ctrl_cmd(0xE108); send_data_cmd(0x20);
    send_ctrl_cmd(0xE109); send_data_cmd(0x26);
    send_ctrl_cmd(0xE10A); send_data_cmd(0x83);
    send_ctrl_cmd(0xE10B); send_data_cmd(0x16);
    send_ctrl_cmd(0xE10C); send_data_cmd(0x3B);
    send_ctrl_cmd(0xE10D); send_data_cmd(0x4C);
    send_ctrl_cmd(0xE10E); send_data_cmd(0x78);
    send_ctrl_cmd(0xE10F); send_data_cmd(0x96);
    send_ctrl_cmd(0xE110); send_data_cmd(0x4A);
    send_ctrl_cmd(0xE111); send_data_cmd(0x4D);
    send_ctrl_cmd(0xE200); send_data_cmd(0x0E);
    send_ctrl_cmd(0xE201); send_data_cmd(0x14);
    send_ctrl_cmd(0xE202); send_data_cmd(0x29);
    send_ctrl_cmd(0xE203); send_data_cmd(0x3A);
    send_ctrl_cmd(0xE204); send_data_cmd(0x1D);
    send_ctrl_cmd(0xE205); send_data_cmd(0x30);
    send_ctrl_cmd(0xE206); send_data_cmd(0x61);
    send_ctrl_cmd(0xE207); send_data_cmd(0x3D);
    send_ctrl_cmd(0xE208); send_data_cmd(0x22);
    send_ctrl_cmd(0xE209); send_data_cmd(0x2A);
    send_ctrl_cmd(0xE20A); send_data_cmd(0x87);
    send_ctrl_cmd(0xE20B); send_data_cmd(0x16);
    send_ctrl_cmd(0xE20C); send_data_cmd(0x3B);
    send_ctrl_cmd(0xE20D); send_data_cmd(0x4C);
    send_ctrl_cmd(0xE20E); send_data_cmd(0x78);
    send_ctrl_cmd(0xE20F); send_data_cmd(0x96);
    send_ctrl_cmd(0xE210); send_data_cmd(0x4A);
    send_ctrl_cmd(0xE211); send_data_cmd(0x4D);
    send_ctrl_cmd(0xE300); send_data_cmd(0x0E);
    send_ctrl_cmd(0xE301); send_data_cmd(0x14);
    
    send_ctrl_cmd(0xE302); send_data_cmd(0x29);
    send_ctrl_cmd(0xE303); send_data_cmd(0x3A);
    send_ctrl_cmd(0xE304); send_data_cmd(0x1D);
    send_ctrl_cmd(0xE305); send_data_cmd(0x30);
    send_ctrl_cmd(0xE306); send_data_cmd(0x61);
    send_ctrl_cmd(0xE307); send_data_cmd(0x3F);
    send_ctrl_cmd(0xE308); send_data_cmd(0x20);
    send_ctrl_cmd(0xE309); send_data_cmd(0x26);
    send_ctrl_cmd(0xE30A); send_data_cmd(0x83);
    send_ctrl_cmd(0xE30B); send_data_cmd(0x16);
    send_ctrl_cmd(0xE30C); send_data_cmd(0x3B);
    send_ctrl_cmd(0xE30D); send_data_cmd(0x4C);
    send_ctrl_cmd(0xE30E); send_data_cmd(0x78);
    send_ctrl_cmd(0xE30F); send_data_cmd(0x96);
    send_ctrl_cmd(0xE310); send_data_cmd(0x4A);
    send_ctrl_cmd(0xE311); send_data_cmd(0x4D);
    send_ctrl_cmd(0xE400); send_data_cmd(0x0E);
    send_ctrl_cmd(0xE401); send_data_cmd(0x14);
    send_ctrl_cmd(0xE402); send_data_cmd(0x29);
    send_ctrl_cmd(0xE403); send_data_cmd(0x3A);
    send_ctrl_cmd(0xE404); send_data_cmd(0x1D);
    send_ctrl_cmd(0xE405); send_data_cmd(0x30);
    send_ctrl_cmd(0xE406); send_data_cmd(0x61);
    send_ctrl_cmd(0xE407); send_data_cmd(0x3D);
    send_ctrl_cmd(0xE408); send_data_cmd(0x22);
    send_ctrl_cmd(0xE409); send_data_cmd(0x2A);
    send_ctrl_cmd(0xE40A); send_data_cmd(0x87);
    send_ctrl_cmd(0xE40B); send_data_cmd(0x16);
    send_ctrl_cmd(0xE40C); send_data_cmd(0x3B);
    send_ctrl_cmd(0xE40D); send_data_cmd(0x4C);
    send_ctrl_cmd(0xE40E); send_data_cmd(0x78);
    send_ctrl_cmd(0xE40F); send_data_cmd(0x96);
    send_ctrl_cmd(0xE410); send_data_cmd(0x4A);
    send_ctrl_cmd(0xE411); send_data_cmd(0x4D);
    send_ctrl_cmd(0xE500); send_data_cmd(0x0E);
    send_ctrl_cmd(0xE501); send_data_cmd(0x14);
    send_ctrl_cmd(0xE502); send_data_cmd(0x29);
    send_ctrl_cmd(0xE503); send_data_cmd(0x3A);
    send_ctrl_cmd(0xE504); send_data_cmd(0x1D);
    send_ctrl_cmd(0xE505); send_data_cmd(0x30);
    send_ctrl_cmd(0xE506); send_data_cmd(0x61);
    send_ctrl_cmd(0xE507); send_data_cmd(0x3F);
    send_ctrl_cmd(0xE508); send_data_cmd(0x20);
    send_ctrl_cmd(0xE509); send_data_cmd(0x26);
    send_ctrl_cmd(0xE50A); send_data_cmd(0x83);
    
    send_ctrl_cmd(0xE50B); send_data_cmd(0x16);
    send_ctrl_cmd(0xE50C); send_data_cmd(0x3B);
    send_ctrl_cmd(0xE50D); send_data_cmd(0x4C);
    send_ctrl_cmd(0xE50E); send_data_cmd(0x78);
    send_ctrl_cmd(0xE50F); send_data_cmd(0x96);
    send_ctrl_cmd(0xE510); send_data_cmd(0x4A);
    send_ctrl_cmd(0xE511); send_data_cmd(0x4D);
    send_ctrl_cmd(0x2900);

    MDELAY(200);
    
    send_ctrl_cmd(0x2C00);*/    
}


// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{
    memset(params, 0, sizeof(LCM_PARAMS));

    params->type   = LCM_TYPE_DPI;
    params->ctrl   = LCM_CTRL_SERIAL_DBI;
    params->width  = FRAME_WIDTH;
    params->height = FRAME_HEIGHT;
	params->io_select_mode = 0;	

    /* serial host interface configurations */
    
    params->dbi.port                    = 0;
    params->dbi.clock_freq              = LCM_DBI_CLOCK_FREQ_7M;
    params->dbi.data_width              = LCM_DBI_DATA_WIDTH_8BITS;
    params->dbi.data_format.color_order = LCM_COLOR_ORDER_RGB;
    params->dbi.data_format.trans_seq   = LCM_DBI_TRANS_SEQ_MSB_FIRST;
    params->dbi.data_format.padding     = LCM_DBI_PADDING_ON_LSB;
    params->dbi.data_format.format      = LCM_DBI_FORMAT_RGB565;
    params->dbi.data_format.width       = LCM_DBI_DATA_WIDTH_16BITS;
    params->dbi.cpu_write_bits          = LCM_DBI_CPU_WRITE_32_BITS;
    params->dbi.io_driving_current      = LCM_DRIVING_CURRENT_8MA;

    params->dbi.serial.cs_polarity      = LCM_POLARITY_RISING;
    params->dbi.serial.clk_polarity     = LCM_POLARITY_RISING;
    params->dbi.serial.clk_phase        = LCM_CLOCK_PHASE_0;
    params->dbi.serial.is_non_dbi_mode  = 1;
    
    /* RGB interface configurations */
    
    params->dpi.mipi_pll_clk_ref  = 0;      //the most important parameters: set pll clk to 66Mhz and dpi clk to 33Mhz
    params->dpi.mipi_pll_clk_div1 = 36;
    params->dpi.mipi_pll_clk_div2 = 7;
    params->dpi.dpi_clk_div       = 2;
    params->dpi.dpi_clk_duty      = 1;

    params->dpi.clk_pol           = LCM_POLARITY_RISING;
    params->dpi.de_pol            = LCM_POLARITY_RISING;
    params->dpi.vsync_pol         = LCM_POLARITY_FALLING;
    params->dpi.hsync_pol         = LCM_POLARITY_FALLING;

    params->dpi.hsync_pulse_width = 30;
    params->dpi.hsync_back_porch  = 16;
    params->dpi.hsync_front_porch = 210;
    params->dpi.vsync_pulse_width = 13;
    params->dpi.vsync_back_porch  = 10;
    params->dpi.vsync_front_porch = 22;
    
    params->dpi.format            = LCM_DPI_FORMAT_RGB888;   // format is 24 bit
    params->dpi.rgb_order         = LCM_COLOR_ORDER_RGB;
    params->dpi.is_serial_output  = 0;

    params->dpi.intermediat_buffer_num = 2;

    params->dpi.io_driving_current = LCM_DRIVING_CURRENT_8MA | LCM_DRIVING_CURRENT_4MA | LCM_DRIVING_CURRENT_2MA;;
}


static void lcm_init(void)
{
    lcm_util.set_gpio_dir(GPIO138, GPIO_DIR_OUT);
    lcm_util.set_gpio_mode(GPIO138, GPIO_MODE_01);
    SET_RESET_PIN(0);
    MDELAY(25);
    SET_RESET_PIN(1);
    MDELAY(50);

 //   init_lcm_registers();
}


static void lcm_suspend(void)
{
/*    send_ctrl_cmd(0x2800);
    send_ctrl_cmd(0x1000);
    MDELAY(20);*/
}


static void lcm_resume(void)
{
/*    send_ctrl_cmd(0x1100);
    MDELAY(200);
	send_ctrl_cmd(0x2900);*/
}


// ---------------------------------------------------------------------------
//  Get LCM Driver Hooks
// ---------------------------------------------------------------------------
LCM_DRIVER ha5266_lcm_drv = 
{
    .name			= "ha5266",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
};
