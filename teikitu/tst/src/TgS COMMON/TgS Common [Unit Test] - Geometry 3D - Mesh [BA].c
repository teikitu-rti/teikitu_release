/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 3D - Mesh [BA].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
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

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Reset) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Is_Valid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Support_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Volume) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Area) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Sweep_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Project) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Is_Contained) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Copy_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Init) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS_TX_TL) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS_TX_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Copy) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_CG_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_Indx_List) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_Vert_List) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_Indx_Count) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_Vert_Count) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_CG_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_CG_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_DT) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_BA_VL) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_BA_IL) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_CG_BA_VL) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_CG_BA_IL) );




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
FCN_V(UNIT_TEST__SETUP__MA_Init_VL)(
    VEC_OBJ_T(TgMESH_BA,PCU) );

TgEXTN TgVOID
FCN_V(UNIT_TEST__SETUP__MA_Init_IL)(
    VEC_OBJ_T(TgMESH_BA,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_MA) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_MA) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Reset)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Is_Valid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Support_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Volume)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Area)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Sweep_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Project)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Is_Contained)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Copy_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Init)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS_TX_TL)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS_TX_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Copy)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_CG_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Query_Indx_List)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Query_Vert_List)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Query_Indx_Count)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Query_Vert_Count)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Query_CG_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Query_CG_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Query_DT)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_BA_VL)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_BA_IL)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_CG_BA_VL)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_CG_BA_IL)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Reset) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Reset) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Is_Valid) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Is_Valid)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Support_Point) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Support_Point) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Support_Point)( &sMA0, vV0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Volume) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Volume) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Volume)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Area) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Area) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Area)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_BA) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_BA) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_BA)( &sBA0, &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Sweep_BA) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Sweep_BA) )
{
    VEC_T(1)                            vV0;
    VEC_OBJ_T(TgMESH_BA)                sMA0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Sweep_BA)( &sBA0, &sMA0, vV0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Project) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Project) )
{
    VEC_T(1)                            vV0, vVal;
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Project)( &vVal, &vVal, &sMA0, vV0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Is_Contained) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Is_Contained) )
{
    VEC_T(1)                            vS0;
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Is_Contained)( &sMA0, vS0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_TX) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_TX) )
{
    VEC_T(3)                            xM0;
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_TX)( &sMA0, &xM0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Copy_TX) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Copy_TX) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0, sMA1;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Copy_TX)( &sMA1, &sMA0, &xM0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Init) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Init) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );

    FCN_VO(tgGM_MA_Init)( &sMA0, 9, 12, ETgSWEEP_STATIC );
    for (TgRSIZE uiIndex = 0; uiIndex < sMA0.m_sMS.m_nuiVert; ++uiIndex)
    {
        sMA0.m_sMS.m_pvVert_List[uiIndex] = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    };
    for (TgRSIZE uiIndex = 0; uiIndex < sMA0.m_sMS.m_nuiIndx; ++uiIndex)
    {
        sMA0.m_sMS.m_puiIndx_List[uiIndex] = (TgUINT_E16)(uiIndex % sMA0.m_sMS.m_nuiVert);
    };
    FCN_VO(tgGM_MA_Update_Face_CG_BA)( &sMA0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_MA_Is_Valid)( &sMA0 ));

    FCN_VO(tgGM_MA_Init)( &sMA0, 9, 0, ETgSWEEP_STATIC );
    for (TgRSIZE uiIndex = 0; uiIndex < sMA0.m_sMS.m_nuiVert; ++uiIndex)
    {
        sMA0.m_sMS.m_pvVert_List[uiIndex] = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    };
    FCN_VO(tgGM_MA_Update_Face_CG_BA)( &sMA0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_MA_Is_Valid)( &sMA0 ));

    FCN_VO(tgGM_MA_Init)( &sMA0, 9, 12, ETgSWEEP_LINEAR);
    FCN_VO(tgGM_DT_Set)( &sMA0.m_sDT, vV0 );
    for (TgRSIZE uiIndex = 0; uiIndex < sMA0.m_sMS.m_nuiVert; ++uiIndex)
    {
        sMA0.m_sMS.m_pvVert_List[uiIndex] = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    };
    for (TgRSIZE uiIndex = 0; uiIndex < sMA0.m_sMS.m_nuiIndx; ++uiIndex)
    {
        sMA0.m_sMS.m_puiIndx_List[uiIndex] = (TgUINT_E16)(uiIndex % sMA0.m_sMS.m_nuiVert);
    };
    FCN_VO(tgGM_MA_Update_Face_CG_BA)( &sMA0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_MA_Is_Valid)( &sMA0 ));

    FCN_VO(tgGM_MA_Init)( &sMA0, 9, 0, ETgSWEEP_LINEAR );
    FCN_VO(tgGM_DT_Set)( &sMA0.m_sDT, vV0 );
    for (TgRSIZE uiIndex = 0; uiIndex < sMA0.m_sMS.m_nuiVert; ++uiIndex)
    {
        sMA0.m_sMS.m_pvVert_List[uiIndex] = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    };
    FCN_VO(tgGM_MA_Update_Face_CG_BA)( &sMA0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_MA_Is_Valid)( &sMA0 ));

    FCN_VO(tgGM_MA_Init)( &sMA0, 9, 12, ETgSWEEP_ROTATIONAL);
    for (TgRSIZE uiIndex = 0; uiIndex < sMA0.m_sMS.m_nuiVert; ++uiIndex)
    {
        sMA0.m_sMS.m_pvVert_List[uiIndex] = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
        sMA0.m_pvVert_DT[uiIndex] = vV0;
    };
    for (TgRSIZE uiIndex = 0; uiIndex < sMA0.m_sMS.m_nuiIndx; ++uiIndex)
    {
        sMA0.m_sMS.m_puiIndx_List[uiIndex] = (TgUINT_E16)(uiIndex % sMA0.m_sMS.m_nuiVert);
    };
    FCN_VO(tgGM_MA_Update_Face_CG_BA)( &sMA0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_MA_Is_Valid)( &sMA0 ));

    FCN_VO(tgGM_MA_Init)( &sMA0, 9, 0, ETgSWEEP_ROTATIONAL);
    for (TgRSIZE uiIndex = 0; uiIndex < sMA0.m_sMS.m_nuiVert; ++uiIndex)
    {
        sMA0.m_sMS.m_pvVert_List[uiIndex] = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
        sMA0.m_pvVert_DT[uiIndex] = vV0;
    };
    FCN_VO(tgGM_MA_Update_Face_CG_BA)( &sMA0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_MA_Is_Valid)( &sMA0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MA_Init_MS)( &sMA0, &sMS0 );

    FCN_VO(tgGM_MA_Reset)( &sMA0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS_TX) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS_TX) )
{
    VEC_T(3)                            xM0;
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MA_Init_MS_TX)( &sMA0, &sMS0, &xM0 );

    FCN_VO(tgGM_MA_Reset)( &sMA0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS_TX_TL) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS_TX_TL) )
{
    VEC_T(1)                            vV0;
    VEC_T(3)                            xM0;
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MA_Init_MS_TX_TL)( &sMA0, &sMS0, &xM0, vV0 );

    FCN_VO(tgGM_MA_Reset)( &sMA0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS_TX_TX) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Init_MS_TX_TX) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;
    VEC_T(3)                            xM0;
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_VO(tgGM_MA_Init_MS_TX_TX)( &sMA0, &sMS0, &xM0, &xM0 );

    FCN_VO(tgGM_MA_Reset)( &sMA0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Copy) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Copy) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0, sMA1;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Copy)( &sMA1, &sMA0 );

    FCN_VO(tgGM_MA_Reset)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_BA) ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_BA) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Update_Face_BA)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_CG_BA) -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_CG_BA) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Update_Face_CG_BA)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Query_Indx_List) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_Indx_List) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Query_Indx_List)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Query_Vert_List) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_Vert_List) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Query_Vert_List)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Query_Indx_Count) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_Indx_Count) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    Test__Expect_EQ( TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX), FCN_VO(tgGM_MA_Query_Indx_Count)( &sMA0 ) );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Query_Vert_Count) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_Vert_Count) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    Test__Expect_EQ( TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX) >> 1, FCN_VO(tgGM_MA_Query_Vert_Count)( &sMA0 ) );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Query_CG_0) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_CG_0) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Query_CG_0)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Query_CG_1) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_CG_1) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Query_CG_1)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Query_DT) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Query_DT) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Query_DT)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_BA_VL) -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_BA_VL) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_VL)( &sMA0 );
    FCN_VO(tgGM_MA_Update_Face_BA_VL)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_BA_IL) -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_BA_IL) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Update_Face_BA_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_CG_BA_VL) ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_CG_BA_VL) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_VL)( &sMA0 );
    FCN_VO(tgGM_MA_Update_Face_CG_BA_VL)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_CG_BA_IL) ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MA_Update_Face_CG_BA_IL) )
{
    VEC_OBJ_T(TgMESH_BA)                sMA0;

    FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Update_Face_CG_BA_IL)( &sMA0 );
    FCN_VO(tgGM_MA_Reset)( &sMA0 );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__SETUP__MA_Init_VL) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_V(UNIT_TEST__SETUP__MA_Init_VL)( VEC_OBJ_T(TgMESH_BA,PCU) psMA )
{
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );

    tgMM_Set_U08_0x00( psMA, sizeof( VEC_OBJ_T(TgMESH_BA) ) );

    FCN_VO(tgGM_MA_Init)( psMA, TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX), 0, ETgSWEEP_LINEAR );
    FCN_VO(tgGM_DT_Set)( &psMA->m_sDT, vV0 );

    for (TgRSIZE uiIndx = 0, uiVert; uiIndx < psMA->m_sMS.m_nuiIndx; ++uiIndx)
    {
        uiVert = KTgGM_ICOSAHEDRON_PN_INDEX[uiIndx];
        TgERROR(uiVert < psMA->m_sMS.m_nuiVert);
        psMA->m_sMS.m_pvVert_List[uiVert].m_aData[0] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[0];
        psMA->m_sMS.m_pvVert_List[uiVert].m_aData[1] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[1];
        psMA->m_sMS.m_pvVert_List[uiVert].m_aData[2] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[2];
        psMA->m_sMS.m_pvVert_List[uiVert].m_aData[3] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[3];
    };

    tgMM_Copy( psMA->m_sMS.m_puiIndx_List, psMA->m_sMS.m_nuiIndx*sizeof( psMA->m_sMS.m_puiIndx_List[0] ), KTgGM_ICOSAHEDRON_PN_INDEX, sizeof( KTgGM_ICOSAHEDRON_PN_INDEX ) );
    TgERROR( psMA->m_sMS.m_nuiIndx*sizeof( psMA->m_sMS.m_puiIndx_List[0] ) >= sizeof( KTgGM_ICOSAHEDRON_PN_INDEX ) );

    FCN_VO(tgGM_MA_Update_Face_CG_BA)( psMA );
}


