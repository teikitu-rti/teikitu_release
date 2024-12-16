/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Profile Sample.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*   ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_COMMON_UTIL_MP_PROFILE_SAMPLE_H)
#define TGS_COMMON_UTIL_MP_PROFILE_SAMPLE_H
#pragma once


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_UTIL_MT_PROFILE_RECORD Profile Record
    @ingroup TGS_COMMON_UTILITY_MT
    @warning WARNING: Keep in mind that there is no guarantee (and in fact is unlikely) that the execution of a large amount of code will not be stalled by other thread processing
    taking the CPU context. Therefore, the timing reported by this process is more of a rough guide or framework since it only considers the time between the two markers (start,
    stop) and not the actual amount of time spent processing on the hardware.
    @note We use 16 bits to record the max depth (recursion) into the profile marker, and 48 bits (of a possible 64 bits) to record the CPU cycle count | timer. Note that the
    system returns the relative count from process start.
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_STRUCT(STg2_Profile_Record,)
{
    TgALIGN(TgCCL) TgSINT_F64_A                 m_iRecord_DepthAndStart;
    TgUINT_E08                                  m_uiPad0[TgCCL - (8 % TgCCL)];
    TgSINT_F64_A                                m_iRecord_Idle_Total;
    TgUINT_E08                                  m_uiPad1[TgCCL - (8 % TgCCL)];
    TgSINT_F64_A                                m_iRecord_Sample_Total;
    TgUINT_E08                                  m_uiPad2[TgCCL - (8 % TgCCL)];

    TgFLOAT32                                   m_fReport_Sample;
    TgFLOAT32                                   m_fReport_Idle;
    TgFLOAT32                                   m_fReport_Total;
    TgUINT_E08                                  m_uiPad3[TgCCL - (12 % TgCCL)];
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Macros                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define OUTPUT_PERFORMANCE_CAPTURE( A, ... )                                                                                                                                        \
    {                                                                                                                                                                               \
        STg2_Profile_Record                 sProfile;                                                                                                                               \
        TgFLOAT64                           fExecute;                                                                                                                               \
        TgUINT_E64                          uiExecute;                                                                                                                              \
        TgCHAR_U8                           szExecute[32], szExecuteMSG[32];                                                                                                        \
                                                                                                                                                                                    \
        tgProfile_Sample_Reset( &sProfile );                                                                                                                                        \
        tgProfile_Sample_Start( &sProfile );                                                                                                                                        \
            __VA_ARGS__;                                                                                                                                                            \
        tgProfile_Sample_Stop( &sProfile );                                                                                                                                         \
        tgProfile_Sample_Report( &sProfile );                                                                                                                                       \
        fExecute = (TgFLOAT64)sProfile.m_fReport_Sample;                                                                                                                            \
        uiExecute = (TgUINT_E64)tgPM_FLOOR_F64( 1E3 * fExecute );                                                                                                                   \
        tgUSZ_Formatted_From_U64( szExecute, sizeof( szExecute ), uiExecute );                                                                                                      \
        tgUSZ_PrintF( szExecuteMSG, sizeof( szExecuteMSG ), u8"%s ns", szExecute );                                                                                                 \
        TgMSGF( 0x0, A u8": %s\n", szExecuteMSG );                                                                                                                                  \
    }




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/** @addtogroup TGS_COMMON_UTIL_MT_PROFILE_RECORD */
/** @{ */

/** @brief Reset the current profile sample (clear it)
    @param [in,out] ARG Pointer to a profile record object */
TgINLINE TgVOID
tgProfile_Sample_Reset(
    STg2_Profile_Record_PCU ARG );

/** @brief Mark the start of a profile sample
    @param [in,out] ARG Pointer to a profile record object
    @return The current time value that was used */
TgINLINE TgSINT_F64
tgProfile_Sample_Start(
    STg2_Profile_Record_PCU ARG );

/** @brief Mark the end of a profile sample
    @param [in,out] ARG Pointer to a profile record object
    @return The current time value that was used */
TgINLINE TgSINT_F64
tgProfile_Sample_Stop(
    STg2_Profile_Record_PCU  ARG );

/** @brief Generate a report from the profile record
    @param [in,out] ARG Pointer to a profile record object */
TgINLINE TgVOID
tgProfile_Sample_Report(
    STg2_Profile_Record_PCU ARG );

/** @} TGS_COMMON_UTIL_MT_PROFILE_RECORD */


/* =============================================================================================================================================================================== */
#endif
