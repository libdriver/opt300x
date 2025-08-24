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
 * @file      driver_opt300x_read_test.c
 * @brief     driver opt300x read test source file
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

#include "driver_opt300x_read_test.h"

static opt300x_handle_t gs_handle;        /**< opt300x handle */

/**
 * @brief     read test
 * @param[in] type chip type
 * @param[in] addr_pin iic device address
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t opt300x_read_test(opt300x_t type, opt300x_address_t addr_pin, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    opt300x_info_t info;
    
    /* link interface function */
    DRIVER_OPT300X_LINK_INIT(&gs_handle, opt300x_handle_t);
    DRIVER_OPT300X_LINK_IIC_INIT(&gs_handle, opt300x_interface_iic_init);
    DRIVER_OPT300X_LINK_IIC_DEINIT(&gs_handle, opt300x_interface_iic_deinit);
    DRIVER_OPT300X_LINK_IIC_READ(&gs_handle, opt300x_interface_iic_read);
    DRIVER_OPT300X_LINK_IIC_WRITE(&gs_handle, opt300x_interface_iic_write);
    DRIVER_OPT300X_LINK_DELAY_MS(&gs_handle, opt300x_interface_delay_ms);
    DRIVER_OPT300X_LINK_DEBUG_PRINT(&gs_handle, opt300x_interface_debug_print);
    DRIVER_OPT300X_LINK_RECEIVE_CALLBACK(&gs_handle, opt300x_interface_receive_callback);

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
    
    /* start read test */
    opt300x_interface_debug_print("opt300x: start read test.\n");
    
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
    
    /* continuous read test */
    opt300x_interface_debug_print("opt300x: continuous read test.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t raw;
        float lux;
        float nw_cm2;
        
        /* delay 1000ms */
        opt300x_interface_delay_ms(1000);
        
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
    
    /* single read test */
    opt300x_interface_debug_print("opt300x: single read test.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t raw;
        float lux;
        float nw_cm2;
        
        /* delay 1000ms */
        opt300x_interface_delay_ms(1000);
        
        if (type == OPT3002)
        {
            res = opt3002_single_read(&gs_handle, &raw, &nw_cm2);
            if (res != 0)
            {
                opt300x_interface_debug_print("opt3002: single read failed.\n");
                (void)opt300x_deinit(&gs_handle);
                
                return 1;
            }
            opt300x_interface_debug_print("opt300x: %0.2f nW/cm2.\n", nw_cm2);
        }
        else
        {
            res = opt300x_single_read(&gs_handle, &raw, &lux);
            if (res != 0)
            {
                opt300x_interface_debug_print("opt3002: single read failed.\n");
                (void)opt300x_deinit(&gs_handle);
                
                return 1;
            }
            opt300x_interface_debug_print("opt300x: %0.2f lux.\n", lux);
        }
    }
    
    /* finish read test */
    opt300x_interface_debug_print("opt300x: finish read test.\n");
    (void)opt300x_deinit(&gs_handle);
    
    return 0;
}
