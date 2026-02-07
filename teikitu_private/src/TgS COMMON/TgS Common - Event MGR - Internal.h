/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Event MGR - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_EVENT_MGR_INTERNAL_H)
#define TGS_COMMON_EVENT_MGR_INTERNAL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Constants                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

enum { KTgEM_MAX_TE_FRM_POOL                =    16 };
enum { KTgEM_MAX_TE_SEC_POOL                =    16 };
enum { KTgEM_NUM_TE_IN_POOL                 =    69 };


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_UNION(STg2_EM_TB,)
{
    STg2_UT_ST__ST_Node                         m_sHead_Next; /* Untyped (void) pointer to next element */
    struct
    {
        TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        STg2_EM_TB                                  *m_psHead_Next; /* Typed pointer to the next element */
        TgFLOAT32                                   m_fStart;
        TgFLOAT32                                   m_fEnd;
        TgSINT_E32                                  m_iStart;
        TgSINT_E32                                  m_iEnd;

        TgUINT_E32                                  m_uiLocal_Index;

        TgUINT_E32                                  m_bfFlags;
    #if 0 != (224 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad1[224 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
};

TgTYPE_STRUCT(STg2_EM_TE,)
{
    TgFCN_EM_CALLBACK                           m_pfnCallback;
    TgUINT_PTR                                  m_uiParam;
};
TgCOMPILER_ASSERT( sizeof( STg2_EM_TE ) == 16, 0 );


/* ---- Time Pools --------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_EM_TE_Pool, )
{
    TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    STg2_Job                                    m_sJob;

    STg2_EM_TE_Pool                             *m_psFree_Next;  /**< Synchronization: g_asXXX_NewDel_Lock */
    STg2_EM_TB_P                                m_psFree;  /**< Synchronization: g_asXXX_NewDel_Lock */
    TgSINT_E32                                  m_niUsed;  /**< Synchronization: g_asXXX_NewDel_Lock */

    /* Aliases for the data held in the derived structure and only assigned during initialization */
    /* Used for per-entity synchronization or configuration data */
    TgUINT_E32                                  m_bfFlags;  /**< Synchronization: None */
    TgSINT_E32                                  m_iPool;  /**< Synchronization: Logical (write once - init) */
    TgUINT_E32                                  m_uiPad0;

    /* Synchronization is achieved for these members through execution logic (isolated, non-concurrent access) */
    STg2_EM_TB_P                                m_psWaiting;  /**< Synchronization: Logical (isolation) */
    STg2_EM_TB_P                                m_psActive;  /**< Synchronization: Logical (isolation) */
    TgUINT_E08                                  m_iPad1[TgBUILD_HARDWARE__POINTER_SIZE];

    union {
        TgEM_TE_FRM_ID                              m_atiEM_TE_FRM_NoSingleton[KTgEM_NUM_TE_IN_POOL];  /**< Synchronization: g_asXXX_Data_Lock */
        TgEM_TE_SEC_ID                              m_atiEM_TE_SEC_NoSingleton[KTgEM_NUM_TE_IN_POOL];  /**< Synchronization: g_asXXX_Data_Lock */
    };

#if 0 != (160 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgUINT_E08                                  m_uiPad2[160 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
#endif

    STg2_EM_TB                                  m_asTB[KTgEM_NUM_TE_IN_POOL];  /**< Synchronization: g_asXXX_Data_Lock */
    STg2_EM_TE                                  m_asTE[KTgEM_NUM_TE_IN_POOL];  /**< Synchronization: g_asXXX_Data_Lock */

    /* Lockless data structures (multi-thread safe) */
    STg2_UT_LF__ST                              m_sNew;  /**< Synchronization: Self */

#if 0 != (160 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgUINT_E08                                  m_uiPad3[160 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
#endif
};
//TgCOMPILER_ASSERT( sizeof( STg2_EM_TE_Pool ) == 4096, 0 );


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Internal Data                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* Time Line | Event Base Flags  */

TgINLINE TgVOID                             tgEM_TB_Set_Paused( STg2_EM_TB_PCU, TgBOOL_C );
TgINLINE TgVOID                             tgEM_TB_Set_Active( STg2_EM_TB_PCU, TgBOOL_C );
TgINLINE TgBOOL                             tgEM_TB_Is_Paused( STg2_EM_TB_CPCU );
TgINLINE TgBOOL                             tgEM_TB_Is_Active( STg2_EM_TB_CPCU );

/* Pool Utility Functions */

TgINLINE TgRESULT                           tgEM_TE_FRM_Lock( TgEM_TE_FRM_ID, TgUINT_E32_C, TgUINT_E32_C );
TgINLINE TgRESULT                           tgEM_TE_SEC_Lock( TgEM_TE_SEC_ID, TgUINT_E32_C, TgUINT_E32_C );

TgEXTN TgVOID                               tgEM_TP_Init( STg2_EM_TE_Pool_PC );

TgEXTN STg2_EM_TE_Pool_P                    g_apsEM_TE_FRM[KTgEM_MAX_TE_FRM_POOL];         /**< Synchronization: g_sEM_TE_FRM_Lock */
TgEXTN STg2_EM_TE_Pool_P                    g_psEM_TE_FRM_Free_List;                       /**< Synchronization: g_sEM_TE_FRM_Lock */
TgEXTN STg2_UT_LF_ISO__SN                   g_sEM_TE_FRM_Lock;
TgEXTN STg2_UT_LF_ISO__SN                   g_asEM_TE_FRM_Data_Lock[KTgEM_MAX_TE_FRM_POOL];
TgEXTN STg2_UT_LF_ISO__SN                   g_asEM_TE_FRM_NewDel_Lock[KTgEM_MAX_TE_FRM_POOL];

TgEXTN STg2_EM_TE_Pool_P                    g_apsEM_TE_SEC[KTgEM_MAX_TE_SEC_POOL];         /**< Synchronization: g_sEM_TE_SEC_Lock */
TgEXTN STg2_EM_TE_Pool_P                    g_psEM_TE_SEC_Free_List;                       /**< Synchronization: g_sEM_TE_SEC_Lock */
TgEXTN STg2_UT_LF_ISO__SN                   g_sEM_TE_SEC_Lock;
TgEXTN STg2_UT_LF_ISO__SN                   g_asEM_TE_SEC_Data_Lock[KTgEM_MAX_TE_SEC_POOL];
TgEXTN STg2_UT_LF_ISO__SN                   g_asEM_TE_SEC_NewDel_Lock[KTgEM_MAX_TE_SEC_POOL];


/* =============================================================================================================================================================================== */
#endif
