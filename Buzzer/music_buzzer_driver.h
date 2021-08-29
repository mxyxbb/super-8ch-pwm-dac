/*
 * buzzerDriver.h
 *
 *  Created on: Feb 22, 2019
 *      Author: lukasz
 */

#ifndef MUSIC_BUZZERDRIVER_H_
#define MUSIC_BUZZERDRIVER_H_

#define BUZZER_NUM 	8

typedef struct  
{
	uint8_t once_flag;
	uint16_t note_index;
	uint16_t os,os_next;
	float time_count;
} MUSIC_HandleTypeDef;

typedef struct {
  uint16_t freq; 
  int16_t value; 
	uint16_t phase;
	uint16_t phase_max;
	
} MIDI_HandleTypeDef;

void MXY_MUSIC_Init(MUSIC_HandleTypeDef* hmusic);
void buzzerDriverInit(void);
void setBuzzer(uint8_t channel, uint32_t newFreq);
void music_Play(uint8_t index);
void wave_gen(void);

extern MUSIC_HandleTypeDef hmusic1;
extern MUSIC_HandleTypeDef hmusic2;
extern MUSIC_HandleTypeDef hmusic3;

#endif /* BUZZERDRIVER_H_ */
