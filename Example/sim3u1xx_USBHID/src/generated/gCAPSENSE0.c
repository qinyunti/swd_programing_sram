//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

//==============================================================================
// WARNING:
//
// This file is auto-generated by AppBuilder and should not be modified.
// Any hand modifications will be lost if the project is regenerated.
//==============================================================================
// library
// hal
#include <si32_device.h>
#include <SI32_CLKCTRL_A_Type.h>
#include <SI32_CAPSENSE_A_Type.h>
// application
#include "gCAPSENSE0.h"

//==============================================================================
// 2nd Level Interrupt Handlers
//==============================================================================
extern void my_convert_complete_handler(void);
extern void my_scan_complete_handler(void);

//==============================================================================
//1st LEVEL  INTERRUPT HANDLERS
//==============================================================================
// Prints the value sensed at the end of each convert, and a newline at the end of each scan
void CAPSENSE0_IRQHandler(void)
{
  if (SI32_CAPSENSE_A_is_conversion_complete_interrupt_pending(SI32_CAPSENSE_0))
  {
    my_convert_complete_handler();
  }// is_conversion_complete_interrupt_pending

  if (SI32_CAPSENSE_A_is_end_of_scan_interrupt_pending(SI32_CAPSENSE_0))
  {
    my_scan_complete_handler();
  }// is_end_of_scan_interrupt_pending
}

//==============================================================================
//CONFIGURATION FUNCTIONS
//==============================================================================

//------------------------------------------------------------------------------
void CAPSENSE0_enter_default_mode_from_reset(void)
{
   // ENABLE CAPSENSE CLOCK
   SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0,
                                                   SI32_CLKCTRL_A_APBCLKG0_CAPSENSE0);

   // SETUP CAPSENSE FOR SINGLE SCAN OF SLIDER (CS0-3, 8-9)
   SI32_CAPSENSE_A_enable_bias(SI32_CAPSENSE_0);
   SI32_CAPSENSE_A_select_single_conversion_mode(SI32_CAPSENSE_0);
   SI32_CAPSENSE_A_set_conversion_start_source(SI32_CAPSENSE_0, 0);
   SI32_CAPSENSE_A_write_scanm(SI32_CAPSENSE_0, 0x01);
   SI32_CAPSENSE_A_set_gain(SI32_CAPSENSE_0, 1);
   SI32_CAPSENSE_A_set_conversion_rate(SI32_CAPSENSE_0,
      SI32_CAPSENSE_A_CONVERSION_RATE_16_CLOCKS_16_BITS);
   SI32_CAPSENSE_A_set_number_to_accumulate(SI32_CAPSENSE_0,
      SI32_CAPSENSE_A_ACCUMULATOR_MODE_32_SAMPLES);

   // ENABLE INTERRUPTS
   NVIC_ClearPendingIRQ(CAPSENSE0_IRQn);
   NVIC_EnableIRQ(CAPSENSE0_IRQn);
   SI32_CAPSENSE_A_enable_conversion_done_interrupt(SI32_CAPSENSE_0);
}

//-eof--------------------------------------------------------------------------
