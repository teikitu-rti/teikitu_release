/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Vector] [S].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_VECTOR_S_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(tgMH_SETU_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_SETU_S)( VAR_T(CPCU) pty )
{
    VEC_S_T(1)                          vResult;

    tgMM_Copy( &vResult, sizeof(vResult), pty, TEMPLATE__VECTOR_DIM*sizeof( VAR_T() ) );

    TgMSVC_WARN_SUPPRESS( 6001 )
    return (vResult);
}


/* ---- FCN_V(tgMH_SETA_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_SETA_S)( VAR_T(CPCU) pty )
{
    VEC_S_T(1)                          vResult;

    tgMM_Copy( &vResult, sizeof(vResult), pty, TEMPLATE__VECTOR_DIM*sizeof( VAR_T() ) );

    TgMSVC_WARN_SUPPRESS( 6001 )
    return (vResult);
}


/* ---- FCN_V(tgMH_SET1_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_SET1_S)( VAR_T(C) fX )
{
    #define EQN(A) fX
    GENERATE__VEC_ASSIGN_EQN
    #undef EQN
}


/* ---- FCN_V(tgMH_RAND_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_RAND_S)( TgVOID )
{
    #define EQN(A) FCN_F(tgCM_RAND)()
    GENERATE__VEC_ASSIGN_EQN
    #undef EQN
}


/* ---- FCN_V(tgMH_ADD_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_ADD_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    #define EQN(A) (VAR_T())(vARG_0.m_aData[A] + vARG_1.m_aData[A])
    GENERATE__VEC_ASSIGN_EQN;
    #undef EQN
}

/* ---- FCN_V(tgMH_SUB_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_SUB_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    #define EQN(A) (VAR_T())(vARG_0.m_aData[A] - vARG_1.m_aData[A])
    GENERATE__VEC_ASSIGN_EQN;
    #undef EQN
}


/* ---- FCN_V(tgMH_AVG_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_AVG_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    VEC_S_T(1)                          vResult;
    TgUINT_E32                          uiIndex;

    tgMM_Set_U08_0x00( &vResult, sizeof( vResult ) );
    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        if ((VAR_K(KTgMAX) <= vARG_0.m_aData[uiIndex]) && (VAR_K(KTgMAX) <= vARG_1.m_aData[uiIndex]))
        {
            vResult.m_aData[uiIndex] = VAR_K(KTgMAX);
        }
        else if (vARG_1.m_aData[uiIndex] == TYPE_K(0))
        {
            vResult.m_aData[uiIndex] = (VAR_T())(vARG_0.m_aData[uiIndex] / 2);
        }
        else if (vARG_1.m_aData[uiIndex] > TYPE_K(0))
        {
            if (vARG_0.m_aData[uiIndex] > (VAR_K(KTgMAX) - vARG_1.m_aData[uiIndex]))
            {
                vResult.m_aData[uiIndex] = (VAR_T())((vARG_0.m_aData[uiIndex] - (VAR_K(KTgMAX) - vARG_1.m_aData[uiIndex]) + 1) / TYPE_K(2) + VAR_K(KTgMAX) / TYPE_K(2));
            }
            else
            {
                vResult.m_aData[uiIndex] = (VAR_T())((vARG_0.m_aData[uiIndex] + vARG_1.m_aData[uiIndex]) / TYPE_K(2));
            };
        }
        else
        {
            if (vARG_0.m_aData[uiIndex] < (VAR_K(KTgMIN) - vARG_1.m_aData[uiIndex]))
            {
                vResult.m_aData[uiIndex] = (VAR_T())((vARG_0.m_aData[uiIndex] - (VAR_K(KTgMIN) - vARG_1.m_aData[uiIndex])) / TYPE_K(2) + VAR_K(KTgMIN) / TYPE_K(2));
            }
            else
            {
                vResult.m_aData[uiIndex] = (VAR_T())((vARG_0.m_aData[uiIndex] + vARG_1.m_aData[uiIndex]) / TYPE_K(2));
            };
        };
    };

    return (vResult);
}
/* ---- FCN_V(tgMH_PERM_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_PERM_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C)vARG_1, UVAR_T(CPCU) puiMask )
{
    union FCN_V(tgMH_PERM_DATA_ALIAS_OUTPUT_S)
    {
        VEC_S_T(1)                                  v;
        UVAR_T()                                    ui[sizeof( VEC_S_T(1) ) / sizeof( UVAR_T() )];
    }                                   uOut0;

    union FCN_V(tgMH_PERM_DATA_ALIAS_INPUT_S)
    {
        VEC_S_T(1,CP)                               pv;
        UVAR_T(CP)                                  pui;
    }                                   uIn0, uIn1;

    uIn0.pv = &vARG_0;
    uIn1.pv = &vARG_1;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        UVAR_T()                            uiMask = puiMask[uiIndex];
        TgUINT_E08_C                        uiData_Index = (TgUINT_E08)(uiMask & (KTgPERM_PARAM_SELECT_BIT - 1));
        UVAR_T(CP)                          puiData = (0 == (uiMask & KTgPERM_PARAM_SELECT_BIT)) ? uIn0.pui : uIn1.pui;

        uOut0.ui[uiIndex] = puiData[uiData_Index];
    };

    return (uOut0.v);
}


/* ---- FCN_V(tgMH_SEL_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_SEL_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1, UVAR_T(CPCU) puiMask )
{
    union FCN_V(tgMH_SEL_DATA_ALIAS_OUTPUT_S)
    {
        VEC_S_T(1)                                  v;
        UVAR_T()                                    i[sizeof( VEC_S_T(1) ) / sizeof( UVAR_T() )];
    }                                   uOut0;

    union FCN_V(tgMH_SEL_DATA_ALIAS_INPUT_S)
    {
        VEC_S_T(1,CP)                               pv;
        UVAR_T(CP)                                  pi;
    }                                   uIn0, uIn1;

    uIn0.pv = &vARG_0;
    uIn1.pv = &vARG_1;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        uOut0.i[uiIndex] = (UVAR_T())((uIn0.pi[uiIndex] & ~(puiMask[uiIndex])) | (uIn1.pi[uiIndex] & puiMask[uiIndex]));
    };

    return (uOut0.v);
}


/* ---- FCN_V(tgMH_AND_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_AND_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    union FCN_V(tgMH_AND_DATA_ALIAS_OUTPUT_S)
    {
        VEC_S_T(1)                                  v;
        TgUINT_E32                                  i[sizeof( VEC_S_T(1) ) / sizeof( TgUINT_E32 )];
    }                                   uOut0;

    TgCOMPILER_ASSERT( sizeof( uOut0.v ) == sizeof( uOut0.i ), 0 );

    union FCN_V(tgMH_AND_DATA_ALIAS_INPUT_S)
    {
        VEC_S_T(1,CP)                               pv;
        TgUINT_E32_CP                               pi;
    }                                   uIn0, uIn1;

    uIn0.pv = &vARG_0;
    uIn1.pv = &vARG_1;

    for (TgRSIZE uiIndex = 0; uiIndex < sizeof( uOut0.i ) / sizeof( uOut0.i[0] ); ++uiIndex)
    {
        uOut0.i[uiIndex] = uIn0.pi[uiIndex] & uIn1.pi[uiIndex];
    };

    return (uOut0.v);
}


/* ---- FCN_V(tgMH_OR_S) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_OR_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    union FCN_V(tgMH_OR_DATA_ALIAS_OUTPUT_S)
    {
        VEC_S_T(1)                                  v;
        TgUINT_E32                                  i[sizeof( VEC_S_T(1) ) / sizeof( TgUINT_E32 )];
    }                                   uOut0;

    TgCOMPILER_ASSERT( sizeof( uOut0.v ) == sizeof( uOut0.i ), 0 );

    union FCN_V(tgMH_OR_DATA_ALIAS_INPUT_S)
    {
        VEC_S_T(1,CP)                               pv;
        TgUINT_E32_CP                               pi;
    }                                   uIn0, uIn1;

    uIn0.pv = &vARG_0;
    uIn1.pv = &vARG_1;

    for (TgRSIZE uiIndex = 0; uiIndex < sizeof( uOut0.i ) / sizeof( uOut0.i[0] ); ++uiIndex)
    {
        uOut0.i[uiIndex] = uIn0.pi[uiIndex] | uIn1.pi[uiIndex];
    };

    return (uOut0.v);
}


/* ---- FCN_V(tgMH_XOR_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_XOR_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    union FCN_V(tgMH_XOR_DATA_ALIAS_OUTPUT_S)
    {
        VEC_S_T(1)                                  v;
        TgUINT_E32                                  i[sizeof( VEC_S_T(1) ) / sizeof( TgUINT_E32 )];
    }                                   uOut0;

    TgCOMPILER_ASSERT( sizeof( uOut0.v ) == sizeof( uOut0.i ), 0 );

    union FCN_V(tgMH_XOR_DATA_ALIAS_INPUT_S)
    {
        VEC_S_T(1,CP)                               pv;
        TgUINT_E32_CP                               pi;
    }                                   uIn0, uIn1;

    uIn0.pv = &vARG_0;
    uIn1.pv = &vARG_1;

    for (TgRSIZE uiIndex = 0; uiIndex < sizeof( uOut0.i ) / sizeof( uOut0.i[0] ); ++uiIndex)
    {
        uOut0.i[uiIndex] = uIn0.pi[uiIndex] ^ uIn1.pi[uiIndex];
    };

    return (uOut0.v);
}


/* ---- FCN_V(tgMH_MAX_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_MAX_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    #define EQN(A) FCN_F(tgCM_MAX)( vARG_0.m_aData[A], vARG_1.m_aData[A] )
    GENERATE__VEC_ASSIGN_EQN
    #undef EQN
}


/* ---- FCN_V(tgMH_MAX_ELEM_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCN_V(tgMH_MAX_ELEM_S)( VEC_S_T(1,C) vARG_0 )
{
#if defined(TEMPLATE__ENABLE_INTEGER)
    VAR_T()                             tVal = VAR_K(KTgMIN);
#else
    VAR_T()                             tVal = -VAR_K(KTgMAX);
#endif

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        tVal = FCN_F(tgCM_MAX)( tVal, vARG_0.m_aData[uiIndex] );
    };

    return (tVal);
}


/* ---- FCN_V(tgMH_MIN_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_MIN_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    #define EQN(A) FCN_F(tgCM_MIN)( vARG_0.m_aData[A], vARG_1.m_aData[A] )
    GENERATE__VEC_ASSIGN_EQN
    #undef EQN
}


/* ---- FCN_V(tgMH_MIN_ELEM_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCN_V(tgMH_MIN_ELEM_S)( VEC_S_T(1,C) vARG_0 )
{
#if defined(TEMPLATE__ENABLE_INTEGER)
    VAR_T()                             tVal = VAR_K(KTgMAX);
#else
    VAR_T()                             tVal = VAR_K(KTgMAX);
#endif

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        tVal = FCN_F(tgCM_MIN)( tVal, vARG_0.m_aData[uiIndex] );
    };

    return (tVal);
}


/* ---- FCN_V(tgMH_ABS_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_ABS_S)( VEC_S_T(1,C) vARG_0 )
{
    #define EQN(A) FCN_F(tgPM_ABS)( vARG_0.m_aData[A] )
    GENERATE__VEC_ASSIGN_EQN;
    #undef EQN
}


/* ---- FCN_V(tgMH_SGN_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_SGN_S)( VEC_S_T(1,C) vARG_0 )
{
    #define EQN(A) FCN_F(tgCM_SGN)( vARG_0.m_aData[A] )
    GENERATE__VEC_ASSIGN_EQN;
    #undef EQN
}


/* ---- FCN_V(tgMH_CMP_EQ_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCLANG_WARN_DISABLE_PUSH(float-equal)
TgINLINE VEC_S_T(1) FCN_V(tgMH_CMP_EQ_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    #define EQN(A) (VAR_T())((vARG_0.m_aData[A] == vARG_1.m_aData[A]) ? UVAR_MASK : 0)
    GENERATE__VEC_ASSIGN_EQN
    #undef EQN
}
TgCLANG_WARN_DISABLE_POP(float-equal)


/* ---- FCN_V(tgMH_CMP_NE_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCLANG_WARN_DISABLE_PUSH(float-equal)
TgINLINE VEC_S_T(1) FCN_V(tgMH_CMP_NE_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C)vARG_1 )
{
    #define EQN(A) (VAR_T())((vARG_0.m_aData[A] != vARG_1.m_aData[A]) ? UVAR_MASK : 0)
    GENERATE__VEC_ASSIGN_EQN
    #undef EQN
}
TgCLANG_WARN_DISABLE_POP(float-equal)


/* ---- FCN_V(tgMH_CMP_GE_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_CMP_GE_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    #define EQN(A) (VAR_T())((vARG_0.m_aData[A] >= vARG_1.m_aData[A]) ? UVAR_MASK : 0)
    GENERATE__VEC_ASSIGN_EQN
    #undef EQN
}


/* ---- FCN_V(tgMH_CMP_GT_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_CMP_GT_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    #define EQN(A) (VAR_T())((vARG_0.m_aData[A] >  vARG_1.m_aData[A]) ? UVAR_MASK : 0)
    GENERATE__VEC_ASSIGN_EQN
    #undef EQN
}


/* ---- FCN_V(tgMH_CMP_LE_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_CMP_LE_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    #define EQN(A) (VAR_T())((vARG_0.m_aData[A] <= vARG_1.m_aData[A]) ? UVAR_MASK : 0)
    GENERATE__VEC_ASSIGN_EQN
    #undef EQN
}


/* ---- FCN_V(tgMH_CMP_LT_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_CMP_LT_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    #define EQN(A) (VAR_T())(vARG_0.m_aData[A] <  vARG_1.m_aData[A] ? UVAR_MASK : 0)
    GENERATE__VEC_ASSIGN_EQN
    #undef EQN
}


/* ---- FCN_V(tgMH_CMP_ALL_TO_BOOL_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( VEC_S_T(1,C) vARG_0 )
{
    union FCN_V(tgMH_CMP_ALL_DATA_ALIAS_INPUT_S)
    {
        VEC_S_T(1,CP)                               pv;
        UVAR_T(CP)                                  pi;
    }                                   uIn0;

    uIn0.pv = &vARG_0;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        if (0 == uIn0.pi[uiIndex])
        {
            return (false);
        };
    };

    return (true);
}


/* ---- FCN_V(tgMH_CMP_ANY_TO_BOOL_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_CMP_ANY_TO_BOOL_S)( VEC_S_T(1,C) vARG_0 )
{
    union FCN_V(tgMH_CMP_ALL_DATA_ALIAS_INPUT_S)
    {
        VEC_S_T(1,CP)                               pv;
        UVAR_T(CP)                                  pi;
    }                                   uIn0;

    uIn0.pv = &vARG_0;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        if (0 != uIn0.pi[uiIndex])
        {
            return (true);
        };
    };

    return (false);
}


/* =============================================================================================================================================================================== */
#endif
