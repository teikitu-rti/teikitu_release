/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Ellipse.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_ELLIPSE_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_EL_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_EL_Reset)( VEC_OBJ_T(TgELLIPSE,PCU) psEL0 )
{
    FCN_V(tgMH_CLI,3)( &psEL0->m_mReference_Frame );
    psEL0->m_vMajor = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psEL0->m_vMinor = FCN_V(tgMH_SET1)( TYPE_K(0) );
}


/* ---- FCN_VO(tgGM_EL_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_EL_Area)( VEC_OBJ_T(TgELLIPSE,CPCU) psEL0 )
{
    return (FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( VAR_K(KTgPI) ), FCN_V(tgMH_MUL)( psEL0->m_vMajor, psEL0->m_vMinor ) ));
}


/* ---- FCN_VO(tgGM_EL_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_EL_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgELLIPSE,CPCU) psEL0 )
{
    VEC_T(1)                            vA0, vA1, vA2, vC0;

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_EL_Is_Valid)( psEL0 ));

    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psEL0->m_mReference_Frame );

    {
        VEC_T(1,C)                          vR0 = FCN_V(tgMH_MUL)( psEL0->m_vMajor, vA0 );
        VEC_T(1,C)                          vR1 = FCN_V(tgMH_MUL)( psEL0->m_vMinor, vA2 );

        VEC_T(1,C)                          vV0 = FCN_V(tgMH_SUB)( vC0, vR0 );
        VEC_T(1,C)                          vV1 = FCN_V(tgMH_ADD)( vC0, vR0 );
        VEC_T(1,C)                          vV2 = FCN_V(tgMH_SUB)( vC0, vR1 );
        VEC_T(1,C)                          vV3 = FCN_V(tgMH_ADD)( vC0, vR1 );

        FCN_VO(tgGM_BA_Init_PT)( psBA0, vC0 );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, vV0 );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, vV1 );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, vV2 );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, vV3 );
    }
}


/* ---- FCN_VO(tgGM_EL_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_EL_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgELLIPSE,CPCU) psEL1, VEC_T(1,C) vDT )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vDT ));

    FCN_VO(tgGM_EL_BA)( psBA0, psEL1 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_EL_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_EL_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgELLIPSE,CPCU) psEL0, VEC_T(1,C) vDN )
{
    VEC_T(1)                            vA0, vA1, vA2, vC0;

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_EL_Is_Valid)( psEL0 ));

    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psEL0->m_mReference_Frame );

    {
        VEC_T(1,C)                          vDN_A0 = FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vDN, vA0 ) );
        VEC_T(1,C)                          vDN_A2 = FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vDN, vA2 ) );

        VEC_T(1,C)                          vV0 = FCN_V(tgMH_MUL)( psEL0->m_vMajor, vDN_A0 );
        VEC_T(1,C)                          vV1 = FCN_V(tgMH_MAD)( psEL0->m_vMinor, vDN_A2, vV0 );
        VEC_T(1,C)                          vV2 = FCN_V(tgMH_DOT)( vDN, vC0 );

        *pvMin = FCN_V(tgMH_SUB)( vV2, vV1 );
        *pvMax = FCN_V(tgMH_ADD)( vV2, vV1 );
    }
}


/* ---- FCN_VO(tgGM_EL_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_EL_Is_Contained)( VEC_OBJ_T(TgELLIPSE,CPCU) psEL0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vA0, vA1, vA2, vC0;

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_EL_Is_Valid)( psEL0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    if ((FCN_V(tgMH_Is_NR0)( psEL0->m_vMajor )) || (FCN_V(tgMH_Is_NR0)( psEL0->m_vMinor )))
    {
        return (false);
    };

    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psEL0->m_mReference_Frame );

    {
        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, vC0 );
        VEC_T(1,C)                          vDS_A1 = FCN_V(tgMH_DOT)( vDS, vA1 );

        if (!FCN_V(tgMH_Is_NR0)( vDS_A1 ))
        {
            return (false);
        }
        else
        {
            VEC_T(1,C)                          vDS_A0 = FCN_V(tgMH_DOT)( vDS, vA0 );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDS_A0, psEL0->m_vMajor ) ))
            {
                return (false);
            }
            else
            {
                VEC_T(1,C)                          vDS_A2 = FCN_V(tgMH_DOT)( vDS, vA2 );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDS_A2, psEL0->m_vMinor ) ))
                {
                    return (false);
                }
                else
                {
                    return (true);
                };
            };
        };
    };
}


/* ---- FCN_VO(tgGM_EL_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_EL_TX)( VEC_OBJ_T(TgELLIPSE,PCU) psEL0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    FCN_V(tgMH_CAT,3)( &psEL0->m_mReference_Frame, &psEL0->m_mReference_Frame, pmM0 );
}


/* ---- FCN_VO(tgGM_EL_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_EL_Copy_TX)( VEC_OBJ_T(TgELLIPSE,PCU) psEL0, VEC_OBJ_T(TgELLIPSE,CPCU) psEL1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_EL_Is_Valid)( psEL1 ) && !FCN_V(tgMH_NAN,3)( pmM0 ));

    FCN_V(tgMH_CAT,3)( &psEL0->m_mReference_Frame, &psEL1->m_mReference_Frame, pmM0 );
    psEL0->m_vMajor = psEL1->m_vMajor;
    psEL0->m_vMinor = psEL1->m_vMinor;
}


/* ---- FCN_VO(tgGM_EL_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_EL_Init)( VEC_OBJ_T(TgELLIPSE,PCU) psEL0, VEC_T(3,CPCU) pmM0, VEC_T(1,C) vMaj, VEC_T(1,C) vMin )
{
    FCN_VO(tgGM_EL_Set_Reference_Frame)( psEL0, pmM0 );
    FCN_VO(tgGM_EL_Set_Major_Radius)( psEL0, vMaj );
    FCN_VO(tgGM_EL_Set_Minor_Radius)( psEL0, vMin );
}


/* ---- FCN_VO(tgGM_EL_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_EL_Copy)( VEC_OBJ_T(TgELLIPSE,PCU) psEL0, VEC_OBJ_T(TgELLIPSE,CPCU) psEL1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_EL_Is_Valid)( psEL1 ));

    psEL0->m_mReference_Frame = psEL1->m_mReference_Frame;
    psEL0->m_vMajor = psEL1->m_vMajor;
    psEL0->m_vMinor = psEL1->m_vMinor;
}


/* ---- FCN_VO(tgGM_EL_Set_Reference_Frame) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_EL_Set_Reference_Frame)( VEC_OBJ_T(TgELLIPSE,PCU) psEL0, VEC_T(3,CPCU) pmReference_Frame )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Reference_Frame,3)( pmReference_Frame ));

    psEL0->m_mReference_Frame = *pmReference_Frame;
}


/* ---- FCN_VO(tgGM_EL_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_EL_Set_Origin)( VEC_OBJ_T(TgELLIPSE,PCU) psEL0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));
    FCN_V(tgMH_Set_T,3)( &psEL0->m_mReference_Frame, vS0 );
}


/* ---- FCN_VO(tgGM_EL_Set_Major_Radius) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_EL_Set_Major_Radius)( VEC_OBJ_T(TgELLIPSE,PCU) psEL0, VEC_T(1,C) vRadius )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( vRadius ));
    psEL0->m_vMajor = vRadius;
}


/* ---- FCN_VO(tgGM_EL_Set_Minor_Radius) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_EL_Set_Minor_Radius)( VEC_OBJ_T(TgELLIPSE,PCU) psEL0, VEC_T(1,C) vRadius )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( vRadius ));
    psEL0->m_vMinor = vRadius;
}


/* ---- FCN_VO(tgGM_EL_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_EL_Query_Origin)( VEC_OBJ_T(TgELLIPSE,CPCU) psEL0 )
{
    return (FCN_V(tgMH_Query_Axis_3,3)( &psEL0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_EL_Query_Major_Unit) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_EL_Query_Major_Unit)( VEC_OBJ_T(TgELLIPSE,CPCU) psEL0 )
{
    return (FCN_V(tgMH_Query_Axis_0,3)( &psEL0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_EL_Query_Normal) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_EL_Query_Normal)( VEC_OBJ_T(TgELLIPSE,CPCU) psEL0 )
{
    return (FCN_V(tgMH_Query_Axis_1,3)( &psEL0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_EL_Query_Minor_Unit) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_EL_Query_Minor_Unit)( VEC_OBJ_T(TgELLIPSE,CPCU) psEL0 )
{
    return (FCN_V(tgMH_Query_Axis_2,3)( &psEL0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_EL_Query_Major_Radius) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_EL_Query_Major_Radius)( VEC_OBJ_T(TgELLIPSE,CPCU) psEL0 )
{
    return (psEL0->m_vMajor);
}


/* ---- FCN_VO(tgGM_EL_Query_Minor_Radius) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_EL_Query_Minor_Radius)( VEC_OBJ_T(TgELLIPSE,CPCU) psEL0 )
{
    return (psEL0->m_vMinor);
}


/* =============================================================================================================================================================================== */
#endif
