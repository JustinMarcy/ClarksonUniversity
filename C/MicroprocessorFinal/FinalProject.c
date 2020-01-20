#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

void delayMs(int n);
void delayUs(int n);
void keypad_init(void);
char keypad_getkey(void);
void UART0_init(void);
void UART0_Transmit_Poll(uint8_t data);
void LCD_nibble_write(unsigned char data, unsigned char control);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
void calcAndDisplServoAngle(int);
void setServoPositionToAngle(int);


#define RS 4    /* BIT2 mask */
#define EN 8    /* BIT3 mask */
#define mod 2047

short int servoMin = 1320, servoMax = 7320; // 2.2% to 12.2% because higher numbers seem to get servo stuck
short int servoScanSpeed = 10; // higher = servo moves faster in scan mode
char prevKey[] = "aa";
char prevKeypadKeys[] = "aa";
char prevKeyboardKey = 'a';
int ldr_pot = 3;
unsigned char hexKeys[] = {' ','A','3','2','1','B','6','5','4','C','9','8','7','D','#','0','*'};
int counter1 = 0, counter2 = 0;
char c = '`';
unsigned char key, keypressed;
short int result;
char displayString1[] = " Potentiometer  ";
char displayString2[] = " Photoresistor  ";
char displayString3[] = "   Servo scan   ";
char displayString4[] = "  Servo manual  ";
char displayString5[] = "   DC manual    ";
int main(void) {


	BOARD_InitBootClocks();
	__disable_irq();        /* global disable IRQs */
	PWM_init();                     /* Configure PWM */
	ADC0_init();                    /* Configure ADC0 */
	UART0_init();
	keypad_init();
	LCD_init();
	__enable_irq();         /* global enable IRQs */
	LCD_command(1);         /* clear display */
	delayMs(8);
	char string[16];

	while(1)
	{
		TPM0_IRQHandler();
	}
}
void PORTD_IRQHandler(void)
{
	/*TODO: add numbers of modes to output to putty in front of words*/
	unsigned char key = keypad_getkey();
	char string[16];

	keypressed = hexKeys[key];
	PRINTF("Key pressed = %c\r\n", keypressed);
	prevKeypadKeys[0] = prevKeypadKeys[1];
	prevKeypadKeys[1] = keypressed;

	if (strcmp(prevKeypadKeys,"#1")==0) {
		strncpy(string, displayString1, 16);
		delayUs(8); UART0->D = '#';
		delayUs(8); UART0->D = '1';
		for (int i=0; i<sizeof(string); i++){
			LCD_command(0x80|i);
			LCD_data(string[i]);
			UART0->D = string[i];
		}
		delayUs(8); UART0->D = '\r';
		ldr_pot = 3;
	}
	else if (strcmp(prevKeypadKeys,"#2")==0) {
		strncpy(string, displayString2, 16);
		delayUs(8); UART0->D = '#';
		delayUs(8); UART0->D = '2';
		for (int i=0; i<sizeof(string); i++){
			LCD_command(0x80|i);
			LCD_data(string[i]);
			UART0->D = string[i];
		}
		delayUs(8); UART0->D = '\r';
		ldr_pot = 0;
	}
	else if (strcmp(prevKeypadKeys,"#3")==0) {
		strncpy(string, displayString3, 16);
		delayUs(8); UART0->D = '#';
		delayUs(8); UART0->D = '3';
		for (int i=0; i<sizeof(string); i++){
			LCD_command(0x80|i);
			LCD_data(string[i]);
			UART0->D = string[i];
		}
		delayUs(8); UART0->D = '\r';
	}
	else if (strcmp(prevKeypadKeys,"#4")==0) {
		strncpy(string, displayString4, 16);
		delayUs(8); UART0->D = '#';
		delayUs(8); UART0->D = '4';
		for (int i=0; i<sizeof(string); i++){
			LCD_command(0x80|i);
			LCD_data(string[i]);
			UART0->D = string[i];
		}
		delayUs(8); UART0->D = '\r';
	}
	else if (strcmp(prevKeypadKeys,"#5")==0) {
		strncpy(string, displayString5, 16);
		delayUs(8); UART0->D = '#';
		delayUs(8); UART0->D = '5';
		for (int i=0; i<sizeof(string); i++){
			LCD_command(0x80|i);
			LCD_data(string[i]);
			UART0->D = string[i];
		}
		delayUs(8); UART0->D = '\r';
	}

	PTD->PDDR |= 0x0F;          /* enable all rows */
	PTD->PCOR = 0x0F;
	PORTD->ISFR |= 0xF0; // clear flag on pins 7-4
}

