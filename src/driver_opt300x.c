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
 * @file      driver_opt300x.c
 * @brief     driver opt300x source file
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

#include "driver_opt300x.h"
#include <math.h>

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Texas Instruments OPT300X"        /**< chip name */
#define MANUFACTURER_NAME         "Texas Instruments"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        1.6f                               /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                               /**< chip max supply voltage */
#define MAX_CURRENT               0.01f                              /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                             /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                              /**< chip max operating temperature */
#define DRIVER_VERSION            1000                               /**< driver version */

/**
 * @brief chip register definition
 */
#define OPT300X_REG_RESULT                 0x00        /**< result register */
#define OPT300X_REG_CONFIGURATION          0x01        /**< configuration register */
#define OPT300X_REG_LOW_LIMIT              0x02        /**< low limit register */
#define OPT300X_REG_HIGH_LIMIT             0x03        /**< high limit register */
#define OPT300X_REG_MANUFACTURER_ID        0x7E        /**< manufacturer id register */
#define OPT300X_REG_DEVICE_ID              0x7F        /**< device id register */

/**
 * @brief      read bytes
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[in]  reg iic register address
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_opt300x_iic_read(opt300x_handle_t *handle, uint8_t reg, uint16_t *data)
{
    uint8_t buf[2];
    
    memset(buf, 0, sizeof(uint8_t) * 2);                                        /* clear the buffer */
    if (handle->iic_read(handle->iic_addr, reg, (uint8_t *)buf, 2) != 0)        /* read data */
    {
        return 1;                                                               /* return error */
    }
    *data = (uint16_t)(((uint16_t)buf[0] << 8) | buf[1]);                       /* set data */
   
    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     write bytes
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] reg iic register address
 * @param[in] data sent data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_opt300x_iic_write(opt300x_handle_t *handle, uint8_t reg, uint16_t data)
{
    uint8_t buf[2];
  
    buf[0] = (data >> 8) & 0xFF;                                                 /* set MSB */
    buf[1] = data & 0xFF;                                                        /* set LSB */
    if (handle->iic_write(handle->iic_addr, reg, (uint8_t *)buf, 2) != 0)        /* write data */
    {
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

/**
 * @brief     set the chip type
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t opt300x_set_type(opt300x_handle_t *handle, opt300x_t type)
{
    if (handle == NULL)                  /* check handle */
    {
        return 2;                        /* return error */
    }
    
    handle->type = (uint8_t)type;        /* set chip type */
    
    return 0;                            /* success return 0 */
}

/**
 * @brief      get the iic chip type
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *type pointer to a chip type buffer
 * @return      status code
 *              - 0 success
 *              - 2 handle is NULL
 * @note        none
 */
uint8_t opt300x_get_type(opt300x_handle_t *handle, opt300x_t *type)
{
    if (handle == NULL)                     /* check handle */
    {
        return 2;                           /* return error */
    }
    
    *type = (opt300x_t)handle->type;        /* get iic address */
    
    return 0;                               /* success return 0 */
}

/**
 * @brief     set the iic address pin
 * @param[in] *handle pointer to an opt300x handle structure
 * @param[in] addr_pin chip iic address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t opt300x_set_addr_pin(opt300x_handle_t *handle, opt300x_address_t addr_pin)
{
    if (handle == NULL)                          /* check handle */
    {
        return 2;                                /* return error */
    }
    
    handle->iic_addr = (uint8_t)addr_pin;        /* set iic address */
    
    return 0;                                    /* success return 0 */
}

/**
 * @brief      get the iic address pin
 * @param[in]  *handle pointer to an opt300x handle structure
 * @param[out] *addr_pin pointer to a chip iic address pin buffer
 * @return      status code
 *              - 0 success
 *              - 2 handle is NULL
 * @note        none
 */
