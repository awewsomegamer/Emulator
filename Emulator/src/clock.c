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
	// bool did_signal = false;

	struct timeval te;
	gettimeofday(&te, NULL);
	uint32_t current_ms = te.tv_sec * 1000 + te.tv_usec / 1000;

	for (int i = 0; i < 2; i++) {
		switch (i) {
		case 0:
			// int period = 48000 / channel_frequencies[i];
			// int8_t wave = ((ticks / (period / 2) % 2) ? 1 : 0);
			
			// int8_t wave = (int8_t)((sin(channel_frequencies[0] * (ticks++ / ((1600) / channel_frequencies[0])))) >= 0 ? 1 : -0);

			// if (wave && !last_channel_zero){
			// 	j++;
			// 	call_interrupt(TIMER_INT);
			// }
			
			if (current_ms - last_millisecond == 1){
				call_interrupt(TIMER_INT);
				j++;
			}

			// int8_t wave = (int8_t)sin(ticks) > 0 ? 1 : 0;

			// last_channel_zero = wave;

			break;
		
		case 1:
			if (channels[i] & 1 && channel_frequencies[i] > 0)
				play_frequency(channel_frequencies[i]);
			
			audio_enable(channels[i] & 1);

			break;
		}

		// did_signal = true;
	}
	
	last_millisecond = current_ms;

	if (time(0) == LAST_TIME + 1){
		printf("%d CLOCK INTERRUPTS / SECOND\n", j);
		j = 0;
		LAST_TIME = time(0);
	}

	// if (did_signal)
	// 	ticks = 0;
}
