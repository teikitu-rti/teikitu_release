/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Triangle [Edge].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
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

/* ---- FCN_VO(tgGM_ET_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgGM_ET_Is_Valid)( VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    if (!FCN_VO(tgGM_PT_Is_Valid)( &psET1->m_sPT) )
    {
        return (false);
    };

    /* Sanity Check: on the edge size. */

    if (!FCN_V(tgMH_Is_Valid_Vector)( psET1->m_avEdge[0] ) || FCN_V(tgMH_Is_PRX_CMP_EQ)( psET1->m_avEdge[0], FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Vector)( psET1->m_avEdge[1] ) || FCN_V(tgMH_Is_PRX_CMP_EQ)( psET1->m_avEdge[1], FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Vector)( psET1->m_avEdge[2] ) || FCN_V(tgMH_Is_PRX_CMP_EQ)( psET1->m_avEdge[2], FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_ET_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgGM_ET_Support_Point)( VEC_OBJ_T(TgETRI,CPCU) psET0, VEC_T(1,C) vDN )
{
    VEC_UN_T(1,C)                       uDN_E0 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( vDN, psET0->m_avEdge[0] ) };
    VEC_UN_T(1,C)                       uDN_E2 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_NEG)( FCN_V(tgMH_DOT)( vDN, psET0->m_avEdge[2] ) ) };

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_ET_Is_Valid)( psET0 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    if (FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uDN_E0).x ) && FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uDN_E2).x ))
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( psET0->m_avEdge[0], psET0->m_avEdge[2] );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( VAR_K(KTgTHIRD) ), vX0 );

        return (FCN_V(tgMH_ADD)( psET0->m_sPT.m_avPoint[0], vX1 ));
    }

    if (!(VEC_S_UN_1_MEMBER(uDN_E0).x < TYPE_K(0)))
    {
        if (VEC_S_UN_1_MEMBER(uDN_E2).x > VEC_S_UN_1_MEMBER(uDN_E0).x)
        {
            return (FCN_V(tgMH_SUB)( psET0->m_sPT.m_avPoint[0], psET0->m_avEdge[2] ));
        }
        else
        {
            return (FCN_V(tgMH_ADD)( psET0->m_sPT.m_avPoint[0], psET0->m_avEdge[0] ));
        };
    }
    else if (!(VEC_S_UN_1_MEMBER(uDN_E2).x < TYPE_K(0)))
    {
        return (FCN_V(tgMH_SUB)( psET0->m_sPT.m_avPoint[0], psET0->m_avEdge[2] ));
    };

    return (psET0->m_sPT.m_avPoint[0]);
}


/* ---- FCN_VO(tgGM_ET_Is_Tri_Edge_Ignored) -------------------------------------------------------------------------------------------------------------------------------------- */
/** Edge culling is used in different ways by the different systems.  Sometimes the desired approach is to have an edge included one time even if it's marked to be ignored. For
    instance, during penetration collisions calls it is necessary to ignore an edge in determining the method of separation (normal) but in contact reduction the edge has to be
    considered at least once. */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgGM_ET_Is_Tri_Edge_Ignored)( VEC_OBJ_T(TgETRI,CPCU) psET0, VEC_T(1,C) vT0, VEC_T(1,C) vT1 )
{
    VEC_UN_T(1)                         uU0;

    if (FCN_V(tgMH_Is_NR0)( vT1 ))
    {   /*  Edge generated by vertex 0 and vertex 1 */
        VEC_UN_1_MEMBER(uU0) = psET0->m_avEdge[0];
    }
    else if (FCN_V(tgMH_Is_NR0)( vT0 ))
    {   /* Edge generated by vertex 0 and vertex 2 */
        VEC_UN_1_MEMBER(uU0) = psET0->m_avEdge[2];
    }
    else
    {   /*  Edge generated by vertex 1 and vertex 2 */
        VEC_UN_1_MEMBER(uU0) = psET0->m_avEdge[1];
        TgERROR(FCN_V(tgMH_Is_NR1)( FCN_V(tgMH_ADD)( vT0, vT1 ) ));
    };

    if (VEC_S_UN_1_MEMBER(uU0).x != TYPE_K(0))
    {
        return (VEC_S_UN_1_MEMBER(uU0).x <= TYPE_K(0));
    }
    else if (VEC_S_UN_1_MEMBER(uU0).y != TYPE_K(0))
    {
        return (VEC_S_UN_1_MEMBER(uU0).y <= TYPE_K(0));
    }
    else
    {
        TgERROR(VEC_S_UN_1_MEMBER(uU0).z != TYPE_K(0));
        return (VEC_S_UN_1_MEMBER(uU0).z <= TYPE_K(0));
    };
}


/* ---- FCN_VO(tgGM_ET_Is_Tri_Edge_Ignored_Code) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgGM_ET_Is_Tri_Edge_Ignored_Code)( VEC_OBJ_T(TgETRI,CPCU) psET0, TgRSIZE_C iEdge )
{
    VEC_UN_T(1)                         uU0;

    if (0 == iEdge)
    {   /*  Edge generated by vertex 0 and vertex 1 */
        VEC_UN_1_MEMBER(uU0) = psET0->m_avEdge[0];
    }
    else if (2 == iEdge)
    {   /* Edge generated by vertex 0 and vertex 2 */
        VEC_UN_1_MEMBER(uU0) = psET0->m_avEdge[2];
    }
    else
    {   /*  Edge generated by vertex 1 and vertex 2 */
        VEC_UN_1_MEMBER(uU0) = psET0->m_avEdge[1];
        TgERROR(1 == iEdge);
    };

    if (VEC_S_UN_1_MEMBER(uU0).x != TYPE_K(0))
    {
        return (VEC_S_UN_1_MEMBER(uU0).x <= TYPE_K(0));
    }
    else if (VEC_S_UN_1_MEMBER(uU0).y != TYPE_K(0))
    {
        return (VEC_S_UN_1_MEMBER(uU0).y <= TYPE_K(0));
    }
    else
    {
        TgERROR(VEC_S_UN_1_MEMBER(uU0).z != TYPE_K(0));
        return (VEC_S_UN_1_MEMBER(uU0).z <= TYPE_K(0));
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
