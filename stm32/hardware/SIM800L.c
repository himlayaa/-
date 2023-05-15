#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "delay.h"
#include <string.h>
#include "SIM800L.h"
#include <stdio.h>

//unsigned char PhoneNO[]= "13795934074"; //���շ�����
extern unsigned char SIM800L_buff[64];  //����
unsigned short SIM800L_cnt = 0, SIM800L_cntPre = 0;

//==========================================================
//	�������ƣ�	ESP8266_Clear
//
//	�������ܣ�	��ջ���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SIM800L_Clear(void)
{

	memset(SIM800L_buff, 0, sizeof(SIM800L_buff));
	SIM800L_cnt = 0;

}

//==========================================================
//	�������ƣ�	ESP8266_WaitRecive
//
//	�������ܣ�	�ȴ��������
//
//	��ڲ�����	��
//
//	���ز�����	REV_OK-�������		REV_WAIT-���ճ�ʱδ���
//
//	˵����		ѭ�����ü���Ƿ�������
//==========================================================
_Bool SIM800L_WaitRecive(void)
{

	if(SIM800L_cnt == 0) 							//������ռ���Ϊ0 ��˵��û�д��ڽ��������У�����ֱ����������������
		return REV_WAIT;
		
	if(SIM800L_cnt == SIM800L_cntPre)				//�����һ�ε�ֵ�������ͬ����˵���������
	{
		SIM800L_cnt = 0;							//��0���ռ���
			
		return REV_OK;								//���ؽ�����ɱ�־
	}
		
	SIM800L_cntPre = SIM800L_cnt;					//��Ϊ��ͬ
	
	return REV_WAIT;								//���ؽ���δ��ɱ�־

}

//==========================================================
//	�������ƣ�	SIM800L_SendCmd
//
//	�������ܣ�	��������
//
//	��ڲ�����	cmd������
//				res����Ҫ���ķ���ָ��
//
//	���ز�����	0-�ɹ�	1-ʧ��
//
//	˵����		
//==========================================================
_Bool SIM800L_SendCmd(char *cmd, char *res)
{
	
	int timeOut = 500;

	Usart_SendString(USART1, (unsigned char *)cmd, strlen((const char *)cmd));
	while(timeOut--)
	{
		if(SIM800L_WaitRecive() == REV_OK)							//����յ�����
		{
			if(strstr((const char *)SIM800L_buff, res) != NULL)		//����������ؼ���
			{
				SIM800L_Clear();									//��ջ���
				
				return 0;
			}
		}
		delay_ms(10);
	}
	
	return 1;

}

//==========================================================
//	�������ƣ�	SIM800L_SendData
//
//	�������ܣ�	��������
//
//	��ڲ�����	data������
//				len������
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SIM800L_SendData(unsigned char *data, unsigned short len, char *res)
{
	delay_ms(500);

	char cmdBuf[32];
	
	SIM800L_Clear();								//��ս��ջ���
	sprintf(cmdBuf, "AT+CMGS=\"17744310976\"\r\n");		//��������
	if(!SIM800L_SendCmd(cmdBuf, ">"))				//�յ���>��ʱ���Է�������
	{
		Usart_SendString(USART1, data, len);		//�����豸������������
	}
	delay_ms(500);
	Usart_SendHexWord(USART1,0x1A);
	
//	while(strstr((const char *)SIM800L_buff, res) != NULL)		//����������ؼ���
//	{
//		SIM800L_Clear();									//��ջ���
//		UsartPrintf(USART2, "���ͳɹ�\r\n");
//		return 0;
//	}
//	return 1;
}

void SIM800L_Init(void){
	SIM800L_Clear();
	SIM800L_RESET();
	
	while(SIM800L_SendCmd("AT\r\n", "OK"))
		delay_ms(500);
	
	
	while(SIM800L_SendCmd("AT+CMGF=1\r\n", "OK"))
		delay_ms(500);
	
	
	while(SIM800L_SendCmd("AT+CSCS=\"GSM\"\r\n", "OK"))
		delay_ms(500);
	
	
}

void SIM800L_RESET(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	delay_ms(10);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	
}
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�����ж�
	{
		
		if(SIM800L_cnt >= sizeof(SIM800L_buff))	SIM800L_cnt = 0; //��ֹ���ڱ�ˢ��
		SIM800L_buff[SIM800L_cnt++] = USART1->DR;
		
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
}
