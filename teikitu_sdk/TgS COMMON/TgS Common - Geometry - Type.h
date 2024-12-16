/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_TYPE_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_STRUCT( VEC_OBJ_T(TgDELTA), )
{
    VEC_T(1)                                    m_vUDT; /* Unit Displacement */
    VEC_T(1)                                    m_vDT; /* Displacement */
    VEC_T(1)                                    m_vMag_DT; /* Displacement Magnitude */
    VEC_T(1)                                    m_vDT_DT; /* Displacement Magnitude Squared */
    VEC_T(1)                                    m_vInv_Mag_DT; /* Inverse Magnitude of Displacement */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgRECT2D), )
{
    VEC_UN_T(1)                                 m_uRect;
};


TgTYPE_STRUCT( VEC_OBJ_T(TgBOXAA), )
{
    VEC_T(1)                                    m_vMin, m_vMax;
};


TgTYPE_STRUCT( VEC_OBJ_T(TgBOX), )
{
    VEC_T(3)                                    m_mReference_Frame; /**< Full reference frame (ortho-normal basis and position) */
    VEC_T(1)                                    m_vExtent;
};


TgTYPE_STRUCT( VEC_OBJ_T(TgCIRCLE), )
{
    VEC_T(3)                                    m_mReference_Frame; /**< Full reference frame (ortho-normal basis and position) */
    VEC_T(1)                                    m_vRadius; /**< Radius of the circle. */
    VEC_T(1)                                    m_vRadiusSq;/**< Radius Squared of the circle. */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgELLIPSE), )
{
    VEC_T(3)                                    m_mReference_Frame; /**< Full reference frame (columns are: major axis, normal, minor axis, origin) */
    VEC_T(1)                                    m_vMajor; /**< Major radius. */
    VEC_T(1)                                    m_vMinor; /**< Minor radius. */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgLINE), )
{
    VEC_T(1)                                    m_vOrigin; /**< Origin of the line segment (start point). */
    VEC_T(1)                                    m_vDirN; /**< The line direction. */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgMESH_SIMPLE), )
{
    VEC_T(1,P)                                  m_pvVert_List;
    TgUINT_E16_P                                m_puiIndx_List;
    TgRSIZE                                     m_nuiVert; /**< Number of vertices in the mesh */
    TgRSIZE                                     m_nuiIndx; /**< Number of indices in the mesh, can be zero depending on primitive expectations */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgMESH_BA), )
{
    VEC_OBJ_T(TgMESH_SIMPLE)                    m_sMS; /**< Vertex and Face Data */

    VEC_T(1,P)                                  m_pvVert_DT; /**< Vertex delta for a swept mesh */
    VEC_OBJ_T(TgBOXAA,P)                        m_psBA; /**< Bounding box per face */
    VEC_OBJ_T(TgDELTA)                          m_sDT; /**< Linear displacement vector, valid only for linear sweep. */
    VEC_T(1)                                    m_vCG[2]; /**< Centre of gravity at sweep interval. */
    TgUINT_E32_P                                m_puiFlags; /**< Collision flags per face */
    TgUINT_E32                                  m_nuiFace; /**< Number of faces */
    ETgSWEEP_TYPE                               m_enSweep; /**< Static, Linear or Rotational test indicator. */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgMESH_BVT), )
{
    VEC_OBJ_T(TgMESH_SIMPLE)                    m_sMS; /**< Vertex and Face Data */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgPARALLELOGRAM), )
{
    VEC_T(1)                                    m_vOrigin; /**< Common point of two of the parallelogram's edges. */
    VEC_T(1)                                    m_avEdge[2]; /**< The two edge's sourced at the origin point. */
    VEC_T(1)                                    m_vNormal; /**< The normal for the plane defined by the two edges. */
    VEC_T(1)                                    m_avEdge_Normal[2]; /**< The normal of the plane defined by an edge and normal. */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgPARTICLE), )
{
    VEC_T(1)                                    m_vPos; /**< Initial position. */
    VEC_T(1)                                    m_vVel; /**< Initial velocity. */
    VEC_T(1)                                    m_vAccel; /**< Initial acceleration. */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgPLANE), )
{
    VEC_T(1)                                    m_vPlnEqN; /**< Store the plane constant in the last element of the vector. Nx(x) + Ny(y) + Nz(z) + D = 0*/
    VEC_T(1)                                    m_vNormal; /**< Plane unit-normal. */
    VEC_T(1)                                    m_vD; /**< Plane constant. */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgRAY), )
{
    VEC_T(1)                                    m_vOrigin; /**< Origin of the line segment (start point). */
    VEC_T(1)                                    m_vDirN; /**< The line direction. */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgRECTANGLE), )
{
    VEC_T(1)                                    m_vOrigin; /**< Common point of two of the rectangle's edges. */
    VEC_T(1)                                    m_avEdge[2]; /**< The two edge's sourced at the origin point. */
    VEC_T(1)                                    m_vNormal; /**< The normal for the plane defined by the two edges. */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgSEGMENT), )
{
    VEC_T(1)                                    m_vOrigin; /**< Origin of the line segment (start point). */
    VEC_T(1)                                    m_vDirN; /**< The line direction. */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgSPHERE), )
{
    VEC_T(1)                                    m_vOrigin; /**< Origin of the sphere. */
    VEC_T(1)                                    m_vRadius; /**< Radius of the sphere - broadcast across all lanes */
    VEC_T(1)                                    m_vRadiusSq; /**< Radius square of the sphere - broadcast across all lanes */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgTORUS), )
{
    VEC_OBJ_T(TgCIRCLE)                         m_sCI;
    VEC_T(1)                                    m_vRI; /**< Radius of the tube. */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgPTRI), )
{
    VEC_T(1)                                    m_avPoint[3]; /**< Three vertices defining the triangle */
    VEC_T(1)                                    m_vNormal; /**< Triangle normal, not necessarily valid. */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgETRI), )
{
    VEC_OBJ_T(TgPTRI)                           m_sPT;
    VEC_T(1)                                    m_avEdge[3]; /**< [0-1], [1-2], [2-0] segments between vertices */
};


