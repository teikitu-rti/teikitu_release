/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_TYPE_H)
#define TGS_COMMON_BASE_TYPE_H
#pragma once


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Standard Types ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_DECLARE( int8_t,                     TgSINT_E08 );
TgTYPE_DECLARE( int16_t,                    TgSINT_E16 );
TgTYPE_DECLARE( int32_t,                    TgSINT_E32 );
TgTYPE_DECLARE( long long,                  TgSINT_E64 );
TgTYPE_DECLARE( int_fast8_t,                TgSINT_F08 );
TgTYPE_DECLARE( int_fast16_t,               TgSINT_F16 );
TgTYPE_DECLARE( int_fast32_t,               TgSINT_F32 );
TgTYPE_DECLARE( int_fast64_t,               TgSINT_F64 );
TgTYPE_DECLARE( intptr_t,                   TgSINT_PTR );
TgTYPE_DECLARE( intmax_t,                   TgSINT_MAX );
TgTYPE_DECLARE( ptrdiff_t,                  TgSINT_PTR_DIFF );

TgTYPE_DECLARE( uint8_t,                    TgUINT_E08 );
TgTYPE_DECLARE( uint16_t,                   TgUINT_E16 );
TgTYPE_DECLARE( uint32_t,                   TgUINT_E32 );
TgTYPE_DECLARE( unsigned long long,         TgUINT_E64 );
TgTYPE_DECLARE( uint_fast8_t,               TgUINT_F08 );
TgTYPE_DECLARE( uint_fast16_t,              TgUINT_F16 );
TgTYPE_DECLARE( uint_fast32_t,              TgUINT_F32 );
TgTYPE_DECLARE( uint_fast64_t,              TgUINT_F64 );
TgTYPE_DECLARE( uintptr_t,                  TgUINT_PTR );
TgTYPE_DECLARE( uintmax_t,                  TgUINT_MAX );

TgTYPE_DECLARE( size_t,                     TgSIZE_ALL );
TgTYPE_DECLARE( rsize_t,                    TgRSIZE );

TgTYPE_DECLARE( char,                       TgCHAR_NC );
TgTYPE_DECLARE( wchar_t,                    TgCHAR_WC );
TgTYPE_DECLARE( char8_t,                    TgCHAR_U8 ); /**< UTF-8 encoded strings is the only multibyte format supported */

TgTYPE_DECLARE( float,                      TgFLOAT32 );
TgTYPE_DECLARE( double,                     TgFLOAT64 );

typedef void                                TgVOID;
TgTYPE_MODIFIER_PTR_DEFAULT(                TgVOID );

#if defined(TgCOMPILE_OS_TEXT__WIDE)
    TgTYPE_DECLARE( TgCHAR_WC,                  TgOSCHAR );
#else
    TgTYPE_DECLARE( TgCHAR_NC,                  TgOSCHAR );
#endif

TgTYPE_DECLARE( TgUINT_E32,                 TgFILE );
TgTYPE_DECLARE( TgSINT_E32,                 TgRESULT );
TgTYPE_DECLARE( TgSINT_F64,                 TgTIME );


/* ---- Non Standard Types ------------------------------------------------------------------------------------------------------------------------------------------------------- */

#if defined(TgCOMPILE_FILE__CXX)
TgTYPE_DECLARE( bool,                       TgBOOL );
#else
TgTYPE_DECLARE( _Bool,                      TgBOOL );
#endif

TgTYPE_UNION(TgCOLOUR32,)
{
    TgUINT_E32                                  m_ui32;
    struct
    {
        TgUINT_E08                                  m_uiRed;
        TgUINT_E08                                  m_uiGreen;
        TgUINT_E08                                  m_uiBlue;
        TgUINT_E08                                  m_uiAlpha;
    };
};

TgTYPE_STRUCT(STg2_Connection,)
{
    STg2_Connection_P                           m_psParent;
    STg2_Connection_P                           m_psNext_Parent_Child;
    STg2_Connection_P                           m_psNextHash;
};

typedef TgUINT_E32( *TgPLATFORM_THREAD_FCN )( TgUINT_PTR_C );
TgTYPE_MODIFIER_DEFAULT( TgPLATFORM_THREAD_FCN );


