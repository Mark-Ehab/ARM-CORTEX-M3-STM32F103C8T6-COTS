/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 10, 2023               	*/
/*      			SWC          : EXTI  			            */
/*     			    Description	 : EXTI Config                  */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						   ________   _________ _____    _____             __ _                             */
/*						  |  ____\ \ / /__   __|_   _|  / ____|           / _(_)                            */
/*						  | |__   \ V /   | |    | |   | |     ___  _ __ | |_ _  __ _                       */
/*						  |  __|   > <    | |    | |   | |    / _ \| '_ \|  _| |/ _` |                      */
/*						  | |____ / . \   | |   _| |_  | |___| (_) | | | | | | | (_| |                      */
/*						  |______/_/ \_\  |_|  |_____|  \_____\___/|_| |_|_| |_|\__, |                      */
/*						                                                      	 __/ |                      */
/*		                                                                        |___/                       */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef EXTI_MCAL_CONFIG_H_
#define EXTI_MCAL_CONFIG_H_

/*-------------------------------------------------------*/
/* Enable/Disable EXTI Interrupt :- 			 		 */
/*                                                       */
/* Options: - ENABLE	                                 */
/*			- DISABLE						           	 */
/*														 */
/* Note   : These configurations are for STM32F103C8T6 	 */
/*			MCU only                                     */
/*														 */
/*-------------------------------------------------------*/
#define EXTI_INT_LINE_0      DISABLE
#define EXTI_INT_LINE_1      DISABLE
#define EXTI_INT_LINE_2      DISABLE
#define EXTI_INT_LINE_3      DISABLE
#define EXTI_INT_LINE_4      DISABLE
#define EXTI_INT_LINE_5      DISABLE
#define EXTI_INT_LINE_6      DISABLE
#define EXTI_INT_LINE_7      DISABLE
#define EXTI_INT_LINE_8      DISABLE
#define EXTI_INT_LINE_9      DISABLE
#define EXTI_INT_LINE_10     DISABLE
#define EXTI_INT_LINE_11     DISABLE
#define EXTI_INT_LINE_12     DISABLE
#define EXTI_INT_LINE_13     DISABLE
#define EXTI_INT_LINE_14     DISABLE
#define EXTI_INT_LINE_15     DISABLE

/*-------------------------------------------------------*/
/* Enable/Disable EXTI Event :- 				 		 */
/*                                                       */
/* Options: - ENABLE	                                 */
/*			- DISABLE						           	 */
/*														 */
/* Note   : These configurations are for STM32F103C8T6 	 */
/*			MCU only                                     */
/*														 */
/*-------------------------------------------------------*/
#define EXTI_EVENT_LINE_0    DISABLE
#define EXTI_EVENT_LINE_1    DISABLE
#define EXTI_EVENT_LINE_2    DISABLE
#define EXTI_EVENT_LINE_3    DISABLE
#define EXTI_EVENT_LINE_4    DISABLE
#define EXTI_EVENT_LINE_5    DISABLE
#define EXTI_EVENT_LINE_6    DISABLE
#define EXTI_EVENT_LINE_7    DISABLE
#define EXTI_EVENT_LINE_8    DISABLE
#define EXTI_EVENT_LINE_9    DISABLE
#define EXTI_EVENT_LINE_10   DISABLE
#define EXTI_EVENT_LINE_11   DISABLE
#define EXTI_EVENT_LINE_12   DISABLE
#define EXTI_EVENT_LINE_13   DISABLE
#define EXTI_EVENT_LINE_14   DISABLE
#define EXTI_EVENT_LINE_15   DISABLE

/*-------------------------------------------------------*/
/* Enable/Disable EXTI Interrupt Rising Trigger :- 	     */
/*                                                       */
/* Options: - ENABLE	                                 */
/*			- DISABLE						           	 */
/*														 */
/* Note   : These configurations are for STM32F103C8T6 	 */
/*			MCU only                                     */
/*														 */
/*-------------------------------------------------------*/
#define EXTI_RISING_EDGE_TRIGGER_LINE_0     DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_1     DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_2     DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_3     DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_4     DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_5     DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_6     DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_7     DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_8     DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_9     DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_10    DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_11    DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_12    DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_13    DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_14    DISABLE
#define EXTI_RISING_EDGE_TRIGGER_LINE_15    DISABLE

/*-------------------------------------------------------*/
/* Enable/Disable EXTI Interrupt Falling Trigger :- 	 */
/*                                                       */
/* Options: - ENABLE	                                 */
/*			- DISABLE						           	 */
/*														 */
/* Note   : These configurations are for STM32F103C8T6 	 */
/*			MCU only                                     */
/*														 */
/*-------------------------------------------------------*/
#define EXTI_FALLING_EDGE_TRIGGER_LINE_0    DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_1    DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_2    DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_3    DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_4    DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_5    DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_6    DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_7    DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_8    DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_9    DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_10   DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_11   DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_12   DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_13   DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_14   DISABLE
#define EXTI_FALLING_EDGE_TRIGGER_LINE_15   DISABLE

#endif /* EXTI_MCAL_CONFIG_H_ */
