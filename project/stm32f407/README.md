### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

GPIO Pin: INT PB0.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. OPT300X

#### 3.1 Command Instruction

1. Show opt300x chip and driver information.

   ```shell
   opt300x (-i | --information)
   ```

2. Show opt300x help.

   ```shell
   opt300x (-h | --help)
   ```

3. Show opt300x pin connections of the current board.

   ```shell
   opt300x (-p | --port)
   ```

4. Run opt300x register test.

   ```shell
   opt300x (-t reg | --test=reg) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>] [--addr=<VCC | GND | SCL | SDA>]
   ```

5. Run opt300x read test, num is test times.

   ```shell
   opt300x (-t read | --test=read) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>] [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]
   ```

6. Run opt300x interrupt test, num is test times, low is the interrupt low threshold, high is the interrupt high threshold.

   ```shell
   opt300x (-t int | --test=int) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>] [--addr=<VCC | GND | SCL | SDA>] [--times=<num>] [--low-threshold=<low>] [--high-threshold=<high>]
   ```

7. Run opt300x read function, num is read times.

   ```shell
   opt300x (-e read | --example=read) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>] [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]
   ```
8. Run opt300x shot function, num is read times.

   ```shell
   opt300x (-e shot | --example=shot) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>] [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]
   ```
   
9. Run opt300x interrupt function, num is read times, low is the interrupt low threshold, high is the interrupt high threshold.

   ```shell
   opt300x (-e int | --example=int) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>] [--addr=<VCC | GND | SCL | SDA>] [--times=<num>] [--low-threshold=<low>] [--high-threshold=<high>]
   ```

#### 3.2 Command Example

```shell
opt300x -i

opt300x: chip is Texas Instruments OPT300X.
opt300x: manufacturer is Texas Instruments.
opt300x: interface is IIC.
opt300x: driver version is 1.0.
opt300x: min supply voltage is 1.6V.
opt300x: max supply voltage is 3.6V.
opt300x: max current is 0.01mA.
opt300x: max temperature is 85.0C.
opt300x: min temperature is -40.0C.
```

```shell
opt300x -p

opt300x: SCL connected to GPIOB PIN8.
opt300x: SDA connected to GPIOB PIN9.
opt300x: INT connected to GPIOB PIN0.
```

```shell
opt300x -t reg --type=OPT3001 --addr=GND

opt300x: chip is Texas Instruments OPT300X.
opt300x: manufacturer is Texas Instruments.
opt300x: interface is IIC.
opt300x: driver version is 1.0.
opt300x: min supply voltage is 1.6V.
opt300x: max supply voltage is 3.6V.
opt300x: max current is 0.01mA.
opt300x: max temperature is 85.0C.
opt300x: min temperature is -40.0C.
opt300x: start register test.
opt300x: opt300x_set_type/opt300x_get_type test.
opt300x: set type opt3001.
opt300x: check type ok.
opt300x: set type opt3002.
opt300x: check type ok.
opt300x: set type opt3004.
opt300x: check type ok.
opt300x: set type opt3005.
opt300x: check type ok.
opt300x: set type opt3006.
opt300x: check type ok.
opt300x: set type opt3007.
opt300x: check type ok.
opt300x: opt300x_set_addr_pin/opt300x_get_addr_pin test.
opt300x: set addr pin ADDRESS_GND.
opt300x: check addr pin ok.
opt300x: set addr pin ADDRESS_VCC.
opt300x: check addr pin ok.
opt300x: set addr pin ADDRESS_SDA.
opt300x: check addr pin ok.
opt300x: set addr pin ADDRESS_SCL.
opt300x: check addr pin ok.
opt300x: opt300x_set_low_limit/opt300x_get_low_limit test.
opt300x: set low limit 63223.
opt300x: check low limit ok.
opt300x: opt300x_set_high_limit/opt300x_get_high_limit test.
opt300x: set high limit 37707.
opt300x: check high limit ok.
opt300x: opt300x_set_range/opt300x_get_range test.
opt300x: set range 40.95 lux.
opt300x: check range ok.
opt300x: set range 81.90 lux.
opt300x: check range ok.
opt300x: set range 163.80 lux.
opt300x: check range ok.
opt300x: set range 327.60 lux.
opt300x: check range ok.
opt300x: set range 655.20 lux.
opt300x: check range ok.
opt300x: set range 1310.40 lux.
opt300x: check range ok.
opt300x: set range 2620.80 lux.
opt300x: check range ok.
opt300x: set range 5241.60 lux.
opt300x: check range ok.
opt300x: set range 10483.20 lux.
opt300x: check range ok.
opt300x: set range 20966.40 lux.
opt300x: check range ok.
opt300x: set range 41932.80 lux.
opt300x: check range ok.
opt300x: set range 83865.60 lux.
opt300x: check range ok.
opt300x: set range auto range lux.
opt300x: check range ok.
opt300x: opt300x_set_conversion_time/opt300x_get_conversion_time test.
opt300x: set conversion time 100ms.
opt300x: check conversion time ok.
opt300x: set conversion time 800ms.
opt300x: check conversion time ok.
opt300x: opt300x_set_interrupt_latch/opt300x_get_interrupt_latch test.
opt300x: enable interrupt latch.
opt300x: check interrupt latch ok.
opt300x: disable interrupt latch.
opt300x: check interrupt latch ok.
opt300x: opt300x_set_interrupt_latch/opt300x_get_interrupt_latch test.
opt300x: set interrupt pin polarity low.
opt300x: check interrupt pin polarity ok.
opt300x: set interrupt pin polarity high.
opt300x: check interrupt pin polarity ok.
opt300x: opt300x_set_mask_exponent/opt300x_get_mask_exponent test.
opt300x: enable mask exponent.
opt300x: check mask exponent ok.
opt300x: disable mask exponent.
opt300x: check mask exponent ok.
opt300x: opt300x_set_fault_count/opt300x_get_fault_count test.
opt300x: set fault count one.
opt300x: check fault count ok.
opt300x: set fault count two.
opt300x: check fault count ok.
opt300x: set fault count four.
opt300x: check fault count ok.
opt300x: set fault count eight.
opt300x: check fault count ok.
opt300x: opt300x_limit_convert_to_register/opt300x_limit_convert_to_data test.
opt300x: set lux 640.90.
opt300x: check lux 640.80.
opt300x: finish register test.
```

