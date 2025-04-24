/*
 * reset.c
 *
 *  Created on: Apr 1, 2025
 *      Author: fbcks
 */


#include "reset.h"
#include "rtc.h"


static uint32_t reset_count = 0;


bool resetInit(void)
{
    bool ret = true;

    //if reset pin pressed
    if(RCC->CSR == (1 << 26))
    {
        rtcBackupRegWrite(1, rtcBackupRegRead(1) + 1);//increase 1
        delay(500);
        reset_count = rtcBackupRegRead(1);
    }
    rtcBackupRegWrite(1, 0);

    if(reset_count != 2)//부트로더를 호출하는 게 아니면 점프해라(reset 두번 누르면 부트로더 영역 진입)
    {
    	void (**jump_func)() = (void (**)())(0x8005000 + 4);

    	if((uint32_t)(*jump_func) != 0xFFFFFFFF)
    	{
    		HAL_RCC_DeInit();//펌웨어로 올라가기 전에 부트로더에 쓴 클럭이나 hal의 interrupt들을 끄는 것
    		HAL_DeInit();

    		for(int i = 0; i < 8; i++)
    		{
    			NVIC->ICER[i] = 0xFFFFFFFF;
    			__DSB();
    			__ISB();
    		}
    		SysTick->CTRL = 0;

    		(*jump_func)();
    	}
    }

    return ret;
}

uint32_t resetGetCount(void)
{


    return 0;
}
