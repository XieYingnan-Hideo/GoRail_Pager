/*-----------------------------------------------------------------------
*@file     main.c
*@brief    GoRail_Pager�������ļ�
*@author   лӢ��(xieyingnan1994@163.com��
*@version  1.0
*@date     2020/08/03
-----------------------------------------------------------------------*/
#include "GoRail_Pager.h"
/*-----------------------------------------------------------------------
*@brief		�����ײ�Ӳ����ʼ��
*@param		��
*@retval	��
-----------------------------------------------------------------------*/
void HW_Base_Init(void)
{
	Delay_init();		//��ʼ��Systick��ʱ
	HW_USART1_Init(115200);	//��ʼ�����п�
	IIC_GPIOConfig();	//��ʼ�����ģ��IIC�����õ���GPIO��
	HW_GPIO_Init_Out(STATUS_LED_CLOCK,STATUS_LED_PORT,
									STATUS_LED_PIN,GPIO_Mode_Out_PP);
	STATUS_LED_OFF();	//�ر�״ָ̬ʾ��
	HW_GPIO_Init_Out(BUZZER_CLOCK,BUZZER_PORT,BUZZER_PIN,GPIO_Mode_Out_PP);
	BUZZER_OFF();	//�رշ�����
	HW_TIM_Interrupt_Init(INT_TIM_PERIOD,INT_TIM_PRESCALER);//��ʼ�������ṩʱ���Ķ�ʱ��								
	HW_TIM_Interrupt_Enable();	//��ʱ����ʱ���ж�
	OLED_Init();	//SSD1306 OLED��Ļ��ʼ��
}
/*-----------------------------------------------------------------------
*@brief		���������������
*@param		��
*@retval	��
-----------------------------------------------------------------------*/
int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//�򿪸��ù���ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	//�ر�JTAG,ֻ����SWD
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//��ʼ���ж�������Ϊ��2
	
	HW_Base_Init();			//�����ײ�Ӳ����ʼ��
	ShowBuildInfo();		//���ڴ�ӡ�汾��Ϣ
	ShowSettings();			//���ڴ�ӡ������Ŀ
	ShowSplashScreen();		//OLED��ʾ��������Ͱ汾��Ϣ
	CC1101_Initialize();	//���CC1101����ʼ������
	CC1101_StartReceive(Rx_Callback);	//��ʼ����

	while(true)
	{
		if(bDataArrivalFlag)
		{
			RxDataFeedProc();	//�������׺�ʼ��ȡ���ݲ�������ʾ
			bDataArrivalFlag = false;//�������ձ�־λ
		}
		//��Ӧ�������ױ�־λ���������ڴ����������ַ���				
		if(bit_IsTrue(USART1_RxState,USART1_RXCOMPLETE_FLAG))
		{
			ParseSerialCmdLine((char*)USART1_RxBuffer);//����������һ��������ʼ����
			USART1_RxState = 0;//����������׵ı�־λ�����ݼ���
		}
	}
}
