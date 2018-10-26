#ifndef __TOUCH_SCREEN_H
#define	__TOUCH_SCREEN_H

#include "stm32f4xx.h"


#define TOUCH_XPLUS_GPIO_PORT     GPIOG
#define TOUCH_XPLUS_GPIO_CLK      RCC_AHB1Periph_GPIOG
#define TOUCH_XPLUS_GPIO_PIN      GPIO_Pin_9
#define TOUCH_XPLUS_PINSOURCE     GPIO_PinSource9
#define TOUCH_XPLUS_CHANNEL		  ADC_Channel_1

#define TOUCH_XMINUS_GPIO_PORT    GPIOG
#define TOUCH_XMINUS_GPIO_CLK     RCC_AHB1Periph_GPIOG
#define TOUCH_XMINUS_GPIO_PIN     GPIO_Pin_13
#define TOUCH_XMINUS_PINSOURCE    GPIO_PinSource13
#define TOUCH_XMINUS_CHANNEL	  ADC_Channel_1

#define TOUCH_YPLUS_GPIO_PORT     GPIOI
#define TOUCH_YPLUS_GPIO_CLK      RCC_AHB1Periph_GPIOI
#define TOUCH_YPLUS_GPIO_PIN      GPIO_Pin_7
#define TOUCH_YPLUS_PINSOURCE     GPIO_PinSource7
#define TOUCH_YPLUS_CHANNEL		  ADC_Channel_0


#define TOUCH_YMINUS_GPIO_PORT     GPIOI
#define TOUCH_YMINUS_GPIO_CLK      RCC_AHB1Periph_GPIOI
#define TOUCH_YMINUS_GPIO_PIN      GPIO_Pin_6
#define TOUCH_YMINUS_PINSOURCE     GPIO_PinSource6
#define TOUCH_YMINUS_CHANNEL	   ADC_Channel_1

void Touch_GPIO_Config(void);


#endif /* __TOUCH_SCREEN_H */

