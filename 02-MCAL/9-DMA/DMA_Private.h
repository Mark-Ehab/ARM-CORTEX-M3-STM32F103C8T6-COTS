/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Nov 21, 2023               	*/
/*      			SWC          : DMA  			            */
/*     			    Description	 : DMA Private                  */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*   	                    _____  __  __            _____      _            _                              */
/*   	                   |  __ \|  \/  |   /\     |  __ \    (_)          | |                             */
/*   	                   | |  | | \  / |  /  \    | |__) | __ ___   ____ _| |_ ___                        */
/*   	                   | |  | | |\/| | / /\ \   |  ___/ '__| \ \ / / _` | __/ _ \                       */
/*   	                   | |__| | |  | |/ ____ \  | |   | |  | |\ V / (_| | ||  __/                       */
/*   	                   |_____/|_|  |_/_/    \_\ |_|   |_|  |_| \_/ \__,_|\__\___|                       */
/*   					                                              							            */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef MCAL_DMA_PRIVATE_H_
#define MCAL_DMA_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              DMA REGISTERS DEFINITION		          	  	     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define DMA_Channel_t Type */
typedef struct
{
	volatile uint32_t CCR;                        /* Channel memory address register */
	volatile uint32_t CNDTR;                      /* Channel number of data register */
	volatile uint32_t CPAR;                       /* Channel peripheral address register */
	volatile uint32_t CMAR;                       /* Channel memory address register */
	volatile uint32_t RESERVED;                   /* Reserved bits */
}DMA_Channel_t;

typedef struct
{
	volatile uint32_t ISR;						  /* Interrupt status register */
	volatile uint32_t IFCR;						  /* Interrupt flag clear register */
	volatile DMA_Channel_t Channel[7];            /* DMA seven channels */
}DMA_t;

#define DMA ((volatile DMA_t*)0x40020000)

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              SOME BITS DEFINITIONS		 	             		 */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Some bits definitions of Channel Configuration Register (DMA_CCRx) */
#define CCR_EN				0U
#define CCR_TCIE            1U
#define CCR_HTIE            2U
#define CCR_TEIE            3U
#define CCR_DIR             4U
#define CCR_CIRC            5U
#define CCR_PINC            6U
#define CCR_MINC            7U
#define CCR_MEM2MEM         14U

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                  PRIVATE MACROS		       		    		     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* DMA Channel Priority Level Possible Values */
#define DMA_CHANNEL_PRIORITY_MASK   					    0xFFFFCFFFU
#define DMA_CHANNEL_PRIORITY_LOW_VAL					    0x00000000U
#define DMA_CHANNEL_PRIORITY_MEDIUM_VAL				    	0x00001000U
#define DMA_CHANNEL_PRIORITY_HIGH_VAL					    0x00002000U
#define DMA_CHANNEL_PRIORITY_VERY_HIGH_VAL					0x00003000U

/* DMA Memory Size Possible Values */
#define DMA_MEMORY_SIZE_MASK   					 		    0xFFFFF3FFU
#define DMA_MEMORY_SIZE_8_BITS_VAL						   	0x00000000U
#define DMA_MEMORY_SIZE_16_BITS_VAL						    0x00000400U
#define DMA_MEMORY_SIZE_32_BITS_VAL						    0x00000800U

/* DMA Peripheral Size Possible Values */
#define DMA_PERIPHERAL_SIZE_MASK   					 		0xFFFFFCFFU
#define DMA_PERIPHERAL_SIZE_8_BITS_VAL						0x00000000U
#define DMA_PERIPHERAL_SIZE_16_BITS_VAL						0x00000100U
#define DMA_PERIPHERAL_SIZE_32_BITS_VAL						0x00000200U

/* Define Min and Max Block Length Values */
#define DMA_MIN_BLOCK_LENGTH_VAL                            0U
#define DMA_MAX_BLOCK_LENGTH_VAL                            65535U

#endif /* MCAL_DMA_PRIVATE_H_ */
