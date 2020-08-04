/*********************************************************************************************
�ļ�����IIC_SoftSimulate.h - ʹ��GPIO�����ģ��IIC����Э�顡 
��д�ˣ�лӢ��(E-mail:xieyingnan1994@163.com)���� ��
��дʱ�䣺2018��10��15�ա�������  
�޸���־������
����NO.1-								
**********************************************************************************************
˵����
**********************************************************************************************/
#ifndef HW_IIC_SOFTSIM_H
#define HW_IIC_SOFTSIM_H

void IIC_GPIOConfig(void);	//��������ģ��IIC��GPIO��
void IIC_Start(void);	//������ʼ�ź�
void IIC_Stop(void);	//������ֹ�ź�
uint8_t IIC_WaitAck(void);//�����ȴ��ӻ���Ӧ
void IIC_SendAck(void);	//�������ӻ�������Ӧ�ź�
void IIC_SendNAck(void);	//�������ӻ����ͷ���Ӧ�ź�
void IIC_SendOneByte(uint8_t ByteData);	//����1�ֽ�����
uint8_t IIC_ReadOneByte(void);	//��ȡ1�ֽ�����

#endif
