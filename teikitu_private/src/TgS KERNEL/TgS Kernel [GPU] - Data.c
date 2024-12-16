/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Data [GPU].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */
#if !defined (ENABLE_RELOAD_GUARD)

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  System ID                                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgKI_DEFINE(KN_GPU_CXT_HOST_ID);
TgKI_DEFINE(KN_GPU_CXT_HOST_EXTN_ID);
TgKI_DEFINE(KN_GPU_CXT_DEVC_ID);
TgKI_DEFINE(KN_GPU_CXT_EXEC_ID);
TgKI_DEFINE(KN_GPU_CXT_SWAP_ID);
TgKI_DEFINE(KN_GPU_CXT_WORK_ID);

TgKN_GPU_CS_ID_C                            KTgKN_GPU_CS_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_DS_ID_C                            KTgKN_GPU_DS_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_GS_ID_C                            KTgKN_GPU_GS_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_HS_ID_C                            KTgKN_GPU_HS_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_PS_ID_C                            KTgKN_GPU_PS_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_VS_ID_C                            KTgKN_GPU_VS_ID__INVALID = { KTgID__INVALID_VALUE };

TgKN_GPU_TX_CBE_ID_C                        KTgKN_GPU_TX_CBE_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_TX_IMG_ID_C                        KTgKN_GPU_TX_IMG_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_TX_VOL_ID_C                        KTgKN_GPU_TX_VOL_ID__INVALID = { KTgID__INVALID_VALUE };

TgKN_GPU_TX_CBE_INST_ID_C                   KTgKN_GPU_TX_CBE_INST_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_TX_IMG_INST_ID_C                   KTgKN_GPU_TX_IMG_INST_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_TX_VOL_INST_ID_C                   KTgKN_GPU_TX_VOL_INST_ID__INVALID = { KTgID__INVALID_VALUE };




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/* NOTE: Data definitions for templated resource and resource libraries are declared in the associated source files. */

/* ---- Configuration ------------------------------------------------------------------------------------------------------------------------------------------------------------ */

TgCN_VAR_ID                                 g_tiCVAR_KN_GPU_Adapter;
TgCN_VAR_ID                                 g_tiCVAR_KN_GPU_Output;
TgCN_VAR_ID                                 g_tiCVAR_KN_GPU_Width;
TgCN_VAR_ID                                 g_tiCVAR_KN_GPU_Height;
TgCN_VAR_ID                                 g_tiCVAR_KN_GPU_Refresh_Rate;
TgCN_VAR_ID                                 g_tiCVAR_KN_GPU_ScanOut_HDR;

TgCHAR_U8                                   g_szKN_GPU_Adapter[128];
TgCHAR_U8                                   g_szKN_GPU_Output[32];
TgUINT_E32                                  g_uiKN_GPU_Width;
TgUINT_E32                                  g_uiKN_GPU_Height;
TgUINT_E32                                  g_uiKN_GPU_Refresh_Rate;
TgBOOL                                      g_bKN_GPU_ScanOut_HDR;


/* ---- GPU - Console ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#if TgCOMPILE__CONSOLE
TgCHAR_U8                                   g_uszKN_GPU_LOG_Render_Buffer[KTgCN_OSLOG_LINE_LENGTH*KTgCN_OSLOG_MAX_LINE];
TgRSIZE                                     g_nuiKN_GPU_LOG_Line;
TgCHAR_U8                                   g_uszKN_GPU_CON_Render_Buffer[KTgCN_OSCON_MAX_LINE*KTgCN_OSCON_LINE_LENGTH];
TgRSIZE                                     g_nuiKN_GPU_CON_Line;
/*# TgCOMPILE__CONSOLE */
#endif


/* ---- Enumeration and Contexts ------------------------------------------------------------------------------------------------------------------------------------------------- */

STg2_KN_GPU_CXT_HOST_EXTN                   g_sKN_GPU_CXT_HOST_EXT;
STg2_KN_GPU_CXT_HOST                        g_sKN_GPU_CXT_HOST;

