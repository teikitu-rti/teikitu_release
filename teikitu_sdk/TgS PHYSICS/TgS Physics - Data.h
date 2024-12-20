/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Data.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_DATA_H)
#define TGS_PHYSICS_DATA_H
#pragma once


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Profile Markers                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

PROFILE_EXTERN( PH_COMMANDS__CLIENT );

#if defined(TgBUILD_FEATURE__CLIENT) || defined(TgBUILD_FEATURE__SERVER)
PROFILE_ARRAY_EXTERN( ETgPH_MAX_WORLD, PH_SIMULATE_BATCH );
PROFILE_EXTERN( PH_SIMULATE_BATCH_TOTAL );

PROFILE_ARRAY_EXTERN( ETgPH_MAX_WORLD, PH_COLLISION );
PROFILE_EXTERN( PH_COLLISION_TOTAL );

    PROFILE_ARRAY_EXTERN( ETgPH_MAX_WORLD, PH_COLLISION_WORLD );
    PROFILE_EXTERN( PH_COLLISION_WORLD_TOTAL );

        PROFILE_ARRAY_EXTERN( ETgPH_MAX_WORLD, PH_COLLISION_CONTACT_PAIR_GENEARTION );
        PROFILE_EXTERN( PH_COLLISION_CONTACT_PAIR_GENEARTION_TOTAL );

            PROFILE_ARRAY_EXTERN( ETgPH_MAX_WORLD, PH_COLLISION_CONTACT_CALLBACK );
            PROFILE_EXTERN( PH_COLLISION_CONTACT_CALLBACK_TOTAL );

PROFILE_ARRAY_EXTERN( ETgPH_MAX_WORLD, PH_BUILD_SETS );
PROFILE_EXTERN( PH_BUILD_SETS_TOTAL );

    PROFILE_ARRAY_EXTERN( ETgPH_MAX_WORLD, PH_BUILD_SETS_INNER );
    PROFILE_EXTERN( PH_BUILD_SETS_INNER_TOTAL );

PROFILE_ARRAY_EXTERN( ETgPH_MAX_WORLD, PH_SOLVE_SETS );
PROFILE_EXTERN( PH_SOLVE_SETS_TOTAL );

PROFILE_ARRAY_EXTERN( ETgPH_MAX_WORLD, PH_UPDATE_WORLD__SIMULATE_BATCH );
PROFILE_EXTERN( PH_SOLVER_BATCH_TOTAL );

PROFILE_ARRAY_EXTERN( ETgPH_MAX_WORLD, PH_CMD_BUFFER_EXECEUTE );
PROFILE_EXTERN( PH_CMD_BUFFER_EXECEUTE_TOTAL );
/*# defined(TgBUILD_FEATURE__CLIENT) || defined(TgBUILD_FEATURE__SERVER) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */


/* =============================================================================================================================================================================== */
#endif
