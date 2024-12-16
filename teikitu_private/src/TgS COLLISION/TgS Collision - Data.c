/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Data.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD)
    #define TEMPLATE__VECTOR_DIM 4
    #define ENABLE_RELOAD_GUARD
    #if !defined(TEMPLATE__TYPE_SIZE)
        #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
            #define TEMPLATE__TYPE_SIZE 64
            #include __FILE__
            #undef TEMPLATE__TYPE_SIZE
        #endif
        #define TEMPLATE__TYPE_SIZE 32
    #endif
    #undef ENABLE_RELOAD_GUARD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
TgWARN_DISABLE_PUSH(,cast-function-type-strict)


/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Private Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

FCN_VO(TgCO_FCN_ClosestSq)                  FCN_VO(g_apfnCO_ClosestSq)[ETgPM_MAX][ETgPM_MAX];
FCN_VO(TgCO_FCN_Closest)                    FCN_VO(g_apfnCO_Closest)[ETgPM_MAX][ETgPM_MAX];
FCN_VO(TgCO_FCN_DistSq)                     FCN_VO(g_apfnCO_DistSq)[ETgPM_MAX][ETgPM_MAX];
FCN_VO(TgCO_FCN_Dist)                       FCN_VO(g_apfnCO_Dist)[ETgPM_MAX][ETgPM_MAX];
FCN_VO(TgCO_FCN_Penetrate)                  FCN_VO(g_apfnCO_Penetrate)[ETgPM_MAX][ETgPM_MAX];
FCN_VO(TgCO_FCN_Sweep)                      FCN_VO(g_apfnCO_Sweep)[ETgPM_MAX][ETgPM_MAX];
FCN_VO(TgCO_FCN_Test)                       FCN_VO(g_apfnCO_Test)[ETgPM_MAX][ETgPM_MAX];

// FCN_VO(TgCO_FCN_TEST_SWEEP)                 FCN_VO(g_apfnCO_Test_Sweep)[ETgPM_MAX][ETgPM_MAX];
// FCN_VO(TgCO_FCN_SWEEP_PENETRATE)            FCN_VO(g_apfnCO_Sweep_Penetrate)[ETgPM_MAX][ETgPM_MAX];




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Private Functions for Data Setup                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
#define FCN_VO_CO(A,B,C,D) FCN_VO(g_apfnCO_##C)[ETgPM_##B][ETgPM_##D] = (FCN_VO(TgCO_FCN_##C))FCN_VO(A##_##B##_##C##_##D)

