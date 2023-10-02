/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 12, 2023               	*/
/*      			SWC          : FPEC  			            */
/*     			    Description	 : FPEC Program                 */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						 ______ _____  ______ _____   _____                                                 */
/*						|  ____|  __ \|  ____/ ____| |  __ \                                                */
/*						| |__  | |__) | |__ | |      | |__) | __ ___   __ _ _ __ __ _ _ __ ___              */
/*						|  __| |  ___/|  __|| |      |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \             */
/*						| |    | |    | |___| |____  | |   | | | (_) | (_| | | | (_| | | | | | |            */
/*						|_|    |_|    |______\_____| |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|            */
/*						                                               __/ |                                */
/*						                            				  |___/                                 */
/*----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "STD_TYPES.h"
#include "STD_ERRORS.h"
#include "BIT_MATH.h"

#include "FPEC_Private.h"
#include "FPEC_Config.h"
#include "FPEC_Interface.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             FUNCTIONS IMPLEMENTATIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: FlashPageErase          					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_PageNumber				                          */
/*				   Brief: Number of page in flash to be erased					  */
/* 				   Range:(FPEC_PAGE_0 --> FPEC_PAGE_127) 						  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function erases a full page on flash memory based on its  */
/* 				   passed number									        	  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t FPEC_FlashPageErase(uint8_t Copy_PageNumber)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;				/* Variable to hold status of the function */

	/* Check if passed page number is within its valid range */
	if(Copy_PageNumber >= FPEC_PAGE_0 && Copy_PageNumber <= FPEC_PAGE_127)
	{
		/* Wait for Busy Flag */
		while (GET_BIT(FPEC->SR,SR_BSY) == 1);

		/* Check if FPEC is locked or not */
		if (GET_BIT(FPEC->CR,CR_LOCK) == 1)
		{
			FPEC -> KEYR = FPEC_UNLOCK_KEY1;
			FPEC -> KEYR = FPEC_UNLOCK_KEY2;
		}

		/* Page Erase Operation */
		SET_BIT(FPEC->CR,CR_PER);

		/* Write Page address */
		FPEC->AR = (uint32_t)(Copy_PageNumber * 1024) + FPEC_FLASH_FIRST_ADDRESS ;

		/* Start operation */
		SET_BIT(FPEC->CR,CR_STRT);

		/* Wait for Busy Flag */
		while (GET_BIT(FPEC->SR,SR_BSY) == 1);

		/* End of Page Erasing Operation */
		SET_BIT(FPEC->SR,SR_EOP);
		CLEAR_BIT(FPEC->CR,CR_PER);
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: EraseBankArea          					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_PageNumber				                          */
/*				   Brief: Number of bank start page in flash for the bank to be   */
/* 				          erased. 										  		  */
/*				   Range:(FPEC_PAGE_0 --> FPEC_PAGE_127)						  */
/*                 -------------------------------------------------------------- */
/*				   uint32_t Copy_BankSize								    	  */
/*				   Brief: Size of the bank to be erased in flash                  */
/*				   Range: Limited to flash size.                                  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function erases a full bank on flash memory based on	  */
/* 				   passed start page number	and bank size				       	  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t FPEC_EraseBankArea(uint8_t Copy_PageNumber , uint32_t Copy_BankSize)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;				/* Variable to hold status of the function */
	uint8_t Local_PageCounter;							/* Variable to hold counts of flash pages */

	/* Check if passed page number and bank size are within their valid ranges */
	if((Copy_PageNumber >= FPEC_PAGE_0 && Copy_PageNumber <= FPEC_PAGE_127) &&
	   (Copy_BankSize >= 0 && Copy_BankSize <= 4294967295))
	{
		/* Traverse over each page in the bank then erase it until you reach the bank end */
		for (Local_PageCounter = 0 ; Local_PageCounter < Copy_BankSize ; Local_PageCounter++)
		{
			/* Erase a page in flash memory */
			FPEC_FlashPageErase((uint8_t)(Local_PageCounter + Copy_PageNumber));
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
/* @Function Name: FlashWriteHexRecord	          					              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint32_t Copy_Address                                          */
/*				   Brief: Data Hex Record Address								  */
/*				   Range: Limited to flash size	(FPEC_FLASH_FIRST_ADDRESS -->	  */
/* 						  FPEC_FLASH_LASR_ADDRESS)								  */
/*                 -------------------------------------------------------------- */
/* 				   uint16_t* Copy_pData                                           */
/*				   Brief: Array of halfwords (Data Hex Record)					  */
/*				   Range: None								   					  */
/*                 -------------------------------------------------------------- */
/* 				   uint8_t Copy_Length				                      	      */
/*				   Brief: Halfword Count in Data Hex Record						  */
/*				   Range: Any value can be stored within one byte 				  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function writes a hex record on flash based on its		  */
/*				   passed address, data and length in halfwords					  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t FPEC_FlashWriteHexRecord(uint32_t Copy_Address, uint16_t* Copy_pData, uint8_t Copy_Length)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;				/* Variable to hold status of the function */
	uint8_t Local_HalfWordCounter;						/* Variable to hold counts of halfwords in data hex record */

	/* Check if passed pointer (array) is NULL pointer or not */
	if(Copy_pData != NULL)
	{
		/* Check if passed flash address and length are within their valid ranges */
		if((Copy_Address >= FPEC_FLASH_FIRST_ADDRESS && Copy_Address <= FPEC_FLASH_LAST_ADDRESS) &&
		   (Copy_Length >= 0 && Copy_Length <= 255))
		{
			/* Wait for Busy Flag */
			while (GET_BIT(FPEC->SR,SR_BSY) == 1);

			/* Check if FPEC is locked or not */
			if (GET_BIT(FPEC->CR,CR_LOCK) == 1)
			{
				FPEC -> KEYR = FPEC_UNLOCK_KEY1;
				FPEC -> KEYR = FPEC_UNLOCK_KEY2;
			}

			for (Local_HalfWordCounter = 0; Local_HalfWordCounter < Copy_Length; Local_HalfWordCounter++)
			{
				/* Write Flash Programming */
				SET_BIT(FPEC->CR,CR_PG);

				/* Half word flash programming operation */
				*((volatile uint16_t*)Copy_Address) = Copy_pData[Local_HalfWordCounter];
				Copy_Address += 2;

				/* Wait for Busy Flag */
				while (GET_BIT(FPEC->SR,SR_BSY) == 1);

				/* End of Flash Programming Operation */
				SET_BIT(FPEC->SR,SR_EOP);
				CLEAR_BIT(FPEC->CR,CR_PG);
			}
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
/* @Function Name: WriteOptionByteData0          					              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Value				                   	          */
/*				   Brief: Value to be stored in option byte Data 0 				  */
/*				   Range: Any value can be stored within one byte				  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function stores a value in option byte Data0		 	  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t FPEC_WriteOptionByteData0(uint8_t Copy_Value)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;				/* Variable to hold status of the function */

	/* Check if passed value is within its valid range */
	if (Copy_Value >= 0 && Copy_Value <= 255)
	{
		/* Wait for Busy Flag */
		while (GET_BIT(FPEC->SR,SR_BSY) == 1);

		/* Check if FPEC is locked or not */
		if ( GET_BIT(FPEC->CR,CR_LOCK) == 1)
		{
			/* Unlock FPEC */
			FPEC -> KEYR = FPEC_UNLOCK_KEY1;
			FPEC -> KEYR = FPEC_UNLOCK_KEY2;
		}

		/* Unlock Option Bytes Programming */
		FPEC -> OPTKEYR = FPEC_UNLOCK_KEY1;
		FPEC -> OPTKEYR = FPEC_UNLOCK_KEY2;

		/* Enable Option Bytes Programming */
		SET_BIT(FPEC->CR,CR_OPTWRE);

		/* Erase Option Bytes */
		SET_BIT(FPEC->CR,CR_OPTER);
		SET_BIT(FPEC->CR,CR_STRT);

		/* Wait for Busy Flag */
		while (GET_BIT(FPEC->SR,SR_BSY) == 1);

		/* End of Option Bytes Erase Operation */
		SET_BIT(FPEC->SR,SR_EOP);
		CLEAR_BIT(FPEC->CR,CR_OPTER);

		/* Program Option Bytes */
		SET_BIT(FPEC->CR,CR_OPTPG);

		/* Unlock read protection */
		*(volatile uint16_t*)(0x1FFFF800) = FPEC_READ_PROTECTION_UNLOCK_KEY;

		/* Wait for Busy Flag */
		while (GET_BIT(FPEC->SR,SR_BSY) == 1);

		/* Set Option Byte DATA0 */
		FPEC_OPTION_BYTE_DATA0 = (uint16_t)Copy_Value;

		/* Wait for Busy Flag */
		while (GET_BIT(FPEC->SR,SR_BSY) == 1);

		/* End of Option Bytes Programming Operation */
		SET_BIT(FPEC->SR,SR_EOP);
		CLEAR_BIT(FPEC->CR,CR_OPTPG);
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: EraseBankArea          					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None									                          */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : uint8_t* Copy_pValue                                           */
/*				   Brief: Input argument of type pointer to unit8_t that holds    */
/* 					   	  the address of the variable in which the data read from */
/*					  	  option byte Data0 will be stored						  */
/*				   Range: None													  */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function gets (reads) the value stored in option byte 	  */
/* 				   Data0	  													  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t FPEC_GetOptionByteData0Val(uint8_t* Copy_pValue)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;				/* Variable to hold status of the function */

	/* Check if passed pointer is NULL pointer or not */
	if(Copy_pValue != NULL)
	{
		/* Get Value of Option Byte Data0 */
		*Copy_pValue = (uint8_t)((FPEC->OBR & FPEC_OPTION_BYTE_DATA0_MASK)>>10);
	}
	else
	{
		/* Passed pointer is NULL pointer */
		Local_Status = NULL_POINTER;
	}

	return Local_Status;
}
