#ifndef MAIN_H
#define MAIN_H

#ifdef USE_FMOD
    #include <fmod/fmod.h>

    extern FMOD_RESULT F_API __real_FMOD_System_CreateSound(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
    extern FMOD_RESULT F_API __real_FMOD_System_CreateStream(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
#endif

#endif