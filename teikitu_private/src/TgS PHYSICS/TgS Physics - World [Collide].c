
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - World [Collide].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COLLISION/TgS Collision.inl"
#include "TgS Physics - Internal.inl"


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static STg2_PH_Body_PP                      s_psBY_Reactivated;
static TgRSIZE                              s_nuiBY_Reactivated, s_nuiBY_Reactivated_MAX;
static TgUINT_E64_P                         s_puiFM_Reactivated;
static TgRSIZE                              s_nuiFM_Reactivated, s_nuiFM_Reactivated_MAX;

static TgVOID
tgPH_Update_World__Collide__Callback(
    TgUINT_MAX_C ARG0, TgUINT_MAX_C ARG1 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Update_World__Collide__Simple_IMM ----------------------------------------------------------------------------------------------------------------------------------- */
/* SYNC: READS Forms | Bodies, Constraints (in Child Functions).                                                                                                                   */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Collide__Simple_IMM( TgPH_WORLD_ID_C tiWorld, TgRSIZE_C uiBegin, TgRSIZE_C uiEnd )
{
    STg2_PH_Update__Simulation_CPC      psUpdate_Simulation = g_asPH_Update__Simulation + tiWorld.m_uiI;
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if (nullptr == psWorld) TgATTRIBUTE_UNLIKELY
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale World ID submitted for update." );
        return;
    }
    else
    {
        TgRSIZE_C                           nuiForm_World = TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Form_Total__Used + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) );
        TgRSIZE                             uiIndex0, uiIndex1;

        #pragma region Iterate through this batch and find all colliding objects for it.
        for (uiIndex0 = uiBegin; uiIndex0 < uiEnd; ++uiIndex0)
        {
            STg2_PH_Form_PC                     psFM0 = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex0];
            TgBOXAA_F32_04_P                    psBA0, psBA1;

            for (uiIndex1 = uiIndex0 + 1; uiIndex1 < nuiForm_World; ++uiIndex1)
            {
                STg2_PH_Form_PC                     psFM1 = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex1];

                if (uiIndex1 >= uiBegin && uiIndex1 <= uiIndex0)
                {
                    continue;
                };

                if (0 == ((psFM0->m_uiCategory & psFM1->m_uiCollide) & KTgPA_CATEGORY_BIT_MASK__AND_TEST))
                {
                    continue;
                };

                if (0 == ((psFM1->m_uiCategory & psFM0->m_uiCollide) & KTgPA_CATEGORY_BIT_MASK__AND_TEST))
                {
                    continue;
                };

                if (0 == (((psFM0->m_uiCategory & psFM1->m_uiCollide) | (psFM1->m_uiCategory & psFM0->m_uiCollide)) & KTgPA_CATEGORY_BIT_MASK__OR_TEST))
                {
                    continue;
                };

                TgDIAG( ((0 != psFM0->m_tiBY.m_uiKI) && (psFM0->m_uiCategory & (1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING))) || ((0 != psFM1->m_tiBY.m_uiKI) && (psFM1->m_uiCategory & (1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING))));

                psBA0 = (psFM0->m_uiCategory & (1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING)) ? psUpdate_Simulation->m_asFM_BA_W + psFM0->m_uiUsed_Index : &psFM0->m_sBA_W;
                psBA1 = (psFM1->m_uiCategory & (1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING)) ? psUpdate_Simulation->m_asFM_BA_W + psFM1->m_uiUsed_Index : &psFM1->m_sBA_W;
                if (!tgCO_BA_Test_BA_F32_04( psBA0, psBA1 ))
                {
                    continue;
                };

                tgPH_Update_World__Collide__Callback( psFM0->m_tiForm.m_uiKI, psFM1->m_tiForm.m_uiKI );
            };
        };
        #pragma endregion
    };
}