void keypad_init(void)
{
	SIM->SCGC5   |= 0x1000;     /* enable clock to Port D*/
	PORTD->PCR[0] = 0x103;      /* make PTD0 pin as GPIO and enable pullup*/
	PORTD->PCR[1] = 0x103;      /* make PTD1 pin as GPIO and enable pullup*/
	PORTD->PCR[2] = 0x103;      /* make PTD2 pin as GPIO and enable pullup*/
	PORTD->PCR[3] = 0x103;      /* make PTD3 pin as GPIO and enable pullup*/
	PORTD->PCR[4] = 0x103;      /* make PTD4 pin as GPIO and enable pullup*/
	PORTD->PCR[5] = 0x103;      /* make PTD5 pin as GPIO and enable pullup*/
	PORTD->PCR[6] = 0x103;      /* make PTD6 pin as GPIO and enable pullup*/
	PORTD->PCR[7] = 0x103;      /* make PTD7 pin as GPIO and enable pullup*/
	PTD->PDDR     = 0x0F;       /* make PTD7-4 as input pins, PTC3-0 as outputs */

	// configure input pins PTD7-4 for interrupt
	PORTD->PCR[7] &= ~0xF0000; // clear interrupt selection
	PORTD->PCR[7] |= 0xA0000; // enable falling edge interrupt
	PORTD->PCR[6] &= ~0xF0000; // clear interrupt selection
	PORTD->PCR[6] |= 0xA0000; // enable falling edge interrupt
	PORTD->PCR[5] &= ~0xF0000; // clear interrupt selection
	PORTD->PCR[5] |= 0xA0000; // enable falling edge interrupt
	PORTD->PCR[4] &= ~0xF0000; // clear interrupt selection
	PORTD->PCR[4] |= 0xA0000; // enable falling edge interrupt

	NVIC_EnableIRQ(PORTD_IRQn); // enable INT31 for PORTD interrupts

}

char keypad_getkey(void)
{
	int row, col;
	const char row_select[] = {0x01, 0x02, 0x04, 0x08}; /* one row is active */

	/* If a key is pressed, it gets here to find out which key.
	 * It activates one row at a time and read the input to see
	 * which column is active. */
	for (row = 0; row < 4; row++)
	{
		PTD->PDDR = 0;                  /* disable all rows */
		PTD->PDDR |= row_select[row];   /* enable one row */
		PTD->PCOR = row_select[row];    /* drive the active row low */
		delayUs(2);                     /* wait for signal to settle */
		col = PTD->PDIR & 0xF0;         /* read all columns */
		if (col != 0xF0) break;         /* if one of the input is low, some key is pressed. */
	}

	/* gets here when one of the rows has key pressed, check which column it is */
	if (col == 0xE0) return row * 4 + 1;    /* key in column 0 */
	if (col == 0xD0) return row * 4 + 2;    /* key in column 1 */
	if (col == 0xB0) return row * 4 + 3;    /* key in column 2 */
	if (col == 0x70) return row * 4 + 4;    /* key in column 3 */

	return 0;   /* just to be safe */
}


