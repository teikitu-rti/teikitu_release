/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Resource [Shader].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD)

    #define __PARENT_FILE__ "TgS Kernel [GPU] - Resource [Shader].c"
    #define ENABLE_RELOAD_GUARD
    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
    #undef ENABLE_RELOAD_GUARD
    #undef __PARENT_FILE__

#else
#if defined(MACRO_BUILD_SHADER)
/* == Kernel ===================================================================================================================================================================== */

/* ---- T(tgKN_GPU_,__Execute_Load) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT T(tgKN_GPU_,__Execute_Load)( TgKN_FILE_ID_C tiFile, TgRSIZE_C UNUSED_PARAM uiFile_Offset, T(STg2_KN_GPU_,_DESC_CPC) psDESC, ETgKN_GPU_ALLOCATOR_C UNUSED_PARAM enAllocator,
                                      T(TgKN_GPU_,_ID_C) sID  )
{
    if (nullptr != psDESC)
    {
        if (nullptr == psDESC->m_puiData || 0 >= psDESC->m_nuiData)
        {
            return (KTgE_FAIL);
        };

        T(g_asKN_Lib_,_Data)[sID.m_uiIndex].m_sSH.m_puiConstData = psDESC->m_puiData;
        T(g_asKN_Lib_,_Data)[sID.m_uiIndex].m_sSH.m_nuiData = psDESC->m_nuiData;

        tgBF_Set_Flag_U64( &T(g_asKN_Lib_,_Data)[sID.m_uiIndex].m_sSH.m_uiFlags, ETgKN_GPU_SHADER_FLAGS_FREE_MEMORY_ON_RELEASE, true );
    }
    else
    {
        STg2_KN_File_Read_Command           sRead_Command;

        if (KTgKN_FILE_ID__INVALID.m_uiKI == tiFile.m_uiKI)
        {
            return (KTgE_FAIL);
        };

        tgMM_Set_U08_0x00( &sRead_Command, sizeof( sRead_Command ) );
        sRead_Command.m_tiFile = tiFile; // TODO use file offset
        sRead_Command.m_pfnAllocator = tgKN_FILE_ALLOCATOR__Default_Malloc_Pool; // TODO: Use enAllocator to select an allocator

        TgVERIFY(TgSUCCEEDED(tgKN_FS_BL_Read( &sRead_Command ))); // TODO Use an async command

        T(g_asKN_Lib_,_Data)[sID.m_uiIndex].m_sSH.m_puiData = (TgUINT_E08_P)sRead_Command.m_pBuffer;
        T(g_asKN_Lib_,_Data)[sID.m_uiIndex].m_sSH.m_nuiData = sRead_Command.m_nuiResult;

        tgBF_Set_Flag_U64( &T(g_asKN_Lib_,_Data)[sID.m_uiIndex].m_sSH.m_uiFlags, ETgKN_GPU_SHADER_FLAGS_FREE_MEMORY_ON_RELEASE, false );
    };

    return (KTgS_OK);
}


/* ---- T(tgKN_GPU_,__Execute_Free) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_,__Execute_Free)( T(TgKN_GPU_,_ID_C) sID )
{
    if (false == tgBF_Test_Flag_U64( &T(g_asKN_Lib_,_Data)[sID.m_uiIndex].m_sSH.m_uiFlags, ETgKN_GPU_SHADER_FLAGS_FREE_MEMORY_ON_RELEASE ))
    {
        TgFREE_POOL( (TgVOID_P)T(g_asKN_Lib_,_Data)[sID.m_uiIndex].m_sSH.m_puiData );
    }
    tgMM_Set_U08_0x00( T(g_asKN_Lib_,_Data) + sID.m_uiIndex, sizeof( T(g_asKN_Lib_,_Data)[0] ) );
}


/* =============================================================================================================================================================================== */
/*# defined(MACRO_BUILD_SHADER) */
#endif

/*# !defined(ENABLE_RELOAD_GUARD) */
#endif
