/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Nov 21, 2023               	*/
/*      			SWC          : DMA  			            */
/*     			    Description	 : DMA Program	                */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						 _____  __  __            _____                                                     */
/*						|  __ \|  \/  |   /\     |  __ \                                                    */
/*						| |  | | \  / |  /  \    | |__) | __ ___   __ _ _ __ __ _ _ __ ___                  */
/*						| |  | | |\/| | / /\ \   |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \                 */
/*						| |__| | |  | |/ ____ \  | |   | | | (_) | (_| | | | (_| | | | | | |                */
/*						|_____/|_|  |_/_/    \_\ |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|                */
/*						                                           __/ |                                    */
/*						                        				   |___/                                    */
/*----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "STD_TYPES.h"
#include "STD_ERRORS.h"
#include "BIT_MATH.h"

#include "DMA_Private.h"
#include "DMA_Config.h"
#include "DMA_Interface.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            GLOBAL VARIABLES DEFINITIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
void(*DMA_TransferCompleteNotificationFunc[7])(void) = {NULL};		   /* Array of pointers to DMA seven channels transfer complete callback functions */
void(*DMA_HalfTransferNotificationFunc[7])(void) = {NULL};               /* Array of pointers to DMA seven channels half transfer callback functions */
void(*DMA_TransferErrorNotificationFunc[7])(void) = {NULL};              /* Array of pointers to DMA seven channels transfer error callback functions */

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	FUNCTIONS IMPLEMENTATIONS		          	         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: ChannelInit          					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_ChannelId                                         */
/* 			       Brief: Desired DMA channel id                                  */
/* 			       Range: (DMA_CH1 --> DMA_CH7)                                   */
/* 			       -------------------------------------------------------------- */
/* 				   DMA_ChannelConfig_t* Copy_pChannelConfig			              */
/* 			       Brief: Pointer to DMA channel configurations                   */
/* 			       Range: None                                                    */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Initializes any DMA channel based on passed channel id         */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t DMA_ChannelInit(uint8_t Copy_ChannelId ,DMA_ChannelConfig_t* Copy_pChannelConfig)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_ErrorStatus = RT_OK;

	/* Check if passed pointer is NULL pointer or not */
	if(Copy_pChannelConfig != NULL)
	{
		/* Check if passed channel id is within valid range or not */
		if(Copy_ChannelId >= DMA_CH1 && Copy_ChannelId <= DMA_CH7)
		{
			/* Make sure that selected DMA channel is disabled before configuration through clearing EN bit in CCRx register */
			CLEAR_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_EN);

			/*********************************Memory To Memory Mode Configuration*********************************/
			/* Check if memory to memory mode is enabled or not based on passed configuration */
			if(Copy_pChannelConfig->memToMemModeEnable == DMA_MEM_TO_MEM_MODE_ENABLE)
			{
				/* Set MEM2MEM bit in CCRx register */
				SET_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_MEM2MEM);
			}
			else if(Copy_pChannelConfig->memToMemModeEnable == DMA_MEM_TO_MEM_MODE_DISABLE)
			{
				/* Clear MEM2MEM bit in CCRx register */
				CLEAR_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_MEM2MEM);
			}
			else
			{
				/* Out of range error */
				Local_ErrorStatus = OUT_OF_RANGE;
			}

			/*********************************Channel Priority Level Configuration*********************************/
			/* Clear channel priority level bits of CCRx register */
			DMA->Channel[Copy_ChannelId].CCR &= DMA_CHANNEL_PRIORITY_MASK;

			/* Check channel priority level based on passed configuration */
			switch(Copy_pChannelConfig->channelPriorityLevel)
			{
				case DMA_CHANNEL_PRIORITY_LOW:

					/* Set channel priority level bits of CCRx register to 00 */
					DMA->Channel[Copy_ChannelId].CCR |= DMA_CHANNEL_PRIORITY_LOW_VAL;

					break;
				case DMA_CHANNEL_PRIORITY_MEDIUM:

					/* Set channel priority level bits of CCRx register to 01 */
					DMA->Channel[Copy_ChannelId].CCR |= DMA_CHANNEL_PRIORITY_MEDIUM_VAL;

					break;
				case DMA_CHANNEL_PRIORITY_HIGH:

					/* Set channel priority level bits of CCRx register to 10 */
					DMA->Channel[Copy_ChannelId].CCR |= DMA_CHANNEL_PRIORITY_HIGH_VAL;

					break;
				case DMA_CHANNEL_PRIORITY_VERY_HIGH:

					/* Set channel priority level bits of CCRx register to 11 */
					DMA->Channel[Copy_ChannelId].CCR |= DMA_CHANNEL_PRIORITY_VERY_HIGH_VAL;

					break;
				default:

					/* Out of range error */
					Local_ErrorStatus = OUT_OF_RANGE;
			}

			/*********************************Memory Size Configuration*********************************/
			/* Clear memory size bits of CCRx register */
			DMA->Channel[Copy_ChannelId].CCR &= DMA_MEMORY_SIZE_MASK;

			/* Check memory size based on passed configuration */
			switch(Copy_pChannelConfig->memorySize)
			{
				case DMA_MEMORY_SIZE_8_BITS:

					/* Set memory size bits of CCRx register to 00 */
					DMA->Channel[Copy_ChannelId].CCR |= DMA_MEMORY_SIZE_8_BITS_VAL;

					break;
				case DMA_MEMORY_SIZE_16_BITS:

					/* Set memory size bits of CCRx register to 01 */
					DMA->Channel[Copy_ChannelId].CCR |= DMA_MEMORY_SIZE_16_BITS_VAL;

					break;
				case DMA_MEMORY_SIZE_32_BITS:

					/* Set memory size bits of CCRx register to 10 */
					DMA->Channel[Copy_ChannelId].CCR |= DMA_MEMORY_SIZE_32_BITS_VAL;

					break;
				default:

					/* Out of range error */
					Local_ErrorStatus = OUT_OF_RANGE;
			}


			/*********************************Peripheral Size Configuration*********************************/
			/* Clear peripheral size bits of CCRx register */
			DMA->Channel[Copy_ChannelId].CCR &= DMA_PERIPHERAL_SIZE_MASK;

			/* Check peripheral size based on passed configuration */
			switch(Copy_pChannelConfig->peripheralSize)
			{
				case DMA_PERIPHERAL_SIZE_8_BITS:

					/* Set peripheral size bits of CCRx register to 00 */
					DMA->Channel[Copy_ChannelId].CCR |= DMA_PERIPHERAL_SIZE_8_BITS_VAL;

					break;
				case DMA_PERIPHERAL_SIZE_16_BITS:

					/* Set peripheral size bits of CCRx register to 01 */
					DMA->Channel[Copy_ChannelId].CCR |= DMA_PERIPHERAL_SIZE_16_BITS_VAL;

					break;
				case DMA_PERIPHERAL_SIZE_32_BITS:

					/* Set peripheral size bits of CCRx register to 10 */
					DMA->Channel[Copy_ChannelId].CCR |= DMA_PERIPHERAL_SIZE_32_BITS_VAL;

					break;
				default:

					/* Out of range error */
					Local_ErrorStatus = OUT_OF_RANGE;
			}

			/*********************************Memory Increment Mode Configuration*********************************/
			/* Check if memory increment mode is enabled or not based on passed configuration */
			if(Copy_pChannelConfig->memoryIncrementModeEnable == DMA_MEMORY_INCREMENT_MODE_ENABLE)
			{
				/* Set MINC bit in CCRx register */
				SET_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_MINC);
			}
			else if(Copy_pChannelConfig->memoryIncrementModeEnable == DMA_MEMORY_INCREMENT_MODE_DISABLE)
			{
				/* Clear MINC bit in CCRx register */
				CLEAR_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_MINC);
			}
			else
			{
				/* Out of range error */
				Local_ErrorStatus = OUT_OF_RANGE;
			}

			/*********************************Peripheral Increment Mode Configuration*********************************/
			/* Check if peripheral increment mode is enabled or not based on passed configuration */
			if(Copy_pChannelConfig->peripheralIncrementModeEnable == DMA_PERIPHERAL_INCREMENT_MODE_ENABLE)
			{
				/* Set PINC bit in CCRx register */
				SET_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_PINC);
			}
			else if(Copy_pChannelConfig->peripheralIncrementModeEnable == DMA_PERIPHERAL_INCREMENT_MODE_DISABLE)
			{
				/* Clear PINC bit in CCRx register */
				CLEAR_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_PINC);
			}
			else
			{
				/* Out of range error */
				Local_ErrorStatus = OUT_OF_RANGE;
			}

			/*********************************Circular Mode Configuration*********************************/
			/* Check if circular mode is enabled or not based on passed configuration */
			if(Copy_pChannelConfig->circularModeEnable == DMA_CIRCULAR_MODE_ENABLE)
			{
				/* Set CIRC bit in CCRx register */
				SET_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_CIRC);
			}
			else if(Copy_pChannelConfig->circularModeEnable == DMA_CIRCULAR_MODE_DISABLE)
			{
				/* Clear CIRC bit in CCRx register */
				CLEAR_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_CIRC);
			}
			else
			{
				/* Out of range error */
				Local_ErrorStatus = OUT_OF_RANGE;
			}

			/*********************************Data Transfer Direction Configuration*********************************/
			/* Check data transfer direction based on passed configuration */
			if(Copy_pChannelConfig->dataTransferDirection == DMA_READ_FROM_MEMORY)
			{
				/* Set DIR bit in CCRx register */
				SET_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_DIR);
			}
			else if(Copy_pChannelConfig->dataTransferDirection == DMA_READ_FROM_PERIPHERAL)
			{
				/* Clear DIR bit in CCRx register */
				CLEAR_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_DIR);
			}
			else
			{
				/* Out of range error */
				Local_ErrorStatus = OUT_OF_RANGE;
			}

			/*********************************Transfer Error Interrupt Enable Configuration*********************************/
			/* Check if transfer error interrupt is enabled or not based on passed configuration */
			if(Copy_pChannelConfig->transferErrorInterruptEnable == DMA_TRANSFER_ERROR_INTERRUPT_ENABLE)
			{
				/* Set TEIE bit in CCRx register */
				SET_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_TEIE);
			}
			else if(Copy_pChannelConfig->transferErrorInterruptEnable == DMA_TRANSFER_ERROR_INTERRUPT_DISABLE)
			{
				/* Clear TEIE bit in CCRx register */
				CLEAR_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_TEIE);
			}
			else
			{
				/* Out of range error */
				Local_ErrorStatus = OUT_OF_RANGE;
			}


			/*********************************Half Transfer Interrupt Enable Configuration*********************************/
			/* Check if half transfer interrupt is enabled or not based on passed configuration */
			if(Copy_pChannelConfig->halfTransferInterruptEnable == DMA_HALF_TRANSFER_INTERRUPT_ENABLE)
			{
				/* Set HTIE bit in CCRx register */
				SET_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_HTIE);
			}
			else if(Copy_pChannelConfig->halfTransferInterruptEnable == DMA_HALF_TRANSFER_INTERRUPT_DISABLE)
			{
				/* Clear HTIE bit in CCRx register */
				CLEAR_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_HTIE);
			}
			else
			{
				/* Out of range error */
				Local_ErrorStatus = OUT_OF_RANGE;
			}

			/*********************************Transfer Complete Interrupt Enable Configuration*********************************/
			/* Check if transfer complete interrupt is enabled or not based on passed configuration */
			if(Copy_pChannelConfig->transferCompleteInterruptEnable == DMA_TRANSFER_COMPLETE_INTERRUPT_ENABLE)
			{
				/* Set TCIE bit in CCRx register */
				SET_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_TCIE);
			}
			else if(Copy_pChannelConfig->transferCompleteInterruptEnable == DMA_TRANSFER_COMPLETE_INTERRUPT_DISABLE)
			{
				/* Clear TCIE bit in CCRx register */
				CLEAR_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_TCIE);
			}
			else
			{
				/* Out of range error */
				Local_ErrorStatus = OUT_OF_RANGE;
			}

			/*********************************Block Length Configuration*********************************/
			/* Check if block length based on passed configuration is within valid range or not */
			if(Copy_pChannelConfig->channelBlockLength >= DMA_MIN_BLOCK_LENGTH_VAL && Copy_pChannelConfig->channelBlockLength <= DMA_MAX_BLOCK_LENGTH_VAL)
			{
				/* Set number of data bytes in the block to be transfered through selected channel in CNDTRx register */
				DMA->Channel[Copy_ChannelId].CNDTR = Copy_pChannelConfig->channelBlockLength;
			}
			else
			{
				/* Out of range error */
				Local_ErrorStatus = OUT_OF_RANGE;
			}
		}
		else
		{
			/* Out of range error */
			Local_ErrorStatus = OUT_OF_RANGE;
		}
	}
	else
	{
		/* Passed pointer is NULL pointer */
		Local_ErrorStatus = NULL_POINTER;
	}

	return Local_ErrorStatus;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: ChannelStart          			                              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_ChannelId                                         */
