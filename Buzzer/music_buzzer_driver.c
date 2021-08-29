/*
 * music_buzzer_driver.c
 *
 *  Created on: Aug 8, 2021
 *      Author: mxyxbb
 */
 
#include "dac.h"
#include "main.h"
#include "melody.h"
#include "music_buzzer_driver.h"
#include "music_Graze_the_Roof0.h"
//#include "music_headD0.h"
#include "music_omr.h"
//#include "music_Lemon.h"
//#include "music_palbg.h"
#include "music_pal1.h"
//#include "music_pal3_1.h"
//#include "music_the_internationale_PNO.h"
#include "music_hlxd.h"
#include "music_dlaam.h"
//#include "music_dshh.h"
//#include "music_qby.h"

#define CPU_FREQ	168000000
#define APB1_PRESCALER 	42
#define APB2_PRESCALER 	84
#define IT_FREQ 50000.f // 2 * freq of the interrupt

uint8_t buzzer_busy[BUZZER_NUM];
float buzzer_keep_time[BUZZER_NUM];

MUSIC_HandleTypeDef hmusic1;
MUSIC_HandleTypeDef hmusic2;
MUSIC_HandleTypeDef hmusic3;
MUSIC_HandleTypeDef hmusic4;
MUSIC_HandleTypeDef hmusic5;
MUSIC_HandleTypeDef hmusic6;
MUSIC_HandleTypeDef hmusic7;
MUSIC_HandleTypeDef hmusic8;
MUSIC_HandleTypeDef hmusic9;
MUSIC_HandleTypeDef hmusic10;
MUSIC_HandleTypeDef hmusic11;
MUSIC_HandleTypeDef hmusic12;
MUSIC_HandleTypeDef hmusic13;
MUSIC_HandleTypeDef hmusic14;
MUSIC_HandleTypeDef hmusic15;
MIDI_HandleTypeDef hmidi[BUZZER_NUM];
MIDI_HandleTypeDef hmidi1;



void MXY_MUSIC_Init(MUSIC_HandleTypeDef* hmusic)
{
	hmusic->once_flag = 0;
	hmusic->note_index = 0;
	hmusic->os = 0;
	hmusic->os_next = 0;
	hmusic->time_count = 0;
}

/*
 * Buzzer driver init (8,9,10,11,12,13,14)
 */

 #define USE_TIM4 //APB1 42MHz
 #define USE_TIM8 //APB2 84MHz
 #define USE_TIM9 //APB2 84MHz
 #define USE_TIM10 //APB2 84MHz
 #define USE_TIM11 //APB2 84MHz
 #define USE_TIM12 //APB1 42MHz
 #define USE_TIM13 //APB1 42MHz
 #define USE_TIM14 //APB1 42MHz

