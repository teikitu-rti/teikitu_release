/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_TYPE_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_UNION( VEC_OBJ_T(UTg2_CO_Primitive), )
{
    VEC_OBJ_T(TgPARTICLE)                       m_sPC;
    VEC_OBJ_T(TgLINE)                           m_sLN;
    VEC_OBJ_T(TgRAY)                            m_sRY;
    VEC_OBJ_T(TgSEGMENT)                        m_sSG;
    VEC_OBJ_T(TgCIRCLE)                         m_sCI;
    VEC_OBJ_T(TgELLIPSE)                        m_sEL;
    VEC_OBJ_T(TgPARALLELOGRAM)                  m_sPE;
    VEC_OBJ_T(TgPLANE)                          m_sPN;
    VEC_OBJ_T(TgRECTANGLE)                      m_sRT;
    VEC_OBJ_T(TgPTRI)                           m_sPT;
    VEC_OBJ_T(TgETRI)                           m_sET;
    VEC_OBJ_T(TgCTRI)                           m_sCT;
    VEC_OBJ_T(TgSTRI)                           m_sST;
    VEC_OBJ_T(TgBOXAA)                          m_sBA;
    VEC_OBJ_T(TgBOX)                            m_sBX;
    VEC_OBJ_T(TgMESH_SIMPLE)                    m_sMS;
    VEC_OBJ_T(TgMESH_BVT)                       m_sMB;
    VEC_OBJ_T(TgMESH_BA)                        m_sMA;
    VEC_OBJ_T(TgSPHERE)                         m_sSP;
    VEC_OBJ_T(TgTORUS)                          m_sTS;
    VEC_OBJ_T(TgTUBE)                           m_sTB;
};

TgTYPE_STRUCT( VEC_OBJ_T(STg2_CO_Clip_List), )
{
    TgRSIZE                                     m_nuiPoint; /**< Current number of points stored in the variable sized clip array. */
    TgRSIZE                                     m_nuiMax; /**< Maximum number of points in the variable sized clip array. */
    VEC_T(1)                                    m_avPoint[]; /**< Variable sized clip array. */
};

/* ---- Separating Axis ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT( VEC_OBJ_T(STg2_CO_Axis_Project), )
{
    VEC_T(1)                                    m_avMinVert[4], m_avMaxVert[4]; /**< Points coincident at min/max. */
    TgUINT_E32                                  m_uiMinID, m_uiMaxID; /**< Bitfield representing the triangle feature at min/max. */
    TgUINT_E32                                  m_nuiMinDepth, m_nuiMaxDepth; /**< Count of vertices coincident at min/max. */
};

TgTYPE_STRUCT( VEC_OBJ_T(STg2_CO_Axis_Test), )
{
    VEC_T(1)                                    m_vLimitT; /**< Maximal limit on the time value. */
    VEC_T(1)                                    m_vMin0, m_vMax0; /**< The extremities of the primitive projected onto the axis. */
    VEC_T(1)                                    m_vMin1, m_vMax1; /**< The extremities of the primitive projected onto the axis. */
    VEC_T(1)                                    m_vSpeed; /**< The relative speed of primitive 1 to primitive 0 along the axis. */
    VEC_T(1)                                    m_vMinT, m_vMaxT; /**< First and last time of contact. */
};

TgTYPE_STRUCT( VEC_OBJ_T(STg2_CO_Axis_Info), )
{
    VEC_T(1)                                    m_vNormal;
    VEC_T(1)                                    m_vMinT;
    ETgCO_AXIS_CONTACT_DIRECTION                m_enSide;
#if 0 != STRUCT_PAD(12,4)
    TgUINT_E08                                  m_iPad[STRUCT_PAD(12,4)];
#endif
};

TgTYPE_STRUCT( VEC_OBJ_T(STg2_CO_Axis_Result), )
{
    VEC_T(1)                                    m_vNormal;
    VEC_T(1)                                    m_vPoint;
    VEC_T(1)                                    m_vDepth;
    TgSINT_E32                                  m_iAxis;
#if 0 != STRUCT_PAD(12,4)
    TgUINT_E08                                  m_iPad[STRUCT_PAD(12,4)];
#endif
};

/* ---- Result ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT( VEC_OBJ_T(STg2_CO_Context), )
{
    TgSINT_E32                                  m_iTriIdx;
};

TgTYPE_STRUCT( VEC_OBJ_T(STg2_CO_Contact), )
{
    VEC_T(1)                                    m_vS0; /**< Contact position - position on the surface of the object. */
    VEC_T(1)                                    m_vN0; /**< Contact normal - minimal direction to remove penetration, or the normal of the contact surface at the position. */
    VEC_T(1)                                    m_vT0; /**< Normalized time of contact (first for a range). */
    VEC_T(1)                                    m_vDepth; /**< Penetration depth */
