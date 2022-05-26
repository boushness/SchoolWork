// Riley Ruckman
// TCES 460, Wi21
// Lab 10 - Part b

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////

/*																																*/
/*															ADC																*/
/*																																*/

//Create definitions for ADC0 registers
#define SYSCTL_RCGCADC_R 		(*((volatile unsigned long *)0x400FE638))
#define ADC0_ACTSS_R 				(*((volatile unsigned long *)0x40038000))
#define ADC0_EMUX_R 				(*((volatile unsigned long *)0x40038014))
#define ADC0_SSMUX3_R 			(*((volatile unsigned long *)0x400380A0))
#define ADC0_SSCTL3_R 			(*((volatile unsigned long *)0x400380A4))
#define ADC0_PSSI_R 				(*((volatile unsigned long *)0x40038028))
#define ADC0_RIS_R 					(*((volatile unsigned long *)0x40038004))
#define ADC0_SSFIFO3_R 			(*((volatile unsigned long *)0x400380A8))
#define ADC0_ISC_R 					(*((volatile unsigned long *)0x4003800C))
#define ADC0_PC_R           (*((volatile unsigned long *)0x40038FC4))
	
#define ADC0_IM_R           (*((volatile unsigned long *)0x40038008))
#define NVIC_EN0_R          (*((volatile unsigned long *)0xE000E100))							
#define NVIC_PRI4_R         (*((volatile unsigned long *)0xE000E410))

//Create definitions for PORT D registers
#define SYSCTL_RCGC2_R 			(*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTD_DATA_R 	(*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R 		(*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R 	(*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_PUR_R 		(*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_DEN_R 		(*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_LOCK_R 	(*((volatile unsigned long *)0x40007520))
#define GPIO_PORTD_CR_R 		(*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_AMSEL_R 	(*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R 	(*((volatile unsigned long *)0x4000752C))
	
//Create definitions for Timer1 registers
#define TIMER1_CFG_R 				(*((volatile unsigned long *)0x40031000))
#define TIMER1_TAMR_R 			(*((volatile unsigned long *)0x40031004))
#define TIMER1_CTL_R 				(*((volatile unsigned long *)0x4003100C))
#define TIMER1_RIS_R 				(*((volatile unsigned long *)0x4003101C))
#define TIMER1_ICR_R 				(*((volatile unsigned long *)0x40031024))
#define TIMER1_TAILR_R 			(*((volatile unsigned long *)0x40031028))
#define TIMER1_TAPR_R 			(*((volatile unsigned long *)0x40031038))

////////////////////////////////////////////////////////////////////

/*																																*/
/*															UART															*/
/*																																*/

//Create definitions for UART5 registers
#define SYSCTL_RCGCUART_R       (*((volatile unsigned long *)0x400FE618))
#define UART5_IBRD_R            (*((volatile unsigned long *)0x40011024))
#define UART5_FBRD_R            (*((volatile unsigned long *)0x40011028))
#define UART5_CTL_R             (*((volatile unsigned long *)0x40011030))
#define UART5_LCRH_R            (*((volatile unsigned long *)0x4001102C))
#define UART5_DR_R              (*((volatile unsigned long *)0x40011000))
#define UART5_FR_R              (*((volatile unsigned long *)0x40011018))
#define UART5_CC_R              (*((volatile unsigned long *)0x40011FC8))

//Create definitions for Port E registers
#define GPIO_PORTE_DATA_R 	(*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R 		(*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_PUR_R 		(*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R 		(*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_CR_R 		(*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R 	(*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_AFSEL_R 	(*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PCTL_R 	(*((volatile unsigned long *)0x4002452C))

////////////////////////////////////////////////////////////////////

/*																																*/
/*															LEDs															*/
/*																																*/

//Create definitions of PORTF registers
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))

////////////////////////////////////////////////////////////////////

/*																																*/
/*												Normal-Use Timer												*/
/*																																*/

//Create definitions for Timer0 registers
#define TIMER0_CFG_R 				(*((volatile unsigned long *)0x40030000))
#define TIMER0_TAMR_R 			(*((volatile unsigned long *)0x40030004))
#define TIMER0_CTL_R 				(*((volatile unsigned long *)0x4003000C))
#define TIMER0_RIS_R 				(*((volatile unsigned long *)0x4003001C))
#define TIMER0_ICR_R 				(*((volatile unsigned long *)0x40030024))
#define TIMER0_TAILR_R 			(*((volatile unsigned long *)0x40030028))
#define TIMER0_TAPR_R 			(*((volatile unsigned long *)0x40030038))
#define SYSCTL_RCGCTIMER_R 	(*((volatile unsigned long *)0x400FE604))

////////////////////////////////////////////////////////////////////

