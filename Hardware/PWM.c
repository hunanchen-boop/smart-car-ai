#include "stm32f10x.h"

void PWM_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);//内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=100-1;//周期ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=36-1;//预分频器PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_InitStructure;
	TIM_OCStructInit(&TIM_InitStructure);
	TIM_InitStructure.TIM_OCMode=TIM_OCMode_PWM1;//输出比较模式
	TIM_InitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//设置比较极性
	TIM_InitStructure.TIM_OutputState=TIM_OutputState_Enable;//设置输出使能
	TIM_InitStructure.TIM_Pulse=0;//设置CCR寄存器值

//PWM频率：Freq=CK_PSC/（PSC+1）/（ARR+1）
//PWM占空比：Duty=CCR/（ARR+1）
//PWM分辨率：Reso=1/（ARR+1）

	TIM_OC3Init(TIM2,&TIM_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2,Compare);
}

