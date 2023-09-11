/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 7, 2023               	*/
/*      			SWC          : NVIC  			            */
/*     			    Description	 : NVIC Interface               */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*				   _   ___      _______ _____   _____       _             __                                */
/*				  | \ | \ \    / /_   _/ ____| |_   _|     | |           / _|                               */
/*				  |  \| |\ \  / /  | || |        | |  _ __ | |_ ___ _ __| |_ __ _  ___ ___                  */
/*				  | . ` | \ \/ /   | || |        | | | '_ \| __/ _ \ '__|  _/ _` |/ __/ _ \                 */
/*				  | |\  |  \  /   _| || |____   _| |_| | | | ||  __/ |  | || (_| | (_|  __/                 */
/*				  |_| \_|   \/   |_____\_____| |_____|_| |_|\__\___|_|  |_| \__,_|\___\___|                 */
/*						                                                                                    */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef MCAL_NVIC_INTERFACE_H_
#define MCAL_NVIC_INTERFACE_H_

/*------------------------------------------------------------------------------------------------------------*/
/* Notes to consider about NVIC while interfacing :                                                           */
/*                                                                          				                  */
/* 1) NVIC is a core peripheral (Standard) ==> (Low Interrupt Latency)                   		              */
/* 2) NVIC in general supports 255 interrupts divided into 15 internal interrupts and 240 external interrupts */
/* 3) NVIC is a vector table based system                                                		              */
/* 4) NVIC supports independent enable pin for each external interrupt even if it's a NMI                     */
/* 5) NVIC supports nesting especially Normal Nesting and don't support Self Nesting                          */
/* 6) NVIC supports independent set and clear pending flag for each external interrupt for debugging purposes */
/* 7) NVIC supports software and hardware priorities                                                          */
/*                                                                                               	   	      */
/* Important Note : NVIC manages all interrupts but controls only external ones which means that internal     */
/*        	        interrupts caused by core peripherals can only by controlled through their drivers'       */
/* 		            registers 										   					    				  */
/*                                                                                                  	      */
/*                                                                                                  	      */
/*------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	    INTERFACE MACROS		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Available External Interrupts' IDs Connected to NVIC's 240 External Interrupt Pins */
#define NVIC_WWDG                              0U    /* Window watchdog interrupt */
#define NVIC_PVD                               1U    /* PVD through EXTI Line detection interrupt */
#define NVIC_TAMPER                            2U    /* Tamper interrupt */
#define NVIC_RTC                               3U    /* RTC global interrupt */
#define NVIC_FLASH                             4U    /* Flash global interrupt */
#define NVIC_RCC                               5U    /* RCC global interrupt */
#define NVIC_EXTI0                             6U    /* EXTI Line0 interrupt */
#define NVIC_EXTI1                             7U    /* EXTI Line1 interrupt */
#define NVIC_EXTI2                             8U    /* EXTI Line2 interrupt */
#define NVIC_EXTI3                             9U    /* EXTI Line3 interrupt */
#define NVIC_EXTI4                             10U   /* EXTI Line4 interrupt */
#define NVIC_DMA1_Channel1                     11U   /* DMA1 Channel1 global interrupt */
#define NVIC_DMA1_Channel2                     12U   /* DMA1 Channel2 global interrupt */
#define NVIC_DMA1_Channel3                     13U   /* DMA1 Channel3 global interrupt */
#define NVIC_DMA1_Channel4                     14U   /* DMA1 Channel4 global interrupt */
#define NVIC_DMA1_Channel5                     15U   /* DMA1 Channel5 global interrupt */
#define NVIC_DMA1_Channel6                     16U   /* DMA1 Channel6 global interrupt */
#define NVIC_DMA1_Channel7                     17U   /* DMA1 Channel7 global interrupt */
#define NVIC_ADC1_2                            18U   /* ADC1 and ADC2 global interrupt */
#define NVIC_USB_HP_CAN_TX                     19U   /* USB High Priority or CAN TX interrupts */
#define NVIC_USB_LP_CAN_RX0                    20U   /* USB Low Priority or CAN RX0 interrupts */
#define NVIC_CAN_RX1                           21U   /* CAN RX1 interrupt */
#define NVIC_CAN_SCE                           22U   /* CAN SCE interrupt */
#define NVIC_EXTI9_5                           23U   /* EXTI Line[9:5] interrupts */
#define NVIC_TIM1_BRK                          24U   /* TIM1 Break interrupt */
#define NVIC_TIM1_UP                           25U   /* TIM1 Update interrupt */
#define NVIC_TIM1_TRG_COM                      26U   /* TIM1 Trigger and Commutation interrupts */
#define NVIC_TIM1_CC                           27U   /* TIM1 Capture Compare interrupt */
#define NVIC_TIM2                              28U   /* TIM2 global interrupt */
#define NVIC_TIM3                              29U   /* TIM3 global interrupt */
#define NVIC_TIM4                              30U   /* TIM4 global interrupt */
#define NVIC_I2C1_EV                           31U   /* I2C1 event interrupt */
#define NVIC_I2C1_ER                           32U   /* I2C1 error interrupt */
#define NVIC_I2C2_EV                           33U   /* I2C2 event interrupt */
#define NVIC_I2C2_ER                           34U   /* I2C2 error interrupt */
#define NVIC_SPI1                              35U   /* SPI1 global interrupt */
#define NVIC_SPI2                              36U   /* SPI2 global interrupt */
#define NVIC_USART1                            37U   /* USART1 global interrupt */
#define NVIC_USART2                            38U   /* USART2 global interrupt */
#define NVIC_USART3                            39U   /* USART3 global interrupt */
#define NVIC_EXTI15_10                         40U   /* EXTI Line[15:10] interrupts */
#define NVIC_RTCAlarm                          41U   /* RTC alarm through EXTI line interrupt */
#define NVIC_USBWakeup                         42U   /* USB wakeup from suspend through EXTI line interrupt */
#define NVIC_TIM8_BRK                          43U   /* TIM8 Break interrupt */
#define NVIC_TIM8_UP                           44U   /* TIM8 Update interrupt */
#define NVIC_TIM8_TRG_COM                      45U   /* TIM8 Trigger and Commutation interrupts */
#define NVIC_TIM8_CC                           46U   /* TIM8 Capture Compare interrupt */
#define NVIC_ADC3                              47U   /* ADC3 global interrupt */
#define NVIC_FSMC                              48U   /* FSMC global interrupt */
#define NVIC_SDIO                              49U   /* SDIO global interrupt */
#define NVIC_TIM5                              50U   /* TIM5 global interrupt */
#define NVIC_SPI3                              51U   /* SPI3 global interrupt */
#define NVIC_UART4                             52U   /* UART4 global interrupt */
#define NVIC_UART5                             53U   /* UART5 global interrupt */
#define NVIC_TIM6                              54U   /* TIM6 global interrupt */
#define NVIC_TIM7                              55U   /* TIM7 global interrupt */
#define NVIC_DMA2_Channel1                     56U   /* DMA2 Channel1 global interrupt */
#define NVIC_DMA2_Channel2                     57U   /* DMA2 Channel2 global interrupt */
#define NVIC_DMA2_Channel3                     58U   /* DMA2 Channel3 global interrupt */
#define NVIC_DMA2_Channel4_5                   59U   /* DMA2 Channel4 and DMA2 Channel5 global interrupts */

