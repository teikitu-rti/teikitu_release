/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Data.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_DATA_H)
#define TGS_KERNEL_DATA_H
#pragma once


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgJOB_QUEUE_ID                       g_sJob_Stack__JiT; /**< Emergency must-get done work that will stall execution */
TgEXTN TgJOB_QUEUE_ID                       g_sJob_Queue__Render_High; /**< Queue used by the render system - take priority over the Game Queues */
TgEXTN TgJOB_QUEUE_ID                       g_sJob_Queue__Render_Normal; /**< Queue used by the render system - take priority over the Game Queues */
TgEXTN TgJOB_QUEUE_ID                       g_sJob_Queue__GPU; /**< Queue used by the render system - take priority over the Game Queues */
TgEXTN TgJOB_QUEUE_ID                       g_sJob_Queue__Client_High; /**< Used for jobs that are dependencies for large amounts of work */
TgEXTN TgJOB_QUEUE_ID                       g_sJob_Queue__Client_Normal; /**< Standard queue for all game jobs */
TgEXTN TgJOB_QUEUE_ID                       g_sJob_Queue__Client_Low; /**< These should be expected to take more than one frame */

TgEXTN TgJOB_THREAD_ID                      g_atiJob_Thread[KTgMAX_NUM_THREAD]; /**< Default thread pool created by the kernel for the job manager. */

TgEXTN TgKN_FS_MOUNT_ID                     g_tiKN_FS_HDD__Mount_APP;


/* =============================================================================================================================================================================== */
#endif
