/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - System.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COLLISION/TgS Collision - System.inl"

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/*  Large switch statements are known to be particularly bad on the in-order CPUs in the current consoles.  However, all other methods would be equivalent. Possible solutions
    that were debated (not tested): (1) Function pointers - this would require the retrieval of the pointer and then a jump to the function.  Since jumps are near-equivalent to a
    branch, nothing is gained.  (2) Virtual tables - at a compiler/machine level this is the same as (1). */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID
FCN_VO(tgCO_REQ_Copy_Common)(
    VEC_OBJ_T(STg2_CO_Request,PC), VEC_OBJ_T(STg2_CO_Request,CPC) );

TgINLINE TgVOID
FCN_VO(tgCO_REQ_Set_Owns_Data)(
    VEC_OBJ_T(STg2_CO_Request,PC), TgBOOL_C );

TgINLINE TgBOOL
FCN_VO(tgCO_REQ_Query_Owns_Data)(
    VEC_OBJ_T(STg2_CO_Request,PC) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_REQ_Ignore_Connection) ------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_REQ_Ignore_Connection)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, STg2_Connection_PC psConnection, TgBOOL_C bFlag )
{
    TgRSIZE_C                           nuiMax = psRequest->m_nuiConnection_Ignored;

    TgPARAM_CHECK( nullptr != psRequest && nullptr != psConnection );

    /* Check to see if the object is in the ignore list. */
    for (TgRSIZE uiIndex = 0; uiIndex < nuiMax; ++uiIndex)
    {
        if (psRequest->m_apsConnection_Ignored[uiIndex] != psConnection)
        {
            continue;
        };

        if (!bFlag)
        {
            if (uiIndex + 1 != nuiMax)
            {
                psRequest->m_apsConnection_Ignored[uiIndex] = psRequest->m_apsConnection_Ignored[nuiMax - 1];
            };

            --psRequest->m_nuiConnection_Ignored;
        };

        return (KTgS_OK);
    };

    if (nuiMax >= KTgCO_REQUEST__MAX_IGNORE || !bFlag)
    {
        return (KTgE_FAIL);
    };

    psRequest->m_apsConnection_Ignored[psRequest->m_nuiConnection_Ignored++] = psConnection;
    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_REQ_Ignore_Connection_Graph) ------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_REQ_Ignore_Connection_Graph)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, STg2_Connection_PC psConnection, TgBOOL_C bFlag )
{
    TgRSIZE_C                           nuiMax = psRequest->m_nuiConnection_Graph_Ignored;

    TgPARAM_CHECK( nullptr != psRequest && nullptr != psConnection );

    /* Check to see if the object is in the ignore list. */
    for (TgRSIZE uiIndex = 0; uiIndex < nuiMax; ++uiIndex)
    {
        if (psRequest->m_apsConnection_Graph_Ignored[uiIndex] != psConnection)
        {
            continue;
        };

        if (!bFlag)
        {
            if (uiIndex + 1 != nuiMax)
            {
                psRequest->m_apsConnection_Graph_Ignored[uiIndex] = psRequest->m_apsConnection_Graph_Ignored[nuiMax - 1];
            };

            --psRequest->m_nuiConnection_Graph_Ignored;
        };

        return (KTgS_OK);
    };

    if (nuiMax >= KTgCO_REQUEST__MAX_IGNORE || !bFlag)
    {
        return (KTgE_FAIL);
    };

    psRequest->m_apsConnection_Graph_Ignored[psRequest->m_nuiConnection_Graph_Ignored++] = psConnection;
    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_REQ_Ignore_Native_String) ---------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_REQ_Ignore_Native_String)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, TgSINT_E32_C nsVal, TgBOOL_C bFlag )
{
    TgRSIZE_C                           nuiMax = psRequest->m_nuiNative_String;

    if (KTgUID_NONE == nsVal)
    {
        return (KTgE_FAIL);
    };

    /* Check to see if the object is in the ignore list. */
    for (TgRSIZE uiIndex = 0; uiIndex < nuiMax; ++uiIndex)
    {
        if (psRequest->m_aiNative_String[uiIndex] != nsVal)
        {
            continue;
        };

        if (!bFlag)
        {
            if (uiIndex + 1 != nuiMax)
            {
                psRequest->m_aiNative_String[uiIndex] = psRequest->m_aiNative_String[nuiMax - 1];
            };

            --psRequest->m_nuiNative_String;
        };

        return (KTgS_OK);
    };

    if (nuiMax >= KTgCO_REQUEST__MAX_IGNORE || !bFlag)
    {
        return (KTgE_FAIL);
    };

    psRequest->m_aiNative_String[psRequest->m_nuiNative_String++] = nsVal;
    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_REQ_Is_Ignored_Connection) --------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgCO_REQ_Is_Ignored_Connection)(VEC_OBJ_T(STg2_CO_Request,CPC) psRequest, STg2_Connection_CPC psConnection)
{
    TgPARAM_CHECK( nullptr != psRequest && nullptr != psConnection );

    /* Check to see if all objects are being ignored. */
    if (FCN_VO(tgCO_REQ_Is_Ignored_All)( psRequest ))
    {
        return (true);
    };

    /* Check to see if the object is in the ignore list. */
    for (TgRSIZE uiIndex = 0; uiIndex < psRequest->m_nuiConnection_Ignored; ++uiIndex)
    {
        if (psRequest->m_apsConnection_Ignored[uiIndex] == psConnection)
        {
            return (true);
        };
    };

    /* Not ignored. */
    return (false);
}


