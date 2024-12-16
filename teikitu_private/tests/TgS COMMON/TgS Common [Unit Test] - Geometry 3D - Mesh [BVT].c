/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 3D - Mesh [BVT].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

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

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Reset) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Is_Valid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Support_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Volume) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Area) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Sweep_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Project) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Is_Contained) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Copy_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Init_MS) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Init_MS_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Init) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Copy) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Query_Indx_List) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Query_Vert_List) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Query_Indx_Count) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Query_Vert_Count) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Extern Test Setup Functions                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgVOID
FCN_V(UNIT_TEST__SETUP__MS_Init_VL)(
    VEC_OBJ_T(TgMESH_SIMPLE, PCU));

TgEXTN TgVOID
FCN_V(UNIT_TEST__SETUP__MS_Init_IL)(
    VEC_OBJ_T(TgMESH_SIMPLE, PCU));

TgEXTN TgVOID
FCN_V(UNIT_TEST__SETUP__MB_Init_IL)(
    VEC_OBJ_T(TgMESH_BVT,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_MB) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_MB) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Reset)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Is_Valid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Support_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Volume)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Area)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Sweep_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Project)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Is_Contained)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Copy_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Init_MS)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Init_MS_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Init)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Copy)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Query_Indx_List)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Query_Vert_List)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Query_Indx_Count)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MB_Query_Vert_Count)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Reset) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Reset) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;

    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Is_Valid) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;

    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_VO(tgGM_MB_Is_Valid)( &sMB0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Support_Point) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Support_Point) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_VO(tgGM_MB_Support_Point)( &sMB0, vV0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Volume) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Volume) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;

    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_VO(tgGM_MB_Volume)( &sMB0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Area) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Area) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;

    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_VO(tgGM_MB_Area)( &sMB0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_BA) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_BA) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_VO(tgGM_MB_BA)( &sBA0, &sMB0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Sweep_BA) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Sweep_BA) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_VO(tgGM_MB_Sweep_BA)( &sBA0, &sMB0, vV0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Project) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Project) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;
    VEC_T(1)                            vV0, vVal;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_VO(tgGM_MB_Project)( &vVal, &vVal, &sMB0, vV0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Is_Contained) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Is_Contained) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_VO(tgGM_MB_Is_Contained)( &sMB0, vS0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_TX) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_TX) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;
    VEC_T(3)                            xM0;

    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_VO(tgGM_MB_TX)( &sMB0, &xM0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Copy_TX) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Copy_TX) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0, sMB1;
    VEC_T(3)                            xM0;

    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_V(tgMH_CLI,3)( &xM0 );
    tgMM_Set_U08_0x00( &sMB1, sizeof( VEC_OBJ_T(TgMESH_BVT) ) );
    FCN_VO(tgGM_MB_Copy_TX)( &sMB1, &sMB0, &xM0 );

    FCN_VO(tgGM_MB_Reset)( &sMB0 );
    FCN_VO(tgGM_MB_Reset)( &sMB1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Init_MS) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Init_MS) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;
    VEC_OBJ_T(TgMESH_BVT)               sMB0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    tgMM_Set_U08_0x00( &sMB0, sizeof( VEC_OBJ_T(TgMESH_BVT) ) );
    FCN_VO(tgGM_MB_Init_MS)( &sMB0, &sMS0 );

    FCN_VO(tgGM_MS_Reset)( &sMS0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Init_MS_TX) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Init_MS_TX) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;
    VEC_T(3)                            xM0;
    VEC_OBJ_T(TgMESH_BVT)               sMB0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_V(tgMH_CLI,3)( &xM0 );
    tgMM_Set_U08_0x00( &sMB0, sizeof( VEC_OBJ_T(TgMESH_BVT) ) );
    FCN_VO(tgGM_MB_Init_MS_TX)( &sMB0, &sMS0, &xM0 );

    FCN_VO(tgGM_MS_Reset)( &sMS0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Init) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Init) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;

    tgMM_Set_U08_0x00( &sMB0, sizeof( sMB0 ) );
    FCN_VO(tgGM_MB_Init)( &sMB0, 9, 12 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Copy) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Copy) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0, sMB1;

    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    tgMM_Set_U08_0x00( &sMB1, sizeof( VEC_OBJ_T(TgMESH_BVT) ) );
    FCN_VO(tgGM_MB_Copy)( &sMB1, &sMB0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );
    FCN_VO(tgGM_MB_Reset)( &sMB1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Query_Indx_List) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Query_Indx_List) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;

    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_VO(tgGM_MB_Query_Indx_List)( &sMB0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Query_Vert_List) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Query_Vert_List) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;

    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    FCN_VO(tgGM_MB_Query_Vert_List)( &sMB0 );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Query_Indx_Count) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Query_Indx_Count) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;

    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    Test__Expect_EQ( TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX), FCN_VO(tgGM_MB_Query_Indx_Count)( &sMB0) );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MB_Query_Vert_Count) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MB_Query_Vert_Count) )
{
    VEC_OBJ_T(TgMESH_BVT)               sMB0;

    FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( &sMB0 );
    Test__Expect_EQ( TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX) >> 1, FCN_VO(tgGM_MB_Query_Vert_Count)( &sMB0 ) );
    FCN_VO(tgGM_MB_Reset)( &sMB0 );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__SETUP__MB_Init_IL) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_V(UNIT_TEST__SETUP__MB_Init_IL)( VEC_OBJ_T(TgMESH_BVT,PCU) psMT )
{
    tgMM_Set_U08_0x00( psMT, sizeof( VEC_OBJ_T(TgMESH_BVT) ) );

    FCN_VO(tgGM_MB_Init)( psMT, TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX) >> 1, TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX) );

    for (TgRSIZE uiVert = 0; uiVert < psMT->m_sMS.m_nuiVert; ++uiVert)
    {
        psMT->m_sMS.m_pvVert_List[uiVert].m_aData[0] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[0];
        psMT->m_sMS.m_pvVert_List[uiVert].m_aData[1] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[1];
        psMT->m_sMS.m_pvVert_List[uiVert].m_aData[2] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[2];
        psMT->m_sMS.m_pvVert_List[uiVert].m_aData[3] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[3];
    };

    tgMM_Copy( psMT->m_sMS.m_puiIndx_List, psMT->m_sMS.m_nuiIndx*sizeof( psMT->m_sMS.m_puiIndx_List[0] ), KTgGM_ICOSAHEDRON_PN_INDEX, sizeof( KTgGM_ICOSAHEDRON_PN_INDEX ) );
    TgERROR( psMT->m_sMS.m_nuiIndx*sizeof( psMT->m_sMS.m_puiIndx_List[0] ) >= sizeof( KTgGM_ICOSAHEDRON_PN_INDEX ) );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