TgTYPE_STRUCT( VEC_OBJ_T(TgCTRI), )
{
    VEC_OBJ_T(TgETRI)                           m_sET;
    TgUINT_E32                                  m_bfFlags; /**< Bitfield container for a collection of booleans. */
#if 0 != STRUCT_PAD(12,12)
    TgUINT_E08                                  m_iPad[STRUCT_PAD(12,12)];
#endif
};


TgTYPE_STRUCT( VEC_OBJ_T(TgSTRI), )
{
    VEC_OBJ_T(TgCTRI)                           m_sCT;
    VEC_OBJ_T(TgPLANE)                          m_avPlane[3];
};


/* Tube definition - centre point and the vector such that its sum and difference with the origin are the two end points. */
TgTYPE_STRUCT( VEC_OBJ_T(TgTUBE), )
{
    VEC_T(3)                                    m_mReference_Frame; /**< Full reference frame (ortho-normal basis and position) */
    VEC_T(1)                                    m_vHAX; /**< Primary half-axis of the tube */
    VEC_OBJ_T(TgSEGMENT)                        m_sAX; /**< Segment from end-to-end of the tube */
    VEC_T(1)                                    m_vRadius; /**< Radius of the tube */
    VEC_T(1)                                    m_vExtent; /**< Half-height of the tube */
    VEC_T(1)                                    m_vRadiusSq; /**< Radius Squared */
};



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgINLINE TgVOID
FCN_VO(tgGM_DT_Reset)(
    VEC_OBJ_T(TgDELTA,PCU) TgANALYSIS_NO_NULL ARG0 );

TgINLINE TgBOOL
FCN_VO(tgGM_DT_Is_Valid)(
    VEC_OBJ_T(TgDELTA,CPCU) );

TgINLINE TgVOID
FCN_VO(tgGM_DT_TX)(
    VEC_OBJ_T(TgDELTA,PCU), VEC_T(3,CPCU) );

TgINLINE TgVOID
FCN_VO(tgGM_DT_Copy_TX)(
    VEC_OBJ_T(TgDELTA,PCU), VEC_OBJ_T(TgDELTA,CPCU), VEC_T(3,CPCU) );

TgINLINE TgVOID
FCN_VO(tgGM_DT_Set)(
    VEC_OBJ_T(TgDELTA,PCU), VEC_T(1,C) );


/* =============================================================================================================================================================================== */
#endif
