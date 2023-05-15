#ifndef __OLED_H
#define __OLED_H		


#include "sys.h"
#include "stdlib.h"
#include "string.h" 	 
#include "delay.h"


//--------------OLED��������---------------------
#define PAGE_SIZE			8
#define XLevelL				0x00
#define XLevelH				0x10
#define YLevel				0xB0
#define	Brightness		0xFF 
#define WIDTH					128
#define HEIGHT				64	


//-------------д��������ݶ���-------------------
#define OLED_CMD			0		//д����
#define OLED_DATA			1		//д���� 


//-----------------OLED�˿ڶ���----------------

#define OLED_RST_PIN		GPIO_Pin_8					//��λ�ź� RES
#define OLED_RST_PORT		GPIOA						//��λ�ź�
#define OLED_RST_CLK		RCC_APB2Periph_GPIOA		//��λ�ź�

#define OLED_DC_PIN			GPIO_Pin_15					//����/��������ź� DC
#define OLED_DC_PORT		GPIOB						//����/��������ź�
#define OLED_DC_CLK			RCC_APB2Periph_GPIOB		//����/��������ź�

#define OLED_CS_PIN			GPIO_Pin_13 				//Ƭѡ�ź� CS
#define OLED_CS_PORT		GPIOB						//Ƭѡ�ź�
#define OLED_CS_CLK			RCC_APB2Periph_GPIOB		//Ƭѡ�ź�

#define SPI2_SCK_PIN		GPIO_Pin_12					//ʱ���ź� D0/SCL
#define SPI2_SCK_PORT		GPIOA						//ʱ���ź�
#define SPI2_SCK_CLK		RCC_APB2Periph_GPIOA		//ʱ���ź�

#define SPI2_MOSI_PIN		GPIO_Pin_11					//���ݷ����ź� D1/SDA
#define SPI2_MOSI_PORT	    GPIOA							//���ݷ����ź�
#define SPI2_MOSI_CLK		RCC_APB2Periph_GPIOA		//���ݷ����ź�

//-----------------OLED�˿ڲ�������----------------
void OLED_Init_GPIO(void);		   


#endif


