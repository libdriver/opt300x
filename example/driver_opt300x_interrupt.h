/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_opt300x_interrupt.h
 * @brief     driver opt300x interrupt header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-08-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/08/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_OPT300X_INTERRUPT_H
#define DRIVER_OPT300X_INTERRUPT_H

#include <driver_opt300x_interface.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup opt300x_example_driver
 * @{
 */

/**
 * @brief opt300x interrupt example default definition
 */
#define OPT300X_INTERRUPT_DEFAULT_INTERRUPT_LATCH        OPT300X_BOOL_TRUE                      /**< enable interrupt latch */
#define OPT300X_INTERRUPT_DEFAULT_INTERRUPT_POLARITY     OPT300X_INTERRUPT_POLARITY_LOW         /**< interrupt pin polarity low */
#define OPT3002_INTERRUPT_DEFAULT_RANGE                  OPT3002_RANGE_AUTO                     /**< auto range */
#define OPT3005_INTERRUPT_DEFAULT_RANGE                  OPT3005_RANGE_AUTO                     /**< auto range */
#define OPT300X_INTERRUPT_DEFAULT_RANGE                  OPT300X_RANGE_AUTO                     /**< auto range */
#define OPT300X_INTERRUPT_DEFAULT_CONVERSION_TIME        OPT300X_CONVERSION_TIME_800_MS         /**< 800ms */
#define OPT300X_INTERRUPT_DEFAULT_MASK_EXPONENT          OPT300X_BOOL_FALSE                     /**< disable mask exponent */
#define OPT300X_INTERRUPT_DEFAULT_FAULT_COUNT            OPT300X_FAULT_COUNT_ONE                /**< fault count one */

/**
 * @brief  interrupt irq
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t opt300x_interrupt_irq_handler(void);

/**
 * @brief     interrupt example init
 * @param[in] type chip type
 * @param[in] addr_pin iic device address
 * @param[in] low_threshold low threshold in lux or in nw/cm2
 * @param[in] high_threshold high threshold in lux or in nw/cm2
 * @param[in] *callback pointer to a callback function address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t opt300x_interrupt_init(opt300x_t type, opt300x_address_t addr_pin, 
                               float low_threshold, float high_threshold,
                               void (*callback)(uint8_t type));

/**
 * @brief  interrupt example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t opt300x_interrupt_deinit(void);

/**
 * @brief      interrupt example read
 * @param[out] *lux pointer to a lux buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t opt300x_interrupt_read(float *lux);

/**
 * @brief      interrupt example read
 * @param[out] *nw_cm2 pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t opt3002_interrupt_read(float *nw_cm2);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
