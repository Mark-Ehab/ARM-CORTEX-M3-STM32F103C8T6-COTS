/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 17, 2021               	*/
/*             		Description	 : Standard Types               */
/* 	        		Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						  _____ _______ _____    _________     _______  ______  _____                       */
/*						 / ____|__   __|  __ \  |__   __\ \   / /  __ \|  ____|/ ____|                      */
/*						| (___    | |  | |  | |    | |   \ \_/ /| |__) | |__  | (___                        */
/*						 \___ \   | |  | |  | |    | |    \   / |  ___/|  __|  \___ \                       */
/*						 ____) |  | |  | |__| |    | |     | |  | |    | |____ ____) |                      */
/*						|_____/   |_|  |_____/     |_|     |_|  |_|    |______|_____/                       */
/*						                                                                                    */
/*						                                                                                    */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef LIB_STD_TYPES_H_
#define LIB_STD_TYPES_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              STANDARD TYPES DEFINITION		           		     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
typedef unsigned char 			uint8_t;
typedef signed char 			sint8_t;
typedef unsigned short int 		uint16_t;
typedef signed short int 		sint16_t;
typedef unsigned long int 		uint32_t;
typedef signed long int 		sint32_t;
typedef float 					float32_t;
typedef double 					float64_t;
typedef long double 			float128_t;

/* Define NULL as 0 */
#define NULL  			0U

#endif /* LIB_STD_TYPES_H_ */
