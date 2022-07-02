#include <audio.h>

int next_sample = 0;

void play_frequency(int frequency){
	for (int i = 0; i < 4800; i++) {
		int period = 48000 / frequency;
		int8_t sample = ((next_sample++ / (period / 2) % 2) ? 2 : -2);

		SDL_QueueAudio(audio_device, &sample, sizeof(int8_t));
	}	
}

void audio_enable(bool enable){
	SDL_PauseAudioDevice(audio_device, !enable);
}
