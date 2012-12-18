#include "GAudio.h"
GAudio::GAudio(){
}
HRESULT GAudio::PrepareXACT()
{
    HRESULT hr;
    WCHAR str[MAX_PATH];
    HANDLE hFile;
    DWORD dwFileSize;
    DWORD dwBytesRead;
    HANDLE hMapFile;

    // Clear struct
    ZeroMemory( &g_audioState, sizeof( AUDIO_STATE ) );

    hr = CoInitializeEx( NULL, COINIT_MULTITHREADED );  // COINIT_APARTMENTTHREADED will work too
    if( SUCCEEDED( hr ) )
    {
        // Switch to auditioning mode based on command line.  Change if desired
        bool bAuditionMode = DoesCommandLineContainAuditionSwitch();
        bool bDebugMode = false;

        DWORD dwCreationFlags = 0;
        if( bAuditionMode ) dwCreationFlags |= XACT_FLAG_API_AUDITION_MODE;
        if( bDebugMode ) dwCreationFlags |= XACT_FLAG_API_DEBUG_MODE;

        hr = XACT3CreateEngine( dwCreationFlags, &g_audioState.pEngine );
    }
    if( FAILED( hr ) || g_audioState.pEngine == NULL )
        return E_FAIL;

    // Initialize & create the XACT runtime 
    XACT_RUNTIME_PARAMETERS xrParams = {0};
    xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
    hr = g_audioState.pEngine->Initialize( &xrParams );
    if( FAILED( hr ) )
        return hr;

    if( FAILED( hr = FindMediaFileCch( str, MAX_PATH, L"sounds.xwb" ) ) )
        return hr;

    // Create an "in memory" XACT wave bank file using memory mapped file IO
    // Memory mapped files tend to be the fastest for most situations assuming you 
    // have enough virtual address space for a full map of the file
    hr = E_FAIL; // assume failure
	hFile = CreateFile((LPCSTR)str, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
    if( hFile != INVALID_HANDLE_VALUE )
    {
        dwFileSize = GetFileSize( hFile, NULL );
        if( dwFileSize != -1 )
        {
            hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
            if( hMapFile )
            {
                g_audioState.pbWaveBank = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
                if( g_audioState.pbWaveBank )
                {
                    hr = g_audioState.pEngine->CreateInMemoryWaveBank( g_audioState.pbWaveBank, dwFileSize, 0,
                                                                       0, &g_audioState.pWaveBank );
                }
                CloseHandle( hMapFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
            }
        }
        CloseHandle( hFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
    }
    if( FAILED( hr ) )
        return E_FAIL; // CleanupXACT() will cleanup state before exiting

    // Read and register the sound bank file with XACT.  Do not use memory mapped file IO because the 
    // memory needs to be read/write and the working set of sound banks are small.
    if( FAILED( hr = FindMediaFileCch( str, MAX_PATH, L"sounds.xsb" ) ) )
        return hr;
    hr = E_FAIL; // assume failure
    hFile = CreateFile( (LPCSTR)str, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
    if( hFile != INVALID_HANDLE_VALUE )
    {
        dwFileSize = GetFileSize( hFile, NULL );
        if( dwFileSize != -1 )
        {
            // Allocate the data here and free the data when recieving the sound bank destroyed notification
            g_audioState.pbSoundBank = new BYTE[dwFileSize];
            if( g_audioState.pbSoundBank )
            {
                if( 0 != ReadFile( hFile, g_audioState.pbSoundBank, dwFileSize, &dwBytesRead, NULL ) )
                {
                    hr = g_audioState.pEngine->CreateSoundBank( g_audioState.pbSoundBank, dwFileSize, 0,
                                                                0, &g_audioState.pSoundBank );
                }
            }
        }
        CloseHandle( hFile );
    }
    if( FAILED( hr ) )
        return E_FAIL; // CleanupXACT() will cleanup state before exiting

    // Get the sound cue index from the sound bank
    //
    // Note that if the cue does not exist in the sound bank, the index will be XACTINDEX_INVALID
    // however this is ok especially during development.  The Play or Prepare call will just fail.
    g_audioState.iZap = g_audioState.pSoundBank->GetCueIndex( "bounce" );

    return S_OK;
}

VOID GAudio::CleanupXACT()
{
    // Shutdown XACT
    //
    // Note that pEngine->ShutDown is synchronous and will take some time to complete 
    // if there are still playing cues.  Also pEngine->ShutDown() is generally only 
    // called when a game exits and is not the preferred method of changing audio 
    // resources. To know when it is safe to free wave/sound bank data without 
    // shutting down the XACT engine, use the XACTNOTIFICATIONTYPE_SOUNDBANKDESTROYED 
    // or XACTNOTIFICATIONTYPE_WAVEBANKDESTROYED notifications 
    if( g_audioState.pEngine )
    {
        g_audioState.pEngine->ShutDown();
        g_audioState.pEngine->Release();
    }

    if( g_audioState.pbSoundBank )
        delete[] g_audioState.pbSoundBank;
    g_audioState.pbSoundBank = NULL;

    // After pEngine->ShutDown() returns it is safe to release memory mapped files
    if( g_audioState.pbWaveBank )
        UnmapViewOfFile( g_audioState.pbWaveBank );
    g_audioState.pbWaveBank = NULL;

    CoUninitialize();
}


//--------------------------------------------------------------------------------------
// Helper function to try to find the location of a media file
//--------------------------------------------------------------------------------------
HRESULT GAudio::FindMediaFileCch( WCHAR* strDestPath, int cchDest, LPCWSTR strFilename )
{
    bool bFound = false;

    if( NULL == strFilename || strFilename[0] == 0 || NULL == strDestPath || cchDest < 10 )
        return E_INVALIDARG;

    // Get the exe name, and exe path
    WCHAR strExePath[MAX_PATH] = {0};
    WCHAR strExeName[MAX_PATH] = {0};
    WCHAR* strLastSlash = NULL;
	GetModuleFileName( NULL, (LPSTR)strExePath, MAX_PATH );
    strExePath[MAX_PATH - 1] = 0;
    strLastSlash = wcsrchr( strExePath, TEXT( '\\' ) );
    if( strLastSlash )
    {
        StringCchCopy( (LPSTR)strExeName, MAX_PATH, &strLastSlash[1] );

        // Chop the exe name from the exe path
        *strLastSlash = 0;

        // Chop the .exe from the exe name
        strLastSlash = wcsrchr( strExeName, TEXT( '.' ) );
        if( strLastSlash )
            *strLastSlash = 0;
    }

	StringCchCopy( (STRSAFE_LPSTR)strDestPath, cchDest, (STRSAFE_LPCSTR)strFilename );
    if( GetFileAttributes( (STRSAFE_LPSTR)strDestPath ) != 0xFFFFFFFF )
        return S_OK;

    // Search all parent directories starting at .\ and using strFilename as the leaf name
    WCHAR strLeafName[MAX_PATH] = {0};
    StringCchCopy( (STRSAFE_LPSTR)strLeafName, MAX_PATH, (STRSAFE_LPSTR)strFilename );

    WCHAR strFullPath[MAX_PATH] = {0};
    WCHAR strFullFileName[MAX_PATH] = {0};
    WCHAR strSearch[MAX_PATH] = {0};
    WCHAR* strFilePart = NULL;

	GetFullPathName( ".", MAX_PATH, (LPSTR)strFullPath, (LPSTR*)strFilePart );
    if( strFilePart == NULL )
        return E_FAIL;

    while( strFilePart != NULL && *strFilePart != '\0' )
    {
        StringCchPrintf( (STRSAFE_LPCSTR)strFullFileName, MAX_PATH, "%s\\%s", strFullPath, strLeafName );
        if( GetFileAttributes( (STRSAFE_LPCSTR)strFullFileName ) != 0xFFFFFFFF )
        {
			StringCchCopy( (STRSAFE_LPSTR)strDestPath, cchDest, (STRSAFE_LPCSTR)strFullFileName );
            bFound = true;
            break;
        }

        StringCchPrintf( (STRSAFE_LPSTR)strFullFileName, MAX_PATH,"%s\\Tutorials\\%s\\%s", strFullPath, strExeName, strLeafName );
        if( GetFileAttributes( (STRSAFE_LPSTR)strFullFileName ) != 0xFFFFFFFF )
        {
            StringCchCopy( (STRSAFE_LPSTR)strDestPath, cchDest, (STRSAFE_LPCSTR)strFullFileName );
            bFound = true;
            break;
        }

        StringCchPrintf( (STRSAFE_LPSTR)strSearch, MAX_PATH, "%s\\..", strFullPath );
        GetFullPathName( (LPCSTR)strSearch, MAX_PATH, (LPSTR)strFullPath, &strFilePart );
    }
    if( bFound )
        return S_OK;

    // On failure, return the file as the path but also return an error code
    StringCchCopy( (STRSAFE_LPSTR)strDestPath, cchDest, (STRSAFE_LPCSTR)strFilename );

    return HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND );
}


//--------------------------------------------------------------------------------------
bool GAudio::DoesCommandLineContainAuditionSwitch()
{
    const WCHAR* strAuditioning = L"-audition"; size_t nArgLen; int nNumArgs;
    LPWSTR* pstrArgList = CommandLineToArgvW( (LPCWSTR)GetCommandLine(), &nNumArgs );
    for( int iArg = 1; iArg < nNumArgs; iArg++ )
    {
		StringCchLength( (STRSAFE_PCNZCH)pstrArgList[iArg], 256, &nArgLen );
        if( _wcsnicmp( pstrArgList[iArg], strAuditioning, nArgLen ) == 0 && nArgLen == 9 )
            return true;
    }
    LocalFree( pstrArgList );
    return false;
}


LPCSTR GAudio::ConvertLPWSTCToLPCSTR(wchar_t* pStr,int* length)
{
 LPCSTR pszOut = NULL;
 int nOutputStrLen = 0;
 if(pStr != NULL)
 {
  int nInputStrLen = wcslen(pStr);
  nOutputStrLen = WideCharToMultiByte(CP_ACP,0,pStr,nInputStrLen,NULL,0,0,0);
  pszOut = new char[nOutputStrLen];
  if(pszOut)
  {
   memset((void*)pszOut,0x00,sizeof(CHAR)*nOutputStrLen);
   WideCharToMultiByte(CP_ACP,0,pStr,nInputStrLen,(LPSTR)pszOut,nOutputStrLen,0,0);
  }
 }
 *length = nOutputStrLen;
 return pszOut;
}