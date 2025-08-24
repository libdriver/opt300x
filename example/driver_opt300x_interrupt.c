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
 * @file      driver_opt300x_interrupt.c
 * @brief     driver opt300x interrupt source file
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

#include "driver_opt300x_interrupt.h"

static opt300x_handle_t gs_handle;        /**< opt300x handle */

/**
 * @brief  interrupt irq
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t opt300x_interrupt_irq_handler(void)
{
    if (opt300x_irq_handler(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

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
                               void (*callback)(uint8_t type))
{
    uint8_t res;
    uint16_t limit;
    
    /* link interface function */
    DRIVER_OPT300X_LINK_INIT(&gs_handle, opt300x_handle_t);
    DRIVER_OPT300X_LINK_IIC_INIT(&gs_handle, opt300x_interface_iic_init);
    DRIVER_OPT300X_LINK_IIC_DEINIT(&gs_handle, opt300x_interface_iic_deinit);
    DRIVER_OPT300X_LINK_IIC_READ(&gs_handle, opt300x_interface_iic_read);
    DRIVER_OPT300X_LINK_IIC_WRITE(&gs_handle, opt300x_interface_iic_write);
    DRIVER_OPT300X_LINK_DELAY_MS(&gs_handle, opt300x_interface_delay_ms);
    DRIVER_OPT300X_LINK_DEBUG_PRINT(&gs_handle, opt300x_interface_debug_print);
    DRIVER_OPT300X_LINK_RECEIVE_CALLBACK(&gs_handle, callback);
    
    /* set chip type */
    res = opt300x_set_type(&gs_handle, type);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set type failed.\n");
        
        return 1;
    }
    
    /* set iic address */
    res = opt300x_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set addr pin failed.\n");
        
        return 1;
    }
    
    /* opt300x init */
    res = opt300x_init(&gs_handle);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: init failed.\n");
        
        return 1;
    }
    
    if (type != OPT3002)
    {
        /* convert low threshold lux */
        res = opt300x_limit_convert_to_register(&gs_handle, low_threshold, &limit);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: limit convert to register failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set low limit */
        res = opt300x_set_low_limit(&gs_handle, limit);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set low limit failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* convert high threshold lux */
        res = opt300x_limit_convert_to_register(&gs_handle, high_threshold, &limit);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: limit convert to register failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set high limit */
        res = opt300x_set_high_limit(&gs_handle, limit);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set high limit failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
    }
    else
    {
        /* convert low threshold nw_cm2 */
        res = opt3002_limit_convert_to_register(&gs_handle, low_threshold, &limit);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: limit convert to register failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set low limit */
        res = opt300x_set_low_limit(&gs_handle, limit);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set low limit failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* convert high threshold nw_cm2 */
        res = opt3002_limit_convert_to_register(&gs_handle, high_threshold, &limit);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: limit convert to register failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set high limit */
        res = opt300x_set_high_limit(&gs_handle, limit);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set high limit failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* set default interrupt latch */
    res = opt300x_set_interrupt_latch(&gs_handle, OPT300X_INTERRUPT_DEFAULT_INTERRUPT_LATCH);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set interrupt latch failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default interrupt pin polarity */
    res = opt300x_set_interrupt_pin_polarity(&gs_handle, OPT300X_INTERRUPT_DEFAULT_INTERRUPT_POLARITY);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set interrupt pin polarity failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default range */
    if (type == OPT3002)
    {
        res = opt3002_set_range(&gs_handle, OPT3002_INTERRUPT_DEFAULT_RANGE);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
    }
    else if (type == OPT3005)
    {
        res = opt3005_set_range(&gs_handle, OPT3005_INTERRUPT_DEFAULT_RANGE);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
    }
    else
    {
        res = opt300x_set_range(&gs_handle, OPT300X_INTERRUPT_DEFAULT_RANGE);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* set default conversion time */
    res = opt300x_set_conversion_time(&gs_handle, OPT300X_INTERRUPT_DEFAULT_CONVERSION_TIME);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set conversion time failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default mask exponent */
    res = opt300x_set_mask_exponent(&gs_handle, OPT300X_INTERRUPT_DEFAULT_MASK_EXPONENT);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set mask exponent failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default fault count */
    res = opt300x_set_fault_count(&gs_handle, OPT300X_INTERRUPT_DEFAULT_FAULT_COUNT);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set fault count failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* start continuous read */
    res = opt300x_start_continuous_read(&gs_handle);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: start continuous read failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      interrupt example read
 * @param[out] *lux pointer to a lux buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t opt300x_interrupt_read(float *lux)
{
    uint16_t raw;
    
    /* read data */
    if (opt300x_continuous_read(&gs_handle, (uint16_t *)&raw, lux) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      interrupt example read
 * @param[out] *nw_cm2 pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t opt3002_interrupt_read(float *nw_cm2)
{
    uint16_t raw;
    
    /* read data */
    if (opt3002_continuous_read(&gs_handle, (uint16_t *)&raw, nw_cm2) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  interrupt example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t opt300x_interrupt_deinit(void)
{
    /* stop continuous read */
    if (opt300x_stop_continuous_read(&gs_handle) != 0)
    {
        return 1;
    }
    
    /* close opt300x */
    if (opt300x_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
