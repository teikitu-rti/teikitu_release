
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box-Linear.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOX_LINEAR_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCNI_VO(tgCO_BX_Clip) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCNI_VO(tgCO_BX_Clip)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    TgRESULT                            iResult = KTgE_FAIL;
    VEC_T(1)                            vT0, vT1, vK0, vK1;

    if ((psCL->m_nuiMax < 2) || (TgFAILED( iResult = FCNI_VO(tgCO_BX_Clip_PM)( &vT0, &vT1, psBX0, vS0, vD0 ) )))
    {
        psCL->m_nuiPoint = 0;
        return (iResult);
    }
    else
    {
        if (TEMPLATE__PRIM_0_CAP_0)
        {
            VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vT0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
            VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_LE)( vT1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ))
            {
                psCL->m_nuiPoint = 0;
                return (KTgE_NO_INTERSECT);
            };
        };

        if (TEMPLATE__PRIM_0_CAP_1)
        {
            VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vT0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );
            VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GT)( vT1, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ))
            {
                psCL->m_nuiPoint = 0;
                return (KTgE_NO_INTERSECT);
            };
        };

        vK0 = FCN_V(tgMH_MUL)( vT0, vD0 );
        vK1 = FCN_V(tgMH_MUL)( vT1, vD0 );

        psCL->m_avPoint[0] = FCN_V(tgMH_ADD)( vS0, vK0 );
        psCL->m_avPoint[1] = FCN_V(tgMH_ADD)( vS0, vK1 );
        psCL->m_nuiPoint = 2;

        return (KTgS_OK);
     };
}


/* ---- FCNI_VO(tgCO_BXF_Clip_PM) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCNI_VO(tgCO_BXF_Clip_PM)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_OBJ_T(TgBOX,CPC) psBX0, TgSINT_E32_C i0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_OBJ_T(TgRECTANGLE)              sFace;

    return (FCNI_VO(tgCO_RT_Clip_PM)( pvLN0, pvLN1, FCN_VO(tgCO_BXF_Init_Face)( &sFace, psBX0, i0 ), vS0, vD0 ));
}


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* =============================================================================================================================================================================== */

/*# !defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__PRIM_0_CAP_0 0
        #define TEMPLATE__PRIM_0_CAP_1 0
        #define TEMPLATE__PRIM_0 LR
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__PRIM_0_CAP_0 0
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__PRIM_0_CAP_0 1
        #define TEMPLATE__PRIM_0_CAP_1 0
        #define TEMPLATE__PRIM_0 LR
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__PRIM_0_CAP_0 1
        #define TEMPLATE__PRIM_0_CAP_1 1
        #define TEMPLATE__PRIM_0 LR
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 1
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TGS_COLLISION_BOX_LINEAR_INL


/*# !defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOX_LINEAR_INL) */
#endif
