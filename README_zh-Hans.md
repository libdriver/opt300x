[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver OPT300X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/opt300x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

OPT300X是一种测量可见光强度的传感器。传感器的光谱响应与人眼的明视响应紧密匹配，并且包括显著的红外抑制。OPT300X是一种单芯片照度计，测量人眼可见的光强度。该器件的精确光谱响应和强大的红外抑制能力使OPT300X能够精确测量人眼看到的光的强度，而不管光源如何。当工业设计要求将传感器安装在深色玻璃下以实现美学时，强大的红外抑制也有助于保持高精度。OPT300X专为为人类创造基于光的体验的系统而设计，是光电二极管、光敏电阻或其他环境光传感器的理想首选替代品，具有较少的人眼匹配和红外抑制。

LibDriver OPT300X是LibDriver推出的OPT300X全功能驱动，该驱动提供亮度读取、亮度中断检测等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver OPT300X的源文件。

/interface目录包含了LibDriver OPT300X与平台无关的IIC总线模板。

/test目录包含了LibDriver OPT300X驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver OPT300X编程范例。

/doc目录包含了LibDriver OPT300X离线文档。

/datasheet目录包含了OPT300X数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/opt300x/index.html](https://www.libdriver.com/docs/opt300x/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。