// Allysen Arntsen, Riley Ruckman, Travis Shields
// TCES430, Au20
// Project

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create definition for PORT B registers
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// Create definitions for Port E registers
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))

// Create definitions for Port D registers  // Keypad ROW Pins as output
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *)0x40007520))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))

// Create definitions for Port A registers  // Keypad Column Pins as input
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
	
#define GPIO_PORTA_IS_R         (*((volatile unsigned long *)0x40004404))
#define GPIO_PORTA_IBE_R        (*((volatile unsigned long *)0x40004408))
#define GPIO_PORTA_IEV_R        (*((volatile unsigned long *)0x4000440C))
#define GPIO_PORTA_IM_R         (*((volatile unsigned long *)0x40004410))
#define GPIO_PORTA_ICR_R        (*((volatile unsigned long *)0x4000441C))
#define NVIC_PRI0_R             (*((volatile unsigned long *)0xE000E400))
#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Global variables
static int numbers[16] = {0xC0,0xF9,0xA4,0xB0,0x99, // Each value turns on bits needed
0x92,0x82,0xF8,0x80,0x90, 
0x88, 0x80, 0xC6, 0xC0, 0x86, 0x8E}; // to show numbers in display

static int letters[2] = {0x06,0x2F}; // Displays "E" and "r" for "Err" message

static int digit1, digit2, digit3, digit4; // Number to be displayed in each digit

static unsigned int key;	// key # pressed
static unsigned int num1 = 0, num2 = 0, operation, decimalsShow = 0;	// track operands 1 & 2, operation to be performed, and if decimals needed
static unsigned int numberSelect = 1;	// which number (operand 1, operand 2, or result) is being shown
static double result = 0.0, decimals = 0.0; // result and decimals of result (Used for DIV operation)