/* 			       Brief: Desired DMA channel id                                  */
/*			       Range: (DMA_CH1 --> DMA_CH7)                                   */
/*			       -------------------------------------------------------------- */
/*	               uint32_t* Copy_pSourceAddress                                  */
/*			       Brief: Pointer to DMA channel source                           */
/*			       Range: None                                                    */
/*			       -------------------------------------------------------------- */
/*	               uint32_t* Copy_pDestinationAddress				              */
/* 			       Brief: Pointer to DMA channel destination                      */
/* 			       Range: None                                                    */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function forces selected DMA channel to start transaction */
/* 				   through specifying channel source address and destination      */
/* 				   address                                                        */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t DMA_ChannelStart(uint8_t Copy_ChannelId , uint32_t* Copy_pSourceAddress , uint32_t* Copy_pDestinationAddress)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_ErrorStatus = RT_OK;

	/* Check if passed pointers are NULL pointers or not */
	if(Copy_pSourceAddress != NULL && Copy_pDestinationAddress != NULL)
	{
		/* Check if passed channel id is valid and within range or not */
		if(Copy_ChannelId >= DMA_CH1 && Copy_ChannelId <= DMA_CH7)
		{
			/* Make sure that selected DMA channel is disabled through clearing EN bit in CCRx register */
			CLEAR_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_EN);

			/* Make sure that both source and destination address registers are cleared before setting passed ones */
			DMA->Channel[Copy_ChannelId].CPAR = 0;
			DMA->Channel[Copy_ChannelId].CMAR = 0;

			/* Set passed source and destination addresses */
			DMA->Channel[Copy_ChannelId].CPAR = Copy_pSourceAddress;
			DMA->Channel[Copy_ChannelId].CMAR = Copy_pDestinationAddress;

			/* Enable selected DMA channel at the end to start data transaction on the channel through setting EN bit in CCRx register */
			SET_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_EN);
		}
		else
		{
			/* Out of range error */
			Local_ErrorStatus = OUT_OF_RANGE;
		}
	}
	else
	{
		/* One or both of passed pointers is a NULL pointer */
		Local_ErrorStatus = NULL_POINTER;
	}

	return Local_ErrorStatus;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetChannelState          		                              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_ChannelId                                         */
