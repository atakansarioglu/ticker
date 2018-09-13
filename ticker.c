/**
 * @file      ticker.c
 * @author    Atakan S.
 * @date      01/01/2018
 * @version   1.0
 * @brief     Implements abstraction routines for Ticker usage.
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

#include "ticker.h"
#include "ticker_hw.h"

// Type Definitions.
typedef struct{
	uint32_t ms:32;			///< Counts ms.
	uint32_t sub:8;			///< Counts sub-ms.
	uint32_t ticks:24;		///< Counts every tick.
}tTickerTime;

// Variables.
tTickerTime TickerTime;	///< Holds the time.

/**
 * @brief The virtual TickerISR.
 */
void TickerISR(void){
	// Tick.
	TickerTime.ticks++;
	
    // Increase the sub and the ms counter.
    if((++TickerTime.sub) >= TICKER_SUBMS_COUNT){
       TickerTime.sub = 0;
       TickerTime.ms++;

       // Hook for scheduled tasks.
       mTickerHook_ms();
    }
    
    // Hook for scheduled tasks.
    mTickerHook_fast();
}

/**
 * @brief Initializes Ticker. After calling this function, enable global interrupts manually.
 */
void TickerInit(void){
    uint8_t wasIntEn;
    
    // Save state and disable the interrupts.
    wasIntEn = mIsIntEnabled();
    mIntDisable();
	
	// HW Init.
	TickerHwInit();
    
    // Initialize the counters.
	TickerTime.ms = 0;
	TickerTime.sub = 0;
	TickerTime.ticks = 0;
    
    // Re-enable interrupts.
    if(wasIntEn){
        mIntEnable();
    }
}

/**
 * @brief Reads thread-safe time ticks.
 * @return 16-bit Ticker count.
 */
uint16_t TickerRead_ticks(void){
	uint16_t ticks;
	do{
		ticks = TickerTime.ticks;
	}while(ticks != TickerTime.ticks);
	return ticks;
}

/**
 * @brief Reads thread-safe time in ms.
 * @return 32-bit ms time, only relative-time usage.
 */
uint32_t TickerRead_ms(void){
	uint32_t ms;
	do{
		ms = TickerTime.ms;
	}while(ms != TickerTime.ms);
	return ms;
}

#endif // Exclude from compile when not included in projech.h
