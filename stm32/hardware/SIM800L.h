#ifndef __SIM800L_H_
#define __SIM800L_H_

#define REV_OK		0	//������ɱ�־
#define REV_WAIT	1	//����δ��ɱ�־

void SIM800L_Clear(void);
_Bool SIM800L_WaitRecive(void);
_Bool SIM800L_SendCmd(char *cmd, char *res);
void SIM800L_SendData(unsigned char *data, unsigned short len, char *res);
void SIM800L_Init(void);
void SIM800L_RESET(void);


#endif
