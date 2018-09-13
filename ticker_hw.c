/**
 * @file      ticker_hw.c
 * @author    Atakan S.
 * @date      01/01/2018
 * @version   1.1
 * @brief     Hardware implementation for ticker.
 *
 * @copyright Copyright (c) 2018 Atakan SARIOGLU ~ www.atakansarioglu.com
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 */

#include "porty.h"
#ifdef _H_TICKER // Exclude from compile when not included in projech.h

#include "ticker_hw.h"

// Ticker uses ARM SysTick timer hardware.
#if defined(TICKERHW_USE_ARMSYSTICK)

/**
 * @brief Ticker hardware init.
 */
void TickerHwInit(void) {
	// Configure ARM Cortex-M built-in SysTick.
	SysTick_Config(TICKER_PERIOD_TICKS);
}

/**
 * @brief SysTick IRQ handler for ARM Cortex-M.
 */
void SysTick_Handler(void) {
	// Call the virtual ISR and exit.
	TickerISR();
}

// Ticker uses TIM4 timer.
#elif defined(TICKERHW_USE_TIM4)

/**
 * @brief Ticker hardware init.
 */
void TickerHwInit(void) {
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 
	//-- TIM4 clock enable.
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 
	//-- Enable the TIM4 global Interrupt.
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = IRQPRIORITY_TIM4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 
	//-- Time base init.
	TIM_TimeBaseStructure.TIM_Period = TICKER_PERIOD_TICKS;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 
	//-- TIM4 IT enable.
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
 
	//-- TIM2 enable counter.
	TIM_Cmd(TIM4, ENABLE);
}
 
/**
 * @brief Ticker hardware ISR, uses TIM4 IRQ handler.
 */
void TIM4_IRQHandler(void) {
	//-- Clear the interrupt flag.
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
 
	// Call the virtual ISR and exit.
	TickerISR();
}

#endif

#endif // Exclude from compile when not included in projech.h
