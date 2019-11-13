// Wrapper Library for OpenAL
// Author: M.D.Snellgrove
// Date: 17/3/2002
// History:

// Changes by M Snellgrove 26/7/2003
//   Conditional Compilation using OpenAL

// Changes by Judebert 1/8/2003
//   Portability fix for WIN32 systems

// Changes by M Snellgrove 5/8/2003
//   Code cleanup

#include "sampleio.h"

#include <SDL.h>

// Empty Noaudio sound routines
#if AP_AUDIO==AUDIO_NOAUDIO

sampleio :: sampleio(){}
void sampleio :: init(int, char [][255], int, int){}
void sampleio :: close(){}
void sampleio :: update(){}
void sampleio :: channel(int, int){}
void sampleio :: loop(int, int){}
void sampleio :: play(int){}
void sampleio :: stop(int){}
void sampleio :: psource(int, int, bool){}
void sampleio :: volume(int, double){}
ALboolean sampleio :: sourceisplaying(ALuint){return false;}

#endif

// OpenAL sound routines
#if AP_AUDIO==AUDIO_OPENAL

// taken from mojoal example code
static ALenum get_openal_format(const SDL_AudioSpec *spec)
{
    if ((spec->channels == 1) && (spec->format == AUDIO_U8)) {
        return AL_FORMAT_MONO8;
    } else if ((spec->channels == 1) && (spec->format == AUDIO_S16SYS)) {
        return AL_FORMAT_MONO16;
    } else if ((spec->channels == 2) && (spec->format == AUDIO_U8)) {
        return AL_FORMAT_STEREO8;
    } else if ((spec->channels == 2) && (spec->format == AUDIO_S16SYS)) {
        return AL_FORMAT_STEREO16;
    } else if ((spec->channels == 1) && (spec->format == AUDIO_F32SYS)) {
        return alIsExtensionPresent("AL_EXT_FLOAT32") ? alGetEnumValue("AL_FORMAT_MONO_FLOAT32") : AL_NONE;
    } else if ((spec->channels == 2) && (spec->format == AUDIO_F32SYS)) {
        return alIsExtensionPresent("AL_EXT_FLOAT32") ? alGetEnumValue("AL_FORMAT_STEREO_FLOAT32") : AL_NONE;
    }
    return AL_NONE;
}

// Constructor

sampleio :: sampleio(){

  initdone = false;

}

// Initialize OpenAL

void sampleio :: init(int nsamples, char filenames[][255], int nsources,
                      int npool){
  if (initdone){
    cerr << "sampleio: call to init when already in use" << endl;
    exit(1);
  }

  initdone = true;
  numsamples = nsamples;
  numsources = nsources;
  numpool = npool;
  samples = new ALuint[numsamples];
  sources = new ALuint[numsources+numpool];
  poolcount = numsources;

  // Initialize audio device
  openal_device = alcOpenDevice(NULL);
  if (!openal_device) {
    cerr << "sampleio: error opening openal default device!\n";
    exit(1);
  }

  openal_context = alcCreateContext(openal_device, NULL);
  if (!openal_context) {
    cerr << "sampleio: could not create openal context!\n";
    alcCloseDevice(openal_device);
    exit(1);
  }

  alcMakeContextCurrent(openal_context);

  ALfloat zeroes[] = { 0.0f, 0.0f,  0.0f };
  ALfloat back[]   = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
  ALfloat front[]  = { 0.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f };
  ALfloat position[] = { 0.0f, 0.0f, -4.0f };

  // Setup Listener
  alListenerfv(AL_POSITION, zeroes);
  alListenerfv(AL_VELOCITY, zeroes);
  alListenerfv(AL_ORIENTATION, front);

  // Load in samples
  alGenBuffers(numsamples, samples);
  for (int i = 0; i < numsamples; i++){
    SDL_AudioSpec spec;
    Uint8 *buf = NULL;
    Uint32 buflen = 0;
    if (!SDL_LoadWAV(filenames[i], &spec, &buf, &buflen)) {
      cerr << "sampleio: could not open " << filenames[i] << ": " << SDL_GetError() << endl;
      exit(1);
    }

    ALenum alfmt = AL_NONE;
    if ((alfmt = get_openal_format(&spec)) == AL_NONE) {
      //printf("Can't queue '%s', format not supported by the AL.\n", fname);
      cerr << "sampleio: could not open " << filenames[i] << ", format not supported by the al.\n";
      SDL_FreeWAV(buf);
      exit(1);
    }

    alBufferData(samples[i], alfmt, buf, buflen, spec.freq);

    SDL_FreeWAV(buf);
  }

  // Generate Sources
  alGenSources(numsources+numpool, sources);

  for(int j=0;j<numsources+numpool;j++){
    alSourcefv(sources[j], AL_POSITION, position );
    alSourcefv(sources[j], AL_VELOCITY, zeroes );
    alSourcefv(sources[j], AL_ORIENTATION, back );
  }

}

