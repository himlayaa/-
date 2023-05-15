#ifndef __DHT11_H
#define __DHT11_H

#define DHT11_RCC	RCC_APB2Periph_GPIOA   //��������RCC
#define DHT11_PORT	GPIOA				   //����˿�
#define DHT11_IO	GPIO_Pin_0			   //����IO�˿�

void DHT11_IO_OUT(void);
void DHT11_IO_IN(void);
void DHT11_RST(void);
u8 DHT11_Check(void);
u8 DHT11_Init(void);
u8 DHT11_Read_Bit(void);
u8 DHT11_Read_Byte(void);
u8 DHT11_Read_Data(u8 *temp, u8 *humi);

#endif
