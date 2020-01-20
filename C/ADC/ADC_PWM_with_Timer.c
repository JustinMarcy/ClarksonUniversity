//Analog input to FRDM KL25Z pin E20 (PTE20)
//Apply a 3.3 V p-p sine with 1.67 V DC offset
//PWM output from FRDM KL25Z pin C2  (PTC2)
//The sampling rate is dictated by the period of the PWM
//PWM frequency = 48 MHx/2047 = 22.9 KHz
//To avoid aliasing keep the input frequency less than 22.9/2 = 11.45 KHz
//To observe aliasing, increase input frequency

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
void ADC0_init(void);
void PWM_init(void);
void Timer0_init(void);
volatile uint32_t result;
//***********************************************************************************************************
// Three projects in one.This project generates clock or PWM signals.										*
// Be sure to chose the correct prescaler Setting for each                                                          *
// Buzzer & DC motor - prescaler is 8 - Modify handler code accordingly by commenting and uncommenting codes*
// PWM servo - prescaler is 16 - Chose handler code for the servo                                           *
//***********************************************************************************************************
#define mod 2047

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    PRINTF("hello world.\r\n");

    __disable_irq();        /* global disable IRQs */
    SIM->SCGC5 |= 0x400;        /* enable clock to Port B */
    PORTB->PCR[18] = 0x100;     /* make PTB18 pin as GPIO */
    PTB->PDDR |= 0x40000;       /* make PTB18 as output pin */
    PWM_init();                     /* Configure PWM */
    ADC0_init();                    /* Configure ADC0 */
//    Timer0_init();
    __enable_irq();         /* global enable IRQs */

    while (1) {
    }
}

void PWM_init(void) // Also enables the TOF interrupt
{
    SIM->SCGC5 |= 0x0800;       /* enable clock to Port C*/
    SIM->SCGC6 |= 0x01000000;   /* enable clock to TPM0 */
    PORTC->PCR[2] = 0x0400;     /* PTC2 used by TPM0 */
    SIM->SOPT2 |= 0x01000000;   /* use MCGFLLCLK as timer counter clock */
    TPM0->SC = 0;               /* disable timer */
    TPM0->CONTROLS[1].CnSC = 0x20|0x08;   /* edge-aligned, pulse high MSB:MSA=10, ELSB:ELSA=10*/
    TPM0->MOD = mod;            /* Set up modulo register for 42.6 us period or 23.3 kHz rate */
    TPM0->CONTROLS[1].CnV = mod/2;  /* Set up default channel value for 50% dutycycle */
	TPM0->SC |= 0x80;           /* clear TOF */
	TPM0->SC |= 0x40;           /* enable timeout interrupt */
//*************************PRE-Scaler settings *********************************************
//	TPM0->SC |= 0x0B;           /* enable timer with prescaler /8 For DC motor and Buzzer*/
	TPM0->SC |= 0x0C;           /* enable timer with prescaler /16 for SERVO*/
//******************************************************************************************
    NVIC_EnableIRQ(TPM0_IRQn);  /* enable Timer1 interrupt in NVIC */
}


void TPM0_IRQHandler(void) {
    ADC0->SC1[0] = 0;           		/* start conversion on channel 0 */
    while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
    result = ADC0->R[0];        /* read conversion result and clear COCO flag */

/* 1.-----Frequency generation from 100 to 1000 Hz, 50% Duty cycle------*/

//    TPM0->MOD = 6000 + result*12;
//    TPM0->CONTROLS[1].CnV = TPM0->MOD/2;  /* Set up channel value 50% Duty cycle*/

/* 2. ----- DC Motor Control with PWM 0-100% duty cycle----------------*/

//    TPM0->MOD = mod*2;
//    TPM0->CONTROLS[1].CnV = result;  /* Set up channel value 50% Duty cycle*/

/* 3. ------ PWM Generation for Servo---Set prescaler /16--------------*/

    TPM0->MOD = 60000;
    TPM0->CONTROLS[1].CnV = 1500 + result*3/2;  /* Set up channel value 50% Duty cycle*/

/*---------------------------------------------------------------------*/

    PTB->PTOR = 0x40000;        /* toggle red LED */
    TPM0->SC |= 0x80;           /* clear TOF */
}

void ADC0_init(void)
{
    SIM->SCGC5 |= 0x2000;       /* clock to PORTE */
    PORTE->PCR[20] = 0;         /* PTE20 analog input */
    SIM->SCGC6 |= 0x8000000;    /* clock to ADC0 */
    ADC0->SC2 &= ~0x40;         /* software trigger */
    ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00; /* clock div by 4, long sample time, single ended 12 bit, bus clock */
}