inline void buzzerDriverInit(void)
{
#ifdef USE_TIM4
	//Base Timer configuration:
	TIM4 -> CR1 &= ~(TIM_CR1_CKD_0 | TIM_CR1_CKD_1 | TIM_CR1_DIR);	// TIME x1 and DIR UP
	TIM4 -> CR1 |= TIM_CR1_ARPE;									// Auto reload
	TIM4 -> PSC = APB1_PRESCALER - 1;									// Prescaler
	TIM4 ->ARR = 60000;												// Period

	//Pulse
	TIM4 -> CCER &= ~TIM_CCER_CC4E;
	TIM4 -> CCER |= TIM_CCER_CC4P;

	TIM4 -> CCMR2 &= ~TIM_CR2_OIS4;
	TIM4 -> CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;

	TIM4 -> CR1 |= TIM_CR1_CEN;
	TIM4 ->CCER |= TIM_CCER_CC4E;
	//Set pulse
	TIM4 -> CCR1 = 60000/2;
#endif
#ifdef USE_TIM8
	//Base Timer configuration:
	TIM8 -> CR1 &= ~(TIM_CR1_CKD_0 | TIM_CR1_CKD_1 | TIM_CR1_DIR);	// TIME x1 and DIR UP
	TIM8 -> CR1 |= TIM_CR1_ARPE;									// Auto reload
	TIM8 -> PSC = APB2_PRESCALER - 1;									// Prescaler
	TIM8 ->ARR = 60000;												// Period

	//Pulse
	TIM8 -> CCER &= ~TIM_CCER_CC4E;
	TIM8 -> CCER |= TIM_CCER_CC4P;

	TIM8 -> CCMR2 &= ~TIM_CR2_OIS4;
	TIM8 -> CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;

	TIM8 -> CR1 |= TIM_CR1_CEN;
	TIM8 ->CCER |= TIM_CCER_CC4E;
	//Set pulse
	TIM8 -> CCR1 = 60000/2;
#endif
#ifdef USE_TIM9
	//Base Timer configuration:
	TIM9 -> CR1 &= ~(TIM_CR1_CKD_0 | TIM_CR1_CKD_1 | TIM_CR1_DIR);	// TIME x1 and DIR UP
	TIM9 -> CR1 |= TIM_CR1_ARPE;									// Auto reload
	TIM9 -> PSC = APB2_PRESCALER - 1;									// Prescaler
	TIM9 ->ARR = 60000;												// Period

	//Pulse
	TIM9 -> CCER &= ~TIM_CCER_CC4E;
	TIM9 -> CCER |= TIM_CCER_CC4P;

	TIM9 -> CCMR2 &= ~TIM_CR2_OIS4;
	TIM9 -> CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;

	TIM9 -> CR1 |= TIM_CR1_CEN;
	TIM9 ->CCER |= TIM_CCER_CC4E;
	//Set pulse
	TIM9 -> CCR1 = 60000/2;
#endif
#ifdef USE_TIM10
	//Base Timer configuration:
	TIM10-> CR1 &= ~(TIM_CR1_CKD_0 | TIM_CR1_CKD_1 | TIM_CR1_DIR);	// TIME x1 and DIR UP
	TIM10-> CR1 |= TIM_CR1_ARPE;									// Auto reload
	TIM10-> PSC = APB2_PRESCALER - 1;									// Prescaler
	TIM10->ARR = 60000;												// Period

	//Pulse
	TIM10-> CCER &= ~TIM_CCER_CC4E;
	TIM10-> CCER |= TIM_CCER_CC4P;

	TIM10-> CCMR2 &= ~TIM_CR2_OIS4;
	TIM10-> CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;

	TIM10 -> CR1 |= TIM_CR1_CEN;
	TIM10 ->CCER |= TIM_CCER_CC4E;
	//Set pulse
	TIM10-> CCR1 = 60000/2;
#endif
#ifdef USE_TIM11
	//Base Timer configuration:
	TIM11-> CR1 &= ~(TIM_CR1_CKD_0 | TIM_CR1_CKD_1 | TIM_CR1_DIR);	// TIME x1 and DIR UP
	TIM11-> CR1 |= TIM_CR1_ARPE;									// Auto reload
	TIM11-> PSC = APB2_PRESCALER - 1;									// Prescaler
	TIM11->ARR = 60000;												// Period

	//Pulse
	TIM11-> CCER &= ~TIM_CCER_CC4E;
	TIM11-> CCER |= TIM_CCER_CC4P;

	TIM11-> CCMR2 &= ~TIM_CR2_OIS4;
	TIM11-> CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;

	TIM11 -> CR1 |= TIM_CR1_CEN;
	TIM11 ->CCER |= TIM_CCER_CC4E;
	//Set pulse
	TIM11-> CCR1 = 60000/2;
#endif
#ifdef USE_TIM12
	//Base Timer configuration:
	TIM12 -> CR1 &= ~(TIM_CR1_CKD_0 | TIM_CR1_CKD_1 | TIM_CR1_DIR);	// TIME x1 and DIR UP
	TIM12 -> CR1 |= TIM_CR1_ARPE;									// Auto reload
	TIM12 -> PSC = APB1_PRESCALER - 1;									// Prescaler
	TIM12 ->ARR = 60000;												// Period

	//Pulse
	TIM12 -> CCER &= ~TIM_CCER_CC4E;
	TIM12 -> CCER |= TIM_CCER_CC4P;

	TIM12 -> CCMR2 &= ~TIM_CR2_OIS4;
	TIM12 -> CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;

	TIM12 -> CR1 |= TIM_CR1_CEN;
	TIM12 ->CCER |= TIM_CCER_CC4E;
	//Set pulse
	TIM12 -> CCR1 = 60000/2;
#endif
#ifdef USE_TIM13
	//Base Timer configuration:
	TIM13 -> CR1 &= ~(TIM_CR1_CKD_0 | TIM_CR1_CKD_1 | TIM_CR1_DIR);	// TIME x1 and DIR UP
	TIM13 -> CR1 |= TIM_CR1_ARPE;									// Auto reload
	TIM13 -> PSC = APB1_PRESCALER - 1;									// Prescaler
	TIM13 ->ARR = 60000;												// Period

	//Pulse
	TIM13 -> CCER &= ~TIM_CCER_CC4E;
	TIM13 -> CCER |= TIM_CCER_CC4P;

	TIM13 -> CCMR2 &= ~TIM_CR2_OIS4;
	TIM13 -> CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;

	TIM13 -> CR1 |= TIM_CR1_CEN;
	TIM13 ->CCER |= TIM_CCER_CC4E;
	//Set pulse
	TIM13 -> CCR1 = 60000/2;
#endif
#ifdef USE_TIM14
	//Base Timer configuration:
	TIM14 -> CR1 &= ~(TIM_CR1_CKD_0 | TIM_CR1_CKD_1 | TIM_CR1_DIR);	// TIME x1 and DIR UP
	TIM14 -> CR1 |= TIM_CR1_ARPE;									// Auto reload
	TIM14 -> PSC = APB1_PRESCALER - 1;									// Prescaler
	TIM14 ->ARR = 60000;												// Period

	//Pulse
	TIM14 -> CCER &= ~TIM_CCER_CC4E;
	TIM14 -> CCER |= TIM_CCER_CC4P;

	TIM14 -> CCMR2 &= ~TIM_CR2_OIS4;
	TIM14 -> CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;

	TIM14 -> CR1 |= TIM_CR1_CEN;
	TIM14 ->CCER |= TIM_CCER_CC4E;
	//Set pulse
	TIM14 -> CCR1 = 60000/2;
#endif
}

