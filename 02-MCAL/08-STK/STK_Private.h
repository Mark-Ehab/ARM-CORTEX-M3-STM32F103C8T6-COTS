/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Mar 4, 2022               	*/
/*      			SWC          : STK  			            */
/*     			    Description	 : STK Private                  */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*   	                     _____ _______ _  __  _____      _            _                                 */
/*   	                    / ____|__   __| |/ / |  __ \    (_)          | |                                */
/*   	                   | (___    | |  | ' /  | |__) | __ ___   ____ _| |_ ___                           */
/*   	                    \___ \   | |  |  <   |  ___/ '__| \ \ / / _` | __/ _ \                          */
/*   	                    ____) |  | |  | . \  | |   | |  | |\ V / (_| | ||  __/                          */
/*   	                   |_____/   |_|  |_|\_\ |_|   |_|  |_| \_/ \__,_|\__\___|                          */
/*   					                                           							                */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef STK_MCAL_PRIVATE_H_
#define STK_MCAL_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              STK REGISTERS DEFINITION		          	  	     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

typedef struct
{
        volatile uint32_t CTRL; 				/* SysTick control and status register */
        volatile uint32_t LOAD;        			/* SysTick reload value register */
        volatile uint32_t VAL;         			/* SysTick current value register */
        volatile uint32_t CALIB;        		/* SysTick calibration value register */
}STK_t;

#define STK  ((volatile STK_t*)0xE000E010)

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              SOME BITS DEFINITIONS		 	             		 */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Some bits definitions of SysTick control and status register (STK_CTRL) */
#define CTRL_ENABLE			                    0U  /* Counter enable */
#define CTRL_TICKINT		                    1U  /* SysTick exception request enable */
#define CTRL_CLKSOURCE                          2U  /* Clock source selection */
#define CTRL_COUNTFLAG                          16U /* Counter flag */

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                  PRIVATE MACROS		       		    		     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define Systick Interval Modes */
#define STK_SINGLE_INTERVAL    0U
#define STK_PERIODIC_INTERVAL  1U

/* Define Systick Clear Value */
#define STK_CLEAR			   0U

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            CONFIGURATION OPTIONS VALUES		       		         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* SysTick Clock Source Options */
#define AHB_DIV_BY_EIGHT     0U
#define AHB  		         1U

/* Enable/Disable option values of SysTick exception request */
#define DISABLE				 0U
#define ENABLE				 1U

#endif /* STK_PRIVATE_H_ */
