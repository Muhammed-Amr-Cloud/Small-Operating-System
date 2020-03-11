/*
 * timer_lcfg.c
 *
 *  Created on: Nov 4, 2019
 *      Author: Mohamed
 */

#ifndef TIMER_LCFG_C_
#define TIMER_LCFG_C_

#include "timer_lcfg.h"

#define F_CPU 8000000UL

/*****************************************************************************************
 * 							CONFIGURATION STRUCTURE INIT								 *
 *****************************************************************************************/


timer_Confguration_s timer_Zero_Cfg = {	TIMER_ZERO, TIMER, 255 , INTERRUPT_ENABLE,8000000UL};


#endif /* TIMER_LCFG_C_ */
