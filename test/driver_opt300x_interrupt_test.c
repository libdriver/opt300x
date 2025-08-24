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
 * @file      driver_opt300x_interrupt_test.c
 * @brief     driver opt300x interrupt test source file
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
 
#include "driver_opt300x_interrupt_test.h"

static opt300x_handle_t gs_handle;        /**< opt300x handle */
static uint8_t gs_flag = 0;               /**< flag */

/**
 * @brief  interrupt test irq
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t opt300x_interrupt_test_irq_handler(void)
{
    if (opt300x_irq_handler(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     interface receive callback
 * @param[in] type irq type
 * @note      none
 */
static void a_receive_callback(uint8_t type)
{
    switch (type)
    {
        case OPT300X_INTERRUPT_HIGH_LIMIT :
        {
            gs_flag = 1;
            opt300x_interface_debug_print("opt300x: irq high limit.\n");
            
            break;
        }
        case OPT300X_INTERRUPT_LOW_LIMIT :
        {
            gs_flag = 1;
            opt300x_interface_debug_print("opt300x: irq low limit.\n");
            
            break;
        }
        default :
        {
            opt300x_interface_debug_print("opt300x: unknown code.\n");
            
            break;
        }
    }
}

/**
 * @brief     interrupt test
 * @param[in] type chip type
 * @param[in] addr_pin iic device address
 * @param[in] low_threshold low threshold in lux or in nw/cm2
 * @param[in] high_threshold high threshold in lux or in nw/cm2
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t opt300x_interrupt_test(opt300x_t type, opt300x_address_t addr_pin, 
                               float low_threshold, float high_threshold, uint32_t times)
{
    uint8_t res;
    uint16_t limit;
    uint32_t t;
    opt300x_info_t info;
    
    /* link interface function */
    DRIVER_OPT300X_LINK_INIT(&gs_handle, opt300x_handle_t);
    DRIVER_OPT300X_LINK_IIC_INIT(&gs_handle, opt300x_interface_iic_init);
    DRIVER_OPT300X_LINK_IIC_DEINIT(&gs_handle, opt300x_interface_iic_deinit);
    DRIVER_OPT300X_LINK_IIC_READ(&gs_handle, opt300x_interface_iic_read);
    DRIVER_OPT300X_LINK_IIC_WRITE(&gs_handle, opt300x_interface_iic_write);
    DRIVER_OPT300X_LINK_DELAY_MS(&gs_handle, opt300x_interface_delay_ms);
    DRIVER_OPT300X_LINK_DEBUG_PRINT(&gs_handle, opt300x_interface_debug_print);
    DRIVER_OPT300X_LINK_RECEIVE_CALLBACK(&gs_handle, a_receive_callback);

    /* get chip information */
    res = opt300x_info(&info);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        opt300x_interface_debug_print("opt300x: chip is %s.\n", info.chip_name);
        opt300x_interface_debug_print("opt300x: manufacturer is %s.\n", info.manufacturer_name);
        opt300x_interface_debug_print("opt300x: interface is %s.\n", info.interface);
        opt300x_interface_debug_print("opt300x: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        opt300x_interface_debug_print("opt300x: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        opt300x_interface_debug_print("opt300x: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        opt300x_interface_debug_print("opt300x: max current is %0.2fmA.\n", info.max_current_ma);
        opt300x_interface_debug_print("opt300x: max temperature is %0.1fC.\n", info.temperature_max);
        opt300x_interface_debug_print("opt300x: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
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
    
    /* start interrupt test */
    opt300x_interface_debug_print("opt300x: start interrupt test.\n");
    
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
    
    /* enable interrupt latch */
    res = opt300x_set_interrupt_latch(&gs_handle, OPT300X_BOOL_TRUE);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set interrupt latch failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set interrupt pin polarity low */
    res = opt300x_set_interrupt_pin_polarity(&gs_handle, OPT300X_INTERRUPT_POLARITY_LOW);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set interrupt pin polarity failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set auto range */
    if (type == OPT3002)
    {
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_AUTO);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
    }
    else if (type == OPT3005)
    {
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_AUTO);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
    }
    else
    {
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_AUTO);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* set conversion time 800ms */
    res = opt300x_set_conversion_time(&gs_handle, OPT300X_CONVERSION_TIME_800_MS);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set conversion time failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable mask exponent */
    res = opt300x_set_mask_exponent(&gs_handle, OPT300X_BOOL_FALSE);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set mask exponent failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set fault count one */
    res = opt300x_set_fault_count(&gs_handle, OPT300X_FAULT_COUNT_ONE);
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
    
    /* run the testing */
    t = times;
    gs_flag = 0;
    while (t != 0)
    {
        uint16_t raw;
        float lux;
        float nw_cm2;
        
        /* delay 1000ms */
        opt300x_interface_delay_ms(1000);
        
        if (gs_flag != 0)
        {
            gs_flag = 0;
            t--;
        }
        
        if (type == OPT3002)
        {
            res = opt3002_continuous_read(&gs_handle, &raw, &nw_cm2);
            if (res != 0)
            {
                opt300x_interface_debug_print("opt3002: continuous read failed.\n");
                (void)opt300x_deinit(&gs_handle);
                
                return 1;
            }
            opt300x_interface_debug_print("opt300x: %0.2f nW/cm2.\n", nw_cm2);
        }
        else
        {
            res = opt300x_continuous_read(&gs_handle, &raw, &lux);
            if (res != 0)
            {
                opt300x_interface_debug_print("opt3002: continuous read failed.\n");
                (void)opt300x_deinit(&gs_handle);
                
                return 1;
            }
            opt300x_interface_debug_print("opt300x: %0.2f lux.\n", lux);
        }
    }
    
    /* stop continuous read */
    res = opt300x_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: stop continuous read failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish interrupt test */
    opt300x_interface_debug_print("opt300x: finish interrupt test.\n");
    (void)opt300x_deinit(&gs_handle);
    
    return 0;
}
