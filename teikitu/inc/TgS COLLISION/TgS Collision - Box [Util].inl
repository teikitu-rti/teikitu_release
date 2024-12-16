/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box [Util].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOX_UTIL_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */


/* ---- FCN_VO(tgCO_BX_Clip_Points) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BX_Clip_Points)( VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_T(1,C) vS0, VEC_T(1,C) vS1 )
{
    VEC_T(1,C)                          vD0 = FCN_V(tgMH_SUB)( vS1, vS0 );

    return (FCN_VO(tgCO_BX_Clip_PM_LR11)( pvSG0, pvSG1, psBX0, vS0, vD0 ));
}


/* ---- FCN_VO(tgCO_BXF_Init_Face) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_OBJ_T(TgRECTANGLE,P) FCN_VO(tgCO_BXF_Init_Face)( VEC_OBJ_T(TgRECTANGLE,PC) psRT0, VEC_OBJ_T(TgBOX,CPC) psBX0, TgSINT_F32_C i0 )
{
    VEC_T(1)                            vK0, vK1, vK2;

    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SPX)( psBX0->m_vExtent );
    VEC_T(1,C)                          vY0 = FCN_V(tgMH_SPY)( psBX0->m_vExtent );
    VEC_T(1,C)                          vZ0 = FCN_V(tgMH_SPZ)( psBX0->m_vExtent );

    switch (i0)
    {
        case 0:
            vK0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vX0, vY0, vZ0 );
            vK1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_NEG)( vY0 ), FCN_VO(tgGM_BX_Query_Axis_Unit_1)( psBX0 ) );
            vK2 = FCN_V(tgMH_MUL)( FCN_V(tgMH_NEG)( vZ0 ), FCN_VO(tgGM_BX_Query_Axis_Unit_2)( psBX0 ) );
            FCN_VO(tgGM_RT_Init_SEN)( psRT0, vK0, vK1, vK2, FCN_VO(tgGM_BX_Query_Axis_Unit_0)( psBX0 ) );
            break;
        case 1:
            vK0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vX0, vY0, vZ0 );
            vK1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_NEG)( vX0 ), FCN_VO(tgGM_BX_Query_Axis_Unit_0)( psBX0 ) );
            vK2 = FCN_V(tgMH_MUL)( FCN_V(tgMH_NEG)( vZ0 ), FCN_VO(tgGM_BX_Query_Axis_Unit_2)( psBX0 ) );
            FCN_VO(tgGM_RT_Init_SEN)( psRT0, vK0, vK1, vK2, FCN_VO(tgGM_BX_Query_Axis_Unit_1)( psBX0 ) );
            break;
        case 2:
            vK0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vX0, vY0, vZ0 );
            vK1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_NEG)( vX0 ), FCN_VO(tgGM_BX_Query_Axis_Unit_0)( psBX0 ) );
            vK2 = FCN_V(tgMH_MUL)( FCN_V(tgMH_NEG)( vY0 ), FCN_VO(tgGM_BX_Query_Axis_Unit_1)( psBX0 ) );
            FCN_VO(tgGM_RT_Init_SEN)( psRT0, vK0, vK1, vK2, FCN_VO(tgGM_BX_Query_Axis_Unit_2)( psBX0 ) );
            break;
        default:
            TgS_NO_DEFAULT(break);
    };

    return (psRT0);
}


/* ---- FCN_VO(tgCO_BXF_Clip) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BXF_Clip)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgBOX,CPC) psBX0, TgSINT_F32_C i0 )
{
    VEC_OBJ_T(TgRECTANGLE)              sFace;

    return (FCN_VO(tgCO_RT_Clip)( psCL, FCN_VO(tgCO_BXF_Init_Face)( &sFace, psBX0, i0 ) ));
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

    #define TGS_COLLISION_BOX_UTIL_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOX_UTIL_INL) */
#endif
