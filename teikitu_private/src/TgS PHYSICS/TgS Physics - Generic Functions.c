/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Generic Functions.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS COMMON/TgS Common.inl"
#include "TgS Physics - Internal.inl"

    #define __PARENT_FILE__ "TgS Physics - Generic Functions.c"
    #define ENABLE_RELOAD_GUARD
    #include "TgS PHYSICS/TgS Physics - Object [INC].h"
    #undef ENABLE_RELOAD_GUARD
    #undef __PARENT_FILE__

#else
/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */






/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- T_NAME(tgPH_,_Init) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if !defined(T_STATIC)
#if defined(T_GLOBAL)
T_ID(TgPH_,_ID) T_NAME(tgPH_,_Init)( TgVOID )
#else
T_ID(TgPH_,_ID) T_NAME(tgPH_,_Init)( TgPH_WORLD_ID_C tiWorld )
#endif
{
    union
    {
        T_NAME(STg2_PH_,_P)                 T_NAME(ps,);
        STg2_UT_ST__ST_Node_P               psNode;
        
    }                                   T_NAME(u,);

    struct
    {
        T_ID(TgPH_,_ID)                     tiID;
    }                                   sCommand;

    TgUINT_E32                          uiIndex;

    /* Pop the next free object off the stack */
    T_NAME(u,).psNode = tgCM_UT_LF__ST__Pop( &T_NAME_VAR(sPH_,_Free_Stack).m_sStack );
    if (nullptr == T_NAME(u,).psNode)
    {
    #if defined(T_GLOBAL)
        T_NAME(u,).T_NAME(ps,) = T_NAME(tgPH_,_Grow_Commit_List)();
    #else
        T_NAME(u,).T_NAME(ps,) = T_NAME(tgPH_,_Grow_Commit_List)( tiWorld );
    #endif
        if (nullptr == T_NAME(u,).psNode)
        {
            return (T_ID(KTgPH_,_ID__INVALID));
        };
    };

    uiIndex = (TgUINT_E32)(T_NAME(u,).T_NAME(ps,) - T_NAME_VAR(asPH_,));
    TgSTD_ATOMIC(fetch_add_explicit)( &T_NAME_VAR(xnuiPH_,), 1, TgSTD_MEMORY_ORDER(relaxed) );

    /* Initialize the object */

#if defined(T_GLOBAL)
    T_ID(tgPH_,_ID_Init)( &T_NAME(u,).T_NAME(ps,)->T_NAME(m_ti,), uiIndex, (TgUINT_E08)ETgPH_MAX_WORLD, KTgPH_MAX_SCENE );
#else
    T_ID(tgPH_,_ID_Init)( &T_NAME(u,).T_NAME(ps,)->T_NAME(m_ti,), uiIndex, (TgUINT_E08)tiWorld.m_uiI, KTgPH_MAX_SCENE );
#endif

    sCommand.tiID.m_uiKI = T_NAME(u,).T_NAME(ps,)->T_NAME(m_ti,).m_uiKI;

    if (TgSUCCEEDED(tgCM_UT__CMD_BUF__Queue_Command( g_asPH_Command_To_World + sCommand.tiID.m_uiWorld, T_NAME(tgPH_,_Init_Do_Command), sizeof(sCommand), &sCommand )))
    {
        return (T_NAME(u,).T_NAME(ps,)->T_NAME(m_ti,));
    };

    /* Failed to add the init command. Invalidate the object and put it back on the free stack, and return a failure (invalid id). */
    T_NAME(u,).T_NAME(ps,)->T_NAME(m_ti,).m_uiKI = KTgID__INVALID_VALUE;
    tgCM_UT_LF__ST__Push( &T_NAME_VAR(sPH_,_Free_Stack).m_sStack, T_NAME(u,).psNode );
    TgSTD_ATOMIC(fetch_sub_explicit)( &T_NAME_VAR(xnuiPH_,), 1, TgSTD_MEMORY_ORDER(relaxed) );

    return T_ID(KTgPH_,_ID__INVALID);
}
/*# !defined(T_STATIC) */
#endif


