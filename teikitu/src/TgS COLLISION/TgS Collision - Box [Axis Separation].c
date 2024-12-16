/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box [Axis Separation].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
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

/* ---- FCN_VO(tgCO_BX_Axis_ProjInfo) -------------------------------------------------------------------------------------------------------------------------------------------- */
/*   Their are a few different ways, depending on relative orientation, that a box's vertices can be mapped onto a line. First, if the axis is identical to one of the box's axes  */
/* then the four points on each face that is normal to the line will be projected only onto one unique point ( two in total for the entire box ). The second way would be if the   */
/* line is parallel to one of the box's faces. The four vertices defining the face to which the line is parallel would each map to a unique point. However, the other four points  */
/* would map one to one to the existing projections since the edge formed between the two faces is normal to the line in question (by definition). The last case has the line      */
/* being in arbitrary orientation, non - collinear or co-planar to the box in any way.                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_VO(tgCO_BX_Axis_ProjInfo)( VEC_OBJ_T(STg2_CO_Axis_Project,PC) psConfig, VEC_T(1,C) vAxis, VEC_OBJ_T(TgBOX,CPC) psBX0 )
{
    VEC_T(1)                            vA0, vA1, vA2, vC0;
    VEC_T(1)                            vAX_UX0, vAX_UX1, vAX_UX2, vABS_AX_EX0, vABS_AX_EX1, vABS_AX_EX2;
    TgBOOL                              vAX_UX0_GTZ, vAX_UX1_GTZ, vAX_UX2_GTZ;

    /* Project the vertices onto the normal from the first triangle. */

    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psBX0->m_mReference_Frame );

    vAX_UX0 = FCN_V(tgMH_DOT)( vA0, vAxis );
    vAX_UX1 = FCN_V(tgMH_DOT)( vA1, vAxis );
    vAX_UX2 = FCN_V(tgMH_DOT)( vA2, vAxis );

    vAX_UX0_GTZ = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vAX_UX0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
    vAX_UX1_GTZ = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vAX_UX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
    vAX_UX2_GTZ = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vAX_UX2, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );

    vABS_AX_EX0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPX)( psBX0->m_vExtent ), FCN_V(tgMH_ABS)( vAX_UX0 ) );
    vABS_AX_EX1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ), FCN_V(tgMH_ABS)( vAX_UX1 ) );
    vABS_AX_EX2 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPZ)( psBX0->m_vExtent ), FCN_V(tgMH_ABS)( vAX_UX2 ) );

    /* This is a direct sort using the projections as the key. */

    switch ((FCN_V(tgMH_Is_NR0)( vAX_UX0 ) ? 0 : 1) + (FCN_V(tgMH_Is_NR0)( vAX_UX1 ) ? 0 : 2) + (FCN_V(tgMH_Is_NR0)( vAX_UX2 ) ? 0 : 4))
    {
        case 7:
        { /* Unique maximal and minimal vertices */

            VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL)( vABS_AX_EX0, vA0 );
            VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL)( vABS_AX_EX1, vA1 );
            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL)( vABS_AX_EX2, vA2 );
            VEC_T(1,C)      vK4 = FCN_V(tgMH_ADD)( vK0, vK1 );
            VEC_T(1,C)      vK3 = FCN_V(tgMH_ADD)( vK4, vK2 );

            psConfig->m_avMinVert[0] = FCN_V(tgMH_SUB)( vC0, vK3 );
            psConfig->m_avMaxVert[0] = FCN_V(tgMH_ADD)( vC0, vK3 );
            psConfig->m_uiMinID = 1;
            psConfig->m_uiMaxID = 1;

            break;
        }

        case 6: /* Parallel to the x-axis normal-defined plane (perpendicular to x-axis). */

            if (vAX_UX1_GTZ)
            {
                psConfig->m_avMinVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 0u  : 4u) );
                psConfig->m_avMinVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 1u : 5u) );
                psConfig->m_avMaxVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 6u : 2u) );
                psConfig->m_avMaxVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 7u : 3u) );

            }
            else
            {
                psConfig->m_avMinVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 2u : 6u) );
                psConfig->m_avMinVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 3u : 7u) );
                psConfig->m_avMaxVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 4u : 0u) );
                psConfig->m_avMaxVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 5u : 1u) );
            };

            psConfig->m_uiMinID = 2;
            psConfig->m_uiMaxID = 2;

            break;

        case 5: /* Parallel to the y-axis normal-defined plane. */

            if (vAX_UX0_GTZ)
            {
                psConfig->m_avMinVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 0u : 4u) );
                psConfig->m_avMinVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 2u : 6u) );
                psConfig->m_avMaxVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 5u : 1u) );
                psConfig->m_avMaxVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 7u : 3u) );

            }
            else
            {
                psConfig->m_avMinVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 1u : 5u) );
                psConfig->m_avMinVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 3u : 7u) );
                psConfig->m_avMaxVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 4u : 0u) );
                psConfig->m_avMaxVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 6u : 2u) );
            };

            psConfig->m_uiMinID = 2;
            psConfig->m_uiMaxID = 2;

            break;

        case 4: /* Separation axis is parallel to box z-axis. */

            psConfig->m_avMinVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 0u : 4u) );
            psConfig->m_avMinVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 1u : 5u) );
            psConfig->m_avMinVert[2] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 2u : 6u) );
            psConfig->m_avMinVert[3] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 3u : 7u) );

            psConfig->m_avMaxVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 4u : 0u) );
            psConfig->m_avMaxVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 5u : 1u) );
            psConfig->m_avMaxVert[2] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 6u : 2u) );
            psConfig->m_avMaxVert[3] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX2_GTZ ? 7u : 3u) );

            psConfig->m_uiMinID = 4;
            psConfig->m_uiMaxID = 4;

            break;

        case 3: /* Parallel to the z-axis normal-defined plane. */

            if (vAX_UX0_GTZ)
            {
                psConfig->m_avMinVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 0u : 2u) );
                psConfig->m_avMinVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 4u : 6u) );
                psConfig->m_avMaxVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 3u : 1u) );
                psConfig->m_avMaxVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 7u : 5u) );

            }
            else
            {
                psConfig->m_avMinVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 1u : 3u) );
                psConfig->m_avMinVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 5u : 7u) );
                psConfig->m_avMaxVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 2u : 0u) );
                psConfig->m_avMaxVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 6u : 4u) );
            };

            psConfig->m_uiMinID = 2;
            psConfig->m_uiMaxID = 2;

            break;

        case 2: /* Separation axis is parallel to box y-axis. */

            psConfig->m_avMinVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 0u : 2u) );
            psConfig->m_avMinVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 1u : 3u) );
            psConfig->m_avMinVert[2] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 4u : 6u) );
            psConfig->m_avMinVert[3] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 5u : 7u) );

            psConfig->m_avMaxVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 2u : 0u) );
            psConfig->m_avMaxVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 3u : 1u) );
            psConfig->m_avMaxVert[2] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 6u : 4u) );
            psConfig->m_avMaxVert[3] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX1_GTZ ? 7u : 5u) );

            psConfig->m_uiMinID = 4;
            psConfig->m_uiMaxID = 4;

            break;

        case 1: /* Separation axis is parallel to box x-axis. */

            psConfig->m_avMinVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX0_GTZ ? 0u : 5u) );
            psConfig->m_avMinVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX0_GTZ ? 2u : 7u) );
            psConfig->m_avMinVert[2] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX0_GTZ ? 6u : 3u) );
            psConfig->m_avMinVert[3] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX0_GTZ ? 4u : 1u) );

            psConfig->m_avMaxVert[0] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX0_GTZ ? 5u : 0u) );
            psConfig->m_avMaxVert[1] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX0_GTZ ? 7u : 2u) );
            psConfig->m_avMaxVert[2] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX0_GTZ ? 3u : 6u) );
            psConfig->m_avMaxVert[3] = FCN_VO(tgGM_BX_Calc_Point_Index)( psBX0, (vAX_UX0_GTZ ? 1u : 4u) );

            psConfig->m_uiMinID = 4;
            psConfig->m_uiMaxID = 4;

            break;

        default:
            TgS_NO_DEFAULT(return);
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
