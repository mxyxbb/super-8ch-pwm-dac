#include "tim.h"
#include "music_buzzer_driver.h"
#include "cpost.h"
#include "control_task.h"
#include "dac.h"



uint8_t key;
uint8_t count1,count2;



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == (&htim6))//ÖÐ¶ÏÆµÂÊÎª25kHz
    {
			count1++;
			wave_gen();
			if(count1>25)//1ms
			{
				music_Play(14);
				count1=0;
			}	

//				testfunc();


		}
}
