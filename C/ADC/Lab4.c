//Analog input to FRDM KL25Z pin E20 (PTE20)
//PWM output from FRDM KL25Z pin C2  (PTC2)

// LAB 4

#include "MKL25Z4.h"
void ADC0_init(void);
void PWM_init(void);
int option = 1;

int main(void) {

    short int result;
    BOARD_InitBootClocks();

    PWM_init();                     /* Configure PWM */
    ADC0_init();                    /* Configure ADC0 */

    while (1) {
        ADC0->SC1[3] = 0;           /* start conversion on channel 0 */
        while(!(ADC0->SC1[3] & 0x80)) { } /* wait for conversion complete */
        result = ADC0->R[0];        /* read conversion result and clear COCO flag */
        TPM0->CONTROLS[1].CnV = 1500 + result*3/2;  /* Set up channel value between 2.5% and 12.5%*/
    }
}

void PWM_init(void)
{
    SIM->SCGC5 |= 0x1800;       		   /* enable clock to Port C*/
    SIM->SCGC6 |= 0x01000000;   		   /* enable clock to TPM0 */
    PORTC->PCR[2] = 0x0400;     		   /* PTC2 used by TPM0 */
    SIM->SOPT2 |= 0x01000000;   		   /* use MCGFLLCLK as timer counter clock */

    TPM0->SC = 0;               		  /* disable timer */
    TPM0->CONTROLS[1].CnSC = 0x20|0x08;   /* edge-aligned PWM, pulse high MSB:MSA=10, ELSB:ELSA=10*/
    TPM0->MOD = 60000;          		  /* Set up modulo register for 50 Hz - 48.00 MHz */
    TPM0->CONTROLS[1].CnV = 1500;  		  /* Set up channel value for 2.5% duty-cycle */
    TPM0->SC = 0x0C;            		  /* enable TPM0 with pre-scaler /16 */
}

void ADC0_init(void)
{
	uint16_t calibration;

    SIM->SCGC5 |= 0x2000;       /* clock to PORTE */
    if (option == 1)
    {
    	PORTE->PCR[22] = 0;         /* Pot PTE20 analog input */
    }
    else if (option == 2)
    {
    	PORTE->PCR[20] = 0;         /* LDR PTE20 analog input */
    }

    SIM->SCGC6 |= 0x8000000;    /* clock to ADC0 */
    ADC0->SC2 &= ~0x40;         /* software trigger */
    /* clock div by 4, long sample time, single ended 12 bit, bus clock */
    ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00;

    //Start Calibration
    ADC0->SC3 |= ADC_SC3_CAL_MASK;
	while (ADC0->SC3 & ADC_SC3_CAL_MASK) {
	// Wait for calibration to complete
	}
	// Finish off the calibration
	// Initialize a 16-bit variable in RAM
	calibration = 0x0;
	// Add the plus-side calibration results to the variable
	calibration += ADC0->CLP0;
	calibration += ADC0->CLP1;
	calibration += ADC0->CLP2;
	calibration += ADC0->CLP3;
	calibration += ADC0->CLP4;
	calibration += ADC0->CLPS;
	// Divide by two
	calibration /= 2;
	// Set the MSB of the variable
	calibration |= 0x8000;
	// Store the value in the plus-side gain calibration register
	ADC0->PG = calibration;
	// Repeat the procedure for the minus-side calibration value
	calibration = 0x0000;
	calibration += ADC0->CLM0;
	calibration += ADC0->CLM1;
	calibration += ADC0->CLM2;
	calibration += ADC0->CLM3;
	calibration += ADC0->CLM4;
	calibration += ADC0->CLMS;
	calibration /= 2;
	calibration |= 0x8000;
	ADC0->MG = calibration;
    //Done Calibration

	/* Reconfigure ADC0*/
    /* clock div by 4, long sample time, single ended 12 bit, bus clock */
    ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00;
}
