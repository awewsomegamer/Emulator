#include <audio.h>
#include <SDL2/SDL_audio.h>

// bool playing = false;

// int SamplesPerSecond = 48000;
// int16_t ToneVolume = 3000;
// uint32_t RunningSampleIndex = 0;
// int BytesPerSample = sizeof(int16_t) * 2;

// void play_frequency(int frequecny){

// 	if (!playing){
// 		int SquareWavePeriod = SamplesPerSecond / frequecny;
// 		int HalfSquareWavePeriod = SquareWavePeriod / 2;
// 		int BytesToWrite = 800 * BytesPerSample;
		
// 		void* SoundBuffer = malloc(BytesToWrite);
// 		int16_t* SampleOut = (int16_t*) SoundBuffer;
// 		int SampleCount = BytesToWrite/BytesPerSample;

// 		for (int i = 0; i < SampleCount; i++){
// 			int64_t v = ((RunningSampleIndex++ / HalfSquareWavePeriod) % 2) ? ToneVolume : -ToneVolume;
// 			*SampleOut++ = v;
// 			*SampleOut++ = v;
// 		}

// 		SDL_QueueAudio(1, SoundBuffer, BytesToWrite);
// 		free(SoundBuffer);

// 		SDL_PauseAudio(0);

// 		playing = true;
// 	}
// }

// void play_stop(){
// 	SDL_PauseAudio(1);
// 	playing = false;
// }


