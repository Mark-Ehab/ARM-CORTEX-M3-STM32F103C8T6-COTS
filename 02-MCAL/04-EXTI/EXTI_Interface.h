/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 10, 2023               	*/
/*      			SWC          : EXTI  			            */
/*     			    Description	 : EXTI Interface               */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*				   ________   _________ _____   _____       _             __                                */
/*				  |  ____\ \ / /__   __|_   _| |_   _|     | |           / _|                               */
/*				  | |__   \ V /   | |    | |     | |  _ __ | |_ ___ _ __| |_ __ _  ___ ___                  */
/*				  |  __|   > <    | |    | |     | | | '_ \| __/ _ \ '__|  _/ _` |/ __/ _ \                 */
/*				  | |____ / . \   | |   _| |_   _| |_| | | | ||  __/ |  | || (_| | (_|  __/                 */
/*				  |______/_/ \_\  |_|  |_____| |_____|_| |_|\__\___|_|  |_| \__,_|\___\___|                 */
/*				                                                                                            */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef EXTI_MCAL_INTERFACE_H_
#define EXTI_MCAL_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	    INTERFACE MACROS		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
/* External Interrupt Lines */
#define EXTI_LINE_0                       0U
#define EXTI_LINE_1                       1U
#define EXTI_LINE_2                       2U
#define EXTI_LINE_3                       3U
#define EXTI_LINE_4                       4U
#define EXTI_LINE_5                       5U
#define EXTI_LINE_6                       6U
#define EXTI_LINE_7                       7U
#define EXTI_LINE_8                       8U
#define EXTI_LINE_9                       9U
#define EXTI_LINE_10                      10U
#define EXTI_LINE_11                      11U
#define EXTI_LINE_12                      12U
#define EXTI_LINE_12                      12U
#define EXTI_LINE_14                      14U
#define EXTI_LINE_15                      15U

/* External Interrupt Sense Triggers */
#define EXTI_RISING_EDGE 		 		  0U
#define EXTI_FALLING_EDGE 		  		  1U
#define EXTI_ANY_LOGICAL_CHANGE   	      2U

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  FUNCTIONS PROTOTYPES		          	             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: Init					                                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None					                                          */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                                           */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Initialize all EXTI interrupt lines through setting their      */
/*                 interrupt and event masking states in addition to their sense  */
/* 				   triggers based on config file  								  */
/*--------------------------------------------------------------------------------*/
void EXTI_Init(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: EnableInterrupt					                              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_EXTILine					                      */
/*				   Brief: EXTI Interrupt line Id to be unmasked                   */
/*				   Range: (EXTI_LINE_0 --> EXTI_LINE_15)                          */
/*				   Note : This range is for STM32F103C8T6 MCU                     */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                 */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function unmasks (enables) the EXTI interrupt based on    */
/*				   its passed line Id											  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t EXTI_EnableInterrupt(uint8_t Copy_EXTILine);

/*--------------------------------------------------------------------------------*/
/* @Function Name: DisableInterrupt					                              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_EXTILine					                      */
/*				   Brief: EXTI Interrupt line Id to be masked                     */
/*				   Range: (EXTI_LINE_0 --> EXTI_LINE_15)                          */
/*				   Note : This range is for STM32F103C8T6 MCU                     */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                 */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function masks (disables) the EXTI interrupt based on     */
/*				   its passed line Id											  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t EXTI_DisableInterrupt(uint8_t Copy_EXTILine);

/*--------------------------------------------------------------------------------*/
/* @Function Name: EnableEvent					                                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_EXTILine					                      */
/*				   Brief: EXTI Event line Id to be unmasked                       */
/*				   Range: (EXTI_LINE_0 --> EXTI_LINE_15)                          */
/*				   Note : This range is for STM32F103C8T6 MCU                     */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                 */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function unmasks (enables) the EXTI event based on its    */
/*				   passed line Id												  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t EXTI_EnableEvent(uint8_t Copy_EXTILine);

/*--------------------------------------------------------------------------------*/
/* @Function Name: DisableEvent					                                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_EXTILine					                      */
/*				   Brief: EXTI Event line Id to be masked                         */
/*				   Range: (EXTI_LINE_0 --> EXTI_LINE_15)                          */
/*				   Note : This range is for STM32F103C8T6 MCU                     */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                 */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function masks (disables) the EXTI event based on its     */
/*				   passed line Id												  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t EXTI_DisableEvent(uint8_t Copy_EXTILine);

/*--------------------------------------------------------------------------------*/
/* @Function Name: SoftwareInterruptTrigger					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_EXTILine					                      */
/*				   Brief: EXTI Interrupt line Id to be triggered by software      */
/*				   Range: (EXTI_LINE_0 --> EXTI_LINE_15)                          */
/*				   Note : This range is for STM32F103C8T6 MCU                     */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                 */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function triggers EXTI interrupt by software based on     */
/*				   its passed line Id and the interrupt triggers if and only if   */
/*				   this interrupt is unmasked previously				          */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t EXTI_SoftwareInterruptTrigger(uint8_t Copy_EXTILine);

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetInterruptSenseTrigger					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_EXTILine					                      */
/*				   Brief: EXTI Interrupt line Id for which sense interrupt 		  */
/*						  trigger will be set					                  */
/*				   Range: (EXTI_LINE_0 --> EXTI_LINE_15)                          */
/*				   Note : This range is for STM32F103C8T6 MCU                     */
/*				   -------------------------------------------------------------- */
/*                 uint8_t Copy_EXTISenseTrigger								  */
/*				   Brief: EXTI Interrupt sense trigger					 		  */
/*				   Range: (EXTI_RISING_EDGE - EXTI_FALLING_EDGE -				  */
/* 						   EXTI_ANY_LOGICAL_CHANGE)                          	  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                 */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function sets the EXTI interrupt/event sense control      */
/*				   based on its passed line Id                                    */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t EXTI_SetInterruptSenseTrigger(uint8_t Copy_EXTILine , uint8_t Copy_EXTISenseTrigger);

/*--------------------------------------------------------------------------------*/
/* @Function Name: RegisterCallback					                              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_EXTILine					                      */
/*				   Brief: EXTI Interrupt line Id for which callback will be       */
/*                        registered					                          */
/*				   Range: (EXTI_LINE_0 --> EXTI_LINE_15)                          */
/*				   Note : This range is for STM32F103C8T6 MCU                     */
/*				   -------------------------------------------------------------- */
/*				   void (*pEXTI_Callback_Func)(void)							  */
/*				   Brief: Pointer to callback function associated with EXTI       */
/*                 Range: None                                                    */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                                 */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function registers callback function of passed EXTI line  */
/*				   that will be called in application once associated EXTI is     */
/*                 triggered													  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t EXTI_RegisterCallback(uint8_t Copy_EXTILine , void (*pEXTI_Callback_Func)(void));

#endif /* EXTI_MCAL_INTERFACE_H_ */
