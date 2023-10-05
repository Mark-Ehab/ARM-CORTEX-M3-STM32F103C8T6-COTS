/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 10, 2023               	*/
/*      			SWC          : EXTI  			            */
/*     			    Description	 : EXTI Private                 */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						   ________   _________ _____   _____      _            _                           */
/*						  |  ____\ \ / /__   __|_   _| |  __ \    (_)          | |                          */
/*						  | |__   \ V /   | |    | |   | |__) | __ ___   ____ _| |_ ___                     */
/*						  |  __|   > <    | |    | |   |  ___/ '__| \ \ / / _` | __/ _ \                    */
/*						  | |____ / . \   | |   _| |_  | |   | |  | |\ V / (_| | ||  __/                    */
/*						  |______/_/ \_\  |_|  |_____| |_|   |_|  |_| \_/ \__,_|\__\___|                    */
/*						                                                                                    */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef EXTI_MCAL_PRIVATE_H_
#define EXTI_MCAL_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            	 EXTI REGISTERS DEFINITION		          		     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
typedef struct
{
	volatile uint32_t IMR;			/* Interrupt mask register */
	volatile uint32_t EMR;          /* Event mask register */
	volatile uint32_t RTSR;         /* Rising trigger selection register */
	volatile uint32_t FTSR;         /* Falling trigger selection register */
	volatile uint32_t SWIER;        /* Software interrupt event register */
	volatile uint32_t PR;           /* Pending register */
} EXTI_t;

#define EXTI ((volatile EXTI_t*) 0x40010400)

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            CONFIGURATION OPTIONS VALUES		       		         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Enable and Disable signal values */
#define DISABLE					0
#define ENABLE					1

#endif /* EXTI_MCAL_PRIVATE_H_ */
