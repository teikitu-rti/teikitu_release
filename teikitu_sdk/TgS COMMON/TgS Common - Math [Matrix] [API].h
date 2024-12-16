/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Matrix] [API].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_MATRIX_API_H)


#if defined(TEMPLATE_TYPE_EXPANSION__RELOAD)

/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#include "TgS COMMON/TgS Common - Math [Matrix] [S].h"
#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */
    #include "TgS COMMON/TgS Common - Math [Matrix].h"
#endif

#if defined(TEMPLATE__ENABLE_INTEGER)
    #error Not supported

#else
    #include "TgS COMMON/TgS Common - Math [Matrix] [S] [F].h"
    #if (4 == TEMPLATE__VECTOR_COL)
        #include "TgS COMMON/TgS Common - Math [Matrix] [S] [F] [44].h"
    #elif (3 == TEMPLATE__VECTOR_COL)
        #include "TgS COMMON/TgS Common - Math [Matrix] [S] [F] [34].h"
    #endif

    #if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */
        #include "TgS COMMON/TgS Common - Math [Matrix] [F].h"
        #if (4 == TEMPLATE__VECTOR_COL)
            #include "TgS COMMON/TgS Common - Math [Matrix] [F] [44].h"
        #elif (3 == TEMPLATE__VECTOR_COL)
            #include "TgS COMMON/TgS Common - Math [Matrix] [F] [34].h"
        #endif
    #endif

#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */


/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TEMPLATE__TEST_AND_UNLOAD_TEMPLATE_MACROS

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__VECTOR_COL 3
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__VECTOR_COL 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__VECTOR_COL 3
    #define TEMPLATE__TYPE_SIZE 64
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__VECTOR_COL 4
    #define TEMPLATE__TYPE_SIZE 64
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COMMON_MATH_VECTOR_API_H) */
#endif
