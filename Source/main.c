#include <stdio.h>
#include<stdint.h>
#include <uart_rx.h>
#include<stm32f411xe.h>
#include <uart_rx.h>
#define GPIOAEN			(1U<<0)
#define PIN5			(1U<<5)
#define LED				PIN5
#define SR_RXNE			(1U<<5)
void USART2_IRQHandler(void);
static void dma1_callback(void);
void DMA1_Stream6_IRQHandler(void);

int main(void)
{
	RCC->AHB1ENR|=(1U<<0);
	GPIOA->MODER|=(1U<<10);
	GPIOA->MODER&=~(1U<<11);
	//uart2_rx_interrupt_init();
	char message[31]="Hello I'm Embedded Developer";
	uart2_txrx_init();
	dma1_stream6_init((uint32_t)message,(uint32_t)&USART2->DR,31);
	while(1)
	{

	}
}

static void dma1_callback(void)
{
	GPIOA->ODR|=LED;

}

void DMA1_Stream6_IRQHandler(void)
{
	/*Check for transfer complete interrupt*/
	if((DMA1->HISR) & HISR_TCIF6)
	{
		/*Clear flag*/
		DMA1->HIFCR|=HIFCR_CTCIF6;
		/*Do something*/
		dma1_callback();
	}

}
