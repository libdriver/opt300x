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
 * @file      driver_opt300x.h
 * @brief     driver opt300x header file
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

#ifndef DRIVER_OPT300X_H
#define DRIVER_OPT300X_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup opt300x_driver opt300x driver function
 * @brief    opt300x driver modules
 * @{
 */

/**
 * @addtogroup opt300x_base_driver
 * @{
 */

/**
 * @brief opt300x type enumeration definition
 */
typedef enum
{
    OPT3001 = 0x01,        /**< opt3001 */
    OPT3002 = 0x02,        /**< opt3002 */
    OPT3004 = 0x04,        /**< opt3004 */
    OPT3005 = 0x05,        /**< opt3005 */
    OPT3006 = 0x06,        /**< opt3006 */
    OPT3007 = 0x07,        /**< opt3007 */
} opt300x_t;

/**
 * @brief opt300x address enumeration definition
 */
typedef enum
{
    OPT300X_ADDRESS_GND = 0x88,        /**< ADDR pin connected to GND */
    OPT300X_ADDRESS_VCC = 0x8A,        /**< ADDR pin connected to VCC */
    OPT300X_ADDRESS_SDA = 0x8C,        /**< ADDR pin connected to SDA */
    OPT300X_ADDRESS_SCL = 0x8E,        /**< ADDR pin connected to SCL */
} opt300x_address_t;

/**
 * @brief opt300x bool enumeration definition
 */
typedef enum
{
    OPT300X_BOOL_FALSE = 0x00,        /**< disable */
    OPT300X_BOOL_TRUE  = 0x01,        /**< enable */
} opt300x_bool_t;

/**
 * @brief opt300x conversion time enumeration definition
 */
typedef enum
{
    OPT300X_CONVERSION_TIME_100_MS = 0x00,        /**< 100ms */
    OPT300X_CONVERSION_TIME_800_MS = 0x01,        /**< 800ms */
} opt300x_conversion_time_t;

/**
 * @brief opt300x interrupt polarity enumeration definition
 */
typedef enum
{
    OPT300X_INTERRUPT_POLARITY_LOW  = 0x00,        /**< polarity low */
    OPT300X_INTERRUPT_POLARITY_HIGH = 0x01,        /**< polarity high */
} opt300x_interrupt_polarity_t;

/**
 * @brief opt300x fault count enumeration definition
 */
typedef enum
{
    OPT300X_FAULT_COUNT_ONE   = 0x00,        /**< one fault count */
    OPT300X_FAULT_COUNT_TWO   = 0x01,        /**< two fault counts */
    OPT300X_FAULT_COUNT_FOUR  = 0x02,        /**< four fault counts */
    OPT300X_FAULT_COUNT_EIGHT = 0x03,        /**< eight fault counts */
} opt300x_fault_count_t;

/**
 * @brief opt300x range enumeration definition
 */
typedef enum
{
    OPT300X_RANGE_40P95_LUX    = 0x00,        /**< 40.95 lux */
    OPT300X_RANGE_81P90_LUX    = 0x01,        /**< 81.90 lux */
    OPT300X_RANGE_163P80_LUX   = 0x02,        /**< 163.80 lux */
    OPT300X_RANGE_327P60_LUX   = 0x03,        /**< 327.60 lux */
    OPT300X_RANGE_655P20_LUX   = 0x04,        /**< 655.20 lux */
    OPT300X_RANGE_1310P40_LUX  = 0x05,        /**< 1310.40 lux */
    OPT300X_RANGE_2620P80_LUX  = 0x06,        /**< 2620.80 lux */
    OPT300X_RANGE_5241P60_LUX  = 0x07,        /**< 5241.60 lux */
    OPT300X_RANGE_10483P20_LUX = 0x08,        /**< 10483.20 lux */
    OPT300X_RANGE_20966P40_LUX = 0x09,        /**< 20966.40 lux */
    OPT300X_RANGE_41932P80_LUX = 0x0A,        /**< 41932.80 lux */
    OPT300X_RANGE_83865P60_LUX = 0x0B,        /**< 83865.60 lux */
    OPT300X_RANGE_AUTO         = 0x0C,        /**< auto range lux */
} opt300x_range_t;

/**
 * @brief opt3002 range enumeration definition
 */
typedef enum
{
    OPT3002_RANGE_4914_NW_CM2     = 0x00,        /**< 4914 nW/cm2 */
    OPT3002_RANGE_9828_NW_CM2     = 0x00,        /**< 9828 nW/cm2 */
    OPT3002_RANGE_19656_NW_CM2    = 0x00,        /**< 19656 nW/cm2 */
    OPT3002_RANGE_39312_NW_CM2    = 0x00,        /**< 39312 nW/cm2 */
    OPT3002_RANGE_78624_NW_CM2    = 0x00,        /**< 78624 nW/cm2 */
    OPT3002_RANGE_157248_NW_CM2   = 0x00,        /**< 157248 nW/cm2 */
    OPT3002_RANGE_314496_NW_CM2   = 0x00,        /**< 314496 nW/cm2 */
    OPT3002_RANGE_628992_NW_CM2   = 0x00,        /**< 628992 nW/cm2 */
    OPT3002_RANGE_1257984_NW_CM2  = 0x00,        /**< 1257984 nW/cm2 */
    OPT3002_RANGE_2515968_NW_CM2  = 0x00,        /**< 2515968 nW/cm2 */
    OPT3002_RANGE_5031936_NW_CM2  = 0x00,        /**< 5031936 nW/cm2 */
    OPT3002_RANGE_10063872_NW_CM2 = 0x00,        /**< 10063872 nW/cm2 */
    OPT3002_RANGE_AUTO            = 0x0C,        /**< auto range nW/cm2 */
} opt3002_range_t;

/**
 * @brief opt3005 range enumeration definition
 */
typedef enum
{
    OPT3005_RANGE_81P90_LUX     = 0x00,        /**< 81.90 lux */
    OPT3005_RANGE_163P80_LUX    = 0x01,        /**< 163.80 lux */
    OPT3005_RANGE_327P60_LUX    = 0x02,        /**< 327.60 lux */
    OPT3005_RANGE_655P20_LUX    = 0x03,        /**< 655.20 lux */
    OPT3005_RANGE_1310P40_LUX   = 0x04,        /**< 1310.40 lux */
    OPT3005_RANGE_2620P80_LUX   = 0x05,        /**< 2620.80 lux */
    OPT3005_RANGE_5241P60_LUX   = 0x06,        /**< 5241.60 lux */
    OPT3005_RANGE_10483P20_LUX  = 0x07,        /**< 10483.20 lux */
    OPT3005_RANGE_20966P40_LUX  = 0x08,        /**< 20966.40 lux */
    OPT3005_RANGE_41932P80_LUX  = 0x09,        /**< 41932.80 lux */
    OPT3005_RANGE_83865P60_LUX  = 0x0A,        /**< 83865.60 lux */
    OPT3005_RANGE_167731P20_LUX = 0x0B,        /**< 167731.20 lux */
    OPT3005_RANGE_AUTO          = 0x0C,        /**< auto range lux */
} opt3005_range_t;

/**
 * @brief opt300x interrupt enumeration definition
 */
typedef enum
{
    OPT300X_INTERRUPT_HIGH_LIMIT = 0x00,        /**< high limit */
    OPT300X_INTERRUPT_LOW_LIMIT  = 0x01,        /**< low limit */
} opt300x_interrupt_t;

/**
 * @brief opt300x handle structure definition
 */
typedef struct opt300x_handle_s
{
    uint8_t iic_addr;                                                                   /**< iic device address */
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*receive_callback)(uint8_t type);                                             /**< point to a receive_callback function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t type;                                                                       /**< chip type */
    uint8_t inited;                                                                     /**< inited flag */
} opt300x_handle_t;

