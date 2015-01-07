

/**@file tmedia_denoise.h
 * @brief Denoiser (Noise suppression, AGC, AEC, VAD) Plugin
 *

 */
#ifndef TINYMEDIA_DENOISE_H
#define TINYMEDIA_DENOISE_H

#include "tinymedia_config.h"
#include "tinymedia/tmedia_params.h"

#include "tsk_object.h"

TMEDIA_BEGIN_DECLS

/** cast any pointer to @ref tmedia_denoise_t* object */
#define TMEDIA_DENOISE(self)		((tmedia_denoise_t*)(self))

/** Base object for all Denoisers */
typedef struct tmedia_denoise_s
{
	TSK_DECLARE_OBJECT;

	tsk_bool_t opened;
	
	uint32_t echo_tail;
	uint32_t echo_skew;
	tsk_bool_t echo_supp_enabled;
	tsk_bool_t agc_enabled ;
	float agc_level;
	tsk_bool_t vad_enabled;
	tsk_bool_t noise_supp_enabled;
	int32_t noise_supp_level;

	const struct tmedia_denoise_plugin_def_s* plugin;
}
tmedia_denoise_t;

#define TMEDIA_DECLARE_DENOISE tmedia_denoise_t __denoise__

/** Virtual table used to define a consumer plugin */
typedef struct tmedia_denoise_plugin_def_s
{
	//! object definition used to create an instance of the denoiser
	const tsk_object_def_t* objdef;
	
	//! full description (usefull for debugging)
	const char* desc;

	int (*set) (tmedia_denoise_t* , const tmedia_param_t*);
	int (* open) (tmedia_denoise_t*, uint32_t frame_size, uint32_t sampling_rate);
	int (*echo_playback) (tmedia_denoise_t* self, const void* echo_frame);
	//! aec, vad, noise suppression, echo cancellation before sending packet over network
	int (* process_record) (tmedia_denoise_t*, void* audio_frame, tsk_bool_t* silence_or_noise);
	//! noise suppression before playing sound
	int (* process_playback) (tmedia_denoise_t*, void* audio_frame);
	int (* close) (tmedia_denoise_t* );
}
tmedia_denoise_plugin_def_t;

TINYMEDIA_API int tmedia_denoise_init(tmedia_denoise_t* self);
TINYMEDIA_API int tmedia_denoise_set(tmedia_denoise_t* self, const tmedia_param_t* param);
TINYMEDIA_API int tmedia_denoise_open(tmedia_denoise_t* self, uint32_t frame_size, uint32_t sampling_rate);
TINYMEDIA_API int tmedia_denoise_echo_playback(tmedia_denoise_t* self, const void* echo_frame);
TINYMEDIA_API int tmedia_denoise_process_record(tmedia_denoise_t* self, void* audio_frame, tsk_bool_t* silence_or_noise);
TINYMEDIA_API int tmedia_denoise_process_playback(tmedia_denoise_t* self, void* audio_frame);
TINYMEDIA_API int tmedia_denoise_close(tmedia_denoise_t* self);
TINYMEDIA_API int tmedia_denoise_deinit(tmedia_denoise_t* self);

TINYMEDIA_API int tmedia_denoise_plugin_register(const tmedia_denoise_plugin_def_t* plugin);
TINYMEDIA_API int tmedia_denoise_plugin_unregister();
TINYMEDIA_API tmedia_denoise_t* tmedia_denoise_create();

TMEDIA_END_DECLS


#endif /* TINYMEDIA_DENOISE_H */ 
