/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box-Sphere.c
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


/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_SP_Penetrate_BX) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_SP_Penetrate_BX)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgBOX,CPC) psBX0 )
{
    TgPARAM_CHECK( FCN_VO(tgGM_BX_Is_Valid)(psBX0) && FCN_VO(tgGM_SP_Is_Valid)(psSP0) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else
    {
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
        VEC_T(1)                            vBX0_U0, vBX0_U1, vBX0_U2, vBX0_OG;
        TgRESULT                            iResult = FCN_V(tgMH_Query_Reference_Frame,3)( &vBX0_U0, &vBX0_U1, &vBX0_U2, &vBX0_OG, &psBX0->m_mReference_Frame );

        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( psSP0->m_vOrigin, vBX0_OG );

        /* Determine the point that is contained within the box that is closest to the sphere origin. This is done by projecting the difference between the two primitives' origins
           along the box reference frame, and limiting the projection to the limits of the box along each axis. If projection is further than a radius away from the box surface
           then the axis is a separating axis, and there is no contact between the primitives. */

        VEC_T(1,C)                          vDS__BX0_U0 = FCN_V(tgMH_DOT)( vDS, vBX0_U0 );
        VEC_T(1,C)                          vEXT__DS__BX0_U0 = FCN_V(tgMH_ABS)( vDS__BX0_U0 );
        VEC_T(1,C)                          vEXT__BX0_U0 = FCN_V(tgMH_SPX)( psBX0->m_vExtent );
        TgBOOL_C                            bExceed_BX0_E0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vEXT__DS__BX0_U0, vEXT__BX0_U0 ) );
        VEC_T(1,C)                          vP0 = FCN_V(tgMH_CP_SGN)( FCN_V(tgMH_MIN)( vEXT__DS__BX0_U0, vEXT__BX0_U0 ), vDS__BX0_U0 );

        VEC_T(1,C)                          vDS__BX0_U1 = FCN_V(tgMH_DOT)( vDS, vBX0_U1 );
        VEC_T(1,C)                          vEXT__DS__BX0_U1 = FCN_V(tgMH_ABS)( vDS__BX0_U1 );
        VEC_T(1,C)                          vEXT__BX0_U1 = FCN_V(tgMH_SPY)( psBX0->m_vExtent );
        TgBOOL_C                            bExceed_BX0_E1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vEXT__DS__BX0_U1, vEXT__BX0_U1 ) );
        VEC_T(1,C)                          vP1 = FCN_V(tgMH_CP_SGN)( FCN_V(tgMH_MIN)( vEXT__DS__BX0_U1, vEXT__BX0_U1 ), vDS__BX0_U1 );

        VEC_T(1,C)                          vDS__BX0_U2 = FCN_V(tgMH_DOT)( vDS, vBX0_U2 );
        VEC_T(1,C)                          vEXT__DS__BX0_U2 = FCN_V(tgMH_ABS)( vDS__BX0_U2 );
        VEC_T(1,C)                          vEXT__BX0_U2 = FCN_V(tgMH_SPZ)( psBX0->m_vExtent );
        TgBOOL_C                            bExceed_BX0_E2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vEXT__DS__BX0_U2, vEXT__BX0_U2 ) );
        VEC_T(1,C)                          vP2 = FCN_V(tgMH_CP_SGN)( FCN_V(tgMH_MIN)( vEXT__DS__BX0_U2, vEXT__BX0_U2 ), vDS__BX0_U2 );

        (void)iResult;

        if (bExceed_BX0_E0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_SUB)( vEXT__DS__BX0_U0, vEXT__BX0_U0 ), psSP0->m_vRadius ) ))
        {
            return (KTgE_NO_INTERSECT);
        };

        if (bExceed_BX0_E1 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_SUB)( vEXT__DS__BX0_U1, vEXT__BX0_U1 ), psSP0->m_vRadius ) ))
        {
            return (KTgE_NO_INTERSECT);
        };

        if (bExceed_BX0_E2 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_SUB)( vEXT__DS__BX0_U2, vEXT__BX0_U2 ), psSP0->m_vRadius ) ))
        {
            return (KTgE_NO_INTERSECT);
        };

        /*  If the origin lies outside even one face then calculating the penetration contact is done by simply creating the point of closest proximity on the box to the sphere
            origin. This point is the contact point, and the vector difference is the normal of contact. */

        if (bExceed_BX0_E0 || bExceed_BX0_E1 || bExceed_BX0_E2)
        {
            VEC_T(1)                            vMAG_NM;

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vP0, vP1, vP2 );
            psContact->m_vN0 = FCN_V(tgMH_NORM_LEN)( &vMAG_NM, FCN_V(tgMH_SUB)( psContact->m_vS0, psSP0->m_vOrigin ) );
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = FCN_V(tgMH_SUB)( psSP0->m_vRadius, vMAG_NM );

            /* Need to validate that the resulting point is within the sphere. */
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vMAG_NM, psSP0->m_vRadius ) ))
            {
                return (KTgE_NO_INTERSECT);
            }
            else
            {
                ++psPacket->m_nuiContact;
                return (KTgS_OK);
            }
        }
        else
        {
            /*  The sphere origin must be contained within the box.  Penetration is determined by finding the axis of minimum penetration and creating a contact to eject the
                sphere out of the nearest face aligned with that axis.  All of the measurements must be negative (ie the point is contained), thus, it is the least negative
                (or the greatest value) that determines the axis what has the minimal penetration. */

            VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vEXT__BX0_U0, vEXT__DS__BX0_U0 );
            VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vEXT__BX0_U1, vEXT__DS__BX0_U1 );
            VEC_T(1,C)                          vX2 = FCN_V(tgMH_SUB)( vEXT__BX0_U2, vEXT__DS__BX0_U2 );

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
            psContact->m_vS0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vP0, vP1, vP2 );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX0, vX1 ) ))
            {
                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX0, vX2 ) ))
                {
                    VEC_T(1,C)                          vK0 = FCN_V(tgMH_CP_SGN)( vEXT__BX0_U0, vP0 );
                    VEC_T(1,C)                          vN0 = FCN_V(tgMH_CP_SGN)( FCN_VO(tgGM_BX_Query_Axis_Unit_0)( psBX0 ), vP0 );

                    psContact->m_vS0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vK0, vP1, vP2 );
                    psContact->m_vN0 = vN0;
                    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    psContact->m_vDepth = FCN_V(tgMH_ADD)( psSP0->m_vRadius, FCN_V(tgMH_SUB)( vEXT__BX0_U0, vEXT__DS__BX0_U0 ) );

                    ++psPacket->m_nuiContact;

                    return (KTgS_OK);
                }
                else
                {
                    VEC_T(1,C)                          vK0 = FCN_V(tgMH_CP_SGN)( vEXT__BX0_U2, vP2 );
                    VEC_T(1,C)                          vN0 = FCN_V(tgMH_CP_SGN)( FCN_VO(tgGM_BX_Query_Axis_Unit_2)( psBX0 ), vP2 );

                    psContact->m_vS0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vP0, vP1, vK0 );
                    psContact->m_vN0 = vN0;
                    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    psContact->m_vDepth = FCN_V(tgMH_ADD)( psSP0->m_vRadius, FCN_V(tgMH_SUB)( vEXT__BX0_U2, vEXT__DS__BX0_U2 ) );

                    ++psPacket->m_nuiContact;

                    return (KTgS_OK);
                };
            }
            else
            {
                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX1, vX2 ) ))
                {
                    VEC_T(1,C)                          vK0 = FCN_V(tgMH_CP_SGN)( vEXT__BX0_U1, vP1 );
                    VEC_T(1,C)                          vN0 = FCN_V(tgMH_CP_SGN)( FCN_VO(tgGM_BX_Query_Axis_Unit_1)( psBX0 ), vP1 );

                    psContact->m_vS0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vP0, vK0, vP2 );
                    psContact->m_vN0 = vN0;
                    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    psContact->m_vDepth = FCN_V(tgMH_ADD)( psSP0->m_vRadius, FCN_V(tgMH_SUB)( vEXT__BX0_U1, vEXT__DS__BX0_U1 ) );

                    ++psPacket->m_nuiContact;

                    return (KTgS_OK);
                }
                else
                {
                    VEC_T(1,C)                          vK0 = FCN_V(tgMH_CP_SGN)( vEXT__BX0_U2, vP2 );
                    VEC_T(1,C)                          vN0 = FCN_V(tgMH_CP_SGN)( FCN_VO(tgGM_BX_Query_Axis_Unit_2)( psBX0 ), vP2 );

                    psContact->m_vS0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vP0, vP1, vK0 );
                    psContact->m_vN0 = vN0;
                    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    psContact->m_vDepth = FCN_V(tgMH_ADD)( psSP0->m_vRadius, FCN_V(tgMH_SUB)( vEXT__BX0_U2, vEXT__DS__BX0_U2 ) );

                    ++psPacket->m_nuiContact;

                    return (KTgS_OK);
                };
            };
        };
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
