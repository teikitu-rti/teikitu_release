/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (UWP) Common - Base - API [Universal].cpp
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define COMMON_INCLUDE_PREAMBLE_ONLY
#include "TgS COMMON/TgS (WIN) Common -- INCLUDE.h"
#include "TgS COMMON/TgS (WIN) Common - Base - LoadDLL.h"

#define DIRECTINPUT_VERSION 0x0800
#pragma warning( push, 3 )

#include <windows.h>
#include <Psapi.h>
#include <stdio.h>
#include <excpt.h>

#pragma warning( pop )




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgVOID tgCM_Path_Query_Application_Data_Folder( TgCHAR_U8_P dir, TgRSIZE_C maxsize )
{
    if (!maxsize) return;
    *dir = 0;
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
    Microsoft::WRL::ComPtr<IKnownFolderManager> mgr;
    HRESULT hr = CoCreateInstance( CLSID_KnownFolderManager, nullptr, CLSCTX_INPROC_SERVER, IID_IKnownFolderManager, (LPVOID*)&mgr );
    if (SUCCEEDED( hr ))
    {
        Microsoft::WRL::ComPtr<IKnownFolder> folder;
        hr = mgr->GetFolder( FOLDERID_LocalAppData, &folder );
        if (SUCCEEDED( hr ))
        {
            LPWSTR szPath = 0;
            hr = folder->GetPath( 0, &szPath );
            if (SUCCEEDED( hr ))
            {
                wcscpy_s( dir, maxsize, szPath );
                wcscat_s( dir, maxsize, L”\\MyUniqueApplicationName” );
                CreateDirectory( dir, nullptr );
                CoTaskMemFree( szPath );
            }
        }
    }
#else // Windows Store WinRT app
    auto folder = Windows::Storage::ApplicationData::Current->LocalFolder;
    wcscpy_s( dir, maxsize, folder->Path->Data() );
#endif
}



TgVOID tgCM_Path_Query_Temporary_Folder( TgCHAR_U8_P dir, TgRSIZE_C maxsize )
{
    if (!maxsize) return;
    *dir = 0;
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
    DWORD nChars = GetTempPath( maxsize, dir );
    if (nChars > 0)
        dir[nChars - 1] = '\0'; // Trim trailing '\'
    else
        *dir = 0;
#else // Windows Store WinRT app
    auto folder = Windows::Storage::ApplicationData::Current->TemporaryFolder;
    wcscpy_s( dir, maxsize, folder->Path->Data() );
#endif // WINAPI_FAMILY_PARTITION
}


