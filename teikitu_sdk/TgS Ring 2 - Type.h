/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Ring 2 - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_RING_2_TYPE_H)
#define TGS_RING_2_TYPE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TgS Ring 0 - Type.h"


/* == Ring 2 ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  System ID                                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgKI_DECLARE(KN_NOTIFY_ID)
TgKI_DECLARE(KN_FILE_SYSTEM_ID)
TgKI_DECLARE(KN_FS_MOUNT_ID)
TgKI_DECLARE(KN_FILE_ID)
TgKI_DECLARE(KN_FILE_JOB_ID)

#if defined(TgBUILD_FEATURE__GRAPHICS)
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
TgKI_DECLARE(KN_GPU_CXT_HOST_ID) /**< Host Context ID - the physical machine that hosts the GPU hardware, and data managed by its memory controller. */
TgKI_DECLARE(KN_GPU_CXT_HOST_EXTN_ID) /**< Host Data External Context ID - resource UIDs that are made available outside of the kernel. */
TgKI_DECLARE(KN_GPU_CXT_DEVC_ID) /**< GPU Device Context ID - this may be a physical device, or a virtual device depending on the driver. */
TgKI_DECLARE(KN_GPU_CXT_EXEC_ID) /**< GPU Execution Context ID - represents a single GPU node, and data managed by its memory controller. */
TgKI_DECLARE(KN_GPU_CXT_SWAP_ID) /**< GPU SwapChain Context ID - represents a physical output device. */
TgKI_DECLARE(KN_GPU_CXT_WORK_ID) /**< GPU Work ID - represents a single self-contained command (list, allocator, heap, etc.). */
TgKI_DECLARE(KN_GPU_RENDER_TARGET_ID) /**< GPU Render Target ID - represents a single render target (framebuffer, texture, etc.). */
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

/* =============================================================================================================================================================================== */
#endif