// Clearup routine

void sampleio :: close(){

  if (initdone){
    delete [] samples;
    delete [] sources;
    initdone = false;
    alcMakeContextCurrent(NULL);
    alcDestroyContext(openal_context);
    alcCloseDevice(openal_device);
  }

}

// Update method (blank)

void sampleio :: update(){

}

// Play a channel

void sampleio :: channel(int chan, int sample){
  if (!initdone){
    cerr << "sampleio: initialize before use" << endl;
    return;
  }
  if ((chan < 0) || (chan >= numsources)){
    cerr << "sampleio: attempt to play nonexistant source " << chan
         << endl;
    return;
  }
  if ((sample < 0) || (sample >= numsamples)){
    cerr << "sampleio: attempt to play nonexistant sample " << sample
         << endl;
    return;
  }

  psource(chan, sample, false);
}

// Loop a sample

void sampleio :: loop(int chan, int sample){

  if (!initdone){
    cerr << "sampleio: initialize before use" << endl;
    return;
  }
  if ((chan < 0) || (chan >= numsources)){
    cerr << "sampleio: attempt to play nonexistant source " << chan
         << endl;
    return;
  }
  if ((sample < 0) || (sample >= numsamples)){
    cerr << "sampleio: attempt to play nonexistant sample " << sample
         << endl;
    return;
  }
  psource(chan, sample, true);

}

// Play a sample

void sampleio :: play(int sample){

  if (!initdone){
    cerr << "sampleio: initialize before use" << endl;
    return;
  }
  if (numpool == 0){
    cerr << "sampleio: attempt to play nonexistant pool " << endl;
    return;
  }
  if ((sample < 0) || (sample >= numsamples)){
    cerr << "sampleio: attempt to play nonexistant sample " << sample
         << endl;
    return;
  }
  poolcount++;
  if (poolcount == numsources + numpool) poolcount = numsources;
  psource(poolcount, sample, false);

}

// Stop current sample

void sampleio :: stop(int i){

  if (!initdone){
    cerr << "sampleio: initialize before use" << endl;
    return;
  }
  if ((i < 0) || (i >= numsources)){
    cerr << "sampleio: attempt to stop nonexistant source " << i
         << endl;
    return;
  }
  if (sourceisplaying(sources[i])){
    alSourceStop(sources[i]);
  }

}

// Actaully start a sample

void sampleio :: psource(int i, int sample, bool loop){

  // Stop current sample
  if (sourceisplaying(sources[i])){
    alSourceStop(sources[i]);
  }

  // Change to new sample
  alSourcei(sources[i], AL_BUFFER, samples[sample]);
  if (loop){
    alSourcei(sources[i], AL_LOOPING, AL_TRUE);
  }else{
    alSourcei(sources[i], AL_LOOPING, AL_FALSE);
  }

  // Play new sample
  alSourcePlay(sources[i]);

}

// Volume control function

void sampleio :: volume(int i, double vol){

  if (!initdone){
    cerr << "sampleio: initialize before use" << endl;
    return;
  }
  if ((i < 0) || (i >= numsources)){
    cerr << "sampleio: attempt to volume nonexistant source " << i
         << endl;
    return;
  }
  ALfloat volf = ALfloat(vol);
  alSourcef(sources[i], AL_GAIN, volf);

}

// Check on playing sources function

ALboolean sampleio ::  sourceisplaying(ALuint sid) {

  ALint state;
  if(alIsSource(sid) == AL_FALSE){
    return AL_FALSE;
  }
  state = AL_INITIAL;

  alGetSourcei(sid, AL_SOURCE_STATE, &state);

  switch(state) {
    case AL_PLAYING: case AL_PAUSED:
      return AL_TRUE;
    default:
      break;
  }
  return AL_FALSE;

}

#endif