STg2_KN_GPU_CXT_DEVC                        g_asKN_GPU_CXT_DEVC[KTgKN_GPU_MAX_DEVC_CONTEXT];
STg2_UT_LF_ISO__ST                          g_sKN_GPU_CXT_DEVC_Free_Stack;
STg2_KN_GPU_CXT_EXEC_EXTN                   g_asKN_GPU_CXT_EXEC_EXT[KTgKN_GPU_MAX_EXEC_CONTEXT];
STg2_KN_GPU_CXT_EXEC                        g_asKN_GPU_CXT_EXEC[KTgKN_GPU_MAX_EXEC_CONTEXT];
STg2_UT_LF_ISO__ST                          g_sKN_GPU_CXT_EXEC_Free_Stack;
STg2_KN_GPU_CXT_SWAP                        g_asKN_GPU_CXT_SWAP[KTgKN_GPU_MAX_SWAP_CONTEXT];
STg2_UT_LF_ISO__ST                          g_sKN_GPU_CXT_SWAP_Free_Stack;


/* ---- GPU Resource ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#define __PARENT_FILE__ "TgS Kernel [GPU] - Data.c"
#define ENABLE_RELOAD_GUARD
#include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__


/* ---- GPU - Resource - Shader -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ---- GPU - Resource - Input --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ---- GPU - Resource - Texture ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ---- GPU - Resource - Debug Output -------------------------------------------------------------------------------------------------------------------------------------------- */

STg2_KN_GPU_FONT                            g_sKN_GPU_STD_DOS_Font[ETgKN_GPU_DOS_FONT_ROM_COUNT] = {
                                                {
                                                    .m_uiFntX = 8,
                                                    .m_uiFntY = 8,
                                                    .m_uiBufX = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Default_Data),
                                                    .m_nuiGlyph = TgARRAY_COUNT( g_uiKN_GPU_STD_DOS_Font_Default_Data ) * 8 / (8*8),
                                                    .m_puiData = g_uiKN_GPU_STD_DOS_Font_Default_Data,
                                                    .m_uszName = u8"FONT DOS Default"
                                                },
                                                {
                                                    .m_uiFntX = 8,
                                                    .m_uiFntY = 8,
                                                    .m_uiBufX = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Future_Data),
                                                    .m_nuiGlyph = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Future_Data) * 8 / (8*8),
                                                    .m_puiData = g_uiKN_GPU_STD_DOS_Font_Future_Data,
                                                    .m_uszName = u8"FONT DOS Future"
                                                },
                                                {
                                                    .m_uiFntX = 8,
                                                    .m_uiFntY = 8,
                                                    .m_uiBufX = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Block_Data),
                                                    .m_nuiGlyph = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Block_Data) * 8 / (8*8),
                                                    .m_puiData = g_uiKN_GPU_STD_DOS_Font_Block_Data,
                                                    .m_uszName = u8"FONT DOS Block"
                                                },
                                                {
                                                    .m_uiFntX = 8,
                                                    .m_uiFntY = 16,
                                                    .m_uiBufX = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Marcio_Data),
                                                    .m_nuiGlyph = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Marcio_Data) * 8 / (8*16),
                                                    .m_puiData = g_uiKN_GPU_STD_DOS_Font_Marcio_Data,
                                                    .m_uszName = u8"FONT DOS Marcio"
                                                }
                                            };

                                            /* Single Quad used for rendering text, which is based instance rendering. */
STg2_KN_GPU_Vertex_UI_Text_C                g_sVertex_Text[4] = {
                                                { { { 0.0F, 0.0F } }, { { 0.0f, 1.0f } } }, { { { 0.0F, 1.0F } }, { { 0.0f, 0.0f } } },
                                                { { { 1.0F, 0.0F } }, { { 1.0f, 1.0f } } }, { { { 1.0F, 1.0F } }, { { 1.0f, 0.0f } } },
                                            };
TgRSIZE_C                                   g_uiAligned_Debug_Text_Constant_Buffer_Size = (sizeof( STg2_KN_GPU_HLSL_CB_Debug_Text ) + 255) & ~255ULL;

                                            /* Single quad used for clearing the render target. */
