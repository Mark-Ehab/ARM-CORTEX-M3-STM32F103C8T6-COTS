/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Mar 4, 2022               	*/
/*      			SWC          : STK  			            */
/*     			    Description	 : STK Interface                */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						  _____ _______ _  __  _____       _             __                                 */
/*						 / ____|__   __| |/ / |_   _|     | |           / _|                                */
/*						| (___    | |  | ' /    | |  _ __ | |_ ___ _ __| |_ __ _  ___ ___                   */
/*						 \___ \   | |  |  <     | | | '_ \| __/ _ \ '__|  _/ _` |/ __/ _ \                  */
/*						 ____) |  | |  | . \   _| |_| | | | ||  __/ |  | || (_| | (_|  __/                  */
/*						|_____/   |_|  |_|\_\ |_____|_| |_|\__\___|_|  |_| \__,_|\___\___|                  */
/*						                                                                                    */
/*                                                                                                	        */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef STK_MCAL_INTERFACE_H_
#define STK_MCAL_INTERFACE_H_

/*--------------------------------------------------------------------------------------------------------*/
/*																										  */
/*									    Important Notes on SYSTICK									      */
/*																								 	  	  */
/* Note(1)	: The number of ticks (RELOAD) value can be any value in the range 0x00000001-0x00FFFFFF 	  */
/*																								     	  */
/* Note(2)	: The RELOAD value is calculated according to its use:										  */
/*			  1) To generate a multi-shot timer with a period of N processor clock cycles, use a RELOAD   */
/*  		  value of N-1. For example, if the SysTick interrupt is required every 100 clock pulses, set */
/* 	    	  RELOAD to 99.                                                                               */
/* 	          2) To deliver a single SysTick interrupt after a delay of N processor clock cycles, use a   */
/*  		  RELOAD of value N. For example, if a SysTick interrupt is required after 400 clock		  */
/*  		  pulses, set RELOAD to 400.																  */
/*																								 	  	  */
/*--------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	    INTERFACE MACROS			                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define SysTick Boundary Values */
#define STK_MIN_VALUE					0x00000001U
#define STK_MAX_VALUE					0x00FFFFFFU

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  FUNCTIONS PROTOTYPES		          	             */
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
void STK_Init(void);

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
ERROR_STATUS_t STK_BusyWait(uint32_t Copy_Ticks);

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
ERROR_STATUS_t STK_SetSingleInterval(uint32_t Copy_Ticks , void (*Copy_pCallbackFunction)(void));

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
ERROR_STATUS_t STK_SetPeriodicInterval(uint32_t Copy_Ticks , void (*Copy_pCallbackFunction)(void));

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
void STK_StopTimer(void);

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
ERROR_STATUS_t STK_GetElapsedTime(uint32_t* Copy_pElapesdTime);

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
ERROR_STATUS_t STK_GetRemainingTime(uint32_t* Copy_pRemainingTime);

#endif /* STK_INTERFACE_H_ */
