[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver OPT300X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/opt300x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

OPT300X是一種量測可見光强度的感測器。 感測器的光譜響應與人眼的明視響應緊密匹配，並且包括顯著的紅外抑制。 OPT300X是一種單晶片照度計，量測人眼可見的光强度。 該器件的精確光譜響應和强大的紅外抑制能力使OPT300X能够精確量測人眼看到的光的强度，而不管光源如何。 當工業設計要求將感測器安裝在深色玻璃下以實現美學時，强大的紅外抑制也有助於保持高精度。 OPT300X專為為人類創造基於光的體驗的系統而設計，是光電二極體、光敏電阻或其他環境光感測器的理想首選替代品，具有較少的人眼匹配和紅外抑制。

LibDriver OPT300X是LibDriver推出的OPT300X全功能驅動，該驅動提供亮度讀取、亮度中斷檢測等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver OPT300X的源文件。

/interface目錄包含了LibDriver OPT300X與平台無關的IIC總線模板。

/test目錄包含了LibDriver OPT300X驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver OPT300X編程範例。

/doc目錄包含了LibDriver OPT300X離線文檔。

/datasheet目錄包含了OPT300X數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/opt300x/index.html](https://www.libdriver.com/docs/opt300x/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。