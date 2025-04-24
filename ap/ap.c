/*
 * ap.c
 *
 *  Created on: Mar 25, 2025
 *      Author: fbcks
 */


#include "ap.h"


void apInit(void)
{

}

void apMain(void)
{
    uint32_t prev_time;

    prev_time = millis();

	while(1)
	{
	    if(millis() - prev_time >= 100)//부트로더인 걸 확인하기 위해 100으로 줄임
	    {
	        prev_time = millis();
	        ledToggle(_DEF_LED1);
	    }
	}
}
