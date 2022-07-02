#include <clock.h>
#include <interrupts.h>

// Channel information
uint8_t channels[2];

// Measured in Hz
// 0: IRQ
// 1: Speaker
uint32_t channel_frequencies[2] = {11981, 0};

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
	if (data == 0)
		return;

	channels[(data >> 6) & 3] = data;

	// Write new data

	uint32_t frequency = ind(CLOCK_DATA);
	
	// Make sure there is new frequency to write
	if (frequency == 0)
		return;

	channel_frequencies[(data >> 6) & 3] = frequency;

	// Mark as read
	outb(CLOCK_WRITE, 0);
	outd(CLOCK_DATA, 0);
}

void generate_clock_signal() {
	bool did_signal = false;

	for (int i = 0; i < 2; i++) {
		if (ticks % channel_frequencies[i] != 0)
			i++;

		switch (i) {
		case 0:
			call_interrupt(TIMER_INT);

			break;
		
		case 1:
			if (channels[i] & 1)
				play_frequency(channel_frequencies[i]);
			
			audio_enable(channels[i] & 1);

			break;
		}

		did_signal = true;
	}

	if (did_signal)
		ticks = 0;
}