/* 			       Brief: Desired DMA channel id                                  */
/*			       Range: (DMA_CH1 --> DMA_CH7)                                   */
/*			       -------------------------------------------------------------- */
/*	               uint8_t Copy_ChannelState	                                  */
/*			       Brief: The state of DMA channel whether enabled on disabled    */
/*			       Range: (DMA_CHANNEL_DISABLE - DMA_CHANNEL_ENABLE)              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function either enables or disables DMA channel based on  */
/*                 passed state                                                   */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t DMA_SetChannelState(uint8_t Copy_ChannelId, uint8_t Copy_ChannelState)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_ErrorStatus = RT_OK;

	/* Check if passed channel id and channel state values are valid and within their valid ranges or not */
	if((Copy_ChannelId >= DMA_CH1 && Copy_ChannelId <= DMA_CH7) &&
	   (Copy_ChannelState == DMA_CHANNEL_ENABLE || Copy_ChannelState == DMA_CHANNEL_DISABLE))
	{
		/* Check passed channel state */
		if(Copy_ChannelState == DMA_CHANNEL_ENABLE)
		{
			/* Set EN bit in CCRx register */
			SET_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_EN);
		}
		else
		{
			/* Clear EN bit in CCRx register */
			CLEAR_BIT(DMA->Channel[Copy_ChannelId].CCR,CCR_EN);
		}
	}
	else
	{
		/* Out of range error */
		Local_ErrorStatus = OUT_OF_RANGE;
	}

	return Local_ErrorStatus;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: RegisterTransferCompleteCallback        		                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_ChannelId                                         */
