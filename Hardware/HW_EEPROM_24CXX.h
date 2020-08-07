/*********************************************************************************************
��Ŀ����IIC_EEPROM
�ļ�����EEPROM_24CXX.h - IIC���߽ӿڵ�EEPROM����
��д�ˣ�лӢ��(E-mail:xieyingnan1994@163.com)���� ��
��дʱ�䣺2018��10��15�ա�������  
�޸���־������
����NO.1-								
**********************************************************************************************
˵����
**********************************************************************************************/
#ifndef	HW_EEPROM_24CXX_H
#define HW_EEPROM_24CXX_H

uint8_t EEPROM_CheckDevice(uint8_t DevAddr);	//��������ϵ�24CXX�����Ƿ�����Ӧ
uint8_t EEPROM_WaitStandby(void);	//�ȴ�д�������е�EEPROM�ָ�������״̬
uint8_t HW_EEPROM_getChar(uint16_t addr);	//EEPROM�ж�ȡһ���ֽ�����
uint8_t HW_EEPROM_putChar(uint16_t addr, uint8_t new_value);	//EEPROM��д��һ���ֽ�����

#endif
