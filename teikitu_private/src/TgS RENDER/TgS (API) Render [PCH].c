/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (REF) Render [PCH].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Render ===================================================================================================================================================================== */

/* 2183: Empty Translation Unit */
TgCLANG_WARN_SUPPRESS(missing-prototypes)
TgVOID Prevent2183_REF_Render_Static( TgVOID )
{
}


#if defined(TgBUILD_FEATURE__GRAPHICS)
TgVOID tgRN_Calc_UV_Animation( TgATTRIBUTE_UNUSED TgVEC_F32_04_1_PCU ARG0, TgATTRIBUTE_UNUSED TgVEC_F32_04_1_PCU ARG1, TgATTRIBUTE_UNUSED TgRN_MATERIAL_ID_C ARG2, TgATTRIBUTE_UNUSED TgVEC_F32_04_1 ARG3, TgATTRIBUTE_UNUSED TgVEC_F32_04_1 ARG4 ) {} /* #IMPLEMENT */
TgVOID tgRN_Release_Mesh_Set( TgATTRIBUTE_UNUSED TgRN_MESH_SET_ID_C ARG0 ) {} /* #IMPLEMENT */
TgVOID tgRN_Release_Material( TgATTRIBUTE_UNUSED TgRN_MATERIAL_ID_C ARG0 ) {} /* #IMPLEMENT */
TgRN_MATERIAL_ID tgRN_Hash_Instance_Material( TgATTRIBUTE_UNUSED TgUINT_MAX_C ARG0, TgATTRIBUTE_UNUSED ETgKN_GPU_DEFAULT_INPUT_LAYOUT_C ARG1 ) { return KTgRN_MATERIAL_ID__INVALID; } /* #IMPLEMENT */
TgBOOL tgRN_Material__Is_Opaque( TgATTRIBUTE_UNUSED TgRN_MATERIAL_ID_C ARG0 ) { return true; } /* #IMPLEMENT */
TgVOID tgRN_DBG_Wireframe_BoxAA( TgATTRIBUTE_UNUSED TgCOLOUR32_C ARG0, TgATTRIBUTE_UNUSED TgVEC_F32_04_1 ARG1, TgATTRIBUTE_UNUSED TgVEC_F32_04_1 ARG2 ) {} /* #IMPLEMENT */
TgVOID tgRN_DBG_Sphere( TgATTRIBUTE_UNUSED TgCOLOUR32_C ARG0, TgATTRIBUTE_UNUSED TgVEC_F32_04_1 ARG1, TgATTRIBUTE_UNUSED TgFLOAT32_C ARG2 ) {} /* #IMPLEMENT */
TgVOID tgRN_DBG_Line( TgATTRIBUTE_UNUSED TgVEC_F32_04_1 ARG0, TgATTRIBUTE_UNUSED TgCOLOUR32_C ARG1, TgATTRIBUTE_UNUSED TgVEC_F32_04_1 ARG2, TgATTRIBUTE_UNUSED TgCOLOUR32_C ARG3 ) {} /* #IMPLEMENT */
TgVOID tgRN_DBG_Axes( TgATTRIBUTE_UNUSED TgVEC_F32_04_3_CPCU ARG0, TgATTRIBUTE_UNUSED TgFLOAT32_C ARG1 ) {} /* #IMPLEMENT */
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