/* 			       Brief: Desired DMA channel id                                  */
/*			       Range: (DMA_CH1 --> DMA_CH7)                                   */
/*			       -------------------------------------------------------------- */
/*	               void(*Copy_NotificationFunc)(void)	                          */
/*			       Brief: Pointer to DMA transfer complete callback function      */
/*			       Range: None										              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function registers DMA transfer complete callback         */
/*                 function of selected DMA channel that will be called once      */
/*                 DMA transfer is completed within channel's DMA handler         */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t DMA_RegisterTransferCompleteCallback(uint8_t Copy_ChannelId , void(*Copy_NotificationFunc)(void))
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_ErrorStatus = RT_OK;

	/* Check if passed pointer is a NULL pointer or not */
	if(Copy_NotificationFunc != NULL)
	{
		/* Check if passed channel id is within valid range or not */
		if(Copy_ChannelId >= DMA_CH1 && Copy_ChannelId <= DMA_CH7)
		{
			/* Register passed pointer to function as a DMA transfer complete callback function for selected channel */
			DMA_TransferCompleteNotificationFunc[Copy_ChannelId] = Copy_NotificationFunc;
		}
		else
		{
			/* Out of range error */
			Local_ErrorStatus = OUT_OF_RANGE;
		}
	}
	else
	{
		/* Passed pointer is a NULL pointer */
		Local_ErrorStatus = NULL_POINTER;
	}

	return Local_ErrorStatus;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: RegisterHalfTransferCallback         		                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_ChannelId                                         */
/* 			       Brief: Desired DMA channel id                                  */
/*			       Range: (DMA_CH1 --> DMA_CH7)                                   */
/*			       -------------------------------------------------------------- */
/*	               void(*Copy_NotificationFunc)(void)	                          */
/*			       Brief: Pointer to DMA half transfer callback function          */
/*			       Range: None										              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function registers DMA half transfer callback function of */
/*                 selected DMA channel that will be called once DMA half transfer*/
/*                 is completed within channel's DMA handler                      */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t DMA_RegisterHalfTransferCallback(uint8_t Copy_ChannelId , void(*Copy_NotificationFunc)(void))
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_ErrorStatus = RT_OK;

	/* Check if passed pointer is a NULL pointer or not */
	if(Copy_NotificationFunc != NULL)
	{
		/* Check if passed channel id is within valid range or not */
		if(Copy_ChannelId >= DMA_CH1 && Copy_ChannelId <= DMA_CH7)
		{
			/* Register passed pointer to function as a DMA half transfer callback function for selected channel */
			DMA_HalfTransferNotificationFunc[Copy_ChannelId] = Copy_NotificationFunc;
		}
		else
		{
			/* Out of range error */
			Local_ErrorStatus = OUT_OF_RANGE;
		}
	}
	else
	{
		/* Passed pointer is a NULL pointer */
		Local_ErrorStatus = NULL_POINTER;
	}

	return Local_ErrorStatus;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: RegisterTransferErrorCallback        		                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_ChannelId                                         */