/* ---- FCN_V(UNIT_TEST__SETUP__MA_Init_IL) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_V(UNIT_TEST__SETUP__MA_Init_IL)( VEC_OBJ_T(TgMESH_BA,PCU) psMA )
{
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );

    tgMM_Set_U08_0x00( psMA, sizeof( VEC_OBJ_T(TgMESH_BA) ) );

    FCN_VO(tgGM_MA_Init)( psMA, (TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX) >> 1), TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX), ETgSWEEP_LINEAR );
    FCN_VO(tgGM_DT_Set)( &psMA->m_sDT, vV0 );

    for (TgRSIZE uiVert = 0; uiVert < psMA->m_sMS.m_nuiVert; ++uiVert)
    {
        psMA->m_sMS.m_pvVert_List[uiVert].m_aData[0] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[0];
        psMA->m_sMS.m_pvVert_List[uiVert].m_aData[1] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[1];
        psMA->m_sMS.m_pvVert_List[uiVert].m_aData[2] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[2];
        psMA->m_sMS.m_pvVert_List[uiVert].m_aData[3] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[3];
    };

    tgMM_Copy( psMA->m_sMS.m_puiIndx_List, psMA->m_sMS.m_nuiIndx*sizeof( psMA->m_sMS.m_puiIndx_List[0] ), KTgGM_ICOSAHEDRON_PN_INDEX, sizeof( KTgGM_ICOSAHEDRON_PN_INDEX ) );
    TgERROR( psMA->m_sMS.m_nuiIndx*sizeof( psMA->m_sMS.m_puiIndx_List[0] ) >= sizeof( KTgGM_ICOSAHEDRON_PN_INDEX ) );

    FCN_VO(tgGM_MA_Update_Face_CG_BA)( psMA );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
