/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 17, 2023               	*/
/*      			SWC          : AFIO  			            */
/*     			    Description	 : AFIO Private                 */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*		                            ______ _____ ____    _____      _            _                          */
/*		                      /\   |  ____|_   _/ __ \  |  __ \    (_)          | |                         */
/*		                     /  \  | |__    | || |  | | | |__) | __ ___   ____ _| |_ ___                    */
/*		                    / /\ \ |  __|   | || |  | | |  ___/ '__| \ \ / / _` | __/ _ \                   */
/*		                   / ____ \| |     _| || |__| | | |   | |  | |\ V / (_| | ||  __/                   */
/*		                  /_/    \_\_|    |_____\____/  |_|   |_|  |_| \_/ \__,_|\__\___|                   */
/*						                                                   							        */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef AFIO_MCAL_PRIVATE_H_
#define AFIO_MCAL_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            	 AFIO REGISTERS DEFINITION		          		     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
typedef struct
{
	volatile uint32_t EVCR;				  /* Event control register */
	volatile uint32_t MAPR;               /* AF remap and debug I/O configuration register */
	volatile uint32_t EXTICR1;            /* External interrupt configuration register 1 */
	volatile uint32_t EXTICR2;            /* External interrupt configuration register 2 */
	volatile uint32_t EXTICR3;            /* External interrupt configuration register 3 */
	volatile uint32_t EXTICR4;            /* External interrupt configuration register 4 */
	volatile uint32_t MAPR2;              /* AF remap and debug I/O configuration register2 */

}AFIO_t;

#define AFIO ((volatile AFIO_t*)0x40010000)

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            	     PRIVATE MACROS		          		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Alternative Function Remap Masks */

/* SPI1 Remap Mask */
#define AFIO_SPI1_REMAP_MASK            0xFFFFFFFEU

/* I2C1 Remap Mask */
#define AFIO_I2C1_REMAP_MASK            0xFFFFFFFDU

/* USART1 Remap Mask */
#define AFIO_USART1_REMAP_MASK          0xFFFFFFFBU

/* USART2 Remap Mask */
#define AFIO_USART2_REMAP_MASK          0xFFFFFFF7U

/* USART3 Remap Mask */
#define AFIO_USART3_REMAP_MASK          0xFFFFFFCFU

/* TIM1 Remap Mask */
#define AFIO_TIM1_REMAP_MASK            0xFFFFFF3FU

/* TIM2 Remap Mask */
#define AFIO_TIM2_REMAP_MASK            0xFFFFFCFFU

/* TIM3 Remap Mask */
#define AFIO_TIM3_REMAP_MASK            0xFFFFF3FFU

/* TIM4 Remap Mask */
#define AFIO_TIM4_REMAP_MASK            0xFFFFEFFFU

/* CAN Remap Mask */
#define AFIO_CAN_REMAP_MASK             0xFFFF9FFFU

/* PD01 Remap Mask */
#define AFIO_PD01_REMAP_MASK            0xFFFF7FFFU

/* TIM5CH4 Internal Remap Mask */
#define AFIO_TIM5CH4_IREMAP_MASK        0xFFFEFFFFU

/* ADC 1 External trigger injected conversion Remap Mask */
#define AFIO_ADC1_ETRGINJ_REMAP_MASK    0xFFFDFFFFU

/* ADC 1 external trigger regular conversion Remap Mask */
#define AFIO_ADC1_ETRGREG_REMAP_MASK    0xFFFBFFFFU

/* ADC 2 external trigger injected conversion Remap Mask */
#define AFIO_ADC2_ETRGINJ_REMAP_MASK    0xFFF7FFFFU

/* ADC 2 external trigger regular conversion Remap Mask */
#define AFIO_ADC2_ETRGREG_REMAP_MASK    0xFFEFFFFFU

/* Serial wire JTAG configuration */
#define AFIO_SWJ_CFG_REMAP_MASK         0xF8FFFFFFU

/* TIM9 Remap Mask */
#define AFIO_TIM9_REMAP_MASK			0xFFFFFFDFU

/* TIM10 Remap Mask */
#define AFIO_TIM10_REMAP_MASK           0xFFFFFFBFU

/* TIM11 Remap Mask */
#define AFIO_TIM11_REMAP_MASK           0xFFFFFF7FU

/* TIM13 Remap Mask */
#define AFIO_TIM13_REMAP_MASK			0xFFFFFEFFU

/* TIM14 Remap Mask */
#define AFIO_TIM14_REMAP_MASK			0xFFFFFDFFU

/* FSMC NADV Remap Mask */
#define AFIO_FSMC_NADV_REMAP_MASK		0xFFFFFBFFU


#endif /* AFIO_MCAL_PRIVATE_H_ */
