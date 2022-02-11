#include "pwm.h"


void PWM_TIM14_Init(u32 arr, u32 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructrue;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
		GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructrue.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructrue.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructrue.TIM_OutputState = TIM_OutputState_Enable;
    //TIM_OCInitStructrue.TIM_Pulse = 0;
    TIM_OC1Init(TIM14, &TIM_OCInitStructrue);

    TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM14, ENABLE);

    TIM_Cmd(TIM14, ENABLE);

}
