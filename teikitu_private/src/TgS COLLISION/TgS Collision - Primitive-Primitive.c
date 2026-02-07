/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Primitive-Primitive.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD)
    #define TEMPLATE__VECTOR_DIM 4

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define ENABLE_RELOAD_GUARD
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
        #undef TEMPLATE__TYPE_SIZE
        #undef ENABLE_RELOAD_GUARD
    #endif

    #define TEMPLATE__TYPE_SIZE 32
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_PM_ClosestSq_PM) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PM_ClosestSq_PM)( VEC_T(1,PC) pvDistSq, VEC_T(1,PC) pvPM0, VEC_T(1,PC) pvPM1, 
                                       ETgPM_SHORT_C enPM0, VEC_OBJ_T(UTg2_CO_Primitive,CPC) puPM0, 
                                       ETgPM_SHORT_C enPM1, VEC_OBJ_T(UTg2_CO_Primitive,CPC) puPM1 )
{
    FCN_VO(TgCO_FCN_ClosestSq)          pfnCO_ClosestSq;

    TgPARAM_CHECK(nullptr != pvDistSq);
    TgPARAM_CHECK(nullptr != pvPM0);
    TgPARAM_CHECK(nullptr != pvPM1);
    TgPARAM_CHECK(nullptr != puPM0);
    TgPARAM_CHECK(nullptr != puPM1);

    if ((ETgPM_UNKNOWN >= enPM0) || (enPM0 >= ETgPM_MAX) || (ETgPM_UNKNOWN >= enPM1) || (enPM1 >= ETgPM_MAX))
    {
        return KTgE_FAIL;
    };

    pfnCO_ClosestSq = FCN_VO(g_apfnCO_ClosestSq)[enPM0][enPM1];

    if (nullptr == pfnCO_ClosestSq)
    {
        return KTgE_FAIL;
    };

    *pvDistSq = pfnCO_ClosestSq( pvPM0, pvPM1, puPM0, puPM1 );
    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_PM_Closest_PM) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PM_Closest_PM)( VEC_T(1,PC) pvDist, VEC_T(1,PC) pvPM0, VEC_T(1,PC) pvPM1, 
                                     ETgPM_SHORT_C enPM0, VEC_OBJ_T(UTg2_CO_Primitive,CPC) puPM0, 
                                     ETgPM_SHORT_C enPM1, VEC_OBJ_T(UTg2_CO_Primitive,CPC) puPM1 )
{
    FCN_VO(TgCO_FCN_Closest)            pfnCO_Closest;

    TgPARAM_CHECK(nullptr != pvDist);
    TgPARAM_CHECK(nullptr != pvPM0);
    TgPARAM_CHECK(nullptr != pvPM1);
    TgPARAM_CHECK(nullptr != puPM0);
    TgPARAM_CHECK(nullptr != puPM1);

    if ((ETgPM_UNKNOWN >= enPM0) || (enPM0 >= ETgPM_MAX) || (ETgPM_UNKNOWN >= enPM1) || (enPM1 >= ETgPM_MAX))
    {
        return KTgE_FAIL;
    };

    pfnCO_Closest = FCN_VO(g_apfnCO_Closest)[enPM0][enPM1];

    if (nullptr == pfnCO_Closest)
    {
        return KTgE_FAIL;
    };

    *pvDist = pfnCO_Closest( pvPM0, pvPM1, puPM0, puPM1 );
    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_PM_DistSq_PM) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PM_DistSq_PM)( VEC_T(1,PC) pvDistSq,
                                    ETgPM_SHORT_C enPM0, VEC_OBJ_T(UTg2_CO_Primitive,CPC) puPM0, 
                                    ETgPM_SHORT_C enPM1, VEC_OBJ_T(UTg2_CO_Primitive,CPC) puPM1 )
{
    FCN_VO(TgCO_FCN_DistSq)             pfnCO_DistSq;

    TgPARAM_CHECK(nullptr != pvDistSq);
    TgPARAM_CHECK(nullptr != puPM0);
    TgPARAM_CHECK(nullptr != puPM1);

    if ((ETgPM_UNKNOWN >= enPM0) || (enPM0 >= ETgPM_MAX) || (ETgPM_UNKNOWN >= enPM1) || (enPM1 >= ETgPM_MAX))
    {
        return KTgE_FAIL;
    };

    pfnCO_DistSq = FCN_VO(g_apfnCO_DistSq)[enPM0][enPM1];

    if (nullptr == pfnCO_DistSq)
    {
        return KTgE_FAIL;
    };

    *pvDistSq = pfnCO_DistSq( puPM0, puPM1 );
    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_PM_Dist_PM) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PM_Dist_PM)( VEC_T(1,PC) pvDist,
                                  ETgPM_SHORT_C enPM0, VEC_OBJ_T(UTg2_CO_Primitive,CPC) puPM0, 
                                  ETgPM_SHORT_C enPM1, VEC_OBJ_T(UTg2_CO_Primitive,CPC) puPM1 )
{
    FCN_VO(TgCO_FCN_Dist)               pfnCO_Dist;

    TgPARAM_CHECK(nullptr != pvDist);
    TgPARAM_CHECK(nullptr != puPM0);
    TgPARAM_CHECK(nullptr != puPM1);

    if ((ETgPM_UNKNOWN >= enPM0) || (enPM0 >= ETgPM_MAX) || (ETgPM_UNKNOWN >= enPM1) || (enPM1 >= ETgPM_MAX))
    {
        return KTgE_FAIL;
    };

    pfnCO_Dist = FCN_VO(g_apfnCO_Dist)[enPM0][enPM1];

    if (nullptr == pfnCO_Dist)
    {
        return KTgE_FAIL;
    };

    *pvDist = pfnCO_Dist( puPM0, puPM1 );
    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_PM_Penetrate_PM) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PM_Penetrate_PM)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket,
                                       ETgPM_SHORT_C enPM0, VEC_OBJ_T(UTg2_CO_Primitive,CPC) puPM0, 
                                       ETgPM_SHORT_C enPM1, VEC_OBJ_T(UTg2_CO_Primitive,CPC) puPM1 )
{
    FCN_VO(TgCO_FCN_Penetrate)          pfnCO_Penetrate;

    TgPARAM_CHECK(nullptr != psPacket);
    TgPARAM_CHECK(nullptr != puPM0);
    TgPARAM_CHECK(nullptr != puPM1);

    if ((ETgPM_UNKNOWN >= enPM0) || (enPM0 >= ETgPM_MAX) || (ETgPM_UNKNOWN >= enPM1) || (enPM1 >= ETgPM_MAX))
    {
        return KTgE_FAIL;
    };

    pfnCO_Penetrate = FCN_VO(g_apfnCO_Penetrate)[enPM0][enPM1];

    if (nullptr == pfnCO_Penetrate)
    {
        //TgDIAG(false);
        return KTgE_FAIL;
    };

    return (pfnCO_Penetrate( psPacket, puPM0, puPM1 ));
}


