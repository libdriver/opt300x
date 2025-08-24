[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver OPT300X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/opt300x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

OPT300Xは、可視光の強度を測定するセンサーです。センサーのスペクトル応答は、人間の目の明所視応答と厳密に一致し、優れた赤外線遮断機能を備えています。OPT300Xは、人間の目に見える光の強度を測定するシングルチップの照度計です。高精度のスペクトル応答と強力な赤外線遮断機能により、OPT300Xは光源の種類に関わらず、人間の目に見える光の強度を正確に測定できます。また、優れた赤外線遮断機能は、意匠性を考慮して暗いガラスの下にセンサーを取り付けなければならない工業デザインにおいても、高精度の維持に役立ちます。OPT300Xは、人間に光に基づく体験を提供するシステム向けに設計されており、人間の目との一致や赤外線遮断機能が低いフォトダイオード、フォトレジスタ、その他の周囲光センサーの理想的な代替品です。

LibDriver OPT300Xは、LibDriverによって起動されたOPT300X全機能ドライバーであり、輝度の読み取り、輝度の割り込み検出、およびその他の機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver OPT300Xのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver OPT300X用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver OPT300Xドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver OPT300Xプログラミング例が含まれています。

/ docディレクトリには、LibDriver OPT300Xオフラインドキュメントが含まれています。

/ datasheetディレクトリには、OPT300Xデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/opt300x/index.html](https://www.libdriver.com/docs/opt300x/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。