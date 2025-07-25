# 供STM32HAL使用的AD7606驱动

## 实现的功能

STM32F407 AD7606驱动代码，包含FFT

> [!IMPORTANT]
> 作者使用了基于CMake的编译工具链，[USART头文件](Core/Inc/usart.h)和[USART源文件](Core/Src/usart.c)中关于printf的定义可能需要修改，尤其是当开发者使用Keil工具链编译时
> 修改方法：使用CubeMX配置文件重新生成即可，记得切换对应的生成方式，如MDK-ARM

## 整体思路

ad7606通电后一直采集数据，STM32通过TIM4定时设置采样率，计数器到达重装值后触发中断，在中断中把数据存入数组。

## 注意事项

1. 在`while`中不要延时太久，否则会出现数据一直为0的现象

## 参考资料

ad7606是一款8通道16位ADC

|   测量范围   |   理论最小分辨率  |    模拟输入滤波器带宽  |
|---|---|---|
|   ±5V        |    0.153mv  |  15KHz（-3dB）|
|   ±10V        |   0.305mv  |  23KHz（-3dB）|

输入阻抗：1MΩ

8个通道采样率为200KSPS，能处理最高信号频率100KHz

模块可选SPI接口或16位并口，默认SPI

信噪比：90dB（典型值，无过采样，±10V） 89dB（典型值，无过采样，±5V）

最大耐受电压±16.5 V
