/*
****************************************************************************
                
                PC11 -> RD(SCK)                                   OUT_PP        VERY_HIGH
                PA0  -> D7(MISO)                                  IPD
                PC12 -> CS                                        OUT_PP        VERY_HIGH
                PC10 -> RST                                       OUT_PP        VERY_HIGH
                PA1  -> CB(CONVST)                                OUT_PP        VERY_HIGH
                PA2  -> RANGE                                     OUT_PP        VERY_HIGH
                PC4 -> OS0                                        OUT_PP        VERY_HIGH
                PC5 -> OS1                                        OUT_PP        VERY_HIGH
                PC6 -> OS2                                        OUT_PP        VERY_HIGH
                PB15 -> BUSY                                      EXTI          FALLING
                GND -> GND                                        OUT_PP        VERY_HIGH
            
****************************************************************************
*/
#ifndef _ad7606_H_
#define _ad7606_H_
#include "stdint.h"
#include "string.h"
#include "stm32f4xx.h"
#include <stdio.h>
#include "gpio.h"
#include "tim.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "arm_math.h"
#include "arm_const_structs.h"
#include "arm_common_tables.h"

#define ENABLE_INT()     __set_PRIMASK(0) 
#define DISABLE_INT()    __set_PRIMASK(1) 

#define CH_NUM           8 
#define FIFO_SIZE        1*1024*2

#define uchar unsigned char
#define uint  unsigned int    
#define ulong  unsigned long int

#define AD_CS_LOW()                         CS_GPIO_Port->BSRR = CS_Pin << 16U
#define AD_CS_HIGH()                        CS_GPIO_Port->BSRR = CS_Pin

#define AD_RESET_LOW()                      RST_GPIO_Port->BSRR = RST_Pin << 16U
#define AD_RESET_HIGH()                     RST_GPIO_Port->BSRR = RST_Pin

#define AD_CONVST_LOW()                     CONVST_GPIO_Port->BSRR = CONVST_Pin << 16U
#define AD_CONVST_HIGH()                    CONVST_GPIO_Port->BSRR = CONVST_Pin  //CB--CONVST

#define AD_RANGE_5V()                       RANGE_GPIO_Port->BSRR = RANGE_Pin << 16U
#define AD_RANGE_10V()                      RANGE_GPIO_Port->BSRR = RANGE_Pin

#define AD_OS0_0()                          OS0_GPIO_Port->BSRR = OS0_Pin << 16U
#define AD_OS0_1()                          OS0_GPIO_Port->BSRR = OS0_Pin

#define AD_OS1_0()                          OS1_GPIO_Port->BSRR = OS1_Pin << 16U
#define AD_OS1_1()                          OS1_GPIO_Port->BSRR = OS1_Pin

#define AD_OS2_0()                          OS2_GPIO_Port->BSRR = OS2_Pin << 16U
#define AD_OS2_1()                          OS2_GPIO_Port->BSRR = OS2_Pin

#define AD_MISO_LOW()                       MISO_GPIO_Port->BSRR  = MISO_Pin << 16U
#define AD_MISO_HIGH()                      MISO_GPIO_Port->BSRR  = MISO_Pin   //D7--MISO

#define AD_SCK_LOW()                        RD_GPIO_Port->BSRR  = RD_Pin << 16U
#define AD_CSK_HIGH()                       RD_GPIO_Port->BSRR  = RD_Pin        //RD--SCLk

#define AD_MISO_IN                          HAL_GPIO_ReadPin(MISO_GPIO_Port, MISO_Pin)

typedef struct
{
    uint16_t usRead;
    uint16_t usWrite;
    uint16_t usCount;
    uint16_t usBuf[FIFO_SIZE];
}FIFO_t;

void ad7606_Reset(void);
void ad7606_init(void);
void ad7606_SetOS(uint8_t _ucMode);
void ad7606_StartRecord(void);
void ad7606_StopRecord(void);
void ad7606_IRQSrc(void);
void ad7606_StartConv(void);
void ad7606_get_fft_data(void);
void fft_get_maxvalue(void);
float32_t filter_fft(void);
int32_t ad7606_get_signal_average_val(int8_t channal,int8_t average_num);

extern FIFO_t  g_tAD;

#endif

