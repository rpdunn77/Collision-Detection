#ifndef Jukebox_H_
#define Jukebox_H_

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>

class Jukebox {
   private: 
     static void mixaudio(void *unused, Uint8 *stream, int len);
   
   public:
     // The init function to set up the audio. Call this once.
     static bool init();
     // Play a sound.
     static void PlaySound(const char *file);
};

#endif /* Jukebox_H_ */
