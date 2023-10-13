/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Mar 4, 2022               	*/
/*      			SWC          : STK  			            */
/*     			    Description	 : STK Program                  */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						  _____ _______ _  __  _____                                                        */
/*						 / ____|__   __| |/ / |  __ \                                                       */
/*						| (___    | |  | ' /  | |__) | __ ___   __ _ _ __ __ _ _ __ ___                     */
/*						 \___ \   | |  |  <   |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \                    */
/*						 ____) |  | |  | . \  | |   | | | (_) | (_| | | | (_| | | | | | |                   */
/*						|_____/   |_|  |_|\_\ |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|                   */
/*						                                        __/ |                                       */
/*						                     				   |___/                                        */
/*----------------------------------------------------------------------------------------------------- ----*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

#include "STD_TYPES.h"
#include "STD_ERRORS.h"
#include "BIT_MATH.h"

#include "STK_Config.h"
#include "STK_Interface.h"
#include "STK_Private.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            GLOBAL VARIABLES DEFINITIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

uint8_t Global_IntervalMode;						/* Global variable that holds interval mode whether it's single or periodic */
void(*Global_CallbackFunction)(void) = NULL;		/* Global variable that holds pointer to function to be called once STK event is triggered */

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             FUNCTIONS IMPLEMENTATIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: Init          					                              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Initializes systick based on configuration file through        */
/*                 selecting systick clock source in addition to systick          */
/*                 interrupt enabling/disabling									  */
/*--------------------------------------------------------------------------------*/
void STK_Init(void)
{
	/* Disable SysTick Timer */
	CLEAR_BIT(STK->CTRL,CTRL_ENABLE);

	/* Check selected SysTick clock source based on configuration file */
	#if   STK_CLK_SOURCE == AHB_DIV_BY_EIGHT

		/* Select AHB/8 as Clock Source of SysTick Timer */
		CLEAR_BIT(STK->CTRL,CTRL_CLKSOURCE);

	#elif STK_CLK_SOURCE == AHB

		/* Select AHB as Clock Source of SysTick Timer */
		SET_BIT(STK->CTRL,CTRL_CLKSOURCE);

	#else

		#error " Wrong Systick Clock Source Configuration !"

	#endif

	/* Check if SysTick exception request is enabled or not based on configuration file */
	#if   STK_EXCEPTION_REQUEST == ENABLE

		/* Enable SysTick timer exception request */
		SET_BIT(STK->CTRL,CTRL_TICKINT);

	#elif STK_EXCEPTION_REQUEST == DISABLE

		/* Disable SysTick timer exception request */
		CLEAR_BIT(STK->CTRL,CTRL_TICKINT);

	#else

		#error " Wrong SysTick Exception Request Enable Signal Configuration !"

	#endif
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: BusyWait          					                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint32_t Copy_Ticks				                              */
/*                 Brief: Number of STK ticks required to block the processor for */
/*                        a specific time                                         */
/*                 Range: (STK_MIN_VALUE --> STK_MAX_VALUE)                       */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Delays (locks) the processor for N clock cycles based on the   */
/*                 number of ticks passed (Synchronous)                           */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t STK_BusyWait(uint32_t Copy_Ticks)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed ticks number is within valid range (SysTick timer resolution) or not */
	if(Copy_Ticks >= STK_MIN_VALUE && Copy_Ticks <= STK_MAX_VALUE)
	{
		/* Set the Number of ticks (Reload or Start) Value in LOAD Register */
		STK->LOAD = Copy_Ticks;

		/* Start (Enable) SysTick Timer */
		SET_BIT(STK->CTRL,CTRL_ENABLE);

		/* Lock the processor until SysTick timer reaches 0 */
		while (GET_BIT(STK->CTRL,CTRL_COUNTFLAG) != 1);

		/* Stop (Disable) SysTick Timer */
		CLEAR_BIT(STK->CTRL,CTRL_ENABLE);

		/* Clear SysTick Timer */
		STK->LOAD = STK_CLEAR;

		/* Clear Systick Timer Counter Flag through writing any value in VAL register */
		STK->VAL = STK_CLEAR;
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetSingleInterval          					                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint32_t Copy_Ticks                                            */
/* 				   Brief: Number of STK ticks required to achieve one STK 		  */
/*						  interval												  */
/*				   Range: (STK_MIN_VALUE --> STK_MAX_VALUE)						  */
/*				   -------------------------------------------------------------- */
/*                 void (*Copy_pCallbackFunction)(void)                           */
/*				   Brief: Pointer to callback function to be called once STK      */
/*						  event is triggered									  */
/*				   Range: None                                                    */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Sets a count-down timer that generates an interrupt only once  */
/*                 when it reaches 0 after N clock cycles based on the number of  */
/*                 ticks passed (Asynchronous)                                    */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t STK_SetSingleInterval(uint32_t Copy_Ticks , void (*Copy_pCallbackFunction)(void))
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed pointer is not NULL pointer */
	if(Copy_pCallbackFunction != NULL)
	{
		/* Check if passed ticks number is within valid range (SysTick timer resolution) or not */
		if(Copy_Ticks >= STK_MIN_VALUE && Copy_Ticks <= STK_MAX_VALUE)
		{
			/* Assign the passed function as a callback function to be called in ISR when triggered */
			Global_CallbackFunction = Copy_pCallbackFunction;

			/* Set the interval mode */
			Global_IntervalMode = STK_SINGLE_INTERVAL;

			/* Set the Number of ticks (Reload or Start) Value in LOAD Register */
			STK->LOAD = Copy_Ticks;

			/* Enable Systick Interrupt */
			SET_BIT(STK->CTRL,CTRL_TICKINT);

			/* Start (Enable) Systick Timer */
			SET_BIT(STK->CTRL,CTRL_ENABLE);
		}
		else
		{
			/* Function is not behaving as expected */
			Local_Status = RT_NOK;
		}
	}
	else
	{
		/* Passed pointer is NULL pointer */
		Local_Status = NULL_POINTER;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetPeriodicInterval          					              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint32_t Copy_Ticks                                            */
/* 				   Brief: Number of STK ticks required to achieve one STK 		  */
/*						  interval												  */
/*				   Range: (STK_MIN_VALUE --> STK_MAX_VALUE)						  */
/*				   -------------------------------------------------------------- */
/*                 void (*Copy_pCallbackFunction)(void)                           */
/*				   Brief: Pointer to callback function to be called once STK      */
/*						  event is triggered									  */
/*				   Range: None                                                    */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Sets a count-down timer that generates interrupt periodically  */
/*                 when it reaches 0 every N clock cycles based on the number of  */
/*                 ticks passed (Asynchronous)                                    */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t STK_SetPeriodicInterval(uint32_t Copy_Ticks , void (*Copy_pCallbackFunction)(void))
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed pointer is not NULL pointer */
	if(Copy_pCallbackFunction != NULL)
	{
		/* Check if passed ticks number is within valid range (SysTick timer resolution) or not */
		if(Copy_Ticks >= STK_MIN_VALUE && Copy_Ticks <= STK_MAX_VALUE)
		{
			/* Assign the passed function as a callback function to be called in ISR when triggered */
			Global_CallbackFunction = Copy_pCallbackFunction;

			/* Set the interval mode */
			Global_IntervalMode = STK_PERIODIC_INTERVAL;

			/* Set the Number of ticks (Reload or Start) Value in LOAD Register */
			STK->LOAD = Copy_Ticks;

			/* Enable Systick Interrupt */
			SET_BIT(STK->CTRL,CTRL_TICKINT);

			/* Start (Enable) Systick Timer */
			SET_BIT(STK->CTRL,CTRL_ENABLE);
		}
		else
		{
			/* Function is not behaving as expected */
			Local_Status = RT_NOK;
		}
	}
	else
	{
		/* Passed pointer is NULL pointer */
		Local_Status = NULL_POINTER;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: STK_StopTimer          					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Stops the SysTick Timer										  */
/*--------------------------------------------------------------------------------*/
void STK_StopTimer(void)
{
	/* Disable SysTick Interrupt */
	CLEAR_BIT(STK->CTRL,CTRL_TICKINT);

	/* Stop (Disable) SYSTICK Timer */
	CLEAR_BIT(STK->CTRL,CTRL_ENABLE);

	/* Clear SysTick Timer */
	STK->LOAD = STK_CLEAR;

	/* Clear Systick Timer Counter Flag through writing any value in VAL register */
	STK->VAL = STK_CLEAR;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: GetElapsedTime          					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : uint32_t* Copy_pElapesdTime                                    */
/*				   Brief: Pointer to uint32_t variable that will hold STK elapsed */
/*				          time that will be gotten from the function              */
/*				   Range: None                                                    */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Calculates the elapsed time of SysTick timer					  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t STK_GetElapsedTime(uint32_t* Copy_pElapesdTime)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed pointer is NULL or not */
	if(Copy_pElapesdTime != NULL)
	{
		/* Calculate elapsed time through subtraction of VAL register value from LOAD register value */
		*Copy_pElapesdTime = STK->LOAD - STK->VAL;
	}
	else
	{
		/* Passed pointer is NULL pointer */
		Local_Status = NULL_POINTER;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: GetRemainingTime          									  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : uint32_t* Copy_pRemainingTime                                  */
/*				   Brief: Pointer to uint32_t variable that will hold STK 		  */
/*				          remaining time that will be gotten from the function    */
/*				   Range: None                                                    */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Calculates the remaining time of SysTick timer to reach 0	  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t STK_GetRemainingTime(uint32_t* Copy_pRemainingTime)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed pointer is NULL or not */
	if(Copy_pRemainingTime != NULL)
	{
		/* Calculate remaining time through reading the current value of VAL register */
		*Copy_pRemainingTime = STK->VAL;
	}
	else
	{
		/* Passed pointer is NULL pointer */
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
/* @Description	: SysTick Exception Handler                                       */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void SysTick_Handler(void)
{
	/* Check source of SysTick exception handler */
	if(Global_IntervalMode == STK_SINGLE_INTERVAL)
	{
		/* Disable SysTick Interrupt */
		CLEAR_BIT(STK->CTRL,CTRL_TICKINT);

		/* Stop (Disable) SysTick Timer */
		CLEAR_BIT(STK->CTRL,CTRL_ENABLE);

		/* Clear SysTick Timer */
		STK->LOAD = STK_CLEAR;
	}

	/* Clear Systick Timer Counter Flag through writing any value in VAL register */
	STK->VAL = STK_CLEAR;

	/* Check if STK Callback Function is Registered or Not */
	if(Global_CallbackFunction != NULL)
	{
		/* Invoke STK Callback Function */
		Global_CallbackFunction();
	}
}
