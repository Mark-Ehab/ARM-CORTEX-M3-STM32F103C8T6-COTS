/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 17, 2023               	*/
/*      			SWC          : AFIO  			            */
/*     			    Description	 : AFIO Program                 */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*																									        */
/*							  ______ _____ ____    _____                                                    */
/*						/\   |  ____|_   _/ __ \  |  __ \                                                   */
/*					   /  \  | |__    | || |  | | | |__) | __ ___   __ _ _ __ __ _ _ __ ___                 */
/*					  / /\ \ |  __|   | || |  | | |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \                */
/*					 / ____ \| |     _| || |__| | | |   | | | (_) | (_| | | | (_| | | | | | |               */
/*					/_/    \_\_|    |_____\____/  |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|               */
/*																	__/ |                                   */
/*																   |___/                                    */
/*----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "STD_TYPES.h"
#include "STD_ERRORS.h"
#include "BIT_MATH.h"

#include "AFIO_Private.h"
#include "AFIO_Config.h"
#include "AFIO_Interface.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              FUNCTIONS IMPLEMENTATIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetEXTIConfiguration          			                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_EXTILine                                          */
/* 				   Brief: EXTI line id that will be mapped as input source for    */
/*                        external interrupt event (ISR)                          */
/*                 Range: (AFIO_EXTI_LINE_0 --> AFIO_EXTI_LINE_15)                */
/*				   Note : This range is for STM32F103C8T6 MCU                     */
/*                 -------------------------------------------------------------- */
/*                 uint8_t Copy_PortMap                                           */
/*                 Brief: Port id that will be mapped as input source for         */
/*                        selected EXTI line id									  */
/*                 Range: (AFIO_PORTA - AFIO_PORTB - AFIO_PORTC)                  */
/*				   Note : This range is for STM32F103C8T6 MCU                     */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                            	  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function configures which EXTI line in which port that    */
/*				   will be mapped as an input source for external interrupt event */
/*				   (ISR)											              */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t AFIO_SetEXTIConfiguration(uint8_t Copy_EXTILine , uint8_t Copy_PortMap)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed EXTI line and port map values are within valid range or not */
	if((Copy_EXTILine >= AFIO_EXTI_LINE_0 && Copy_EXTILine <= AFIO_EXTI_LINE_15) &&
	   (Copy_PortMap == AFIO_PORTA || Copy_PortMap == AFIO_PORTB || Copy_PortMap == AFIO_PORTC))
	{
		if(Copy_EXTILine < 4)
		{
			/* Clear EXTI configuration bits of passed EXTI line */
			AFIO->EXTICR1 &= ~((0b1111) << (4 * Copy_EXTILine));

			/* Set port map value in configuration bits of passed EXTI line */
			AFIO->EXTICR1 |= (Copy_PortMap << (4 * Copy_EXTILine));
		}
		else if(Copy_EXTILine < 8)
		{
			/* Decrease EXTI line value by 4 */
			Copy_EXTILine -= 4;

			/* Clear EXTI configuration bits of passed EXTI line */
			AFIO->EXTICR2 &= ~((0b1111) << (4 * Copy_EXTILine));

			/* Set port map value in configuration bits of passed EXTI line */
			AFIO->EXTICR2 |= (Copy_PortMap << (4 * Copy_EXTILine));
		}
		else if(Copy_EXTILine < 12)
		{
			/* Decrease EXTI line value by 8 */
			Copy_EXTILine -= 8;

			/* Clear EXTI configuration bits of passed EXTI line */
			AFIO->EXTICR3 &= ~((0b1111) << (4 * Copy_EXTILine));

			/* Set port map value in configuration bits of passed EXTI line */
			AFIO->EXTICR3 |= (Copy_PortMap << (4 * Copy_EXTILine));
		}
		else
		{
			/* Decrease EXTI line value by 12 */
			Copy_EXTILine -= 12;

			/* Clear EXTI configuration bits of passed EXTI line */
			AFIO->EXTICR4 &= ~((0b1111) << (4 * Copy_EXTILine));

			/* Set port map value in configuration bits of passed EXTI line */
			AFIO->EXTICR4 |= (Copy_PortMap << (4 * Copy_EXTILine));
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
/* @Function Name: AlternativeFunctionRemap          					          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : Copy_FunctionRemapType                                         */
/* 				   Brief: Types of alternative functions for which GPIO pins will */
/*						  be re-mapped                                            */
/*                 Range: (AFIO_SPI1_REMAP --> AFIO_ADC2_ETRGREG_REMAP)           */
/*                 -------------------------------------------------------------- */
/*                 uint32_t Copy_FunctionRemapVal								  */
/*                 Brief: Values of alternative functions for which GPIO pins     */
/*						  will be re-mapped                                       */
/*                 Range:- AFIO_SPI1_NO_REMAP	                                  */
/*                       - AFIO_SPI1_REMAP			                              */
/*                       - AFIO_I2C1_NO_REMAP	                                  */
/*                       - AFIO_I2C1_REMAP			                              */
/*                       - AFIO_USART1_NO_REMAP	                                  */
/*                       - AFIO_USART1_REMAP		                              */
/*                       - AFIO_USART2_NO_REMAP	                                  */
/*                       - AFIO_USART2_REMAP		                              */
/*                       - AFIO_USART3_NO_REMAP	                                  */
/*                       - AFIO_USART3_PARTIAL_REMAP	                          */
/*                       - AFIO_USART3_FULL_REMAP	                              */
/*                       - AFIO_TIM1_NO_REMAP	                                  */
/*                       - AFIO_TIM1_PARTIAL_REMAP	                              */
/*                       - AFIO_TIM1_FULL_REMAP		                              */
/*                       - AFIO_TIM2_NO_REMAP	                                  */
/*                       - AFIO_TIM2_PARTIAL_REMAP1 	                          */
/*                       - AFIO_TIM2_PARTIAL_REMAP2 	                          */
/*                       - AFIO_TIM2_FULL_REMAP		                              */
/*                       - AFIO_TIM3_NO_REMAP	                                  */
/*                       - AFIO_TIM3_PARTIAL_REMAP	                              */
/*                       - AFIO_TIM3_FULL_REMAP		                              */
/*                       - AFIO_TIM4_NO_REMAP	                                  */
/*                       - AFIO_TIM4_FULL_REMAP		                              */
/*                       - AFIO_CANRX_PA11_CANTX_PA12                             */
/*                       - AFIO_CANRX_PB8_CANTX_PB9                               */
/*                       - AFIO_CANRX_PD0_CANTX_PD0                               */
/*                       - AFIO_PD01_NO_REMAP		                              */
/*                       - AFIO_PD0_OSC_IN_PD1_OSC_OUT                            */
/*                       - AFIO_TIM5_CH4_PA3                                      */
/*                       - AFIO_TIM5_CH4_LSI                                      */
/*                       - AFIO_ADC1_EXTI15                                       */
/*                       - AFIO_ADC1_TIM8_CH4                                     */
/*                       - AFIO_ADC1_EXTI11                                       */
/*                       - AFIO_ADC1_TIM8_TRG0                                    */
/*                       - AFIO_ADC2_EXTI15                                       */
/*                       - AFIO_ADC2_TIM8_CH4                                     */
/*                       - AFIO_ADC2_EXTI11                                       */
/*                       - AFIO_ADC2_TIM8_TRG0                                    */
/*                       - AFIO_Full_SWJ				                          */
/*                       - AFIO_Full_SWJ_No_NJTRST	                              */
/*                       - AFIO_SW-DP_N0_JTAG-DP	                              */
/*                       - AFIO_JTAG-DP_N0_SW-DP	                              */
/*                       - AFIO_TIM9_NO_REMAP	                                  */
/*                       - AFIO_TIM9_REMAP			                              */
/*                       - AFIO_TIM10_NO_REMAP	                                  */
/*                       - AFIO_TIM10_REMAP			                              */
/*                       - AFIO_TIM11_NO_REMAP	                                  */
/*                       - AFIO_TIM11_REMAP			                              */
/*                       - AFIO_TIM13_NO_REMAP	                                  */
/*                       - AFIO_TIM13_REMAP			                              */
/*                       - AFIO_TIM14_NO_REMAP	                                  */
/*                       - AFIO_TIM14_REMAP			                              */
/*                       - AFIO_NADV_CONNECT                                      */
/*                       - AFIO_NADV_DISCONNECT        							  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                              	  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function maps MCU pins to operate in alternative          */
/*				   functions rather than being regular I/O pins					  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t AFIO_AlternativeFunctionRemap(uint8_t Copy_FunctionRemapType,uint32_t Copy_FunctionRemapVal)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed function remap value is valid or not */
	if(Copy_FunctionRemapVal == AFIO_SPI1_NO_REMAP       ||  Copy_FunctionRemapVal == AFIO_SPI1_REMAP             ||
	   Copy_FunctionRemapVal == AFIO_I2C1_NO_REMAP       ||  Copy_FunctionRemapVal == AFIO_I2C1_REMAP             ||
	   Copy_FunctionRemapVal == AFIO_USART1_NO_REMAP     ||  Copy_FunctionRemapVal == AFIO_USART1_REMAP           ||
	   Copy_FunctionRemapVal == AFIO_USART2_NO_REMAP     ||  Copy_FunctionRemapVal == AFIO_USART2_REMAP           ||
	   Copy_FunctionRemapVal == AFIO_USART3_NO_REMAP     ||  Copy_FunctionRemapVal == AFIO_USART3_PARTIAL_REMAP   ||
	   Copy_FunctionRemapVal == AFIO_USART3_FULL_REMAP   ||  Copy_FunctionRemapVal == AFIO_TIM1_NO_REMAP          ||
	   Copy_FunctionRemapVal == AFIO_TIM1_PARTIAL_REMAP  ||  Copy_FunctionRemapVal == AFIO_TIM1_FULL_REMAP        ||
	   Copy_FunctionRemapVal == AFIO_TIM2_NO_REMAP       ||  Copy_FunctionRemapVal == AFIO_TIM2_PARTIAL_REMAP1    ||
	   Copy_FunctionRemapVal == AFIO_TIM2_PARTIAL_REMAP2 ||  Copy_FunctionRemapVal == AFIO_TIM2_FULL_REMAP        ||
	   Copy_FunctionRemapVal == AFIO_TIM3_NO_REMAP       ||  Copy_FunctionRemapVal == AFIO_TIM3_PARTIAL_REMAP     ||
	   Copy_FunctionRemapVal == AFIO_TIM3_FULL_REMAP     ||  Copy_FunctionRemapVal == AFIO_TIM4_NO_REMAP          ||
	   Copy_FunctionRemapVal == AFIO_TIM4_FULL_REMAP     ||  Copy_FunctionRemapVal == AFIO_CANRX_PA11_CANTX_PA12  ||
	   Copy_FunctionRemapVal == AFIO_CANRX_PB8_CANTX_PB9 ||  Copy_FunctionRemapVal == AFIO_CANRX_PD0_CANTX_PD0    ||
	   Copy_FunctionRemapVal == AFIO_PD01_NO_REMAP       ||  Copy_FunctionRemapVal == AFIO_PD0_OSC_IN_PD1_OSC_OUT ||
	   Copy_FunctionRemapVal == AFIO_TIM5_CH4_PA3        ||  Copy_FunctionRemapVal == AFIO_TIM5_CH4_LSI           ||
	   Copy_FunctionRemapVal == AFIO_ADC1_EXTI15         ||  Copy_FunctionRemapVal == AFIO_ADC1_TIM8_CH4          ||
	   Copy_FunctionRemapVal == AFIO_ADC1_EXTI11         ||  Copy_FunctionRemapVal == AFIO_ADC1_TIM8_TRG0         ||
	   Copy_FunctionRemapVal == AFIO_ADC2_EXTI15         ||  Copy_FunctionRemapVal == AFIO_ADC2_TIM8_CH4          ||
	   Copy_FunctionRemapVal == AFIO_ADC2_EXTI11         ||  Copy_FunctionRemapVal == AFIO_ADC2_TIM8_TRG0         ||
	   Copy_FunctionRemapVal == AFIO_Full_SWJ            ||  Copy_FunctionRemapVal == AFIO_Full_SWJ_No_NJTRST     ||
	   Copy_FunctionRemapVal == AFIO_SW_DP_N0_JTAG_DP    ||  Copy_FunctionRemapVal == AFIO_JTAG_DP_N0_SW_DP       ||
	   Copy_FunctionRemapVal == AFIO_TIM9_NO_REMAP       ||  Copy_FunctionRemapVal == AFIO_TIM9_REMAP             ||
	   Copy_FunctionRemapVal == AFIO_TIM10_NO_REMAP      ||  Copy_FunctionRemapVal == AFIO_TIM10_REMAP            ||
	   Copy_FunctionRemapVal == AFIO_TIM11_NO_REMAP      ||  Copy_FunctionRemapVal == AFIO_TIM11_REMAP            ||
	   Copy_FunctionRemapVal == AFIO_TIM13_NO_REMAP      ||  Copy_FunctionRemapVal == AFIO_TIM13_REMAP            ||
	   Copy_FunctionRemapVal == AFIO_TIM14_NO_REMAP      ||  Copy_FunctionRemapVal == AFIO_TIM14_REMAP            ||
	   Copy_FunctionRemapVal == AFIO_NADV_CONNECT        ||  Copy_FunctionRemapVal == AFIO_NADV_DISCONNECT)
	{
		/* Switch on function remap type */
		switch(Copy_FunctionRemapType)
		{
		    case AFIO_SPI1:

				/* Reset SPI1 Remap Bits */
				AFIO->MAPR &= AFIO_SPI1_REMAP_MASK;

				/* Set Specified SPI1 Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 0);

				break;

		    case AFIO_I2C1:

				/* Reset I2C1 Remap Bits */
				AFIO->MAPR &= AFIO_I2C1_REMAP_MASK;

				/* Set Specified I2C1 Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 1);

				break;

		    case AFIO_USART1:

				/* Reset USART1 Remap Bits */
				AFIO->MAPR &= AFIO_USART1_REMAP_MASK;

				/* Set Specified USART1 Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 2);

				break;

		    case AFIO_USART2:

				/* Reset USART2 Remap Bits */
				AFIO->MAPR &= AFIO_USART2_REMAP_MASK;

				/* Set Specified USART2 Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 3);

				break;

		    case AFIO_USART3:

				/* Reset USART3 Remap Bits */
				AFIO->MAPR &= AFIO_USART3_REMAP_MASK;

				/* Set Specified USART3 Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 4);

				break;

		    case AFIO_TIM1:

				/* Reset TIM1 Remap Bits */
				AFIO->MAPR &= AFIO_TIM1_REMAP_MASK;

				/* Set Specified TIM1 Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 6);

				break;

		    case AFIO_TIM2:

				/* Reset TIM2 Remap Bits */
				AFIO->MAPR &= AFIO_TIM2_REMAP_MASK;

				/* Set Specified TIM2 Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 8);

				break;

		    case AFIO_TIM3:

				/* Reset TIM3 Remap Bits */
				AFIO->MAPR &= AFIO_TIM3_REMAP_MASK;

				/* Set Specified TIM3 Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 10);

				break;

		    case AFIO_TIM4:

				/* Reset TIM4 Remap Bits */
				AFIO->MAPR &= AFIO_TIM4_REMAP_MASK;

				/* Set Specified TIM4 Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 12);

				break;

		    case AFIO_CAN:

				/* Reset CAN Remap Bits */
				AFIO->MAPR &= AFIO_CAN_REMAP_MASK;

				/* Set Specified CAN Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 13);

				break;

		    case AFIO_PD01:

				/* Reset PD01 Remap Bits */
				AFIO->MAPR &= AFIO_PD01_REMAP_MASK;

				/* Set Specified PD01 Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 15);

				break;

		    case AFIO_TIM5CH4:

				/* Reset TIM5CH4 IRemap Bits */
				AFIO->MAPR &= AFIO_TIM5CH4_IREMAP_MASK;

				/* Set Specified TIM5CH4 IRemap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 16);

				break;

		    case AFIO_ADC1_ETRGINJ:

				/* Reset ADC1_ETRGINJ Remap Bits */
				AFIO->MAPR &= AFIO_ADC1_ETRGINJ_REMAP_MASK;

				/* Set Specified ADC1_ETRGINJ Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 17);

				break;

		    case AFIO_ADC1_ETRGREG:

				/* Reset ADC1_ETRGREG Remap Bits */
				AFIO->MAPR &= AFIO_ADC1_ETRGREG_REMAP_MASK;

				/* Set Specified ADC1_ETRGREG Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 18);

				break;

		    case AFIO_ADC2_ETRGINJ:

				/* Reset ADC2_ETRGINJ Remap Bits */
				AFIO->MAPR &= AFIO_ADC2_ETRGINJ_REMAP_MASK;

				/* Set Specified ADC2_ETRGINJ Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 19);

				break;

		    case AFIO_ADC2_ETRGREG:

				/* Reset ADC2_ETRGREG Remap Bits */
				AFIO->MAPR &= AFIO_ADC2_ETRGREG_REMAP_MASK;

				/* Set Specified ADC2_ETRGREG Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 20);

				break;

            case AFIO_SWJ_CFG:

				/* Reset SWJ_CFG Remap Bits */
				AFIO->MAPR &= AFIO_SWJ_CFG_REMAP_MASK;

				/* Set Specified SWJ_CFG Remap Value */
				AFIO->MAPR |= (Copy_FunctionRemapVal << 24);

				break;

            case AFIO_TIM9:

				/* Reset TIM9 Remap Bits */
				AFIO->MAPR2 &= AFIO_TIM9_REMAP_MASK;

				/* Set Specified TIM9 Remap Value */
				AFIO->MAPR2 |= (Copy_FunctionRemapVal << 5);

				break;

            case AFIO_TIM10:

				/* Reset TIM10 Remap Bits */
				AFIO->MAPR2 &= AFIO_TIM10_REMAP_MASK;

				/* Set Specified TIM10 Remap Value */
				AFIO->MAPR2 |= (Copy_FunctionRemapVal << 6);

				break;

            case AFIO_TIM11:

				/* Reset TIM11 Remap Bits */
				AFIO->MAPR2 &= AFIO_TIM11_REMAP_MASK;

				/* Set Specified TIM11 Remap Value */
				AFIO->MAPR2 |= (Copy_FunctionRemapVal << 7);

				break;

            case AFIO_TIM13:

				/* Reset TIM13 Remap Bits */
				AFIO->MAPR2 &= AFIO_TIM13_REMAP_MASK;

				/* Set Specified TIM13 Remap Value */
				AFIO->MAPR2 |= (Copy_FunctionRemapVal << 8);

				break;

            case AFIO_TIM14:

				/* Reset TIM14 Remap Bits */
				AFIO->MAPR2 &= AFIO_TIM14_REMAP_MASK;

				/* Set Specified TIM14 Remap Value */
				AFIO->MAPR2 |= (Copy_FunctionRemapVal << 9);

				break;

            case AFIO_FSMC_NADV:

				/* Reset FSMC_NADV Remap Bits */
				AFIO->MAPR2 &= AFIO_FSMC_NADV_REMAP_MASK;

				/* Set Specified FSMC_NADV Remap Value */
				AFIO->MAPR2 |= (Copy_FunctionRemapVal << 10);

				break;

		    default:

				/* Function is not behaving as expected */
				Local_Status = RT_NOK;
		}
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}
