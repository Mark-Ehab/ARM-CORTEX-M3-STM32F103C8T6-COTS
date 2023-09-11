/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 7, 2023               	*/
/*      			SWC          : NVIC  		                */
/*             	    Description	 : NVIC Private                 */
/* 	   	            Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*                       _   ___      _______ _____   _____      _            _                             */
/*                      | \ | \ \    / /_   _/ ____| |  __ \    (_)          | |                            */
/*                      |  \| |\ \  / /  | || |      | |__) | __ ___   ____ _| |_ ___                       */
/*                      | . ` | \ \/ /   | || |      |  ___/ '__| \ \ / / _` | __/ _ \                      */
/*                      | |\  |  \  /   _| || |____  | |   | |  | |\ V / (_| | ||  __/                      */
/*                      |_| \_|   \/   |_____\_____| |_|   |_|  |_| \_/ \__,_|\__\___|                      */
/*								                                         								    */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef MCAL_NVIC_PRIVATE_H_
#define MCAL_NVIC_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             NVIC REGISTERS DEFINITION		          		     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
typedef struct 
{
        volatile uint32_t ISER[3]; 		/* Interrupt set-enable registers */
        volatile uint32_t RESERVED0[29];        /* Reserved bits */
        volatile uint32_t ICER[3];         /* Interrupt clear-enable registers */
        volatile uint32_t RESERVED1[63];        /* Reserved bits */
        volatile uint32_t ISPR[3];         /* Interrupt set-pending registers */
        volatile uint32_t RESERVED2[29];        /* Reserved bits */
        volatile uint32_t ICPR[3];         /* Interrupt clear-pending registers */
        volatile uint32_t RESERVED3[29];        /* Reserved bits */
        volatile uint32_t IABR[3];         /* Interrupt active bit registers */
        volatile uint32_t RESERVED4[61];       	/* Reserved bits */
        volatile uint8_t  IPR[80];         /* Interrupt priority bytes */
        volatile uint32_t RESERVED5[695];       /* Reserved bits */
        volatile uint32_t STIR;            /* Software trigger interrupt register */
}NVIC_t;

#define NVIC  ((volatile NVIC_t*)0xE000E100)


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            CONFIGURATION OPTIONS VALUES		       		         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* NVIC Priority Grouping Options */
#define NVIC_G16S0                 0U
#define NVIC_G8S2                  1U
#define NVIC_G4S4                  2U
#define NVIC_G2S8                  3U
#define NVIC_G0S16                 4U

#endif /* MCAL_NVIC_PRIVATE_H_ */
