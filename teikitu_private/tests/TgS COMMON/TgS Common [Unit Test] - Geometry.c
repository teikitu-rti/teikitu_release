/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined(TGS_COMMON_GEOMETRY_H)

#include "../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h"


/* == Common ======================================================================================================================================================================*/

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.*/
/*  File Local Macros                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.*/

#define DECLARE_GEOM_TEST(A)                                                                                                                                                        \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_RT2D_##A);                                                                                                                            \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_BA_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_BX_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_CP_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_CI_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_CY_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_EL_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_LN_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_BA_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_MB_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_MS_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_PE_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_PC_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_PN_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_RY_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_RT_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_SG_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_SP_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_TS_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_CT_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_ET_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_PT_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_ST_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_TB_##A);                                                                                                                              \
    EXTN_METHOD_DECLARE(UNIT_TEST__TEST__GEOM_TYPE_##A);

#define SETUP_GEOM_TEST(A)                                                                                                                                                          \
    s_sTEST__GEOM_##A.m_pszSet = s_sSET__GEOM.m_szSet;                                                                                                                              \
    s_sTEST__GEOM_##A.m_pszCase = u8"Geom " #A;                                                                                                                                     \
    uiIndex = 0;                                                                                                                                                                    \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_RT2D_##A;                                                                                                          \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"RECTANGLE2D";                                                                                                                        \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_BA_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"BOXAA";                                                                                                                              \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_BX_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"BOX";                                                                                                                                \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_CP_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"CAPSULE";                                                                                                                            \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_CI_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"CIRCLE";                                                                                                                             \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_CY_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"CYLINDER";                                                                                                                           \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_EL_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"ELLIPSE";                                                                                                                            \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_LN_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"LINE";                                                                                                                               \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_BA_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"MESH_BA";                                                                                                                            \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_MB_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"MESH_BVT";                                                                                                                           \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_MS_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"MESH_SIMPLE";                                                                                                                        \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_PE_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"PARALLELOGRAM";                                                                                                                      \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_PC_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"PARTICLE";                                                                                                                           \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_PN_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"PLANE";                                                                                                                              \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_RY_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"RAY";                                                                                                                                \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_RT_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"RECTANGLE";                                                                                                                          \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_SG_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"SEGMENT";                                                                                                                            \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_SP_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"SPHERE";                                                                                                                             \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_TS_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"TORUS";                                                                                                                              \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_CT_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"CTRI";                                                                                                                               \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_ET_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"ETRI";                                                                                                                               \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_PT_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"PTRI";                                                                                                                               \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_ST_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"STRI";                                                                                                                               \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_TB_##A;                                                                                                            \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"TUBE";                                                                                                                               \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__GEOM_##A.m_pfnTest[uiIndex] = UNIT_TEST__TEST__GEOM_TYPE_##A;                                                                                                          \
    s_sTEST__GEOM_##A.m_apszTest[uiIndex] = u8"DELTA";                                                                                                                              \
    ++uiIndex;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

DECLARE_GEOM_TEST(F32_04_1)

#if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
DECLARE_GEOM_TEST(F64_04_1)
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.*/
/*  File Local Data */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.*/

static Test_Set                                             s_sSET__GEOM;

static Test_Case                                            s_sTEST__GEOM_F32_04_1;
static Test_Case                                            s_sTEST__GEOM_F64_04_1;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgVOID tgCM_Unit_Test_Register_GEOM( TgVOID )
{
    TgSINT_E32                          uiIndex;

    /* Initialize the unit test structures */

    Unit_Test__Set_Init( &s_sSET__GEOM );

    Unit_Test__Case_Init( &s_sTEST__GEOM_F32_04_1 );
    Unit_Test__Case_Init( &s_sTEST__GEOM_F64_04_1 );



    /* Configure the test set */

    s_sSET__GEOM.m_szSet = u8"Common: Geom";



    /* Configure the test cases */

    SETUP_GEOM_TEST(F32_04_1);
#if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
    SETUP_GEOM_TEST(F64_04_1);
#endif



    /* Register all of the test cases with the test set */

    Unit_Test__Set_Register_Case( &s_sSET__GEOM, &s_sTEST__GEOM_F32_04_1 );
    Unit_Test__Set_Register_Case( &s_sSET__GEOM, &s_sTEST__GEOM_F64_04_1 );



    /* Register the test set with the unit test system */

    Unit_Test__Register( &s_sSET__GEOM );
}

#else

TgEXTN TgVOID                               tgCM_Unit_Test_Register_GEOM(TgVOID);

TgVOID tgCM_Unit_Test_Register_GEOM( TgVOID ) {}

#endif