/* NVIC Interrupt Active Flags */
#define NVIC_INTERRUPT_NOT_ACTIVE			   0U    /* Vector Interrupt not active */
#define NVIC_INTERRUPT_ACTIVE				   1U    /* Vector Interrupt active */

/* Available NVIC Interrupt Group Priorities */
#define NVIC_GROUP_PRIORITY_0                  0b0000  /* Interrupt Group Priority 0  */
#define NVIC_GROUP_PRIORITY_1                  0b0001  /* Interrupt Group Priority 1  */
#define NVIC_GROUP_PRIORITY_2                  0b0010  /* Interrupt Group Priority 2  */
#define NVIC_GROUP_PRIORITY_3                  0b0011  /* Interrupt Group Priority 3  */
#define NVIC_GROUP_PRIORITY_4                  0b0100  /* Interrupt Group Priority 4  */
#define NVIC_GROUP_PRIORITY_5                  0b0101  /* Interrupt Group Priority 5  */
#define NVIC_GROUP_PRIORITY_6                  0b0110  /* Interrupt Group Priority 6  */
#define NVIC_GROUP_PRIORITY_7                  0b0111  /* Interrupt Group Priority 7  */
#define NVIC_GROUP_PRIORITY_8                  0b1000  /* Interrupt Group Priority 8  */
#define NVIC_GROUP_PRIORITY_9                  0b1001  /* Interrupt Group Priority 9  */
#define NVIC_GROUP_PRIORITY_10                 0b1010  /* Interrupt Group Priority 10 */
#define NVIC_GROUP_PRIORITY_11                 0b1011  /* Interrupt Group Priority 11 */
#define NVIC_GROUP_PRIORITY_12                 0b1100  /* Interrupt Group Priority 12 */
#define NVIC_GROUP_PRIORITY_13                 0b1101  /* Interrupt Group Priority 13 */
#define NVIC_GROUP_PRIORITY_14                 0b1110  /* Interrupt Group Priority 14 */
#define NVIC_GROUP_PRIORITY_15                 0b1111  /* Interrupt Group Priority 15 */
#define NVIC_GROUP_PRIORITY_NONE               16U	   /* No Interrupt Group Priority */

