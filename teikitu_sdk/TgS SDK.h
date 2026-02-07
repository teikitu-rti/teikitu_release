/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS SDK.h
    »Author«    Andrew Aye (EMail: mailto:andrew.aye@gmail.com, Web: http://www.andrewaye.com)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_SDK_H)
#define TGS_SDK_H

// Ring 0
#include "TgS Common.h"
#include "TgS Collision.h"
#include "TgS Partition.h"
#include "TgS Path-AI.h"

// Ring 1 - External additions to the engine
#include "TgS Utility.h"

// Ring 2
#include "TgS Kernel.h"
#include "TgS Kernel [GPU].h"

// Ring 3
#include "TgS Input.h"
#include "TgS Physics.h"

// In general, developers are encouraged to include the inline files only on a as-needed basis to reduce the compilation stall caused by PCH processing. However, this one is core
// to fundamental functions that it makes sense to include it into the PCH.
#include "TgS COMMON/TgS Common.inl"


/* =============================================================================================================================================================================== */
#endif

