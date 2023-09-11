/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 7, 2023               	*/
/*      			SWC          : NVIC  			            */
/*     			    Description	 : NVIC Program                 */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*				   _   ___      _______ _____   _____                                                       */
/*				  | \ | \ \    / /_   _/ ____| |  __ \                                                      */
/*				  |  \| |\ \  / /  | || |      | |__) | __ ___   __ _ _ __ __ _ _ __ ___                    */
/*				  | . ` | \ \/ /   | || |      |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \                   */
/*				  | |\  |  \  /   _| || |____  | |   | | | (_) | (_| | | | (_| | | | | | |                  */
/*				  |_| \_|   \/   |_____\_____| |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|                  */
/*						                                         __/ |                                      */
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
#include "NVIC_Private.h"
#include "NVIC_Config.h"
#include "NVIC_Interface.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             FUNCTIONS IMPLEMENTATIONS		                     */
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
ERROR_STATUS_t NVIC_EnableVectorInterrupt(uint8_t Copy_VectorId)
{
        /* Local Variables Definitions */
		ERROR_STATUS_t Local_Status = RT_OK;

		/* Check if passed vector interrupt id is valid or not */
		if(Copy_VectorId >= NVIC_WWDG && Copy_VectorId <= NVIC_DMA2_Channel4_5)
		{
			/* Check in which ISER register this vector interrupt id belongs */
			if(Copy_VectorId < 32U)
			{
				/* Enable Interrupt associated with passed vector id */
				NVIC->NVIC_ISER[0] = (1<<Copy_VectorId);
			}
			else if(Copy_VectorId < 60U)
			{
				/* Enable Interrupt associated with passed vector id */
				Copy_VectorId -= 32U;
				NVIC->NVIC_ISER[1] = (1<<Copy_VectorId);
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
ERROR_STATUS_t NVIC_DisableVectorInterrupt(uint8_t Copy_VectorId)
{
		/* Local Variables Definitions */
		ERROR_STATUS_t Local_Status = RT_OK;

		/* Check if passed vector interrupt id is valid or not */
		if(Copy_VectorId >= NVIC_WWDG && Copy_VectorId <= NVIC_DMA2_Channel4_5)
		{
			/* Check in which ICER register this vector interrupt id belongs */
			if(Copy_VectorId < 32U)
			{
				/* Disable Interrupt associated with passed vector id */
				NVIC->NVIC_ICER[0] = (1<<Copy_VectorId);
			}
			else if(Copy_VectorId < 60U)
			{
				/* Disable Interrupt associated with passed vector id */
				Copy_VectorId -= 32U;
				NVIC->NVIC_ICER[1] = (1<<Copy_VectorId);
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
ERROR_STATUS_t NVIC_SetVectorInterruptPendingFlag(uint8_t Copy_VectorId)
{
		/* Local Variables Definitions */
		ERROR_STATUS_t Local_Status = RT_OK;

		/* Check if passed vector interrupt id is valid or not */
		if(Copy_VectorId >= NVIC_WWDG && Copy_VectorId <= NVIC_DMA2_Channel4_5)
		{
			/* Check in which ISPR register this vector interrupt id belongs */
			if(Copy_VectorId < 32U)
			{
				/* Set pending flag for interrupt associated with passed vector id */
				NVIC->NVIC_ISPR[0] = (1<<Copy_VectorId);
			}
			else if(Copy_VectorId < 60U)
			{
				/* Set pending flag for interrupt associated with passed vector id */
				Copy_VectorId -= 32U;
				NVIC->NVIC_ISPR[1] = (1<<Copy_VectorId);
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
ERROR_STATUS_t NVIC_ClearVectorInterruptPendingFlag(uint8_t Copy_VectorId)
{
		/* Local Variables Definitions */
		ERROR_STATUS_t Local_Status = RT_OK;

		/* Check if passed vector interrupt id is valid or not */
		if(Copy_VectorId >= NVIC_WWDG && Copy_VectorId <= NVIC_DMA2_Channel4_5)
		{
			/* Check in which ICPR register this vector interrupt id belongs */
			if(Copy_VectorId < 32U)
			{
				/* Clear pending flag for interrupt associated with passed vector id */
				NVIC->NVIC_ICPR[0] = (1<<Copy_VectorId);
			}
			else if(Copy_VectorId < 60U)
			{
				/* Clear pending flag for interrupt associated with passed vector id */
				Copy_VectorId -= 32U;
				NVIC->NVIC_ICPR[1] = (1<<Copy_VectorId);
			}
		}
		else
		{
			/* Function is not behaving as expected */
			Local_Status = RT_NOK;
		}

		return Local_Status;
}
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
ERROR_STATUS_t NVIC_GetVectorInterruptActiveFlag(uint8_t Copy_VectorId , uint8_t* Copy_pVectorActiveFlagStatus)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed pointer in NULL pointer or not */
	if(Copy_pVectorActiveFlagStatus == NULL)
	{
		/* Set function status as null pointer */
		Local_Status = NULL_POINTER;
	}
	else
	{
		/* Check if passed vector interrupt id is valid or not */
		if(Copy_VectorId >= NVIC_WWDG && Copy_VectorId <= NVIC_DMA2_Channel4_5)
		{
			/* Check in which IABR register this vector interrupt id belongs */
			if(Copy_VectorId < 32U)
			{
				/* Read active bit of interrupt associated with passed vector id */
				*Copy_pVectorActiveFlagStatus = GET_BIT(NVIC->NVIC_IABR[0],Copy_VectorId);
			}
			else if(Copy_VectorId < 60U)
			{
				/* Read active bit of interrupt associated with passed vector id */
				Copy_VectorId -= 32U;
				*Copy_pVectorActiveFlagStatus = GET_BIT(NVIC->NVIC_IABR[0],Copy_VectorId);
			}
		}
		else
		{
			/* Function is not behaving as expected */
			Local_Status = RT_NOK;
		}
	}

	return Local_Status;
}
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
ERROR_STATUS_t NVIC_SetVectorInterruptPriority(uint8_t Copy_VectorId , uint8_t Copy_VectorGroupPriority , uint8_t Copy_VectorSubPriority)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;
	uint8_t Local_Priority;

	/* Check if passed vector interrupt id is valid or not */
	if((Copy_VectorId >= NVIC_WWDG && Copy_VectorId <= NVIC_DMA2_Channel4_5) &&
	   ((Copy_VectorGroupPriority >= NVIC_GROUP_PRIORITY_0 && Copy_VectorGroupPriority <= NVIC_GROUP_PRIORITY_15) || NVIC_GROUP_PRIORITY_NONE) &&
	   ((Copy_VectorSubPriority   >= NVIC_SUB_PRIORITY_0   && Copy_VectorSubPriority   <= NVIC_SUB_PRIORITY_15)   || NVIC_SUB_PRIORITY_NONE))
	{
		/* Check NVIC Priority Grouping Based on NVIC Configuration File */
		#if	  NVIC_PRIORITY_GROUPING == NVIC_G16S0

			/* Calculate Priority */
			Local_Priority = (uint8_t)(Copy_VectorGroupPriority << 4);

			/* Set priority for passed vector interrupt Id */
			NVIC->NVIC_IPR[Copy_VectorId] = Local_Priority;

		#elif NVIC_PRIORITY_GROUPING == NVIC_G8S2

			/* Calculate Priority */
			Local_Priority = (uint8_t)((Copy_VectorGroupPriority << 1) || Copy_VectorSubPriority);
			Local_Priority = (uint8_t)(Local_Priority << 4);

			/* Set priority for passed vector interrupt Id */
			NVIC->NVIC_IPR[Copy_VectorId] = Local_Priority;

		#elif NVIC_PRIORITY_GROUPING == NVIC_G4S4

			/* Calculate Priority */
			Local_Priority = (uint8_t)((Copy_VectorGroupPriority << 2) || Copy_VectorSubPriority);
			Local_Priority = (uint8_t)(Local_Priority << 4);

			/* Set priority for passed vector interrupt Id */
			NVIC->NVIC_IPR[Copy_VectorId] = Local_Priority;

		#elif NVIC_PRIORITY_GROUPING == NVIC_G2S8

			/* Calculate Priority */
			Local_Priority = (uint8_t)((Copy_VectorGroupPriority << 3) || Copy_VectorSubPriority);
			Local_Priority = (uint8_t)(Local_Priority << 4);

			/* Set priority for passed vector interrupt Id */
			NVIC->NVIC_IPR[Copy_VectorId] = Local_Priority;

		#elif NVIC_PRIORITY_GROUPING == NVIC_G0S16

			/* Calculate Priority */
			Local_Priority = (uint8_t)(Copy_VectorSubPriority << 4);

			/* Set priority for passed vector interrupt Id */
			NVIC->NVIC_IPR[Copy_VectorId] = Local_Priority;

		#else

			#error "Wrong NVIC Priority Grouping Configuration !"

		#endif
	}
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}
