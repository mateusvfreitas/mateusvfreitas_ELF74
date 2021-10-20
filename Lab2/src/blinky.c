//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2013-2020 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.2.0.295 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/systick.h"
#include <stdio.h>

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED using direct register
//! access.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

volatile uint32_t interruptCounter = 0;

// Conta interrup��es
void SysTickIntHandler(void)
{
    interruptCounter++;
}

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
int
main(void)
{
    volatile uint32_t ui32Loop;
    uint32_t sysTickValue=0, pinValue=0, reactionTime;    
        
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
    
    // Habilita a porta do GPIO que � usada para o bot�o
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    // Verifica se o acesso ao perif�rico est� habilitado
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
    {
    }
    
    //
    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);

    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTJ_BASE ,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    IntMasterEnable();
    SysTickIntRegister(SysTickIntHandler);  
    SysTickPeriodSet(10000000);  
    SysTickIntEnable();
    SysTickEnable();
    
    interruptCounter = 0;
    
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
    
    while(interruptCounter<12){
    }
    
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
    
    pinValue = GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0);
    sysTickValue = SysTickValueGet();
    interruptCounter = 0;
    
    while(pinValue == 1 && interruptCounter < 36){
      pinValue = GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0);     
    }
    
    reactionTime = SysTickValueGet() - sysTickValue + (10000000 * interruptCounter);
    
    printf("Clocks: %d\n", reactionTime);
    printf("%.4f segundos\n", (reactionTime*0.000000008333));
   
}