STg2_KN_GPU_Vertex_UI_C                     g_sVertex_UI[4] = {
                                                { { { 0.0F, 0.0F } }, { { 0.0f, 1.0f } }, { { 1.0f, 1.0f, 1.0f, 1.0f } } },
                                                { { { 0.0F, 1.0F } }, { { 0.0f, 0.0f } }, { { 1.0f, 1.0f, 1.0f, 1.0f } } },
                                                { { { 1.0F, 0.0F } }, { { 1.0f, 1.0f } }, { { 1.0f, 1.0f, 1.0f, 1.0f } } },
                                                { { { 1.0F, 1.0F } }, { { 1.0f, 0.0f } }, { { 1.0f, 1.0f, 1.0f, 1.0f } } },
                                            };

TgRSIZE_C                                   g_uiAligned_Debug_Quad_Constant_Buffer_Size = (sizeof( STg2_KN_GPU_HLSL_CB_Debug_UI ) + 255) & ~255ULL;
TgRSIZE_C                                   g_uiAligned_Debug_Model_Constant_Buffer_Size = (sizeof( STg2_KN_GPU_HLSL_CB_Debug_Model ) + 255) & ~255ULL;
TgRSIZE_C                                   g_uiAligned_Debug_Model_Instance_Constant_Buffer_Size = (sizeof( STg2_KN_GPU_HLSL_CB_Debug_Model_Instance ) + 255) & ~255ULL;
TgRSIZE_C                                   g_uiAligned_Debug_Line_Constant_Buffer_Size = (sizeof( STg2_KN_GPU_HLSL_CB_Debug_Line ) + 255) & ~255ULL;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal State | Debug Data                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- Stat --------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL

TgUINT_E32                                  g_uiKN_Stats_Loaded_Mesh_Vertex; /* #IMPLEMENT */
TgUINT_E32                                  g_uiKN_Stats_Loaded_Mesh_Face; /* #IMPLEMENT */
TgRSIZE                                     g_uiKN_Stats_Memory_Buffer; /* #IMPLEMENT */
TgRSIZE                                     g_uiKN_Stats_Memory_Mesh; /* #IMPLEMENT */
TgRSIZE                                     g_uiKN_Stats_Memory_Mesh_Collision; /* #IMPLEMENT */

/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif


/* ---- Debug -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_DEBUG__KERNEL

/*# TgS_DEBUG__KERNEL */
#endif


/* ---- tgKN_GPU_Query_Fixed_Memory ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgKN_GPU_Query_Fixed_Memory( TgVOID )
{
    return ( 0
             + sizeof( g_tiCVAR_KN_GPU_Adapter )
             + sizeof( g_tiCVAR_KN_GPU_Output )
             + sizeof( g_tiCVAR_KN_GPU_Width )
             + sizeof( g_tiCVAR_KN_GPU_Height )
             + sizeof( g_tiCVAR_KN_GPU_Refresh_Rate )
             + sizeof( g_tiCVAR_KN_GPU_ScanOut_HDR )
             + sizeof( g_szKN_GPU_Adapter )
             + sizeof( g_szKN_GPU_Output )
             + sizeof( g_uiKN_GPU_Width )
             + sizeof( g_uiKN_GPU_Height )
             + sizeof( g_uiKN_GPU_Refresh_Rate )
             + sizeof( g_bKN_GPU_ScanOut_HDR )

             + sizeof( g_sKN_GPU_CXT_HOST_EXT )
             + sizeof( g_sKN_GPU_CXT_HOST )
             + sizeof( g_asKN_GPU_CXT_DEVC )
             + sizeof( g_sKN_GPU_CXT_DEVC_Free_Stack )
             + sizeof( g_asKN_GPU_CXT_EXEC )
             + sizeof( g_sKN_GPU_CXT_EXEC_Free_Stack )
             + sizeof( g_asKN_GPU_CXT_SWAP )
             + sizeof( g_sKN_GPU_CXT_SWAP_Free_Stack )

             + tgKN_GPU_CS_Query_Fixed_Memory()
             + tgKN_GPU_DS_Query_Fixed_Memory()
             + tgKN_GPU_GS_Query_Fixed_Memory()
             + tgKN_GPU_HS_Query_Fixed_Memory()
             + tgKN_GPU_PS_Query_Fixed_Memory()
             + tgKN_GPU_VS_Query_Fixed_Memory()

             + tgKN_GPU_TX_CBE_Query_Fixed_Memory()
             + tgKN_GPU_TX_IMG_Query_Fixed_Memory()
             + tgKN_GPU_TX_VOL_Query_Fixed_Memory()

         #if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
             +sizeof( g_uiKN_Stats_Loaded_Mesh_Vertex ) /* #IMPLEMENT */
             + sizeof( g_uiKN_Stats_Loaded_Mesh_Face ) /* #IMPLEMENT */
             + sizeof( g_uiKN_Stats_Memory_Buffer ) /* #IMPLEMENT */
             + sizeof( g_uiKN_Stats_Memory_Mesh ) /* #IMPLEMENT */
             + sizeof( g_uiKN_Stats_Memory_Mesh_Collision ) /* #IMPLEMENT */
         /*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
         #endif
    );
}


/*# defined (ENABLE_RELOAD_GUARD) */
#else

