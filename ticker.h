/**
 * @file      ticker.h
 * @author    Atakan S.
 * @date      01/01/2018
 * @version   1.1
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

#ifndef _H_TICKER
#define _H_TICKER

#include "porty.h"

// Definitions.
#define TICKER_PERIOD_US       	(1000UL/TICKER_SUBMS_COUNT)		///< Period of a Ticker in [us]
#define TICKER_PERIOD_TICKS    	(TICKER_PERIOD_US*CLOCK_MHz)	///< Period of a Ticker in [ticks] (CPU cycles).

// Default settings can be overridden.
#ifndef mTickerHook_ms
#define mTickerHook_ms()										///< General-purpose hook that is called inside ISR every ms.
#endif
#ifndef mTickerHook_fast
#define mTickerHook_fast()										///< General-purpose hook that is called inside ISR everytime.
#endif
#ifndef TICKER_SUBMS_COUNT
#define TICKER_SUBMS_COUNT     	(1UL)			                ///< Number of ticks per [ms] (>=1)
#endif

// Prototypes.
void TickerInit(void);
void TickerISR(void);
uint16_t TickerRead_ticks(void);
uint32_t TickerRead_ms(void);

#endif