/* Available NVIC Interrupt Sub Priorities */
#define NVIC_SUB_PRIORITY_0                    0b0000   /* Interrupt Sub Priority 0  */
#define NVIC_SUB_PRIORITY_1                    0b0001   /* Interrupt Sub Priority 1  */
#define NVIC_SUB_PRIORITY_2                    0b0010   /* Interrupt Sub Priority 2  */
#define NVIC_SUB_PRIORITY_3                    0b0011   /* Interrupt Sub Priority 3  */
#define NVIC_SUB_PRIORITY_4                    0b0100   /* Interrupt Sub Priority 4  */
#define NVIC_SUB_PRIORITY_5                    0b0101   /* Interrupt Sub Priority 5  */
#define NVIC_SUB_PRIORITY_6                    0b0110   /* Interrupt Sub Priority 6  */
#define NVIC_SUB_PRIORITY_7                    0b0111   /* Interrupt Sub Priority 7  */
#define NVIC_SUB_PRIORITY_8                    0b1000   /* Interrupt Sub Priority 8  */
#define NVIC_SUB_PRIORITY_9                    0b1001   /* Interrupt Sub Priority 9  */
#define NVIC_SUB_PRIORITY_10                   0b1010   /* Interrupt Sub Priority 10 */
#define NVIC_SUB_PRIORITY_11                   0b1011   /* Interrupt Sub Priority 11 */
#define NVIC_SUB_PRIORITY_12                   0b1100   /* Interrupt Sub Priority 12 */
#define NVIC_SUB_PRIORITY_13                   0b1101   /* Interrupt Sub Priority 13 */
#define NVIC_SUB_PRIORITY_14                   0b1110   /* Interrupt Sub Priority 14 */
#define NVIC_SUB_PRIORITY_15                   0b1111   /* Interrupt Sub Priority 15 */
#define NVIC_SUB_PRIORITY_NONE                 16U		/* No Interrupt Sub Priority */

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  FUNCTIONS PROTOTYPES		          	             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: EnableVectorInterrupt                                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_VectorId 										  */
/*                 Ex:(NVIC_WWDG,....,NVIC_DMA2_Channel4_5)                       */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                 */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Enables any maskable external interrupt connected to NVIC      */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t NVIC_EnableVectorInterrupt(uint8_t Copy_VectorId);

/*--------------------------------------------------------------------------------*/
/* @Function Name: DisableVectorInterrupt                                         */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_VectorId 										  */
/*				   Ex:(NVIC_WWDG,....,NVIC_DMA2_Channel4_5)						  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                 */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Disables any maskable external interrupt connected to NVIC     */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t NVIC_DisableVectorInterrupt(uint8_t Copy_VectorId);

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetVectorInterruptPendingFlag                                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_VectorId 										  */
/* 	 	 	 	   Ex:(NVIC_WWDG,....,NVIC_DMA2_Channel4_5) 					  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                 */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Forces any maskable external interrupt connected to NVIC into  */
/*                 the pending state through setting its pending flag             */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t NVIC_SetVectorInterruptPendingFlag(uint8_t Copy_VectorId);

/*--------------------------------------------------------------------------------*/
/* @Function Name: ClearVectorInterruptPendingFlag                                */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_VectorId 										  */
/*				   Ex:(NVIC_WWDG,....,NVIC_DMA2_Channel4_5) 					  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                 */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Remove the pending state from any external interrupt connected */
/*				   to NVIC through clearing its pending flag 					  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t NVIC_ClearVectorInterruptPendingFlag(uint8_t Copy_VectorId);

/*----------------------------------------------------------------------------------*/
/* @Function Name: GetVectorInterruptActiveFlag                                     */
/*----------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_VectorId 										    */
/*				   Ex:(NVIC_WWDG,....,NVIC_DMA2_Channel4_5)	 				    	*/
/*----------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                             */
/*----------------------------------------------------------------------------------*/
/* @Param(out)	 : uint8_t* Copy_pVectorActiveFlagStatus 						    */
/*				   Ex:(NVIC_INTERRUPT_ACTIVE, NVIC_INTERRUPT_NOT_ACTIVE)            */
/*----------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                   */
/*----------------------------------------------------------------------------------*/
/* @Description	 : This function indicates the status of each vector interrupt      */
/*                 whether it's active or not                                       */
/*----------------------------------------------------------------------------------*/
ERROR_STATUS_t NVIC_GetVectorInterruptActiveFlag(uint8_t Copy_VectorId , uint8_t* Copy_pVectorActiveFlagStatus);

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetVectorInterruptPriority	                                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_VectorId 										  */
/*				   Ex:(NVIC_WWDG,....,NVIC_DMA2_Channel4_5) 					  */
/*				   uint8_t Copy_VectorGroupPriority								  */
/*				   Ex: (NVIC_GROUP_PRORITY_0 ..... NVIC_GROUP_PRORITY_15)		  */
/*				   or  NVIC_GROUP_PRORITY_NONE 						              */
/*				   uint8_t Copy_VectorSubPriority								  */
/*				   Ex: (NVIC_SUB_PRORITY_0 ..... NVIC_SUB_PRORITY_15)			  */
/*				   or  NVIC_SUB_PRORITY_NONE 						              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                 */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Sets the software priority of any external interrupt connected */
/*				   to NVIC through specifying its group and sub priorities   	  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t NVIC_SetVectorInterruptPriority(uint8_t Copy_VectorId , uint8_t Copy_VectorGroupPriority , uint8_t Copy_VectorSubPriority);

#endif /* MCAL_NVIC_INTERFACE_H_ */