void LCD_init(void)
{
	SIM->SCGC5 |= 0x800;       /* enable clock to Port C */
	PORTC->PCR[8] = 0x100;     /* RS make PTC8 pin as GPIO */
	PORTC->PCR[9] = 0x100;     /* EN make PTC9 pin as GPIO */
	PORTC->PCR[10] = 0x100;    /* make PTC10 pin as GPIO */
	PORTC->PCR[11] = 0x100;    /* make PC11 pin as GPIO */
	PORTC->PCR[12] = 0x100;    /* make PTC12 pin as GPIO */
	PORTC->PCR[13] = 0x100;    /* make PTC13 pin as GPIO */
	PTC->PDDR |= 0x3F00;       /* make PTC13-8 as output pins */

	delayMs(30);                /* initialization sequence */
	LCD_nibble_write(0x30, 0);
	delayMs(10);
	LCD_nibble_write(0x30, 0);
	delayMs(1);
	LCD_nibble_write(0x30, 0);
	delayMs(1);
	LCD_nibble_write(0x20, 0);  /* use 4-bit data mode */
	delayMs(1);

	LCD_command(0x28);          /* set 4-bit data, 2-line, 5x7 font */
	LCD_command(0x06);          /* move cursor right */
	LCD_command(0x01);          /* clear screen, move cursor to home */
	LCD_command(0x0F);          /* turn on display, cursor blinking */
}

void LCD_nibble_write(unsigned char data, unsigned char control)
{
	data &= 0xF0;       /* clear lower nibble for control */
	control &= 0x0F;    /* clear upper nibble for data */
	PTC->PDOR |= (data | control) << 6;       /* RS = 0, RW = 0 */
	PTC->PDOR |= (data | control | EN) << 6;  /* pulse E */
	delayMs(0);
	PTC->PDOR = data;
	PTC->PDOR = 0;
}

void LCD_command(unsigned char command)
{
	LCD_nibble_write(command & 0xF0, 0);   /* upper nibble first */
	LCD_nibble_write(command << 4, 0);     /* then lower nibble */

	if (command < 4)
		delayMs(4);
	else
		delayMs(1);
}

void LCD_data(unsigned char data)
{
	LCD_nibble_write(data & 0xF0, RS);    /* upper nibble first */
	LCD_nibble_write(data << 4, RS);      /* then lower nibble  */
	delayMs(1);
}

void delayUs(int n)
{
	for(int i = 0 ; i < n; i++) {
		for(int j = 0; j < 5; j++);
	}
}

void delayMs(int n) {
	for(int i = 0 ; i < n; i++)
		for(int j = 0 ; j < 3500; j++) { }
}

