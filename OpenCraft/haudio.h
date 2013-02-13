#ifndef __HAUDIO_H
#define __HAUDIO_H
#include "stdsct.h"

struct haudio
{
	uint32_t buffer;
	uint32_t source;
};

enum audioerr
{
	AUDIO_NO_ERR = 0,
	AUDIO_ERR_FILE,
	AUDIO_ERR_NO_RIFF,
	AUDIO_ERR_NO_WAVE,
	AUDIO_ERR_NO_FMT,
	AUDIO_ERR_NOT_PCM,
	AUDIO_ERR_NO_DATA
};

void Audio_Init(void);
void Audio_Quit(void);
struct haudio *Audio_NewHandle(void);
enum audioerr Audio_LoadWAV(struct haudio *handle, const char *wavfile);
void Audio_Play(struct haudio *handle);
void Audio_Pause(struct haudio *handle);
void Audio_Stop(struct haudio *handle);
bool_t Audio_GetPaused(struct haudio *handle);
void Audio_Free(struct haudio *handle);




#endif//__HAUDIO_H