TgVOID FCN_VO(tgCO_FCN_Matrix_Setup_ClosestSq)( TgVOID )
{
    tgMM_Set_U08_0x00( FCN_VO(g_apfnCO_ClosestSq), sizeof(FCN_VO(g_apfnCO_ClosestSq)) );
    // FCN_VO_CO(tgCO,BA,ClosestSq,BA);
    // FCN_VO_CO(tgCO,PE,ClosestSq,PE);
    // FCN_VO_CO(tgCO,PE,ClosestSq,LN);
    // FCN_VO_CO(tgCO,CI,ClosestSq,CI);
    // FCN_VO_CO(tgCO,CI,ClosestSq,LN);
    // FCN_VO_CO(tgCO,PE,ClosestSq,RY);
    // FCN_VO_CO(tgCO,RY,ClosestSq,SG);
    // FCN_VO_CO(tgCO,SG,ClosestSq,LN);
    // FCN_VO_CO(tgCO,CI,ClosestSq,RY);
    // FCN_VO_CO(tgCO,CI,ClosestSq,SG);
    // FCN_VO_CO(tgCO,PE,ClosestSq,SG);
    // FCN_VO_CO(tgCO,PE,ClosestSq,ST);
    // FCN_VO_CO(tgCO,SP,ClosestSq,SG);
    // FCN_VO_CO(tgCO,PE,ClosestSq,RT);
    // FCN_VO_CO(tgCO,SP,ClosestSq,SP);
    // FCN_VO_CO(tgCO,ST,ClosestSq,LN);
    // FCN_VO_CO(tgCO,BX,ClosestSq,SP);
    // FCN_VO_CO(tgCO,BX,ClosestSq,SG);
    // FCN_VO_CO(tgCO,BX,ClosestSq,RY);
    // FCN_VO_CO(tgCO,RY,ClosestSq,RY);
    // FCN_VO_CO(tgCO,PN,ClosestSq,RY);
    // FCN_VO_CO(tgCO,CY,ClosestSq,PN);
    // FCN_VO_CO(tgCO,LN,ClosestSq,SG);
    // FCN_VO_CO(tgCO,LN,ClosestSq,RY);
    // FCN_VO_CO(tgCO,SG,ClosestSq,SG);
    // FCN_VO_CO(tgCO,SG,ClosestSq,RY);
    // FCN_VO_CO(tgCO,RT,ClosestSq,ST);
    // FCN_VO_CO(tgCO,BX,ClosestSq,LN);
    // FCN_VO_CO(tgCO,SP,ClosestSq,ET);
    // FCN_VO_CO(tgCO,SP,ClosestSq,LN);
    // FCN_VO_CO(tgCO,PN,ClosestSq,LN);
    // FCN_VO_CO(tgCO,RY,ClosestSq,LN);
    // FCN_VO_CO(tgCO,RT,ClosestSq,SG);
    // FCN_VO_CO(tgCO,SP,ClosestSq,PN);
    // FCN_VO_CO(tgCO,CP,ClosestSq,CP);
    // FCN_VO_CO(tgCO,CP,ClosestSq,LN);
    // FCN_VO_CO(tgCO,SP,ClosestSq,RY);
    // FCN_VO_CO(tgCO,ST,ClosestSq,RY);
    // FCN_VO_CO(tgCO,ST,ClosestSq,SG);
    // FCN_VO_CO(tgCO,CP,ClosestSq,PN);
    // FCN_VO_CO(tgCO,BX,ClosestSq,PN);
    // FCN_VO_CO(tgCO,CP,ClosestSq,SG);
    // FCN_VO_CO(tgCO,CP,ClosestSq,SP);
    // FCN_VO_CO(tgCO,CP,ClosestSq,ST);
    // FCN_VO_CO(tgCO,LN,ClosestSq,LN);
    // FCN_VO_CO(tgCO,ST,ClosestSq,ST);
    // FCN_VO_CO(tgCO,BA,ClosestSq,SP);
    // FCN_VO_CO(tgCO,RT,ClosestSq,LN);
    // FCN_VO_CO(tgCO,PN,ClosestSq,SG);
    // FCN_VO_CO(tgCO,RT,ClosestSq,RT);
    // FCN_VO_CO(tgCO,RT,ClosestSq,RY);
    // FCN_VO_CO(tgCO,BA,ClosestSq,PN);
    // FCN_VO_CO(tgCO,CP,ClosestSq,RY);
}

