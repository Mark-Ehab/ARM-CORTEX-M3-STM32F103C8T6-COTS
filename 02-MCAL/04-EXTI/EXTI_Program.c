/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 10, 2023               	*/
/*      			SWC          : EXTI  			            */
/*     			    Description	 : EXTI Program                 */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*				   ________   _________ _____   _____                                                       */
/*				  |  ____\ \ / /__   __|_   _| |  __ \                                                      */
/*				  | |__   \ V /   | |    | |   | |__) | __ ___   __ _ _ __ __ _ _ __ ___                    */
/*				  |  __|   > <    | |    | |   |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \                   */
/*				  | |____ / . \   | |   _| |_  | |   | | | (_) | (_| | | | (_| | | | | | |                  */
/*				  |______/_/ \_\  |_|  |_____| |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|                  */
/*				                                               	 __/ |                                      */
/*                                                              |___/                                       */
/*----------------------------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "STD_TYPES.h"
#include "STD_ERRORS.h"
#include "BIT_MATH.h"

#include "EXTI_Private.h"
#include "EXTI_Config.h"
#include "EXTI_Interface.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            GLOBAL VARIABLES DEFINITIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
static void(*Global_EXTI_Callback[16])(void) = {NULL}; /* Array of pointers to EXTI callback functions */

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             FUNCTIONS IMPLEMENTATIONS		                     */
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
void EXTI_Init(void)
{
	/* Initialize one or more interrupts on one or more EXTI lines based on configuration parameters in config file */
	EXTI->IMR = CONC_16_BITS(EXTI_INT_LINE_15,EXTI_INT_LINE_14,EXTI_INT_LINE_13,EXTI_INT_LINE_12,EXTI_INT_LINE_11,EXTI_INT_LINE_10,EXTI_INT_LINE_9,EXTI_INT_LINE_8,EXTI_INT_LINE_7,EXTI_INT_LINE_6,EXTI_INT_LINE_5,EXTI_INT_LINE_4,EXTI_INT_LINE_3,EXTI_INT_LINE_2,EXTI_INT_LINE_1,EXTI_INT_LINE_0);

	/* Initialize one or more events on one or more EXTI lines based on configuration parameters in in config file */
	EXTI->EMR = CONC_16_BITS(EXTI_EVENT_LINE_15,EXTI_EVENT_LINE_14,EXTI_EVENT_LINE_13,EXTI_EVENT_LINE_12,EXTI_EVENT_LINE_11,EXTI_EVENT_LINE_10,EXTI_EVENT_LINE_9,EXTI_EVENT_LINE_8,EXTI_EVENT_LINE_7,EXTI_EVENT_LINE_6,EXTI_EVENT_LINE_5,EXTI_EVENT_LINE_4,EXTI_EVENT_LINE_3,EXTI_EVENT_LINE_2,EXTI_EVENT_LINE_1,EXTI_EVENT_LINE_0);

	/* Initialize one or more interrupt/event sense triggers on one or more EXTI lines based on configuration parameters in config file */
	EXTI->RTSR = CONC_16_BITS(EXTI_RISING_EDGE_TRIGGER_LINE_15,EXTI_RISING_EDGE_TRIGGER_LINE_14,EXTI_RISING_EDGE_TRIGGER_LINE_13,EXTI_RISING_EDGE_TRIGGER_LINE_12,EXTI_RISING_EDGE_TRIGGER_LINE_11,EXTI_RISING_EDGE_TRIGGER_LINE_10,EXTI_RISING_EDGE_TRIGGER_LINE_9,EXTI_RISING_EDGE_TRIGGER_LINE_8,EXTI_RISING_EDGE_TRIGGER_LINE_7,EXTI_RISING_EDGE_TRIGGER_LINE_6,EXTI_RISING_EDGE_TRIGGER_LINE_5,EXTI_RISING_EDGE_TRIGGER_LINE_4,EXTI_RISING_EDGE_TRIGGER_LINE_3,EXTI_RISING_EDGE_TRIGGER_LINE_2,EXTI_RISING_EDGE_TRIGGER_LINE_1,EXTI_RISING_EDGE_TRIGGER_LINE_0);
	EXTI->FTSR = CONC_16_BITS(EXTI_FALLING_EDGE_TRIGGER_LINE_15,EXTI_FALLING_EDGE_TRIGGER_LINE_14,EXTI_FALLING_EDGE_TRIGGER_LINE_13,EXTI_FALLING_EDGE_TRIGGER_LINE_12,EXTI_FALLING_EDGE_TRIGGER_LINE_11,EXTI_FALLING_EDGE_TRIGGER_LINE_10,EXTI_FALLING_EDGE_TRIGGER_LINE_9,EXTI_FALLING_EDGE_TRIGGER_LINE_8,EXTI_FALLING_EDGE_TRIGGER_LINE_7,EXTI_FALLING_EDGE_TRIGGER_LINE_6,EXTI_FALLING_EDGE_TRIGGER_LINE_5,EXTI_FALLING_EDGE_TRIGGER_LINE_4,EXTI_FALLING_EDGE_TRIGGER_LINE_3,EXTI_FALLING_EDGE_TRIGGER_LINE_2,EXTI_FALLING_EDGE_TRIGGER_LINE_1,EXTI_FALLING_EDGE_TRIGGER_LINE_0);
}

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
ERROR_STATUS_t EXTI_EnableInterrupt(uint8_t Copy_EXTILine)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed EXTI line id is within valid range or not */
	if(Copy_EXTILine >= EXTI_LINE_0 && Copy_EXTILine <= EXTI_LINE_15)
	{
		/* Enable desired EXTI Interrupt line based on passed Id */
		SET_BIT(EXTI->IMR , Copy_EXTILine);
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

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
ERROR_STATUS_t EXTI_DisableInterrupt(uint8_t Copy_EXTILine)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed EXTI line id is within valid range or not */
	if(Copy_EXTILine >= EXTI_LINE_0 && Copy_EXTILine <= EXTI_LINE_15)
	{
		/* Disable desired EXTI Interrupt line based on passed Id */
		CLEAR_BIT(EXTI->IMR , Copy_EXTILine);
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

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
ERROR_STATUS_t EXTI_EnableEvent(uint8_t Copy_EXTILine)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed EXTI line id is within valid range or not */
	if(Copy_EXTILine >= EXTI_LINE_0 && Copy_EXTILine <= EXTI_LINE_15)
	{
		/* Enable desired EXTI line Event based on passed Id */
		SET_BIT(EXTI->EMR , Copy_EXTILine);
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

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
ERROR_STATUS_t EXTI_DisableEvent(uint8_t Copy_EXTILine)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed EXTI line id is within valid range or not */
	if(Copy_EXTILine >= EXTI_LINE_0 && Copy_EXTILine <= EXTI_LINE_15)
	{
		/* Disable desired EXTI line Event based on passed Id */
		CLEAR_BIT(EXTI->EMR , Copy_EXTILine);
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

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
ERROR_STATUS_t EXTI_SoftwareInterruptTrigger(uint8_t Copy_EXTILine)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed EXTI line id is within valid range or not */
	if(Copy_EXTILine >= EXTI_LINE_0 && Copy_EXTILine <= EXTI_LINE_15)
	{
		/* Enable desired EXTI Software Trigger Interrupt line based on passed Id */
		SET_BIT(EXTI->SWIER , Copy_EXTILine);
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

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
ERROR_STATUS_t EXTI_SetInterruptSenseTrigger(uint8_t Copy_EXTILine , uint8_t Copy_EXTISenseTrigger)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed EXTI line id is within valid range or not */
	if(Copy_EXTILine >= EXTI_LINE_0 && Copy_EXTILine <= EXTI_LINE_15)
	{
		/* Switch on passed EXTI sense trigger */
		switch(Copy_EXTISenseTrigger)
		{
			case EXTI_RISING_EDGE:

				/* Enable rising trigger selection for passed EXTI line Id */
				SET_BIT(EXTI->RTSR , Copy_EXTILine);

				/* Disable falling trigger selection for passed EXTI line Id */
				CLEAR_BIT(EXTI->FTSR , Copy_EXTILine);

				break;

			case EXTI_FALLING_EDGE:

				/* Disable rising trigger selection for passed EXTI line Id */
				CLEAR_BIT(EXTI->RTSR , Copy_EXTILine);

				/* Enable falling trigger selection for passed EXTI line Id */
				SET_BIT(EXTI->FTSR , Copy_EXTILine);

				break;

			case EXTI_ANY_LOGICAL_CHANGE:

				/* Enable rising trigger selection for passed EXTI line Id */
				SET_BIT(EXTI->RTSR , Copy_EXTILine);

				/* Enable falling trigger selection for passed EXTI line Id */
				SET_BIT(EXTI->FTSR , Copy_EXTILine);

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
ERROR_STATUS_t EXTI_RegisterCallback(uint8_t Copy_EXTILine , void (*pEXTI_Callback_Func)(void))
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed pointer is NULL pointer or not */
	if(pEXTI_Callback_Func != NULL)
	{
		/* Switch on EXTI line Id */
		switch(Copy_EXTILine)
		{
		      case EXTI_LINE_0:

		    	  /* Register passed callback function to EXTI line 0 */
		    	  Global_EXTI_Callback[0] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_1:

		    	  /* Register passed callback function to EXTI line 1 */
		    	  Global_EXTI_Callback[1] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_2:

		    	  /* Register passed callback function to EXTI line 2 */
		    	  Global_EXTI_Callback[2] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_3:

		    	  /* Register passed callback function to EXTI line 3 */
		    	  Global_EXTI_Callback[3] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_4:

		    	  /* Register passed callback function to EXTI line 4 */
		    	  Global_EXTI_Callback[4] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_5:

		    	  /* Register passed callback function to EXTI line 5 */
		    	  Global_EXTI_Callback[5] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_6:

		    	  /* Register passed callback function to EXTI line 6 */
		    	  Global_EXTI_Callback[6] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_7:

		    	  /* Register passed callback function to EXTI line 7 */
		    	  Global_EXTI_Callback[7] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_8:

		    	  /* Register passed callback function to EXTI line 8 */
		    	  Global_EXTI_Callback[8] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_9:

		    	  /* Register passed callback function to EXTI line 9 */
		    	  Global_EXTI_Callback[9] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_10:

		    	  /* Register passed callback function to EXTI line 10 */
		    	  Global_EXTI_Callback[10] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_11:

		    	  /* Register passed callback function to EXTI line 11 */
		    	  Global_EXTI_Callback[11] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_12:

		    	  /* Register passed callback function to EXTI line 12 */
		    	  Global_EXTI_Callback[12] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_13:

		    	  /* Register passed callback function to EXTI line 13 */
		    	  Global_EXTI_Callback[13] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_14:

		    	  /* Register passed callback function to EXTI line 14 */
		    	  Global_EXTI_Callback[14] = pEXTI_Callback_Func;
		    	  break;

		      case EXTI_LINE_15:

		    	  /* Register passed callback function to EXTI line 15 */
		    	  Global_EXTI_Callback[15] = pEXTI_Callback_Func;
		    	  break;

		      default:

					/* Function is not behaving as expected */
					Local_Status = RT_NOK;
		}
	}
	else
	{
		Local_Status = NULL_POINTER;
	}

	return Local_Status;
}

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            	  INTERRUPT HANDLERS		                    	 */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: EXTI Line0 interrupt                                            */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void EXTI0_IRQHandler(void)
{
	/* Check If EXTI0 Callback Function is Registered or Not */
	if(Global_EXTI_Callback[0] != NULL)
	{
		/* Invoke EXTI0 Callback Function */
		Global_EXTI_Callback[0]();
	}

	/* Clear Pending Bit */
	SET_BIT(EXTI->PR,EXTI_LINE_0);
}

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: EXTI Line1 interrupt                                            */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void EXTI1_IRQHandler(void)
{
	/* Check If EXTI1 Callback Function is Registered or Not */
	if(Global_EXTI_Callback[1] != NULL)
	{
		/* Invoke EXTI1 Callback Function */
		Global_EXTI_Callback[1]();
	}

	/* Clear Pending Bit */
	SET_BIT(EXTI->PR,EXTI_LINE_1);
}

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: EXTI Line2 interrupt                                            */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void EXTI2_IRQHandler(void)
{
	/* Check If EXTI2 Callback Function is Registered or Not */
	if(Global_EXTI_Callback[2] != NULL)
	{
		/* Invoke EXTI2 Callback Function */
		Global_EXTI_Callback[2]();
	}

	/* Clear Pending Bit */
	SET_BIT(EXTI->PR,EXTI_LINE_2);
}

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: EXTI Line3 interrupt                                            */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void EXTI3_IRQHandler(void)
{
	/* Check If EXTI3 Callback Function is Registered or Not */
	if(Global_EXTI_Callback[3] != NULL)
	{
		/* Invoke EXTI3 Callback Function */
		Global_EXTI_Callback[3]();
	}

	/* Clear Pending Bit */
	SET_BIT(EXTI->PR,EXTI_LINE_3);
}

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: EXTI Line4 interrupt                                            */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void EXTI4_IRQHandler(void)
{
	/* Check If EXTI4 Callback Function is Registered or Not */
	if(Global_EXTI_Callback[4] != NULL)
	{
		/* Invoke EXTI4 Callback Function */
		Global_EXTI_Callback[4]();
	}

	/* Clear Pending Bit */
	SET_BIT(EXTI->PR,EXTI_LINE_4);
}

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description : EXTI Line[9:5] interrupts                                       */
/*				                                                                  */
/* @Note        :  You can change the priorities of Interrupts [9:5] by changing  */
/*                 "If" condtion order.                                           */
/*																				  */
/*--------------------------------------------------------------------------------*/
void EXTI9_5_IRQHandler(void)
{
	/* Check which EXTI line [5:9] was the source of ISR */

	if(GET_BIT(EXTI->PR,EXTI_LINE_5))
	{
		/* Check If EXTI5 Callback Function is Registered or Not */
		if(Global_EXTI_Callback[5] != NULL)
		{
			/* Invoke EXTI5 Callback Function */
			Global_EXTI_Callback[5]();
		}

		/* Clear Pending Bit */
		SET_BIT(EXTI->PR,EXTI_LINE_5);
	}

	if(GET_BIT(EXTI->PR,EXTI_LINE_6))
	{
		/* Check If EXTI6 Callback Function is Registered or Not */
		if(Global_EXTI_Callback[6] != NULL)
		{
			/* Invoke EXTI6 Callback Function */
			Global_EXTI_Callback[6]();
		}

		/* Clear Pending Bit */
		SET_BIT(EXTI->PR,EXTI_LINE_6);
	}

	if(GET_BIT(EXTI->PR,EXTI_LINE_7))
	{
		/* Check If EXTI7 Callback Function is Registered or Not */
		if(Global_EXTI_Callback[7] != NULL)
		{
			/* Invoke EXTI7 Callback Function */
			Global_EXTI_Callback[7]();
		}

		/* Clear Pending Bit */
		SET_BIT(EXTI->PR,EXTI_LINE_7);
	}

	if(GET_BIT(EXTI->PR,EXTI_LINE_8))
	{
		/* Check If EXTI8 Callback Function is Registered or Not */
		if(Global_EXTI_Callback[8] != NULL)
		{
			/* Invoke EXTI8 Callback Function */
			Global_EXTI_Callback[8]();
		}

		/* Clear Pending Bit */
		SET_BIT(EXTI->PR,EXTI_LINE_8);
	}

	if(GET_BIT(EXTI->PR,EXTI_LINE_9))
	{
		/* Check If EXTI9 Callback Function is Registered or Not */
		if(Global_EXTI_Callback[9] != NULL)
		{
			/* Invoke EXTI9 Callback Function */
			Global_EXTI_Callback[9]();
		}

		/* Clear Pending Bit */
		SET_BIT(EXTI->PR,EXTI_LINE_9);
	}
}

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: EXTI Line[15:10] interrupts                                     */
/*						                                                          */
/* @Note        :  You can change the priorities of Interrupts [15:10] by         */
/*                 changing "If" condtion order.                                  */
/*																				  */
/*--------------------------------------------------------------------------------*/
void EXTI15_10_IRQHandler(void)
{
	/* Check which EXTI line [10:15] was the source of ISR */

	if(GET_BIT(EXTI->PR,EXTI_LINE_10))
	{
		/* Check If EXTI10 Callback Function is Registered or Not */
		if(Global_EXTI_Callback[10] != NULL)
		{
			/* Invoke EXTI10 Callback Function */
			Global_EXTI_Callback[10]();
		}

		/* Clear Pending Bit */
		SET_BIT(EXTI->PR,EXTI_LINE_10);
	}

	if(GET_BIT(EXTI->PR,EXTI_LINE_11))
	{
		/* Check If EXTI11 Callback Function is Registered or Not */
		if(Global_EXTI_Callback[11] != NULL)
		{
			/* Invoke EXTI11 Callback Function */
			Global_EXTI_Callback[11]();
		}

		/* Clear Pending Bit */
		SET_BIT(EXTI->PR,EXTI_LINE_11);
	}

	if(GET_BIT(EXTI->PR,EXTI_LINE_12))
	{
		/* Check If EXTI12 Callback Function is Registered or Not */
		if(Global_EXTI_Callback[12] != NULL)
		{
			/* Invoke EXTI12 Callback Function */
			Global_EXTI_Callback[12]();
		}

		/* Clear Pending Bit */
		SET_BIT(EXTI->PR,EXTI_LINE_12);
	}

	if(GET_BIT(EXTI->PR,EXTI_LINE_13))
	{
		/* Check If EXTI13 Callback Function is Registered or Not */
		if(Global_EXTI_Callback[13] != NULL)
		{
			/* Invoke EXTI13 Callback Function */
			Global_EXTI_Callback[13]();
		}

		/* Clear Pending Bit */
		SET_BIT(EXTI->PR,EXTI_LINE_13);
	}

	if(GET_BIT(EXTI->PR,EXTI_LINE_14))
	{
		/* Check If EXTI14 Callback Function is Registered or Not */
		if(Global_EXTI_Callback[14] != NULL)
		{
			/* Invoke EXTI14 Callback Function */
			Global_EXTI_Callback[14]();
		}

		/* Clear Pending Bit */
		SET_BIT(EXTI->PR,EXTI_LINE_14);
	}

	if(GET_BIT(EXTI->PR,EXTI_LINE_15))
	{
		/* Check If EXTI15 Callback Function is Registered or Not */
		if(Global_EXTI_Callback[15] != NULL)
		{
			/* Invoke EXTI15 Callback Function */
			Global_EXTI_Callback[15]();
		}

		/* Clear Pending Bit */
		SET_BIT(EXTI->PR,EXTI_LINE_15);
	}
}