uint8_t opt300x_get_addr_pin(opt300x_handle_t *handle, opt300x_address_t *addr_pin)
{
    if (handle == NULL)                                     /* check handle */
    {
        return 2;                                           /* return error */
    }
    
    *addr_pin = (opt300x_address_t)handle->iic_addr;        /* get iic address */
 
    return 0;                                               /* success return 0 */
}

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
uint8_t opt300x_init(opt300x_handle_t *handle)
{
    uint8_t res;
    uint16_t id;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->debug_print == NULL)                                           /* check debug_print */
    {
        return 3;                                                              /* return error */
    }
    if (handle->iic_init == NULL)                                              /* check iic_init */
    {
        handle->debug_print("opt300x: iic_init is null.\n");                   /* iic_init is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->iic_deinit == NULL)                                            /* check iic_deinit */
    {
        handle->debug_print("opt300x: iic_deinit is null.\n");                 /* iic_deinit is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->iic_read == NULL)                                              /* check iic_read */
    {
        handle->debug_print("opt300x: iic_read is null.\n");                   /* iic_read is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->iic_write == NULL)                                             /* check iic_write */
    {
        handle->debug_print("opt300x: iic_write is null.\n");                  /* iic_write is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->delay_ms == NULL)                                              /* check delay_ms */
    {
        handle->debug_print("opt300x: delay_ms is null.\n");                   /* delay_ms is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->receive_callback == NULL)                                      /* check receive_callback */
    {
        handle->debug_print("opt300x: receive_callback is null.\n");           /* receive_callback is null */
        
        return 3;                                                              /* return error */
    }
    
    if (handle->iic_init() != 0)                                               /* iic init */
    {
        handle->debug_print("opt300x: iic init failed.\n");                    /* iic init failed */
        
        return 1;                                                              /* return error */
    }
    res = a_opt300x_iic_read(handle, OPT300X_REG_MANUFACTURER_ID, &id);        /* read id */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read id failed.\n");                     /* read id failed */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 4;                                                              /* return error */
    }
    if (id != 0x5449)                                                          /* check id */
    {
        handle->debug_print("opt300x: manufacturer id is invalid.\n");         /* manufacturer id is invalid */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 4;                                                              /* return error */
    }
    res = a_opt300x_iic_read(handle, OPT300X_REG_DEVICE_ID, &id);              /* read id */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read id failed.\n");                     /* read id failed */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 4;                                                              /* return error */
    }
    if (id != 0x3001)                                                          /* check id */
    {
        handle->debug_print("opt300x: device id is invalid.\n");               /* device id is invalid */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 4;                                                              /* return error */
    }
    handle->inited = 1;                                                        /* flag finish initialization */

    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_deinit(opt300x_handle_t *handle)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }   
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 4;                                                              /* return error */
    }
    prev &= ~(3 << 9);                                                         /* clear settings */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);        /* write configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");         /* write configuration failed */
        
        return 4;                                                              /* return error */
    }
    if (handle->iic_deinit() != 0)                                             /* iic deinit */
    {
        handle->debug_print("opt300x: iic deinit failed.\n");                  /* iic deinit failed */
        
        return 1;                                                              /* return error */
    }   
    handle->inited = 0;                                                        /* flag close */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_start_continuous_read(opt300x_handle_t *handle)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    prev &= ~(3 << 9);                                                         /* clear settings */
    prev |= 2 << 9;                                                            /* continuous conversions */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);        /* write configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");         /* write configuration failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_stop_continuous_read(opt300x_handle_t *handle)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    prev &= ~(3 << 9);                                                         /* clear settings */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);        /* write configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");         /* write configuration failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_continuous_read(opt300x_handle_t *handle, uint16_t *raw, float *lux)
{
    uint8_t res;
    uint8_t exponent;
    uint16_t fractional;
    uint16_t prev;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (handle->type == (uint8_t)OPT3002)                                    /* check type */
    {
        handle->debug_print("opt300x: opt3002 can't use this function.\n");  /* opt3002 can't use this function */
        
        return 5;                                                            /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);      /* read configuration */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");        /* read configuration failed */
        
        return 1;                                                            /* return error */
    }
    if ((prev & (1 << 8)) != 0)                                              /* check ovf bit */
    {
        handle->debug_print("opt300x: data is overflow.\n");                 /* data is overflow */
        
        return 4;                                                            /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_RESULT, raw);               /* read result */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("opt300x: read result failed.\n");               /* read result failed */
        
        return 1;                                                            /* return error */
    }
    exponent = ((*raw) >> 12) & 0xF;                                         /* set exponent */
    fractional = (*raw) & 0xFFF;                                             /* set fractional */
    if (handle->type == (uint8_t)OPT3005)                                    /* opt3005 */
    {
        *lux = 0.02f * powf(2.0f, (float)exponent) * ((float)fractional);    /* calculate lux */
    }
    else                                                                     /* the others */
    {
        *lux = 0.01f * powf(2.0f, (float)exponent) * ((float)fractional);    /* calculate lux */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t opt3002_continuous_read(opt300x_handle_t *handle, uint16_t *raw, float *nw_cm2)
{
    uint8_t res;
    uint8_t exponent;
    uint16_t fractional;
    uint16_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    if (handle->type != (uint8_t)OPT3002)                                             /* check type */
    {
        handle->debug_print("opt300x: only opt3002 can use this function.\n");        /* only opt3002 can use this function */
        
        return 5;                                                                     /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);               /* read configuration */
    if (res != 0)                                                                     /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");                 /* read configuration failed */
        
        return 1;                                                                     /* return error */
    }
    if ((prev & (1 << 8)) != 0)                                                       /* check ovf bit */
    {
        handle->debug_print("opt300x: data is overflow.\n");                          /* data is overflow */
        
        return 4;                                                                     /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_RESULT, raw);                        /* read result */
    if (res != 0)                                                                     /* check the result */
    {
        handle->debug_print("opt300x: read result failed.\n");                        /* read result failed */
        
        return 1;                                                                     /* return error */
    }
    exponent = ((*raw) >> 12) & 0xF;                                                  /* set exponent */
    fractional = (*raw) & 0xFFF;                                                      /* set fractional */
    *nw_cm2 = 1.2f * powf(2.0f, (float)exponent) * ((float)fractional);               /* calculate nw/cm2 */
    
    return 0;                                                                         /* success return 0 */
}

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
uint8_t opt300x_single_read(opt300x_handle_t *handle, uint16_t *raw, float *lux)
{
    uint8_t res;
    uint8_t exponent;
    uint16_t fractional;
    uint16_t prev;
    uint32_t timeout = 500;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (handle->type == (uint8_t)OPT3002)                                        /* check type */
    {
        handle->debug_print("opt300x: opt3002 can't use this function.\n");      /* opt3002 can't use this function */
        
        return 6;                                                                /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);          /* read configuration */
    if (res != 0)                                                                /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");            /* read configuration failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(3 << 9);                                                           /* clear settings */
    prev |= (1 << 9);                                                            /* clear settings */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);          /* write configuration */
    if (res != 0)                                                                /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");           /* write configuration failed */
        
        return 1;                                                                /* return error */
    }
    
    while (timeout != 0)                                                         /* 5s */
    {
        handle->delay_ms(10);                                                    /* delay 10ms */
        timeout--;                                                               /* timeout-- */
        res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);      /* read configuration */
        if (res != 0)                                                            /* check the result */
        {
            handle->debug_print("opt300x: read configuration failed.\n");        /* read configuration failed */
            
            return 1;                                                            /* return error */
        }
        if ((prev & (1 << 7)) != 0)                                              /* check ready bit */
        {
            break;                                                               /* break */
        }
        if ((prev & (1 << 8)) != 0)                                              /* check ovf bit */
        {
            handle->debug_print("opt300x: data is overflow.\n");                 /* data is overflow */
            
            return 4;                                                            /* return error */
        }
    }
    if (timeout == 0)                                                            /* check timeout */
    {
        handle->debug_print("opt300x: read timeout.\n");                         /* read timeout */
        
        return 5;                                                                /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_RESULT, raw);                   /* read result */
    if (res != 0)                                                                /* check the result */
    {
        handle->debug_print("opt300x: read result failed.\n");                   /* read result failed */
        
        return 1;                                                                /* return error */
    }
    exponent = ((*raw) >> 12) & 0xF;                                             /* set exponent */
    fractional = (*raw) & 0xFFF;                                                 /* set fractional */
    if (handle->type == (uint8_t)OPT3005)                                        /* opt3005 */
    {
        *lux = 0.02f * powf(2.0f, (float)exponent) * ((float)fractional);        /* calculate lux */
    }
    else                                                                         /* the others */
    {
        *lux = 0.01f * powf(2.0f, (float)exponent) * ((float)fractional);        /* calculate lux */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t opt3002_single_read(opt300x_handle_t *handle, uint16_t *raw, float *nw_cm2)
{
    uint8_t res;
    uint8_t exponent;
    uint16_t fractional;
    uint16_t prev;
    uint32_t timeout = 500;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (handle->type != (uint8_t)OPT3002)                                        /* check type */
    {
        handle->debug_print("opt300x: only opt3002 can use this function.\n");   /* only opt3002 can use this function */
        
        return 6;                                                                /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);          /* read configuration */
    if (res != 0)                                                                /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");            /* read configuration failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(3 << 9);                                                           /* clear settings */
    prev |= (1 << 9);                                                            /* clear settings */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);          /* write configuration */
    if (res != 0)                                                                /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");           /* write configuration failed */
        
        return 1;                                                                /* return error */
    }
    
    while (timeout != 0)                                                         /* 5s */
    {
        handle->delay_ms(10);                                                    /* delay 10ms */
        timeout--;                                                               /* timeout-- */
        res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);      /* read configuration */
        if (res != 0)                                                            /* check the result */
        {
            handle->debug_print("opt300x: read configuration failed.\n");        /* read configuration failed */
            
            return 1;                                                            /* return error */
        }
        if ((prev & (1 << 7)) != 0)                                              /* check ready bit */
        {
            break;                                                               /* break */
        }
        if ((prev & (1 << 8)) != 0)                                              /* check ovf bit */
        {
            handle->debug_print("opt300x: data is overflow.\n");                 /* data is overflow */
            
            return 4;                                                            /* return error */
        }
    }
    if (timeout == 0)                                                            /* check timeout */
    {
        handle->debug_print("opt300x: read timeout.\n");                         /* read timeout */
        
        return 5;                                                                /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_RESULT, raw);                   /* read result */
    if (res != 0)                                                                /* check the result */
    {
        handle->debug_print("opt300x: read result failed.\n");                   /* read result failed */
        
        return 1;                                                                /* return error */
    }
    exponent = ((*raw) >> 12) & 0xF;                                             /* set exponent */
    fractional = (*raw) & 0xFFF;                                                 /* set fractional */
    *nw_cm2 = 1.2f * powf(2.0f, (float)exponent) * ((float)fractional);          /* calculate nw/cm2 */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t opt300x_set_low_limit(opt300x_handle_t *handle, uint16_t limit)
{
    uint8_t res;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_opt300x_iic_write(handle, OPT300X_REG_LOW_LIMIT, limit);        /* write low limit */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("opt300x: write low limit failed.\n");          /* write low limit failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t opt300x_get_low_limit(opt300x_handle_t *handle, uint16_t *limit)
{
    uint8_t res;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_LOW_LIMIT, limit);        /* read low limit */
    if (res != 0)                                                          /* check the result */
    {
        handle->debug_print("opt300x: read low limit failed.\n");          /* read low limit failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t opt300x_set_high_limit(opt300x_handle_t *handle, uint16_t limit)
{
    uint8_t res;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_opt300x_iic_write(handle, OPT300X_REG_HIGH_LIMIT, limit);        /* write high limit */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("opt300x: write high limit failed.\n");          /* write high limit failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t opt300x_get_high_limit(opt300x_handle_t *handle, uint16_t *limit)
{
    uint8_t res;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_HIGH_LIMIT, limit);        /* read high limit */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("opt300x: read high limit failed.\n");          /* read high limit failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t opt300x_limit_convert_to_register(opt300x_handle_t *handle, float lux, uint16_t *reg)
{
    uint16_t remain;
    int xp;
    float f;
    float fraction;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (handle->type == (uint8_t)OPT3002)                                    /* check type */
    {
        handle->debug_print("opt300x: opt3002 can't use this function.\n");  /* opt3002 can't use this function */
        
        return 4;                                                            /* return error */
    }
    
    if (handle->type == (uint8_t)OPT3005)                                    /* opt3005 */
    {
        f = lux / 0.02f;                                                     /* convert */
    }
    else
    {
        f = lux / 0.01f;                                                     /* convert */
    }
    fraction = frexpf(f, &xp);                                               /* run frexp */
    while ((xp > 0xB) || (fraction < 4095.0f))                               /* adjust params */
    {
        if (xp == 0)                                                         /* reach the min */
        {
            break;                                                           /* break */
        }
        if (fraction * 2.0f > 4095.0f)                                       /* reach the max */
        {
            break;                                                           /* break */
        }
        xp--;                                                                /* xp-- */
        fraction *= 2.0f;                                                    /* fraction * 2 */
    }
    remain = (uint16_t)fraction;                                             /* get the integer part */
    *reg = (((uint16_t)(xp & 0xF)) << 12) | (remain & 0xFFF);                /* convert real data to register data */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t opt300x_limit_convert_to_data(opt300x_handle_t *handle, uint16_t reg, float *lux)
{
    uint8_t exponent;
    uint16_t fractional;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (handle->type == (uint8_t)OPT3002)                                    /* check type */
    {
        handle->debug_print("opt300x: opt3002 can't use this function.\n");  /* opt3002 can't use this function */
        
        return 4;                                                            /* return error */
    }
    
    exponent = (reg >> 12) & 0xF;                                            /* set exponent */
    fractional = reg & 0xFFF;                                                /* set fractional */
    if (handle->type == (uint8_t)OPT3005)                                    /* opt3005 */
    {
        *lux = 0.02f * powf(2.0f, (float)exponent) * ((float)fractional);    /* calculate lux */
    }
    else                                                                     /* the others */
    {
        *lux = 0.01f * powf(2.0f, (float)exponent) * ((float)fractional);    /* calculate lux */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t opt3002_limit_convert_to_register(opt300x_handle_t *handle, float nw_cm2, uint16_t *reg)
{
    uint16_t remain;
    int xp;
    float f;
    float fraction;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    if (handle->type != (uint8_t)OPT3002)                                             /* check type */
    {
        handle->debug_print("opt300x: only opt3002 can use this function.\n");        /* only opt3002 can use this function */
        
        return 4;                                                                     /* return error */
    }
    
    f = nw_cm2 / 1.2f;                                                                /* convert */
    fraction = frexpf(f, &xp);                                                        /* run frexp */
    while ((xp > 0xB) || (fraction < 4095.0f))                                        /* adjust params */
    {
        if (xp == 0)                                                                  /* reach the min */
        {
            break;                                                                    /* break */
        }
        if (fraction * 2.0f > 4095.0f)                                                /* reach the max */
        {
            break;                                                                    /* break */
        }
        xp--;                                                                         /* xp-- */
        fraction *= 2.0f;                                                             /* fraction * 2 */
    }
    remain = (uint16_t)fraction;                                                      /* get the integer part */
    *reg = (((uint16_t)(xp & 0xF)) << 12) | (remain & 0xFFF);                         /* convert real data to register data */
    
    return 0;                                                                         /* success return 0 */
}

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
uint8_t opt3002_limit_convert_to_data(opt300x_handle_t *handle, uint16_t reg, float *nw_cm2)
{
    uint8_t exponent;
    uint16_t fractional;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    if (handle->type != (uint8_t)OPT3002)                                             /* check type */
    {
        handle->debug_print("opt300x: only opt3002 can use this function.\n");        /* only opt3002 can use this function */
        
        return 4;                                                                     /* return error */
    }
    
    exponent = (reg >> 12) & 0xF;                                                     /* set exponent */
    fractional = reg & 0xFFF;                                                         /* set fractional */
    *nw_cm2 = 1.2f * powf(2.0f, (float)exponent) * ((float)fractional);               /* calculate lux */
    
    return 0;                                                                         /* success return 0 */
}

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
uint8_t opt300x_set_range(opt300x_handle_t *handle, opt300x_range_t range)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    if (handle->type == (uint8_t)OPT3002)                                      /* check type */
    {
        handle->debug_print("opt300x: opt3002 can't use this function.\n");    /* opt3002 can't use this function */
        
        return 4;                                                              /* return error */
    }
    if (handle->type == (uint8_t)OPT3005)                                      /* check type */
    {
        handle->debug_print("opt300x: opt3005 can't use this function.\n");    /* opt3005 can't use this function */
        
        return 4;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    prev &= ~(0xF << 12);                                                      /* clear settings */
    prev |= range << 12;                                                       /* set range */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);        /* write configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");         /* write configuration failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_get_range(opt300x_handle_t *handle, opt300x_range_t *range)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    if (handle->type == (uint8_t)OPT3002)                                      /* check type */
    {
        handle->debug_print("opt300x: opt3002 can't use this function.\n");    /* opt3002 can't use this function */
        
        return 4;                                                              /* return error */
    }
    if (handle->type == (uint8_t)OPT3005)                                      /* check type */
    {
        handle->debug_print("opt300x: opt3005 can't use this function.\n");    /* opt3005 can't use this function */
        
        return 4;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    *range = (opt300x_range_t)((prev >> 12) & 0xF);                            /* set range */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt3002_set_range(opt300x_handle_t *handle, opt3002_range_t range)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    if (handle->type != (uint8_t)OPT3002)                                             /* check type */
    {
        handle->debug_print("opt300x: only opt3002 can use this function.\n");        /* only opt3002 can use this function */
        
        return 4;                                                                     /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);               /* read configuration */
    if (res != 0)                                                                     /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");                 /* read configuration failed */
        
        return 1;                                                                     /* return error */
    }
    prev &= ~(0xF << 12);                                                             /* clear settings */
    prev |= range << 12;                                                              /* set range */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);               /* write configuration */
    if (res != 0)                                                                     /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");                /* write configuration failed */
        
        return 1;                                                                     /* return error */
    }
    
    return 0;                                                                         /* success return 0 */
}

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
uint8_t opt3002_get_range(opt300x_handle_t *handle, opt3002_range_t *range)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    if (handle->type != (uint8_t)OPT3002)                                             /* check type */
    {
        handle->debug_print("opt300x: only opt3002 can use this function.\n");        /* only opt3002 can use this function */
        
        return 4;                                                                     /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);               /* read configuration */
    if (res != 0)                                                                     /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");                 /* read configuration failed */
        
        return 1;                                                                     /* return error */
    }
    *range = (opt3002_range_t)((prev >> 12) & 0xF);                                   /* set range */
    
    return 0;                                                                         /* success return 0 */
}

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
uint8_t opt3005_set_range(opt300x_handle_t *handle, opt3005_range_t range)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    if (handle->type != (uint8_t)OPT3005)                                             /* check type */
    {
        handle->debug_print("opt300x: only opt3005 can use this function.\n");        /* only opt3005 can use this function */
        
        return 4;                                                                     /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);               /* read configuration */
    if (res != 0)                                                                     /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");                 /* read configuration failed */
        
        return 1;                                                                     /* return error */
    }
    prev &= ~(0xF << 12);                                                             /* clear settings */
    prev |= range << 12;                                                              /* set range */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);               /* write configuration */
    if (res != 0)                                                                     /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");                /* write configuration failed */
        
        return 1;                                                                     /* return error */
    }
    
    return 0;                                                                         /* success return 0 */
}

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
uint8_t opt3005_get_range(opt300x_handle_t *handle, opt3005_range_t *range)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    if (handle->type != (uint8_t)OPT3005)                                             /* check type */
    {
        handle->debug_print("opt300x: only opt3005 can use this function.\n");        /* only opt3005 can use this function */
        
        return 4;                                                                     /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);               /* read configuration */
    if (res != 0)                                                                     /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");                 /* read configuration failed */
        
        return 1;                                                                     /* return error */
    }
    *range = (opt3005_range_t)((prev >> 12) & 0xF);                                   /* set range */
    
    return 0;                                                                         /* success return 0 */
}

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
uint8_t opt300x_set_conversion_time(opt300x_handle_t *handle, opt300x_conversion_time_t t)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    prev &= ~(1 << 11);                                                        /* clear settings */
    prev |= t << 11;                                                           /* set time */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);        /* write configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");         /* write configuration failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_get_conversion_time(opt300x_handle_t *handle, opt300x_conversion_time_t *t)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    *t = (opt300x_conversion_time_t)((prev >> 11) & 0x01);                     /* set time */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_set_interrupt_latch(opt300x_handle_t *handle, opt300x_bool_t enable)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    prev &= ~(1 << 4);                                                         /* clear settings */
    prev |= enable << 4;                                                       /* set bool */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);        /* write configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");         /* write configuration failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_get_interrupt_latch(opt300x_handle_t *handle, opt300x_bool_t *enable)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    *enable = (opt300x_bool_t)((prev >> 4) & 0x01);                            /* set bool */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_set_interrupt_pin_polarity(opt300x_handle_t *handle, opt300x_interrupt_polarity_t polarity)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    prev &= ~(1 << 3);                                                         /* clear settings */
    prev |= polarity << 3;                                                     /* set polarity */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);        /* write configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");         /* write configuration failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_get_interrupt_pin_polarity(opt300x_handle_t *handle, opt300x_interrupt_polarity_t *polarity)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    *polarity = (opt300x_interrupt_polarity_t)((prev >> 3) & 0x01);            /* set polarity */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_set_mask_exponent(opt300x_handle_t *handle, opt300x_bool_t enable)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    prev &= ~(1 << 2);                                                         /* clear settings */
    prev |= enable << 2;                                                       /* set bool */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);        /* write configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");         /* write configuration failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_get_mask_exponent(opt300x_handle_t *handle, opt300x_bool_t *enable)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    *enable = (opt300x_bool_t)((prev >> 2) & 0x01);                            /* set bool */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_set_fault_count(opt300x_handle_t *handle, opt300x_fault_count_t count)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    prev &= ~(3 << 0);                                                         /* clear settings */
    prev |= count << 0;                                                        /* set count */
    res = a_opt300x_iic_write(handle, OPT300X_REG_CONFIGURATION, prev);        /* write configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: write configuration failed.\n");         /* write configuration failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_get_fault_count(opt300x_handle_t *handle, opt300x_fault_count_t *count)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    *count = (opt300x_fault_count_t)((prev >> 0) & 0x03);                      /* set count */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_irq_handler(opt300x_handle_t *handle)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_opt300x_iic_read(handle, OPT300X_REG_CONFIGURATION, &prev);        /* read configuration */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("opt300x: read configuration failed.\n");          /* read configuration failed */
        
        return 1;                                                              /* return error */
    }
    
    if ((prev & (1 << 6)) != 0)                                                /* check flag */
    {
        if (handle->receive_callback != NULL)                                  /* if not null */
        {
            handle->receive_callback(OPT300X_INTERRUPT_HIGH_LIMIT);            /* run the callback */
        }
    }
    if ((prev & (1 << 5)) != 0)                                                /* check flag */
    {
        if (handle->receive_callback != NULL)                                  /* if not null */
        {
            handle->receive_callback(OPT300X_INTERRUPT_LOW_LIMIT);             /* run the callback */
        }
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t opt300x_set_reg(opt300x_handle_t *handle, uint8_t reg, uint16_t data)
{
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }
    
    if (a_opt300x_iic_write(handle, reg, data) != 0)            /* write data */
    {
        handle->debug_print("opt300x: write failed.\n");        /* write failed */
        
        return 1;                                               /* return error */
    }
    
    return 0;                                                   /* success return 0 */
}

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
uint8_t opt300x_get_reg(opt300x_handle_t *handle, uint8_t reg, uint16_t *data)
{
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    }
    
    if (a_opt300x_iic_read(handle, reg, data) != 0)            /* read data */
    {
        handle->debug_print("opt300x: read failed.\n");        /* read failed */
        
        return 1;                                              /* return error */
    }
    
    return 0;                                                  /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an opt300x info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t opt300x_info(opt300x_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(opt300x_info_t));                        /* initialize opt300x info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
