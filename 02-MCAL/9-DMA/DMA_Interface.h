/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Nov 21, 2023               	*/
/*      			SWC          : DMA  			            */
/*     			    Description	 : DMA Interface                */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						 _____  __  __            _____       _             __                              */
/*						|  __ \|  \/  |   /\     |_   _|     | |           / _|                             */
/*						| |  | | \  / |  /  \      | |  _ __ | |_ ___ _ __| |_ __ _  ___ ___                */
/*						| |  | | |\/| | / /\ \     | | | '_ \| __/ _ \ '__|  _/ _` |/ __/ _ \               */
/*						| |__| | |  | |/ ____ \   _| |_| | | | ||  __/ |  | || (_| | (_|  __/               */
/*						|_____/|_|  |_/_/    \_\ |_____|_| |_|\__\___|_|  |_| \__,_|\___\___|               */
/*						                                                                                    */
/*                                                                                                   	    */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef MCAL_DMA_INTERFACE_H_
#define MCAL_DMA_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	     NEW DATA TYPES			               	         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* DMA Channel Configuration Type */
typedef struct
{
	uint8_t transferCompleteInterruptEnable;
	uint8_t halfTransferInterruptEnable;
	uint8_t transferErrorInterruptEnable;
	uint8_t dataTransferDirection;
	uint8_t circularModeEnable;
	uint8_t peripheralIncrementModeEnable;
	uint8_t memoryIncrementModeEnable;
	uint8_t peripheralSize;
	uint8_t memorySize;
	uint8_t channelPriorityLevel;
	uint8_t memToMemModeEnable;
	uint16_t channelBlockLength;
}DMA_ChannelConfig_t;

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	    INTERFACE MACROS			                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* DMA Available Channels */
#define DMA_CH1        			                        0U
#define DMA_CH2                                         1U
#define DMA_CH3                                         2U
#define DMA_CH4                                         3U
#define DMA_CH5                                         4U
#define DMA_CH6                                         5U
#define DMA_CH7                                         6U

/* DMA Channel Enable/Disable Signals */
#define DMA_CHANNEL_DISABLE                             0U
#define DMA_CHANNEL_ENABLE                              1U

/* DMA Memory to Memory Mode */
#define DMA_MEM_TO_MEM_MODE_DISABLE                     0U
#define DMA_MEM_TO_MEM_MODE_ENABLE                      1U

/* DMA Channel Priority Level Options */
#define DMA_CHANNEL_PRIORITY_LOW					    0U
#define DMA_CHANNEL_PRIORITY_MEDIUM					    1U
#define DMA_CHANNEL_PRIORITY_HIGH					    2U
#define DMA_CHANNEL_PRIORITY_VERY_HIGH					3U

/* DMA Memory Size Options */
#define DMA_MEMORY_SIZE_8_BITS						    0U
#define DMA_MEMORY_SIZE_16_BITS						    1U
#define DMA_MEMORY_SIZE_32_BITS						    2U

/* DMA Peripheral Size Options */
#define DMA_PERIPHERAL_SIZE_8_BITS						0U
#define DMA_PERIPHERAL_SIZE_16_BITS						1U
#define DMA_PERIPHERAL_SIZE_32_BITS						2U

/* DMA Memory Increment Mode */
#define DMA_MEMORY_INCREMENT_MODE_DISABLE				0U
#define DMA_MEMORY_INCREMENT_MODE_ENABLE				1U

/* DMA Peripheral Increment Mode */
#define DMA_PERIPHERAL_INCREMENT_MODE_DISABLE			0U
#define DMA_PERIPHERAL_INCREMENT_MODE_ENABLE			1U

/* DMA Circular Mode */
#define DMA_CIRCULAR_MODE_DISABLE					    0U
#define DMA_CIRCULAR_MODE_ENABLE					    1U

/* DMA Transfer Direction Options */
#define DMA_READ_FROM_PERIPHERAL					 	0U
#define DMA_READ_FROM_MEMORY							1U

/* DMA Interrupts */
/* DMA Transfer Complete Interrupt */
#define DMA_TRANSFER_COMPLETE_INTERRUPT_DISABLE			0U
#define DMA_TRANSFER_COMPLETE_INTERRUPT_ENABLE			1U

/* DMA Half Transfer Interrupt */
#define DMA_HALF_TRANSFER_INTERRUPT_DISABLE			    0U
#define DMA_HALF_TRANSFER_INTERRUPT_ENABLE			    1U

/* DMA Transfer Error Interrupt */
#define DMA_TRANSFER_ERROR_INTERRUPT_DISABLE			0U
#define DMA_TRANSFER_ERROR_INTERRUPT_ENABLE			    1U

/* Possible DMA Interrupt Flags */
#define DMA_GLOBAL_INTERRUPT_FLAG           			0U
#define DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG			1U
#define DMA_HALF_TRANSFER_INTERRUPT_FLAG				2U
#define DMA_TRANSFER_ERROR_INTERRUPT_FLAG				3U

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  FUNCTIONS PROTOTYPES		          	             */
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
ERROR_STATUS_t DMA_ChannelInit(uint8_t Copy_ChannelId ,DMA_ChannelConfig_t* Copy_pChannelConfig);

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
ERROR_STATUS_t DMA_ChannelStart(uint8_t Copy_ChannelId , uint32_t* Copy_pSourceAddress , uint32_t* Copy_pDestinationAddress);

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
ERROR_STATUS_t DMA_SetChannelState(uint8_t Copy_ChannelId , uint8_t Copy_ChannelState);

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
ERROR_STATUS_t DMA_RegisterTransferCompleteCallback(uint8_t Copy_ChannelId , void(*Copy_NotificationFunc)(void));

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
ERROR_STATUS_t DMA_RegisterHalfTransferCallback(uint8_t Copy_ChannelId , void(*Copy_NotificationFunc)(void));

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
ERROR_STATUS_t DMA_RegisterTransferErrorCallback(uint8_t Copy_ChannelId , void(*Copy_NotificationFunc)(void));

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
/*                        - DMA_TRANSFER_ERROR_INTERRUPT_FLAG					  */
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
ERROR_STATUS_t DMA_GetInterruptFlagStatus(uint8_t Copy_ChannelId , uint8_t Copy_InterruptFlagId , uint8_t* Copy_pInterruptFlagStatus);

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
/* 						  - DMA_TRANSFER_COMPLETE_INTERRUPT_FLAG                  */
/*                        - DMA_HALF_TRANSFER_INTERRUPT_FLAG	                  */
/*                        - DMA_TRANSFER_ERROR_INTERRUPT_FLAG		              */
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
ERROR_STATUS_t DMA_ClearInterruptFlag(uint8_t Copy_ChannelId , uint8_t Copy_InterruptFlagId);

#endif /* MCAL_DMA_INTERFACE_H_ */
