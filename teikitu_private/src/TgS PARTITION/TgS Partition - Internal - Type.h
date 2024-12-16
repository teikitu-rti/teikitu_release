/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Partition - Internal - Type.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PARTITION_INTERNAL_TYPE_H)
#define TGS_PARTITION_INTERNAL_TYPE_H
#pragma once


/* == Partition ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Private Types                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_PA_Graph,)
{
    TgPARTITION_GRAPH_ID_SINGLETON TgALIGN(16)  m_tiGraph_Singleton;
    TgRSIZE                                     m_uiSize;
    ETgPA_GRAPH_TYPE                            m_enPA_Graph;
    TgUINT_E08                                  m_uiPad[12];
};

TgTYPE_STRUCT(STg2_PA_Graph__PNS__Point_End,)
{
    TgFLOAT32                                   m_fVal; /**< The axis projected min/max value */
    TgUINT_E16                                  m_uiNext; /**< Index of the AABB/Object */
    TgUINT_E16                                  m_uiPrev; /**< Index of the AABB/Object */
    TgBOOL                                      m_bMax;
    TgUINT_E08                                  m_iPad[3];
};

TgTYPE_STRUCT(STg2_PA_Graph__PNS__Contact_Pair,)
{
    TgRSIZE                                     m_uiContact_Next; /**< Index to next element in side-chain */
    TgUINT_MAX                                  m_uiCallbackID_0; /**< Callback ID of the 1st object. */
    TgUINT_MAX                                  m_uiCallbackID_1; /**< Callback ID of the 2nd object. */
    TgUINT_E64                                  m_bPaired_Contact : 1; /**< This is the second of two contacts created between the two objects. */
    TgUINT_E64                                  m_uiObject_Index: 63;
};

TgTYPE_STRUCT(STg2_PA_Graph__Prune_And_Sweep,)
{
    STg2_PA_Graph                               m_sBase_Struct;

    /* Prune and Sweep data for recording object occupancy per axis. */

    STg2_PA_Graph__PNS__Point_End               m_asX0[KTgPA_PNS_MAX_INTERVAL + 1];
    STg2_PA_Graph__PNS__Point_End               m_asX1[KTgPA_PNS_MAX_INTERVAL + 1];
    STg2_PA_Graph__PNS__Point_End               m_asX2[KTgPA_PNS_MAX_INTERVAL + 1];
    TgUINT_E08                                  m_uiPad1[12];

    /* Array of Objects managed by the Graph. */

    struct {
        TgUINT_MAX                                  m_uiCallbackID; /**< ID used to pass into collision callback */
        TgUINT_E64                                  m_uiCategory; /**< Object category mask */
        TgUINT_E64                                  m_uiCollide; /**< Object collide mask */
        TgRSIZE                                     m_uiContact_Linked_List_Head; /**< Index to first contact pair for this object */
        TgBOXAA_F32_04                              m_sBA; /**< Object AABB */
        TgPARTITION_OBJECT_ID_SINGLETON             m_tiObject_Singleton; /**< Object ID in this PnS partition */
        TgUINT_E64                                  m_uiPad;
    }                                           m_asObject[KTgPA_PNS_MAX_OBJECTS];

                                                /* Pool of nodes for a linked list per object */
    STg2_PA_Graph__PNS__Contact_Pair            m_asContact_Pair[KTgPA_PNS_MAX_CONTACT_PAIR];

    TgRSIZE                                     m_nuiObjects;
    TgRSIZE                                     m_uiEmpty; /**< First empty contact element */

    STg1_MT_MX                                  m_sSystem_Lock;
#if 0 != (SIZE_STg1_MT_MX % 16)
    TgUINT_E08                                  m_uiPad2[16 - SIZE_STg1_MT_MX % 16];
#endif
};


/* =============================================================================================================================================================================== */
#endif