/* ---- T_NAME(tgPH_,_Reset) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT T_NAME(tgPH_,_Reset)( T_ID(TgPH_,_ID_C) tiID )
{
#if !defined(T_STATIC) && !defined(T_GLOBAL)
    TgPH_WORLD_ID_C                     tiWorld = { .m_uiI = tiID.m_uiWorld };
/*# !defined(T_STATIC) && !defined(T_GLOBAL) */
#endif

#if !defined(T_STATIC)
    struct
    {
        T_ID(TgPH_,_ID_C)                   tiID;
    }                                   sCommand = { tiID };
/*# !defined(T_STATIC) */
#endif

    #if defined(T_GLOBAL)
    TgPARAM_CHECK(tiID.m_uiWorld == ETgPH_MAX_WORLD);
    #else
    if (tiID.m_uiWorld >= ETgPH_MAX_WORLD)
        return KTgE_FAIL;
    #endif

    #if defined(T_STATIC)
    if (tiID.m_uiI >= T_ID(ETgPH_MAX_,))
        return KTgE_FAIL;
    #else
    if (tiID.m_uiI >= T_NAME_VAR(nuiPH_,_Total_Commit))
        return KTgE_FAIL;
    #endif

#if !defined(T_STATIC)
    return tgCM_UT__CMD_BUF__Queue_Command( g_asPH_Command_To_World + tiID.m_uiWorld, T_NAME(tgPH_,_Reset_Do_Command), sizeof(sCommand), &sCommand );
/*# !defined(T_STATIC) */
#else
    return T_NAME(tgPH_,_Reset_Internal)( T_NAME_DECLARE(asPH_,) + tiID.m_uiI );
/*# !defined(T_STATIC) */
#endif
}


/* ---- T_NAME(tgPH_,_Query_Count) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(T_GLOBAL)
TgRSIZE T_NAME(tgPH_,_Query_Count)( TgVOID )
#else
TgRSIZE T_NAME(tgPH_,_Query_Count)( TgPH_WORLD_ID_C tiWorld )
#endif
{
#if !defined(T_STATIC)
    #if defined(T_GLOBAL)
    return (TgSTD_ATOMIC(load)( &T_NAME(g_xnuiPH_,) ));
    #else
    if (tiWorld.m_uiI >= ETgPH_MAX_WORLD)
        return 0;
    return (TgSTD_ATOMIC(load)( &T_NAME(g_axnuiPH_,)[tiWorld.m_uiI] ));
    #endif
/*# !defined(T_STATIC) */
#else

    return T_ID(ETgPH_MAX_,);

/*# !defined(T_STATIC) */
#endif
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- T_NAME(tgPH_Module_,_Init) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgPH_Module_,_Init)( TgVOID )
{
#if !defined(T_STATIC)
#if !defined(T_GLOBAL)
    TgPH_WORLD_ID                       tiWorld = { .m_uiKI = 0 };

    for (tiWorld.m_uiI = (TgUINT_E64)ETgPH_WORLD__BEGIN; tiWorld.m_uiI < (TgUINT_E64)ETgPH_WORLD__END; ++tiWorld.m_uiI)
#endif
    {
        T_NAME_VAR(nuiPH_,_Increase_Commit) = 0;
        T_NAME_VAR(nuiPH_,_Total_Commit) = 0;
        T_NAME_VAR(nuiPH_,_Total_Reserve) = 0;
    }

    T_NAME(tgPH_Module_,_Init_Internal)();

#if !defined(T_GLOBAL)
    for (tiWorld.m_uiI = (TgUINT_E64)ETgPH_WORLD__BEGIN; tiWorld.m_uiI < (TgUINT_E64)ETgPH_WORLD__END; ++tiWorld.m_uiI)
#endif
    {
        tgCM_UT_LF__ST__Init( & T_NAME_VAR(sPH_,_Free_Stack).m_sStack );
        TgSTD_ATOMIC(store_explicit)( & T_NAME_VAR(xnuiPH_,), 0, TgSTD_MEMORY_ORDER(relaxed) );
        T_NAME_VAR(asPH_,) = (T_NAME(STg2_PH_,_P))TgRESERVE_VIRTUAL( T_NAME_VAR(nuiPH_,_Total_Reserve) * sizeof( T_NAME(STg2_PH_,) ) );

        tgCM_UT_LF__SN__Init( & T_NAME_VAR(sPH_,_Commit_Lock).m_sLock );
        TgSTD_ATOMIC(store_explicit)( &T_NAME_VAR(xnuiPH_,_Total__Used), 0, TgSTD_MEMORY_ORDER(relaxed) );
    }
/*# !defined(T_STATIC) */
#else
#if !defined(T_GLOBAL)
    TgPH_WORLD_ID                       tiWorld = { .m_uiKI = 0 };

    for (tiWorld.m_uiI = (TgUINT_E64)ETgPH_WORLD__BEGIN; tiWorld.m_uiI < (TgUINT_E64)ETgPH_WORLD__END; ++tiWorld.m_uiI)
#endif
    {
        TgSINT_E32                          iIndex;

        /* Static resources are all initialized during the module init. */

        for (iIndex = 0; iIndex < T_ID(ETgPH_MAX_,); ++iIndex)
        {
            T_NAME(tgPH_,_Init_Internal)( T_NAME_VAR(asPH_,) + iIndex );
        }
    }

/*# !defined(T_STATIC) */
#endif
}


