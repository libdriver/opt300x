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
 * @file      driver_opt300x_shot.c
 * @brief     driver opt300x shot source file
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

#include "driver_opt300x_shot.h"

static opt300x_handle_t gs_handle;        /**< opt300x handle */

/**
 * @brief     shot example init
 * @param[in] type chip type
 * @param[in] addr_pin iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t opt300x_shot_init(opt300x_t type, opt300x_address_t addr_pin)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_OPT300X_LINK_INIT(&gs_handle, opt300x_handle_t);
    DRIVER_OPT300X_LINK_IIC_INIT(&gs_handle, opt300x_interface_iic_init);
    DRIVER_OPT300X_LINK_IIC_DEINIT(&gs_handle, opt300x_interface_iic_deinit);
    DRIVER_OPT300X_LINK_IIC_READ(&gs_handle, opt300x_interface_iic_read);
    DRIVER_OPT300X_LINK_IIC_WRITE(&gs_handle, opt300x_interface_iic_write);
    DRIVER_OPT300X_LINK_DELAY_MS(&gs_handle, opt300x_interface_delay_ms);
    DRIVER_OPT300X_LINK_DEBUG_PRINT(&gs_handle, opt300x_interface_debug_print);
    DRIVER_OPT300X_LINK_RECEIVE_CALLBACK(&gs_handle, opt300x_interface_receive_callback);
    
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
    
    /* set default range */
    if (type == OPT3002)
    {
        res = opt3002_set_range(&gs_handle, OPT3002_SHOT_DEFAULT_RANGE);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3002: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
    }
    else if (type == OPT3005)
    {
        res = opt3005_set_range(&gs_handle, OPT3005_SHOT_DEFAULT_RANGE);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt3005: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
    }
    else
    {
        res = opt300x_set_range(&gs_handle, OPT300X_SHOT_DEFAULT_RANGE);
        if (res != 0)
        {
            opt300x_interface_debug_print("opt300x: set range failed.\n");
            (void)opt300x_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* set default conversion time */
    res = opt300x_set_conversion_time(&gs_handle, OPT300X_SHOT_DEFAULT_CONVERSION_TIME);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set conversion time failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default mask exponent */
    res = opt300x_set_mask_exponent(&gs_handle, OPT300X_SHOT_DEFAULT_MASK_EXPONENT);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set mask exponent failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default fault count */
    res = opt300x_set_fault_count(&gs_handle, OPT300X_SHOT_DEFAULT_FAULT_COUNT);
    if (res != 0)
    {
        opt300x_interface_debug_print("opt300x: set fault count failed.\n");
        (void)opt300x_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      shot example read
 * @param[out] *lux pointer to a lux buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t opt300x_shot_read(float *lux)
{
    uint16_t raw;
    
    /* read data */
    if (opt300x_single_read(&gs_handle, (uint16_t *)&raw, lux) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      shot example read
 * @param[out] *nw_cm2 pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t opt3002_shot_read(float *nw_cm2)
{
    uint16_t raw;
    
    /* read data */
    if (opt3002_single_read(&gs_handle, (uint16_t *)&raw, nw_cm2) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  shot example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t opt300x_shot_deinit(void)
{
    /* close opt300x */
    if (opt300x_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
