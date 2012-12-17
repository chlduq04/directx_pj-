#ifndef _GAUDIO_H_
#define	_GAUDIO_H_
#include <xact3.h>
#include <strsafe.h>
class GAudio{
private:
struct AUDIO_STATE
{
    IXACT3Engine* pEngine;
    IXACT3WaveBank* pWaveBank;
    IXACT3SoundBank* pSoundBank;

	XACTINDEX iZap;

    VOID* pbWaveBank; // Handle to wave bank data.  Its memory mapped so call UnmapViewOfFile() upon cleanup to release file
    VOID* pbSoundBank; // Pointer to sound bank data.  Call delete on it when the sound bank is destroyed
};
AUDIO_STATE g_audioState;
public:
	GAudio();
	inline void playSpace(){g_audioState.pSoundBank->Play( g_audioState.iZap, 0, 0, NULL );};
	inline AUDIO_STATE getAudioState(){return g_audioState;};

	HRESULT PrepareXACT();
	bool DoesCommandLineContainAuditionSwitch();
	HRESULT FindMediaFileCch( WCHAR* strDestPath, int cchDest, LPCWSTR strFilename );
	VOID CleanupXACT();

};
#endif