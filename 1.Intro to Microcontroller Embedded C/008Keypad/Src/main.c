#include<stdint.h>
#include<stdio.h>

void delay(void)
{
	for(uint32_t i =0 ; i < 300000 ; i++);

}

int main(void)
{
	//peripheral register addresses
	uint32_t volatile *const pGPIOCModeReg  =  (uint32_t*)(0x40020800);
	uint32_t volatile *const pInPutDataReg  =  (uint32_t*)(0x40020800+0x10);
	uint32_t volatile *const pOutPutDataReg =  (uint32_t*)(0x40020800+0x14);
	uint32_t volatile *const pClockCtrlReg  =  (uint32_t*)(0x40023800+0x30);
	uint32_t volatile *const pPulluPCownReg =  (uint32_t*)(0x40020800 + 0x0C);
	uint32_t *AHB1ENR = (uint32_t*)0x40023830;
	uint32_t *GPIOAMODE = (uint32_t*)0x40020000;
	uint32_t *GPIOAOUTD = (uint32_t*)0x40020014;

	//Enable GPIO Clock for GPIOA
	*AHB1ENR = *AHB1ENR | 0x01;

	//Mask value for clearing = 0xfffff3ff or ~(3 << 10)
	//*GPIOAMODE &= 0xfffff3ff;
	*GPIOAMODE &= ~(3 << 10);

	//Mask value for setting = 0x00000400 or (1 << 10)
	//*GPIOAMODE |= 0x00000400;
	*GPIOAMODE |= (1 << 10);

     //1.Enable the peripheral clock of GPIOC peripheral
	*pClockCtrlReg |= ( 1 << 2);


    // 2.configure PC0,PC1,PC2,PC3 as output (rows)
	*pGPIOCModeReg &= ~(0xFF); //clear with ~11111111
	*pGPIOCModeReg |= 0x55;   //set with 01010101


	// 3. configure PC8 , PC9, PC10, PC11 as input (columns)
    *pGPIOCModeReg &= ~(0xFF << 16); // with ~11111111

	// 4.Enable internal pull-up resistors for PC8 PC9 PC10 PC11
    *pPulluPCownReg &= ~(0xFF << 16); //clear with ~11111111
    *pPulluPCownReg |=  (0x55 << 16); //set with 01010101

while(1){
    //make all rows HIGH
    *pOutPutDataReg |= 0x0f; // set with 1111

    //make R1 LOW(PC0)
    *pOutPutDataReg &= ~( 1 << 0);

    //scan the columns
    //check C1(PC8) low or high
    if(!(*pInPutDataReg & ( 1 << 8))){
    	//key is pressed
    	delay();
    	printf("1\n");
    	fflush(stdout);
    	*GPIOAOUTD ^= (1 << 5);
    }

    //check C2(PC9) low or high
    if(!(*pInPutDataReg & ( 1 << 9))){
    	//key is pressed
    	delay();
    	printf("2\n");
    	*GPIOAOUTD ^= (1 << 5);
    }

    //check C3(PC10) low or high
    if(!(*pInPutDataReg & ( 1 << 10))){
    	//key is pressed
    	delay();
    	printf("3\n");
    	*GPIOAOUTD ^= (1 << 5);
    }

    //check C4(PC11) low or high
    if(!(*pInPutDataReg & ( 1 << 11))){
    	//key is pressed
    	delay();
    	printf("A\n");
    }


    //make all rows HIGH
     *pOutPutDataReg |= 0x0f;
    //make R2 LOW(PC1)
    *pOutPutDataReg &= ~( 1 << 1);

    //scan the columns
    //check C1(PC8) low or high
    if(!(*pInPutDataReg & ( 1 << 8))){
    	//key is pressed
    	delay();
    	printf("4\n");
    }

    //check C2(PC9) low or high
    if(!(*pInPutDataReg & ( 1 << 9))){
    	//key is pressed
    	delay();
    	printf("5\n");
    }

    //check C3(PC10) low or high
    if(!(*pInPutDataReg & ( 1 << 10))){
    	//key is pressed
    	delay();
    	printf("6\n");
    }

    //check C4(PC11) low or high
    if(!(*pInPutDataReg & ( 1 << 11))){
    	//key is pressed
    	delay();
    	printf("B\n");
    }

    //make all rows HIGH
     *pOutPutDataReg |= 0x0f;
    //make R3 LOW(PC2)
    *pOutPutDataReg &= ~( 1 << 2);

    //scan the columns
    //check C1(PC8) low or high
    if(!(*pInPutDataReg & ( 1 << 8))){
    	//key is pressed
    	delay();
    	printf("7\n");
    }

    //check C2(PC9) low or high
    if(!(*pInPutDataReg & ( 1 << 9))){
    	//key is pressed
    	delay();
    	printf("8\n");
    }

    //check C3(PC10) low or high
    if(!(*pInPutDataReg & ( 1 << 10))){
    	//key is pressed
    	delay();
    	printf("9\n");
    }

    //check C4(PC11) low or high
    if(!(*pInPutDataReg & ( 1 << 11))){
    	//key is pressed
    	delay();
    	printf("C\n");
    }

    //make all rows HIGH
     *pOutPutDataReg |= 0x0f;
    //make R4 LOW(PC2)
    *pOutPutDataReg &= ~( 1 << 3);

    //scan the columns
    //check C1(PC8) low or high
    if(!(*pInPutDataReg & ( 1 << 8))){
    	//key is pressed
    	delay();
    	printf("*\n");
    }

    //check C2(PC9) low or high
    if(!(*pInPutDataReg & ( 1 << 9))){
    	//key is pressed
    	delay();
    	printf("0\n");
    }

    //check C3(PC10) low or high
    if(!(*pInPutDataReg & ( 1 << 10))){
    	//key is pressed
    	delay();
    	printf("#\n");
    }

    //check C4(PC11) low or high
    if(!(*pInPutDataReg & ( 1 << 11))){
    	//key is pressed
    	delay();
    	printf("D\n");
    }

}//while end

}
