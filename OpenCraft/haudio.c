#include "haudio.h"
#include <stdlib.h>
#include <stdio.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#define AUDIO_EXIT_ERR(err) if(file) {fclose(file); return err;}

static ALCdevice *device = NULL;
static ALCcontext *context = NULL;

static bool_t cmp4b(uint8_t *a, uint8_t *b)
{
	if(a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3])
		return TRUE;
	return FALSE;
}

void Audio_Init(void)
{
	device = alcOpenDevice(NULL);
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
}

void Audio_Quit(void)
{
	alcDestroyContext(context);
	alcCloseDevice(device);
	alcMakeContextCurrent(NULL);
}

struct haudio *Audio_NewHandle(void)
{
	struct haudio *tmp;

	tmp = malloc(sizeof(struct haudio));
	alGenBuffers(1, &tmp->buffer);
	alGenSources(1, &tmp->source);
	alSourcef(tmp->source, AL_GAIN, 1.0f);
	alSourcei(tmp->source, AL_LOOPING, TRUE);
	return tmp;
}

enum audioerr Audio_LoadWAV(struct haudio *handle, const char *wavfile)
{
	FILE *file;
	unsigned char id[4];
	uint16_t format, channels, bps; //bits per sample
	uint32_t samplerate, datasize;
	void *data;
	ALenum bformat;

	file = fopen(wavfile, "rb");
	if(!file) return AUDIO_ERR_FILE;

	fread(id, 1, 4, file);
	if(!cmp4b(id, "RIFF")) AUDIO_EXIT_ERR(AUDIO_ERR_NO_RIFF)

	fseek(file, 4, SEEK_CUR);
	fread(id, 1, 4, file);
	if(!cmp4b(id, "WAVE")) AUDIO_EXIT_ERR(AUDIO_ERR_NO_WAVE)

	fread(id, 1, 4, file);
	if(!cmp4b(id, "fmt ")) AUDIO_EXIT_ERR(AUDIO_ERR_NO_FMT)

	fseek(file, 4, SEEK_CUR);
	fread(&format, 2, 1, file);
	if(format != 1) AUDIO_EXIT_ERR(AUDIO_ERR_NOT_PCM)

	fread(&channels, 2, 1, file); //NumChannels
	fread(&samplerate, 4, 1, file); //SampleRate
	fseek(file, 6, SEEK_CUR);
	fread(&bps, 2, 1, file); //BitsPerSample

	fread(id, 1, 4, file);
	if(!cmp4b(id, "data")) AUDIO_EXIT_ERR(AUDIO_ERR_NO_DATA)

	fread(&datasize, 4, 1, file); //DataSize

	data = malloc((bps / 8) * datasize);
	fread(data, bps / 8, datasize, file);
	if(channels == 1)
	{
		if(bps == 8) bformat = AL_FORMAT_MONO8;
		else if(bps == 16) bformat = AL_FORMAT_MONO16;
	}
	else if(channels == 2)
	{
		if(bps == 8) bformat = AL_FORMAT_STEREO8;
		else if(bps == 16) bformat = AL_FORMAT_STEREO16;
	}
	alBufferData(handle->buffer, bformat, data, datasize, samplerate);
	alSourcei(handle->source, AL_BUFFER, handle->buffer);

	free(data);
	fclose(file);
	return AUDIO_NO_ERR;
}

void Audio_Play(struct haudio *handle)
{
	alSourcePlay(handle->source);
}

void Audio_Pause(struct haudio *handle)
{
	alSourcePause(handle->source);
}

void Audio_Stop(struct haudio *handle)
{
	alSourceStop(handle->source);
}

bool_t Audio_GetPaused(struct haudio *handle)
{
	int32_t val;

	alGetSourcei(handle->source, AL_PAUSED, &val);
	return val;
}

void Audio_Free(struct haudio *handle)
{
	alDeleteBuffers(1, &handle->buffer);
	alDeleteSources(1, &handle->source);
	free(handle);
	handle = NULL;
}