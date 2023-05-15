#include "stm32f10x.h"                  // Device header
#include "pwm.h"

void PWM_Init(void){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		 //����PB3��PB4��PA15Ĭ��Ϊ���Զ˿ڣ�������Ҫ����һ�²���ʹ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //����AFIO����ʱ��
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //�ر�JTAG���Թ���

		GPIO_InitTypeDef  GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //���ʹ��GPIO_Pin_2 /TIM_OC3Init()�Ļ���оƬ��bugû����
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	
		TIM_InternalClockConfig(TIM2); 
		
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;  //ARR
		TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;  //PSC
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
		
		TIM_OCInitTypeDef TIM_OCInitStructure;
		TIM_OCStructInit(&TIM_OCInitStructure); //���ṹ�帳��ʼֵ�����޸�ͨ�ö�ʱ������Ҫ�Ĳ���
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;  //CCR ->50[1kHz ,50%,1%]
		TIM_OC2Init(TIM2,&TIM_OCInitStructure);
		
		TIM_Cmd(TIM2,ENABLE);//
}

void PWM_SetCompare(uint16_t compare){
		TIM_SetCompare2(TIM2,compare);	
}

void Motor_Init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	PWM_Init();
}

void Motor_SetSpeed(int8_t speed){
	if(speed >= 0){ //����
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
		GPIO_SetBits(GPIOB,GPIO_Pin_4);
		PWM_SetCompare(speed); //	
	}else{
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
		GPIO_SetBits(GPIOB,GPIO_Pin_4);
		PWM_SetCompare(-speed); //�ٶ�
	}
}
