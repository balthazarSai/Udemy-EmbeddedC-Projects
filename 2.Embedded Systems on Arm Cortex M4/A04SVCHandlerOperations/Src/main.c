/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

int32_t add_numbers(int32_t x,int32_t y);
int32_t sub_numbers(int32_t x,int32_t y);
int32_t mul_numbers(int32_t x,int32_t y);
int32_t div_numbers(int32_t x,int32_t y);

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void){
	int32_t res;
	res = add_numbers(40,-90);
	printf("Result: %d\n",res);
	res = sub_numbers(40,-90);
	printf("Result: %d\n",res);
	res = mul_numbers(374,890);
	printf("Result: %d\n",res);
	res = div_numbers(67,-3);
	printf("Result: %d\n",res);
	for(;;);
}
__attribute ((naked))void SVC_Handler(void){
	__asm("MRS r0,MSP");
	__asm("B SVC_Handler_c");
}

void SVC_Handler_c(uint32_t *pStackBase){
	uint8_t *pMSR_PC = (uint8_t*) pStackBase[6];
	int32_t arg0,arg1,res;

	pMSR_PC-=2;
	uint8_t svc_number = *pMSR_PC;

	printf("SVC Number: %d\n",svc_number);

	arg0 = pStackBase[0];
	arg1 = pStackBase[1];


	switch(svc_number){
	case 36:
		res = arg0+arg1;
		break;
	case 37:
		res = arg0-arg1;
		break;
	case 38:
		res = arg0*arg1;
		break;
	case 39:
		res = arg0/arg1;
		break;
	default:
		printf("Unknown SVC\n");
		break;
	}
	pStackBase[0] = res;

}

int32_t add_numbers(int32_t x,int32_t y){
	int32_t result;
	__asm volatile("SVC #36");
	__asm volatile("MOV %0,r0":"=r"(result)::);
	return result;
}
int32_t sub_numbers(int32_t x,int32_t y){
	int32_t result;
	__asm volatile("SVC #37");
	__asm volatile("MOV %0,r0":"=r"(result)::);
	return result;
}
int32_t mul_numbers(int32_t x,int32_t y){
	int32_t result;
	__asm volatile("SVC #38");
	__asm volatile("MOV %0,r0":"=r"(result)::);
	return result;
}
int32_t div_numbers(int32_t x,int32_t y){
	int32_t result;
	__asm volatile("SVC #39");
	__asm volatile("MOV %0,r0":"=r"(result)::);
	return result;
}