/* ---- T_NAME(tgPH_Module_,_Free) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgPH_Module_,_Free)( TgVOID )
{
#if !defined(T_STATIC)
#if !defined(T_GLOBAL)
    TgPH_WORLD_ID                       tiWorld = { .m_uiKI = 0 };
#endif

#if !defined(T_GLOBAL)
    for (tiWorld.m_uiI = (TgUINT_E64)ETgPH_WORLD__BEGIN; tiWorld.m_uiI < (TgUINT_E64)ETgPH_WORLD__END; ++tiWorld.m_uiI)
#endif
    {
        tgCM_UT_LF__ST__Free( & T_NAME_VAR(sPH_,_Free_Stack).m_sStack );
        tgCM_UT_LF__SN__Free_Unsafe( & T_NAME_VAR(sPH_,_Commit_Lock).m_sLock );
        TgFREE_VIRTUAL( T_NAME_VAR( asPH_, ) );
        T_NAME_VAR(nuiPH_,_Increase_Commit) = 0;
        T_NAME_VAR(nuiPH_,_Total_Commit) = 0;
        T_NAME_VAR(nuiPH_,_Total_Reserve) = 0;
    }
/*# !defined(T_STATIC) */
#endif
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- T_NAME(tgPH_,_Grow_Reserve_List) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* Precondition: This is under a write lock for the associated data, and tiWorld is validated.                                                                                     */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TGS_TOOLS) && TGS_TOOLS && !defined(T_STATIC)
#if defined(T_GLOBAL)
static T_NAME(STg2_PH_,_P) T_NAME(tgPH_,_Grow_Reserve_List)( TgVOID )
#else
static T_NAME(STg2_PH_,_P) T_NAME(tgPH_,_Grow_Reserve_List)( TgPH_WORLD_ID_C tiWorld )
#endif
{
    TgRSIZE_C                           nbyIncrease_Commit = T_NAME_VAR(nuiPH_,_Increase_Commit) * sizeof( T_NAME(STg2_PH_,) );
    TgRSIZE                             nuiTotal_Commit = T_NAME_VAR(nuiPH_,_Total_Commit);
    TgRSIZE                             nbyTotal_Commit = nuiTotal_Commit * sizeof( T_NAME(STg2_PH_,) );

    TgRSIZE                             nbyTotal_Reserve = T_NAME_VAR(nuiPH_,_Total_Reserve) * sizeof( T_NAME(STg2_PH_,) );

    TgRSIZE                             nuiCommit_Start;

    union
    {
        T_NAME(STg2_PH_,_P)                 T_NAME(ps,);
        STg2_UT_ST__ST_Node_P               psNode;
        
    }                                   T_NAME(u,);

    /* Pop the next free object off the stack, checking for the race condition where a previous thread already increased the size of the array. */
    T_NAME(u,).psNode = tgCM_UT_LF__ST__Pop( &T_NAME_VAR(sPH_,_Free_Stack).m_sStack );
    if (nullptr != T_NAME(u,).psNode)
    {
        return (T_NAME(u,).T_NAME(ps,));
    };

    nuiCommit_Start = T_NAME_VAR(nuiPH_,_Total_Commit);

    /* If we have already reserved more nodes in the array, commit the memory and add them to the free stack. */
    if (T_NAME_VAR(nuiPH_,_Total_Commit) < T_NAME_VAR(nuiPH_,_Total_Reserve))
    {
        T_NAME(STg2_PH_,_P)                 T_NAME(ps,_Check);

        nbyTotal_Commit = tgMM_Required_Virtual_Size( tgCM_MIN_UMAX( nbyTotal_Reserve, nbyTotal_Commit + nbyIncrease_Commit ) );

        T_NAME(ps,_Check) = (T_NAME(STg2_PH_,_P))TgCOMMIT_VIRTUAL( T_NAME_VAR(asPH_,), 0, nbyTotal_Commit );
        if (nullptr == T_NAME(ps,_Check))
        {
            return nullptr;
        };

        nuiTotal_Commit = nbyTotal_Commit / sizeof( T_NAME(STg2_PH_,) );
        T_NAME_VAR(nuiPH_,_Total_Commit) = nuiTotal_Commit;
    }
    else
    {
        T_NAME(STg2_PH_,_P)                 T_NAME(psNew_,);

        /* Resize the array, reserving and committing memory according to the configuration. */

        nbyTotal_Reserve = tgMM_Required_Virtual_Size( nbyTotal_Reserve + nbyIncrease_Commit );
        nbyTotal_Commit = tgMM_Required_Virtual_Size( nbyTotal_Commit + nbyIncrease_Commit );

        T_NAME(psNew_,) = (T_NAME(STg2_PH_,_P))TgRESERVE_VIRTUAL( nbyTotal_Reserve );
        if (nullptr == T_NAME(psNew_,))
        {
            return nullptr;
        };

        T_NAME(psNew_,) = (T_NAME(STg2_PH_,_P))TgCOMMIT_VIRTUAL( T_NAME(psNew_,), 0, nbyTotal_Commit );
        if (nullptr == T_NAME(psNew_,))
        {
            TgFREE_VIRTUAL( T_NAME(psNew_,) );
            return nullptr;
        };

        tgMM_Copy( T_NAME(psNew_,), nbyTotal_Commit, T_NAME_VAR(asPH_,), nuiTotal_Commit * sizeof( T_NAME(STg2_PH_,) ) );

        TgFREE_VIRTUAL(T_NAME_VAR(asPH_,));
        T_NAME_VAR(asPH_,) = T_NAME(psNew_,);
        
        nuiTotal_Commit = nbyTotal_Commit / sizeof( T_NAME(STg2_PH_,) );
        T_NAME_VAR(nuiPH_,_Total_Commit) = nuiTotal_Commit;
        T_NAME_VAR(nuiPH_,_Total_Reserve) = nbyTotal_Reserve / sizeof( T_NAME(STg2_PH_,) );
    };

    /* Add all but one of the newly available objects to the free stack. */
    for (; nuiCommit_Start + 1 < nuiTotal_Commit; ++nuiCommit_Start)
    {
        tgCM_UT_LF__ST__Push( &T_NAME_VAR(sPH_,_Free_Stack).m_sStack, &(T_NAME_VAR(asPH_,)[nuiCommit_Start].m_sNode_Stack) );
    };

    /* Return the last available object (which was not added to the free stack). */
    return (T_NAME_VAR(asPH_,) + nuiTotal_Commit - 1);
}
/*# defined(TGS_TOOLS) && TGS_TOOLS && !defined(T_STATIC) */
#endif


