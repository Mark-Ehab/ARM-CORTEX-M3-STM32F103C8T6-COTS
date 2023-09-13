/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 7, 2023               	*/
/*      			SWC          : RCC  			            */
/*     			    Description	 : RCC Interface                */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						  _____   _____ _____   _____       _             __                                */
/*						 |  __ \ / ____/ ____| |_   _|     | |           / _|                               */
/*						 | |__) | |   | |        | |  _ __ | |_ ___ _ __| |_ __ _  ___ ___                  */
/*						 |  _  /| |   | |        | | | '_ \| __/ _ \ '__|  _/ _` |/ __/ _ \                 */
/*						 | | \ \| |___| |____   _| |_| | | | ||  __/ |  | || (_| | (_|  __/                 */
/*						 |_|  \_\\_____\_____| |_____|_| |_|\__\___|_|  |_| \__,_|\___\___|                 */
/*						                                                                               	    */
/*                                                                                                		    */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef RCC_MCAL_INTERFACE_H_
#define RCC_MCAL_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	    INTERFACE MACROS		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Bus IDs */
#define RCC_AHB                              0U			/* Advanced High-Performance Bus */
#define RCC_APB1                             1U			/* Advanced Peripheral Bus 1 */
#define RCC_APB2                             2U			/* Advanced Peripheral Bus 2 */

/* Peripheral IDs */

/* Peripherals Connected on AHB Bus */
#define RCC_DMA1							 0U			/* DMA1 ID */
#define RCC_DMA2                             1U         /* DMA2 ID */
#define RCC_SRAM		                     2U         /* SRAM interface ID */
#define RCC_FLITF                            4U         /* FLITF ID */
#define RCC_CRC                              6U         /* CRC ID */
#define RCC_FSMC                             8U         /* FSMC ID */
#define RCC_SDIO                             10U        /* SDIO ID */

/* Peripherals Connected on APB2 Bus */
#define RCC_AFIO							 0U         /* Alternate function IO ID */
#define RCC_GPIOA                            2U         /* IO port A ID */
#define RCC_GPIOB                            3U         /* IO port B ID */
#define RCC_GPIOC                            4U         /* IO port C ID */
#define RCC_GPIOD                            5U         /* IO port D ID */
#define RCC_GPIOE                            6U         /* IO port E ID */
#define RCC_GPIOF                            7U         /* IO port F ID */
#define RCC_GPIOG                            8U         /* IO port G ID */
#define RCC_ADC1                             9U         /* ADC 1 interface ID */
#define RCC_ADC2                             10U        /* ADC 2 interface ID */
#define RCC_TIM1                             11U        /* TIM1 timer ID */
#define RCC_SPI1                             12U        /* SPI1 ID */
#define RCC_TIM8                             13U        /* TIM8 Timer ID */
#define RCC_USART1                           14U        /* USART1 ID */
#define RCC_ADC3                             15U        /* ADC3 interface ID */
#define RCC_TIM9                             19U        /* TIM9 timer ID */
#define RCC_TIM10                            20U        /* TIM10 timer ID */
#define RCC_TIM11                            21U        /* TIM11 timer ID */

/* Peripherals Connected on APB1 Bus */
#define RCC_TIM2                             0U         /* TIM2 timer ID */
#define RCC_TIM3                             1U         /* TIM3 timer ID */
#define RCC_TIM4                             2U         /* TIM4 timer ID */
#define RCC_TIM5                             3U         /* TIM5 timer ID */
#define RCC_TIM6                             4U         /* TIM6 timer ID */
#define RCC_TIM7                             5U         /* TIM7 timer ID */
#define RCC_TIM12                            6U         /* TIM12 timer ID */
#define RCC_TIM13                            7U         /* TIM13 timer ID */
#define RCC_TIM14                            8U         /* TIM14 timer ID */
#define RCC_WWDG                             11U        /* Window watchdog ID */
#define RCC_SPI2                             14U        /* SPI2 ID */
#define RCC_SPI3                             15U        /* SPI3 ID */
#define RCC_USART2                           17U        /* USART2 ID */
#define RCC_USART3                           18U        /* USART3 ID */
#define RCC_UART4                            19U        /* USART4 ID */
#define RCC_UART5                            20U        /* USART5 ID */
#define RCC_I2C1                             21U        /* I2C1 ID */
#define RCC_I2C2                             22U        /* I2C2 ID */
#define RCC_USB                              23U        /* USB ID */
#define RCC_CAN                              25U        /* CAN ID */
#define RCC_BKP                              27U        /* Backup interface ID */
#define RCC_PWR                              28U        /* Power interface ID */
#define RCC_DAC                              29U        /* DAC interface ID */

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  FUNCTIONS PROTOTYPES		          	             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: Init							                                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Initialize RCC through setting the clock for the system		  */
/* 				   and its type based on configuration file						  */
/*--------------------------------------------------------------------------------*/
void RCC_Init(void);

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
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Enables clock for any peripheral based on passed peripheral ID */
/* 				   and bus ID to which the peripheral is connected				  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t RCC_EnablePeripheralClk(uint8_t Copy_BusId , uint8_t Copy_PeripheralId);

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
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Disables clock for any peripheral based on passed peripheral   */
/* 				   ID and bus ID to which the peripheral is connected			  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t RCC_DisablePeripheralClk(uint8_t Copy_BusId , uint8_t Copy_PeripheralId);

#endif /* RCC_MCAL_INTERFACE_H_ */
