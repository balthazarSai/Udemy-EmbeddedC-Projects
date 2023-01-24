#include<stdint.h>
#include "led.h"



void delay(uint32_t count)
{
  for(uint32_t i = 0 ; i < count ; i++);
}

void led_init_all(void)
{

	uint32_t *pRCC_AHB1ENR = (uint32_t*)0x40023830;  //0x40023800
	uint32_t *pGPIOAMODER = (uint32_t*)0x40020000; //0x40020C00


	*pRCC_AHB1ENR |= ( 1 << 0); //ENABLE GPIOA
	//configure LED_GREEN
	*pGPIOAMODER |= ( 1 << (2 * LED_GREEN));
	*pGPIOAMODER |= ( 1 << (2 * LED_YELLOW));
	*pGPIOAMODER |= ( 1 << (2 * LED_RED));
	*pGPIOAMODER |= ( 1 << (2 * LED_BLUE));

#if 0
	//configure the outputtype
	*pGpioOpTypeReg |= ( 1 << (2 * LED_GREEN));
	*pGpioOpTypeReg |= ( 1 << (2 * LED_ORANGE));
	*pGpioOpTypeReg |= ( 1 << (2 * LED_RED));
	*pGpioOpTypeReg |= ( 1 << (2 * LED_BLUE));
#endif

    led_off(LED_GREEN);
    led_off(LED_YELLOW);
    led_off(LED_RED);
    led_off(LED_BLUE);



}

void led_on(uint8_t led_no)
{
  uint32_t *pGPIOADATAREG = (uint32_t*)0x40020014;
  *pGPIOADATAREG |= ( 1 << led_no);

}

void led_off(uint8_t led_no)
{
	  uint32_t *pGPIOADATAREG = (uint32_t*)0x40020014;
	  *pGPIOADATAREG &= ~( 1 << led_no);

}
