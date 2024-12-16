/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Partition - Constants.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PARTITION_CONSTANTS_H)
#define TGS_PARTITION_CONSTANTS_H
#pragma once

#if !defined(TGS_PARTITION_H)
#error This file should not be included directly - use the correct platform include wrapper
#endif


/* == Partition ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_PARTITION Object Partition Managers (Scene Graphs)
*/

    /** @defgroup TGS_PARTITION_MODULE Module Management Functions
        @ingroup TGS_PARTITION
    */

    /** @defgroup TGS_PARTITION_SYSTEM Module Functions
        @ingroup TGS_PARTITION
    */

    /** @defgroup TGS_PARTITION_PRUNE_AND_SWEEP Prune and Sweep Functions
        @ingroup TGS_PARTITION
    */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_ENUM(ETgPA_GRAPH_TYPE, TgSINT_E32,

    ETgPA_GRAPH_TYPE__BEGIN,

    ETgPA_GRAPH_TYPE__UNKNOWN = ETgPA_GRAPH_TYPE__BEGIN,    ETgPA_GRAPH_TYPE__BINARY_SPACE,                         ETgPA_GRAPH_TYPE__BOUNDING_VOLUME_TREE,
    ETgPA_GRAPH_TYPE__PRUNE_SWEEP,                          ETgPA_GRAPH_TYPE__SPHERE,                               ETgPA_GRAPH_TYPE__BOX_TREE,
    ETgPA_GRAPH_TYPE__AXIS_ALIGNED_BOUNDING_BOX,

    ETgPA_GRAPH_TYPE__END,
    ETgPA_GRAPH_TYPE__MAX = ETgPA_GRAPH_TYPE__END,
    ETgPA_GRAPH_TYPE__COUNT = ETgPA_GRAPH_TYPE__END - ETgPA_GRAPH_TYPE__BEGIN,
);

enum { /* PA GRAPH requires last two bits, 0-47 are intersection test (0 != CategeoryA & CollideB && 0 != CategeoryB & CollideA),
          48-61 are union tests (0 != CategeoryA & CollideB || 0 != CategeoryB & CollideA) */

       KTgPA_CATEGORY_BIT__RESERVED__PA_GRAPH_0     = 63,
       KTgPA_CATEGORY_BIT__RESERVED__PA_GRAPH_1     = 62,
       KTgPA_CATEGORY_BIT__RESERVED__USER_0         = 61,
       KTgPA_CATEGORY_BIT__RESERVED__USER_1         = 60,
       KTgPA_CATEGORY_BIT__LAST_OR_BIT              = 59,
       KTgPA_CATEGORY_BIT__LAST_AND_BIT             = 47,
};

TgEXTN TgUINT_E64_C                         KTgPA_CATEGORY_BIT_MASK__RESERVED;
TgEXTN TgUINT_E64_C                         KTgPA_CATEGORY_BIT_MASK__OR_TEST;
TgEXTN TgUINT_E64_C                         KTgPA_CATEGORY_BIT_MASK__AND_TEST;


/* =============================================================================================================================================================================== */
#endif