/* ---- tgPH_Update_World__Collide__Partition_Manager_IMM ------------------------------------------------------------------------------------------------------------------------ */
/* SYNC: READS Forms, Bodies | Constraints (in Child Functions). WRITES to Form's PnS ID (only).                                                                                   */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Collide__Partition_Manager_IMM( TgPH_WORLD_ID_C tiWorld )
{
    TgRSIZE_C                           nuiForm_World = TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Form_Total__Used + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) );
    TgRSIZE_C                           nuiBody_World = TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Body_Total__Used + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) );
    STg2_PH_Update__Simulation_CPC      psUpdate_Simulation = g_asPH_Update__Simulation + tiWorld.m_uiI;
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );
    TgRSIZE_C                           uiCacheStride = KTgPH_CACHE_BIT__TOTAL_RESERVED;
    TgRSIZE_C                           nuiCacheItem = 64 / uiCacheStride;
    TgRSIZE                             uiIndex;

    if (nullptr == psWorld) TgATTRIBUTE_UNLIKELY
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale World ID submitted for update." );
        return;
    };

    /* Iterate through all of the current forms to determine if changes with the prune and sweep system is necessary. Enabled forms have to be inserted into the scene graph
       and if disabled they must be removed from the system. This is an optimization requirement since the smaller the list that needs to be traversed and compared will
       drastically decrease computation time. */

    #pragma region Iterate through this batch and find all colliding objects for it.
    PROFILE_ARRAY_START( tiWorld.m_uiI, PH_COLLISION_CONTACT_PAIR_GENEARTION, tgPH_Update_World__Collide__Partition_Manager_IMM );
    PROFILE_START( PH_COLLISION_CONTACT_PAIR_GENEARTION_TOTAL, tgPH_Update_World__Collide__Partition_Manager_IMM );

    for (uiIndex = 0; uiIndex < nuiForm_World; ++uiIndex)
    {
        TgUINT_E64_PC                       puiFM_Category_Cache = g_aauiPH_Form_Used_Category[tiWorld.m_uiI] + uiIndex/nuiCacheItem;
        TgUINT_E64_C                        uiFM_Cache_Value = (*puiFM_Category_Cache) >> (uiCacheStride*(uiIndex % nuiCacheItem));

        if (uiFM_Cache_Value & (1ULL << KTgPH_CACHE_BIT__ENABLE_COLLSION))
        {
            if (0 == (uiFM_Cache_Value & (1ULL << KTgPH_CACHE_BIT__VALID_PA_ID)))
            {
                STg2_PH_Form_PC                     psFM = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex];

                psFM->m_uiCategory |= KTgID__INVALID_VALUE != psFM->m_tiBY.m_uiKI ? 1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING_GRAPH : 0;
                tgPA_Graph_Insert_Object( &psFM->m_tiPnS, psWorld->m_tiPA_Graph, psFM->m_tiForm.m_uiKI, psFM->m_uiCategory, psFM->m_uiCollide, &psFM->m_sBA_W );
                tgPH_Form_Update_Category_Cache( psFM );
            }
            else if (uiFM_Cache_Value & (1ULL << KTgPH_CACHE_BIT__FORM_IS_UPDATING_GRAPH) || (uiFM_Cache_Value & (1ULL << KTgPH_CACHE_BIT__FORM_IS_UPDATING)))
            {
                if (uiFM_Cache_Value & (1ULL << KTgPH_CACHE_BIT__FORM_IS_UPDATING))
                {
                    STg2_PH_Form_PC                     psFM = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex];

                    psFM->m_uiCategory |= 1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING_GRAPH;
                    *puiFM_Category_Cache |= 1ULL << (uiCacheStride*(uiIndex % nuiCacheItem) + KTgPH_CACHE_BIT__FORM_IS_UPDATING_GRAPH);
                    tgPA_Graph_Object_Update( psWorld->m_tiPA_Graph, psFM->m_tiPnS, psUpdate_Simulation->m_asFM_BA_W + psFM->m_uiUsed_Index, psFM->m_uiCategory, psFM->m_uiCollide );
                }
                else
                {
                    STg2_PH_Form_PC                     psFM = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex];

                    psFM->m_uiCategory &= ~(1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING_GRAPH);
                    *puiFM_Category_Cache &= ~(1ULL << (uiCacheStride*(uiIndex % nuiCacheItem) + KTgPH_CACHE_BIT__FORM_IS_UPDATING_GRAPH));
                    tgPA_Graph_Object_Update( psWorld->m_tiPA_Graph, psFM->m_tiPnS, &psFM->m_sBA_W, psFM->m_uiCategory, psFM->m_uiCollide );
                };
            };
        }
        else if (uiFM_Cache_Value & (1ULL << KTgPH_CACHE_BIT__VALID_PA_ID))
        {
            STg2_PH_Form_PC                     psFM = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex];

            tgPA_Graph_Remove_Object( psWorld->m_tiPA_Graph, psFM->m_tiPnS );
            psFM->m_tiPnS.m_uiKI = KTgID__INVALID_VALUE;
            psFM->m_uiCategory &= ~(1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING_GRAPH);
            tgPH_Form_Update_Category_Cache( psFM );
        };
    };

    s_psBY_Reactivated = (STg2_PH_Body_PP)TgMALLOC_POOL( sizeof(STg2_PH_Body_P) * nuiBody_World );
    s_nuiBY_Reactivated = 0;
    s_nuiBY_Reactivated_MAX = nuiBody_World;

    TgVERIFY(TgSUCCEEDED(tgPA_Graph_Execute_Function( psWorld->m_tiPA_Graph, tgPH_Update_World__Collide__Callback )));

    if (s_nuiBY_Reactivated > 0)
    {
        s_puiFM_Reactivated = (TgUINT_E64_P)TgMALLOC_POOL( sizeof(TgUINT_E64) * nuiForm_World );
        s_nuiFM_Reactivated = 0;
        s_nuiFM_Reactivated_MAX = nuiForm_World;

        do 
        {
            for (uiIndex = 0; uiIndex < s_nuiBY_Reactivated; ++uiIndex)
            {
                STg2_PH_Form_P                      psFM;

                tgPH_Body_Set_Update_IMM( s_psBY_Reactivated[uiIndex], true );
                tgPH_Update_World__Simulate_Batch_IMM( tiWorld, s_psBY_Reactivated[uiIndex]->m_uiUsed_Index, s_psBY_Reactivated[uiIndex]->m_uiUsed_Index + 1 );

                if (KTgID__INVALID_VALUE == s_psBY_Reactivated[uiIndex]->m_tiFM_Head.m_uiKI)
                {
                    continue;
                };

                psFM = tgPH_Form_Get_Form_From_ID( s_psBY_Reactivated[uiIndex]->m_tiFM_Head );

                for (;nullptr != psFM && s_nuiFM_Reactivated < s_nuiFM_Reactivated_MAX; psFM = tgPH_Form_Get_Form_From_ID( psFM->m_tiNext ))
                {
                    if (psFM->m_uiCategory & (1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING_GRAPH) || (psFM->m_uiCategory & (1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING)))
                    {
                        TgUINT_E64_PC                       puiFM_Category_Cache = g_aauiPH_Form_Used_Category[tiWorld.m_uiI] + psFM->m_uiUsed_Index/nuiCacheItem;

                        if (psFM->m_uiCategory & (1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING))
                        {
                            psFM->m_uiCategory |= 1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING_GRAPH;
                            *puiFM_Category_Cache |= 1ULL << (uiCacheStride*(psFM->m_uiUsed_Index % nuiCacheItem) + KTgPH_CACHE_BIT__FORM_IS_UPDATING_GRAPH);
                            tgPA_Graph_Object_Update( psWorld->m_tiPA_Graph, psFM->m_tiPnS, psUpdate_Simulation->m_asFM_BA_W + psFM->m_uiUsed_Index, psFM->m_uiCategory, psFM->m_uiCollide );
                        }
                        else
                        {
                            psFM->m_uiCategory &= ~(1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING_GRAPH);
                            *puiFM_Category_Cache &= ~(1ULL << (uiCacheStride*(psFM->m_uiUsed_Index % nuiCacheItem) + KTgPH_CACHE_BIT__FORM_IS_UPDATING_GRAPH));
                            tgPA_Graph_Object_Update( psWorld->m_tiPA_Graph, psFM->m_tiPnS, &psFM->m_sBA_W, psFM->m_uiCategory, psFM->m_uiCollide );
                        };
                    };
                    s_puiFM_Reactivated[s_nuiFM_Reactivated] = psFM->m_tiPnS.m_uiKI;
                    ++s_nuiFM_Reactivated;
                };
            };

            s_nuiBY_Reactivated = 0;
            TgVERIFY(TgSUCCEEDED(tgPA_Graph_Object_List_Execute_Function( psWorld->m_tiPA_Graph, tgPH_Update_World__Collide__Callback, s_puiFM_Reactivated, s_nuiFM_Reactivated )));
        }
        while (s_nuiBY_Reactivated > 0);

        TgFREE_POOL(s_puiFM_Reactivated);
        s_puiFM_Reactivated = nullptr;
        s_nuiFM_Reactivated = 0;
        s_nuiFM_Reactivated_MAX = 0;
    };

    TgFREE_POOL(s_psBY_Reactivated);
    s_psBY_Reactivated = nullptr;
    s_nuiBY_Reactivated = 0;
    s_nuiBY_Reactivated_MAX = 0;

    PROFILE_STOP( PH_COLLISION_CONTACT_PAIR_GENEARTION_TOTAL, tgPH_Update_World__Collide__Partition_Manager_IMM );
    PROFILE_ARRAY_STOP( tiWorld.m_uiI, PH_COLLISION_CONTACT_PAIR_GENEARTION, tgPH_Update_World__Collide__Partition_Manager_IMM );
    #pragma endregion
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Update_World__Collide__Callback ------------------------------------------------------------------------------------------------------------------------------------- */
/* SYNC: READS Forms, Bodies, Constraints. WRITES to Contact Constraints created in Immediate mode (linked list modification is deferred).                                         */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPH_Update_World__Collide__Callback( TgUINT_MAX_C uiKI_FY0, TgUINT_MAX_C uiKI_FY1 )
{
    TgPH_FORM_ID_C                      tiFM0 = { .m_uiKI = uiKI_FY0 };
    STg2_PH_Form_CPC                    psFM0 = tgPH_Form_Get_Form_From_ID( tiFM0 );
    TgPH_FORM_ID_C                      tiFM1 = { .m_uiKI = uiKI_FY1 };
    STg2_PH_Form_CPC                    psFM1 = tgPH_Form_Get_Form_From_ID( tiFM1 );
    STg2_PH_Body_P                      psBY0, psBY1;

#if defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS
    TgSTD_ATOMIC(fetch_add_explicit)( &g_xnuiFM_Callback, 1, TgSTD_MEMORY_ORDER(relaxed) );
/*# defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS */
#endif

    #pragma region Input Parameter validation checks. There is no reason this function should ever get bad data.
    /* Validates that valid Forms, and the Form and Body are in the same World. */
    TgDIAG((nullptr != psFM0) && (nullptr != psFM1));
    TgDIAG(psFM0->m_tiForm.m_uiWorld == psFM1->m_tiForm.m_uiWorld);

    /* Tests to see if the forms have an existing constraint between their bodies. */
    if (tgPH_Constraint_Query_Connected( psFM0->m_tiBY, psFM1->m_tiBY )) TgATTRIBUTE_UNLIKELY
    {
        return;
    };

    /* Validates that the forms do not share a body. */
    if (psFM0->m_tiBY.m_uiKI == psFM1->m_tiBY.m_uiKI) TgATTRIBUTE_UNLIKELY
    {
        return;
    };

    psBY0 = KTgID__INVALID_VALUE != psFM0->m_tiBY.m_uiKI ? tgPH_Body_Get_Body_From_ID( psFM0->m_tiBY ) : nullptr;
    psBY1 = KTgID__INVALID_VALUE != psFM1->m_tiBY.m_uiKI ? tgPH_Body_Get_Body_From_ID( psFM1->m_tiBY ) : nullptr;

    /* Validate that we have at least one valid body. Reminder that forms without bodies are considered to be kinematic. */
    TgDIAG((nullptr != psBY0) || (nullptr != psBY1));
    TgDIAG( ((nullptr != psBY0) && (psBY0->m_bUpdate)) || ((nullptr != psBY1) && (psBY1->m_bUpdate)));
    TgDIAG(nullptr == psBY0 || psBY0->m_uiUsed_Index < TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Body_Total__Used + psBY0->m_tiBody.m_uiWorld, TgSTD_MEMORY_ORDER(relaxed) ));
    TgDIAG(nullptr == psBY1 || psBY1->m_uiUsed_Index < TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Body_Total__Used + psBY1->m_tiBody.m_uiWorld, TgSTD_MEMORY_ORDER(relaxed) ));
    #pragma endregion

    #pragma region Collision Test and Contact Generation.
    PROFILE_ARRAY_START( psFM0->m_tiForm.m_uiWorld, PH_COLLISION_CONTACT_CALLBACK, tgPH_Update_World__Collide__Callback );
    PROFILE_START( PH_COLLISION_CONTACT_CALLBACK_TOTAL, tgPH_Update_World__Collide__Callback );
    do
    {
        STg2_PH_Update__Simulation_CPC      psUpdate_Simulation = g_asPH_Update__Simulation + psFM0->m_tiForm.m_uiWorld;

        TgBOOL_C                            bFM0_Update = psFM0->m_uiCategory & (1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING);
        TgVEC_F32_04_1                      vFM0_Pos_O2W = bFM0_Update ? psUpdate_Simulation->m_avFM_Pos_O2W[psFM0->m_uiUsed_Index] : psFM0->m_vPos_O2W;
        TgVEC_F32_04_3_CP                   pmFM0_Final_O2W = bFM0_Update ? psUpdate_Simulation->m_amFM_Final_O2W + psFM0->m_uiUsed_Index : &psFM0->m_mFinal_O2W;
        TgVEC_F32_04_1                      vΔFM0_Pos_02W = tgMH_SUB_F32_04_1( vFM0_Pos_O2W, psFM0->m_vPos_O2W );

        TgBOOL_C                            bFM1_Update = psFM1->m_uiCategory & (1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING);
        TgVEC_F32_04_1                      vFM1_Pos_O2W = bFM1_Update ? psUpdate_Simulation->m_avFM_Pos_O2W[psFM1->m_uiUsed_Index] : psFM1->m_vPos_O2W;
        TgVEC_F32_04_3_CP                   pmFM1_Final_O2W = bFM1_Update ? psUpdate_Simulation->m_amFM_Final_O2W + psFM1->m_uiUsed_Index : &psFM1->m_mFinal_O2W;
        TgVEC_F32_04_1                      vΔFM1_Pos_02W = tgMH_SUB_F32_04_1( vFM1_Pos_O2W, psFM1->m_vPos_O2W );

        STg2_CO_Packet_F32_04               sCO_Packet;
        STg2_CO_Contact_F32_04              sCO_Contact[4];
        TgDELTA_F32_04                      sΔFM1_Rel_FM0;

        TgVEC_F32_04_1                      vTime, vRestitution_Factor;

        UTg2_CO_Primitive_F32_04            uPM0,uPM1;
        TgRESULT                            iResult;
        TgRSIZE                             uiIndex;

    #if defined(TgBUILD_FEATURE__PHYSICS__COLLISION_SWEEP)
        TgVEC_F32_04_1                      vFM1_ΔSP_LEN, vFM1_LEN_CMP;
        TgVEC_F32_04_3                      mFM0, mFM1;
    /*# defined(TgBUILD_FEATURE__PHYSICS__COLLISION_SWEEP) */
    #endif

        #pragma region Initialize the Contact Packet used to gather the Contact Points.

        sCO_Packet.m_vSweepTol = tgMH_SET1_F32_04_1( 10.0F * KTgEPS_F32 );
        sCO_Packet.m_vSnapTol = tgMH_SET1_F32_04_1( 10.0F * KTgEPS_F32 );
        sCO_Packet.m_psContact = sCO_Contact;
        sCO_Packet.m_nuiContact = 0;
        sCO_Packet.m_nuiMaxContact = TgARRAY_COUNT(sCO_Contact);
        sCO_Packet.m_bReport_Penetration = true;

        #pragma endregion

        /* Calculate the movement of Form 1 in Form 0 Reference Frame. */
        tgGM_DT_Set_F32_04( &sΔFM1_Rel_FM0, tgMH_SUB_F32_04_1( vΔFM1_Pos_02W, vΔFM0_Pos_02W ) );
        vTime = tgMH_SET1_F32_04_1( 1.0F );

    #if defined(TgBUILD_FEATURE__PHYSICS__COLLISION_SWEEP)

        #pragma region Based on the Translation of the Forms, determine if a Sweep Test should be used.

        /* Determine if the Form's translation (velocity) is greater than 50% of its size along the vector of translation (centre of gravity should not penetrate other Forms). */
        vFM1_LEN_CMP = tgMH_CMP_GT_F32_04_1( sΔFM1_Rel_FM0.m_vMag_DT, tgMH_SET1_F32_04_1( KTgEPS_F32 ) );
        if (tgMH_CMP_ANY_TO_BOOL_F32_04_1( vFM1_LEN_CMP ) && (nullptr != psFM1->m_pfnPM_Support_Point))
        {
            UTg2_CO_Primitive_F32_04            uPM;
            TgVEC_F32_04_1                      vFM1_Support_Point, vFM1_ΔSP, vFM1_LEN_TST;

            psFM1->m_pfnPM_Copy_TX( &uPM, &psFM1->m_uPM, pmFM1_Final_O2W );
            vFM1_Support_Point = psFM1->m_pfnPM_Support_Point( &uPM, sΔFM1_Rel_FM0.m_vUDT );
            vFM1_ΔSP = tgMH_SUB_F32_04_1( vFM1_Support_Point, vFM1_Pos_O2W );
            vFM1_LEN_TST = tgMH_MUL_F32_04_1( tgMH_SET1_F32_04_1( 2.0F ), sΔFM1_Rel_FM0.m_vMag_DT );

            vFM1_ΔSP_LEN = tgMH_LEN_F32_04_1( vFM1_ΔSP );
            vFM1_LEN_CMP = tgMH_CMP_LT_F32_04_1( vFM1_ΔSP_LEN, vFM1_LEN_TST );
        }
        else
        {
            vFM1_ΔSP_LEN = tgMH_SET1_F32_04_1( 0.0F );
            vFM1_LEN_CMP = tgMH_SET1_F32_04_1( 0.0F );
        };

        #pragma endregion

        #pragma region Collision Sweep Test (if required).
        if (tgMH_CMP_ANY_TO_BOOL_F32_04_1( vFM1_LEN_CMP ))
        {
            /* NOTE: This sweep test differs from testing along the continuum of motion for both Forms. The difference is that the Forms are swept through their linear motion path
                     but not their rotational changes. The rotation change is done immediately (which can lead to a pre-penetration), and then we sweep the Forms through the linear
                     path. This action can create "false" results. Some attempt is made to filter these out. However, it follows the tenets of the Physics Module that we are biased
                     toward performance, believability, consistency, and reproducibility. Correctness is not a hard requirement, and we are willing to accept the occasional
                     "incorrect" contact as it would be believable. */

            TgVEC_F32_04_3                      mFM0_Prev_Final_O2W, mFM1_Prev_Final_O2W;

            #pragma region Collision Sweep Test Setup (starting for previous position sweeping to predicted position).
            tgMH_Set_Rot_F32_04_3( &mFM0_Prev_Final_O2W, pmFM0_Final_O2W ); 
            tgMH_Set_T_F32_04_3( &mFM0_Prev_Final_O2W, psFM0->m_vPos_O2W );
            psFM0->m_pfnPM_Copy_TX( &uPM0, &psFM0->m_uPM, &mFM0_Prev_Final_O2W );

            tgMH_Set_Rot_F32_04_3( &mFM1_Prev_Final_O2W, pmFM1_Final_O2W );
            tgMH_Set_T_F32_04_3( &mFM1_Prev_Final_O2W, psFM1->m_vPos_O2W );
            #pragma endregion

            /* If required, use the Sweep test. If one does not exist for this primitive pair, use a fully self contained sphere to do the sweep and then do a penetration test
               based on the time of contact. */
            if (tgCO_PM_Sweep_PM_Supported_F32_04( psFM0->m_enPM, psFM1->m_enPM ))
            {
                psFM1->m_pfnPM_Copy_TX( &uPM1, &psFM1->m_uPM, &mFM1_Prev_Final_O2W );

                #pragma region Collision Sweep Test.
                iResult = tgCO_PM_Sweep_PM_F32_04( &sCO_Packet, &vTime, psFM0->m_enPM, &uPM0, psFM1->m_enPM, &uPM1, &sΔFM1_Rel_FM0 );
                if (TgFAILED(iResult) && (KTgE_PREPENETRATION != iResult))
                {
                    break;
                };
                #pragma endregion
            }
            else if (tgCO_PM_Sweep_PM_Supported_F32_04( psFM0->m_enPM, ETgPM_SP ))
            {
                #pragma region Collision Sweep Sphere Test - Reposition Primitive for Penetration Test.
                UTg2_CO_Primitive_F32_04            uPM2;

                tgGM_SP_Init_F32_04(&uPM2.m_sSP, psFM1->m_vPos_O2W, vFM1_ΔSP_LEN);
                iResult = tgCO_PM_Sweep_PM_F32_04( &sCO_Packet, &vTime, psFM0->m_enPM, &uPM0, ETgPM_SP, &uPM2, &sΔFM1_Rel_FM0 );
                if (TgSUCCEEDED(iResult) || (KTgE_PREPENETRATION == iResult))
                {
                    /* Interpolate the position and rotation of the two Forms for the Penetration Test. */
                    vFM0_Pos_O2W = tgMH_MAD_F32_04_1( vΔFM0_Pos_02W, vTime, psFM0->m_vPos_O2W );
                    tgMH_Set_Rot_F32_04_3( &mFM0, pmFM0_Final_O2W );
                    tgMH_Set_T_F32_04_3( &mFM0, vFM0_Pos_O2W );
                    pmFM0_Final_O2W = &mFM0;
                    vFM1_Pos_O2W = tgMH_MAD_F32_04_1( vΔFM1_Pos_02W, vTime, psFM1->m_vPos_O2W );
                    tgMH_Set_Rot_F32_04_3( &mFM1, pmFM1_Final_O2W );
                    tgMH_Set_T_F32_04_3( &mFM1, vFM1_Pos_O2W );
                    pmFM1_Final_O2W = &mFM1;
                    sCO_Packet.m_nuiContact = 0;
                };

                /* FALL THROUGH to the Penetration test is intentional. */
                #pragma endregion
            };
        };
        #pragma endregion
    /*# defined(TgBUILD_FEATURE__PHYSICS__COLLISION_SWEEP) */
    #endif

        #pragma region Collision Penetration Test for Repositioned Forms and Sweep Test not Required.
        if (0 == sCO_Packet.m_nuiContact)
        {
            #pragma region Collision Penetration Test (penetration test at the predicted position).
            TgDIAG(nullptr != psFM0->m_pfnPM_Copy_TX);
            psFM0->m_pfnPM_Copy_TX( &uPM0, &psFM0->m_uPM, pmFM0_Final_O2W );
            TgDIAG(nullptr != psFM1->m_pfnPM_Copy_TX);
            psFM1->m_pfnPM_Copy_TX( &uPM1, &psFM1->m_uPM, pmFM1_Final_O2W );

            iResult = tgCO_PM_Penetrate_PM_F32_04( &sCO_Packet, psFM0->m_enPM, &uPM0, psFM1->m_enPM, &uPM1 );
            if (TgFAILED(iResult))
            {
                break;
            };
            #pragma endregion
        };
        #pragma endregion

        #pragma region Add the Contact Constraints to the World Update for the Solver.
        vRestitution_Factor = tgMH_SET1_F32_04_1(-0.9F); // tgPH_Material_Calc_Restitution_Factor( psFM0, vΔFM0_Pos_02W, psFM1, vΔFM1_Pos_02W );
        for (uiIndex = 0; uiIndex < sCO_Packet.m_nuiContact; ++uiIndex)
        {
            TgVEC_F32_04_1                      vX0 = tgMH_SUB_F32_04_1( vTime, KTgONE_F32_04_1 );
            TgVEC_F32_04_1                      vX1 = tgMH_MUL_F32_04_1( vX0, sΔFM1_Rel_FM0.m_vDT );
            TgVEC_F32_04_1                      vX2 = tgMH_DOT_F32_04_1( vX1, sCO_Contact[uiIndex].m_vN0 );

            sCO_Contact[uiIndex].m_vDepth = tgMH_ADD_F32_04_1( vX2, sCO_Contact[uiIndex].m_vDepth );
            tgPH_Constraint_Contact__Init_IMM( psFM0, psFM1, vRestitution_Factor, sCO_Contact + uiIndex );
        };
        #pragma endregion

        #pragma region If a contact was created, add any inactive bodies to a reactivation list.
        if (sCO_Packet.m_nuiContact > 0)
        {
            if ((nullptr != psBY0) && (!psBY0->m_bUpdate) && (s_nuiBY_Reactivated < s_nuiBY_Reactivated_MAX))
            {
                s_psBY_Reactivated[s_nuiBY_Reactivated] = psBY0;
                ++s_nuiBY_Reactivated;
            }
            if ((nullptr != psBY1) && (!psBY1->m_bUpdate) && (s_nuiBY_Reactivated < s_nuiBY_Reactivated_MAX))
            {
                s_psBY_Reactivated[s_nuiBY_Reactivated] = psBY1;
                ++s_nuiBY_Reactivated;
            }
        };
        #pragma endregion
    } while (0);

    PROFILE_STOP( PH_COLLISION_CONTACT_CALLBACK_TOTAL, tgPH_Update_World__Collide__Callback );
    PROFILE_ARRAY_STOP( psFM0->m_tiForm.m_uiWorld, PH_COLLISION_CONTACT_CALLBACK, tgPH_Update_World__Collide__Callback );
    #pragma endregion
}