/*
 * 	Set new frequency
 *
 * 	args:
 * 	newFreq - new frequency in Hz.
 */
void buzzerSetNewFrequency1(uint32_t newFreq)
{
#if 1
	uint64_t tempFreq = newFreq;
	if(newFreq != 0){

	uint64_t tempNewValue = (uint64_t) 2000000 / tempFreq;

	// setting new value
	TIM9 ->ARR = (uint32_t)tempNewValue;
	TIM9 -> CCR1 = (uint32_t)tempNewValue/2;
	}
	else{
		TIM9 -> CCR1 = 0;
	}
#else
	freqs[0]=newFreq;
#endif
}
void buzzerSetNewFrequency2(uint32_t newFreq)
{
#if 1
	uint64_t tempFreq = newFreq;
	if(newFreq != 0){

	uint64_t tempNewValue = (uint64_t) 2000000 / tempFreq;

	// setting new value
	TIM12 ->ARR = (uint32_t)tempNewValue;
	TIM12 -> CCR1 = (uint32_t)tempNewValue/2;
	}
	else{
		TIM12 -> CCR1 = 0;
	}
#else
	freqs[1]=newFreq;
#endif
}
void buzzerSetNewFrequency3(uint32_t newFreq)
{
	uint64_t tempFreq = newFreq;
	if(newFreq != 0){

	uint64_t tempNewValue = (uint64_t) 2000000 / tempFreq;

	// setting new value
	TIM8 ->ARR = (uint32_t)tempNewValue;
	TIM8 -> CCR1 = (uint32_t)tempNewValue/2;
	}
	else{
		TIM8 -> CCR1 = 0;
	}
}
void buzzerSetNewFrequency4(uint32_t newFreq)
{
	uint64_t tempFreq = newFreq;
	if(newFreq != 0){

	uint64_t tempNewValue = (uint64_t) 2000000 / tempFreq;

	// setting new value
	TIM10 ->ARR = (uint32_t)tempNewValue;
	TIM10 -> CCR1 = (uint32_t)tempNewValue/2;
	}
	else{
		TIM10 -> CCR1 = 0;
	}
}
void buzzerSetNewFrequency5(uint32_t newFreq)
{
	uint64_t tempFreq = newFreq;
	if(newFreq != 0){

	uint64_t tempNewValue = (uint64_t) 2000000 / tempFreq;

	// setting new value
	TIM11 ->ARR = (uint32_t)tempNewValue;
	TIM11 -> CCR1 = (uint32_t)tempNewValue/2;
	}
	else{
		TIM11 -> CCR1 = 0;
	}
}
void buzzerSetNewFrequency6(uint32_t newFreq)
{
	uint64_t tempFreq = newFreq;
	if(newFreq != 0){

	uint64_t tempNewValue = (uint64_t) 2000000 / tempFreq;

	// setting new value
	TIM13 ->ARR = (uint32_t)tempNewValue;
	TIM13 -> CCR1 = (uint32_t)tempNewValue/2;
	}
	else{
		TIM13 -> CCR1 = 0;
	}
}
void buzzerSetNewFrequency7(uint32_t newFreq)
{
	uint64_t tempFreq = newFreq;
	if(newFreq != 0){

	uint64_t tempNewValue = (uint64_t) 2000000 / tempFreq;

	// setting new value
	TIM14 ->ARR = (uint32_t)tempNewValue;
	TIM14 -> CCR1 = (uint32_t)tempNewValue/2;
	}
	else{
		TIM14 -> CCR1 = 0;
	}
}
void buzzerSetNewFrequency8(uint32_t newFreq)
{
	uint64_t tempFreq = newFreq;
	if(newFreq != 0){

	uint64_t tempNewValue = (uint64_t) 2000000 / tempFreq;

	// setting new value
	TIM4 ->ARR = (uint32_t)tempNewValue;
	TIM4 -> CCR1 = (uint32_t)tempNewValue/2;
	}
	else{
		TIM4 -> CCR1 = 0;
	}
}
void setBuzzer(uint8_t channel, uint32_t newFreq)
{
#if 0
	switch (channel)
  {
  	case 0:
			buzzerSetNewFrequency1(newFreq);
  		break;
  	case 1:
  		buzzerSetNewFrequency2(newFreq);
  		break;
  	case 2:
  		buzzerSetNewFrequency3(newFreq);
  		break;
  	case 3:
  		buzzerSetNewFrequency4(newFreq);
  		break;
  	case 4:
  		buzzerSetNewFrequency5(newFreq);
  		break;
  	case 5:
  		buzzerSetNewFrequency6(newFreq);
  		break;
  	case 6:
  		buzzerSetNewFrequency7(newFreq);
  		break;
  	case 7:
  		buzzerSetNewFrequency8(newFreq);
  		break;
  	default:
  		break;
  }
#else
	hmidi[channel].freq=newFreq;
//	freq2[channel]=newFreq+newFreq;
#endif
}
//void musicPlay()
//{
//	__ExecuteOnce(buzzerDriverInit());

