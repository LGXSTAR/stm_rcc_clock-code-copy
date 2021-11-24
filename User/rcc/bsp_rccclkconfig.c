#include "bsp_rccclkconfic.h"

void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
	ErrorStatus HSEStatus;
	
	RCC_DeInit();
	//ʹ��HSE
	RCC_HSEConfig(RCC_HSE_ON);
  //�ȴ�HSE������ȡ��־
	HSEStatus = RCC_WaitForHSEStartUp();
	
	if(HSEStatus==SUCCESS)
  {
		//ʹ��Ԥȡָ
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		
		//HCLK=SYSCLK=72M
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		//PCLK1=HCLK=36M
    RCC_PCLK1Config(RCC_HCLK_Div2);
		//PCLK2=HCLK=72M
    RCC_PCLK2Config(RCC_HCLK_Div1);
		
		//����PLLCLK=HSE*RCC_PLLMul_x
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
		//ʹ��PLL
    RCC_PLLCmd(ENABLE);
		
		//�ȴ�PLL�ȶ�
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		//ѡ��SYSCLK��Դ
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		//�ȴ��ȶ�
    while(RCC_GetSYSCLKSource()!=0x08);
		
	}
	else
	{
		//���HSE����ʧ�ܣ��û������������Ӵ���������
	}
}


void HSI_SetSysClk(uint32_t RCC_PLLMul_x)
{
	__IO uint32_t HSIStatus = 0;
	
	RCC_DeInit();
	//ʹ��HSI
	RCC_HSICmd(ENABLE);
  //�ȴ�HSI������ȡ��־
	HSIStatus = RCC->CR & RCC_CR_HSIRDY;
	
	if(HSIStatus == RCC_CR_HSIRDY)
  {
		//ʹ��Ԥȡָ
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		
		//HCLK=SYSCLK=72M
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		//PCLK1=HCLK=36M
    RCC_PCLK1Config(RCC_HCLK_Div2);
		//PCLK2=HCLK=72M
    RCC_PCLK2Config(RCC_HCLK_Div1);
		
		//����PLLCLK=HSI*RCC_PLLMul_x
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x);
		//ʹ��PLL
    RCC_PLLCmd(ENABLE);
		
		//�ȴ�PLL�ȶ�
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		//ѡ��SYSCLK��Դ
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		//�ȴ��ȶ�
    while(RCC_GetSYSCLKSource()!=0x08);
		
	}
	else
	{
		//���HSI����ʧ�ܣ��û������������Ӵ���������
	}
}