TgVOID FCN_VO(tgCO_FCN_Matrix_Setup_Closest)( TgVOID )
{
    tgMM_Set_U08_0x00( FCN_VO(g_apfnCO_Closest), sizeof(FCN_VO(g_apfnCO_Closest)) );
    // FCN_VO_CO(tgCO,CP,Closest,SP);
    // FCN_VO_CO(tgCO,CP,Closest,SG);
    // FCN_VO_CO(tgCO,CP,Closest,RY);
    // FCN_VO_CO(tgCO,RY,Closest,LN);
    // FCN_VO_CO(tgCO,PE,Closest,ST);
    // FCN_VO_CO(tgCO,CP,Closest,PN);
    // FCN_VO_CO(tgCO,PE,Closest,SG);
    // FCN_VO_CO(tgCO,RT,Closest,ST);
    // FCN_VO_CO(tgCO,RT,Closest,SG);
    // FCN_VO_CO(tgCO,RT,Closest,RY);
    // FCN_VO_CO(tgCO,RT,Closest,RT);
    // FCN_VO_CO(tgCO,CI,Closest,LN);
    // FCN_VO_CO(tgCO,PE,Closest,RY);
    // FCN_VO_CO(tgCO,PE,Closest,RT);
    // FCN_VO_CO(tgCO,CP,Closest,LN);
    // FCN_VO_CO(tgCO,CI,Closest,SG);
    // FCN_VO_CO(tgCO,CI,Closest,RY);
    // FCN_VO_CO(tgCO,CP,Closest,CP);
    // FCN_VO_CO(tgCO,SG,Closest,LN);
    // FCN_VO_CO(tgCO,PN,Closest,RY);
    // FCN_VO_CO(tgCO,LN,Closest,LN);
    // FCN_VO_CO(tgCO,CI,Closest,CI);
    // FCN_VO_CO(tgCO,LN,Closest,RY);
    // FCN_VO_CO(tgCO,RY,Closest,RY);
    // FCN_VO_CO(tgCO,RY,Closest,SG);
    // FCN_VO_CO(tgCO,LN,Closest,SG);
    // FCN_VO_CO(tgCO,SG,Closest,RY);
    // FCN_VO_CO(tgCO,SG,Closest,SG);
    // FCN_VO_CO(tgCO,SP,Closest,ET);
    // FCN_VO_CO(tgCO,SP,Closest,LN);
    // FCN_VO_CO(tgCO,SP,Closest,PN);
    // FCN_VO_CO(tgCO,SP,Closest,RY);
    // FCN_VO_CO(tgCO,SP,Closest,SG);
    // FCN_VO_CO(tgCO,PN,Closest,SG);
    // FCN_VO_CO(tgCO,BX,Closest,SP);
    // FCN_VO_CO(tgCO,BX,Closest,SG);
    // FCN_VO_CO(tgCO,BX,Closest,RY);
    // FCN_VO_CO(tgCO,BX,Closest,PN);
    // FCN_VO_CO(tgCO,SP,Closest,SP);
    // FCN_VO_CO(tgCO,BX,Closest,LN);
    // FCN_VO_CO(tgCO,CY,Closest,PN);
    // FCN_VO_CO(tgCO,PN,Closest,LN);
    // FCN_VO_CO(tgCO,PE,Closest,PE);
    // FCN_VO_CO(tgCO,PE,Closest,LN);
    // FCN_VO_CO(tgCO,ST,Closest,LN);
    // FCN_VO_CO(tgCO,ST,Closest,RY);
    // FCN_VO_CO(tgCO,ST,Closest,SG);
    // FCN_VO_CO(tgCO,ST,Closest,ST);
    // FCN_VO_CO(tgCO,BA,Closest,SP);
    // FCN_VO_CO(tgCO,BA,Closest,PN);
    // FCN_VO_CO(tgCO,BA,Closest,BA);
    // FCN_VO_CO(tgCO,RT,Closest,LN);
    // FCN_VO_CO(tgCO,CP,Closest,ST);
}

