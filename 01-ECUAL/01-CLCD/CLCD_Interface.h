/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 18, 2021               	*/
/*              	SWC          : CLCD				        	*/
/*              	Description	 : CLCD Interface               */
/* 	       		    Version      : V1.0                         */
/****************************************************************/

#ifndef HAL_CLCD_INTERFACE_H_
#define HAL_CLCD_INTERFACE_H_

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*				     _____ _      _____ _____    _____       _             __                               */
/*				    / ____| |    / ____|  __ \  |_   _|     | |           / _|                              */
/*				   | |    | |   | |    | |  | |   | |  _ __ | |_ ___ _ __| |_ __ _  ___ ___                 */
/*				   | |    | |   | |    | |  | |   | | | '_ \| __/ _ \ '__|  _/ _` |/ __/ _ \                */
/*				   | |____| |___| |____| |__| |  _| |_| | | | ||  __/ |  | || (_| | (_|  __/                */
/*				    \_____|______\_____|_____/  |_____|_| |_|\__\___|_|  |_| \__,_|\___\___|                */
/*																									        */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   INTERFACE MACROS		                             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* CLCD Commands */
#define CLCD_FUNCTION_SET_EIGHT_BIT_MODE_CMD  		    0x38U
#define CLCD_FUNCTION_SET_FOUR_BIT_MODE_CMD  		    0x28U
#define CLCD_DISPLAY_ON_CURSOR_OFF_CMD   	    	    0x0CU
#define CLCD_DISPLAY_OFF_CURSOR_OFF_CMD    	    	    0x08U
#define CLCD_DISPLAY_ON_CURSOR_ON_CMD   	    		0x0EU
#define CLCD_DISPLAY_OFF_CURSOR_ON_CMD    	    	    0x0AU
#define CLCD_BLINK_CURSOR_CMD						    0x0FU
#define CLCD_SHIFT_LEFT_CURSOR_CMD					    0x10U
#define CLCD_SHIFT_RIGHT_CURSOR_CMD					    0x14U
#define CLCD_SHIFT_LEFT_DISPLAY_CMD					    0x18U
#define CLCD_SHIFT_RIGHT_DISPLAY_CMD					0x1CU
#define CLCD_BEGIN_AT_FIRST_LINE_CMD					0x80U
#define CLCD_BEGIN_AT_SECOND_LINE_CMD					0xC0U
#define CLCD_DISPLAY_CLEAR_CMD 						    0x01U
#define CLCD_ENTRY_MODE_CMD						  	    0x06U

/* CLCD Rows */
#define CLCD_ROW_0										0U
#define CLCD_ROW_1										1U

