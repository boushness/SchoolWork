// Riley Ruckman
// TCES 460, Wi21
// Lab 10 - Part a

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
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

//Create definitions for PORTE registers
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_LOCK_R       (*((volatile unsigned long *)0x40024520))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
	
//Create definitions for UART5 registers
#define SYSCTL_RCGCUART_R       (*((volatile unsigned long *)0x400FE618))
#define UART5_IBRD_R            (*((volatile unsigned long *)0x40011024))
#define UART5_FBRD_R            (*((volatile unsigned long *)0x40011028))
#define UART5_CTL_R             (*((volatile unsigned long *)0x40011030))
#define UART5_LCRH_R            (*((volatile unsigned long *)0x4001102C))
#define UART5_DR_R              (*((volatile unsigned long *)0x40011000))
#define UART5_FR_R              (*((volatile unsigned long *)0x40011018))
#define UART5_CC_R              (*((volatile unsigned long *)0x40011FC8))

//Create definitions for timer0 registers
#define TIMER0_CFG_R            (*((volatile unsigned long *)0x40030000))
#define TIMER0_TAMR_R           (*((volatile unsigned long *)0x40030004))
#define TIMER0_CTL_R            (*((volatile unsigned long *)0x4003000C))
#define TIMER0_RIS_R            (*((volatile unsigned long *)0x4003001C))
#define TIMER0_ICR_R            (*((volatile unsigned long *)0x40030024))
#define TIMER0_TAILR_R          (*((volatile unsigned long *)0x40030028))
#define TIMER0_TAPR_R           (*((volatile unsigned long *)0x40030038)) 
#define SYSCTL_RCGCTIMER_R      (*((volatile unsigned long *)0x400FE604))
	
// Function Prototypes
void timer0A_delayMs(int ttime);
void timer0_InIt(void);
void PortF_Init(void);
void HC05_Init(void);
char BLT_Read(void);
void BLT_Write(unsigned char data);
void BLT_Write_Str(char *s);

int main(void)
{
		// Initialize PORTF and UART5 ports/features
		PortF_Init();
		HC05_Init();
	
    while(1)
    {
			// Reads new data from Rx FIFO
			char c = BLT_Read();
			
			// If 'A' is received, a message is sent back and the onboard LED blinks RED twice at 1 Hz.
			if(c == 'A') {
				BLT_Write_Str("Hello World!! RED LED ON\n");
				for (int i = 0; i < 2; i++) {
					GPIO_PORTF_DATA_R = 0x02;
					timer0A_delayMs(1000);
					GPIO_PORTF_DATA_R = 0x00;
					timer0A_delayMs(1000);
				}
			// If 'B' is received, a message is sent back and the onboard LED blinks BLUE twice at 1 Hz.
			} else if(c == 'B') {
				BLT_Write_Str("Hello World!! BLUE LED ON\n");
				for (int i = 0; i < 2; i++) {
					GPIO_PORTF_DATA_R = 0x04;
					timer0A_delayMs(1000);
					GPIO_PORTF_DATA_R = 0x00;
					timer0A_delayMs(1000);
				}
			// If 'C' is received, a message is sent back and the onboard LED blinks RED-BLUE-GREEN at 1 Hz.
			} else if(c == 'C') {
				BLT_Write_Str("BYE World!! RGB LEDs ON\n");
				for (int i = 0; i < 3; i++) {
					// Since RED, BLUE, and GREEN are 0x2, 0x4, and 0x8, respectively, shifting
					// 2 by i will give the correct values for a RED-BLUE-GREEN sequence./
					GPIO_PORTF_DATA_R = 2 << i; 
					timer0A_delayMs(1000);
					GPIO_PORTF_DATA_R = 0x00;
					timer0A_delayMs(1000);
				}
			}
    }
}

//Initializes timer0
//Used for delay
void timer0_InIt(void) {
	
	SYSCTL_RCGCTIMER_R |= 0x01;   	/* enable clock to Timer0 */

	TIMER0_CTL_R = 0x00;          	/* disable Timer before initialization */
	TIMER0_CFG_R = 0x04;         		/* 16-bit option */
	TIMER0_TAMR_R = 0x02;        		/* periodic mode and down-counter */
	TIMER0_TAILR_R = 50000 - 1;  		/* Timer A interval load value register */
	TIMER0_ICR_R = 0x01;          	/* clear the TimerA timeout flag*/
	TIMER0_CTL_R |= 0x01;        		/* enable Timer A after initialization */
	TIMER0_TAPR_R = 0; 							// Prescalar value.. Can extend the cycle time max 255 times
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
	timer0_InIt();
	int i;

	for(i = 0; i < ttime; i++) { 
		while ((TIMER0_RIS_R & 0x01) == 0);      /* wait for TimerA timeout flag */
		TIMER0_ICR_R = 0x01;      /* clear the TimerA timeout flag */
	}
}