/* ---- T_NAME(tgPH_,_Grow_Commit_List) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if !defined(T_STATIC)
#if defined(T_GLOBAL)
T_NAME(STg2_PH_,_P) T_NAME(tgPH_,_Grow_Commit_List)( TgVOID )
#else
T_NAME(STg2_PH_,_P) T_NAME(tgPH_,_Grow_Commit_List)( TgPH_WORLD_ID_C tiWorld )
#endif
{
    tgCM_UT_LF__SN__Lock_Spin( &T_NAME_VAR(sPH_,_Commit_Lock).m_sLock );
    {
        TgRSIZE_C                           nbyIncrease_Commit = T_NAME_VAR(nuiPH_,_Increase_Commit) * sizeof( T_NAME(STg2_PH_,) );
        TgRSIZE                             nuiTotal_Commit = T_NAME_VAR(nuiPH_,_Total_Commit) ;
        TgRSIZE                             nbyTotal_Commit = nuiTotal_Commit * sizeof( T_NAME(STg2_PH_,) );
        union
        {
            T_NAME(STg2_PH_,_P)                 T_NAME(ps,);
            STg2_UT_ST__ST_Node_P               psNode;
        
        }                                   T_NAME(u,);

        /* Validate that the free stack is empty */
        TgPARAM_CHECK(T_NAME_VAR(nuiPH_,_Increase_Commit) >= 1);

        /* Now that we are in the lock, check to see if another thread already increased the commit space. */
        T_NAME(u,).psNode = tgCM_UT_LF__ST__Pop( &T_NAME_VAR(sPH_,_Free_Stack).m_sStack );
        if (nullptr != T_NAME(u,).psNode)
        {
            tgCM_UT_LF__SN__Signal( &T_NAME_VAR(sPH_,_Commit_Lock).m_sLock );
            return T_NAME(u,).T_NAME(ps,);
        };

        TgPARAM_CHECK( tgCM_UT_LF__ST__Is_Empty( &T_NAME_VAR(sPH_,_Free_Stack).m_sStack ) );

        /* If we have already reserved more nodes in the array, commit the memory and add them to the free stack */
        if (T_NAME_VAR(nuiPH_,_Total_Commit) < T_NAME_VAR(nuiPH_,_Total_Reserve))
        {
            TgRSIZE_C                           nbyTotal_Reserve = T_NAME_VAR(nuiPH_,_Total_Reserve) * sizeof( T_NAME(STg2_PH_,) );

            T_NAME(STg2_PH_,_P)                 T_NAME(ps,_Check);
            TgRSIZE                             nuiCommit_Start;

            nbyTotal_Commit = tgMM_Required_Virtual_Size( tgCM_MIN_UMAX( nbyTotal_Reserve, nbyTotal_Commit + nbyIncrease_Commit ) );

            T_NAME(ps,_Check) = (T_NAME(STg2_PH_,_P))TgCOMMIT_VIRTUAL( T_NAME_VAR(asPH_,), 0, nbyTotal_Commit );
            if (nullptr == T_NAME(ps,_Check))
            {
                tgCM_UT_LF__SN__Signal( &T_NAME_VAR(sPH_,_Commit_Lock).m_sLock );
                return nullptr;
            };

            nuiCommit_Start = nuiTotal_Commit;
            nuiTotal_Commit = nbyTotal_Commit / sizeof( T_NAME(STg2_PH_,) );
            T_NAME_VAR(nuiPH_,_Total_Commit) = nuiTotal_Commit;

            for (; nuiCommit_Start + 1 < nuiTotal_Commit; ++nuiCommit_Start)
            {
                tgCM_UT_LF__ST__Push( &T_NAME_VAR(sPH_,_Free_Stack).m_sStack, &(T_NAME_VAR(asPH_,)[nuiCommit_Start].m_sNode_Stack) );
            };

            tgCM_UT_LF__SN__Signal( &T_NAME_VAR(sPH_,_Commit_Lock).m_sLock );
            return (T_NAME_VAR(asPH_,) + nuiTotal_Commit - 1);
        }
        else
        {
        #if defined(TGS_TOOLS) && TGS_TOOLS
            /* In general, we do not want to resize the these arrays during the game run time. However, for tools it may make sense. It will cause a frame hitch. */
            T_NAME(STg2_PH_,_P)                 T_NAME(psReturn_,);
            #if defined(T_GLOBAL)
            T_NAME(psReturn_,) = T_NAME(tgPH_,_Grow_Reserve_List)();
            #else
            T_NAME(psReturn_,) = T_NAME(tgPH_,_Grow_Reserve_List)( tiWorld );
            #endif

            return T_NAME(psReturn_,);

        /*# defined(TGS_TOOLS) && TGS_TOOLS */
        #else

            tgCM_UT_LF__SN__Signal( &T_NAME_VAR(sPH_,_Commit_Lock).m_sLock );
            return (nullptr);

        /*# defined(TGS_TOOLS) && TGS_TOOLS */
        #endif
        };
    };
}
/*# !defined(T_STATIC) */
#endif




/*# defined (ENABLE_RELOAD_GUARD) */
#endif
