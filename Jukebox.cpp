/*************************************************************
 * Jukebox - a simple class to play WAV files
 * g++ Jukebox.cpp `sdl-config --cflags --libs`  -lSDL_mixer
 * ./a.out sounds/AHH.WAV
 *************************************************************/

#include "Jukebox.h"
#include <cstdio>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <mba/msgno.h>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>

#define NUM_SOUNDS 5

struct sample {
    Uint8 *data;
    Uint32 dpos;
    Uint32 dlen;
} sounds[NUM_SOUNDS];

void Jukebox::mixaudio(void *unused, Uint8 *stream, int len)
{
	int i;
	Uint32 amount;
	for (i = 0; i < NUM_SOUNDS; i++) {
		amount = (sounds[i].dlen-sounds[i].dpos);
		if (amount > (Uint32)len) {
			amount = len;
		}
		SDL_MixAudio(stream, &sounds[i].data[sounds[i].dpos], amount, SDL_MIX_MAXVOLUME);
		sounds[i].dpos += amount;
	}
	(void)unused;
}

void Jukebox::PlaySound(const char *file)
{
	int index;
	SDL_AudioSpec wave;
	Uint8 *data;
	Uint32 dlen;
	SDL_AudioCVT cvt;

	/* Look for an empty (or finished) sound slot */
	for ( index=0; index<NUM_SOUNDS; ++index ) {
		if ( sounds[index].dpos == sounds[index].dlen ) {
			break;
		}
	}
	if ( index == NUM_SOUNDS )
		return;

	/* Load the sound file and convert it to 16-bit stereo at 22kHz */
	if ( SDL_LoadWAV(file, &wave, &data, &dlen) == NULL ) {
		fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
		return;
	}
	SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq, AUDIO_S16, 2, 22050);
    cvt.buf = (Uint8*)malloc(dlen*cvt.len_mult);
	memcpy(cvt.buf, data, dlen);
	cvt.len = dlen;
	SDL_ConvertAudio(&cvt);
	SDL_FreeWAV(data);

	/* Put the sound data in the slot (it starts playing immediately) */
	if (sounds[index].data) {
		free(sounds[index].data);
	}
	SDL_LockAudio();
	sounds[index].data = cvt.buf;
	sounds[index].dlen = cvt.len_cvt;
	sounds[index].dpos = 0;
	SDL_UnlockAudio();
}

bool Jukebox::init()
{
    SDL_AudioSpec fmt;
	/* Set 16-bit stereo audio at 22Khz */
	fmt.freq = 22050;
	fmt.format = AUDIO_S16;
	fmt.channels = 2;
	fmt.samples = 512;        /* A good value for games */
	fmt.callback = Jukebox::mixaudio;
	fmt.userdata = NULL;
	/* Open the audio device. */
	if (SDL_OpenAudio(&fmt, NULL) < 0) {
        printf("Unable to open audio: %s\n", SDL_GetError());
        return false;
		//MMSG("Unable to open audio: %s\n", SDL_GetError());
		//return EXIT_FAILURE;
	}
    /* Start playing sound! */
	SDL_PauseAudio(0);
    return true;
}

/*
int main(int argc, char *argv[])
{
   if(!Jukebox::init())
      exit;



	for (int i = 1; i < argc; i++) {
		fprintf(stderr, "%s", argv[i]);
		Jukebox::PlaySound(argv[i]);


sleep(2);
	}

	SDL_CloseAudio();

	return EXIT_SUCCESS;
}
*/
