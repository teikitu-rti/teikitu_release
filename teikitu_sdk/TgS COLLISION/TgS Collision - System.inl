/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - System.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_SYSTEM_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision =================d================================================================================================================================================= */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Collision - Request Functions                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_REQ_Init_Test) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgCO_REQ_Init_Test)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, ETgPM_SHORT_C enPM, ETgCO_PURPOSE_C enPurpose )
{
    FCN_VO(tgCO_REQ_Reset)( psRequest );
    psRequest->m_enPM = enPM;
    psRequest->m_enPurpose = enPurpose;
    psRequest->m_enTest = ETgCO_TEST__BOOLEAN;
}


/* ---- FCN_VO(tgCO_REQ_Init_Test_Sweep) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgCO_REQ_Init_Test_Sweep)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, ETgPM_SHORT_C enPM, VEC_T(1,C) vDT, ETgCO_PURPOSE_C enPurpose )
{
    FCN_VO(tgCO_REQ_Reset)( psRequest );
    psRequest->m_enPM = enPM;
    psRequest->m_enPurpose = enPurpose;
    psRequest->m_enTest = ETgCO_TEST__BOOLEAN_SWEEP;
    psRequest->m_fToI = TYPE_K(1);
    FCN_VO(tgGM_DT_Set)( &psRequest->m_sDT, vDT );
}


/* ---- FCN_VO(tgCO_REQ_Init_Intersect) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgCO_REQ_Init_Intersect)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, ETgPM_SHORT_C enPM, ETgCO_PURPOSE_C enPurpose )
{
    FCN_VO(tgCO_REQ_Reset)( psRequest );
    psRequest->m_enPM = enPM;
    psRequest->m_enPurpose = enPurpose;
    psRequest->m_enTest = ETgCO_TEST__INTERSECT;
}


/* ---- FCN_VO(tgCO_REQ_Init_Penetrate) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgCO_REQ_Init_Penetrate)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, ETgPM_SHORT_C enPM, ETgCO_PURPOSE_C enPurpose )
{
    FCN_VO(tgCO_REQ_Reset)( psRequest );
    psRequest->m_enPM = enPM;
    psRequest->m_enPurpose = enPurpose;
    psRequest->m_enTest = ETgCO_TEST__PENETRATE;
    tgBF_Set_Flag_U32( &psRequest->m_bfFlags, ETgCO_FLAGS_ORDER_PARAMETER, true );
}


/* ---- FCN_VO(tgCO_REQ_Init_Sweep) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgCO_REQ_Init_Sweep)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, ETgPM_SHORT_C enPM, VEC_T(1,C) vDT, ETgCO_PURPOSE_C enPurpose )
{
    FCN_VO(tgCO_REQ_Reset)( psRequest );
    psRequest->m_enPM = enPM;
    psRequest->m_enPurpose = enPurpose;
    psRequest->m_enTest = ETgCO_TEST__SWEEP;
    psRequest->m_fToI = TYPE_K(1);
    FCN_VO(tgGM_DT_Set)( &psRequest->m_sDT, vDT );
}


/* ---- FCN_VO(tgCO_REQ_Init_Sweep_Penetrate) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgCO_REQ_Init_Sweep_Penetrate)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, ETgPM_SHORT_C enPM, VEC_T(1,C) vDT, ETgCO_PURPOSE_C enPurpose )
{
    FCN_VO(tgCO_REQ_Reset)( psRequest );
    psRequest->m_enPM = enPM;
    psRequest->m_enPurpose = enPurpose;
    psRequest->m_enTest = ETgCO_TEST__SWEEP_PENETRATE;
    psRequest->m_fToI = TYPE_K(1);
    FCN_VO(tgGM_DT_Set)( &psRequest->m_sDT, vDT );
}


/* ---- FCN_VO(tgCO_REQ_Init_Collect) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgCO_REQ_Init_Collect)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, ETgPM_SHORT_C enPM, ETgCO_PURPOSE_C enPurpose )
{
    FCN_VO(tgCO_REQ_Reset)( psRequest );
    psRequest->m_enPM = enPM;
    psRequest->m_enPurpose = enPurpose;
    psRequest->m_enTest = ETgCO_TEST__COLLECT;
}


/* ---- FCN_VO(tgCO_REQ_Set_Include_Filter) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgCO_REQ_Set_Include_Filter)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, TgUINT_E32_C uiFilter )
{
    psRequest->m_uiFilter_Objects = uiFilter;
}


/* ---- FCN_VO(tgCO_REQ_RQ_Ignore_Reset) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgCO_REQ_RQ_Ignore_Reset)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest )
{
    tgBF_Set_Flag_U32( &psRequest->m_bfFlags, ETgCO_FLAGS_IGNORE_ALL, false );
    psRequest->m_nuiConnection_Graph_Ignored = 0;
    psRequest->m_nuiConnection_Ignored = 0;
    psRequest->m_nuiNative_String = 0;
}


/* ---- FCN_VO(tgCO_REQ_Ignore_All) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgCO_REQ_Ignore_All)( VEC_OBJ_T(STg2_CO_Request,PC) psRequest, TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &psRequest->m_bfFlags, ETgCO_FLAGS_IGNORE_ALL, bFlag );
}


/* ---- FCN_VO(tgCO_REQ_Is_Ignored_All) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_REQ_Is_Ignored_All)( VEC_OBJ_T(STg2_CO_Request,CPC) psRequest )
{
    return (tgBF_Test_Flag_U32( &psRequest->m_bfFlags, ETgCO_FLAGS_IGNORE_ALL ));
}


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TGS_COLLISION_SYSTEM_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_SYSTEM_INL) */
#endif
