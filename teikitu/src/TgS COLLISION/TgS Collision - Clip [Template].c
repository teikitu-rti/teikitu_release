/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Clip [Template].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COLLISION/TgS Collision - Segment.inl"

#include "TgS COLLISION/TgS Collision - Box [Util].inl"
#include "TgS COLLISION/TgS Collision - Capsule [Util].inl"
#include "TgS COLLISION/TgS Collision - Triangle [Util].inl"

#include "TgS COLLISION/TgS Collision - Box-Linear.inl"

#include "TgS COLLISION/TgS Collision - Capsule-Segment.inl"
#include "TgS COLLISION/TgS Collision - Cylinder-Segment.inl"
#include "TgS COLLISION/TgS Collision - Plane-Segment.inl"
#include "TgS COLLISION/TgS Collision - Sphere-Segment.inl"

#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCN_CO(Clip) ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_CO(Clip)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, PRIM_CPC psPM0 )
{
    TgRSIZE                             uiIdx = 0, nuiCount = 0;
    TgBOOL                              bFirst = false;
    VEC_T(1)                            vG0, vG1, vOne;
    VEC_T(1,CPC)                        avData = psCL->m_avPoint;
    VEC_T(1,P)                          avPoint;

    TgALLOCA( VEC_T(1), (TgUINT_F32)psCL->m_nuiPoint + 2u, avPoint );

    if (!avPoint || psCL->m_nuiMax <= 2)
    {
        /* Integrity check on the data stream.  There must exist at least two points in the clip list. */
        return (KTgE_FAIL);
    };

    vOne = FCN_V(tgMH_SET1)( TYPE_K(1) );

    /* First iterate to find the first point contained inside of the tube. */
    for (; uiIdx < psCL->m_nuiPoint; ++uiIdx)
    {
        /* Check to see if the point is contained within the primitive */

        if (!FCN_GM(Is_Contained)( psPM0, avData[uiIdx] ))
        {
            continue;
        };

        if (uiIdx != 0)
        {
            /* F_Clip the line segment from iPrevIdx to uiIdx to the primitive, adding the clipped point to the list */
            if (TgSUCCEEDED( FCN_CO(Clip_Points)( &vG0, &vG1, psPM0, avData[uiIdx], avData[uiIdx - 1] ) ))
            {
                VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL)( vG1, avData[uiIdx - 1] );
                VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SUB)( vOne, vG1 ), avData[uiIdx] );

//#                TgERROR( (!FCN_F(tgPM_NAN)(fG1)) && fG1 > TYPE_K(0) && fG1 < TYPE_K(1) );

                avPoint[nuiCount++] = FCN_V(tgMH_ADD)( vK1, vK0 );
            }
            else
            {
                TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"tgCO_Internal_Clip did not find intersection." );
            };
        }
        else
        {
            bFirst = true;
        };

        /* Add the first point contained by the primitive */

        avPoint[nuiCount++] = avData[uiIdx];

        break;
    };

    /*  Either all points have been found to be outside of the primitive, which will cause processing to logically terminate or the first point contained within the */
    /* primitive has been isolated. Further processing is done by sequentially adding contained points or clipping the segment between a known contained point and an */
    /* unconstrained point. */
    for (; uiIdx < psCL->m_nuiPoint; ++uiIdx)
    {
        TgRSIZE                             uiNIdx = (uiIdx + 1) % psCL->m_nuiPoint;

        /* Check to see if the point is contained inside the primitive */

        if (!FCN_GM(Is_Contained)( psPM0, avData[uiNIdx] ))
        {
            /* F_Clip the line segment from uiIdx to uiNIdx to the primitive, adding the clipped point to the list */
            if (TgSUCCEEDED( FCN_CO(Clip_Points)( &vG0, &vG1, psPM0, avData[uiIdx], avData[uiNIdx] ) ))
            {
//#                TgERROR( (!FCN_F(tgPM_NAN)( fG1 )) && fG1 > TYPE_K(0) && fG1 < TYPE_K(1) );
                if (nuiCount >= psCL->m_nuiMax)
                {
                    TgFREEA( avPoint );
                    return (KTgE_FAIL);
                }
                else
                {
                    VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SUB)( vOne, vG1 ), avData[uiIdx] );
                    VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL)( vG1, avData[uiNIdx] );

                    avPoint[nuiCount++] = FCN_V(tgMH_ADD)( vK1, vK2 );
                };
            }
            else
            {
                TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"tgCO_Internal_Clip did not find intersection." );
            };

            /* Continue through the list until a new valid point is found */
            for (++uiIdx; uiIdx < psCL->m_nuiPoint; ++uiIdx)
            {
                uiNIdx = (uiIdx + 1) % psCL->m_nuiPoint;

                /* Check to see if the point is contained within the primitive */

                if (!FCN_GM(Is_Contained) (psPM0, avData[uiNIdx] ))
                {
                    continue;
                }

                /* F_Clip the line segment from uiIdx to uiNIdx to the primitive, adding the clipped point to the list */
                if (TgSUCCEEDED( FCN_CO(Clip_Points)( &vG0, &vG1, psPM0, avData[uiNIdx], avData[uiIdx] ) ))
                {
//#                    TgERROR( (!FCN_F(tgPM_NAN)( fG1 )) && fG1 > TYPE_K(0) && fG1 < TYPE_K(1) );
                    if (nuiCount >= psCL->m_nuiMax)
                    {
                        TgFREEA( avPoint );
                        return (KTgE_FAIL);
                    }
                    else
                    {
                        VEC_T(1,C)      vK4 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SUB)( vOne, vG1 ), avData[uiNIdx] );
                        VEC_T(1,C)      vK5 = FCN_V(tgMH_MUL)( vG1, avData[uiIdx] );

                        avPoint[nuiCount++] = FCN_V(tgMH_ADD)( vK4, vK5 );
                    }
                }
                else
                {
                    TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"tgCO_Internal_Clip did not find intersection." );
                };

                break;
            };

            if (uiIdx == psCL->m_nuiPoint - 1)
            {
                if (bFirst)
                {
                    /* F_Clip the line segment from uiIdx to uiNIdx to the primitive, adding the clipped point to the list */
                    if (TgSUCCEEDED( FCN_CO(Clip_Points)( &vG0, &vG1, psPM0, avData[0], avData[uiIdx] ) ))
                    {
//#                        TgERROR( (!FCN_F(tgPM_NAN)( fG1 )) && fG1 > TYPE_K(0) && fG1 < TYPE_K(1) );
                        if (nuiCount >= psCL->m_nuiMax)
                        {
                            TgFREEA( avPoint );
                            return (KTgE_FAIL);
                        }
                        else
                        {
                            VEC_T(1,C)      vK6 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SUB)( vOne, vG1 ), avData[0] );
                            VEC_T(1,C)      vK7 = FCN_V(tgMH_MUL)( vG1, avData[uiIdx] );

                            avPoint[nuiCount++] = FCN_V(tgMH_ADD)( vK6, vK7 );
                        }
                    }
                    else
                    {
                        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Algorithm - Tube F_Clip did not find intersection." );
                    };
                };

                break;
            };
        };

        if (nuiCount >= psCL->m_nuiMax)
        {
            TgFREEA( avPoint );
            return (KTgE_FAIL);
        };

        avPoint[nuiCount++] = avData[uiNIdx];
    };

    TgERROR( nuiCount < psCL->m_nuiMax );

    for (uiIdx = 0; uiIdx < nuiCount; ++uiIdx)
    {
        psCL->m_avPoint[uiIdx] = avPoint[uiIdx];
    };

    psCL->m_nuiPoint = nuiCount;
    TgFREEA( avPoint );

    return (KTgS_OK);
}


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* =============================================================================================================================================================================== */