void UART0_IRQHandler(void) {
	c = UART0->D;           /* read the char received */
	UART0->D = c;	/* transmit the received char back */

	char string[16];
	if (prevKeyboardKey == '#'){
		switch(c){
		case '1':
			prevKeyboardKey = c;
			strncpy(string, displayString1, 16);
			for (int i=0; i<sizeof(string); i++){
				LCD_command(0x80|i);
				LCD_data(string[i]);
				UART0->D = string[i];
			}
			delayUs(8); UART0->D = '\r';
			ldr_pot = 3;
			break;

		case '2':
			prevKeyboardKey = c;
			strncpy(string, displayString2, 16);
			for (int i=0; i<sizeof(string); i++){
				LCD_command(0x80|i);
				LCD_data(string[i]);
				UART0->D = string[i];
			}
			delayUs(8); UART0->D = '\r';
			ldr_pot = 0;
			break;

		case '3':
			prevKeyboardKey = c;
			strncpy(string, displayString3, 16);
			for (int i=0; i<sizeof(string); i++){
				LCD_command(0x80|i);
				LCD_data(string[i]);
				UART0->D = string[i];
			}
			for(int i = servoMin; i < servoMax; i += servoScanSpeed) {  // 2.2% to 12.2%
				TPM0->CONTROLS[1].CnV = i;
				calcAndDisplServoAngle(i);
			}
			for(int i = servoMax; i > servoMin; i -= servoScanSpeed) {  // 12.2% to 2.2%
				TPM0->CONTROLS[1].CnV = i;
				calcAndDisplServoAngle(i);
			}
			delayUs(8); UART0->D = '\r';
			break;

		case '4':
			prevKeyboardKey = c;
			strncpy(string, displayString4, 16);
			for (int i=0; i<sizeof(string); i++){
				LCD_command(0x80|i);
				LCD_data(string[i]);
				UART0->D = string[i];

			}
//			delayUs(100);
//			UART0->D = 'G';
			// output menu to putty
			/* TODO: Does not output menu correctly (also not really important) */
//			char menuOfAngles[] = "0: -90; 1: -70; 2: -50; 3: -30; 4: -10; 5: +10; 6: +30; 7: +50; 8: +70; 9: +90;";
//			for (int i=0; i<sizeof(menuOfAngles); i++){
//				delayUs(100);
//				UART0->D = string[i];
//			}
			/* TODO: Does not work */
//			while(isdigit(c)) { // while input is a digit
//				switch(c){
//				case '0': setServoPositionToAngle(-90); break;
//				case '1': setServoPositionToAngle(-70); break;
//				case '2': setServoPositionToAngle(-50); break;
//				case '3': setServoPositionToAngle(-30); break;
//				case '4': setServoPositionToAngle(-10); break;
//				case '5': setServoPositionToAngle(10);  break;
//				case '6': setServoPositionToAngle(30);  break;
//				case '7': setServoPositionToAngle(50);  break;
//				case '8': setServoPositionToAngle(70);  break;
//				case '9': setServoPositionToAngle(90);  break;
//				}
//				c = UART0->D;           /* read the char received */
//			} // end while
			delayUs(8); UART0->D = '\r';
			break;

		case '5':
			prevKeyboardKey = c;
			strncpy(string, displayString5, 16);
			for (int i=0; i<sizeof(string); i++){
				LCD_command(0x80|i);
				LCD_data(string[i]);
				UART0->D = string[i];
			}
			delayUs(8); UART0->D = '\r';
			break;

		default:
			prevKeyboardKey = c;
			UART0->D = c;	/* transmit the received char back */
			break;
		}
	}
			else {
		/* TODO: Does not work here either*/
//		if(isdigit(c)) { // if input is a digit
//			switch(c){
//			case '0': setServoPositionToAngle(-90); break;
//			case '1': setServoPositionToAngle(-70); break;
//			case '2': setServoPositionToAngle(-50); break;
//			case '3': setServoPositionToAngle(-30); break;
//			case '4': setServoPositionToAngle(-10); break;
//			case '5': setServoPositionToAngle(10);  break;
//			case '6': setServoPositionToAngle(30);  break;
//			case '7': setServoPositionToAngle(50);  break;
//			case '8': setServoPositionToAngle(70);  break;
//			case '9': setServoPositionToAngle(90);  break;
//			}
//		}  // end if
		prevKeyboardKey = c;
	}
	PORTA->ISFR = 0x10; /* clear interrupt flag */
}

void UART0_init(void) {
	SIM->SCGC4 |= SIM_SCGC4_UART0(1);   /* enable clock for UART0 */
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);  /* use FLL output for UART Baud rate generator */
	UART0->C2   = 0;   /* turn off UART0 while changing configurations */
	UART0->BDH  = UART0_BDH_SBR(0);  /* SBR12:SBR8 = 0b00000    - 115200 Baud */
	UART0->BDL  = UART0_BDL_SBR(26); /* SBR7:SBR0  = 0b00001100 - 115200 Baud */
	UART0->C4   = UART0_C4_OSR(15);  /* Over Sampling Ratio (15+1) */
	UART0->C1   = UART0_C1_M(0);     /* 8-bit data */
	UART0->C2   = 0x2C;     		// enable transmit & Receive & Interrupt

	NVIC->ISER[0] |= 0x00001000;    /* enable INT12 (bit 12 of ISER[0]) */

	SIM->SCGC5     = SIM_SCGC5_PORTA(1);  /* enable clock for PORTA */
	PORTA->PCR[1]  = PORT_PCR_MUX(2);     /* make PTA2 UART0_Tx pin */
	PORTA->PCR[2]  = PORT_PCR_MUX(2);     /* make PTA1 UART0_Rx pin */
}

