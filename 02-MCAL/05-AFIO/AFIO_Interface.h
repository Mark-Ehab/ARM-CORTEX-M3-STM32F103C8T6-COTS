/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 17, 2023               	*/
/*      			SWC          : AFIO  			            */
/*     			    Description	 : AFIO Interface               */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*  						  ______ _____ ____    _____       _             __                             */
/*  					/\   |  ____|_   _/ __ \  |_   _|     | |           / _|                            */
/*  				   /  \  | |__    | || |  | |   | |  _ __ | |_ ___ _ __| |_ __ _  ___ ___               */
/*  				  / /\ \ |  __|   | || |  | |   | | | '_ \| __/ _ \ '__|  _/ _` |/ __/ _ \              */
/*  				 / ____ \| |     _| || |__| |  _| |_| | | | ||  __/ |  | || (_| | (_|  __/              */
/*  				/_/    \_\_|    |_____\____/  |_____|_| |_|\__\___|_|  |_| \__,_|\___\___|              */
/*																								            */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef AFIO_MCAL_INTERFACE_H_
#define AFIO_MCAL_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	    INTERFACE MACROS		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
/* External Interrupt Lines */
#define AFIO_EXTI_LINE_0               0U
#define AFIO_EXTI_LINE_1               1U
#define AFIO_EXTI_LINE_2               2U
#define AFIO_EXTI_LINE_3               3U
#define AFIO_EXTI_LINE_4               4U
#define AFIO_EXTI_LINE_5               5U
#define AFIO_EXTI_LINE_6               6U
#define AFIO_EXTI_LINE_7               7U
#define AFIO_EXTI_LINE_8               8U
#define AFIO_EXTI_LINE_9               9U
#define AFIO_EXTI_LINE_10              10U
#define AFIO_EXTI_LINE_11              11U
#define AFIO_EXTI_LINE_12              12U
#define AFIO_EXTI_LINE_12              12U
#define AFIO_EXTI_LINE_14              14U
#define AFIO_EXTI_LINE_15              15U

/* EXTI Lines Port Mappings */
#define AFIO_PORTA  		           0b0000
#define AFIO_PORTB  		           0b0001
#define AFIO_PORTC  		           0b0010

/* Alternative Functions Remap Types*/
#define AFIO_SPI1                      0U
#define AFIO_I2C1                      1U
#define AFIO_USART1                    2U
#define AFIO_USART2                    3U
#define AFIO_USART3                    4U
#define AFIO_TIM1                      5U
#define AFIO_TIM2                      6U
#define AFIO_TIM3                      7U
#define AFIO_TIM4                      8U
#define AFIO_CAN                       9U
#define AFIO_PD01                     10U
#define AFIO_TIM5CH4                  11U
#define AFIO_ADC1_ETRGINJ             12U
#define AFIO_ADC1_ETRGREG             13U
#define AFIO_ADC2_ETRGINJ             14U
#define AFIO_ADC2_ETRGREG             15U
#define AFIO_SWJ_CFG                  16U
#define AFIO_TIM9                     17U
#define AFIO_TIM10                    18U
#define AFIO_TIM11                    19U
#define AFIO_TIM13                    20U
#define AFIO_TIM14                    21U
#define AFIO_FSMC_NADV                22U

/* Alternative Functions Remap Values */

/* SPI1 Remap Values */
#define AFIO_SPI1_NO_REMAP	           0x00000000U
#define AFIO_SPI1_REMAP			       0x00000001U

/* I2C1 Remap Values */
#define AFIO_I2C1_NO_REMAP	           0x00000000U
#define AFIO_I2C1_REMAP			       0x00000001U

/* USART1 Remap Values */
#define AFIO_USART1_NO_REMAP	       0x00000000U
#define AFIO_USART1_REMAP		       0x00000001U

/* USART2 Remap Values */
#define AFIO_USART2_NO_REMAP	       0x00000000U
#define AFIO_USART2_REMAP		       0x00000001U

/* USART3 Remap Values */
#define AFIO_USART3_NO_REMAP	       0x00000000U
#define AFIO_USART3_PARTIAL_REMAP	   0x00000001U
#define AFIO_USART3_FULL_REMAP		   0x00000003U

