[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver OPT300X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/opt300x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The OPT300X is a sensor that measures the intensity of visible light. The spectral response of the sensor tightly matches the photopic response of the human eye and includes significant infrared rejection. The OPT300X is a single-chip lux meter, measuring the intensity of light as visible by the human eye. The precision spectral response and strong IR rejection of the device enables the OPT300X to accurately meter the intensity of light as seen by the human eye regardless of light source. The strong IR rejection also aids in maintaining high accuracy when industrial design calls for mounting the sensor under dark glass for aesthetics. The OPT300X is designed for systems that create light-based experiences for humans, and an ideal preferred replacement for photodiodes, photoresistors, or other ambient light sensors with less human eye matching and IR rejection.

LibDriver OPT300X is a full-featured driver of OPT300X launched by LibDriver.It provides brightness reading, brightness interrupt detection and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver OPT300X source files.

/interface includes LibDriver OPT300X IIC platform independent template.

/test includes LibDriver OPT300X driver test code and this code can test the chip necessary function simply.

/example includes LibDriver OPT300X sample code.

/doc includes LibDriver OPT300X offline document.

/datasheet includes OPT300X datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_opt300x_basic.h"

uint8_t res;
uint32_t i;
float lux;
float nw_cm2;

/* basic init */
res = opt300x_basic_init(OPT3001, OPT300X_ADDRESS_GND);
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
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
        opt300x_interface_debug_print("opt300x: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
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
        opt300x_interface_debug_print("opt300x: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
        opt300x_interface_debug_print("opt300x: read is %0.2f nW/cm2.\n", nw_cm2);
    }
    
    ...
}

...
    
/* basic deinit */
(void)opt300x_basic_deinit();

return 0;
```

#### example shot

```C
#include "driver_opt300x_shot.h"

uint8_t res;
uint32_t i;
float lux;
float nw_cm2;

/* shot init */
res = opt300x_shot_init(OPT3001, OPT300X_ADDRESS_GND);
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
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
        opt300x_interface_debug_print("opt300x: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
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
        opt300x_interface_debug_print("opt300x: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
        opt300x_interface_debug_print("opt300x: read is %0.2f nW/cm2.\n", nw_cm2);
    }
    
    ...
}

...
    
/* shot deinit */
(void)opt300x_shot_deinit();

return 0;
```

#### example interrupt

```C
#include "driver_opt300x_interrupt.h"

uint8_t res;
uint32_t i;
float lux;
float nw_cm2;
float high_threshold = 100.0f;
float low_threshold = 50.0f;
volatile uint8_t g_flag;

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
res = opt300x_interrupt_init(OPT3001, OPT300X_ADDRESS_GND, low_threshold, high_threshold, a_callback);
if (res != 0)
{
    (void)gpio_interrupt_deinit();
    g_gpio_irq = NULL;

    return 1;
}

...
    
/* loop */
g_flag = 0;
for (i = 0; i < 3; i++)
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
        opt300x_interface_debug_print("opt300x: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
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
        opt300x_interface_debug_print("opt300x: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
        opt300x_interface_debug_print("opt300x: read is %0.2f nW/cm2.\n", nw_cm2);
    }

    /* check interrupt */
    if (g_flag != 0)
    {
        opt300x_interface_debug_print("opt300x: find interrupt.\n");

        break;
    }
    
    ...
}

...
    
/* deinit */
(void)opt300x_interrupt_deinit();
(void)gpio_interrupt_deinit();
g_gpio_irq = NULL;

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/opt300x/index.html](https://www.libdriver.com/docs/opt300x/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.