/*																																*/
/*			Function Prototypes & Global Variable Initialization			*/
/*																																*/

void ADC_Init(void);
void timer0A_delayMs(int ttime);
void timer0_Init(void);
void ADC0SS3_Handler(void);
void PortF_Init(void);
void HC05_Init(void);
char BLT_Read(void);
void BLT_Write(unsigned char data);
void BLT_Write_Str(char *s);

static int temperature = 0;
static int oldTemperature;

////////////////////////////////////////////////////////////////////

int main(void){
	
	// Initialize necessary ports/modules
	ADC_Init();
	HC05_Init();
	PortF_Init();
	while(1){
		
		// Reads new data from Rx FIFO
		char c = BLT_Read();
		
		// If read data from UART is 'A'
		if(c == 'A') {
			// Converts temperature into str then writes it to the Tx FIFO
			char stemp[5];
			sprintf(stemp, "%d", temperature);
			BLT_Write_Str("Current Temperature is: ");
			BLT_Write_Str(stemp);
			
			// Calculates temperature difference between new and previous reading
			// and converts it into a str
			int tempDifference = temperature - oldTemperature;
			char stempDif[5];
			sprintf(stempDif, "%d", abs(tempDifference));	// Takes absolute value of difference for sending to user
			
			// Based off the temperature difference, an unique message will be sent
			if (tempDifference > 0) {
				BLT_Write_Str("\nTemperature increase: ");
				BLT_Write_Str(stempDif);
			} else if (tempDifference < 0) {
				BLT_Write_Str("\nTemperature decrease: ");
				BLT_Write_Str(stempDif);
			} else {
				BLT_Write_Str("\nTemperature unchanged");
			}
			BLT_Write_Str("\n");
		}
	}
}

// Interrupt Handler for ADC0SS3 interrupt
void ADC0SS3_Handler(void) {

	oldTemperature = temperature;
	// temperature = ((ADC0_SSFIFO3_R & 0xFFF) - 500)/10;
	// Converts 12-bit conversion result in SS3's FIFO to Celsius, and then Fahrenheit
	temperature = (int)((((((ADC0_SSFIFO3_R & 0xFFF) * (3.3/4096.0) * 1000.0) - 500) / 10) * (9.0/5.0)) + 32);
		
	// If the temperature difference is at most -2, then the LED blinks RED twice at 1 Hz.
	// This is to simulate a signal being sent to a heater to turn on
	if ((temperature - oldTemperature) <= -2) {
			for (int i = 0; i < 2; i++) {
			GPIO_PORTF_DATA_R = 0x02;
			timer0A_delayMs(1000);
			GPIO_PORTF_DATA_R = 0x00;
			timer0A_delayMs(1000);
		}
	// If the temperature difference is at least 2, then the LED blinks GREEN twice at 1 Hz.
	// This is to simulate a signal being sent to a cooler to turn on
	} else if ((temperature - oldTemperature) >= 2) {
		for (int i = 0; i < 2; i++) {
			GPIO_PORTF_DATA_R = 0x08;
			timer0A_delayMs(1000);
			GPIO_PORTF_DATA_R = 0x00;
			timer0A_delayMs(1000);
		}
	}
	
	// Clears flag that were set due to ADC0 conversion 
	// completion and TIMER0 timeout condition, respectively
	ADC0_ISC_R |= 0x8; /* clear completion flag */
	TIMER1_ICR_R = 0x01; /* clear the TimerA timeout flag */
}

/* multiple of millisecond delay using periodic mode */
void timer0_Init(void){
	
	SYSCTL_RCGCTIMER_R |= 0x01; /* enable clock to Timer0 */
	TIMER0_CTL_R = 0x00; /* disable Timer before initialization */
	TIMER0_CFG_R = 0x04; /* 16-bit option */
	TIMER0_TAMR_R = 0x02; /* periodic mode and down-counter */
	TIMER0_TAILR_R = 50000 - 1; /* Timer A interval load value register */
	TIMER0_ICR_R = 0x1; /* clear the TimerA timeout flag*/
	TIMER0_CTL_R |= 0x01; /* enable Timer A after initialization */
	TIMER0_TAPR_R = 0; // Prescalar value.. Can extend the cycle time max 256 times
}

// Subroutine to initialize Port F
void PortF_Init(void) {
	
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // F clock
  delay = SYSCTL_RCGC2_R;           // reading register adds a delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // unlock PortF  
  GPIO_PORTF_CR_R = 0x0E;           // allow changes to PF3-PF1       
  GPIO_PORTF_AMSEL_R = 0x00;        // disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // no alternate function
  GPIO_PORTF_PUR_R = 0x00;          // disable pull-up resistors       
  GPIO_PORTF_DEN_R = 0x0E;          // enable digital pins PF3-PF1  
}

