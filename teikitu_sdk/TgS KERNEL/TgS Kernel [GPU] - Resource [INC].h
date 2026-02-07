/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Resource [INC].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

    /** Resource Types
        VS = Vertex Shader
        TCS = Tesselation Control Shader
        TES = Tesselation Evaluation Shader
        GS = Geometry Shader
        TS = Task Shader
        MS = Mesh Shader
        FS = Fragment Shader
        CS = Computer Shader
        IL = Input Layout
        VT = Vertex Declaration
        TX_CBE = Texture, Cube
        TX_VOL = Texture, Volume
        TX_IMG = Texture, 2D
        IX = Index Stream
        VX = Vertex Stream
        SH = Shader
        TX = Texture
        KB = Constant Buffers
        BF = Buffer
        PSO = Pipeline State Objects
        ?? = Texture Samplers */

    #define T(A,...) TgMACRO_CONCAT3V(A,TgMACRO_BUILD_RESOURCE_TYPE,__VA_ARGS__)
#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__ERROR
    #define T_USZ(A,...) TgMACRO_CONCAT3V_USZ(A,TgMACRO_BUILD_RESOURCE_TYPE,__VA_ARGS__)
#endif

    #define MACRO_BUILD_SHADER

    #define TgMACRO_BUILD_RESOURCE_TYPE VS
        #include __PARENT_FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #define TgMACRO_BUILD_RESOURCE_TYPE TCS
        #include __PARENT_FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #define TgMACRO_BUILD_RESOURCE_TYPE TES
        #include __PARENT_FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #define TgMACRO_BUILD_RESOURCE_TYPE GS
        #include __PARENT_FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #define TgMACRO_BUILD_RESOURCE_TYPE TS
        #include __PARENT_FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #define TgMACRO_BUILD_RESOURCE_TYPE MS
        #include __PARENT_FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #define TgMACRO_BUILD_RESOURCE_TYPE FS
        #include __PARENT_FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #define TgMACRO_BUILD_RESOURCE_TYPE CS
        #include __PARENT_FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #undef MACRO_BUILD_SHADER

    #define MACRO_BUILD_TEXTURE

    #define TgMACRO_BUILD_RESOURCE_TYPE TX_IMG
        #include __PARENT_FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #define TgMACRO_BUILD_RESOURCE_TYPE TX_CBE
        #include __PARENT_FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #define TgMACRO_BUILD_RESOURCE_TYPE TX_VOL
        #include __PARENT_FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #undef MACRO_BUILD_TEXTURE

#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__ERROR
    #undef T_USZ
#endif
    #undef T

    #define TGS_KERNEL_RESOURCE_GPU_H