// const unsigned char keymap[4][4];
static int keymap[4][4] = {
{ 1, 2, 3, 10},			// 1, 2, 3, ADD
{ 4, 5, 6, 11},			// 4, 5, 6, SUB
{ 7, 8, 9, 12},			// 7, 8, 9, MULT
{ 14, 0, 15, 13},		// backspace, 0, enter/=, DIV
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//		Function Prototypes		//
void PortAD_Init(void); 												// PORTA: Keypad column
																								// PORTD: keypad row
void PortBE_Init(void); 												// PORT B: 7-SED a, b, c, d, e, f, g, LED selection
																								// PORT E: Select Digit 1, 2, 3, 4 (L-R)
void Delay(void);																// Creates 0.1ms delay
void Display(int digit, int number);						// Takes digit and number for LED display
void DisplayError(int digit, int letterIndex); 	// Only for displaying 'Err' letters on display
void DisplayDecimal(int digit, int number);		 	// Display() but can show decimal point
void NumSplit(int counted);										 	// Splits number into 4 digits								

// Interrupt Functions
void DisableInterrupts(void);
void EnableInterrupts(void);
void WaitForInterrupt(void);
void GPIOA_Handler(void);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PortAD_Init(void){
SYSCTL_RCGC2_R |= 0x00000009; // clk for A and D
// Initialize PORTD as Row output
	GPIO_PORTD_LOCK_R = 0x4C4F434B;   // Unlock PortD
  GPIO_PORTD_CR_R = 0xCC;           // Allow changes to PD7, PD6, PD3, PD2    
  GPIO_PORTD_AMSEL_R = 0x00;        // Disable analog function
  GPIO_PORTD_PCTL_R = 0x00000000;   // GPIO clear bit PCTL  
  GPIO_PORTD_DIR_R = 0xCC;          // PD7, PD6, PD3, PD2  output  
  GPIO_PORTD_AFSEL_R = 0x00;        // No alternate function
  GPIO_PORTD_PUR_R = 0x00;          // No Enable pullup resistor      
  GPIO_PORTD_DEN_R = 0xCC;          // Enable digital pins PD7, PD6, PD3, PD2 
	
// Initialize PORTA as column input & setup interrupts for inputs
	GPIO_PORTA_LOCK_R = 0x4C4F434B;   // Unlock PortA
  GPIO_PORTA_CR_R = 0xF0;           // Allow changes to PA7-PA4    
  GPIO_PORTA_AMSEL_R = 0x00;        // Disable analog function
  GPIO_PORTA_PCTL_R = 0x00000000;   // GPIO clear bit PCTL  
  GPIO_PORTA_DIR_R = 0x00;          // PA7-PA4 input  
  GPIO_PORTA_AFSEL_R = 0x00;        // No alternate function
  GPIO_PORTA_PUR_R = 0xF0;          // Enable pullup resistors on PA7-PA4      
  GPIO_PORTA_DEN_R = 0xF0;          // Enable digital pins PA7-PA4
	
	GPIO_PORTA_IS_R &= ~0xF0;       /*  PA7-PA4 is edge-sensitive */
	GPIO_PORTA_IBE_R &= ~0xF0;      /*  PA7-PA4 is not both edges */
	GPIO_PORTA_IEV_R &= ~0xF0;      /*  PA7-PA4 falling edge event */
	GPIO_PORTA_ICR_R = 0xF0;        /*  Clear flag4 */
	GPIO_PORTA_IM_R |= 0xF0;        /*  arm interrupt on PA7-PA4 */
	NVIC_PRI0_R = (NVIC_PRI0_R & 0xFFFFFF0F) | 0x000000A0; /*  priority 5 */
	NVIC_EN0_R = 0x00000001;        /*  Enable interrupt 30 in NVIC */
	
	EnableInterrupts();             /* Enable global Interrupt flag (I) */
}

// Subroutine to initialize ports B and E
void PortBE_Init(void){
  SYSCTL_RCGC2_R |= 0x00000002;     // Port B clock initialized
  GPIO_PORTB_CR_R = 0xFF;           // Allow changes to PB7-PB0      
  GPIO_PORTB_AMSEL_R = 0x00;        // Disable analog function
  GPIO_PORTB_PCTL_R = 0x00000000;   // GPIO clear bit PCTL  
  GPIO_PORTB_DIR_R = 0xFF;          // Set PB7-PB0 outputs  
  GPIO_PORTB_PUR_R = 0x00;          // Disable pullup resistors      
  GPIO_PORTB_DEN_R = 0xFF;          // 7) Enable digital pins PB7-PB0        

  SYSCTL_RCGC2_R |= 0x00000010;     // Port E clock initialized
  GPIO_PORTE_CR_R = 0x0F;           // Allow changes to PE4-0      
  GPIO_PORTE_AMSEL_R = 0x00;        // Disable analog function
  GPIO_PORTE_PCTL_R = 0x00000000;   // GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R = 0x0F;          // PE3-PE0 output  
  GPIO_PORTE_PUR_R = 0x00;          // Disable pullup resistors      
  GPIO_PORTE_DEN_R = 0x0F;          // Enable digital pins PE3-PE0
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////\

// Initializes ports and constantly displays an operand, the result, or an error message
int main(void){
  PortBE_Init();         // Initialize microcontroller ports
	PortAD_Init();

	while(1){
		GPIO_PORTD_DATA_R = 0x00;
		
		if (numberSelect == 1) {	// Selects first operand for displaying
			NumSplit(num1);
		} else if (numberSelect == 2) {		// Selects second operand for displaying
			NumSplit(num2);
		} else {							// display the result
			NumSplit((int)result);
			// Checks if the decimals need to be shown or not (for DIV operation with a non-zero remainder)
			if(decimalsShow == 1) NumSplit((int)decimals);
		}
		
		if(result < 9999) {			// check for too many digits error
			Display(1, digit4);		// digit4 displays first digit
			Delay();							// wait briefly
			Display(2, digit3);		// digit3 displays next digit
			Delay();				
			Display(4, digit2);		// digit2 displays third digit
			Delay();
			
			// check that operation is division, the decimal has not been shown yet, but the decimal part is non-zero
			if (operation == 13 && decimalsShow == 0 && (int)decimals != 0) {
				DisplayDecimal(8, digit1);	// digit1 displays final digit with a decimal point
			} else {
				Display(8,digit1);					// digit1 displays final digit as normal
			}
			Delay();
		} else {								// in case result is > 9999
			DisplayError(2, 0);		// digit 1 displays "E"
			Delay();							// wait
			DisplayError(4, 1);		// digit 2 displays "r"
			Delay();				
			DisplayError(8, 1);		// digit 3 displays "r"
			Delay();				
		}
	}
}

// Handler called when an interrupt occurs on PA7-PA4 on PORT A
void GPIOA_Handler(void)
{
    volatile int readback;
			
		result = 0;								// initialize result
		if(numberSelect == 3) {		// checks if the result has been displayed and if the decimals need to be shown (for DIV operation)
			if(operation == 13 && decimalsShow == 0 && (int)decimals != 0) {
				decimalsShow = 1; // Makes the decimals display and ignored key press
			} else {
				numberSelect = 1;	// Resets to first operand and other values for next calculation
				decimalsShow = 0;
				operation = 0;
				decimals = 0;
			}
		}
		
		// Variables for locating key press
		int row, column;
	
	// first check if any key has been pressed
		GPIO_PORTD_DATA_R = 0x00;
		column = GPIO_PORTA_DATA_R &0xF0;
		if(column != 0xF0){
			while (1){ // find out which row has been activated
				row = 0;
				GPIO_PORTD_DATA_R = 0xC8;
				Delay();
				column = GPIO_PORTA_DATA_R &0xF0;
				if(column != 0xF0) 
					{break;}

				row = 1;
				GPIO_PORTD_DATA_R = 0xC4;
				Delay();
				column = GPIO_PORTA_DATA_R &0xF0;
				if(column != 0xF0) 
					{break;}

				row = 2;
				GPIO_PORTD_DATA_R = 0x8C;
				Delay();
				column = GPIO_PORTA_DATA_R &0xF0;
				if(column != 0xF0) 
					{break;}

				row = 3;
				GPIO_PORTD_DATA_R = 0x04C;
				Delay();
				column = GPIO_PORTA_DATA_R &0xF0;
				if(column != 0xF0) 
					{break;}
				
				break;
			}
			
			if (column == 0xE0) key = keymap[row][0]; /* key in column 0 */
			if (column == 0xD0) key = keymap[row][1]; /* key in column 1 */
			if (column == 0xB0) key = keymap[row][2]; /* key in column 2 */
			if (column == 0x70) key = keymap[row][3]; /* key in column 3 */
		}
		
		// check if key entered was not a number
		if (key > 9 && key < 14) {
			// check that first number is entered. Then begin to display second and set operation to
			// the corresponding key # that is pressed
			if (numberSelect == 1) {
				numberSelect = 2;
				operation = key;
			}
		// if backspace was pressed, remove last digit from the corresponoding operand (via int division)
		} else if (key == 14) {
			if (numberSelect == 1) {
				num1 = (num1/10);
			} else if (numberSelect == 2) {
				num2 = (num2/10);
			}
		// if key pressed was a number, process it into corresponding operand value
		//
		} else if (key < 10) {
			if (numberSelect == 1) {
				num1 = ((num1*10) + key) % 10000;
			} else if (numberSelect == 2) {
				num2 = ((num2*10) + key) % 10000;
			}
		// if enter has been pressed and both digits are inputted, calculate result
		} else if (key == 15 && numberSelect == 2) {
				numberSelect = 3; // now showing result as it is calculated
				
				if(operation == 10) result = num1 + num2; // + | Addition
				if(operation == 11) result = num1 - num2; // - | Subtraction
				if(operation == 12) result = num1 * num2; // x | Multiplication
				if(operation == 13) {											// / | Division
					result = ((double)num1 / num2);						// Double division to get remainder
					decimals = 10000 * (double)(result - (int)result);	// Removes integers from result and moves 4 decimal places up 4 spaces
				}
				
				num1 = num2 = 0;	// reset operands
		}
		
		Delay();
		GPIO_PORTA_ICR_R = 0xF0;        /* clear PA7-PA4 flag */
    readback = GPIO_PORTA_ICR_R;    /* a read to force clearing of interrupt flag */
    readback = readback;
}


/*********** DisableInterrupts ***************
*
* disable interrupts
*
* inputs:  none
* outputs: none
*/

void DisableInterrupts(void)
{
    __asm ("    CPSID  I\n");
}

/*********** EnableInterrupts ***************
*
* emable interrupts
*
* inputs:  none
* outputs: none
*/

void EnableInterrupts(void)
{
    __asm  ("    CPSIE  I\n");
}

/*********** WaitForInterrupt ************************
*
* go to low power mode while waiting for the next interrupt
*
* inputs:  none
* outputs: none
*/

void WaitForInterrupt(void)
{
    __asm  ("    WFI\n");
//GPIOPortA_Handler();
}

// Creates 0.1ms delay
void Delay(void){
	unsigned long volatile time;
	time = (727240*200)/91000;  // 0.1 ms
		while(time){
			time--;
		}
}

// Takes digit and number for LED display
void Display(int digit, int number){
	//number1 = atoi(key);
	GPIO_PORTB_DATA_R = 0x00; // Turns off LEDs
	GPIO_PORTE_DATA_R = digit; // Selects digit
	GPIO_PORTB_DATA_R = numbers[number]; // Turns on number in selected digit
	Delay(); // Wait 0.1 ms
}

// Takes digit and number for LED display, while also displaying the digit's decimal point
void DisplayDecimal(int digit, int number){
	//number1 = atoi(key);
	GPIO_PORTB_DATA_R = 0x00; // Turns off LEDs
	GPIO_PORTE_DATA_R = digit; // Selects digit
	GPIO_PORTB_DATA_R = numbers[number] - 0x80; // Turns on number and decimal point in selected digit
	Delay(); // Wait 0.1 ms
}

// Takes digit and number for LED display
void DisplayError(int digit, int letterIndex){
	//number1 = atoi(key);
	GPIO_PORTB_DATA_R = 0x00; // Turns off LEDs
	GPIO_PORTE_DATA_R = digit; // Selects digit
	GPIO_PORTB_DATA_R = letters[letterIndex]; // Turns on number in selected digit
	Delay(); // Wait 0.1 ms
}

// Parses number into 4 digits
void NumSplit(int counted){
	digit1 = counted%10; //Copies value in counter, divides it by 10 and then keeps remainder
	counted /= 10; //Dividing value in counter by 10 shifts it by one decimal
	digit2 = counted%10;
	counted /= 10;
	digit3 = counted%10;
	counted /= 10;
	digit4 = counted%10; // digit1: holds 1000's digit, digit2: 100's digit, 
	counted /=10; // digit3: 10th digit, digit4: unit digit
}
