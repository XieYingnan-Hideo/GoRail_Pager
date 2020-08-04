/*********************************************************************************************
�ļ�����IIC_SoftSimulate.c - ʹ��GPIO�����ģ��IIC����Э�顡 
��д�ˣ�лӢ��(E-mail:xieyingnan1994@163.com)���� ��
��дʱ�䣺2018��10��15�ա�������  
�޸���־������
����NO.1-								
**********************************************************************************************
˵����
**********************************************************************************************/
#include "Hardware.h"
/*---------------��ģ��˽�еĺꡢ���͡���������������----------------------*/
#define IIC_GPIO_PORT	GPIOB	//IIC����GPIO�˿�
#define IIC_GPIO_CLOCK	RCC_APB2Periph_GPIOB	//GPIO�˿�ʱ��
#define IIC_SCL_PIN		GPIO_Pin_4	//SCLʱ���߶�Ӧ��GPIO����
#define IIC_SDA_PIN		GPIO_Pin_6	//SDA�����߶�Ӧ��GPIO����

#define IIC_SDA_1()		IIC_GPIO_PORT->BSRR = IIC_SDA_PIN	//SDA��λ
#define IIC_SDA_0()		IIC_GPIO_PORT->BRR = IIC_SDA_PIN	//SDA��λ
#define IIC_SCL_1()		IIC_GPIO_PORT->BSRR = IIC_SCL_PIN	//SCL��λ
#define IIC_SCL_0()		IIC_GPIO_PORT->BRR = IIC_SCL_PIN	//SCL��λ
#define IIC_SDA_Read()	((uint16_t)(IIC_GPIO_PORT->IDR & IIC_SDA_PIN))	//��ȡSDA��״̬

static void IIC_Delay(void);	//IICר�õ���ʱ�������ڲ�������ʱ��
/*---------------------------------------------------------------------------
��������IIC_GPIOConfig
���ܣ���������ģ��IIC��GPIO��
�����������
����ֵ����
---------------------------------------------------------------------------*/
void IIC_GPIOConfig(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(IIC_GPIO_CLOCK,ENABLE);//��ʱ��
	
	GPIO_InitStructure.GPIO_Pin = IIC_SCL_PIN|IIC_SDA_PIN;//ѡ������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//��©���ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�趨����
	GPIO_Init(IIC_GPIO_PORT,&GPIO_InitStructure);//��ʼ��GPIO
}
/*---------------------------------------------------------------------------
��������IIC_Delay
���ܣ�IICר����ʱ�������ڲ�������ʱ��
�����������
����ֵ����
---------------------------------------------------------------------------*/
static void IIC_Delay(void)
{
	uint8_t	i;
	for(i = 0;i < 8;i++);
	/*
	ѭ��10��, SCLƵ�� = 205kHz;ѭ��7��,SCLƵ�� = 347kHz;
	ѭ��5�Σ�SCLƵ�� = 421kHz;
	*/
}
/*---------------------------------------------------------------------------
��������IIC_Start
���ܣ�������ʼ�ź�
�����������
����ֵ����
---------------------------------------------------------------------------*/
void IIC_Start(void)
{
	IIC_SDA_1();
	IIC_SCL_1();
	
	IIC_Delay();
	IIC_SDA_0();	//��SCLΪ���ڼ�SDA�����½���,����������ʼ�ź�
	IIC_Delay();
	
	IIC_SCL_0();
	IIC_Delay();
}
/*---------------------------------------------------------------------------
��������IIC_Stop
���ܣ�������ֹ�ź�
�����������
����ֵ����
---------------------------------------------------------------------------*/
void IIC_Stop(void)
{	
	IIC_SCL_0();
	IIC_SDA_0();
	IIC_Delay();
	IIC_SCL_1();
	IIC_Delay();	//SCLΪ��ʱ��SDA���������أ���������ֹͣ�ź�
	IIC_SDA_1();
	IIC_Delay();
}
/*---------------------------------------------------------------------------
��������IIC_SendAck
���ܣ��������ӻ�������Ӧ�ź�
�����������
����ֵ����
---------------------------------------------------------------------------*/
void IIC_SendAck(void)
{
	IIC_SDA_0();//����SDA=0
	IIC_Delay();
	
	IIC_SCL_1();//����һ��ʱ������
	IIC_Delay();
	IIC_SCL_0();
	IIC_Delay();
	
	IIC_SDA_1();//�ͷ�SDA����
}
/*---------------------------------------------------------------------------
��������IIC_SendNAck
���ܣ��������ӻ����ͷ���Ӧ�ź�
�����������
����ֵ����
---------------------------------------------------------------------------*/
void IIC_SendNAck(void)
{
	IIC_SDA_1();//����SDA=1
	IIC_Delay();
	
	IIC_SCL_1();//����һ��ʱ������
	IIC_Delay();
	IIC_SCL_0();
	IIC_Delay();
}
/*---------------------------------------------------------------------------
��������IIC_WaitAck
���ܣ������ȴ��ӻ���Ӧ
�����������
����ֵ��0 - ������ȷӦ��1 - ��������Ӧ
---------------------------------------------------------------------------*/
uint8_t IIC_WaitAck(void)
{
	uint8_t Response;
	
	IIC_SDA_1();//�ͷ�SDA��
	IIC_Delay();
	IIC_SCL_1();
	IIC_Delay();	
	
	if(IIC_SDA_Read()){//��ȡ��Ӧ
		Response = 1;
	}//NACK
	else{
		Response = 0;
	}//ACK	

	IIC_SCL_0();
	IIC_Delay();
	
	return Response;
}
/*---------------------------------------------------------------------------
��������IIC_SendOneByte
���ܣ�����1�ֽ�����
���������uint8_t ByteData - Ҫ���͵�����
����ֵ����
---------------------------------------------------------------------------*/
void IIC_SendOneByte(uint8_t ByteData)
{
	uint8_t i;
	
	for(i=0;i < 8;i++)
	{
		if(ByteData & 0x80){//�ȴ�MSB����
			IIC_SDA_1();
		}
		else{
			IIC_SDA_0();
		}
		IIC_Delay();
		IIC_SCL_1();
		IIC_Delay();
		IIC_SCL_0();
		if(i == 7){//��������LSB���ͷ�SDA����
			IIC_SDA_1();
		}
		ByteData <<= 1;//����һ��bit
		IIC_Delay();
	}
}
/*---------------------------------------------------------------------------
��������IIC_ReadOneByte
���ܣ�����1�ֽ�����
�����������
����ֵ����ȡ����1�ֽ�����
---------------------------------------------------------------------------*/
uint8_t IIC_ReadOneByte(void)
{
	uint8_t i;
	uint8_t value = 0;
	
	for(i=0;i < 8;i++)
	{
		value <<= 1;	//����һλ�ڳ��ط�������˳��ΪMSB->LSB
		IIC_SCL_1();
		IIC_Delay();
		if(IIC_SDA_Read()){//��һ��SCLʱ�������ڶ�ȡSDA״̬
			value++;
		}
		IIC_SCL_0();
		IIC_Delay();
	}
	return value;
}
