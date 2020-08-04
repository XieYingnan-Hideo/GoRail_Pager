/*-----------------------------------------------------------------------
*@file     system_utils.h
*@brief    ϵͳ��ʵ�ù���
*@author   лӢ��(xieyingnan1994@163.com��
*@version  1.0
*@date     2020/08/03
-----------------------------------------------------------------------*/
#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

void ParseSerialCmdLine(char *Rxbuff);	//��������������
void CC1101_Initialize(void);	//���CC1101����������
void ShowBuildInfo(void);	//���ڴ�ӡ�汾��Ϣ
void ShowSettings(void);	//���ڴ�ӡ������Ŀ
void ShowMessageLBJ(POCSAG_RESULT* POCSAG_Msg,float rssi,uint8_t lqi);//OLED��Ļ����ʾLBJ������Ϣ
void ShowSplashScreen(void); //OLED��ʾ��������Ͱ汾��Ϣ
void ShowFixedPattern(void); //OLED����ʾ�̶��ַ�(�����Ρ������ٶȡ��Ⱥ���)
void Rx_Callback(void);	//CC1101���ݰ��������ʱ�Ļص�����
void RxDataFeedProc(void);	//��ȡ�ѽ��յ����ݲ��������ʾ

extern volatile bool bDataArrivalFlag;	//��ʶ���ݵ�����־

#endif
