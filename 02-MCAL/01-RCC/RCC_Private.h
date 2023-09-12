/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 7, 2023               	*/
/*      			SWC          : RCC  	               		*/
/*              	Description	 : RCC Private                  */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*		                      _____   _____ _____   _____      _            _                               */
/*		                     |  __ \ / ____/ ____| |  __ \    (_)          | |                              */
/*		                     | |__) | |   | |      | |__) | __ ___   ____ _| |_ ___                         */
/*		                     |  _  /| |   | |      |  ___/ '__| \ \ / / _` | __/ _ \                        */
/*		                     | | \ \| |___| |____  | |   | |  | |\ V / (_| | ||  __/                        */
/*		                     |_|  \_\\_____\_____| |_|   |_|  |_| \_/ \__,_|\__\___|                        */
/*							                                            								    */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef RCC_MCAL_PRIVATE_H_
#define RCC_MCAL_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            	 RCC REGISTERS DEFINITION		          		     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
typedef struct
{
        volatile uint32_t CR;					/* Clock control register */
        volatile uint32_t CFGR;                 /* Clock configuration register */
        volatile uint32_t CIR;                  /* Clock interrupt register */
        volatile uint32_t APB2RSTR;             /* APB2 peripheral reset register */
        volatile uint32_t APB1RSTR;             /* APB1 peripheral reset register */
        volatile uint32_t AHBENR;               /* AHB peripheral clock enable register */
        volatile uint32_t APB2ENR;              /* APB2 peripheral clock enable register  */
        volatile uint32_t APB1ENR;              /* APB1 peripheral clock enable register */
        volatile uint32_t BDCR;                 /* Backup domain control register  */
        volatile uint32_t CSR;                  /* Control/status register */
}RCC_t;

#define RCC  ((volatile RCC_t*)0x40021000)

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              SOME BITS DEFINITIONS		 	             		 */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
/* Some bit definitions of Clock control register (RCC_CR) */
#define CR_HSION		               0U	        /* Internal high-speed clock enable */
#define CR_HSIRDY 		               1U	        /* Internal high-speed clock ready flag */
#define CR_HSEON 		               16U	        /* HSE clock enable */
#define CR_HSERDY 		               17U	        /* External high-speed clock ready flag */
#define CR_HSEBYP 		               18U	        /* External high-speed clock bypass */
#define CR_CSSON		               19U	        /* Clock security system enable */
#define CR_PLLON		               24U	        /* PLL enable */
#define CR_PLLRDY 		               25U	        /* PLL clock ready flag */

/* Some bit definitions of Clock configuration register (RCC_CFGR) */
#define CFGR_PLLSRC					   16U 			/* PLL entry clock source */
#define CFGR_PLLXTPRE 				   17U 			/* HSE divider for PLL entry */

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            		PRIVATE MACROS				       		         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* System Clock Switch Options */
#define RCC_SW_MASK					     0xFFFFFFFC
#define RCC_SW_HSI					     0x00000000
#define RCC_SW_HSE					     0x00000001
#define RCC_SW_PLL					     0x00000002

/* AHB Prescaler Options */
#define RCC_AHB_SYSCLK_PRESCALER_MASK	 0xFFFFFF0F
#define RCC_AHB_SYSCLK_NOT_DIVIDED       0x00000000
#define RCC_AHB_SYSCLK_DIV_BY_2          0x00000080
#define RCC_AHB_SYSCLK_DIV_BY_4          0x00000090
#define RCC_AHB_SYSCLK_DIV_BY_8          0x000000A0
#define RCC_AHB_SYSCLK_DIV_BY_16         0x000000B0
#define RCC_AHB_SYSCLK_DIV_BY_64         0x000000C0
#define RCC_AHB_SYSCLK_DIV_BY_128        0x000000D0
#define RCC_AHB_SYSCLK_DIV_BY_256        0x000000E0
#define RCC_AHB_SYSCLK_DIV_BY_512        0x000000F0

/* APB1 Prescaler Options */
#define RCC_APB1_HCLK_PRESCALER_MASK     0xFFFFF8FF
#define RCC_APB1_HCLK_NOT_DIVIDED        0x00000000
#define RCC_APB1_HCLK_DIV_BY_2           0x00000400
#define RCC_APB1_HCLK_DIV_BY_4           0x00000500
#define RCC_APB1_HCLK_DIV_BY_8           0x00000600
#define RCC_APB1_HCLK_DIV_BY_16          0x00000700

/* APB2 Prescaler Options */
#define RCC_APB2_HCLK_PRESCALER_MASK     0xFFFFC7FF
#define RCC_APB2_HCLK_NOT_DIVIDED        0x00000000
#define RCC_APB2_HCLK_DIV_BY_2           0x00002000
#define RCC_APB2_HCLK_DIV_BY_4           0x00002800
#define RCC_APB2_HCLK_DIV_BY_8           0x00003000
#define RCC_APB2_HCLK_DIV_BY_16          0x00003800