void PWM_init(void)
{
	/////////////////////TPM
	SIM->SCGC5 |= 0x0800;       		   /* enable clock to Port C*/
	SIM->SCGC6 |= 0x01000000;   		   /* enable clock to TPM0 */
	PORTC->PCR[2] = 0x0400;     		   /* PTC2 used by TPM0 */
	SIM->SOPT2 |= 0x01000000;   		   /* use MCGFLLCLK as timer counter clock */

	TPM0->SC = 0;               		  /* disable timer */
	TPM0->CONTROLS[1].CnSC = 0x20|0x08;   /* edge-aligned PWM, pulse high MSB:MSA=10, ELSB:ELSA=10*/
	TPM0->MOD = 60000;          		  /* Set up modulo register for 50 Hz - 48.00 MHz */
	TPM0->CONTROLS[1].CnV = 1500;  		  /* Set up channel value for 2.5% duty-cycle */
	TPM0->SC = 0x0C;            		  /* enable TPM0 with pre-scaler /16 */

	///////////////TPM2////////////////////////////
	SIM->SCGC5 |= 0x0400;       /* enable clock to Port B*/
	SIM->SCGC6 |= 0x04000000;   /* enable clock to TPM2 */
	PORTB->PCR[3] = 0x0300;     /* PTC2 used by TPM2 */
	//  SIM->SOPT2 |= 0x01000000;   /* use MCGFLLCLK as timer counter clock */
	TPM2->SC = 0;               /* disable timer */
	TPM2->CONTROLS[1].CnSC = 0x20|0x08;   /* edge-aligned, pulse high MSB:MSA=10, ELSB:ELSA=10*/
	TPM2->MOD = mod;            /* Set up modulo register for 42.6 us period or 23.3 kHz rate */
	TPM2->CONTROLS[1].CnV = mod/2;  /* Set up default channel value for 50% dutycycle */
	TPM2->SC |= 0x80;           /* clear TOF */
	TPM2->SC |= 0x40;           /* enable timeout interrupt */
	//*************************PRE-Scaler settings *********************************************
	TPM2->SC |= 0x0B;           /* enable timer with prescaler /8 For DC motor and Buzzer*/
	//	TPM2->SC |= 0x0C;           /* enable timer with prescaler /16 for SERVO*/
	//******************************************************************************************

	///////////////TPM1////////////////////////////
	SIM->SCGC5 |= 0x0400;       /* enable clock to Port B*/
	SIM->SCGC6 |= 0x02000000;   /* enable clock to TPM1 */
	PORTB->PCR[1] = 0x0300;     /* PTC2 used by TPM1 */
	//  SIM->SOPT2 |= 0x01000000;   /* use MCGFLLCLK as timer counter clock */
	TPM1->SC = 0;               /* disable timer */
	TPM1->CONTROLS[1].CnSC = 0x20|0x08;   /* edge-aligned, pulse high MSB:MSA=10, ELSB:ELSA=10*/
	TPM1->MOD = mod;            /* Set up modulo register for 42.6 us period or 23.3 kHz rate */
	TPM1->CONTROLS[1].CnV = mod/2;  /* Set up default channel value for 50% dutycycle */
	TPM1->SC |= 0x80;           /* clear TOF */
	TPM1->SC |= 0x40;           /* enable timeout interrupt */
	//*************************PRE-Scaler settings *********************************************
	TPM1->SC |= 0x0B;           /* enable timer with prescaler /8 For DC motor and Buzzer*/
	//	TPM2->SC |= 0x0C;           /* enable timer with prescaler /16 for SERVO*/
	//******************************************************************************************
	NVIC_EnableIRQ(TPM0_IRQn); //enable TPM0 interrupt
	NVIC_EnableIRQ(TPM1_IRQn); //enable TPM1 interrupt
	NVIC_EnableIRQ(TPM2_IRQn); //enable TPM2 interrupt /* enable Timer2 interrupt in NVIC */

}