TgVOID FCN_VO(tgCO_FCN_Matrix_Setup_DistSq)( TgVOID )
{
    tgMM_Set_U08_0x00( FCN_VO(g_apfnCO_DistSq), sizeof(FCN_VO(g_apfnCO_DistSq)) );
    // FCN_VO_CO(tgCO,SG,DistSq,LN);
    // FCN_VO_CO(tgCO,SG,DistSq,SG);
    // FCN_VO_CO(tgCO,BA,DistSq,BA);
    // FCN_VO_CO(tgCO,BA,DistSq,PN);
    // FCN_VO_CO(tgCO,BA,DistSq,SP);
    // FCN_VO_CO(tgCO,BX,DistSq,LN);
    // FCN_VO_CO(tgCO,BX,DistSq,PN);
    // FCN_VO_CO(tgCO,BX,DistSq,RY);
    // FCN_VO_CO(tgCO,BX,DistSq,SG);
    // FCN_VO_CO(tgCO,BX,DistSq,SP);
    // FCN_VO_CO(tgCO,CI,DistSq,CI);
    // FCN_VO_CO(tgCO,CI,DistSq,LN);
    // FCN_VO_CO(tgCO,CI,DistSq,RY);
    // FCN_VO_CO(tgCO,SP,DistSq,ET);
    // FCN_VO_CO(tgCO,SP,DistSq,LN);
    // FCN_VO_CO(tgCO,SP,DistSq,PN);
    // FCN_VO_CO(tgCO,SP,DistSq,RY);
    // FCN_VO_CO(tgCO,SP,DistSq,SG);
    // FCN_VO_CO(tgCO,SP,DistSq,SP);
    // FCN_VO_CO(tgCO,CI,DistSq,SG);
    // FCN_VO_CO(tgCO,CP,DistSq,CP);
    // FCN_VO_CO(tgCO,CP,DistSq,LN);
    // FCN_VO_CO(tgCO,CP,DistSq,PN);
    // FCN_VO_CO(tgCO,CP,DistSq,RY);
    // FCN_VO_CO(tgCO,CP,DistSq,SG);
    // FCN_VO_CO(tgCO,CP,DistSq,SP);
    // FCN_VO_CO(tgCO,CP,DistSq,ST);
    // FCN_VO_CO(tgCO,CY,DistSq,PN);
    // FCN_VO_CO(tgCO,LN,DistSq,LN);
    // FCN_VO_CO(tgCO,LN,DistSq,RY);
    // FCN_VO_CO(tgCO,LN,DistSq,SG);
    // FCN_VO_CO(tgCO,PE,DistSq,LN);
    // FCN_VO_CO(tgCO,PE,DistSq,PE);
    // FCN_VO_CO(tgCO,PE,DistSq,RT);
    // FCN_VO_CO(tgCO,PE,DistSq,RY);
    // FCN_VO_CO(tgCO,PE,DistSq,SG);
    // FCN_VO_CO(tgCO,PE,DistSq,ST);
    // FCN_VO_CO(tgCO,SG,DistSq,RY);
    // FCN_VO_CO(tgCO,PN,DistSq,LN);
    // FCN_VO_CO(tgCO,PN,DistSq,RY);
    // FCN_VO_CO(tgCO,PN,DistSq,SG);
    // FCN_VO_CO(tgCO,RT,DistSq,LN);
    // FCN_VO_CO(tgCO,ST,DistSq,LN);
    // FCN_VO_CO(tgCO,ST,DistSq,RY);
    // FCN_VO_CO(tgCO,ST,DistSq,SG);
    // FCN_VO_CO(tgCO,ST,DistSq,ST);
    // FCN_VO_CO(tgCO,RT,DistSq,RT);
    // FCN_VO_CO(tgCO,RT,DistSq,RY);
    // FCN_VO_CO(tgCO,RT,DistSq,SG);
    // FCN_VO_CO(tgCO,RT,DistSq,ST);
    // FCN_VO_CO(tgCO,RY,DistSq,LN);
    // FCN_VO_CO(tgCO,RY,DistSq,RY);
    // FCN_VO_CO(tgCO,RY,DistSq,SG);
}

TgVOID FCN_VO(tgCO_FCN_Matrix_Setup_Dist)( TgVOID )
{
    tgMM_Set_U08_0x00( FCN_VO(g_apfnCO_Dist), sizeof(FCN_VO(g_apfnCO_Dist)) );
    // FCN_VO_CO(tgCO,PE,Dist,SG);
    // FCN_VO_CO(tgCO,PE,Dist,RY);
    // FCN_VO_CO(tgCO,PE,Dist,RT);
    // FCN_VO_CO(tgCO,PE,Dist,PE);
    // FCN_VO_CO(tgCO,PE,Dist,LN);
    // FCN_VO_CO(tgCO,RT,Dist,LN);
    // FCN_VO_CO(tgCO,RT,Dist,RT);
    // FCN_VO_CO(tgCO,RT,Dist,RY);
    // FCN_VO_CO(tgCO,RT,Dist,SG);
    // FCN_VO_CO(tgCO,RT,Dist,ST);
    // FCN_VO_CO(tgCO,SG,Dist,SG);
    // FCN_VO_CO(tgCO,SG,Dist,RY);
    // FCN_VO_CO(tgCO,SP,Dist,ET);
    // FCN_VO_CO(tgCO,PE,Dist,ST);
    // FCN_VO_CO(tgCO,PN,Dist,LN);
    // FCN_VO_CO(tgCO,SG,Dist,LN);
    // FCN_VO_CO(tgCO,CP,Dist,SG);
    // FCN_VO_CO(tgCO,BX,Dist,RY);
    // FCN_VO_CO(tgCO,ST,Dist,SG);
    // FCN_VO_CO(tgCO,CI,Dist,SG);
    // FCN_VO_CO(tgCO,CP,Dist,ST);
    // FCN_VO_CO(tgCO,CP,Dist,SP);
    // FCN_VO_CO(tgCO,BX,Dist,SG);
    // FCN_VO_CO(tgCO,CP,Dist,RY);
    // FCN_VO_CO(tgCO,BX,Dist,SP);
    // FCN_VO_CO(tgCO,PN,Dist,SG);
    // FCN_VO_CO(tgCO,CI,Dist,CI);
    // FCN_VO_CO(tgCO,CI,Dist,LN);
    // FCN_VO_CO(tgCO,RY,Dist,LN);
    // FCN_VO_CO(tgCO,RY,Dist,RY);
    // FCN_VO_CO(tgCO,RY,Dist,SG);
    // FCN_VO_CO(tgCO,PN,Dist,RY);
    // FCN_VO_CO(tgCO,LN,Dist,LN);
    // FCN_VO_CO(tgCO,LN,Dist,RY);
    // FCN_VO_CO(tgCO,LN,Dist,SG);
    // FCN_VO_CO(tgCO,CP,Dist,PN);
    // FCN_VO_CO(tgCO,CP,Dist,LN);
    // FCN_VO_CO(tgCO,CP,Dist,CP);
    // FCN_VO_CO(tgCO,CI,Dist,RY);
    // FCN_VO_CO(tgCO,SP,Dist,SP);
    // FCN_VO_CO(tgCO,BX,Dist,PN);
    // FCN_VO_CO(tgCO,BX,Dist,LN);
    // FCN_VO_CO(tgCO,SP,Dist,SG);
    // FCN_VO_CO(tgCO,SP,Dist,RY);
    // FCN_VO_CO(tgCO,SP,Dist,PN);
    // FCN_VO_CO(tgCO,SP,Dist,LN);
    // FCN_VO_CO(tgCO,BA,Dist,SP);
    // FCN_VO_CO(tgCO,BA,Dist,PN);
    // FCN_VO_CO(tgCO,BA,Dist,BA);
    // FCN_VO_CO(tgCO,CY,Dist,PN);
    // FCN_VO_CO(tgCO,ST,Dist,LN);
    // FCN_VO_CO(tgCO,ST,Dist,RY);
    // FCN_VO_CO(tgCO,ST,Dist,ST);
}