/**
 * @brief opt300x information structure definition
 */
typedef struct opt300x_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} opt300x_info_t;

/**
 * @}
 */

/**
 * @defgroup opt300x_link_driver opt300x link driver function
 * @brief    opt300x link driver modules
 * @ingroup  opt300x_driver
 * @{
 */

/**
 * @brief     initialize opt300x_handle_t structure
 * @param[in] HANDLE pointer to an opt300x handle structure
 * @param[in] STRUCTURE opt300x_handle_t
 * @note      none
 */
#define DRIVER_OPT300X_LINK_INIT(HANDLE, STRUCTURE)          memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to an opt300x handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_OPT300X_LINK_IIC_INIT(HANDLE, FUC)           (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to an opt300x handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_OPT300X_LINK_IIC_DEINIT(HANDLE, FUC)         (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE pointer to an opt300x handle structure
 * @param[in] FUC pointer to an iic_read function address
 * @note      none
 */
#define DRIVER_OPT300X_LINK_IIC_READ(HANDLE, FUC)           (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE pointer to an opt300x handle structure
 * @param[in] FUC pointer to an iic_write function address
 * @note      none
 */
#define DRIVER_OPT300X_LINK_IIC_WRITE(HANDLE, FUC)          (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to an opt300x handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_OPT300X_LINK_DELAY_MS(HANDLE, FUC)           (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to an opt300x handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_OPT300X_LINK_DEBUG_PRINT(HANDLE, FUC)        (HANDLE)->debug_print = FUC

/**
 * @brief     link receive_callback function
 * @param[in] HANDLE pointer to an opt300x handle structure
 * @param[in] FUC pointer to a receive_callback function address
 * @note      none
 */
