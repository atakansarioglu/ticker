/**
 * @file      ticker_hw.h
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

#ifndef _H_TICKER_HW
#define _H_TICKER_HW

#include "porty.h"

// Default timer setting.
#if !defined(TICKERHW_USE_ARMSYSTICK) && !defined(TICKERHW_USE_TIM4)
#define TICKERHW_USE_ARMSYSTICK
#endif
#if defined(TICKERHW_USE_TIM4) && !defined(IRQPRIORITY_TIM4)
#define IRQPRIORITY_TIM4 1
#endif

/**
 * @brief Ticker hardware init.
 */
void TickerHwInit(void);

#endif