/* PLL Multiplication Factor Options */
#define RCC_PLL_MUL_MASK				0xFFC3FFFF
#define RCC_PLL_MUL_BY_2				0x00000000
#define RCC_PLL_MUL_BY_3                0x00040000
#define RCC_PLL_MUL_BY_4                0x00080000
#define RCC_PLL_MUL_BY_5                0x000C0000
#define RCC_PLL_MUL_BY_6                0x00100000
#define RCC_PLL_MUL_BY_7                0x00140000
#define RCC_PLL_MUL_BY_8                0x00180000
#define RCC_PLL_MUL_BY_9                0x001C0000
#define RCC_PLL_MUL_BY_10               0x00200000
#define RCC_PLL_MUL_BY_11               0x00240000
#define RCC_PLL_MUL_BY_12               0x00280000
#define RCC_PLL_MUL_BY_13               0x002C0000
#define RCC_PLL_MUL_BY_14               0x00300000
#define RCC_PLL_MUL_BY_15               0x00340000
#define RCC_PLL_MUL_BY_16               0x00380000

/* Microcontroller Clock Output Options */
#define RCC_MCO_MASK                    0xF8FFFFFF
#define RCC_MCO_NO_CLK                  0x00000000
#define RCC_MCO_SYS_CLK                 0x04000000
#define RCC_MCO_HSI_CLK                 0x05000000
#define RCC_MCO_HSE_CLK                 0x06000000
#define RCC_MCO_PLL_DIV_BY_2_CLK        0x07000000

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            CONFIGURATION OPTIONS VALUES		       		         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
/* Available RCC Clock Enable Signals */
#define HSI_ON                         0U
#define HSE_ON                         1U
#define PLL_ON                         2U
#define HSI_AND_HSE_ON 	               3U
#define HSI_AND_PLLON 	               4U
#define HSE_AND_PLL_ON 	               5U
#define HSI_AND_HSE_AND_PLL_ON         6U

/* Available RCC System Clock Options */
#define HSI                            0U
#define HSE                            1U
#define PLL                            2U

/* RCC HSE Clock Options */
#define HSE_RC                         0U
#define HSE_CRYSTAL                    1U
#define HSE_CERAMIC                    2U

/* AHB Prescaler Options */
#define SYSCLK_NOT_DIVIDED             0U
#define SYSCLK_DIV_BY_2                2U
#define SYSCLK_DIV_BY_4                4U
#define SYSCLK_DIV_BY_8                8U
#define SYSCLK_DIV_BY_16               16U
#define SYSCLK_DIV_BY_64               64U
#define SYSCLK_DIV_BY_128              128U
#define SYSCLK_DIV_BY_256              256U
#define SYSCLK_DIV_BY_512 			   512U

/* APB1 & APB2 Prescaler Options */
#define HCLK_NOT_DIVIDED               0U
#define HCLK_DIV_BY_2                  2U
#define HCLK_DIV_BY_4                  4U
#define HCLK_DIV_BY_8                  8U
#define HCLK_DIV_BY_16                 16U

/* PLL Entry Clock Source Options */
#define PLL_HSI_DIV_BY_2               0U
#define PLL_HSE		                   1U

/* HSE Divider for PLL Entry Options */
#define PLL_DIV_FACTOR_HSE             0U
#define PLL_DIV_FACTOR_HSE_DIV_BY_2    1U

/* PLL Multiplication Factor Options */
#define PLL_MUL_BY_2                   2U
#define PLL_MUL_BY_3                   3U
#define PLL_MUL_BY_4                   4U
#define PLL_MUL_BY_5                   5U
#define PLL_MUL_BY_6                   6U
#define PLL_MUL_BY_7                   7U
#define PLL_MUL_BY_8                   8U
#define PLL_MUL_BY_9                   9U
#define PLL_MUL_BY_10                  10U
#define PLL_MUL_BY_11                  11U
#define PLL_MUL_BY_12                  12U
#define PLL_MUL_BY_13                  13U
#define PLL_MUL_BY_14                  14U
#define PLL_MUL_BY_15                  15U
#define PLL_MUL_BY_16                  16U

/* Microcontroller Output Clock Options */
#define MCO_NO_CLK                     0U
#define MCO_SYSCLK                     1U
#define MCO_HSI_CLK                    2U
#define MCO_HSE_CLK                    3U
#define MCO_PLL_DIV_BY_2_CLK           4U

#endif /* RCC_MCAL_PRIVATE_H_ */