TgVOID FCN_VO(tgCO_FCN_Matrix_Setup_Penetrate)( TgVOID )
{
    tgMM_Set_U08_0x00( FCN_VO(g_apfnCO_Penetrate), sizeof(FCN_VO(g_apfnCO_Penetrate)) );
    // FCN_VO_CO(tgCO,BA,Penetrate,SP);
    // FCN_VO_CO(tgCO,BA,Penetrate,BA);
    FCN_VO_CO(tgCO,BX,Penetrate,PN);
    FCN_VO_CO(tgCO,BX,Penetrate,SP);
    // FCN_VO_CO(tgCO,BX,Penetrate,CY);
    FCN_VO_CO(tgCO,CP,Penetrate,PN);
    // FCN_VO_CO(tgCO,CP,Penetrate,SP);
    // FCN_VO_CO(tgCO,CP,Penetrate,CY);
    // FCN_VO_CO(tgCO,CP,Penetrate,CP);
    // FCN_VO_CO(tgCO,CY,Penetrate,CY);
    // FCN_VO_CO(tgCO,LN,Penetrate,CP);
    //FCN_VO_CO(tgCO,PN,Penetrate,BA);
    FCN_VO_CO(tgCO,PN,Penetrate,BX);
    // FCN_VO_CO(tgCO,PN,Penetrate,CY);
    FCN_VO_CO(tgCO,PN,Penetrate,SP);
    FCN_VO_CO(tgCO,PN,Penetrate,CP);
    // FCN_VO_CO(tgCO,RY,Penetrate,CP);
    // FCN_VO_CO(tgCO,SG,Penetrate,CP);
    FCN_VO_CO(tgCO,SP,Penetrate,SP);
    FCN_VO_CO(tgCO,SP,Penetrate,BA);
    FCN_VO_CO(tgCO,SP,Penetrate,BX);
    FCN_VO_CO(tgCO,SP,Penetrate,CY);
    FCN_VO_CO(tgCO,SP,Penetrate,LN);
    FCN_VO_CO(tgCO,SP,Penetrate,PN);
    FCN_VO_CO(tgCO,SP,Penetrate,RY);
    FCN_VO_CO(tgCO,SP,Penetrate,SG);
    FCN_VO_CO(tgCO,SP,Penetrate,ST);
    // FCN_VO_CO(tgCO,ST,Penetrate,BX);
    // FCN_VO_CO(tgCO,ST,Penetrate,CI);
    // FCN_VO_CO(tgCO,ST,Penetrate,CP);
    // FCN_VO_CO(tgCO,ST,Penetrate,CY);
    // FCN_VO_CO(tgCO,ST,Penetrate,SP);
}