#define DRIVER_OPT300X_LINK_RECEIVE_CALLBACK(HANDLE, FUC)   (HANDLE)->receive_callback = FUC

/**
 * @}
 */

/**
 * @defgroup opt300x_base_driver opt300x base driver function
 * @brief    opt300x base driver modules
 * @ingroup  opt300x_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an opt300x info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t opt300x_info(opt300x_info_t *info);

/**
 * @brief     set the chip type
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t opt300x_set_type(opt300x_handle_t *handle, opt300x_t type);

/**
 * @brief      get the iic chip type
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *type pointer to a chip type buffer
 * @return      status code
 *              - 0 success
 *              - 2 handle is NULL
 * @note        none
 */
uint8_t opt300x_get_type(opt300x_handle_t *handle, opt300x_t *type);

/**
 * @brief     set the iic address pin
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] addr_pin chip iic address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t opt300x_set_addr_pin(opt300x_handle_t *handle, opt300x_address_t addr_pin);

/**
 * @brief      get the iic address pin
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *addr_pin pointer to a chip iic address pin buffer
 * @return      status code
 *              - 0 success
 *              - 2 handle is NULL
 * @note        none
 */
uint8_t opt300x_get_addr_pin(opt300x_handle_t *handle, opt300x_address_t *addr_pin);

/**
 * @brief     irq handler
 * @param[in] *handle pointer to an opt300x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t opt300x_irq_handler(opt300x_handle_t *handle);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to an opt300x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 id is invalid
 * @note      none
 */