/* 			       Brief: Desired DMA channel id                                  */
/*			       Range: (DMA_CH1 --> DMA_CH7)                                   */
/*			       -------------------------------------------------------------- */
/*	               void(*Copy_NotificationFunc)(void)	                          */
/*			       Brief: Pointer to DMA transfer error callback function         */
/*			       Range: None										              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function registers DMA transfer error callback function   */
/*                 of selected DMA channel that will be called once DMA transfer  */
/*                 error is occurred within channel's DMA handler                 */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t DMA_RegisterTransferErrorCallback(uint8_t Copy_ChannelId , void(*Copy_NotificationFunc)(void))
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_ErrorStatus = RT_OK;

	/* Check if passed pointer is a NULL pointer or not */
	if(Copy_NotificationFunc != NULL)
	{
		/* Check if passed channel id is within valid range or not */
		if(Copy_ChannelId >= DMA_CH1 && Copy_ChannelId <= DMA_CH7)
		{
			/* Register passed pointer to function as a DMA transfer error callback function for selected channel */
			DMA_TransferErrorNotificationFunc[Copy_ChannelId] = Copy_NotificationFunc;
		}
		else
		{
			/* Out of range error */
			Local_ErrorStatus = OUT_OF_RANGE;
		}
	}
	else
	{
		/* Passed pointer is a NULL pointer */
		Local_ErrorStatus = NULL_POINTER;
	}

	return Local_ErrorStatus;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: GetInterruptFlagStatus        				                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_ChannelId                                         */
/* 			       Brief: Desired DMA channel id                                  */
/*			       Range: (DMA_CH1 --> DMA_CH7)                                   */
/*			       -------------------------------------------------------------- */
/*	               uint8_t Copy_InterruptFlagId			                          */
/*			       Brief: DMA interrupt flag Id							          */
/*			       Range: - DMA_GLOBAL_INTERRUPT_FLAG                             */
/*                        - DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG                  */
/*                        - DMA_HALF_TRANSFER_INTERRUPT_FLAG	                  */
/*                        - DMA_TRANSFER_ERROR_INTERRUPT_FLAG	    			  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : uint8_t* Copy_pInterruptFlagStatus                             */
/*                 Brief: Pointer to uint8_t variable that will hold interrupt    */
/*                        flag status                                             */
/*                 Range: None                                                    */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function gets the status of DMA interrupt flags whether   */
/*                 they are raised or not                                         */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t DMA_GetInterruptFlagStatus(uint8_t Copy_ChannelId , uint8_t Copy_InterruptFlagId , uint8_t* Copy_pInterruptFlagStatus)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_ErrorStatus = RT_OK;

	/* Check if passed pointer is NULL pointer or not */
	if(Copy_pInterruptFlagStatus != NULL)
	{
		/* Check if passed channel id is within valid range or not */
		if(Copy_ChannelId >= DMA_CH1 && Copy_ChannelId <= DMA_CH7)
		{
			/* Check passed interrupt flag id */
			switch(Copy_InterruptFlagId)
			{
				case DMA_GLOBAL_INTERRUPT_FLAG:

					/* Get DMA global interrupt status */
					*Copy_pInterruptFlagStatus = GET_BIT(DMA->ISR,((Copy_ChannelId * 4) + Copy_InterruptFlagId));
					break;

				case DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG:

					/* Get DMA transfer complete interrupt status */
					*Copy_pInterruptFlagStatus = GET_BIT(DMA->ISR,((Copy_ChannelId * 4) + Copy_InterruptFlagId));
					break;

				case DMA_HALF_TRANSFER_INTERRUPT_FLAG:

					/* Get DMA half transfer interrupt status */
					*Copy_pInterruptFlagStatus = GET_BIT(DMA->ISR,((Copy_ChannelId * 4) + Copy_InterruptFlagId));
					break;

				case DMA_TRANSFER_ERROR_INTERRUPT_FLAG:

					/* Get DMA transfer error interrupt status */
					*Copy_pInterruptFlagStatus = GET_BIT(DMA->ISR,((Copy_ChannelId * 4) + Copy_InterruptFlagId));
					break;

				default:

					/* Out of range error */
					Local_ErrorStatus = OUT_OF_RANGE;
			}
		}
		else
		{
			/* Out of range error */
			Local_ErrorStatus = OUT_OF_RANGE;
		}
	}
	else
	{
		/* Passed pointer is a NULL pointer */
		Local_ErrorStatus = NULL_POINTER;
	}

	return Local_ErrorStatus;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: ClearInterruptFlag           				                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_ChannelId                                         */