// Initialize ADC0 module and PORTD for ADC use
void ADC_Init(void){
	
	SYSCTL_RCGC2_R |= 0x08; // Enable clock PORTD
	SYSCTL_RCGCADC_R |= 0x01; // Enable clock ADC0
	
	/* initialize PD1 for AIN6 input */
	GPIO_PORTD_AFSEL_R |= 0x2; /* enable alternate function */
	GPIO_PORTD_DEN_R &= ~0x2; /* disable digital function */
	GPIO_PORTD_AMSEL_R |= 0x2; /* enable analog function */
	
	/* initialize ADC0 */
	ADC0_ACTSS_R &= ~0x8; /* disable SS3 during configuration */
	ADC0_EMUX_R = 0x5000; /* timer trigger conversion */
	ADC0_SSMUX3_R = 0x6; /* get input from channel 6 */
	ADC0_SSCTL3_R |= 0x6; /* take one sample at a time, set flag at 1st sample */
	ADC0_PC_R = 0x00;			/* sets sampling rate to 125 kHz */
	
	ADC0_IM_R |= 0x08; /* enables interrupt mask for SS3 in ADC0 */
	NVIC_EN0_R = 0x00020000; /*  Enable interrupt 17 in NVIC */				
	NVIC_PRI4_R = (NVIC_PRI4_R & 0xFFFF0FFF) | 0x00004000; /*  priority 2 */
	ADC0_ACTSS_R |= 0x8; /* enable ADC0 sequencer 3 */
	
	ADC0_PSSI_R = 0x01;	// Start conversion
	
	// Initialize Timer1
	SYSCTL_RCGCTIMER_R |= 0x02;     /* enable clock to Timer1 */
 
	TIMER1_CTL_R = 0x00;            /* disable Timer before initialization */
	TIMER1_CFG_R = 0x00;         		/* 32-bit option */
	TIMER1_TAMR_R = 0x02;        		/* periodic mode and down-counter */
	TIMER1_TAILR_R = 500000000 - 1; /* Timer A interval load value register */
	TIMER1_ICR_R = 0x1;          		/* clear the Timer A timeout flag*/
	TIMER1_TAPR_R = 0; 							// Prescalar value.. Can extend the cycle time max 255 times

	TIMER1_CTL_R |= 0x21;        		/* enable Timer A after initialization */
}

// Subroutine to initialize UART5
void HC05_Init(void) {
	
	SYSCTL_RCGC2_R |= 0x10;	// Enable clock for PORTE
	SYSCTL_RCGCUART_R |= 0x20; //Enable clock for UART5
	
	timer0A_delayMs(1);
	
	GPIO_PORTE_AMSEL_R = 0x00;	// Disable analog function
	GPIO_PORTE_DEN_R = 0x30;	// PE4, PE5 are digital pins
	GPIO_PORTE_AFSEL_R = 0x30;	// Enable alternate functions for PE4, PE5
	GPIO_PORTE_PCTL_R = 0x00110000;	// PE4 = UART5Rx, PE5 = UART5Tx

	UART5_CTL_R = 0x00;	//Disable UART5 module
	UART5_IBRD_R = 325;	// For 9600 baud rate with f = 50MHz, integer = 325
	UART5_FBRD_R = 33;	// For 9600 baud rate with f = 50MHz, fraction = 33
	UART5_CC_R = 0x00;	// Select system clock
	UART5_LCRH_R = 0x60;	// 8-bit, no parity, 1 stop bit, no FIFO
	UART5_CTL_R = 0x301;	// Enable Rx, Tx, and UART5
}

// Receives and reads char from Rx FIFO
char BLT_Read(void){
	
	char data;
	while((UART5_FR_R & 0x10) != 0);	// Wait until Rx buffer is not full
	data = UART5_DR_R;	// Copy Rx data to local data variable
	return (unsigned char) data;	// Return data
}

// Writes a char to Tx FIFO to send
void BLT_Write(unsigned char data){
	
	while((UART5_FR_R & 0x20) != 0);	// Wait until Tx buffer is not full
	UART5_DR_R = data;	// Copy data into Tx
}

// Writes a string to Tx FIFO by repeatedly calling BLT_Write for each char in the string
void BLT_Write_Str(char* s) {
		
	// Writes string's contents to Tx buffer, one-by-one
	while(*s) {
		BLT_Write(*(s++));
	}
}

/* multiple of millisecond delay using periodic mode */
void timer0A_delayMs(int ttime)
{
	timer0_Init();
	int i;

	for(i = 0; i < ttime; i++) { 
		while ((TIMER0_RIS_R & 0x01) == 0);      /* wait for TimerA timeout flag */
		TIMER0_ICR_R = 0x01;      /* clear the TimerA timeout flag */
	}
}