uint8_t opt300x_init(opt300x_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to an opt300x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t opt300x_deinit(opt300x_handle_t *handle);

/**
 * @brief     start the chip reading
 * @param[in] *handle pointer to an opt300x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 start continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t opt300x_start_continuous_read(opt300x_handle_t *handle);

/**
 * @brief     stop the chip reading
 * @param[in] *handle pointer to an opt300x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t opt300x_stop_continuous_read(opt300x_handle_t *handle);

/**
 * @brief      read data from the chip continuously
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *raw pointer to a raw data buffer
 * @param[out] *lux pointer to a converted lux buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 data is overflow
 *             - 5 opt3002 can't use this function
 * @note       none
 */
uint8_t opt300x_continuous_read(opt300x_handle_t *handle, uint16_t *raw, float *lux);

/**
 * @brief      read data from the chip continuously
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *raw pointer to a raw data buffer
 * @param[out] *nw_cm2 pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 data is overflow
 *             - 5 only opt3002 can use this function
 * @note       none
 */
uint8_t opt3002_continuous_read(opt300x_handle_t *handle, uint16_t *raw, float *nw_cm2);

/**
 * @brief      read data from the chip
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *raw pointer to a raw data buffer
 * @param[out] *lux pointer to a converted lux buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 data is overflow
 *             - 5 read timeout
 *             - 6 opt3002 can't use this function
 * @note       none
 */
uint8_t opt300x_single_read(opt300x_handle_t *handle, uint16_t *raw, float *lux);

/**
 * @brief      read data from the chip
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *raw pointer to a raw data buffer
 * @param[out] *nw_cm2 pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 data is overflow
 *             - 5 read timeout
 *             - 6 only opt3002 can use this function
 * @note       none
 */
uint8_t opt3002_single_read(opt300x_handle_t *handle, uint16_t *raw, float *nw_cm2);

/**
 * @brief     set low limit
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] limit low limit
 * @return    status code
 *            - 0 success
 *            - 1 set low limit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t opt300x_set_low_limit(opt300x_handle_t *handle, uint16_t limit);

/**
 * @brief      get low limit
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *limit pointer to a low limit buffer
 * @return     status code
 *             - 0 success
 *             - 1 get low limit failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t opt300x_get_low_limit(opt300x_handle_t *handle, uint16_t *limit);

/**
 * @brief     set high limit
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] limit high limit
 * @return    status code
 *            - 0 success
 *            - 1 set high limit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t opt300x_set_high_limit(opt300x_handle_t *handle, uint16_t limit);

/**
 * @brief      get high limit
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *limit pointer to a high limit buffer
 * @return     status code
 *             - 0 success
 *             - 1 get high limit failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t opt300x_get_high_limit(opt300x_handle_t *handle, uint16_t *limit);

/**
 * @brief      convert the limit threshold to the register raw data
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[in]  lux input lux
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 opt3002 can't use this function
 * @note       none
 */
uint8_t opt300x_limit_convert_to_register(opt300x_handle_t *handle, float lux, uint16_t *reg);

/**
 * @brief      convert the register raw data to the limit threshold
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[in]  reg register raw data
 * @param[out] *lux pointer to a lux buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 opt3002 can't use this function
 * @note       none
 */
uint8_t opt300x_limit_convert_to_data(opt300x_handle_t *handle, uint16_t reg, float *lux);

/**
 * @brief      convert the limit threshold to the register raw data
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[in]  nw_cm2 input data
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 only opt3002 can use this function
 * @note       none
 */
uint8_t opt3002_limit_convert_to_register(opt300x_handle_t *handle, float nw_cm2, uint16_t *reg);

/**
 * @brief      convert the register raw data to the limit threshold
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[in]  reg register raw data
 * @param[out] *nw_cm2 pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 only opt3002 can use this function
 * @note       none
 */
uint8_t opt3002_limit_convert_to_data(opt300x_handle_t *handle, uint16_t reg, float *nw_cm2);

/**
 * @brief     set range
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] range set range
 * @return    status code
 *            - 0 success
 *            - 1 set range failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 type is invalid
 * @note      none
 */
uint8_t opt300x_set_range(opt300x_handle_t *handle, opt300x_range_t range);

/**
 * @brief      get range
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *range pointer to a range buffer
 * @return     status code
 *             - 0 success
 *             - 1 get range failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 type is invalid
 * @note       none
 */
uint8_t opt300x_get_range(opt300x_handle_t *handle, opt300x_range_t *range);

/**
 * @brief     set range
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] range set range
 * @return    status code
 *            - 0 success
 *            - 1 set range failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 only opt3002 can use this function
 * @note      none
 */
uint8_t opt3002_set_range(opt300x_handle_t *handle, opt3002_range_t range);

/**
 * @brief      get range
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *range pointer to a range buffer
 * @return     status code
 *             - 0 success
 *             - 1 get range failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 only opt3002 can use this function
 * @note       none
 */
uint8_t opt3002_get_range(opt300x_handle_t *handle, opt3002_range_t *range);

/**
 * @brief     set range
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] range set range
 * @return    status code
 *            - 0 success
 *            - 1 set range failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 only opt3005 can use this function
 * @note      none
 */
uint8_t opt3005_set_range(opt300x_handle_t *handle, opt3005_range_t range);

/**
 * @brief      get range
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *range pointer to a range buffer
 * @return     status code
 *             - 0 success
 *             - 1 get range failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 only opt3005 can use this function
 * @note       none
 */
uint8_t opt3005_get_range(opt300x_handle_t *handle, opt3005_range_t *range);

/**
 * @brief     set conversion time
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] t conversion time
 * @return    status code
 *            - 0 success
 *            - 1 set conversion time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t opt300x_set_conversion_time(opt300x_handle_t *handle, opt300x_conversion_time_t t);

/**
 * @brief      get conversion time
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *t pointer to a conversion time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get conversion time failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t opt300x_get_conversion_time(opt300x_handle_t *handle, opt300x_conversion_time_t *t);

/**
 * @brief     enable or disable interrupt latch
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt latch failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t opt300x_set_interrupt_latch(opt300x_handle_t *handle, opt300x_bool_t enable);

/**
 * @brief      get interrupt latch status
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt latch failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t opt300x_get_interrupt_latch(opt300x_handle_t *handle, opt300x_bool_t *enable);

/**
 * @brief     set interrupt pin polarity
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] polarity interrupt polarity
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt pin polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t opt300x_set_interrupt_pin_polarity(opt300x_handle_t *handle, opt300x_interrupt_polarity_t polarity);

/**
 * @brief      get interrupt pin polarity
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *polarity pointer to an interrupt polarity buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt pin latch failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t opt300x_get_interrupt_pin_polarity(opt300x_handle_t *handle, opt300x_interrupt_polarity_t *polarity);

/**
 * @brief     enable or disable mask exponent
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set mask exponent failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t opt300x_set_mask_exponent(opt300x_handle_t *handle, opt300x_bool_t enable);

/**
 * @brief      get mask exponent status
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mask exponent failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t opt300x_get_mask_exponent(opt300x_handle_t *handle, opt300x_bool_t *enable);

/**
 * @brief     set fault count
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] count fault count
 * @return    status code
 *            - 0 success
 *            - 1 set fault count failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t opt300x_set_fault_count(opt300x_handle_t *handle, opt300x_fault_count_t count);

/**
 * @brief      get fault count
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *count pointer to a fault count buffer
 * @return     status code
 *             - 0 success
 *             - 1 get fault count failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t opt300x_get_fault_count(opt300x_handle_t *handle, opt300x_fault_count_t *count);

/**
 * @}
 */

/**
 * @defgroup opt300x_extend_driver opt300x extend driver function
 * @brief    opt300x extend driver modules
 * @ingroup  opt300x_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] reg iic register address
 * @param[in] data sent data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t opt300x_set_reg(opt300x_handle_t *handle, uint8_t reg, uint16_t data);

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[in]  reg iic register address
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t opt300x_get_reg(opt300x_handle_t *handle, uint8_t reg, uint16_t *data);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