/* ---- FCN_VO(tgCO_REQ_Is_Ignored_Native_String) -----------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgCO_REQ_Is_Ignored_Native_String)(VEC_OBJ_T(STg2_CO_Request,CPC) psRequest, TgSINT_E32_C nsVal)
{
    TgPARAM_CHECK( nullptr != psRequest && KTgUID_NONE != nsVal );

    /* Check to see if all objects are being ignored. */
    if (FCN_VO(tgCO_REQ_Is_Ignored_All)( psRequest ))
    {
        return (true);
    };

    /* Check to see if the object is in the ignore list. */
    for (TgRSIZE uiIndex = 0; uiIndex < psRequest->m_nuiNative_String; ++uiIndex)
    {
        if (psRequest->m_aiNative_String[uiIndex] == nsVal)
        {
            return (true);
        };
    };

    /* Not ignored. */
    return (false);
}


/* ---- FCN_VO(tgCO_REQ_Reset) ------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_VO(tgCO_REQ_Reset)(VEC_OBJ_T(STg2_CO_Request,PC) psRequest)
{
    if (FCN_VO(tgCO_REQ_Query_Owns_Data)(psRequest))
    {
        TgFREE_POOL( psRequest->m_psResult );
    };

    tgMM_Set_U08_0x00( psRequest, sizeof( VEC_OBJ_T(STg2_CO_Request) ) );

    psRequest->m_sPacket.m_psContact = psRequest->m_asContact;
    psRequest->m_sPacket.m_vSweepTol = FCN_V(tgMH_SET1)( VAR_K(KTgROOT_EPS) );
    psRequest->m_sPacket.m_vSnapTol = FCN_V(tgMH_SET1)( VAR_K(KTgEPS) );
    psRequest->m_sPacket.m_nuiMaxContact = 8;

    psRequest->m_psResult = psRequest->m_asInternal_Result;
    psRequest->m_nuiResult_End = KTgCO_REQUEST__INTERNAL_RESULTS;
}


/* ---- FCN_VO(tgCO_REQ_F_TX) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_VO(tgCO_REQ_F_TX)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, VEC_T(3,CPCU) pmM0 )
{
    FCN_VO(tgGM_DT_TX)( &psRequest->m_sDT, pmM0 );

    for (TgRSIZE uiIndex = 0; uiIndex < psRequest->m_nuiResult_Last; ++uiIndex)
    {
        psRequest->m_psResult[uiIndex].m_sContact.m_vS0 = FCN_V(tgMH_TX_P,3)( psRequest->m_psResult[uiIndex].m_sContact.m_vS0, pmM0 );
        psRequest->m_psResult[uiIndex].m_sContact.m_vN0 = FCN_V(tgMH_TX_V,3)( psRequest->m_psResult[uiIndex].m_sContact.m_vN0, pmM0 );
        FCN_VO(tgGM_PT_TX)( &psRequest->m_psResult[uiIndex].m_sPT, pmM0 );
    };
}


/* ---- FCN_VO(tgCO_REQ_F_Copy_TX) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_VO(tgCO_REQ_F_Copy_TX)( VEC_OBJ_T(STg2_CO_Request,PC) psDest, VEC_OBJ_T(STg2_CO_Request,CPC) psSrc, VEC_T(3,CPCU) pmM0 )
{
    FCN_VO(tgCO_REQ_Reset)( psDest );
    FCN_VO(tgCO_REQ_Copy_Common)( psDest, psSrc );

    FCN_VO(tgGM_DT_Copy_TX)( &psDest->m_sDT, &psSrc->m_sDT, pmM0 );

    for (TgRSIZE uiIndex = 0; uiIndex < psSrc->m_nuiResult_Last; ++uiIndex)
    {
        psDest->m_psResult[uiIndex].m_sContact.m_vS0 = FCN_V(tgMH_TX_P,3)( psSrc->m_psResult[uiIndex].m_sContact.m_vS0, pmM0 );
        psDest->m_psResult[uiIndex].m_sContact.m_vN0 = FCN_V(tgMH_TX_V,3)( psSrc->m_psResult[uiIndex].m_sContact.m_vN0, pmM0 );
        FCN_VO(tgGM_PT_Copy_TX)( &psDest->m_psResult[uiIndex].m_sPT, &psSrc->m_psResult[uiIndex].m_sPT, pmM0 );
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_REQ_Next_Result) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_OBJ_T(STg2_CO_Result,P) FCN_VO(tgCO_REQ_Next_Result)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, VEC_T(1,C) vS0, VEC_T(1,C) vNormal, VEC_T(1,C) vValue )
{
    VEC_T(1)                            vK0;

    for (TgRSIZE nuiCount = 0; nuiCount < psRequest->m_nuiResult_Last; ++nuiCount)
    {
        vK0 = FCN_V(tgMH_SUB)( vS0, psRequest->m_psResult[nuiCount].m_sContact.m_vS0 );
        if (!FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_LSQ)( vK0 ) ))
        {
            continue;
        };

        vK0 = FCN_V(tgMH_SUB)( vNormal, psRequest->m_psResult[nuiCount].m_sContact.m_vN0 );
        if (!FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_LSQ)( vK0 ) ))
        {
            continue;
        };

        return (psRequest->m_psResult + nuiCount);
    };

    if (psRequest->m_nuiResult_Last < psRequest->m_nuiResult_End)
    {
        return (psRequest->m_psResult + psRequest->m_nuiResult_Last++);
    };

    if (tgBF_Test_Flag_U32( &psRequest->m_bfFlags, ETgCO_FLAGS_NO_SORT ))
    {
        return (nullptr);
    };

    if (tgBF_Test_Flag_U32( &psRequest->m_bfFlags, ETgCO_FLAGS_ORDER_PARAMETER ))
    {
        /* When sorting on depth, find the value closest to zero, and replace that entry. */

        VEC_T(1)                            vTMP;
        TgRSIZE                             nuiCurrent = 0;

        vTMP = psRequest->m_psResult[0].m_sContact.m_vDepth;

        for (TgRSIZE nuiCount = 1; nuiCount < psRequest->m_nuiResult_End; ++nuiCount)
        {
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTMP, psRequest->m_psResult[nuiCount].m_sContact.m_vDepth ) ))
            {
                vTMP = psRequest->m_psResult[nuiCount].m_sContact.m_vDepth;
                nuiCurrent = nuiCount;
            };
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTMP, vValue ) ))
        {
            return (nullptr);
        }
        else
        {
            return (psRequest->m_psResult + nuiCurrent);
        };
    }
    else
    {
        /* When sorting on time, find the value furthest from zero, and replace that entry. */

        VEC_T(1)                            vTMP;
        TgRSIZE                             nuiCurrent = 0;

        vTMP = psRequest->m_psResult[0].m_sContact.m_vT0;

        for (TgRSIZE nuiCount = 1; nuiCount < psRequest->m_nuiResult_End; ++nuiCount)
        {
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTMP, psRequest->m_psResult[nuiCount].m_sContact.m_vT0 ) ))
            {
                vTMP = psRequest->m_psResult[nuiCount].m_sContact.m_vT0;
                nuiCurrent = nuiCount;
            };
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTMP, vValue ) ))
        {
            return (nullptr);
        }
        else
        {
            return (psRequest->m_psResult + nuiCurrent);
        };
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_REQ_Copy_Common) ------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID FCN_VO(tgCO_REQ_Copy_Common)( VEC_OBJ_T(STg2_CO_Request,PC) psDest, VEC_OBJ_T(STg2_CO_Request,CPC) psSrc )
{
    VEC_OBJ_T(STg2_CO_Result,P)         psResult;
    TgRSIZE                             nuiResult_End;
    TgBOOL                              bOwnsData = FCN_VO(tgCO_REQ_Query_Owns_Data)(psDest);

    /* If there is a result size mismatch, free the current buffer and create a new buffer */
    if (psDest->m_nuiResult_End < psSrc->m_nuiResult_End)
    {
        if (bOwnsData)
        {
            TgFREE_POOL( psDest->m_psResult );
        };

        psResult = (VEC_OBJ_T(STg2_CO_Result,P))TgMALLOC_POOL( (TgRSIZE)psSrc->m_nuiResult_End * sizeof( VEC_OBJ_T(STg2_CO_Result) ) );
        nuiResult_End = psSrc->m_nuiResult_End;
        bOwnsData = true;
        TgCRITICAL_MSGF( nullptr != psResult, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
    }
    else
    {
        psResult = psDest->m_psResult;
        nuiResult_End = psDest->m_nuiResult_End;
    }

    /* Copy the data */
    tgMM_Copy( psDest, sizeof( VEC_OBJ_T(STg2_CO_Request) ), psSrc, sizeof( VEC_OBJ_T(STg2_CO_Request) ) );

    /* Reassign the buffer */
    psDest->m_psResult = psResult;
    psDest->m_nuiResult_End = nuiResult_End;
    FCN_VO(tgCO_REQ_Set_Owns_Data)(psDest, bOwnsData);

    /* Copy the results */
    tgMM_Copy( psResult, KTgMAX_RSIZE, psSrc->m_psResult, (TgRSIZE)psSrc->m_nuiResult_Last*sizeof( VEC_OBJ_T(STg2_CO_Result,P) ) );
    psDest->m_nuiResult_Last = psSrc->m_nuiResult_Last;
}


/* ---- FCN_VO(tgCO_REQ_Set_Owns_Data) ----------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgCO_REQ_Set_Owns_Data)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &psRequest->m_bfFlags, ETgCO_FLAGS_OWNS_DATA, bFlag );
}


/* ---- FCN_VO(tgCO_REQ_Query_Owns_Data) --------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_REQ_Query_Owns_Data)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest )
{
    return (tgBF_Test_Flag_U32( &psRequest->m_bfFlags, ETgCO_FLAGS_OWNS_DATA ));
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
