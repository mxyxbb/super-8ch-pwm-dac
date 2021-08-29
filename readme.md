# super buzzer music lib

**This lib can play some MIDI music.**

**Output method:** 8 channel pwm in 1 channel dac

**Platform:** STM32F407VE, HAL Lib

First choose the midi music that you enjoy and download it, then you'll get `xxx.mid`.

Then, use this [mxyxbb/python-midi-to-c: 将midi文件转换为适合c语言处理的数组文件 (github.com)](https://github.com/mxyxbb/python-midi-to-c)

 to convert the `xxx.mid`, you will get `music_xxx.h`

just place the file `music_xxx.h` under the path `\super-8ch-pwm&dac\Buzzer`

then include `music_xxx.h` in the `music_buzzer_driver.c`

then adjust the function `void music_Play(uint8_t index)`

The preparation is finished.

Next, run the function `void wave_gen()` at a freq of 25kHz,

and run the function `void music_Play(uint8_t index)` at a freq of 1kHz.

Finally the wave will output at PA4 by default.

Ps: 

1. if you want to run `void wave_gen()` at a different freq, remember to adjust the DEFINE of `IT_FREQ `at the file `music_buzzer_driver.c` according the commit.
2. you can change the `#if 0` into `#if 1` in the function `void setBuzzer(uint8_t channel, uint32_t newFreq)` to enable the PWM output method. In this method, remember to initialize the PWM peripheral.

