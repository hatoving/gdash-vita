#ifndef FMOD_SYMBOLS_H
#define FMOD_SYMBOLS_H

#include <stdbool.h>

extern void* _ZN4FMOD3DSP15getMeteringInfoEP22FMOD_DSP_METERING_INFOS2_;
extern void* _ZN4FMOD14ChannelControl11getUserDataEPPv;
extern void* _ZN4FMOD14ChannelControl6getDSPEiPPNS_3DSPE;
extern void* _ZN4FMOD3DSP17setParameterFloatEif;
extern void* FMOD_System_Create;
extern void* _ZN4FMOD6System10getVersionEPj;
extern void* FMOD_Debug_Initialize;
extern void* _ZN4FMOD6System19getStreamBufferSizeEPjS1_;
extern void* _ZN4FMOD6System16setDSPBufferSizeEji;
extern void* _ZN4FMOD6System16getDSPBufferSizeEPjPi;
extern void* _ZN4FMOD6System17getSoftwareFormatEPiP16FMOD_SPEAKERMODES1_;
extern void* _ZN4FMOD6System17setSoftwareFormatEi16FMOD_SPEAKERMODEi;
extern void* _ZN4FMOD6System4initEijPv;
extern void* _ZN4FMOD6System18createChannelGroupEPKcPPNS_12ChannelGroupE;
extern void* _ZN4FMOD14ChannelControl13setVolumeRampEb;
extern void* _ZN4FMOD3DSP18setMeteringEnabledEbb;
extern void* _ZN4FMOD12ChannelGroup8addGroupEPS0_bPPNS_13DSPConnectionE;
extern void* _ZN4FMOD6System15createDSPByTypeE13FMOD_DSP_TYPEPPNS_3DSPE;
extern void* _ZN4FMOD3DSP16setParameterBoolEib;
extern void* _ZN4FMOD14ChannelControl6addDSPEiPNS_3DSPE;
extern void* _ZN4FMOD6System11mixerResumeEv;
extern void* _ZN4FMOD6System6updateEv;
extern void* _ZN4FMOD6System12mixerSuspendEv;
extern void* _ZN4FMOD14ChannelControl9setPausedEb;
extern void* FMOD_Channel_GetFadePoints;
extern void* FMOD_Channel_GetDSPClock;
extern void* _ZN4FMOD14ChannelControl11getDSPClockEPyS1_;
extern void* FMOD_Channel_RemoveFadePoints;
extern void* _ZN4FMOD14ChannelControl9setVolumeEf;
extern void* _ZN4FMOD5Sound12getOpenStateEP14FMOD_OPENSTATEPjPbS4_;
extern int _ZN4FMOD6System12createStreamEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE(void *this, const char *fname, int mode, void *exinfo, int **sound);
extern void* _ZN4FMOD5Sound12setLoopCountEi;
extern void* _ZN4FMOD5Sound7releaseEv;
extern void* FMOD_Memory_GetStats;
extern void* _ZN4FMOD6System11getCPUUsageEP14FMOD_CPU_USAGE;
extern void* _ZN4FMOD14ChannelControl4stopEv;
extern void* _ZN4FMOD6System5closeEv;
extern void* _ZN4FMOD6System7releaseEv;
extern void* _ZN4FMOD12ChannelGroup7releaseEv;
extern void* FMOD_System_LockDSP;
extern void* _ZN4FMOD7Channel13getLoopPointsEPjjS1_j;
extern void* _ZN4FMOD7Channel11getPositionEPjj;
extern void* FMOD_Channel_GetDelay;
extern void* FMOD_System_UnlockDSP;
extern void* _ZN4FMOD14ChannelControl11setUserDataEPv;
extern void* _ZN4FMOD14ChannelControl9getVolumeEPf;
extern void* _ZN4FMOD14ChannelControl8getPitchEPf;
extern void* _ZN4FMOD7Channel11setPositionEjj;
extern void* _ZN4FMOD7Channel15getCurrentSoundEPPNS_5SoundE;
extern void* _ZN4FMOD5Sound9getLengthEPjj;
extern void* _ZN4FMOD14ChannelControl8setPitchEf;
extern int _ZN4FMOD14ChannelControl9getPausedEPb(void* channel, bool* paused);
extern void* _ZN4FMOD14ChannelControl12addFadePointEyf;
extern void* _ZN4FMOD7Channel12setLoopCountEi;
extern void* _ZN4FMOD14ChannelControl8setDelayEyyb;
extern void* _ZN4FMOD7Channel13setLoopPointsEjjjj;
extern int _ZN4FMOD6System9playSoundEPNS_5SoundEPNS_12ChannelGroupEbPPNS_7ChannelE(void* system, void* sound, void* channel_group, bool paused, void **channel);
extern void* _ZN4FMOD14ChannelControl11setCallbackEPF11FMOD_RESULTP19FMOD_CHANNELCONTROL24FMOD_CHANNELCONTROL_TYPE33FMOD_CHANNELCONTROL_CALLBACK_TYPEPvS6_E;
extern void* _ZN4FMOD12ChannelGroup14getNumChannelsEPi;
extern void* _ZN4FMOD12ChannelGroup10getChannelEiPPNS_7ChannelE;
extern int _ZN4FMOD6System11createSoundEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE(void *this, const char *fname, int mode, void *exinfo, int** sound);
extern void* _ZN4FMOD6System7lockDSPEv;
extern void* _ZN4FMOD6System9unlockDSPEv;
extern void* _ZN4FMOD14ChannelControl10getNumDSPsEPi;

#endif