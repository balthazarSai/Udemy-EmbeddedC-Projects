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

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define IRQNO_TIMER2 28
#define IRQNO_I2C1 31

uint32_t *pNVIC_IPRBase = (uint32_t*)0xE000E400;
uint32_t *pNVIC_ISERBase = (uint32_t*)0xE000E100;
uint32_t *pNVIC_ISPRBase = (uint32_t*)0xE000E200;

void conf_prio_irq(uint8_t irq_no,uint8_t prio){
	//Find the IPRx
	uint8_t iprx = irq_no/4;
	uint32_t *ipr = pNVIC_IPRBase + iprx;

	// Position in IPRx
	uint8_t pos = (irq_no%4)*8;

	// Confiigure the priority
	*ipr &= ~(0xFF << pos);
	*ipr |= (prio << pos);

}

int main(void)
{
	// Configure priorities
	conf_prio_irq(IRQNO_TIMER2,0x80);
	conf_prio_irq(IRQNO_I2C1,0x80);

	//Set the interrupt pending bit
	*pNVIC_ISPRBase |= (1 << IRQNO_TIMER2);

	//Enable IRQs in NVIC
	*pNVIC_ISERBase |= (1 << IRQNO_I2C1);
	*pNVIC_ISERBase |= (1 << IRQNO_TIMER2);

}

void TIM2_IRQHandler(void){
	printf("[TIM2_IRQHandler]\n");
	*pNVIC_ISPRBase |= (1 << IRQNO_I2C1);
}

void I2C1_EV_IRQHandler(void){
	printf("[I2C1_EV_IRQHandler]\n");
}

