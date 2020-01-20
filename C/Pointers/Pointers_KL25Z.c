/*
 * Copyright (c) 2017, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Pointers_KL25Z.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

	 char ch;

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("hello world.\r\n");

	uint32_t a, *b;

	a = 0xDEADBEEF;
    PRINTF("&a = %x a = %x\r\n", &a, a);

    b = &a;
    *b = 0xFEEDF00D;

    PRINTF("b = %x *b = %x\r\n", b, *b);
    PRINTF("&a = %x a = %x\r\n", &a, a);

    typedef struct foo
    {
      int x;
      float y;
    } myfoo;

    struct foo bar;  	//myfoo bar;
    struct foo *pbar;	//myfoo *pbar;

    bar.x = 10;
    bar.y = 1.34e-10; //0x2f1355a6

    pbar = &bar;
    (*pbar).x = 6;
    pbar->y = 1.380648813e-23; //0x19858735

    (*(struct foo *)(0x20002D00)).x  = 9;
    ((struct foo  *)(0x20002D00))->y = 1.60217662e-19; //0x203d26d1

    (*(myfoo *)(0x20002D00)).x 		 = 4;
    ((myfoo  *)(0x20002D00))->y      = 1.380648813e-23; //0x19858735

    (*((uint32_t *)0x40048038))  = 0x00000400;
    (*((uint32_t *)0x4004A04C))  = 0x00000100;
    (*((uint32_t *)0x400FF054))  = 0x00080000;
    (*((uint32_t *)0x400FF040))  = 0x00000000;
    (*((uint32_t *)0x400FF040))  = 0x00080000;

    (*((uint32_t *)0x4004A048))  = 0x00000100;
    (*((uint32_t *)0x400FF054))  = 0x00040000;
    (*((uint32_t *)0x400FF040))  = 0x00000000;
    (*((uint32_t *)0x400FF040))  = 0x00040000;

    while (1)
    {
        ch = GETCHAR();
        PUTCHAR(ch);
    }
    return 0 ;
}
