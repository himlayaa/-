#include "stm32f10x.h"                  // Device header



void Tim_PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	TIM_DeInit(TIM4);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_9; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //
	

	
	TIM_TimeBaseStructure.TIM_Period = 100 - 1; //������һ�������¼��Զ���װ�Ĵ������ڵ�ֵ arr
	TIM_TimeBaseStructure.TIM_Prescaler = 720 - 1; //����Ԥ��Ƶ��ֵ psc
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //������ԣ���
	//TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	
//	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ������Ƚ��Ĵ���������ֵ
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //����Ƚ�ʹ��
//	TIM_OC3Init(TIM4, &TIM_OCInitStructure); //����ָ���Ĳ�����ʼ��TIM4����
//	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH3 Ԥװ��ʹ��
	
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //
	TIM_OC1Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH1
	
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH2 
	
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH4
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ��TIM4����ARR�ϵ�Ԥװ�ؼĴ���
	//TIM_CtrlPWMOutputs(TIM4,ENABLE);  //MOE �����ʹ�ܣ��߼���ʱ�����뿪��
	TIM_Cmd(TIM4, ENABLE); 

}

void PWM_SetCompare1(uint16_t compare){
		TIM_SetCompare1(TIM4,compare);	
}
void PWM_SetCompare2(uint16_t compare){
		TIM_SetCompare2(TIM4,compare);	
}
void PWM_SetCompare4(uint16_t compare){
		TIM_SetCompare4(TIM4,compare);	
}