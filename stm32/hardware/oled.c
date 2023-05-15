#include "oled.h"
#include "stm32f10x.h"                  // Device header

void OLED_Init_GPIO(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(OLED_DC_CLK,ENABLE);					//ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = OLED_DC_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//�ٶ�50MHz
 	GPIO_Init(OLED_DC_PORT, &GPIO_InitStructure);
 	GPIO_SetBits(OLED_DC_PORT,OLED_DC_PIN);
	
	RCC_APB2PeriphClockCmd(OLED_CS_CLK,ENABLE);					//ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = OLED_CS_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//�ٶ�50MHz
 	GPIO_Init(OLED_CS_PORT, &GPIO_InitStructure);
 	GPIO_SetBits(OLED_CS_PORT,OLED_CS_PIN);
	
	RCC_APB2PeriphClockCmd(OLED_RST_CLK,ENABLE);				//ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = OLED_RST_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//�ٶ�50MHz
 	GPIO_Init(OLED_RST_PORT, &GPIO_InitStructure);
 	GPIO_SetBits(OLED_RST_PORT,OLED_RST_PIN);
	
	RCC_APB2PeriphClockCmd(SPI2_SCK_CLK,ENABLE);					//ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = SPI2_SCK_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//�ٶ�50MHz
 	GPIO_Init(SPI2_SCK_PORT, &GPIO_InitStructure);
 	GPIO_SetBits(SPI2_SCK_PORT,SPI2_SCK_PIN);
	
	RCC_APB2PeriphClockCmd(SPI2_MOSI_CLK,ENABLE);					//ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = SPI2_MOSI_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//�ٶ�50MHz
 	GPIO_Init(SPI2_MOSI_PORT, &GPIO_InitStructure);
 	GPIO_SetBits(SPI2_MOSI_PORT,SPI2_MOSI_PIN);
}
