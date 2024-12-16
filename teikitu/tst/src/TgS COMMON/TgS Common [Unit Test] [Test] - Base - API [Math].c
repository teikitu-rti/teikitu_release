/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Base - API [Math].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include <float.h>

/* == Common ===================================================================================================================================================================== */
/* @MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                  */

#define TEMPLATE__ENABLE_INTEGER

#define TEMPLATE__TYPE_SIZE 8
#include "TgS Common [Unit Test] [Test] - Base - API [Math].c_inc"
#define TEMPLATE__TYPE_SIZE 16
#include "TgS Common [Unit Test] [Test] - Base - API [Math].c_inc"
#define TEMPLATE__TYPE_SIZE 32
#include "TgS Common [Unit Test] [Test] - Base - API [Math].c_inc"
#define TEMPLATE__TYPE_SIZE 64
#include "TgS Common [Unit Test] [Test] - Base - API [Math].c_inc"
#define TEMPLATE__OVERRIDE_INT_TYPE PTR
#include "TgS Common [Unit Test] [Test] - Base - API [Math].c_inc"
#define TEMPLATE__OVERRIDE_INT_TYPE MAX
#include "TgS Common [Unit Test] [Test] - Base - API [Math].c_inc"

#undef TEMPLATE__ENABLE_INTEGER

#include "TgS Common [Unit Test] [Test] - Base - API [Math].c_inc"
