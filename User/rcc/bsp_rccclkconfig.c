#include "bsp_rccclkconfic.h"

void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
	ErrorStatus HSEStatus;
	
	RCC_DeInit();
	//使能HSE
	RCC_HSEConfig(RCC_HSE_ON);
  //等待HSE启动获取标志
	HSEStatus = RCC_WaitForHSEStartUp();
	
	if(HSEStatus==SUCCESS)
  {
		//使能预取指
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		
		//HCLK=SYSCLK=72M
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		//PCLK1=HCLK=36M
    RCC_PCLK1Config(RCC_HCLK_Div2);
		//PCLK2=HCLK=72M
    RCC_PCLK2Config(RCC_HCLK_Div1);
		
		//配置PLLCLK=HSE*RCC_PLLMul_x
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
		//使能PLL
    RCC_PLLCmd(ENABLE);
		
		//等待PLL稳定
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		//选择SYSCLK来源
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		//等待稳定
    while(RCC_GetSYSCLKSource()!=0x08);
		
	}
	else
	{
		//如果HSE启动失败，用户在这离可以添加错误处理事项
	}
}


void HSI_SetSysClk(uint32_t RCC_PLLMul_x)
{
	__IO uint32_t HSIStatus = 0;
	
	RCC_DeInit();
	//使能HSI
	RCC_HSICmd(ENABLE);
  //等待HSI启动获取标志
	HSIStatus = RCC->CR & RCC_CR_HSIRDY;
	
	if(HSIStatus == RCC_CR_HSIRDY)
  {
		//使能预取指
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		
		//HCLK=SYSCLK=72M
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		//PCLK1=HCLK=36M
    RCC_PCLK1Config(RCC_HCLK_Div2);
		//PCLK2=HCLK=72M
    RCC_PCLK2Config(RCC_HCLK_Div1);
		
		//配置PLLCLK=HSI*RCC_PLLMul_x
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x);
		//使能PLL
    RCC_PLLCmd(ENABLE);
		
		//等待PLL稳定
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		//选择SYSCLK来源
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		//等待稳定
    while(RCC_GetSYSCLKSource()!=0x08);
		
	}
	else
	{
		//如果HSI启动失败，用户在这离可以添加错误处理事项
	}
}