/* ---- FCN_VO(tgCO_PM_Sweep_PM_Supported) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgCO_PM_Sweep_PM_Supported)( ETgPM_SHORT_C enPM0, ETgPM_SHORT_C enPM1 )
{
    if ((ETgPM_UNKNOWN >= enPM0) || (enPM0 >= ETgPM_MAX) || (ETgPM_UNKNOWN >= enPM1) || (enPM1 >= ETgPM_MAX))
    {
        return false;
    };

    return (nullptr != FCN_VO(g_apfnCO_Sweep)[enPM0][enPM1]);
}


/* ---- FCN_VO(tgCO_PM_Sweep_PM) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PM_Sweep_PM)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,PC) pvTime, 
                                   ETgPM_SHORT_C enPM0, VEC_OBJ_T(UTg2_CO_Primitive,CPC) puPM0, 
                                   ETgPM_SHORT_C enPM1, VEC_OBJ_T(UTg2_CO_Primitive,CPC) puPM1, VEC_OBJ_T(TgDELTA,CPC) psΔt )
{
    FCN_VO(TgCO_FCN_Sweep)              pfnCO_Sweep;

    TgPARAM_CHECK(nullptr != psPacket);
    TgPARAM_CHECK(nullptr != pvTime);
    TgPARAM_CHECK(nullptr != puPM0);
    TgPARAM_CHECK(nullptr != puPM1);
    TgPARAM_CHECK(nullptr != psΔt);

    if ((ETgPM_UNKNOWN >= enPM0) || (enPM0 >= ETgPM_MAX) || (ETgPM_UNKNOWN >= enPM1) || (enPM1 >= ETgPM_MAX))
    {
        return KTgE_FAIL;
    };

    pfnCO_Sweep = FCN_VO(g_apfnCO_Sweep)[enPM0][enPM1];

    if (nullptr == pfnCO_Sweep)
    {
        return KTgE_FAIL;
    };

    return (pfnCO_Sweep( psPacket, pvTime, puPM0, puPM1, psΔt ));
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