/* 			       Brief: Desired DMA channel id                                  */
/*			       Range: (DMA_CH1 --> DMA_CH7)                                   */
/*			       -------------------------------------------------------------- */
/*	               uint8_t Copy_InterruptFlagId			                          */
/*			       Brief: DMA interrupt flag Id							          */
/*			       Range: - DMA_GLOBAL_INTERRUPT_FLAG                             */
/*                        - DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG                  */
/*                        - DMA_HALF_TRANSFER_INTERRUPT_FLAG	                  */
/*                        - DMA_TRANSFER_ERROR_INTERRUPT_FLAG	    			  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function clears DMA interrupt flags in case they are      */
/* 				   raised                                                         */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t DMA_ClearInterruptFlag(uint8_t Copy_ChannelId , uint8_t Copy_InterruptFlagId)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_ErrorStatus = RT_OK;

	/* Check if passed channel id is within valid range or not */
	if(Copy_ChannelId >= DMA_CH1 && Copy_ChannelId <= DMA_CH7)
	{
		/* Check passed interrupt flag id */
		switch(Copy_InterruptFlagId)
		{
			case DMA_GLOBAL_INTERRUPT_FLAG:

				/* Clear DMA global interrupt flag by setting its corresponding interrupt flag bit to 1 in IFCR register in selected channel */
				SET_BIT(DMA->IFCR,((Copy_ChannelId * 4) + Copy_InterruptFlagId));
				break;

			case DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG:

				/* Clear DMA transfer complete interrupt flag by setting its corresponding interrupt flag bit to 1 in IFCR register in selected channel */
				SET_BIT(DMA->IFCR,((Copy_ChannelId * 4) + Copy_InterruptFlagId));
				break;

			case DMA_HALF_TRANSFER_INTERRUPT_FLAG:

				/* Clear DMA half transfer interrupt flag by setting its corresponding interrupt flag bit to 1 in IFCR register in selected channel */
				SET_BIT(DMA->IFCR,((Copy_ChannelId * 4) + Copy_InterruptFlagId));
				break;

			case DMA_TRANSFER_ERROR_INTERRUPT_FLAG:

				/* Clear DMA transfer error interrupt flag by setting its corresponding interrupt flag bit to 1 in IFCR register in selected channel */
				SET_BIT(DMA->IFCR,((Copy_ChannelId * 4) + Copy_InterruptFlagId));
				break;

			default:

				/* Out of range error */
				Local_ErrorStatus = OUT_OF_RANGE;
		}
	}
	else
	{
		/* Out of range error */
		Local_ErrorStatus = OUT_OF_RANGE;
	}

	return Local_ErrorStatus;
}

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            	  INTERRUPT HANDLERS		                    	 */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: DMA1 channel1 interrupt                                         */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void DMA1_Channel1_IRQHandler(void)
{
	/* Local variables definitions */
	uint8_t Local_InterruptSource = 0;

	/**************************************Check source of interrupt**************************************/

	/* Check if interrupt source is DMA Transfer Complete */
    DMA_GetInterruptFlagStatus(DMA_CH1, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Complete callback function is registered or not */
		if(DMA_TransferCompleteNotificationFunc[0] != NULL)
		{
			/* Invoke DMA Transfer Complete Callback Function */
			DMA_TransferCompleteNotificationFunc[0]();
		}

		/* Clear DMA Transfer Complete flag */
		DMA_ClearInterruptFlag(DMA_CH1, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Half Transfer */
	DMA_GetInterruptFlagStatus(DMA_CH1, DMA_HALF_TRANSFER_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Half Transfer callback function is registered or not */
		if(DMA_HalfTransferNotificationFunc[0] != NULL)
		{
			/* Invoke DMA Half Transfer Callback Function */
			DMA_HalfTransferNotificationFunc[0]();
		}

		/* Clear DMA Half Transfer flag */
		DMA_ClearInterruptFlag(DMA_CH1, DMA_HALF_TRANSFER_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Transfer Error */
	DMA_GetInterruptFlagStatus(DMA_CH1, DMA_TRANSFER_ERROR_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Error callback function is registered or not */
		if(DMA_TransferErrorNotificationFunc[0] != NULL)
		{
			/* Invoke DMA Transfer Error Callback Function */
			DMA_TransferErrorNotificationFunc[0]();
		}

		/* Clear DMA Transfer Error flag */
		DMA_ClearInterruptFlag(DMA_CH1, DMA_TRANSFER_ERROR_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Clear DMA Global Interrupt flag */
	DMA_ClearInterruptFlag(DMA_CH1, DMA_GLOBAL_INTERRUPT_FLAG);
}

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: DMA1 channel2 interrupt                                         */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void DMA1_Channel2_IRQHandler(void)
{
	/* Local variables definitions */
	uint8_t Local_InterruptSource = 0;

	/**************************************Check source of interrupt**************************************/

	/* Check if interrupt source is DMA Transfer Complete */
    DMA_GetInterruptFlagStatus(DMA_CH2, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Complete callback function is registered or not */
		if(DMA_TransferCompleteNotificationFunc[1] != NULL)
		{
			/* Invoke DMA Transfer Complete Callback Function */
			DMA_TransferCompleteNotificationFunc[1]();
		}

		/* Clear DMA Transfer Complete flag */
		DMA_ClearInterruptFlag(DMA_CH2, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Half Transfer */
	DMA_GetInterruptFlagStatus(DMA_CH2, DMA_HALF_TRANSFER_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Half Transfer callback function is registered or not */
		if(DMA_HalfTransferNotificationFunc[1] != NULL)
		{
			/* Invoke DMA Half Transfer Callback Function */
			DMA_HalfTransferNotificationFunc[1]();
		}

		/* Clear DMA Half Transfer flag */
		DMA_ClearInterruptFlag(DMA_CH2, DMA_HALF_TRANSFER_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Transfer Error */
	DMA_GetInterruptFlagStatus(DMA_CH2, DMA_TRANSFER_ERROR_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Error callback function is registered or not */
		if(DMA_TransferErrorNotificationFunc[1] != NULL)
		{
			/* Invoke DMA Transfer Error Callback Function */
			DMA_TransferErrorNotificationFunc[1]();
		}

		/* Clear DMA Transfer Error flag */
		DMA_ClearInterruptFlag(DMA_CH2, DMA_TRANSFER_ERROR_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Clear DMA Global Interrupt flag */
	DMA_ClearInterruptFlag(DMA_CH2, DMA_GLOBAL_INTERRUPT_FLAG);
}

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: DMA1 channel3 interrupt                                         */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void DMA1_Channel3_IRQHandler(void)
{
	/* Local variables definitions */
	uint8_t Local_InterruptSource = 0;

	/**************************************Check source of interrupt**************************************/

	/* Check if interrupt source is DMA Transfer Complete */
    DMA_GetInterruptFlagStatus(DMA_CH3, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Complete callback function is registered or not */
		if(DMA_TransferCompleteNotificationFunc[2] != NULL)
		{
			/* Invoke DMA Transfer Complete Callback Function */
			DMA_TransferCompleteNotificationFunc[2]();
		}

		/* Clear DMA Transfer Complete flag */
		DMA_ClearInterruptFlag(DMA_CH3, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Half Transfer */
	DMA_GetInterruptFlagStatus(DMA_CH3, DMA_HALF_TRANSFER_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Half Transfer callback function is registered or not */
		if(DMA_HalfTransferNotificationFunc[2] != NULL)
		{
			/* Invoke DMA Half Transfer Callback Function */
			DMA_HalfTransferNotificationFunc[2]();
		}

		/* Clear DMA Half Transfer flag */
		DMA_ClearInterruptFlag(DMA_CH3, DMA_HALF_TRANSFER_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Transfer Error */
	DMA_GetInterruptFlagStatus(DMA_CH3, DMA_TRANSFER_ERROR_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Error callback function is registered or not */
		if(DMA_TransferErrorNotificationFunc[2] != NULL)
		{
			/* Invoke DMA Transfer Error Callback Function */
			DMA_TransferErrorNotificationFunc[2]();
		}

		/* Clear DMA Transfer Error flag */
		DMA_ClearInterruptFlag(DMA_CH3, DMA_TRANSFER_ERROR_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Clear DMA Global Interrupt flag */
	DMA_ClearInterruptFlag(DMA_CH3, DMA_GLOBAL_INTERRUPT_FLAG);
}

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: DMA1 channel4 interrupt                                         */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void DMA1_Channel4_IRQHandler(void)
{
	/* Local variables definitions */
	uint8_t Local_InterruptSource = 0;

	/**************************************Check source of interrupt**************************************/

	/* Check if interrupt source is DMA Transfer Complete */
    DMA_GetInterruptFlagStatus(DMA_CH4, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Complete callback function is registered or not */
		if(DMA_TransferCompleteNotificationFunc[3] != NULL)
		{
			/* Invoke DMA Transfer Complete Callback Function */
			DMA_TransferCompleteNotificationFunc[3]();
		}

		/* Clear DMA Transfer Complete flag */
		DMA_ClearInterruptFlag(DMA_CH4, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Half Transfer */
	DMA_GetInterruptFlagStatus(DMA_CH4, DMA_HALF_TRANSFER_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Half Transfer callback function is registered or not */
		if(DMA_HalfTransferNotificationFunc[3] != NULL)
		{
			/* Invoke DMA Half Transfer Callback Function */
			DMA_HalfTransferNotificationFunc[3]();
		}

		/* Clear DMA Half Transfer flag */
		DMA_ClearInterruptFlag(DMA_CH4, DMA_HALF_TRANSFER_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Transfer Error */
	DMA_GetInterruptFlagStatus(DMA_CH4, DMA_TRANSFER_ERROR_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Error callback function is registered or not */
		if(DMA_TransferErrorNotificationFunc[3] != NULL)
		{
			/* Invoke DMA Transfer Error Callback Function */
			DMA_TransferErrorNotificationFunc[3]();
		}

		/* Clear DMA Transfer Error flag */
		DMA_ClearInterruptFlag(DMA_CH4, DMA_TRANSFER_ERROR_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Clear DMA Global Interrupt flag */
	DMA_ClearInterruptFlag(DMA_CH4, DMA_GLOBAL_INTERRUPT_FLAG);
}

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: DMA1 channel5 interrupt                                         */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void DMA1_Channel5_IRQHandler(void)
{
	/* Local variables definitions */
	uint8_t Local_InterruptSource = 0;

	/**************************************Check source of interrupt**************************************/

	/* Check if interrupt source is DMA Transfer Complete */
    DMA_GetInterruptFlagStatus(DMA_CH5, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Complete callback function is registered or not */
		if(DMA_TransferCompleteNotificationFunc[4] != NULL)
		{
			/* Invoke DMA Transfer Complete Callback Function */
			DMA_TransferCompleteNotificationFunc[4]();
		}

		/* Clear DMA Transfer Complete flag */
		DMA_ClearInterruptFlag(DMA_CH5, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Half Transfer */
	DMA_GetInterruptFlagStatus(DMA_CH5, DMA_HALF_TRANSFER_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Half Transfer callback function is registered or not */
		if(DMA_HalfTransferNotificationFunc[4] != NULL)
		{
			/* Invoke DMA Half Transfer Callback Function */
			DMA_HalfTransferNotificationFunc[4]();
		}

		/* Clear DMA Half Transfer flag */
		DMA_ClearInterruptFlag(DMA_CH5, DMA_HALF_TRANSFER_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Transfer Error */
	DMA_GetInterruptFlagStatus(DMA_CH5, DMA_TRANSFER_ERROR_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Error callback function is registered or not */
		if(DMA_TransferErrorNotificationFunc[4] != NULL)
		{
			/* Invoke DMA Transfer Error Callback Function */
			DMA_TransferErrorNotificationFunc[4]();
		}

		/* Clear DMA Transfer Error flag */
		DMA_ClearInterruptFlag(DMA_CH5, DMA_TRANSFER_ERROR_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Clear DMA Global Interrupt flag */
	DMA_ClearInterruptFlag(DMA_CH5, DMA_GLOBAL_INTERRUPT_FLAG);
}

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: DMA1 channel6 interrupt                                         */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void DMA1_Channel6_IRQHandler(void)
{
	/* Local variables definitions */
	uint8_t Local_InterruptSource = 0;

	/**************************************Check source of interrupt**************************************/

	/* Check if interrupt source is DMA Transfer Complete */
    DMA_GetInterruptFlagStatus(DMA_CH6, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Complete callback function is registered or not */
		if(DMA_TransferCompleteNotificationFunc[5] != NULL)
		{
			/* Invoke DMA Transfer Complete Callback Function */
			DMA_TransferCompleteNotificationFunc[5]();
		}

		/* Clear DMA Transfer Complete flag */
		DMA_ClearInterruptFlag(DMA_CH6, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Half Transfer */
	DMA_GetInterruptFlagStatus(DMA_CH6, DMA_HALF_TRANSFER_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Half Transfer callback function is registered or not */
		if(DMA_HalfTransferNotificationFunc[5] != NULL)
		{
			/* Invoke DMA Half Transfer Callback Function */
			DMA_HalfTransferNotificationFunc[5]();
		}

		/* Clear DMA Half Transfer flag */
		DMA_ClearInterruptFlag(DMA_CH6, DMA_HALF_TRANSFER_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Transfer Error */
	DMA_GetInterruptFlagStatus(DMA_CH6, DMA_TRANSFER_ERROR_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Error callback function is registered or not */
		if(DMA_TransferErrorNotificationFunc[5] != NULL)
		{
			/* Invoke DMA Transfer Error Callback Function */
			DMA_TransferErrorNotificationFunc[5]();
		}

		/* Clear DMA Transfer Error flag */
		DMA_ClearInterruptFlag(DMA_CH6, DMA_TRANSFER_ERROR_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Clear DMA Global Interrupt flag */
	DMA_ClearInterruptFlag(DMA_CH6, DMA_GLOBAL_INTERRUPT_FLAG);
}

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/* @Description	: DMA1 channel7 interrupt                                         */
/*				                                                                  */
/*--------------------------------------------------------------------------------*/
void DMA1_Channel7_IRQHandler(void)
{
	/* Local variables definitions */
	uint8_t Local_InterruptSource = 0;

	/**************************************Check source of interrupt**************************************/

	/* Check if interrupt source is DMA Transfer Complete */
    DMA_GetInterruptFlagStatus(DMA_CH7, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Complete callback function is registered or not */
		if(DMA_TransferCompleteNotificationFunc[6] != NULL)
		{
			/* Invoke DMA Transfer Complete Callback Function */
			DMA_TransferCompleteNotificationFunc[6]();
		}

		/* Clear DMA Transfer Complete flag */
		DMA_ClearInterruptFlag(DMA_CH7, DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Half Transfer */
	DMA_GetInterruptFlagStatus(DMA_CH7, DMA_HALF_TRANSFER_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Half Transfer callback function is registered or not */
		if(DMA_HalfTransferNotificationFunc[6] != NULL)
		{
			/* Invoke DMA Half Transfer Callback Function */
			DMA_HalfTransferNotificationFunc[6]();
		}

		/* Clear DMA Half Transfer flag */
		DMA_ClearInterruptFlag(DMA_CH7, DMA_HALF_TRANSFER_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Check if interrupt source is DMA Transfer Error */
	DMA_GetInterruptFlagStatus(DMA_CH7, DMA_TRANSFER_ERROR_INTERRUPT_FLAG, &Local_InterruptSource);

	if(Local_InterruptSource == 1)
	{
		/* Check if DMA Transfer Error callback function is registered or not */
		if(DMA_TransferErrorNotificationFunc[6] != NULL)
		{
			/* Invoke DMA Transfer Error Callback Function */
			DMA_TransferErrorNotificationFunc[6]();
		}

		/* Clear DMA Transfer Error flag */
		DMA_ClearInterruptFlag(DMA_CH7, DMA_TRANSFER_ERROR_INTERRUPT_FLAG);

		/* Clear Local_InterruptSource */
		Local_InterruptSource = 0;
	}

	/******************************************************************************************************/

	/* Clear DMA Global Interrupt flag */
	DMA_ClearInterruptFlag(DMA_CH7, DMA_GLOBAL_INTERRUPT_FLAG);
}