/* TIM1 Remap Values */
#define AFIO_TIM1_NO_REMAP	           0x00000000U
#define AFIO_TIM1_PARTIAL_REMAP	       0x00000001U
#define AFIO_TIM1_FULL_REMAP		   0x00000003U

/* TIM2 Remap Values */
#define AFIO_TIM2_NO_REMAP	           0x00000000U
#define AFIO_TIM2_PARTIAL_REMAP1 	   0x00000001U
#define AFIO_TIM2_PARTIAL_REMAP2 	   0x00000002U
#define AFIO_TIM2_FULL_REMAP		   0x00000003U

/* TIM3 Remap Values */
#define AFIO_TIM3_NO_REMAP	           0x00000000U
#define AFIO_TIM3_PARTIAL_REMAP	       0x00000001U
#define AFIO_TIM3_FULL_REMAP		   0x00000003U

/* TIM4 Remap Values */
#define AFIO_TIM4_NO_REMAP	           0x00000000U
#define AFIO_TIM4_FULL_REMAP		   0x00000001U

/* CAN Remap Values */
#define AFIO_CANRX_PA11_CANTX_PA12     0x00000000U
#define AFIO_CANRX_PB8_CANTX_PB9       0x00000002U
#define AFIO_CANRX_PD0_CANTX_PD0       0x00000003U

/* PD01 Remap Values */
#define AFIO_PD01_NO_REMAP			   0x00000000U
#define AFIO_PD0_OSC_IN_PD1_OSC_OUT    0x00000001U

/* TIM5 Channel4 Internal Remap Values */
#define AFIO_TIM5_CH4_PA3              0x00000000U
#define AFIO_TIM5_CH4_LSI              0x00000001U

/* ADC 1 External Trigger Injected Conversion Remapping Values */
#define AFIO_ADC1_EXTI15               0x00000000U
#define AFIO_ADC1_TIM8_CH4             0x00000001U

/* ADC 1 external Trigger Regular Conversion Remapping Values */
#define AFIO_ADC1_EXTI11               0x00000000U
#define AFIO_ADC1_TIM8_TRG0            0x00000001U

/* ADC 2 External Trigger Injected Conversion Remapping Values */
#define AFIO_ADC2_EXTI15               0x00000000U
#define AFIO_ADC2_TIM8_CH4             0x00000001U

/* ADC 2 External Trigger Regular Conversion Remapping Values */
#define AFIO_ADC2_EXTI11               0x00000000U
#define AFIO_ADC2_TIM8_TRG0            0x00000001U

/* Serial Wire JTAG Configuration */
#define AFIO_Full_SWJ				   0x00000000U
#define AFIO_Full_SWJ_No_NJTRST	       0x00000001U
#define AFIO_SW_DP_N0_JTAG_DP	       0x00000002U
#define AFIO_JTAG_DP_N0_SW_DP	       0x00000004U

/* TIM9 Remap Values */
#define AFIO_TIM9_NO_REMAP	           0x00000000U
#define AFIO_TIM9_REMAP			       0x00000001U

/* TIM10 Remap Values */
#define AFIO_TIM10_NO_REMAP	           0x00000000U
#define AFIO_TIM10_REMAP			   0x00000001U

/* TIM11 Remap Values */
#define AFIO_TIM11_NO_REMAP	           0x00000000U
#define AFIO_TIM11_REMAP			   0x00000001U

/* TIM13 Remap Values */
#define AFIO_TIM13_NO_REMAP	           0x00000000U
#define AFIO_TIM13_REMAP			   0x00000001U

/* TIM14 Remap Values */
#define AFIO_TIM14_NO_REMAP	           0x00000000U
#define AFIO_TIM14_REMAP			   0x00000001U

/* NADV Connect/Disconnect */
#define AFIO_NADV_CONNECT              0x00000000U
#define AFIO_NADV_DISCONNECT           0x00000001U

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  FUNCTIONS PROTOTYPES		          	             */
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
ERROR_STATUS_t AFIO_SetEXTIConfiguration(uint8_t Copy_EXTILine , uint8_t Copy_PortMap);

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
ERROR_STATUS_t AFIO_AlternativeFunctionRemap(uint8_t Copy_FunctionRemapType,uint32_t Copy_FunctionRemapVal);

#endif /* AFIO_MCAL_INTERFACE_H_ */