//  TIM9 -> CR1 |= TIM_CR1_CEN;
//  TIM9 ->CCER |= TIM_CCER_CC4E;

//  int melodyCount = sizeof(melodySizes)/ sizeof(uint32_t);

//  for(int melodyIndex = 0; melodyIndex < melodyCount; melodyIndex++)
//  {
//	  for(int noteIndex = 0; noteIndex < melodySizes[melodyIndex]; noteIndex++)
//  	  {
//	  	  buzzerSetNewFrequency(melody[melodyIndex][noteIndex]);
//	  	  HAL_Delay(noteDurations[melodyIndex][noteIndex] * melodySlowfactor[melodyIndex]);
//  	  }
//  }
//   TIM9 -> CR1 &= ~TIM_CR1_CEN;
//   TIM9 ->CCER &= ~TIM_CCER_CC4E;
//}
float float_abs(float i)
{
	if(i >= 0)
		return i;
	else
		return -i;
}
void buzzertick()
{
	for(uint8_t i=0;i<BUZZER_NUM;i++)
	{
		if (buzzer_busy[i] == 1)
		{
			buzzer_keep_time[i] = buzzer_keep_time[i] - 0.012f;
		}
		if (float_abs(buzzer_keep_time[i]) < 0.012f)
		{
			buzzer_busy[i] = 0;
			buzzer_keep_time[i] = 0;
			setBuzzer(i,0);
		}
	}

}

//·Ç¶ÂÈû
void buzzerPlay(uint16_t* note,uint16_t dura) 
{
//	for(uint16_t i=0;i<omr_len;i++) //0 - 1530
	for(uint8_t j=0;note[j]!=0 && j<BUZZER_NUM;j++) //0 - 7 every note
		for(uint8_t k=0;k<BUZZER_NUM;k++) //0 - 7 search idle buzzer
			if(buzzer_busy[k] == 0) 
			{
				buzzer_busy[k] = 1; // set busy flag
				buzzer_keep_time[k] = dura; // set duration time(the durations of i^th notes are the same
				setBuzzer(k,note[j]);
				break;
			}
}


/*
---example---
MUSIC_HandleTypeDef hmusic1;
musicPlay(&hmusic1,omr_note,omr_notedura,omr_noteos,omr_notelen);
-------------
*/
void _musicPlay(MUSIC_HandleTypeDef* hmusic ,
							uint16_t (*_note)[BUZZER_NUM],
							uint16_t* _notedura,
							uint16_t* _noteos,
							uint16_t notelen)
{
	if(!hmusic->once_flag)
	{
		hmusic->once_flag = 1;
		hmusic->os = _noteos[0];
		hmusic->os_next = _noteos[1];
		buzzerPlay(_note[hmusic->note_index], _notedura[hmusic->note_index]);
	}
	if(float_abs(hmusic->time_count-(float)(hmusic->os_next)) < 0.012f)
	{
		hmusic->note_index = hmusic->note_index + 1;
		hmusic->os = _noteos[hmusic->note_index];
		hmusic->os_next = _noteos[hmusic->note_index+1];
		buzzerPlay(_note[hmusic->note_index], _notedura[hmusic->note_index]);
		while(hmusic->os == hmusic->os_next)
		{
			hmusic->note_index = hmusic->note_index + 1;
			hmusic->os = _noteos[hmusic->note_index];
			hmusic->os_next = _noteos[hmusic->note_index+1];
			buzzerPlay(_note[hmusic->note_index], _notedura[hmusic->note_index]);
		}
	}
	buzzertick();
	hmusic->time_count += 0.012f;	
	if(hmusic->note_index>= notelen-10)
		MXY_MUSIC_Init(hmusic);
}