void ADC0_init(void)
{
	uint16_t calibration;

	SIM->SCGC5 |= 0x2000;       /* clock to PORTE */

	PORTE->PCR[22] = 0;         /* Pot PTE22 analog input */
	PORTE->PCR[20] = 0;         /* LDR PTE20 analog input */

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

void TPM0_IRQHandler(void) {
	NVIC_DisableIRQ(TPM2_IRQn);
	NVIC_DisableIRQ(TPM1_IRQn);
	ADC0->SC1[0] = ldr_pot;           		/* start conversion on channel 0 */
	while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
	result = ADC0->R[0];        /* read conversion result and clear COCO flag */
	/* 3. ------ PWM Generation for Servo---Set prescaler /16--------------*/
	TPM0->MOD = 60000;
	TPM0->CONTROLS[1].CnV = 1500 + result*3/2;  /* Set up channel value 50% Duty cycle*/
	TPM0->SC |= 0x80;           /* clear TOF */
	PORTD->ISFR = 0x10; /* clear interrupt flag */
	if (strcmp(prevKeypadKeys,"#3")==0) {
		for(int i = servoMin; i < servoMax; i += servoScanSpeed) {  // 2.2% to 12.2%
			TPM0->CONTROLS[1].CnV = i;
			calcAndDisplServoAngle(i);
		}
		for(int i = servoMax; i > servoMin; i -= servoScanSpeed) {  // 12.2% to 2.2%
			TPM0->CONTROLS[1].CnV = i;
			calcAndDisplServoAngle(i);
		}
	} else {
		TPM0->CONTROLS[1].CnV = servoMin/*1500, 1380*/ + result*(servoMax-servoMin)/4095/*3/2*/;
		calcAndDisplServoAngle(TPM0->CONTROLS[1].CnV);
	}

	PORTD->ISFR = 0x10; /* clear interrupt flag */
	//    delayMs(30);
	TPM0->SC |= 0x80; /* clear TOF */
	NVIC_EnableIRQ(TPM2_IRQn);
	NVIC_EnableIRQ(TPM1_IRQn);

}
void TPM1_IRQHandler(void) {
	NVIC_DisableIRQ(TPM0_IRQn);
	NVIC_DisableIRQ(TPM2_IRQn);
	/* 1.-----Frequency generation from 100 to 1000 Hz, 50% Duty cycle------*/
	ADC0->SC1[0] = ldr_pot;           		/* start conversion on channel 0 */
	while(!(ADC0->SC1[0] & 0x80)) { } 	/* wait for conversion complete */
	result = ADC0->R[0];        		/* read conversion result and clear COCO flag */
	TPM1->MOD = mod*2;
	TPM1->CONTROLS[1].CnV = result;
	TPM1->SC |= 0x80;           		/* clear TOF */

	NVIC_EnableIRQ(TPM0_IRQn);  /* enable Timer2 interrupt in NVIC */
	NVIC_EnableIRQ(TPM2_IRQn);
}
void TPM2_IRQHandler(void) {
	NVIC_DisableIRQ(TPM0_IRQn);
	NVIC_DisableIRQ(TPM1_IRQn);
	/* 1.-----Frequency generation from 100 to 1000 Hz, 50% Duty cycle------*/
	ADC0->SC1[0] = ldr_pot;           		/* start conversion on channel 0 */
	while(!(ADC0->SC1[0] & 0x80)) { } 	/* wait for conversion complete */
	result = ADC0->R[0];        		/* read conversion result and clear COCO flag */
	TPM2->MOD = 2400 + result*(12000-2400)/4095; //2350 + result*2.36; //3900 + result*2;
	TPM2->CONTROLS[1].CnV = TPM2->MOD/2; /* Set up channel value ?% Duty cycle*/
	TPM2->SC |= 0x80;           		/* clear TOF */

	NVIC_EnableIRQ(TPM0_IRQn);  /* enable Timer2 interrupt in NVIC */
	NVIC_EnableIRQ(TPM1_IRQn);
}



void calcAndDisplServoAngle(int i)
{
	int servoAngle;
	servoAngle = (i - servoMin) * 180 / (servoMax - servoMin) - 90;
	LCD_command(0xC0);
	LCD_data((servoAngle < 0 ? '-' : '+'));
	LCD_command(0xC1);
	LCD_data(abs(servoAngle) / 10 + 0x30);
	LCD_command(0xC2);
	LCD_data(abs(servoAngle) % 10 + 0x30);
	LCD_command(0xC0);
}

void setServoPositionToAngle(int servoAngle) {
	int i = (servoAngle + 90) * (servoMax - servoMin) / 180 + servoMin;
	delayMs(5); TPM0->CONTROLS[1].CnV = i; delayMs(5);
	LCD_command(0xC0);
	LCD_data((servoAngle < 0 ? '-' : '+'));
	LCD_command(0xC1);
	LCD_data(abs(servoAngle) / 10 + 0x30);
	LCD_command(0xC2);
	LCD_data(abs(servoAngle) % 10 + 0x30);
}
