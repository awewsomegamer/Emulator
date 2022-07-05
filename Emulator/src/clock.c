#include <clock.h>
#include <interrupts.h>
#include <sys/time.h>

// Channel information
uint8_t channels[2];

// Measured in Hz
// 0: IRQ
// 1: Speaker
uint32_t channel_frequencies[2] = {1000, 0};
int8_t last_channel_zero = 0;

uint32_t last_millisecond = 0;

int last_channel = 0;

int j = 0;

time_t LAST_TIME;

void init_clock(){
	LAST_TIME = time(0);
}

void update_clock() {
	// 0b 00		00			000					0
	//    Channel
	//				Wave type
	//							Zero (temporarily)
	//												Enalbe

	// Channel: Which channel is being changed
	// Wave type: Sine wave, sawtooth wave, square wave -> Only squarewave
	// Enable: Clock should preform its action

	uint8_t data = inb(CLOCK_WRITE);

	// Make sure there is new data to write
	if (data != 0){
		channels[(data >> 6) & 3] = data;
		last_channel = ((data >> 6) & 3);
	}

	// Write new data

	uint32_t frequency = ind(CLOCK_DATA);
	
	// Make sure there is new frequency to write
	if (frequency != 0)
		channel_frequencies[last_channel] = frequency;
	
	
	// Mark as read
	outb(CLOCK_WRITE, 0);
	outd(CLOCK_DATA, 0);
}

void generate_clock_signal() {
	for (int i = 0; i < 2; i++) {
		switch (i) {
		case 0:
			printf("%d %d %d\n",current_ms - last_millisecond, current_ms, last_millisecond);

			if (current_ms - last_millisecond >= 3){
				call_interrupt(TIMER_INT);

				last_millisecond = current_ms;
			}

			break;
		
		case 1:
			if (channels[i] & 1 && channel_frequencies[i] > 0)
				play_frequency(channel_frequencies[i]);
			
			audio_enable(channels[i] & 1);

			break;
		}
	}
}
