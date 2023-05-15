//stm32ͷ�ļ�
#include "stm32f10x.h"                  // Device header

//C��
#include <stdio.h>
#include <stdarg.h>

//Ӳ������
#include "Delay.h"				//ϵͳ��ʱ
#include "menu.h"				//OLED�˵�
#include "base.h"				//u8g2����
#include "exti.h"				//�ⲿ�ж�
#include "led.h"				//LED��
#include "beep.h"				//������
#include "DHT11.h"				//��ʪ�ȴ�����
#include "BH1750.h"				//���նȴ�����
#include "timer.h"				//��ʱ��
#include "AD.h"					//MQ-2����AD���ݲɼ�
#include "pwm.h"				//PWM����
#include "elecRelay.h"			//�̵���
#include "motor.h"				//���
#include "usart.h"				//����
#include "esp8266.h"			//WIFI���ӣ����ķ���
#include "onenet.h"				//�����ϴ���MQTT�
#include "changhong.h"			//�յ���������
#include "SIM800L.h"




u8 temper;  	   //�¶�
u8 humi;		   //ʪ��
u16 smoke;     	   //����
u8 temp;		   //��ʱ����
float light;	   //���ն�
u8 alarmFlag,beepFlag;	   //������־
u8 Motor_flag;
u8 Wind_flag;
u8 Wind_speed[5] = {0,5,10,15,20};	   //ͨ���ٶ�
u8 Wind_value;
u8 LED1_pwm;	   //LED1����pwmֵ
u8 LED2_pwm;	   //LED2����pwmֵ
u8 Air_value = 0;	   //�յ��¶�
u8 Air_value_before = 0; //�յ�֮ǰ�¶�
u8 Air_flag = 0;
u8 Elec1_value;    //����1���ر�־
u8 Elec2_value;    //����2���ر�־
u8 alarm_free = 5; //����Ƿ��ֶ�����Ϊ0
char Pub_Buf[256]; //�ϴ����ݵ�buff
char brand [10] = {"changhong"};   //�յ�Ʒ��
unsigned char SIM800L_buff[64];
uint8_t ui_index,ui_state;

const char *device_Sub_topics[] = {"/himlayasmarthome/sub"};
const char *device_Pub_topics = {"/himlayasmarthome/pub"};


int main(void)
{
	unsigned short timeCount = 0;	//���ͼ������
	unsigned char *dataPtr = NULL;  //����λ�����ĵ�����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�жϿ�������������


	Tim_PWM_Init();
	beep_Init();
	DHT11_Init();
	BH1750_Init();
	AD_Init();
	elecRelay_Init();
	Motor_Init();
	

	
	Usart2_Init(115200);					//����2������ESP8266��
	Usart3_Init(115200);					//����3�����ⷢ��
	Usart1_Init(115200);					//����1������/SIM������


	SIM800L_Init();
	
	
	ESP8266_Init();					//��ʼ��ESP8266
	
	while(OneNet_DevLink());			//����OneNET
	delay_ms(500);
//	
	
	//	beep_ON();				//��������ʾ����ɹ�
//	delay_ms(200);
//	beep_OFF();
	
	setup_u8g2();
	setup();
	
	
	TIM3_Init(2499,7199);     //��ʱ��3��ʼ������ʱ250ms��һ���ж�
	OneNet_Subscribe(device_Sub_topics, 1);
	

	
	while(1){
		loop();
		if(Air_flag){
			int cur = Air_value - 15;
			if(cur > 0 )Usart_SendString(USART3,code[cur],280);
			else Usart_SendString(USART3,code[0],280);
			USART3_Clear();
			Air_flag = 0;
		}
		
		if(timeCount % 8 == 0){
//			/***********��ʪ�ȴ�������ȡ����*********/
			temp = DHT11_Read_Data(&temper,&humi);  //

//		
//			/***********���նȴ�������ȡ����*********/
			if (!i2c_CheckDevice(BH1750_Addr)){	
				light = LIght_Intensity();

			}

//			/***********����������ȡ����*********/
			smoke = AD_GetValue();
			 

			//�Զ���������
			if(alarm_free == 5){
				if(humi > 95){ //©ˮ
					alarmFlag = 1;
					//SIM800L_Init();
					//SIM800L_SendData("Water leak!",11,"OK");
				}else if(smoke > 60 && temper < 50){ //ȼ��й¶
					alarmFlag = 1;
					Wind_value = Wind_speed[2];
					Wind_flag = 1;
					//SIM800L_Init();
					//SIM800L_SendData("Gas leak!",9,"OK");
				}else if(temper < 50 && light < 30000 && humi < 90 && smoke < 60){ //�������
					
					alarmFlag = 0;
					Wind_flag = Motor_flag == 1 ? 1 : 0;
					
				}else{ //�Ż���
					alarmFlag = 1;
					//SIM800L_Init();
					//SIM800L_SendData("Catch fire!",11,"OK");
				}
			}
			if(alarm_free < 5)alarm_free++;
			
			}
		if(++timeCount >= 40){	//���ͼ��5s
			
			sprintf(Pub_Buf,"{\"Temp\":%d,\"Humi\":%d,\"Smoke\":%d,\"Light\":%d,\"Wind\":%d,\"Beep\":%d,\"LED1\":%d,\"LED1\":%d,\"Elec1_value\":%d,\"Elec2_value\":%d}",
			temper,humi,smoke,(int)light,Wind_flag,beepFlag,LED1_pwm,LED2_pwm,Elec1_value,Elec2_value);
			OneNet_Publish(device_Pub_topics, Pub_Buf);//�����ϴ�
			
			timeCount = 0;
			ESP8266_Clear();
		}		
		dataPtr = ESP8266_GetIPD(3); //ESP8266�����Ʒ�������topic��������
		if(dataPtr != NULL)
		OneNet_RevPro(dataPtr);	
		delay_ms(10);
	
	}		
}	
