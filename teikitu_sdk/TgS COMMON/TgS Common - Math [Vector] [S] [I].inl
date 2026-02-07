/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Vector] [S] [I].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_VECTOR_S_I_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(tgMH_ADD_CLP_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_ADD_CLP_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    VEC_S_T(1)                          vResult;
    TgUINT_E32                          uiIndex;

    tgMM_Set_U08_0x00( &vResult, sizeof( vResult ) );
    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        if (vARG_1.m_aData[uiIndex] == 0)
        {
            vResult.m_aData[uiIndex] = vARG_0.m_aData[uiIndex];
        }
        else if (vARG_1.m_aData[uiIndex] > 0)
        {
            if (vARG_0.m_aData[uiIndex] > (VAR_K(KTgMAX) - vARG_1.m_aData[uiIndex]))
            {
                vResult.m_aData[uiIndex] = VAR_K(KTgMAX);
            }
            else
            {
                vResult.m_aData[uiIndex] = (VAR_T())((vARG_0.m_aData[uiIndex] + vARG_1.m_aData[uiIndex]));
            };
        }
        else
        {
            if (vARG_0.m_aData[uiIndex] < (VAR_K(KTgMIN) - vARG_1.m_aData[uiIndex]))
            {
                vResult.m_aData[uiIndex] = VAR_K(KTgMIN);
            }
            else
            {
                vResult.m_aData[uiIndex] = (VAR_T())((vARG_0.m_aData[uiIndex] + vARG_1.m_aData[uiIndex]));
            };
        };
    };

    return (vResult);
}


/* ---- FCN_V(tgMH_SUB_CLP_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_SUB_CLP_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    VEC_S_T(1)                          vResult;
    TgUINT_E32                          uiIndex;

    tgMM_Set_U08_0x00( &vResult, sizeof( vResult ) );
    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        if (vARG_1.m_aData[uiIndex] == 0)
        {
            vResult.m_aData[uiIndex] = vARG_0.m_aData[uiIndex];
        }
        else if (vARG_1.m_aData[uiIndex] > 0)
        {
            if (vARG_0.m_aData[uiIndex] < (VAR_K(KTgMIN) + vARG_1.m_aData[uiIndex]))
            {
                vResult.m_aData[uiIndex] = VAR_K(KTgMIN);
            }
            else
            {
                vResult.m_aData[uiIndex] = (VAR_T())((vARG_0.m_aData[uiIndex] - vARG_1.m_aData[uiIndex]));
            };
        }
        else
        {
            if (vARG_0.m_aData[uiIndex] < (VAR_K(KTgMAX) + vARG_1.m_aData[uiIndex]))
            {
                vResult.m_aData[uiIndex] = VAR_K(KTgMAX);
            }
            else
            {
                vResult.m_aData[uiIndex] = (VAR_T())((vARG_0.m_aData[uiIndex] - vARG_1.m_aData[uiIndex]));
            };
        };
    };

    return (vResult);
}


/* =============================================================================================================================================================================== */
#endif