/* ---- Alias Union -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @union that contains all native (natural) types for easy alias access*/
TgTYPE_UNION(TgUN_SCALAR,)
{
    TgALIGN(8) TgUINT_E64                       m_uiMask;
    TgUINT_F08                                  m_uiF08;
    TgUINT_F08                                  m_varUINT_F08;
    TgUINT_F16                                  m_uiF16;
    TgUINT_F16                                  m_varUINT_F16;
    TgUINT_E32                                  m_uiF32;
    TgUINT_E32                                  m_varUINT_F32;
    TgUINT_F64                                  m_uiF64;
    TgUINT_F64                                  m_varUINT_F64;
    TgSINT_F08                                  m_iF08;
    TgSINT_F08                                  m_varSINT_F08;
    TgSINT_F16                                  m_iF16;
    TgSINT_F16                                  m_varSINT_F16;
    TgSINT_E32                                  m_iF32;
    TgSINT_E32                                  m_varSINT_F32;
    TgSINT_F64                                  m_iF64;
    TgSINT_F64                                  m_varSINT_F64;
    TgUINT_E08                                  m_uiE08;
    TgUINT_E08                                  m_varUINT_E08;
    TgUINT_E16                                  m_uiE16;
    TgUINT_E16                                  m_varUINT_E16;
    TgUINT_E32                                  m_uiE32;
    TgUINT_E32                                  m_varUINT_E32;
    TgUINT_E64                                  m_uiE64;
    TgUINT_E64                                  m_varUINT_E64;
    TgSINT_E08                                  m_iE08;
    TgSINT_E08                                  m_varSINT_E08;
    TgSINT_E16                                  m_iE16;
    TgSINT_E16                                  m_varSINT_E16;
    TgSINT_E32                                  m_iE32;
    TgSINT_E32                                  m_varSINT_E32;
    TgSINT_E64                                  m_iE64;
    TgSINT_E64                                  m_varSINT_E64;
    TgFLOAT32                                   m_f32;
    TgFLOAT32                                   m_varF32;
    TgFLOAT64                                   m_f64;
    TgFLOAT64                                   m_varF64;

    TgBOOL                                      m_b;
    TgRSIZE                                     m_uiRSIZE;
    TgSIZE_ALL                                  m_uiSIZE;
    TgCHAR_NC                                   m_nc;
    TgCHAR_WC                                   m_wc;
    TgCHAR_U8                                   m_mb;
    TgUINT_MAX                                  m_uiMAX;
    TgSINT_MAX                                  m_iMAX;
    TgUINT_PTR                                  m_uiPTR;
    TgSINT_PTR                                  m_iPTR;

    TgVOID_P                                    m_pPTR;
};
TgCOMPILER_ASSERT(8 == sizeof(TgUN_SCALAR),);

/** @union that contains a pointer to all native (natural) types for easy alias access*/
TgTYPE_UNION(TgUN_POINTER,)
{
    TgUINT_F08_P                                m_pui08;
    TgUINT_F16_P                                m_pui16;
    TgUINT_E32_P                                m_pui32;
    TgUINT_F64_P                                m_pui64;
    TgSINT_F08_P                                m_pi08;
    TgSINT_F16_P                                m_pi16;
    TgSINT_E32_P                                m_pi32;
    TgSINT_F64_P                                m_pi64;
    TgUINT_E08_P                                m_puiE08;
    TgUINT_E16_P                                m_puiE16;
    TgUINT_E32_P                                m_puiE32;
    TgUINT_E64_P                                m_puiE64;
    TgSINT_E08_P                                m_piE08;
    TgSINT_E16_P                                m_piE16;
    TgSINT_E32_P                                m_piE32;
    TgSINT_E64_P                                m_piE64;
    TgFLOAT32_P                                 m_pf32;
    TgFLOAT64_P                                 m_pf64;
    TgBOOL_P                                    m_pb;
    TgRSIZE_P                                   m_puiRSIZE;
    TgSIZE_ALL_P                                m_puiSIZE;
    TgCHAR_NC_P                                 m_ncz;
    TgCHAR_WC_P                                 m_wcz;
    TgCHAR_U8_P                                 m_mbz;
    TgUINT_MAX_P                                m_puiMAX;
    TgSINT_MAX_P                                m_piMAX;
    TgUINT_PTR_P                                m_puiPTR;
    TgSINT_PTR_P                                m_piPTR;

    TgVOID_P                                    m_p;
    TgVOID_P                                    m_pVoid;
    TgUINT_PTR                                  m_uiPTR;
    TgSINT_PTR                                  m_iPTR;
    TgRSIZE                                     m_uiRSIZE;
};
TgTYPE_DECLARE(TgUN_POINTER,TgUN_PTR);


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
TgCOMPILER_ASSERT(sizeof(rsize_t) == TgBUILD_HARDWARE__WORDSIZE,0);
TgCOMPILER_ASSERT(sizeof(size_t) == TgBUILD_HARDWARE__WORDSIZE,0);
TgCOMPILER_ASSERT(sizeof(uintmax_t) == TgBUILD_HARDWARE__WORDSIZE,0);
TgCOMPILER_ASSERT(sizeof(uintptr_t) == TgBUILD_HARDWARE__WORDSIZE,0);

#include "TgS COMMON/TgS Common - Base - Type [Vector].h"
#include "TgS COMMON/TgS Common - Base - Type [Limits].h"
#include "TgS COMMON/TgS Common - Base - Type [Constants].h"
#include "TgS COMMON/TgS Common - Base - Type [MT].h"
#include "TgS COMMON/TgS Common - Base - Type [IO].h"
#include "TgS COMMON/TgS Common - Base - Type [File].h"

#include "TgS Ring 0 - Type.h"
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */


/* =============================================================================================================================================================================== */
#endif