```shell
opt300x -t read --type=OPT3001 --addr=GND --times=3

opt300x: chip is Texas Instruments OPT300X.
opt300x: manufacturer is Texas Instruments.
opt300x: interface is IIC.
opt300x: driver version is 1.0.
opt300x: min supply voltage is 1.6V.
opt300x: max supply voltage is 3.6V.
opt300x: max current is 0.01mA.
opt300x: max temperature is 85.0C.
opt300x: min temperature is -40.0C.
opt300x: start read test.
opt300x: continuous read test.
opt300x: 387.52 lux.
opt300x: 388.16 lux.
opt300x: 383.52 lux.
opt300x: single read test.
opt300x: 383.36 lux.
opt300x: 383.36 lux.
opt300x: 383.36 lux.
opt300x: finish read test.
```

```shell
opt300x -t int --type=OPT3001 --addr=GND --times=3 --low-threshold=50.0 --high-threshold=100.0

opt300x: chip is Texas Instruments OPT300X.
opt300x: manufacturer is Texas Instruments.
opt300x: interface is IIC.
opt300x: driver version is 1.0.
opt300x: min supply voltage is 1.6V.
opt300x: max supply voltage is 3.6V.
opt300x: max current is 0.01mA.
opt300x: max temperature is 85.0C.
opt300x: min temperature is -40.0C.
opt300x: start interrupt test.
opt300x: irq high limit.
opt300x: 578.56 lux.
opt300x: irq high limit.
opt300x: 578.40 lux.
opt300x: irq high limit.
opt300x: 578.40 lux.
opt300x: finish interrupt test.
```

```shell
opt300x -e read --type=OPT3001 --addr=GND --times=3

opt300x: 1/3.
opt300x: read is 145.28 lux.
opt300x: 2/3.
opt300x: read is 150.48 lux.
opt300x: 3/3.
opt300x: read is 157.88 lux.
```

```shell
opt300x -e shot --type=OPT3001 --addr=GND --times=3

opt300x: 1/3.
opt300x: read is 79.20 lux.
opt300x: 2/3.
opt300x: read is 79.60 lux.
opt300x: 3/3.
opt300x: read is 82.64 lux.
```

```shell
opt300x -e int --type=OPT3001 --addr=GND --times=3 --low-threshold=50.0 --high-threshold=100.0

opt300x: 1/3.
opt300x: read is 937.60 lux.
opt300x: irq high limit.
opt300x: find interrupt.
```

```shell
opt300x -h

Usage:
  opt300x (-i | --information)
  opt300x (-h | --help)
  opt300x (-p | --port)
  opt300x (-t reg | --test=reg) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>] [--addr=<VCC | GND | SCL | SDA>]
  opt300x (-t read | --test=read) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>] [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]
  opt300x (-t int | --test=int) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>] [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]
          [--low-threshold=<low>] [--high-threshold=<high>]
  opt300x (-e read | --example=read) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>] [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]
  opt300x (-e shot | --example=shot) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>] [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]
  opt300x (-e int | --example=int) [--type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>] [--addr=<VCC | GND | SCL | SDA>] [--times=<num>]
          [--low-threshold=<low>] [--high-threshold=<high>]

Options:
      --addr=<VCC | GND | SCL | SDA>    Set the addr pin.([default: GND])
  -e <read | shot | int>, --example=<read | shot | int>
                                        Run the driver example.
  -h, --help                            Show the help.
      --high-threshold=<high>           Set the interrupt high threshold.([default: 100.0])
  -i, --information                     Show the chip information.
      --low-threshold=<low>             Set the interrupt low threshold.([default: 50.0])
  -p, --port                            Display the pin connections of the current board.
  -t <reg | read | int>, --test=<reg | read | int>
                                        Run the driver test.
      --type=<OPT3001 | OPT3002 | OPT3004 | OPT3005 | OPT3006 | OPT3007>
                                        Set the chip type.([default: OPT3001])
      --times=<num>                     Set the running times.([default: 3])
```

