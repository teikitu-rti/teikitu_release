/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Math [Constants].c_inc
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include <math.h>


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__Math_Constant ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__Math_Constant )
{
    #define TgPP_KVAL_PI_F                      3.141592653589793238462643383279F

    Test__Expect_NE(0, tgCM_NR0_F32( KTgPI_F32 - (TgPP_KVAL_PI_F) ));
    Test__Expect_NE(0, tgCM_NR0_F32( KTgTWO_PI_F32 - (2.0F*TgPP_KVAL_PI_F) ));
    Test__Expect_NE(0, tgCM_NR0_F32( KTgHALF_PI_F32 - (0.5F*TgPP_KVAL_PI_F) ));
    Test__Expect_NE(0, tgCM_NR0_F32( KTgINVPI_F32 - (1.0F / TgPP_KVAL_PI_F) ));
    Test__Expect_NE(0, tgCM_NR0_F32( KTgSQRT2_F32 - sqrtf( 2.0F ) ));
    Test__Expect_NE(0, tgCM_NR0_F32( KTgSQRT3_F32 - sqrtf( 3.0F ) ));
    Test__Expect_NE(0, tgCM_NR0_F32( KTgSQRT5_F32 - sqrtf( 5.0F ) ));
    Test__Expect_NE(0, tgCM_NR0_F32( KTgTHIRD_F32 - (1.0F / 3.0F) ));
    Test__Expect_NE(0, tgCM_NR0_F32( KTgTWENTYSEVENTH_F32 - (1.0F / 27.0F) ));
    Test__Expect_NE(0, tgCM_NR0_F32( KTgSQRT1_2_F32 - (1.0F / sqrtf( 2.0F )) ));
    Test__Expect_NE(0, tgCM_NR0_F32( KTgDEG_TO_RAD_F32 - (TgPP_KVAL_PI_F / 180.0F) ));
    Test__Expect_NE(0, tgCM_NR0_F32( KTgRAD_TO_DEG_F32 - (180.0F / TgPP_KVAL_PI_F) ));
    Test__Expect_NE(0, tgCM_NR0_F32( KTgGOLDEN_RATIO_F32 - ((1.0F + sqrtf( 5.0F )) * 0.5F) ));

    #define TgPP_KVAL_PI                        3.141592653589793238462643383279

    Test__Expect_NE(0, tgCM_NR0_F64( KTgPI_F64 - (TgPP_KVAL_PI) ));
    Test__Expect_NE(0, tgCM_NR0_F64( KTgTWO_PI_F64 - (2.0*TgPP_KVAL_PI) ));
    Test__Expect_NE(0, tgCM_NR0_F64( KTgHALF_PI_F64 - (0.5*TgPP_KVAL_PI) ));
    Test__Expect_NE(0, tgCM_NR0_F64( KTgINVPI_F64 - (1.0 / TgPP_KVAL_PI) ));
    Test__Expect_NE(0, tgCM_NR0_F64( KTgSQRT2_F64 - sqrt( 2.0 ) ));
    Test__Expect_NE(0, tgCM_NR0_F64( KTgSQRT3_F64 - sqrt( 3.0 ) ));
    Test__Expect_NE(0, tgCM_NR0_F64( KTgSQRT5_F64 - sqrt( 5.0 ) ));
    Test__Expect_NE(0, tgCM_NR0_F64( KTgTHIRD_F64 - (1.0 / 3.0) ));
    Test__Expect_NE(0, tgCM_NR0_F64( KTgTWENTYSEVENTH_F64 - (1.0 / 27.0) ));
    Test__Expect_NE(0, tgCM_NR0_F64( KTgSQRT1_2_F64 - (1.0 / sqrt( 2.0 )) ));
    Test__Expect_NE(0, tgCM_NR0_F64( KTgDEG_TO_RAD_F64 - (TgPP_KVAL_PI / 180.0) ));
    Test__Expect_NE(0, tgCM_NR0_F64( KTgRAD_TO_DEG_F64 - (180.0 / TgPP_KVAL_PI) ));
    Test__Expect_NE(0, tgCM_NR0_F64( KTgGOLDEN_RATIO_F64 - ((1.0 + sqrt( 5.0 )) * 0.5) ));

    Test__Expect_EQ(KTgMAX_U32, KTgFFFF_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(KTgMAX_U32, KTgFFFF_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(KTgMAX_U32, KTgFFFF_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(KTgMAX_U32, KTgFFFF_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(KTgMAX_U32, KTgFFF0_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(KTgMAX_U32, KTgFFF0_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(KTgMAX_U32, KTgFFF0_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0u,         KTgFFF0_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(KTgMAX_U32, KTgFF0F_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(KTgMAX_U32, KTgFF0F_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0u,         KTgFF0F_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(KTgMAX_U32, KTgFF0F_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(KTgMAX_U32, KTgFF00_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(KTgMAX_U32, KTgFF00_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0u,         KTgFF00_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0u,         KTgFF00_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(KTgMAX_U32, KTgF0FF_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0u,         KTgF0FF_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(KTgMAX_U32, KTgF0FF_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(KTgMAX_U32, KTgF0FF_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(KTgMAX_U32, KTgF0F0_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0u,         KTgF0F0_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(KTgMAX_U32, KTgF0F0_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0u,         KTgF0F0_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(KTgMAX_U32, KTgF00F_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0u,         KTgF00F_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0u,         KTgF00F_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(KTgMAX_U32, KTgF00F_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(KTgMAX_U32, KTgF000_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0u,         KTgF000_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0u,         KTgF000_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0u,         KTgF000_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0u,         KTg0FFF_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(KTgMAX_U32, KTg0FFF_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(KTgMAX_U32, KTg0FFF_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(KTgMAX_U32, KTg0FFF_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0u,         KTg0FF0_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(KTgMAX_U32, KTg0FF0_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(KTgMAX_U32, KTg0FF0_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0u,         KTg0FF0_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0u,         KTg0F0F_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(KTgMAX_U32, KTg0F0F_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0u,         KTg0F0F_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(KTgMAX_U32, KTg0F0F_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0u,         KTg0F00_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(KTgMAX_U32, KTg0F00_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0u,         KTg0F00_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0u,         KTg0F00_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0u,         KTg00FF_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0u,         KTg00FF_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(KTgMAX_U32, KTg00FF_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(KTgMAX_U32, KTg00FF_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0u,         KTg00F0_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0u,         KTg00F0_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(KTgMAX_U32, KTg00F0_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0u,         KTg00F0_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0u,         KTg000F_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0u,         KTg000F_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0u,         KTg000F_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(KTgMAX_U32, KTg000F_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0u,         KTg0000_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0u,         KTg0000_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0u,         KTg0000_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0u,         KTg0000_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0x7F800000u,    KTgNAN_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0x7F800000u,    KTgNAN_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0x7F800000u,    KTgNAN_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0x7F800000u,    KTgNAN_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0x80000000u,    KTgSgnM_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0x80000000u,    KTgSgnM_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0x80000000u,    KTgSgnM_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0x80000000u,    KTgSgnM_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0x7F800000u,    KTgINF_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0x7F800000u,    KTgINF_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0x7F800000u,    KTgINF_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0x7F800000u,    KTgINF_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0u,             KTgPNNP_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0x80000000u,    KTgPNNP_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0x80000000u,    KTgPNNP_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0u,             KTgPNNP_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0x04050607u,    KTgYZXW_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0x08090a0bu,    KTgYZXW_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0x00010203u,    KTgYZXW_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0x0c0d0e0fu,    KTgYZXW_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0x08090a0bu,    KTgZXYW_V128.m_vS_U32_04_1.x);
    Test__Expect_EQ(0x00010203u,    KTgZXYW_V128.m_vS_U32_04_1.y);
    Test__Expect_EQ(0x04050607u,    KTgZXYW_V128.m_vS_U32_04_1.z);
    Test__Expect_EQ(0x0c0d0e0fu,    KTgZXYW_V128.m_vS_U32_04_1.w);

    Test__Expect_EQ(0.0F,           KTgZERO_V128.m_vS_F32_04_1.x);
    Test__Expect_EQ(0.0F,           KTgZERO_V128.m_vS_F32_04_1.y);
    Test__Expect_EQ(0.0F,           KTgZERO_V128.m_vS_F32_04_1.z);
    Test__Expect_EQ(0.0F,           KTgZERO_V128.m_vS_F32_04_1.w);
    Test__Expect_EQ(1.0F,           KTgONE_V128.m_vS_F32_04_1.x);
    Test__Expect_EQ(1.0F,           KTgONE_V128.m_vS_F32_04_1.y);
    Test__Expect_EQ(1.0F,           KTgONE_V128.m_vS_F32_04_1.z);
    Test__Expect_EQ(1.0F,           KTgONE_V128.m_vS_F32_04_1.w);
    Test__Expect_EQ(1.0F,           KTgUNIT_X_V128.m_vS_F32_04_1.x);
    Test__Expect_EQ(0.0F,           KTgUNIT_X_V128.m_vS_F32_04_1.y);
    Test__Expect_EQ(0.0F,           KTgUNIT_X_V128.m_vS_F32_04_1.z);
    Test__Expect_EQ(0.0F,           KTgUNIT_X_V128.m_vS_F32_04_1.w);
    Test__Expect_EQ(0.0F,           KTgUNIT_Y_V128.m_vS_F32_04_1.x);
    Test__Expect_EQ(1.0F,           KTgUNIT_Y_V128.m_vS_F32_04_1.y);
    Test__Expect_EQ(0.0F,           KTgUNIT_Y_V128.m_vS_F32_04_1.z);
    Test__Expect_EQ(0.0F,           KTgUNIT_Y_V128.m_vS_F32_04_1.w);
    Test__Expect_EQ(0.0F,           KTgUNIT_Z_V128.m_vS_F32_04_1.x);
    Test__Expect_EQ(0.0F,           KTgUNIT_Z_V128.m_vS_F32_04_1.y);
    Test__Expect_EQ(1.0F,           KTgUNIT_Z_V128.m_vS_F32_04_1.z);
    Test__Expect_EQ(0.0F,           KTgUNIT_Z_V128.m_vS_F32_04_1.w);
    Test__Expect_EQ(0.0F,           KTgUNIT_W_V128.m_vS_F32_04_1.x);
    Test__Expect_EQ(0.0F,           KTgUNIT_W_V128.m_vS_F32_04_1.y);
    Test__Expect_EQ(0.0F,           KTgUNIT_W_V128.m_vS_F32_04_1.z);
    Test__Expect_EQ(1.0F,           KTgUNIT_W_V128.m_vS_F32_04_1.w);

    Test__Expect_EQ(0.0F,           KTgZERO_S_F32_03_1.x);
    Test__Expect_EQ(0.0F,           KTgZERO_S_F32_03_1.y);
    Test__Expect_EQ(0.0F,           KTgZERO_S_F32_03_1.z);
    Test__Expect_EQ(1.0F,           KTgONE_S_F32_03_1.x);
    Test__Expect_EQ(1.0F,           KTgONE_S_F32_03_1.y);
    Test__Expect_EQ(1.0F,           KTgONE_S_F32_03_1.z);
    Test__Expect_EQ(1.0F,           KTgUNIT_X_S_F32_03_1.x);
    Test__Expect_EQ(0.0F,           KTgUNIT_X_S_F32_03_1.y);
    Test__Expect_EQ(0.0F,           KTgUNIT_X_S_F32_03_1.z);
    Test__Expect_EQ(0.0F,           KTgUNIT_Y_S_F32_03_1.x);
    Test__Expect_EQ(1.0F,           KTgUNIT_Y_S_F32_03_1.y);
    Test__Expect_EQ(0.0F,           KTgUNIT_Y_S_F32_03_1.z);
    Test__Expect_EQ(0.0F,           KTgUNIT_Z_S_F32_03_1.x);
    Test__Expect_EQ(0.0F,           KTgUNIT_Z_S_F32_03_1.y);
    Test__Expect_EQ(1.0F,           KTgUNIT_Z_S_F32_03_1.z);

    Test__Expect_EQ(0.0F,           KTgZERO_S_F32_04_1.x);
    Test__Expect_EQ(0.0F,           KTgZERO_S_F32_04_1.y);
    Test__Expect_EQ(0.0F,           KTgZERO_S_F32_04_1.z);
    Test__Expect_EQ(0.0F,           KTgZERO_S_F32_04_1.w);
    Test__Expect_EQ(1.0F,           KTgONE_S_F32_04_1.x);
    Test__Expect_EQ(1.0F,           KTgONE_S_F32_04_1.y);
    Test__Expect_EQ(1.0F,           KTgONE_S_F32_04_1.z);
    Test__Expect_EQ(1.0F,           KTgONE_S_F32_04_1.w);
    Test__Expect_EQ(1.0F,           KTgUNIT_X_S_F32_04_1.x);
    Test__Expect_EQ(0.0F,           KTgUNIT_X_S_F32_04_1.y);
    Test__Expect_EQ(0.0F,           KTgUNIT_X_S_F32_04_1.z);
    Test__Expect_EQ(0.0F,           KTgUNIT_X_S_F32_04_1.w);
    Test__Expect_EQ(0.0F,           KTgUNIT_Y_S_F32_04_1.x);
    Test__Expect_EQ(1.0F,           KTgUNIT_Y_S_F32_04_1.y);
    Test__Expect_EQ(0.0F,           KTgUNIT_Y_S_F32_04_1.z);
    Test__Expect_EQ(0.0F,           KTgUNIT_Y_S_F32_04_1.w);
    Test__Expect_EQ(0.0F,           KTgUNIT_Z_S_F32_04_1.x);
    Test__Expect_EQ(0.0F,           KTgUNIT_Z_S_F32_04_1.y);
    Test__Expect_EQ(1.0F,           KTgUNIT_Z_S_F32_04_1.z);
    Test__Expect_EQ(0.0F,           KTgUNIT_Z_S_F32_04_1.w);
    Test__Expect_EQ(0.0F,           KTgUNIT_W_S_F32_04_1.x);
    Test__Expect_EQ(0.0F,           KTgUNIT_W_S_F32_04_1.y);
    Test__Expect_EQ(0.0F,           KTgUNIT_W_S_F32_04_1.z);
    Test__Expect_EQ(1.0F,           KTgUNIT_W_S_F32_04_1.w);

    Test__Expect_EQ(0.0,            KTgZERO_S_F64_03_1.x);
    Test__Expect_EQ(0.0,            KTgZERO_S_F64_03_1.y);
    Test__Expect_EQ(0.0,            KTgZERO_S_F64_03_1.z);
    Test__Expect_EQ(1.0,            KTgONE_S_F64_03_1.x);
    Test__Expect_EQ(1.0,            KTgONE_S_F64_03_1.y);
    Test__Expect_EQ(1.0,            KTgONE_S_F64_03_1.z);
    Test__Expect_EQ(1.0,            KTgUNIT_X_S_F64_03_1.x);
    Test__Expect_EQ(0.0,            KTgUNIT_X_S_F64_03_1.y);
    Test__Expect_EQ(0.0,            KTgUNIT_X_S_F64_03_1.z);
    Test__Expect_EQ(0.0,            KTgUNIT_Y_S_F64_03_1.x);
    Test__Expect_EQ(1.0,            KTgUNIT_Y_S_F64_03_1.y);
    Test__Expect_EQ(0.0,            KTgUNIT_Y_S_F64_03_1.z);
    Test__Expect_EQ(0.0,            KTgUNIT_Z_S_F64_03_1.x);
    Test__Expect_EQ(0.0,            KTgUNIT_Z_S_F64_03_1.y);
    Test__Expect_EQ(1.0,            KTgUNIT_Z_S_F64_03_1.z);

    Test__Expect_EQ(0.0,            KTgZERO_S_F64_04_1.x);
    Test__Expect_EQ(0.0,            KTgZERO_S_F64_04_1.y);
    Test__Expect_EQ(0.0,            KTgZERO_S_F64_04_1.z);
    Test__Expect_EQ(0.0,            KTgZERO_S_F64_04_1.w);
    Test__Expect_EQ(1.0,            KTgONE_S_F64_04_1.x);
    Test__Expect_EQ(1.0,            KTgONE_S_F64_04_1.y);
    Test__Expect_EQ(1.0,            KTgONE_S_F64_04_1.z);
    Test__Expect_EQ(1.0,            KTgONE_S_F64_04_1.w);
    Test__Expect_EQ(1.0,            KTgUNIT_X_S_F64_04_1.x);
    Test__Expect_EQ(0.0,            KTgUNIT_X_S_F64_04_1.y);
    Test__Expect_EQ(0.0,            KTgUNIT_X_S_F64_04_1.z);
    Test__Expect_EQ(0.0,            KTgUNIT_X_S_F64_04_1.w);
    Test__Expect_EQ(0.0,            KTgUNIT_Y_S_F64_04_1.x);
    Test__Expect_EQ(1.0,            KTgUNIT_Y_S_F64_04_1.y);
    Test__Expect_EQ(0.0,            KTgUNIT_Y_S_F64_04_1.z);
    Test__Expect_EQ(0.0,            KTgUNIT_Y_S_F64_04_1.w);
    Test__Expect_EQ(0.0,            KTgUNIT_Z_S_F64_04_1.x);
    Test__Expect_EQ(0.0,            KTgUNIT_Z_S_F64_04_1.y);
    Test__Expect_EQ(1.0,            KTgUNIT_Z_S_F64_04_1.z);
    Test__Expect_EQ(0.0,            KTgUNIT_Z_S_F64_04_1.w);
    Test__Expect_EQ(0.0,            KTgUNIT_W_S_F64_04_1.x);
    Test__Expect_EQ(0.0,            KTgUNIT_W_S_F64_04_1.y);
    Test__Expect_EQ(0.0,            KTgUNIT_W_S_F64_04_1.z);
    Test__Expect_EQ(1.0,            KTgUNIT_W_S_F64_04_1.w);

    TEST_END_METHOD( KTgS_OK );
}