T(TgKN_GPU_,_ID_A)                          T(g_axsKN_Lib_,_Ref_Singleton)[T(KTgKN_GPU_MAX_,)];
T(STg2_KN_GPU_,_DATA)                       T(g_asKN_Lib_,_Data)[T(KTgKN_GPU_MAX_,)];
STg2_UT_LF_ISO__ST                          T(g_sKN_Lib_,);
STg2_UT_LF_ISO__SN                          T(g_sKN_Lib_,_Lock);
TgUINT_E64_A                                T(g_xnuiKN_Lib_,_Init);

#if defined(MACRO_BUILD_TEXTURE)
T(TgKN_GPU_,_INST_ID_A)                     T(g_axsCXT_,_Inst_Ref_Singleton)[KTgKN_GPU_MAX_EXEC_CONTEXT][T(KTgKN_GPU_MAX_,_INST)];
T(TgKN_GPU_,_ID)                            T(g_asCXT_,)[KTgKN_GPU_MAX_EXEC_CONTEXT][T(KTgKN_GPU_MAX_,_INST)];
STg2_UT_LF_ISO__ST                          T(g_sCXT_,_Inst)[KTgKN_GPU_MAX_EXEC_CONTEXT];
STg2_UT_LF_ISO__SN                          T(g_sCXT_,_Inst_Lock)[KTgKN_GPU_MAX_EXEC_CONTEXT];
/*# defined(MACRO_BUILD_TEXTURE) */
#endif

#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
TgRSIZE                                     T(g_uiKN_Size_GPU_,)[T(KTgKN_GPU_MAX_,)];
TgRSIZE                                     T(g_uiKN_Size_GPU_,_Total);
/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif

#if TgS_DEBUG__KERNEL
TgCHAR_U8                                   T(g_szKN_GPU_,)[T(KTgKN_GPU_MAX_,)][KTgMAX_FILE_NAME];
/*# TgS_DEBUG__KERNEL */
#endif

/* ---- (tgKN_GPU_,_Query_Fixed_Memory) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE T(tgKN_GPU_,_Query_Fixed_Memory)( TgVOID )
{
    return ( 0
             + sizeof( T(g_axsKN_Lib_,_Ref_Singleton ) )
             + sizeof( T(g_asKN_Lib_,_Data ) )
             + sizeof( T(g_sKN_Lib_, ) )
             + sizeof( T(g_sKN_Lib_,_Lock ) )
             + sizeof( T(g_xnuiKN_Lib_,_Init ) )

        #if defined(MACRO_BUILD_TEXTURE)
             + sizeof( T(g_axsCXT_,_Inst_Ref_Singleton ) )
             + sizeof( T(g_asCXT_, ) )
             + sizeof( T(g_sCXT_,_Inst ) )
             + sizeof( T(g_sCXT_,_Inst_Lock ) )
        /*# defined(MACRO_BUILD_TEXTURE) */
        #endif

        #if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
             + sizeof( T(g_uiKN_Size_GPU_,) )
        /*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
        #endif

        #if TgS_DEBUG__KERNEL
             + sizeof( T(g_szKN_GPU_,) )
        /*# TgS_DEBUG__KERNEL */
        #endif
    );
}


/* =============================================================================================================================================================================== */

/*# !defined (ENABLE_RELOAD_GUARD) */
#endif
