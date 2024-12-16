/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (METAL) Effect [Unit Test].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */


/* ---- GPU - Unit Test ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgVOID
tgUnit_Test__FX__Create_Resources(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgUINT_E32 uiNodeMask );

TgEXTN TgRESULT
tgUnit_Test__FX__Render(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgRSIZE_C uiTest_Level );

TgEXTN TgRESULT
tgUnit_Test__FX__Release_Resources(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP );

TgEXTN TgVOID
tgUnit_Test__FX__Setup_Scene_Constant_Buffer(
    STg2_KN_GPU_Render_Buffer_CPCU psRTBuffer );




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgUnit_Test__FX__Create_Resources ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgUnit_Test__FX__Create_Resources( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgUINT_E32 uiNodeMask )
{
    (void)tiCXT_EXEC;
    (void)tiCXT_SWAP;
    (void)uiNodeMask;
}


/* ---- tgUnit_Test__FX__Render -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__FX__Render( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgRSIZE_C uiTest_Level )
{
    (void)tiCXT_EXEC;
    (void)tiCXT_SWAP;
    (void)tiCXT_WORK;
    (void)uiTest_Level;
    return (KTgS_OK);
}


/* ---- tgUnit_Test__FX__Release_Resources --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__FX__Release_Resources( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    (void)tiCXT_EXEC;
    (void)tiCXT_SWAP;
    return (KTgS_OK);
}
