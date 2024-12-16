///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
///*  »Project«   Teikitu Gaming System (TgS) (∂)
//    »File«      TgS Collision - Circle-Point.c
//    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
//    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
///*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
///*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
//    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
//    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
//
//#if !defined (ENABLE_RELOAD_GUARD)
//    #define TEMPLATE__VECTOR_DIM 4
//    #define ENABLE_RELOAD_GUARD
//    #if !defined(TEMPLATE__TYPE_SIZE)
//        #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
//            #define TEMPLATE__TYPE_SIZE 64
//            #include __FILE__
//            #undef TEMPLATE__TYPE_SIZE
//        #endif
//        #define TEMPLATE__TYPE_SIZE 32
//    #endif
//    #undef ENABLE_RELOAD_GUARD
//#endif
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
//
//
///* == Collision ================================================================================================================================================================== */
//
///* ---- FCN_VO(tgCO_CI_ELEM_DistSq_PT) ------------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//VAR_T() FCN_VO(tgCO_CI_ELEM_DistSq_PT)( VEC_T(1,C) vCI_S0, VEC_T(1,C) vCI_N0, VAR_T(C) fRadius, VEC_T(1,C) vS0 )
//{
//    VEC_T(1,C)      vDS = FCN_V(tgMH_SUB)(pvS0, pvCI_S0);
//    VAR_T(C)        fDS_DS = FCN_V(tgMH_LSQ)( vDS );
//
//    TgERROR( FCN_V(tgMH_Is_Valid_Point)(pvCI_S0) && FCN_V(tgMH_Is_Valid_Vector)(pvCI_N0) && FCN_V(tgMH_Is_Valid_Point)(pvS0) );
//    TgERROR( !FCN_F(tgPM_NAN)(fRadius) && fRadius > TYPE_K(0) );
//
//    if (fDS_DS <= VAR_K(KTgEPS))
//    {   /* Quick Out - the point is within tolerance of circle origin. */
//        return (fRadius*fRadius);
//    }
//    else
//    {
//        VAR_T(C)        fDS_N = FCN_V(tgMH_DOT)( vDS, pvCI_N0);
//        VAR_T()                             fLenPDS;
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fDS_N, pvCI_N0);
//        VEC_T(1,C)      vK1 = FCN_V(tgMH_SUB)( vDS, vK0 );
//        VEC_T(1,C)      vPDS = FCN_V(tgMH_NORM_LEN)( fLenPDS, vK1 );
//
//        if (fLenPDS <= VAR_K(KTgEPS))
//        {   /* Quick Out - the point is directly above the origin */
//            return (fRadius*fRadius + fDS_N*fDS_N);
//        }
//        else
//        {
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fRadius, vPDS );
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_SUB)( vDS, vK2 );
//
//            return (FCN_V(tgMH_LSQ)( vK3 ));
//        };
//    };
//}
//
//
///* ---- FCN_VO(tgCO_CI_ELEM_ClosestSq_PT) ---------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//VAR_T() FCN_VO(tgCO_CI_ELEM_ClosestSq_PT)( VEC_T(1,PC) pvCI0, VEC_T(1,C) vCI_S0, VEC_T(1,C) vCI_N0, VAR_T(C) fRadius, VEC_T(1,C) vS0 )
//{
//    VEC_T(1,C)      vDS = FCN_V(tgMH_SUB)(pvS0, pvCI_S0);
//    VAR_T(C)        fDS_DS = FCN_V(tgMH_LSQ)( vDS );
//
//    TgERROR( FCN_V(tgMH_Is_Valid_Point)(pvCI_S0) && FCN_V(tgMH_Is_Valid_Vector)(pvCI_N0) && FCN_V(tgMH_Is_Valid_Point)(pvS0) );
//    TgERROR( !FCN_F(tgPM_NAN)(fRadius) && fRadius > TYPE_K(0) );
//
//    if (fDS_DS <= VAR_K(KTgEPS))
//    {   /* Quick Out - the point is within tolerance of circle origin. */
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_Init_Ortho)(pvCI_N0);
//        VEC_T(1,C)      vDirN = FCN_V(tgMH_NORM)( vK0 );
//        VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fRadius, vDirN );
//
//        *pvCI0 = FCN_V(tgMH_ADD)(pvCI_S0, vK1 );
//
//        return (fRadius*fRadius);
//    }
//    else
//    {
//        VAR_T(C)        fDS_N = FCN_V(tgMH_DOT)( vDS, pvCI_N0);
//        VAR_T()                             fLenPDS;
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fDS_N, pvCI_N0);
//        VEC_T(1,C)      vK1 = FCN_V(tgMH_SUB)( vDS, vK0 );
//        VEC_T(1,C)      vPDS = FCN_V(tgMH_NORM_LEN)( fLenPDS, vK1 );
//
//        if (fLenPDS <= VAR_K(KTgEPS))
//        {
//            /* The point is directly above the origin. Thus, every point on the circle is equidistant - make an arbitrary choice. */
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_Init_Ortho)(pvCI_N0);
//            VEC_T(1,C)      vDirN = FCN_V(tgMH_NORM)( vK2 );
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fRadius, vDirN );
//
//            *pvCI0 = FCN_V(tgMH_ADD)(pvCI_S0, vK3 );
//
//            return (fRadius*fRadius + fDS_N*fDS_N);
//        }
//        else
//        {
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fRadius, vPDS );
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_ADD)(pvCI_S0, vK2 );
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_SUB)(pvS0, vK3 );
//
//            *pvCI0 = vK3;
//
//            return (FCN_V(tgMH_LSQ)( vK4 ));
//        };
//    };
//}
//
//
///* =============================================================================================================================================================================== */
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