//#if 0 != STRUCT_PAD(8,0)
//    TgUINT_E08                                  m_iPad[STRUCT_PAD(8,0)];
//#endif
};

TgTYPE_STRUCT( VEC_OBJ_T(STg2_CO_Packet), )
{
    VEC_T(1)                                    m_vSweepTol;
    VEC_T(1)                                    m_vSnapTol;
    VEC_OBJ_T(STg2_CO_Contact,P)                m_psContact;
    TgRSIZE                                     m_nuiContact;
    TgRSIZE                                     m_nuiMaxContact;
    TgBOOL                                      m_bReport_Penetration;
#if 0 != STRUCT_PAD(7,7)
    TgUINT_E08                                  m_iPad[STRUCT_PAD(7,7)];
#endif
};

TgTYPE_STRUCT( VEC_OBJ_T(STg2_CO_Result), )
{
    VEC_OBJ_T(STg2_CO_Contact)                  m_sContact; /**< Result contact. */
    VEC_OBJ_T(TgPTRI)                           m_sPT; /**< Minimal target triangle representation. */
    VEC_OBJ_T(STg2_CO_Context)                  m_sContext; /**< Context of the result. */
    TgFLOAT32                                   m_fT1; /**< Normalized last time of contact. */
    TgBOOL                                      m_bValid; /**< Allows for easy post-processing of collision results. */
    TgBOOL                                      m_bTri; /**< Indicates if the contained triangle is valid. */
#if 0 != STRUCT_PAD(6,6)
    TgUINT_E08                                  m_iPad[STRUCT_PAD(6,6)];
#endif
};


/* ---- Request ------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

TgTYPE_STRUCT( VEC_OBJ_T(STg2_CO_Request), )
{
    VEC_OBJ_T(STg2_CO_Context) TgALIGN(TgCCL)   m_sContext; /**< Context of the current collision state. */

    ETgPM_SHORT                                 m_enPM; /**< Active primitive for the structure. */
    ETgCO_TEST                                  m_enTest; /**< Test is intersection, penetration and/or sweep. */
    ETgCO_PURPOSE                               m_enPurpose; /**< Bitfield describing the purpose of the collision call. */

    VEC_OBJ_T(TgDELTA)                          m_sDT;

    VEC_OBJ_T(STg2_CO_Result)                   m_asInternal_Result[KTgCO_REQUEST__INTERNAL_RESULTS];

                                                /* Used on a per query basis to be merged into results (temporary data). */
    VEC_OBJ_T(STg2_CO_Packet)                   m_sPacket;
    VEC_OBJ_T(STg2_CO_Contact)                  m_asContact[8];

    VEC_OBJ_T(STg2_CO_Result,P)                 m_psResult;
    TgRSIZE                                     m_nuiResult_End; /* Terminates the memory region. */
    TgRSIZE                                     m_nuiResult_Last; /* Terminates the array of valid results. */

    TgSINT_E32                                  m_aiNative_String[KTgCO_REQUEST__MAX_IGNORE];
    TgRSIZE                                     m_nuiNative_String; /**< Ignore a specific literal (eg class name). */

    TgRSIZE                                     m_nuiConnection_Graph_Ignored; /**< Inclusively ignore all descendants. */
    TgRSIZE                                     m_nuiConnection_Ignored; /**< Ignore only the object. */
    STg2_Connection_P                           m_apsConnection_Graph_Ignored[KTgCO_REQUEST__MAX_IGNORE];
    STg2_Connection_P                           m_apsConnection_Ignored[KTgCO_REQUEST__MAX_IGNORE];

                                                /* Collect List */
    VEC_OBJ_T(TgPTRI,P)                         m_psCollect;
    TgRSIZE                                     m_nuiCollect_End;
    TgRSIZE                                     m_nuiCollect_Last;

    VAR_T()                                     m_fToI; /**< The closest point of intersection during the sweep test [0..1]. */
    VAR_T()                                     m_fDist;
    VAR_T()                                     m_fNudge;

                                                /* Result list filtered by selectors (greatest depth etc.) */
    TgUINT_E32                                  m_uiFilter_Objects; /**< Category of objects included in collision call. */
    TgUINT_E32                                  m_bfFlags; /**< General bitfield for collision flags. */

#if 0 != STRUCT_PAD(4,0)
    TgUINT_E08                                  m_iPad0[STRUCT_PAD(4,0)];
#endif

    VEC_OBJ_T(UTg2_CO_Primitive)                m_uPM;

#if 0 != STRUCT_PAD(48,56)
    TgUINT_E08                                  m_iPad1[STRUCT_PAD(48,56)];
#endif
};


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TGS_COLLISION_TYPE_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_TYPE_H) */
#endif