/* CLCD Columns */
#define CLCD_COLUMN_0								    0U
#define CLCD_COLUMN_1								    1U
#define CLCD_COLUMN_2                                   2U
#define CLCD_COLUMN_3                                   3U
#define CLCD_COLUMN_4                                   4U
#define CLCD_COLUMN_5                                   5U
#define CLCD_COLUMN_6                                   6U
#define CLCD_COLUMN_7                                   7U
#define CLCD_COLUMN_8                                   8U
#define CLCD_COLUMN_9                                   9U
#define CLCD_COLUMN_10                                  10U
#define CLCD_COLUMN_11                                  11U
#define CLCD_COLUMN_12                                  12U
#define CLCD_COLUMN_13                                  13U
#define CLCD_COLUMN_14                                  14U
#define CLCD_COLUMN_15                                  15U

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: Init							                                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Initialize Character LCD								          */
/*--------------------------------------------------------------------------------*/
void CLCD_Init(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: SendCommand							                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Command				                              */
/*                 Brief: Command to be sent to CLCD controller to perform        */
/*						  operation on CLCD                                       */
/*                 Range: - CLCD_FUNCTION_SET_EIGHT_BIT_MODE_CMD                  */
/*						  - CLCD_FUNCTION_SET_FOUR_BIT_MODE_CMD                   */
/*						  - CLCD_DISPLAY_ON_CURSOR_OFF_CMD   	                  */
/*						  - CLCD_DISPLAY_OFF_CURSOR_OFF_CMD    	                  */
/*						  - CLCD_DISPLAY_ON_CURSOR_ON_CMD   	                  */
/*						  - CLCD_DISPLAY_OFF_CURSOR_ON_CMD    	                  */
/*						  - CLCD_BLINK_CURSOR_CMD				                  */
/*						  - CLCD_SHIFT_LEFT_CURSOR_CMD			                  */
/*						  - CLCD_SHIFT_RIGHT_CURSOR_CMD			                  */
/*						  - CLCD_SHIFT_LEFT_DISPLAY_CMD			                  */
/*						  - CLCD_SHIFT_RIGHT_DISPLAY_CMD		                  */
/*						  - CLCD_BEGIN_AT_FIRST_LINE_CMD		                  */
/*						  - CLCD_BEGIN_AT_SECOND_LINE_CMD		                  */
/*						  - CLCD_DISPLAY_CLEAR_CMD 				                  */
/*						  - CLCD_ENTRY_MODE_CMD					                  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Send a command to Character LCD controller	                  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_SendCommand(uint8_t Copy_Command);

/*--------------------------------------------------------------------------------*/
/* @Function Name: WriteCharacter							                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Character				                          */
/*                 Brief: Character to be written on CLCD display 				  */
/*                 Range: Any value can be represented in 1 byte                  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Write a character on Character CLCD		                      */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_WriteCharacter(uint8_t Copy_Character);

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetEightBitMode							                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Set up Character LCD on 8-bit mode							  */
/*--------------------------------------------------------------------------------*/
void CLCD_SetEightBitMode(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetFourBitMode							                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Set up Character LCD on 4-bit mode							  */
/*--------------------------------------------------------------------------------*/
void CLCD_SetFourBitMode(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: DisplayOnCursorOff							                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Turn on display and turn off cursor							  */
/*--------------------------------------------------------------------------------*/
void CLCD_DisplayOnCursorOff(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: DisplayOffCursorOff							                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Turn off display and turn off cursor							  */
/*--------------------------------------------------------------------------------*/
void CLCD_DisplayOffCursorOff(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: DisplayOnCursorOn							                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Turn on display and turn on cursor							  */
/*--------------------------------------------------------------------------------*/
void CLCD_DisplayOnCursorOn(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: DisplayOffCursorOn							                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Turn off display and turn on cursor							  */
/*--------------------------------------------------------------------------------*/
void CLCD_DisplayOffCursorOn(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: BlinkCursor									                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Blink the cursor of Character LCD							  */
/*--------------------------------------------------------------------------------*/
void CLCD_BlinkCursor(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: ShiftLeftCursor									              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Shift left the cursor of Character LCD						  */
/*--------------------------------------------------------------------------------*/
void CLCD_ShiftLeftCursor(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: ShiftRightCursor									              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Shift right the cursor of Character LCD						  */
/*--------------------------------------------------------------------------------*/
void CLCD_ShiftRightCursor(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: ShiftDisplayLeft									              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Shift left the entire display of Character LCD				  */
/*--------------------------------------------------------------------------------*/
void CLCD_ShiftDisplayLeft(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: ShiftDisplayRight									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Shift right the entire display of Character LCD				  */
/*--------------------------------------------------------------------------------*/
void CLCD_ShiftDisplayRight(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: BeginAtFirstLine 									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Force cursor to be at the beginning of the first line		  */
/*--------------------------------------------------------------------------------*/
void CLCD_BeginAtFirstLine(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: BeginAtSecondLine 									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Force cursor to be at the beginning of the second line		  */
/*--------------------------------------------------------------------------------*/
void CLCD_BeginAtSecondLine(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: ClearDisplay     									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Clear the entire display of character LCD		 			  */
/*--------------------------------------------------------------------------------*/
void CLCD_ClearDisplay(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetEntryMode     									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Set up character LCD to operate on the entry mode		 	  */
/*--------------------------------------------------------------------------------*/
void CLCD_SetEntryMode(void);

/*--------------------------------------------------------------------------------*/
/* @Function Name: WriteString      									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t* Copy_pString				                          */
/*				   Brief: Pointer to character for the first character of the     */
/*                        string to be written on character LCD 	              */
/*                 Range: None                                                    */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Write a string on the Character LCD display      		 	  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_WriteString(uint8_t* Copy_pString);

/*--------------------------------------------------------------------------------*/
/* @Function Name: WriteNumber      									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : sint32_t Copy_Number    				                          */
/*				   Brief: Number (Could be positive or negative) to be written on */
/*                        character LCD 	                                      */
/*                 Range: None                                                    */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Write an integer number (Could be positive or negative)        */
/*                 on the Character LCD display      	 						  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_WriteNumber(sint32_t Copy_Number);

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetCGRamAddress      									      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Location    				                      */
/*				   Brief: Address of CGRAM location to be pointed to	          */
/*                 Range: -	                                                      */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Force the Character LCD controller to point to a CGRAM address */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_SetCGRamAddress(uint8_t Copy_Location);

/*--------------------------------------------------------------------------------*/
/* @Function Name: WriteCustomCharactersOnCGRam      							  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t* Copy_pCharacter    				                      */
/*				   Brief: Pointer to character to be stored in CGRAM              */
/*				   Range: None	                                                  */
/*				   -------------------------------------------------------------- */
/*                 uint8_t Copy_Location                                          */
/*				   Brief: Address of CGRAM location to be pointed to	          */
/*				   Range: -											              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Add custom characters to CGRAM of Character LCD   			  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_WriteCustomCharactersOnCGRam(uint8_t* Copy_pCharacter,uint8_t Copy_Location);

/*--------------------------------------------------------------------------------*/
/* @Function Name: WriteCustomCharactersOnCGRam      							  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_RowNumber    				                      */
/*				   Brief: CLCD row number          						          */
/*				   Range: (CLCD_ROW_0 --> CLCD_ROW_1)	                          */
/*				   -------------------------------------------------------------- */
/*                 uint8_t Copy_ColumnNumber                                      */
/*				   Brief: CLCD column number							          */
/*				   Range: (CLCD_COLUMN_0 --> CLCD_COLUMN_15)	                  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Put the cursor at a specific location (segment) on the         */
/*                 character LCD display					                      */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_MoveCursor(uint8_t Copy_RowNumber , uint8_t Copy_ColumnNumber);

#endif /* HAL_CLCD_INTERFACE_H_ */
