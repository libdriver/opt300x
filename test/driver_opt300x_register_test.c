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
 * @file      driver_opt300x_register_test.c
 * @brief     driver opt300x register test source file
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

#include "driver_opt300x_register_test.h"
#include <stdlib.h>

static opt300x_handle_t gs_handle;        /**< opt300x handle */

/**
 * @brief     register test
 * @param[in] type chip type
 * @param[in] addr iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t opt300x_register_test(opt300x_t type, opt300x_address_t addr)
{
    uint8_t res;
    uint16_t reg;
    uint16_t limit;
    uint16_t limit_check;
    float nw_cm2;
    float nw_cm2_check;
    float lux;
    float lux_check;
    opt300x_t type_check;
    opt300x_info_t info;
    opt300x_address_t addr_pin;
    opt300x_bool_t enable;
    opt3002_range_t opt3002_range;
    opt3005_range_t opt3005_range;
    opt300x_range_t range;
    opt300x_conversion_time_t t;
    opt300x_interrupt_polarity_t polarity;
    opt300x_fault_count_t count;
    
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
    
    /* start register test */
    opt300x_interface_debug_print("opt300x: start register test.\n");
    
    /* opt300x_set_type/opt300x_get_type test */
    opt300x_interface_debug_print("opt300x: opt300x_set_type/opt300x_get_type test.\n");
    
    /* opt3001 */
    res = opt300x_set_type(&gs_handle, OPT3001);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set type failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set type opt3001.\n");
    res = opt300x_get_type(&gs_handle, &type_check);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get type failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check type %s.\n", type_check == OPT3001 ? "ok" : "error");
    
    /* opt3002 */
    res = opt300x_set_type(&gs_handle, OPT3002);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set type failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set type opt3002.\n");
    res = opt300x_get_type(&gs_handle, &type_check);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get type failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check type %s.\n", type_check == OPT3002 ? "ok" : "error");
    
    /* opt3004 */
    res = opt300x_set_type(&gs_handle, OPT3004);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set type failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set type opt3004.\n");
    res = opt300x_get_type(&gs_handle, &type_check);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get type failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check type %s.\n", type_check == OPT3004 ? "ok" : "error");
    
    /* opt3005 */
    res = opt300x_set_type(&gs_handle, OPT3005);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set type failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set type opt3005.\n");
    res = opt300x_get_type(&gs_handle, &type_check);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get type failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check type %s.\n", type_check == OPT3005 ? "ok" : "error");
    
    /* opt3006 */
    res = opt300x_set_type(&gs_handle, OPT3006);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set type failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set type opt3006.\n");
    res = opt300x_get_type(&gs_handle, &type_check);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get type failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check type %s.\n", type_check == OPT3006 ? "ok" : "error");
    
    /* opt3007 */
    res = opt300x_set_type(&gs_handle, OPT3007);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set type failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set type opt3007.\n");
    res = opt300x_get_type(&gs_handle, &type_check);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get type failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check type %s.\n", type_check == OPT3007 ? "ok" : "error");
    
    /* opt300x_set_addr_pin/opt300x_get_addr_pin test */
    opt300x_interface_debug_print("opt300x: opt300x_set_addr_pin/opt300x_get_addr_pin test.\n");
    
    /* set ADDRESS_GND */
    res = opt300x_set_addr_pin(&gs_handle, OPT300X_ADDRESS_GND);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set addr pin failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set addr pin ADDRESS_GND.\n");
    res = opt300x_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get addr pin failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check addr pin %s.\n", addr_pin == OPT300X_ADDRESS_GND ? "ok" : "error");
    
    /* set OPT300X_ADDRESS_VCC */
    res = opt300x_set_addr_pin(&gs_handle, OPT300X_ADDRESS_VCC);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set addr pin failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set addr pin ADDRESS_VCC.\n");
    res = opt300x_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get addr pin failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check addr pin %s.\n", addr_pin == OPT300X_ADDRESS_VCC ? "ok" : "error");
    
    /* set OPT300X_ADDRESS_SDA */
    res = opt300x_set_addr_pin(&gs_handle, OPT300X_ADDRESS_SDA);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set addr pin failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set addr pin ADDRESS_SDA.\n");
    res = opt300x_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get addr pin failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check addr pin %s.\n", addr_pin == OPT300X_ADDRESS_SDA ? "ok" : "error");
    
    /* set OPT300X_ADDRESS_SCL */
    res = opt300x_set_addr_pin(&gs_handle, OPT300X_ADDRESS_SCL);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set addr pin failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set addr pin ADDRESS_SCL.\n");
    res = opt300x_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get addr pin failed.\n");
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check addr pin %s.\n", addr_pin == OPT300X_ADDRESS_SCL ? "ok" : "error");
    
    /* set chip type */
    res = opt300x_set_type(&gs_handle, type);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set type failed.\n");
        
        return 1;
    }
    
    /* set address pin */
    res = opt300x_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set addr pin failed.\n");
        
        return 1;
    }
    
    /* init */
    res = opt300x_init(&gs_handle);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: init failed.\n");
        
        return 1;
    }
    
    /* opt300x_set_low_limit/opt300x_get_low_limit test */
    opt300x_interface_debug_print("opt300x: opt300x_set_low_limit/opt300x_get_low_limit test.\n");
    
    /* set low limit */
    limit = rand() % 0xFFFFU;
    res = opt300x_set_low_limit(&gs_handle, limit);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set low limit failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set low limit %d.\n", limit);
    res = opt300x_get_low_limit(&gs_handle, &limit_check);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get low limit failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check low limit %s.\n", limit == limit_check ? "ok" : "error");
    
    /* opt300x_set_high_limit/opt300x_get_high_limit test */
    opt300x_interface_debug_print("opt300x: opt300x_set_high_limit/opt300x_get_high_limit test.\n");
    
    /* set high limit */
    limit = rand() % 0xFFFFU;
    res = opt300x_set_high_limit(&gs_handle, limit);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set high limit failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set high limit %d.\n", limit);
    res = opt300x_get_high_limit(&gs_handle, &limit_check);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get high limit failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check high limit %s.\n", limit == limit_check ? "ok" : "error");
    
    if (type == OPT3002)
    {
        /* opt3002_set_range/opt3002_get_range test */
        opt300x_interface_debug_print("opt3002: opt3002_set_range/opt3002_get_range test.\n");
        
        /* set range 4914 nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_4914_NW_CM2);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range 4914 nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_4914_NW_CM2 ? "ok" : "error");
        
        /* set range 9828 nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_9828_NW_CM2);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range 9828 nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_9828_NW_CM2 ? "ok" : "error");
        
        /* set range 19656 nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_19656_NW_CM2);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range 19656 nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_19656_NW_CM2 ? "ok" : "error");
        
        /* set range 39312 nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_39312_NW_CM2);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range 39312 nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_39312_NW_CM2 ? "ok" : "error");
        
        /* set range 78624 nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_78624_NW_CM2);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range 78624 nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_78624_NW_CM2 ? "ok" : "error");
        
        /* set range 157248 nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_157248_NW_CM2);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range 157248 nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_157248_NW_CM2 ? "ok" : "error");
        
        /* set range 314496 nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_314496_NW_CM2);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range 314496 nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_314496_NW_CM2 ? "ok" : "error");
        
        /* set range 628992 nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_628992_NW_CM2);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range 628992 nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_628992_NW_CM2 ? "ok" : "error");
        
        /* set range 1257984 nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_1257984_NW_CM2);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range 1257984 nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_1257984_NW_CM2 ? "ok" : "error");
        
        /* set range 2515968 nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_2515968_NW_CM2);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range 2515968 nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_2515968_NW_CM2 ? "ok" : "error");
        
        /* set range 5031936 nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_5031936_NW_CM2);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range 5031936 nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_5031936_NW_CM2 ? "ok" : "error");
        
        /* set range 10063872 nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_10063872_NW_CM2);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range 10063872 nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_10063872_NW_CM2 ? "ok" : "error");
        
        /* set range auto range nW/cm2 */
        res = opt3002_set_range(&gs_handle, OPT3002_RANGE_AUTO);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: set range auto range nW/cm2.\n");
        res = opt3002_get_range(&gs_handle, &opt3002_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3002: check range %s.\n", opt3002_range == OPT3002_RANGE_AUTO ? "ok" : "error");
    }
    else if (type == OPT3005)
    {
        /* opt3005_set_range/opt3005_get_range test */
        opt300x_interface_debug_print("opt3005: opt3005_set_range/opt3005_get_range test.\n");
        
        /* set range 81.90 lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_81P90_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range 81.90 lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_81P90_LUX ? "ok" : "error");
        
        /* set range 163.80 lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_163P80_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range 163.80 lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_163P80_LUX ? "ok" : "error");
        
        /* set range 327.60 lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_327P60_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range 327.60 lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_327P60_LUX ? "ok" : "error");
        
        /* set range 655.20 lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_655P20_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range 655.20 lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_655P20_LUX ? "ok" : "error");
        
        /* set range 1310.40 lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_1310P40_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range 1310.40 lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_1310P40_LUX ? "ok" : "error");
        
        /* set range 2620.80 lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_2620P80_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range 2620.80 lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_2620P80_LUX ? "ok" : "error");
        
        /* set range 5241.60 lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_5241P60_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range 5241.60 lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_5241P60_LUX ? "ok" : "error");
        
        /* set range 10483.20 lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_10483P20_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range 10483.20 lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_10483P20_LUX ? "ok" : "error");
        
        /* set range 20966.40 lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_20966P40_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range 20966.40 lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_20966P40_LUX ? "ok" : "error");
        
        /* set range 41932.80 lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_41932P80_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range 41932.80 lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_41932P80_LUX ? "ok" : "error");
        
        /* set range 83865.60 lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_83865P60_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range 83865.60 lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_83865P60_LUX ? "ok" : "error");
        
        /* set range 167731.20 lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_167731P20_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range 167731.20 lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_167731P20_LUX ? "ok" : "error");
        
        /* set range auto range lux */
        res = opt3005_set_range(&gs_handle, OPT3005_RANGE_AUTO);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: set range auto range lux.\n");
        res = opt3005_get_range(&gs_handle, &opt3005_range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt3005: check range %s.\n", opt3005_range == OPT3005_RANGE_AUTO ? "ok" : "error");
    }
    else
    {
        /* opt300x_set_range/opt300x_get_range test */
        opt300x_interface_debug_print("opt300x: opt300x_set_range/opt300x_get_range test.\n");
        
        /* set range 40.95 lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_40P95_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range 40.95 lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_40P95_LUX ? "ok" : "error");
        
        /* set range 81.90 lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_81P90_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range 81.90 lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_81P90_LUX ? "ok" : "error");
        
        /* set range 163.80 lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_163P80_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range 163.80 lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_163P80_LUX ? "ok" : "error");
        
        /* set range 327.60 lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_327P60_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range 327.60 lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_327P60_LUX ? "ok" : "error");
        
        /* set range 655.20 lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_655P20_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range 655.20 lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_655P20_LUX ? "ok" : "error");
        
        /* set range 1310.40 lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_1310P40_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range 1310.40 lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_1310P40_LUX ? "ok" : "error");
        
        /* set range 2620.80 lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_2620P80_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range 2620.80 lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_2620P80_LUX ? "ok" : "error");
        
        /* set range 5241.60 lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_5241P60_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range 5241.60 lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_5241P60_LUX ? "ok" : "error");
        
        /* set range 10483.20 lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_10483P20_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range 10483.20 lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_10483P20_LUX ? "ok" : "error");
        
        /* set range 20966.40 lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_20966P40_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range 20966.40 lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_20966P40_LUX ? "ok" : "error");
        
        /* set range 41932.80 lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_41932P80_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range 41932.80 lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_41932P80_LUX ? "ok" : "error");
        
        /* set range 83865.60 lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_83865P60_LUX);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range 83865.60 lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_83865P60_LUX ? "ok" : "error");
        
        /* set range auto range lux */
        res = opt300x_set_range(&gs_handle, OPT300X_RANGE_AUTO);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set range auto range lux.\n");
        res = opt300x_get_range(&gs_handle, &range);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: get range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check range %s.\n", range == OPT300X_RANGE_AUTO ? "ok" : "error");
    }
    
    /* opt300x_set_conversion_time/opt300x_get_conversion_time test */
    opt300x_interface_debug_print("opt300x: opt300x_set_conversion_time/opt300x_get_conversion_time test.\n");
    
    /* 100ms */
    res = opt300x_set_conversion_time(&gs_handle, OPT300X_CONVERSION_TIME_100_MS);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set conversion time failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set conversion time 100ms.\n");
    res = opt300x_get_conversion_time(&gs_handle, &t);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get conversion time failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check conversion time %s.\n", t == OPT300X_CONVERSION_TIME_100_MS ? "ok" : "error");
    
    /* 800ms */
    res = opt300x_set_conversion_time(&gs_handle, OPT300X_CONVERSION_TIME_800_MS);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set conversion time failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set conversion time 800ms.\n");
    res = opt300x_get_conversion_time(&gs_handle, &t);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get conversion time failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check conversion time %s.\n", t == OPT300X_CONVERSION_TIME_800_MS ? "ok" : "error");
    
    /* opt300x_set_interrupt_latch/opt300x_get_interrupt_latch test */
    opt300x_interface_debug_print("opt300x: opt300x_set_interrupt_latch/opt300x_get_interrupt_latch test.\n");
    
    /* enable interrupt latch */
    res = opt300x_set_interrupt_latch(&gs_handle, OPT300X_BOOL_TRUE);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set interrupt latch failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: enable interrupt latch.\n");
    res = opt300x_get_interrupt_latch(&gs_handle, &enable);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get interrupt latch failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check interrupt latch %s.\n", enable == OPT300X_BOOL_TRUE ? "ok" : "error");
    
    /* disable interrupt latch */
    res = opt300x_set_interrupt_latch(&gs_handle, OPT300X_BOOL_FALSE);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set interrupt latch failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: disable interrupt latch.\n");
    res = opt300x_get_interrupt_latch(&gs_handle, &enable);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get interrupt latch failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check interrupt latch %s.\n", enable == OPT300X_BOOL_FALSE ? "ok" : "error");
    
    /* opt300x_set_interrupt_latch/opt300x_get_interrupt_latch test */
    opt300x_interface_debug_print("opt300x: opt300x_set_interrupt_latch/opt300x_get_interrupt_latch test.\n");
    
    /* set interrupt pin polarity low */
    res = opt300x_set_interrupt_pin_polarity(&gs_handle, OPT300X_INTERRUPT_POLARITY_LOW);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set interrupt pin polarity failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set interrupt pin polarity low.\n");
    res = opt300x_get_interrupt_pin_polarity(&gs_handle, &polarity);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get interrupt pin polarity failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check interrupt pin polarity %s.\n", polarity == OPT300X_INTERRUPT_POLARITY_LOW ? "ok" : "error");
    
    /* set interrupt pin polarity high */
    res = opt300x_set_interrupt_pin_polarity(&gs_handle, OPT300X_INTERRUPT_POLARITY_HIGH);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set interrupt pin polarity failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set interrupt pin polarity high.\n");
    res = opt300x_get_interrupt_pin_polarity(&gs_handle, &polarity);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get interrupt pin polarity failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check interrupt pin polarity %s.\n", polarity == OPT300X_INTERRUPT_POLARITY_HIGH ? "ok" : "error");
    
    /* opt300x_set_mask_exponent/opt300x_get_mask_exponent test */
    opt300x_interface_debug_print("opt300x: opt300x_set_mask_exponent/opt300x_get_mask_exponent test.\n");
    
    /* enable mask exponent */
    res = opt300x_set_mask_exponent(&gs_handle, OPT300X_BOOL_TRUE);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set mask exponent failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: enable mask exponent.\n");
    res = opt300x_get_mask_exponent(&gs_handle, &enable);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get mask exponent failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check mask exponent %s.\n", enable == OPT300X_BOOL_TRUE ? "ok" : "error");
    
    /* disable mask exponent */
    res = opt300x_set_mask_exponent(&gs_handle, OPT300X_BOOL_FALSE);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set mask exponent failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: disable mask exponent.\n");
    res = opt300x_get_mask_exponent(&gs_handle, &enable);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get mask exponent failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check mask exponent %s.\n", enable == OPT300X_BOOL_FALSE ? "ok" : "error");
    
    /* opt300x_set_fault_count/opt300x_get_fault_count test */
    opt300x_interface_debug_print("opt300x: opt300x_set_fault_count/opt300x_get_fault_count test.\n");
    
    /* set fault count one */
    res = opt300x_set_fault_count(&gs_handle, OPT300X_FAULT_COUNT_ONE);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set fault count failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set fault count one.\n");
    res = opt300x_get_fault_count(&gs_handle, &count);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get fault count failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check fault count %s.\n", count == OPT300X_FAULT_COUNT_ONE ? "ok" : "error");
    
    /* set fault count two */
    res = opt300x_set_fault_count(&gs_handle, OPT300X_FAULT_COUNT_TWO);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set fault count failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set fault count two.\n");
    res = opt300x_get_fault_count(&gs_handle, &count);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get fault count failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check fault count %s.\n", count == OPT300X_FAULT_COUNT_TWO ? "ok" : "error");
    
    /* set fault count four */
    res = opt300x_set_fault_count(&gs_handle, OPT300X_FAULT_COUNT_FOUR);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set fault count failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set fault count four.\n");
    res = opt300x_get_fault_count(&gs_handle, &count);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get fault count failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check fault count %s.\n", count == OPT300X_FAULT_COUNT_FOUR ? "ok" : "error");
    
    /* set fault count eight */
    res = opt300x_set_fault_count(&gs_handle, OPT300X_FAULT_COUNT_EIGHT);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set fault count failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: set fault count eight.\n");
    res = opt300x_get_fault_count(&gs_handle, &count);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: get fault count failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    opt300x_interface_debug_print("opt300x: check fault count %s.\n", count == OPT300X_FAULT_COUNT_EIGHT ? "ok" : "error");
    
    if (type == OPT3002)
    {
        /* opt300x_set_fault_count/opt300x_get_fault_count test */
        opt300x_interface_debug_print("opt300x: opt300x_set_fault_count/opt300x_get_fault_count test.\n");
        
        nw_cm2 = (float)(rand() % 10000) / 10.0f;
        res = opt3002_limit_convert_to_register(&gs_handle, nw_cm2, &reg);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: limit convert to register failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set nW/cm2 %0.2f.\n", nw_cm2);
        res = opt3002_limit_convert_to_data(&gs_handle, reg, &nw_cm2_check);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: limit convert to data failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check nW/cm2 %0.2f.\n", nw_cm2_check);
    }
    else
    {
        /* opt300x_limit_convert_to_register/opt300x_limit_convert_to_data test */
        opt300x_interface_debug_print("opt300x: opt300x_limit_convert_to_register/opt300x_limit_convert_to_data test.\n");
        
        lux = (float)(rand() % 10000) / 10.0f;
        res = opt300x_limit_convert_to_register(&gs_handle, lux, &reg);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: limit convert to register failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: set lux %0.2f.\n", lux);
        res = opt300x_limit_convert_to_data(&gs_handle, reg, &lux_check);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: limit convert to data failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
        opt300x_interface_debug_print("opt300x: check lux %0.2f.\n", lux_check);
    }
    
    /* finish register test */
    opt300x_interface_debug_print("opt300x: finish register test.\n");
    (void)opt300x_deinit(&gs_handle);
    
    return 0;
}
