/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision [Unit Test].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   4.51 | »GUID« A9981407-3EC9-42AF-8B6F-8BE6DD919615                                                                                                                 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static Test_Set                                             s_sSET__COLLISION;

static Test_Case                                            s_sTEST__COLLISION_F32_04;
static Test_Case                                            s_sTEST__COLLISION_F64_04;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Macros                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define SETUP_COLLISION_TEST(A)                                                                                                                                                     \
    s_sTEST__COLLISION_##A.m_pszSet = s_sSET__COLLISION.m_szSet;                                                                                                                    \
    s_sTEST__COLLISION_##A.m_pszCase = u8"Collision " #A;                                                                                                                             \
    uiIndex = 0;                                                                                                                                                                    \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_BOXAA_##A;                                                                                                          \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"BOXAA";                                                                                                                           \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_BOX_##A;                                                                                                            \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"BOX";                                                                                                                             \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_CAPSULE_##A;                                                                                                        \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"CAPSULE";                                                                                                                         \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_CIRCLE_##A;                                                                                                         \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"CIRCLE";                                                                                                                          \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_CYLINDER_##A;                                                                                                       \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"CYLINDER";                                                                                                                        \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_ELLIPSE_##A;                                                                                                        \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"ELLIPSE";                                                                                                                         \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_LINE_##A;                                                                                                           \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"LINE";                                                                                                                            \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_PARALLELOGRAM_##A;                                                                                                  \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"PARALLELOGRAM";                                                                                                                   \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_PLANE_##A;                                                                                                          \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"PLANE";                                                                                                                           \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_MESH_##A;                                                                                                           \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"MESH";                                                                                                                            \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_RAY_##A;                                                                                                            \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"RAY";                                                                                                                             \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_RECTANGLE_##A;                                                                                                      \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"RECTANGLE";                                                                                                                       \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_SEGMENT_##A;                                                                                                        \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"SEGMENT";                                                                                                                         \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_SPHERE_##A;                                                                                                         \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"SPHERE";                                                                                                                          \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_TRIANGLE_##A;                                                                                                       \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"TRIANGLE";                                                                                                                        \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_TUBE_##A;                                                                                                           \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"TUBE";                                                                                                                            \
    ++uiIndex;

/*
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_RECTANGLE2D_##A;                                                                                                    \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"RECTANGLE2D";                                                                                                                     \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_PARTICLE_##A;                                                                                                       \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"PARTICLE";                                                                                                                        \
    ++uiIndex;                                                                                                                                                                      \
    s_sTEST__COLLISION_##A.m_pfnTest[uiIndex] = TEST__COLLISION_TORUS_##A;                                                                                                          \
    s_sTEST__COLLISION_##A.m_apszTest[uiIndex] = u8"TORUS";                                                                                                                           \
    ++uiIndex;                                                                                                                                                                      \
    */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Main Execution                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
TgCLANG_WARN_DISABLE_PUSH(missing-prototypes)

TgVOID tgCM_Unit_Test_Register( TgVOID )
{
    //TgSINT_E32                          uiIndex;

    /* Initialize the unit test structures */

    Unit_Test__Set_Init( &s_sSET__COLLISION );

    Unit_Test__Case_Init( &s_sTEST__COLLISION_F32_04 );
    Unit_Test__Case_Init( &s_sTEST__COLLISION_F64_04 );



    /* Configure the test set */

    s_sSET__COLLISION.m_szSet = u8"Collision";



    /* Configure the test cases */

    //SETUP_COLLISION_TEST(F32_04);
    //SETUP_COLLISION_TEST(F64_04);



    /* Register all of the test cases with the test set */

    Unit_Test__Set_Register_Case( &s_sSET__COLLISION, &s_sTEST__COLLISION_F32_04 );
    Unit_Test__Set_Register_Case( &s_sSET__COLLISION, &s_sTEST__COLLISION_F64_04 );



    /* Register the test set with the unit test system */

    Unit_Test__Register( &s_sSET__COLLISION );
}

TgCLANG_WARN_DISABLE_POP(missing-prototypes)