TgVOID FCN_VO(tgCO_FCN_Matrix_Setup_Sweep)( TgVOID )
{
    tgMM_Set_U08_0x00( FCN_VO(g_apfnCO_Sweep), sizeof(FCN_VO(g_apfnCO_Sweep)) );
    // FCN_VO_CO(tgCO,ET,Sweep,PC);
    FCN_VO_CO(tgCO,PN,Sweep,SP);
    // FCN_VO_CO(tgCO,PN,Sweep,BA);
    // FCN_VO_CO(tgCO,PN,Sweep,CP);
    FCN_VO_CO(tgCO,SP,Sweep,TB);
    FCN_VO_CO(tgCO,SP,Sweep,SP);
    //FCN_VO_CO(tgCO,SP,Sweep,ST);
    // FCN_VO_CO(tgCO,ST,Sweep,BX);
    // FCN_VO_CO(tgCO,ST,Sweep,ST);
    FCN_VO_CO(tgCO,TB,Sweep,SP);
    // FCN_VO_CO(tgCO,TB,Sweep,TB);
}


TgVOID FCN_VO(tgCO_FCN_Matrix_Setup_Test)( TgVOID )
{
    tgMM_Set_U08_0x00( FCN_VO(g_apfnCO_Test), sizeof(FCN_VO(g_apfnCO_Test)) );
    // FCN_VO_CO(tgCO,RY,Test,SG);
    // FCN_VO_CO(tgCO,RY,Test,RY);
    // FCN_VO_CO(tgCO,RY,Test,LN);
    // FCN_VO_CO(tgCO,ET,Test,SG);
    // FCN_VO_CO(tgCO,ET,Test,LN);
    // FCN_VO_CO(tgCO,LN,Test,LN);
    // FCN_VO_CO(tgCO,LN,Test,RY);
    // FCN_VO_CO(tgCO,LN,Test,SG);
    // FCN_VO_CO(tgCO,ET,Test,RY);
    // FCN_VO_CO(tgCO,CP,Test,CP);
    // FCN_VO_CO(tgCO,CP,Test,LN);
    // FCN_VO_CO(tgCO,RT,Test,SG);
    // FCN_VO_CO(tgCO,PE,Test,SG);
    // FCN_VO_CO(tgCO,SP,Test,ET);
    // FCN_VO_CO(tgCO,RT,Test,LN);
    // FCN_VO_CO(tgCO,SP,Test,LN);
    // FCN_VO_CO(tgCO,PE,Test,LN);
    // FCN_VO_CO(tgCO,SP,Test,PN);
    // FCN_VO_CO(tgCO,BA,Test,BA);
    // FCN_VO_CO(tgCO,BA,Test,PN);
    // FCN_VO_CO(tgCO,BA,Test,SP);
    // FCN_VO_CO(tgCO,SG,Test,SG);
    // FCN_VO_CO(tgCO,SG,Test,RY);
    // FCN_VO_CO(tgCO,SP,Test,RY);
    // FCN_VO_CO(tgCO,SP,Test,SG);
    // FCN_VO_CO(tgCO,SP,Test,SP);
    // FCN_VO_CO(tgCO,PN,Test,LN);
    // FCN_VO_CO(tgCO,ST,Test,ST);
    // FCN_VO_CO(tgCO,CP,Test,ST);
    // FCN_VO_CO(tgCO,CP,Test,SP);
    // FCN_VO_CO(tgCO,CP,Test,SG);
    // FCN_VO_CO(tgCO,RT,Test,RY);
    // FCN_VO_CO(tgCO,PE,Test,RY);
    // FCN_VO_CO(tgCO,PN,Test,RY);
    // FCN_VO_CO(tgCO,PN,Test,SG);
    // FCN_VO_CO(tgCO,SG,Test,LN);
    // FCN_VO_CO(tgCO,CP,Test,PN);
    // FCN_VO_CO(tgCO,CP,Test,RY);
}



/* =============================================================================================================================================================================== */

TgWARN_DISABLE_POP()
#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