/*# !defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    CLANG_WARN_SUPPRESS(alloca)

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #define PRIM_CPC VEC_OBJ_T(TgBOX,CPC)
    #define FCN_GM(A) FCN_VO(tgGM_BX_##A)
    #define FCN_CO(A) FCN_VO(tgCO_BX_##A)

        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__

        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 32
        #include __FILE__

    #undef FCN_CO
    #undef FCN_GM
    #undef PRIM_CPC

    #define PRIM_CPC VEC_OBJ_T(TgTUBE,CPC)
    #define FCN_GM(A) FCN_VO(tgGM_CP_##A)
    #define FCN_CO(A) FCN_VO(tgCO_CP_##A)

            #define TEMPLATE__VECTOR_DIM 4
            #define TEMPLATE__TYPE_SIZE 64
            #include __FILE__

            #define TEMPLATE__VECTOR_DIM 4
            #define TEMPLATE__TYPE_SIZE 32
            #include __FILE__

    #undef FCN_CO
    #undef FCN_GM
    #undef PRIM_CPC

    #define PRIM_CPC VEC_OBJ_T(TgTUBE,CPC)
    #define FCN_GM(A) FCN_VO(tgGM_CY_##A)
    #define FCN_CO(A) FCN_VO(tgCO_CY_##A)

            #define TEMPLATE__VECTOR_DIM 4
            #define TEMPLATE__TYPE_SIZE 64
            #include __FILE__

            #define TEMPLATE__VECTOR_DIM 4
            #define TEMPLATE__TYPE_SIZE 32
            #include __FILE__

    #undef FCN_CO
    #undef FCN_GM
    #undef PRIM_CPC

    #define PRIM_CPC VEC_OBJ_T(TgPLANE,CPC)
    #define FCN_GM(A) FCN_VO(tgGM_PN_##A)
    #define FCN_CO(A) FCN_VO(tgCO_PN_##A)

            #define TEMPLATE__VECTOR_DIM 4
            #define TEMPLATE__TYPE_SIZE 64
            #include __FILE__

            #define TEMPLATE__VECTOR_DIM 4
            #define TEMPLATE__TYPE_SIZE 32
            #include __FILE__

        #undef FCN_CO
        #undef FCN_GM
        #undef PRIM_CPC

    #define PRIM_CPC VEC_OBJ_T(TgSPHERE,CPC)
    #define FCN_GM(A) FCN_VO(tgGM_SP_##A)
    #define FCN_CO(A) FCN_VO(tgCO_SP_##A)

            #define TEMPLATE__VECTOR_DIM 4
            #define TEMPLATE__TYPE_SIZE 64
            #include __FILE__

            #define TEMPLATE__VECTOR_DIM 4
            #define TEMPLATE__TYPE_SIZE 32
            #include __FILE__

    #undef FCN_CO
    #undef FCN_GM
    #undef PRIM_CPC

    #define PRIM_CPC VEC_OBJ_T(TgSTRI,CPC)
    #define FCN_GM(A) FCN_VO(tgGM_ST_##A)
    #define FCN_CO(A) FCN_VO(tgCO_ST_##A)

            #define TEMPLATE__VECTOR_DIM 4
            #define TEMPLATE__TYPE_SIZE 64
            #include __FILE__

            #define TEMPLATE__VECTOR_DIM 4
            #define TEMPLATE__TYPE_SIZE 32
            #include __FILE__

    #undef FCN_CO
    #undef FCN_GM
    #undef PRIM_CPC

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD


/*# !defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif

/* =============================================================================================================================================================================== */

