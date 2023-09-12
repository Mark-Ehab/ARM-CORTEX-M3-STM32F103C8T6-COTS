/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 7, 2023               	*/
/*      			SWC          : NVIC  			            */
/*     			    Description	 : NVIC Config                  */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*							  _____   _____ _____    _____             __ _                                 */
/*							 |  __ \ / ____/ ____|  / ____|           / _(_)                                */
/*							 | |__) | |   | |      | |     ___  _ __ | |_ _  __ _                           */
/*							 |  _  /| |   | |      | |    / _ \| '_ \|  _| |/ _` |                          */
/*							 | | \ \| |___| |____  | |___| (_) | | | | | | | (_| |                          */
/*							 |_|  \_\\_____\_____|  \_____\___/|_| |_|_| |_|\__, |                          */
/*							                                                __/ |                           */
/*			                                                                |___/                           */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef RCC_MCAL_CONFIG_H_
#define RCC_MCAL_CONFIG_H_

/*-------------------------------------------------------*/
/* Select which RCC clocks to be enabled :- 			 */
/*                                                       */
/* Options: - HSI_ON                                     */
/*			- HSE_ON                                     */
/*			- PLL_ON                                     */
/*			- HSI_AND_HSE_ON 						     */
/*			- HSI_AND_PLLON 						     */
/*			- HSE_AND_PLL_ON 						     */
/*			- HSI_AND_HSE_AND_PLL_ON 				     */
/*														 */
/*-------------------------------------------------------*/
#define RCC_CLK_ENABLE	HSE_ON /* Default: HSI_ON */

/*-------------------------------------------------------*/
/* Select which RCC clock to be system clock :- 	     */
/*                                                       */
/* Options: - HSI                                        */
/*			- HSE                                        */
/*			- PLL                                        */
/*														 */
/*-------------------------------------------------------*/
#define RCC_SYSTEM_CLK	HSE /* Default: HSI */

/*-------------------------------------------------------*/
/* Select the type of RCC HSE clock oscillator :- 	     */
/*                                                       */
/* Options: - HSE_RC                                     */
/*			- HSE_CRYSTAL                                */
/*			- HSE_CERAMIC                                */
/*														 */
/* Note   : Selected only if HSE is enabled				 */
/*-------------------------------------------------------*/
#define RCC_HSE_CLK	HSE_CRYSTAL /* Default: HSE_CRYSTAL */

/*-------------------------------------------------------*/
/* Select AHB clock prescaler :- 			    	     */
/*                                                       */
/* Options: - SYSCLK_NOT_DIVIDED                         */
/*			- SYSCLK_DIV_BY_2                            */
/*			- SYSCLK_DIV_BY_4                            */
/*          - SYSCLK_DIV_BY_8                            */
/*          - SYSCLK_DIV_BY_16                           */
/*          - SYSCLK_DIV_BY_64                           */
/*          - SYSCLK_DIV_BY_128                          */
/*          - SYSCLK_DIV_BY_256                          */
/*          - SYSCLK_DIV_BY_512                          */
/*														 */
/*-------------------------------------------------------*/
#define RCC_AHB_CLK_PRESCALER	SYSCLK_NOT_DIVIDED /* Default: SYSCLK_NOT_DIVIDED */

/*-------------------------------------------------------*/
/* Select APB1 clock prescaler :- 			    	     */
/*                                                       */
/* Options: - HCLK_NOT_DIVIDED                     		 */
/*			- HCLK_DIV_BY_2                         	 */
/*			- HCLK_DIV_BY_4                         	 */
/*          - HCLK_DIV_BY_8                         	 */
/*          - HCLK_DIV_BY_16                             */
/*														 */
/* Warning: The software has to set correctly these bits */
/*			to not exceed 36 MHz on this domain			 */
/*-------------------------------------------------------*/
#define RCC_APB1_CLK_PRESCALER    HCLK_NOT_DIVIDED /* Default: HCLK_NOT_DIVIDED */

/*-------------------------------------------------------*/
/* Select APB2 clock prescaler :- 			    	     */
/*                                                       */
/* Options: - HCLK_NOT_DIVIDED                     		 */
/*			- HCLK_DIV_BY_2                         	 */
/*			- HCLK_DIV_BY_4                         	 */
/*          - HCLK_DIV_BY_8                         	 */
/*          - HCLK_DIV_BY_16                             */
/*														 */
/*-------------------------------------------------------*/
#define RCC_APB2_CLK_PRESCALER    HCLK_NOT_DIVIDED /* Default: HCLK_NOT_DIVIDED */

/*-------------------------------------------------------*/
/* Select PLL entry clock source :- 	    			 */
/*                                                       */
/* Options: - PLL_HSI_DIV_BY_2                           */
/*			- PLL_HSE		                             */
/*														 */
/* Note   : Selected only if PLL is enabled				 */
/*-------------------------------------------------------*/
#define RCC_PLL_CLK_ENTRY   PLL_HSI_DIV_BY_2 /* Default: PLL_HSI_DIV_BY_2 */

/*-------------------------------------------------------*/
/* Select HSE divider for PLL entry :- 	    			 */
/*                                                       */
/* Options: - PLL_DIV_FACTOR_HSE                         */
/*			- PLL_DIV_FACTOR_HSE_DIV_BY_2 		         */
/*														 */
/* Note   : Selected only if PLL is enabled				 */
/*-------------------------------------------------------*/
#define RCC_PLL_HSE_DIV_FACTOR   PLL_DIV_FACTOR_HSE /* Default: PLL_DIV_FACTOR_HSE */

/*-------------------------------------------------------*/
/* Select PLL multiplication factor :- 	    			 */
/*                                                       */
/* Options: - PLL_MUL_BY_2                               */
/*   		- PLL_MUL_BY_3                               */
/*          - PLL_MUL_BY_4                               */
/*          - PLL_MUL_BY_5                               */
/*          - PLL_MUL_BY_6                               */
/*          - PLL_MUL_BY_7                               */
/*          - PLL_MUL_BY_8                               */
/*          - PLL_MUL_BY_9                               */
/*          - PLL_MUL_BY_10                              */
/*          - PLL_MUL_BY_11                              */
/*          - PLL_MUL_BY_12                              */
/*          - PLL_MUL_BY_13                              */
/*          - PLL_MUL_BY_14                              */
/*          - PLL_MUL_BY_15                              */
/*          - PLL_MUL_BY_16                              */
/*          - PLL_MUL_BY_16                              */
/*                                                       */
/* Note   : Selected only if PLL is enabled				 */
/* Caution: The PLL output frequency must not exceed 72  */
/*          MHz										     */
/*-------------------------------------------------------*/
#define RCC_PLL_MUL_FACTOR   PLL_MUL_BY_2 /* Default: PLL_MUL_BY_2 */

/*-------------------------------------------------------*/
/* Select microcontroller clock output (MCO):- 	    	 */
/*                                                       */
/* Options: - MCO_NO_CLK                                 */
/*			- MCO_SYSCLK                                 */
/*          - MCO_HSI_CLK                                */
/*          - MCO_HSE_CLK                                */
/*          - MCO_PLL_DIV_BY_2_CLK                       */
/*                                                       */
/*-------------------------------------------------------*/
#define RCC_MCU_CLK_OUTPUT	MCO_NO_CLK /* Default: MCO_NO_CLK */

#endif /* RCC_MCAL_CONFIG_H_ */
