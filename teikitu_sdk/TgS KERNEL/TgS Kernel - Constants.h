/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Constants.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_CONSTANTS_H)
#define TGS_KERNEL_CONSTANTS_H
#pragma once

#include TgHEADER_OPERATING_SYSTEM(TgS KERNEL/TgS,Kernel - Constants.h) /**< Needed to define the number of job threads to create. */


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

enum { KTgKN_MAX_NOTIFY_ENTRIES             =  1024 };  /**< Maximum number of entities that can be notified */
enum { KTgKN_MAX_FILE_SYSTEM                =     4,    /**< Maximum number of file systems */
       KTgKN_MAX_FILE_SYSTEM_MOUNT          =    16,    /**< Maximum number of file system mounts */
       KTgKN_MAX_FILE_OPEN                  =  1024,    /**< Maximum number of file open requests */
       KTgKN_MAX_FILE_JOB                   =   256,    /**< Maximum number of jobs */
       KTgKN_MAX_FILE_FOLDERS               =   256,    /**< Maximum number of directories */
       KTgKN_MAX_FILE_PER_FOLDER            =  2048 };  /**< Maximum number of files per directory */
enum { KTgKN_RESOURCE_NAME_MAX              =    64 };  /**< Maximum size of a resource name */

TgCOMPILER_ASSERT( KTgKN_MAX_FILE_SYSTEM < 0xFFFF, 0 );


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_ENUM(ETgKN_IO_STATUS, TgSINT_E32,

    ETgKN_IO_STATUS__ERROR = -1,    ETgKN_IO_STATUS__INVALID = 0,   ETgKN_IO_STATUS__QUEUED,        ETgKN_IO_STATUS__EXECUTE,       ETgKN_IO_STATUS__DONE,
    ETgKN_IO_STATUS__CANCEL,        ETgKN_IO_STATUS__MAX,
);


/* =============================================================================================================================================================================== */
#endif
