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
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-08-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/08/30  <td>1.0      <td>Shifeng Li  <td>format the code
 * </table>
 */

#include "driver_opt300x_interrupt_test.h"
#include "driver_opt300x_read_test.h"
#include "driver_opt300x_register_test.h"
#include "driver_opt300x_interrupt.h"
#include "driver_opt300x_shot.h"
#include "driver_opt300x_basic.h"
#include "gpio.h"
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t (*g_gpio_irq)(void) = NULL;        /**< gpio irq */
volatile uint8_t g_flag;                   /**< interrupt flag */

/**
 * @brief     interface receive callback
 * @param[in] type irq type
 * @note      none
 */
void a_callback(uint8_t type)
{
    switch (type)
    {
        case OPT300X_INTERRUPT_HIGH_LIMIT :
        {
            g_flag = 1;
            opt300x_interface_debug_print("opt300x: irq high limit.\n");
            
            break;
        }
        case OPT300X_INTERRUPT_LOW_LIMIT :
        {
            g_flag = 1;
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
 * @brief     opt300x full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t opt300x(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"high-threshold", required_argument, NULL, 2},
        {"low-threshold", required_argument, NULL, 3},
        {"type", required_argument, NULL, 4},
        {"times", required_argument, NULL, 5},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    opt300x_address_t addr = OPT300X_ADDRESS_GND;
    opt300x_t chip_type = OPT3001;
    float high_threshold = 100.0f;
    float low_threshold = 50.0f;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("GND", optarg) == 0)
                {
                    addr = OPT300X_ADDRESS_GND;
                }
                else if (strcmp("VCC", optarg) == 0)
                {
                    addr = OPT300X_ADDRESS_VCC;
                }
                else if (strcmp("SCL", optarg) == 0)
                {
                    addr = OPT300X_ADDRESS_SCL;
                }
                else if (strcmp("SDA", optarg) == 0)
                {
                    addr = OPT300X_ADDRESS_SDA;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* high threshold */
            case 2 :
            {
                high_threshold = (float)atof(optarg);
                
                break;
            }
             
            /* low threshold */
            case 3 :
            {
                low_threshold = (float)atof(optarg);
                
                break;
            }
            
            /* type */
            case 4 :
            {
                /* set the chip type */
                if (strcmp("OPT3001", optarg) == 0)
                {
                    chip_type = OPT3001;
                }
                else if (strcmp("OPT3002", optarg) == 0)
                {
                    chip_type = OPT3002;
                }
                else if (strcmp("OPT3004", optarg) == 0)
                {
                    chip_type = OPT3004;
                }
                else if (strcmp("OPT3005", optarg) == 0)
                {
                    chip_type = OPT3005;
                }
                else if (strcmp("OPT3006", optarg) == 0)
                {
                    chip_type = OPT3006;
                }
                else if (strcmp("OPT3007", optarg) == 0)
                {
                    chip_type = OPT3007;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* running times */
            case 5 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (opt300x_register_test(chip_type, addr) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (opt300x_read_test(chip_type, addr, times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_int", type) == 0)
    {
        uint8_t res;
        
        /* gpio init */
        g_gpio_irq = opt300x_interrupt_test_irq_handler;
        res = gpio_interrupt_init();
        if (res != 0)
        {
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* run interrupt test */
        res = opt300x_interrupt_test(chip_type, addr, low_threshold, high_threshold, times);
        if (res != 0)
        {
            (void)gpio_interrupt_deinit();
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* gpio deinit */
        (void)gpio_interrupt_deinit();
        g_gpio_irq = NULL;
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float lux;
        float nw_cm2;
        
        /* basic init */
        res = opt300x_basic_init(chip_type, addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            opt300x_interface_delay_ms(1000);
            
            if (chip_type != OPT3002)
            {
                /* read data */
                res = opt300x_basic_read(&lux);
                if (res != 0)
                {
                    (void)opt300x_basic_deinit();
                    
                    return 1;
                }
                
                /* output */
                opt300x_interface_debug_print("opt300x: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
                opt300x_interface_debug_print("opt300x: read is %0.2f lux.\n", lux);
            }
            else
            {
                /* read data */
                res = opt3002_basic_read(&nw_cm2);
                if (res != 0)
                {
                    (void)opt300x_basic_deinit();
                    
                    return 1;
                }
                
                /* output */
                opt300x_interface_debug_print("opt300x: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
                opt300x_interface_debug_print("opt300x: read is %0.2f nW/cm2.\n", nw_cm2);
            }
        }
        
        /* basic deinit */
        (void)opt300x_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_shot", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float lux;
        float nw_cm2;
        
        /* shot init */
        res = opt300x_shot_init(chip_type, addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            opt300x_interface_delay_ms(1000);
            
            if (chip_type != OPT3002)
            {
                /* read data */
                res = opt300x_shot_read(&lux);
                if (res != 0)
                {
                    (void)opt300x_shot_deinit();
                    
                    return 1;
                }
                
                /* output */
                opt300x_interface_debug_print("opt300x: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
                opt300x_interface_debug_print("opt300x: read is %0.2f lux.\n", lux);
            }
            else
            {
                /* read data */
                res = opt3002_shot_read(&nw_cm2);
                if (res != 0)
                {
                    (void)opt300x_shot_deinit();
                    
                    return 1;
                }
                
                /* output */
                opt300x_interface_debug_print("opt300x: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
                opt300x_interface_debug_print("opt300x: read is %0.2f nW/cm2.\n", nw_cm2);
            }
        }
        
        /* shot deinit */
        (void)opt300x_shot_deinit();
        
        return 0;
    }
    else if (strcmp("e_int", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float lux;
        float nw_cm2;
        
        /* gpio init */
        g_gpio_irq = opt300x_interrupt_irq_handler;
        res = gpio_interrupt_init();
        if (res != 0)
        {
            g_gpio_irq = NULL;
            (void)opt300x_interrupt_deinit();
            
            return 1;
        }
        
        /* interrupt init */
        res = opt300x_interrupt_init(chip_type, addr, low_threshold, high_threshold, a_callback);
        if (res != 0)
        {
            (void)gpio_interrupt_deinit();
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* loop */
        g_flag = 0;
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            opt300x_interface_delay_ms(1000);
            
            if (chip_type != OPT3002)
            {
                /* read data */
                res = opt300x_interrupt_read(&lux);
                if (res != 0)
                {
                    (void)opt300x_interrupt_deinit();
                    (void)gpio_interrupt_deinit();
                     g_gpio_irq = NULL;
                    
                    return 1;
                }
                
                /* output */
                opt300x_interface_debug_print("opt300x: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
                opt300x_interface_debug_print("opt300x: read is %0.2f lux.\n", lux);
            }
            else
            {
                /* read data */
                res = opt3002_interrupt_read(&nw_cm2);
                if (res != 0)
                {
                    (void)opt300x_interrupt_deinit();
                    (void)gpio_interrupt_deinit();
                     g_gpio_irq = NULL;
                    
                    return 1;
                }
                
                /* output */
                opt300x_interface_debug_print("opt300x: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
                opt300x_interface_debug_print("opt300x: read is %0.2f nW/cm2.\n", nw_cm2);
            }
            
            /* check interrupt */
            if (g_flag != 0)
            {
                opt300x_interface_debug_print("opt300x: find interrupt.\n");
                
                break;
            }
        }
        
        /* deinit */
        (void)opt300x_interrupt_deinit();
        (void)gpio_interrupt_deinit();
        g_gpio_irq = NULL;
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        opt300x_interface_debug_print("Usage:\n");
        opt300x_interface_debug_print("  opt300x (-i | --information)\n");
        opt300x_interface_debug_print("  opt300x (-h | --help)\n");
        opt300x_interface_debug_print("  opt300x (-p | --port)\n");
        opt300x_interface_debug_print("  opt300x (-t reg | --test=reg) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>]");
        opt300x_interface_debug_print(" [--addr=<VCC | GND | SCL | SDA>]\n");
        opt300x_interface_debug_print("  opt300x (-t read | --test=read) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>]");
        opt300x_interface_debug_print(" [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]\n");
        opt300x_interface_debug_print("  opt300x (-t int | --test=int) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>]");
        opt300x_interface_debug_print(" [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]\n");
        opt300x_interface_debug_print("          [--low-threshold=<low>] [--high-threshold=<high>]\n");
        opt300x_interface_debug_print("  opt300x (-e read | --example=read) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>]");
        opt300x_interface_debug_print(" [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]\n");
        opt300x_interface_debug_print("  opt300x (-e shot | --example=shot) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>]");
        opt300x_interface_debug_print(" [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]\n");
        opt300x_interface_debug_print("  opt300x (-e int | --example=int) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>]");
        opt300x_interface_debug_print(" [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]\n");
        opt300x_interface_debug_print("          [--low-threshold=<low>] [--high-threshold=<high>]\n");
        opt300x_interface_debug_print("\n");
        opt300x_interface_debug_print("Options:\n");
        opt300x_interface_debug_print("      --addr=<VCC | GND | SCL | SDA>    Set the addr pin.([default: GND])\n");
        opt300x_interface_debug_print("  -e <read | shot | int>, --example=<read | shot | int>\n");
        opt300x_interface_debug_print("                                        Run the driver example.\n");
        opt300x_interface_debug_print("  -h, --help                            Show the help.\n");
        opt300x_interface_debug_print("      --high-threshold=<high>           Set the interrupt high threshold.([default: 100.0])\n");
        opt300x_interface_debug_print("  -i, --information                     Show the chip information.\n");
        opt300x_interface_debug_print("      --low-threshold=<low>             Set the interrupt low threshold.([default: 50.0])\n");
        opt300x_interface_debug_print("  -p, --port                            Display the pin connections of the current board.\n");
        opt300x_interface_debug_print("  -t <reg | read | int>, --test=<reg | read | int>\n");
        opt300x_interface_debug_print("                                        Run the driver test.\n");
        opt300x_interface_debug_print("      --type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>\n");
        opt300x_interface_debug_print("                                        Set the chip type.([default: OPT3001])\n");
        opt300x_interface_debug_print("      --times=<num>                     Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        opt300x_info_t info;
        
        /* print opt300x info */
        opt300x_info(&info);
        opt300x_interface_debug_print("opt300x: chip is %s.\n", info.chip_name);
        opt300x_interface_debug_print("opt300x: manufacturer is %s.\n", info.manufacturer_name);
        opt300x_interface_debug_print("opt300x: interface is %s.\n", info.interface);
        opt300x_interface_debug_print("opt300x: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        opt300x_interface_debug_print("opt300x: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        opt300x_interface_debug_print("opt300x: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        opt300x_interface_debug_print("opt300x: max current is %0.2fmA.\n", info.max_current_ma);
        opt300x_interface_debug_print("opt300x: max temperature is %0.1fC.\n", info.temperature_max);
        opt300x_interface_debug_print("opt300x: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        opt300x_interface_debug_print("opt300x: SCL connected to GPIO3(BCM).\n");
        opt300x_interface_debug_print("opt300x: SDA connected to GPIO2(BCM).\n");
        opt300x_interface_debug_print("opt300x: INT connected to GPIO17(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = opt300x(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        opt300x_interface_debug_print("opt300x: run failed.\n");
    }
    else if (res == 5)
    {
        opt300x_interface_debug_print("opt300x: param is invalid.\n");
    }
    else
    {
        opt300x_interface_debug_print("opt300x: unknown status code.\n");
    }

    return 0;
}
