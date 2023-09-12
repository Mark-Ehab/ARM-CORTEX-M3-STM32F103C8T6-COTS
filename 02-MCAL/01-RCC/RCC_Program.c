/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 7, 2023               	*/
/*      			SWC          : RCC  			            */
/*     			    Description	 : RCC Program                  */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						  _____   _____ _____   _____                                                       */
/*						 |  __ \ / ____/ ____| |  __ \                                                      */
/*						 | |__) | |   | |      | |__) | __ ___   __ _ _ __ __ _ _ __ ___                    */
/*						 |  _  /| |   | |      |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \                   */
/*						 | | \ \| |___| |____  | |   | | | (_) | (_| | | | (_| | | | | | |                  */
/*						 |_|  \_\\_____\_____| |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|                  */
/*						                                         __/ |                                      */
/*																|___/                                       */
/*----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "STD_TYPES.h"
#include "STD_ERRORS.h"
#include "BIT_MATH.h"

#include "RCC_Private.h"
#include "RCC_Config.h"
#include "RCC_Interface.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             FUNCTIONS IMPLEMENTATIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: Init							                                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : void				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : void                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : void                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Initialize RCC through setting the clock for the system		  */
/* 				   and its type based on configuration file						  */
/*--------------------------------------------------------------------------------*/
void RCC_Init(void)
{
	/************************Check which clock is selected to be system's clock************************/
	/* Clear System Clock Switch Bits */
	RCC->CFGR &= RCC_SW_MASK;

	#if   RCC_SYSTEM_CLK ==  HSI

		/* Set HSI as System Clock */
		RCC->CFGR |= RCC_SW_HSI;

	#elif RCC_SYSTEM_CLK ==  HSE

		/* Set HSE as System Clock */
		RCC->CFGR |= RCC_SW_HSE;

	#elif RCC_SYSTEM_CLK ==  PLL

		/* Set PLL as System Clock */
		RCC->CFGR |= RCC_SW_PLL;

	#else

		#error

	#endif

	/************************Check which AHB Prescaler is selected************************/
	/* Clear AHB Prescaler Bits */
	RCC->CFGR &= RCC_AHB_SYSCLK_PRESCALER_MASK;

	#if   RCC_AHB_CLK_PRESCALER == SYSCLK_NOT_DIVIDED

		/* Set AHB Prescaler to 1 (System Clock Not Divided by any Prescaler) */
		RCC->CFGR |= RCC_AHB_SYSCLK_NOT_DIVIDED;

	#elif RCC_AHB_CLK_PRESCALER == SYSCLK_DIV_BY_2

		/* Set AHB Prescaler to 2 (System Clock Divided by 2) */
		RCC->CFGR |= RCC_AHB_SYSCLK_DIV_BY_2;

	#elif RCC_AHB_CLK_PRESCALER == SYSCLK_DIV_BY_4

		/* Set AHB Prescaler to 4 (System Clock Divided by 4) */
		RCC->CFGR |= RCC_AHB_SYSCLK_DIV_BY_4;

	#elif RCC_AHB_CLK_PRESCALER == SYSCLK_DIV_BY_8

		/* Set AHB Prescaler to 8 (System Clock Divided by 8) */
		RCC->CFGR |= RCC_AHB_SYSCLK_DIV_BY_8;

	#elif RCC_AHB_CLK_PRESCALER == SYSCLK_DIV_BY_16

		/* Set AHB Prescaler to 16 (System Clock Divided by 16) */
		RCC->CFGR |= RCC_AHB_SYSCLK_DIV_BY_16;

	#elif RCC_AHB_CLK_PRESCALER == SYSCLK_DIV_BY_64

		/* Set AHB Prescaler to 64 (System Clock Divided by 64) */
		RCC->CFGR |= RCC_AHB_SYSCLK_DIV_BY_64;

	#elif RCC_AHB_CLK_PRESCALER == SYSCLK_DIV_BY_128

		/* Set AHB Prescaler to 128 (System Clock Divided by 128) */
		RCC->CFGR |= RCC_AHB_SYSCLK_DIV_BY_128;

	#elif RCC_AHB_CLK_PRESCALER == SYSCLK_DIV_BY_256

		/* Set AHB Prescaler to 256 (System Clock Divided by 256) */
		RCC->CFGR |= RCC_AHB_SYSCLK_DIV_BY_256;

	#elif RCC_AHB_CLK_PRESCALER == SYSCLK_DIV_BY_512

		/* Set AHB Prescaler to 512 (System Clock Divided by 512) */
		RCC->CFGR |= RCC_AHB_SYSCLK_DIV_BY_512;

	#else

		#error "Wrong AHB Prescaler Configuration !"

	#endif

	/************************Check which APB1 Prescaler is selected************************/
	/* Clear APB1 Prescaler Bits */
	RCC->CFGR &= RCC_APB1_HCLK_PRESCALER_MASK;

	#if   RCC_APB1_CLK_PRESCALER == HCLK_NOT_DIVIDED

		/* Set APB1 Prescaler to 1 (High Performance Clock Not Divided by any Prescaler) */
		RCC->CFGR |= RCC_APB1_HCLK_NOT_DIVIDED;

	#elif RCC_APB1_CLK_PRESCALER == HCLK_DIV_BY_2

		/* Set APB1 Prescaler to 2 (High Performance Clock Divided by 2) */
		RCC->CFGR |= RCC_APB1_HCLK_DIV_BY_2;

	#elif RCC_APB1_CLK_PRESCALER == HCLK_DIV_BY_4

		/* Set APB1 Prescaler to 4 (High Performance Clock Divided by 4) */
		RCC->CFGR |= RCC_APB1_HCLK_DIV_BY_4;

	#elif RCC_APB1_CLK_PRESCALER == HCLK_DIV_BY_8

		/* Set APB1 Prescaler to 8 (High Performance Clock Divided by 8) */
		RCC->CFGR |= RCC_APB1_HCLK_DIV_BY_8;

	#elif RCC_APB1_CLK_PRESCALER == HCLK_DIV_BY_16

		/* Set APB1 Prescaler to 16 (High Performance Clock Divided by 16) */
		RCC->CFGR |= RCC_APB1_HCLK_DIV_BY_16;

	#else

		#error "Wrong APB1 Prescaler Configuration !"

	#endif

	/************************Check which APB2 Prescaler is selected************************/
	/* Clear APB1 Prescaler Bits */
	RCC->CFGR &= RCC_APB2_HCLK_PRESCALER_MASK;

	#if   RCC_APB2_CLK_PRESCALER == HCLK_NOT_DIVIDED

		/* Set APB2 Prescaler to 1 (High Performance Clock Not Divided by any Prescaler) */
		RCC->CFGR |= RCC_APB2_HCLK_NOT_DIVIDED;

	#elif RCC_APB2_CLK_PRESCALER == HCLK_DIV_BY_2

		/* Set APB2 Prescaler to 2 (High Performance Clock Divided by 2) */
		RCC->CFGR |= RCC_APB2_HCLK_DIV_BY_2;

	#elif RCC_APB2_CLK_PRESCALER == HCLK_DIV_BY_4

		/* Set APB2 Prescaler to 4 (High Performance Clock Divided by 4) */
		RCC->CFGR |= RCC_APB2_HCLK_DIV_BY_4;

	#elif RCC_APB2_CLK_PRESCALER == HCLK_DIV_BY_8

		/* Set APB2 Prescaler to 8 (High Performance Clock Divided by 8) */
		RCC->CFGR |= RCC_APB2_HCLK_DIV_BY_8;

	#elif RCC_APB2_CLK_PRESCALER == HCLK_DIV_BY_16

		/* Set APB2 Prescaler to 16 (High Performance Clock Divided by 16) */
		RCC->CFGR |= RCC_APB2_HCLK_DIV_BY_16;

	#else

		#error "Wrong APB2 Prescaler Configuration !"

	#endif

	/************************Check which PLL entry clock source and PLL multiplication factor are selected************************/
	#if RCC_CLK_ENABLE == PLL_ON || RCC_CLK_ENABLE == HSI_AND_PLLON || RCC_CLK_ENABLE == HSE_AND_PLL_ON || RCC_CLK_ENABLE == HSI_AND_HSE_AND_PLL_ON

		/* Check which PLL entry clock source */
		#if   RCC_PLL_CLK_ENTRY == PLL_HSI_DIV_BY_2

			/* Set HSI/2 as PLL Clock Source */
			CLR_BIT(RCC->CFGR,CFGR_PLLSRC);

		#elif RCC_PLL_CLK_ENTRY == PLL_HSE

			/* Set HSE as PLL Clock Source */
			SET_BIT(RCC->CFGR,CFGR_PLLSRC);

			/* Check HSE Divider for PLL Entry */
			#if   RCC_PLL_HSE_DIV_FACTOR == PLL_DIV_FACTOR_HSE

				/* Set HSE Clock not Divided */
				CLR_BIT(RCC->CFGR,CFGR_PLLXTPRE);

			#elif RCC_PLL_HSE_DIV_FACTOR == PLL_DIV_FACTOR_HSE_DIV_BY_2

				/* Set HSE Clock Divided by 2 */
				SET_BIT(RCC->CFGR,CFGR_PLLXTPRE);

			#else

				#error "Wrong PLL HSE Divider Configuration! "

			#endif

		#else

			#error "Wrong PLL Entry Clock Source Configuration !"

		#endif

		/* Check PLL multiplication factor */

		/* Clear PLL multiplication factor bits */
		RCC->CFGR &= RCC_PLL_MUL_MASK;

		#if   RCC_PLL_MUL_FACTOR == PLL_MUL_BY_2

			/* Set PLL Multiplicatoin Factor to 2 */
			RCC->CFGR |= RCC_PLL_MUL_BY_2;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_3

			/* Set PLL Multiplicatoin Factor to 3 */
			RCC->CFGR |= RCC_PLL_MUL_BY_3;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_4

			/* Set PLL Multiplicatoin Factor to 4 */
			RCC->CFGR |= RCC_PLL_MUL_BY_4;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_5

			/* Set PLL Multiplicatoin Factor to 5 */
			RCC->CFGR |= RCC_PLL_MUL_BY_5;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_6

			/* Set PLL Multiplicatoin Factor to 6 */
			RCC->CFGR |= RCC_PLL_MUL_BY_6;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_7

			/* Set PLL Multiplicatoin Factor to 7 */
			RCC->CFGR |= RCC_PLL_MUL_BY_7;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_8

			/* Set PLL Multiplicatoin Factor to 8 */
			RCC->CFGR |= RCC_PLL_MUL_BY_8;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_9

			/* Set PLL Multiplicatoin Factor to 9 */
			RCC->CFGR |= RCC_PLL_MUL_BY_9;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_10

			/* Set PLL Multiplicatoin Factor to 10 */
			RCC->CFGR |= RCC_PLL_MUL_BY_10;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_11

			/* Set PLL Multiplicatoin Factor to 11 */
			RCC->CFGR |= RCC_PLL_MUL_BY_11;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_12

			/* Set PLL Multiplicatoin Factor to 12 */
			RCC->CFGR |= RCC_PLL_MUL_BY_12;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_13

			/* Set PLL Multiplicatoin Factor to 13 */
			RCC->CFGR |= RCC_PLL_MUL_BY_13;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_14

			/* Set PLL Multiplicatoin Factor to 14 */
			RCC->CFGR |= RCC_PLL_MUL_BY_14;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_15

			/* Set PLL Multiplicatoin Factor to 15 */
			RCC->CFGR |= RCC_PLL_MUL_BY_15;

		#elif RCC_PLL_MUL_FACTOR == PLL_MUL_BY_16

			/* Set PLL Multiplicatoin Factor to 16 */
			RCC->CFGR |= RCC_PLL_MUL_BY_16;

		#else

			#error "Wrong PLL Multiplication Factor Configuration !"

		#endif

	#endif

	/************************Check which Microcontroller output is selected************************/
	/* Clear Microcontroller Clock Output Bits */
	RCC->CFGR &= RCC_MCO_MASK;

	#if   RCC_MCU_CLK_OUTPUT == MCO_NO_CLK

		/* Set  Microcontroller Clock Output to No Clock */
		RCC->CFGR |= RCC_MCO_NO_CLK;

	#elif RCC_MCU_CLK_OUTPUT == MCO_SYSCLK

		/* Set  Microcontroller Clock Output to System Clock */
		RCC->CFGR |= RCC_MCO_SYS_CLK;

	#elif RCC_MCU_CLK_OUTPUT == MCO_HSI_CLK

		/* Set  Microcontroller Clock Output to HSI Clock */
		RCC->CFGR |= RCC_MCO_HSI_CLK;

	#elif RCC_MCU_CLK_OUTPUT == MCO_HSE_CLK

		/* Set  Microcontroller Clock Output to HSE Clock */
		RCC->CFGR |= RCC_MCO_HSE_CLK;

	#elif RCC_MCU_CLK_OUTPUT == MCO_PLL_DIV_BY_2_CLK

		/* Set  Microcontroller Clock Output to PLL/2 Clock */
		RCC->CFGR |= RCC_MCO_PLL_DIV_BY_2_CLK;

	#else

		#error "Wrong Microcontroller Clock Output Configuration !"

	#endif

	/************************Check which type HSE clock is selected************************/
	#if RCC_CLK_ENABLE == HSE_ON || RCC_CLK_ENABLE == HSI_AND_HSE_ON || RCC_CLK_ENABLE == HSE_AND_PLL_ON || RCC_CLK_ENABLE == HSI_AND_HSE_AND_PLL_ON

		#if	  RCC_HSE_CLK == HSE_RC

			/* Set HSEBYP to bypass external 4-16 MHz oscillator */
			SET_BIT(RCC->CR,CR_HSEBYP);

		#elif RCC_HSE_CLK == HSE_CRYSTAL || RCC_HSE_CLK == HSE_CERAMIC

			/* Clear HSEBYP to not bypass external 4-16 MHz oscillator */
			CLR_BIT(RCC->CR,CR_HSEBYP);

		#else

			#error "Wrong RCC HSE Clock Type Configuration !"

		#endif

	#endif

	/************************Check which clock is enabled based on configuration file************************/
		#if	  RCC_CLK_ENABLE == HSI_ON

			/* Enable HSI Clock */
			SET_BIT(RCC->CR,CR_HSION);

		#elif RCC_CLK_ENABLE == HSE_ON

			/* Enable HSE Clock */
			SET_BIT(RCC->CR,CR_HSEON);

			/* Check if HSE oscillator is ready */
			while(!GET_BIT(RCC->CR,CR_HSERDY));

			/* Enable Clock Security System */
			SET_BIT(RCC->CR,CR_CSSON);

		#elif RCC_CLK_ENABLE == PLL_ON

			/* Enable PLL Clock */
			SET_BIT(RCC->CR,CR_PLLON);

		#elif RCC_CLK_ENABLE == HSI_AND_HSE_ON

			/* Enable HSI Clock */
			SET_BIT(RCC->CR,CR_HSION);

			/* Enable HSE Clock */
			SET_BIT(RCC->CR,CR_HSEON);

			/* Check if HSE oscillator is ready */
			while(!GET_BIT(RCC->CR,CR_HSERDY));

			/* Enable Clock Security System */
			SET_BIT(RCC->CR,CR_CSSON);

		#elif RCC_CLK_ENABLE == HSI_AND_PLLON

			/* Enable HSI Clock */
			SET_BIT(RCC->CR,CR_HSION);

			/* Enable PLL Clock */
			SET_BIT(RCC->CR,CR_PLLON);

		#elif RCC_CLK_ENABLE == HSE_AND_PLL_ON

			/* Enable HSE Clock */
			SET_BIT(RCC->CR,CR_HSEON);

			/* Check if HSE oscillator is ready */
			while(!GET_BIT(RCC->CR,CR_HSERDY));

			/* Enable Clock Security System */
			SET_BIT(RCC->CR,CR_CSSON);

			/* Enable PLL Clock */
			SET_BIT(RCC->CR,CR_PLLON);

		#elif RCC_CLK_ENABLE == HSI_AND_HSE_PLL_ON

			/* Enable HSI Clock */
			SET_BIT(RCC->CR,CR_HSION);

			/* Enable HSE Clock */
			SET_BIT(RCC->CR,CR_HSEON);

			/* Check if HSE oscillator is ready */
			while(!GET_BIT(RCC->CR,CR_HSERDY));

			/* Enable Clock Security System */
			SET_BIT(RCC->CR,CR_CSSON);

			/* Enable PLL Clock */
			SET_BIT(RCC->CR,CR_PLLON);

		#else

			#error "Wrong RCC Clock Enable Configuration !"

		#endif

}
/*--------------------------------------------------------------------------------*/
/* @Function Name: EnablePeripheralClk					                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_BusId											  */
/* 				   Ex:(RCC_AHB, RCC_APB1, RCC_APB2) 					          */
/*				   uint8_t Copy_PeripheralId				                      */
/*				   Ex:(RCC_DMA1 ... RCC_SDIO)  (AHB)							  */
/*				   Ex:(RCC_AFIO ... RCC_TIM11) (APB2)                             */
/*				   Ex:(RCC_TIM2 ... RCC_DAC)   (APB2)                             */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : void                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : void                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Enables clock for any peripheral based on passed peripheral ID */
/* 				   and bus ID to which the peripheral is connected				  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t RCC_EnablePeripheralClk(uint8_t Copy_BusId , uint8_t Copy_PeripheralId)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if both passed bus id and peripheral id are valid or not */
	if((Copy_PeripheralId >= 0 && Copy_PeripheralId <= 31) && ( Copy_BusId >= 0 && Copy_BusId <= 2))
	{

		switch(Copy_BusId)
		{
			case RCC_AHB :

				/* Enables the clock source for a peripheral connected to AHB BUS */
				SET_BIT(RCC->AHBENR,Copy_PeripheralId);
				break;

			case RCC_APB1:

				/* Enables the clock source for a peripheral connected to APB1 BUS */
				SET_BIT(RCC->APB1ENR,Copy_PeripheralId);
				break;

			case RCC_APB2:

				/* Enables the clock source for a peripheral connected to APB2 BUS */
				SET_BIT(RCC->APB2ENR,Copy_PeripheralId);
				break;
		}
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}
/*--------------------------------------------------------------------------------*/
/* @Function Name: DisablePeripheralClk					                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_BusId											  */
/* 				   Ex:(RCC_AHB, RCC_APB1, RCC_APB2) 					          */
/*				   uint8_t Copy_PeripheralId				                      */
/*				   Ex:(RCC_DMA1 ... RCC_SDIO)  (AHB)							  */
/*				   Ex:(RCC_AFIO ... RCC_TIM11) (APB2)                             */
/*				   Ex:(RCC_TIM2 ... RCC_DAC)   (APB2)                             */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : void                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : void                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Disables clock for any peripheral based on passed peripheral   */
/* 				   ID and bus ID to which the peripheral is connected			  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t RCC_DisablePeripheralClk(uint8_t Copy_BusId , uint8_t Copy_PeripheralId)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if both passed bus id and peripheral id are valid or not */
	if((Copy_PeripheralId >= 0 && Copy_PeripheralId <= 31) && ( Copy_BusId >= 0 && Copy_BusId <= 2))
	{

		switch(Copy_BusId)
		{
			case RCC_AHB :

				/* Disables the clock source for a peripheral connected to AHB BUS */
				CLR_BIT(RCC->AHBENR,Copy_PeripheralId);
				break;

			case RCC_APB1:

				/* Disables the clock source for a peripheral connected to APB1 BUS */
				CLR_BIT(RCC->APB1ENR,Copy_PeripheralId);
				break;

			case RCC_APB2:

				/* Disables the clock source for a peripheral connected to APB2 BUS */
				CLR_BIT(RCC->APB2ENR,Copy_PeripheralId);
				break;
		}
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}