void music_Play(uint8_t index)
{

	switch (index)
  {
  	case 0:
			_musicPlay(&hmusic1,omr_note,omr_notedura,omr_noteos,omr_len);
  		break;
  	case 1:
			_musicPlay(&hmusic2,Graze_the_Roof_note,Graze_the_Roof_notedura,Graze_the_Roof_noteos,Graze_the_Roof_len);
  		break;
  	case 2:
//			_musicPlay(&hmusic3,headD_note,headD_notedura,headD_noteos,headD_len);
  		break;
  	case 3:
//			_musicPlay(&hmusic4,Lemon_note,Lemon_notedura,Lemon_noteos,Lemon_len);
  		break;
  	case 4:
//			_musicPlay(&hmusic5,palbg_note,palbg_notedura,palbg_noteos,palbg_len);
  		break;
  	case 5:
			_musicPlay(&hmusic6,pal1_note,pal1_notedura,pal1_noteos,pal1_len);
  		break;
  	case 6:
//			_musicPlay(&hmusic7,pal3_1_note,pal3_1_notedura,pal3_1_noteos,pal3_1_len);
  		break;
  	case 7:
//			_musicPlay(&hmusic8,pal4_1_note,pal4_1_notedura,pal4_1_noteos,pal4_1_len);
  		break;
  	case 8:
//			_musicPlay(&hmusic9,the_internationale_PNO_note,the_internationale_PNO_notedura,the_internationale_PNO_noteos,the_internationale_PNO_len);
  		break;
  	case 9:
//			_musicPlay(&hmusic10,xiatiandefeng_note,xiatiandefeng_notedura,xiatiandefeng_noteos,xiatiandefeng_len);
  		break;
  	case 10:
//			_musicPlay(&hmusic11,qby_note,qby_notedura,qby_noteos,qby_len);
			break;
  	case 11:
//  		_musicPlay(&hmusic12,dshh_note,dshh_notedura,dshh_noteos,dshh_len);
  		break;
  	case 12:
			_musicPlay(&hmusic13,hlxd_note,hlxd_notedura,hlxd_noteos,hlxd_len);
  		break;
  	case 13:
//			_musicPlay(&hmusic14,tkzc_note,tkzc_notedura,tkzc_noteos,tkzc_len);
  		break;
  	case 14:
			_musicPlay(&hmusic15,dlaam_note,dlaam_notedura,dlaam_noteos,dlaam_len);
  		break;
  	default:
  		break;
  }
}

void square_cal(MIDI_HandleTypeDef* hmidi, uint16_t num, float duty)
{
	uint16_t temp[BUZZER_NUM];

	for(uint8_t i=0;i<num;i++)
	{
		if(hmidi[i].freq)
		{	
			temp[i] = (uint16_t)(IT_FREQ/hmidi[i].freq);//note;
			
			hmidi[i].phase++;
			if(hmidi[i].phase>=hmidi[i].phase_max) {
				hmidi[i].phase_max=temp[i];			
				hmidi[i].phase=0;
			}
			if(hmidi[i].phase<hmidi[i].phase_max*duty) hmidi[i].value=100;
			else hmidi[i].value=-100;
		}
		else
		{
			hmidi[i].phase=0xfff0;
			hmidi[i].value=-100;
		}
	}
}

void int16_sum(MIDI_HandleTypeDef* hmidi, int16_t alen, int16_t* result)
{
	for(uint16_t i=0;i<alen;i++)
	{
		*result += hmidi[i].value;
	}
}

void wave_gen()
{
	int16_t out=0;
	square_cal(hmidi, BUZZER_NUM, 0.5f);
	int16_sum(hmidi, BUZZER_NUM, &out);
//	drumGenerator(&ch1);
//	int16_sum(&hmidi1, 1, &out);
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (uint32_t)(out+2000));
}


