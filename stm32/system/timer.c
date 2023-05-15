#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "menu.h"				//OLED�˵�
#include "beep.h"
#include "led.h"
#include <string.h>
#include <stdio.h>
#include "pwm.h"
#include "elecRelay.h"
#include "usart.h"
#include "menu.h"
#include "base.h"
#include "onenet.h"
#include "esp8266.h"
#include "motor.h"

char OLED_Buf[26];
extern u8 temper;  	    
extern u8 humi;
extern u16 smoke;     	   //����
extern float light;
extern u8 alarmFlag,beepFlag;
extern u8 Wind_speed[5];	   //
extern u8 Wind_value;
extern u8 Wind_flag;
extern u8 Elec1_value; 
extern u8 Elec2_value;
extern u8 LED1_pwm;
extern u8 LED2_pwm;
extern u8 Air_value;
extern float Step_dev[4];
extern u8 Air_value_before;
extern u8 Air_flag;
extern char Pub_Buf[256]; // �ϴ����ݵ�buff
extern char brand[10];
extern uint8_t ui_index,ui_state;
extern const char *device_Pub_topics;


void TIM2_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM2
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����						 
}


void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		//loop();
//		UsartPrintf(USART_DEBUG, "OneNet_Publish\r\n");  
//		sprintf(Pub_Buf,"{\"Temp\":%d,\"Humi\":%d,\"Smoke\":%d,\"Light\":%d,\"Wind\":%d,\"Beep\":%d,\"LED1\":%d,\"LED2\":%d,\"Elec1_value\":%d,\"Elec1_value\":%d}",
//			temper,humi,smoke,(int)light,Wind_value,alarmFlag,LED1_pwm,LED2_pwm,Elec1_value,Elec2_value);
//			OneNet_Publish(device_Pub_topics, Pub_Buf);//����TCP��MQTTЭ�������ϴ�
//		
//		ESP8266_Clear();
	}
}


void TIM3_Init(u16 arr,u16 psc){ //TIM3��ʱ��������������
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM3
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
		
		//	TIM_ClearFlag(TIM3,TIM_FLAG_Update); //��ֹ���ϵ�ͽ����ж�
		//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����	
}

void TIM3_IRQHandler(void){
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET){
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		
		if(beepFlag)BEEP=!BEEP;
		else BEEP=1;
		
		if(alarmFlag){  //�Զ���������
			beepFlag = 1;
			_clear();
			ui_index = M_WARNING;
		}
		
		PWM_SetCompare1(LED1_pwm); //����PCB��λ�ã���һ��
		PWM_SetCompare2(LED2_pwm);
		
		
		if(Wind_flag){
			Motor_SetSpeed(Wind_value);
			PWM_SetCompare4(Wind_value); //���ת�ٵ�
		} 
		
		//else{
			//Motor_SetSpeed(0);
			//PWM_SetCompare4(0); //���ת�ٵ�
		//}
			
		if(Elec1_value != ELEC1_STATE) elecRelay_action(ELEC1,Elec1_value);
		if(Elec2_value != ELEC2_STATE) elecRelay_action(ELEC2,Elec2_value);
//		
//		if(Elec1_value) elecRelay_Open(ELEC1);  //�̵���1����
//		else elecRelay_Close(ELEC1);
//	
//		
//		if(Elec2_value) elecRelay_Open(ELEC2);  //�̵���2����
//		else elecRelay_Close(ELEC2);
			
		
		if(strstr(brand,"changhong") != NULL && Air_value_before != Air_value){
			//temp_change(Air_value);
			Air_value_before = Air_value;
			Air_flag = 1;
		}
		
		
	}
}
