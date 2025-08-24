[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver OPT300X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/opt300x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

OPT300X는 가시광선의 세기를 측정하는 센서입니다. 센서의 스펙트럼 응답은 사람 눈의 명시적 응답과 매우 일치하며, 뛰어난 적외선 차단 기능을 갖추고 있습니다. OPT300X는 단일 칩 룩스 미터로, 사람 눈에 보이는 빛의 세기를 측정합니다. 정밀한 스펙트럼 응답과 강력한 적외선 차단 기능을 갖춘 OPT300X는 광원에 관계없이 사람 눈에 보이는 빛의 세기를 정확하게 측정합니다. 또한, 강력한 적외선 차단 기능은 산업 디자인상 미적인 측면을 고려하여 어두운 유리 아래에 센서를 장착해야 할 때에도 높은 정확도를 유지하는 데 도움이 됩니다. OPT300X는 빛 기반 경험을 제공하는 시스템을 위해 설계되었으며, 사람 눈의 일치도와 적외선 차단 기능이 낮은 포토다이오드, 포토레지스터 또는 기타 주변광 센서를 대체할 수 있는 이상적인 제품입니다.

LibDriver OPT300X은 LibDriver에서 출시한 OPT300X 전체 기능 드라이버입니다. 밝기 읽기, 밝기 중단 감지 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver OPT300X의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver OPT300X용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver OPT300X드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver OPT300X프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver OPT300X오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 OPT300X데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인IIC 버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/opt300x/index.html](https://www.libdriver.com/docs/opt300x/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.