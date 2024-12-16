/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Data [GPU].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPI - API - External Functions and Objects ------------------------------------------------------------------------------------------------------------------------------- */

HRESULT                                     (__stdcall *g_pfnDXGICreateDXGIFactory)( UINT, REFIID, TgVOID_PP ) = nullptr;

HRESULT                                     (__stdcall *g_pfnDXGIGetDebugInterface1)( UINT, REFIID, TgVOID_PP ) = nullptr;

HRESULT                                     (__stdcall* g_pfnD3D12SerializeVersionedRootSignature )( D3D12_VER_ROOT_SIG_DESC_CP, ID3DBlob_PP, ID3DBlob_PP ) = nullptr;
HRESULT                                     (__stdcall* g_pfnD3D12CreateVersionedRootSignatureDeserializer )( TgVOID_CP, TgRSIZE, REFIID, TgVOID_PP ) = nullptr;
HRESULT                                     (__stdcall* g_pfnD3D12CreateDevice)( IUnknown*, D3D_FEATURE_LEVEL, REFIID, TgVOID_PP ) = nullptr;
HRESULT                                     (__stdcall* g_pfnD3D12GetDebugInterface)( REFIID, TgVOID_PP ) = nullptr;

TgVOID                                      ( __stdcall *g_pfnPIXBeginEventOnCommandList )( ID3D12GraphicsCommandList_P, UINT64, TgCHAR_NC_CP ) = nullptr;
TgVOID                                      ( __stdcall *g_pfnPIXEndEventOnCommandList )( ID3D12GraphicsCommandList_P ) = nullptr;
TgVOID                                      ( __stdcall *g_pfnPIXSetMarkerOnCommandList )( ID3D12GraphicsCommandList_P, UINT64, TgCHAR_NC_CP ) = nullptr;

IDXGIFactory7                               *g_pDXGIFactory;


/* ---- GPU - Contexts ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

STg2_KN_GPU_EXT_CXT_HOST                    g_sKN_GPU_EXT_CXT_HOST;
STg2_KN_GPU_EXT_CXT_DEVC                    g_asKN_GPU_EXT_CXT_DEVC[KTgKN_GPU_MAX_DEVC_CONTEXT];
STg2_KN_GPU_EXT_CXT_EXEC                    g_asKN_GPU_EXT_CXT_EXEC[KTgKN_GPU_MAX_EXEC_CONTEXT];
STg2_KN_GPU_EXT_CXT_SWAP                    g_asKN_GPU_EXT_CXT_SWAP[KTgKN_GPU_MAX_SWAP_CONTEXT];


/* ---- GPU - Resource - Defaults ------------------------------------------------------------------------------------------------------------------------------------------------ */

D3D12_BLEND_DESC const                      g_asKN_GPU_EXT_Default_Blend_State[ETgKN_GPU_DEFAULT_BLEND_STATE_COUNT] = {
                                                {
                                                    .AlphaToCoverageEnable = FALSE,
                                                    .IndependentBlendEnable = FALSE,
                                                    .RenderTarget = { 
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, } },
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA */
                                                    .AlphaToCoverageEnable = FALSE,
                                                    .IndependentBlendEnable = FALSE,
                                                    .RenderTarget = { 
                                                        {  TRUE,FALSE, D3D12_BLEND_SRC_ALPHA, D3D12_BLEND_INV_SRC_ALPHA, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, } },
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA_PREMULT */
                                                    .AlphaToCoverageEnable = FALSE,
                                                    .IndependentBlendEnable = FALSE,
                                                    .RenderTarget = { 
                                                        {  TRUE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_INV_SRC_ALPHA,  D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, },
                                                        { FALSE,FALSE, D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD, D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE, } },
                                                },
                                            };

D3D12_RASTERIZER_DESC const                 g_asKN_GPU_EXT_Default_Rasterizer_State[ETgKN_GPU_DEFAULT_RASTERIZER_STATE_COUNT] = {
                                                {
                                                    .FillMode = D3D12_FILL_MODE_SOLID,
                                                    .CullMode = D3D12_CULL_MODE_BACK,
                                                    .FrontCounterClockwise = FALSE,
                                                    .DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
                                                    .DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
                                                    .SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
                                                    .DepthClipEnable = TRUE,
                                                    .MultisampleEnable = FALSE,
                                                    .AntialiasedLineEnable = FALSE,
                                                    .ForcedSampleCount = 0,
                                                    .ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF
                                                },

                                                {
                                                    .FillMode = D3D12_FILL_MODE_SOLID,
                                                    .CullMode = D3D12_CULL_MODE_BACK,
                                                    .FrontCounterClockwise = FALSE,
                                                    .DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
                                                    .DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
                                                    .SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
                                                    .DepthClipEnable = TRUE,
                                                    .MultisampleEnable = FALSE,
                                                    .AntialiasedLineEnable = TRUE,
                                                    .ForcedSampleCount = 0,
                                                    .ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF
                                                },

                                                {
                                                    .FillMode = D3D12_FILL_MODE_WIREFRAME,
                                                    .CullMode = D3D12_CULL_MODE_BACK,
                                                    .FrontCounterClockwise = FALSE,
                                                    .DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
                                                    .DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
                                                    .SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
                                                    .DepthClipEnable = TRUE,
                                                    .MultisampleEnable = FALSE,
                                                    .AntialiasedLineEnable = FALSE,
                                                    .ForcedSampleCount = 0,
                                                    .ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF
                                                },
                                            };

D3D12_DEPTH_STENCIL_DESC const              g_asKN_GPU_EXT_Default_Depth_Stencil_State[ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_COUNT] = {
                                                {   /* ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_NONE */
                                                    .DepthEnable = FALSE,
                                                    .DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL,
                                                    .DepthFunc = D3D12_COMPARISON_FUNC_LESS,
                                                    .StencilEnable = FALSE,
                                                    .StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK,
                                                    .StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK,
                                                    .FrontFace = { D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS },
                                                    .BackFace = { D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS }
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH */
                                                    .DepthEnable = TRUE,
                                                    .DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL,
                                                    .DepthFunc = D3D12_COMPARISON_FUNC_LESS,
                                                    .StencilEnable = FALSE,
                                                    .StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK,
                                                    .StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK,
                                                    .FrontFace = { D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS },
                                                    .BackFace = { D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS }
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_STENCIL */
                                                    .DepthEnable = TRUE,
                                                    .DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL,
                                                    .DepthFunc = D3D12_COMPARISON_FUNC_LESS,
                                                    .StencilEnable = TRUE,
                                                    .StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK,
                                                    .StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK,
                                                    .FrontFace = { D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS },
                                                    .BackFace = { D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS }
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT */
                                                    .DepthEnable = FALSE,
                                                    .DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO,
                                                    .DepthFunc = D3D12_COMPARISON_FUNC_LESS,
                                                    .StencilEnable = FALSE,
                                                    .StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK,
                                                    .StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK,
                                                    .FrontFace = { D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS },
                                                    .BackFace = { D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS }
                                                },

                                            };

STg2_KN_GPU_PSO_DESC                        g_asKN_GPU_STD_PSO_DESC[ETgKN_GPU_DEFAULT_PSO_COUNT] = {

                                                {   /* ETgKN_GPU_DEFAULT_PSO_PARTICLE_00 */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_00,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT,
                                                    .m_uszName = u8"PARTICLE 00",
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_PSO_PARTICLE_01 */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_01,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT,
                                                    .m_uszName = u8"PARTICLE 01",
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_PSO_DEBUG_UI */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_UI,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_NONE,
                                                    .m_uszName = u8"DEBUG UI",
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_PSO_DEBUG_UI_WITH_GAMMA */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_UI,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_NONE,
                                                    .m_uszName = u8"DEBUG UI GAMMA",
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_PSO_DEBUG_TEXT */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_INSTANCE_VERTEX_UI_TEXT,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_NONE,
                                                    .m_uszName = u8"DEBUG UI TEXT",
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_PSO_DEBUG_LINE */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_LINE,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_LINE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID_LINE_AA,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_NONE,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT,
                                                    .m_uszName = u8"DEBUG LINE",
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_00 */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_GEOM_00,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT,
                                                    .m_uszName = u8"DEBUG GEOM 00",
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_01 */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_GEOM_01,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT,
                                                    .m_uszName = u8"DEBUG GEOM 01",
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_01 WITH GAMMA */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_GEOM_01,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT,
                                                    .m_uszName = u8"DEBUG GEOM 01 WITH GAMMA",
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_02 */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_GEOM_02,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT,
                                                    .m_uszName = u8"DEBUG GEOM 02",
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_02_INSTANCE */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_INSTANCE_VERTEX_GEOM_02,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT,
                                                    .m_uszName = u8"DEBUG GEOM 02 INSTANCE",
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_03 */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_GEOM_03,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT,
                                                    .m_uszName = u8"DEBUG GEOM 03",
                                                },

                                                {   /* ETgKN_GPU_DEFAULT_PSO_UNIT_TEST_SCENE */
                                                    .m_enRoot_Signature = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_UNIT_TEST,
                                                    .m_enInput_Layout = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_INSTANCE_VERTEX_GEOM_02,
                                                    .m_enTopology_Type = ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
                                                    .m_enRasterizer_State = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_DEFAULT_BLEND_STATE_NONE,
                                                    .m_enDepth_State = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uszName = u8"UNIT TEST SCENE",
                                                },
                                            };


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_Query_Fixed_Memory ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgKN_GPU_EXT_Query_Fixed_Memory( TgVOID )
{
    return ( 0
             + sizeof( g_pfnDXGICreateDXGIFactory )
             + sizeof( g_pfnDXGIGetDebugInterface1 )
             + sizeof( g_pfnD3D12SerializeVersionedRootSignature )
             + sizeof( g_pfnD3D12CreateVersionedRootSignatureDeserializer )
             + sizeof( g_pfnD3D12CreateDevice )
             + sizeof( g_pfnD3D12GetDebugInterface )
             + sizeof( g_pDXGIFactory )
             + sizeof( g_sKN_GPU_EXT_CXT_HOST )
             + sizeof( g_asKN_GPU_EXT_CXT_DEVC )
             + sizeof( g_asKN_GPU_EXT_CXT_EXEC )
             + sizeof( g_asKN_GPU_EXT_CXT_SWAP )
    );
}





/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Validation                                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_UNKNOWN == (TgSINT_E32)DXGI_FORMAT_UNKNOWN, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32A32_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R32G32B32A32_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32A32_FLOAT == (TgSINT_E32)DXGI_FORMAT_R32G32B32A32_FLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32A32_UINT == (TgSINT_E32)DXGI_FORMAT_R32G32B32A32_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SINT == (TgSINT_E32)DXGI_FORMAT_R32G32B32A32_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R32G32B32_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32_FLOAT == (TgSINT_E32)DXGI_FORMAT_R32G32B32_FLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32_UINT == (TgSINT_E32)DXGI_FORMAT_R32G32B32_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32_SINT == (TgSINT_E32)DXGI_FORMAT_R32G32B32_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R16G16B16A16_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_FLOAT == (TgSINT_E32)DXGI_FORMAT_R16G16B16A16_FLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_UNORM == (TgSINT_E32)DXGI_FORMAT_R16G16B16A16_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_UINT == (TgSINT_E32)DXGI_FORMAT_R16G16B16A16_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SNORM == (TgSINT_E32)DXGI_FORMAT_R16G16B16A16_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SINT == (TgSINT_E32)DXGI_FORMAT_R16G16B16A16_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R32G32_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32_FLOAT == (TgSINT_E32)DXGI_FORMAT_R32G32_FLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32_UINT == (TgSINT_E32)DXGI_FORMAT_R32G32_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32_SINT == (TgSINT_E32)DXGI_FORMAT_R32G32_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G8X24_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R32G8X24_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_D32_FLOAT_S8X24_UINT == (TgSINT_E32)DXGI_FORMAT_D32_FLOAT_S8X24_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32_FLOAT_X8X24_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_X32_TYPELESS_G8X24_UINT == (TgSINT_E32)DXGI_FORMAT_X32_TYPELESS_G8X24_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R10G10B10A2_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R10G10B10A2_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UNORM == (TgSINT_E32)DXGI_FORMAT_R10G10B10A2_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UINT == (TgSINT_E32)DXGI_FORMAT_R10G10B10A2_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R11G11B10_FLOAT == (TgSINT_E32)DXGI_FORMAT_R11G11B10_FLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R8G8B8A8_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM == (TgSINT_E32)DXGI_FORMAT_R8G8B8A8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM_SRGB == (TgSINT_E32)DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UINT == (TgSINT_E32)DXGI_FORMAT_R8G8B8A8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SNORM == (TgSINT_E32)DXGI_FORMAT_R8G8B8A8_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SINT == (TgSINT_E32)DXGI_FORMAT_R8G8B8A8_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R16G16_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_FLOAT == (TgSINT_E32)DXGI_FORMAT_R16G16_FLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_UNORM == (TgSINT_E32)DXGI_FORMAT_R16G16_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_UINT == (TgSINT_E32)DXGI_FORMAT_R16G16_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_SNORM == (TgSINT_E32)DXGI_FORMAT_R16G16_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_SINT == (TgSINT_E32)DXGI_FORMAT_R16G16_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R32_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_D32_FLOAT == (TgSINT_E32)DXGI_FORMAT_D32_FLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32_FLOAT == (TgSINT_E32)DXGI_FORMAT_R32_FLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32_UINT == (TgSINT_E32)DXGI_FORMAT_R32_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32_SINT == (TgSINT_E32)DXGI_FORMAT_R32_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R24G8_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R24G8_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_D24_UNORM_S8_UINT == (TgSINT_E32)DXGI_FORMAT_D24_UNORM_S8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R24_UNORM_X8_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R24_UNORM_X8_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_X24_TYPELESS_G8_UINT == (TgSINT_E32)DXGI_FORMAT_X24_TYPELESS_G8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R8G8_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_UNORM == (TgSINT_E32)DXGI_FORMAT_R8G8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_UINT == (TgSINT_E32)DXGI_FORMAT_R8G8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_SNORM == (TgSINT_E32)DXGI_FORMAT_R8G8_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_SINT == (TgSINT_E32)DXGI_FORMAT_R8G8_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R16_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_FLOAT == (TgSINT_E32)DXGI_FORMAT_R16_FLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_D16_UNORM == (TgSINT_E32)DXGI_FORMAT_D16_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_UNORM == (TgSINT_E32)DXGI_FORMAT_R16_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_UINT == (TgSINT_E32)DXGI_FORMAT_R16_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_SNORM == (TgSINT_E32)DXGI_FORMAT_R16_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_SINT == (TgSINT_E32)DXGI_FORMAT_R16_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8_TYPELESS == (TgSINT_E32)DXGI_FORMAT_R8_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8_UNORM == (TgSINT_E32)DXGI_FORMAT_R8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8_UINT == (TgSINT_E32)DXGI_FORMAT_R8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8_SNORM == (TgSINT_E32)DXGI_FORMAT_R8_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8_SINT == (TgSINT_E32)DXGI_FORMAT_R8_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A8_UNORM == (TgSINT_E32)DXGI_FORMAT_A8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R1_UNORM == (TgSINT_E32)DXGI_FORMAT_R1_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R9G9B9E5_SHAREDEXP == (TgSINT_E32)DXGI_FORMAT_R9G9B9E5_SHAREDEXP, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_B8G8_UNORM == (TgSINT_E32)DXGI_FORMAT_R8G8_B8G8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_G8R8_G8B8_UNORM == (TgSINT_E32)DXGI_FORMAT_G8R8_G8B8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC1_TYPELESS == (TgSINT_E32)DXGI_FORMAT_BC1_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC1_UNORM == (TgSINT_E32)DXGI_FORMAT_BC1_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC1_UNORM_SRGB == (TgSINT_E32)DXGI_FORMAT_BC1_UNORM_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC2_TYPELESS == (TgSINT_E32)DXGI_FORMAT_BC2_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC2_UNORM == (TgSINT_E32)DXGI_FORMAT_BC2_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC2_UNORM_SRGB == (TgSINT_E32)DXGI_FORMAT_BC2_UNORM_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC3_TYPELESS == (TgSINT_E32)DXGI_FORMAT_BC3_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC3_UNORM == (TgSINT_E32)DXGI_FORMAT_BC3_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC3_UNORM_SRGB == (TgSINT_E32)DXGI_FORMAT_BC3_UNORM_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC4_TYPELESS == (TgSINT_E32)DXGI_FORMAT_BC4_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC4_UNORM == (TgSINT_E32)DXGI_FORMAT_BC4_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC4_SNORM == (TgSINT_E32)DXGI_FORMAT_BC4_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC5_TYPELESS == (TgSINT_E32)DXGI_FORMAT_BC5_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC5_UNORM == (TgSINT_E32)DXGI_FORMAT_BC5_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC5_SNORM == (TgSINT_E32)DXGI_FORMAT_BC5_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B5G6R5_UNORM == (TgSINT_E32)DXGI_FORMAT_B5G6R5_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B5G5R5A1_UNORM == (TgSINT_E32)DXGI_FORMAT_B5G5R5A1_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM == (TgSINT_E32)DXGI_FORMAT_B8G8R8A8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8X8_UNORM == (TgSINT_E32)DXGI_FORMAT_B8G8R8X8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R10G10B10_XR_BIAS_A2_UNORM == (TgSINT_E32)DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8A8_TYPELESS == (TgSINT_E32)DXGI_FORMAT_B8G8R8A8_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM_SRGB == (TgSINT_E32)DXGI_FORMAT_B8G8R8A8_UNORM_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8X8_TYPELESS == (TgSINT_E32)DXGI_FORMAT_B8G8R8X8_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8X8_UNORM_SRGB == (TgSINT_E32)DXGI_FORMAT_B8G8R8X8_UNORM_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC6H_TYPELESS == (TgSINT_E32)DXGI_FORMAT_BC6H_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC6H_UF16 == (TgSINT_E32)DXGI_FORMAT_BC6H_UF16, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC6H_SF16 == (TgSINT_E32)DXGI_FORMAT_BC6H_SF16, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC7_TYPELESS == (TgSINT_E32)DXGI_FORMAT_BC7_TYPELESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC7_UNORM == (TgSINT_E32)DXGI_FORMAT_BC7_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC7_UNORM_SRGB == (TgSINT_E32)DXGI_FORMAT_BC7_UNORM_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_AYUV == (TgSINT_E32)DXGI_FORMAT_AYUV, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_Y410 == (TgSINT_E32)DXGI_FORMAT_Y410, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_Y416 == (TgSINT_E32)DXGI_FORMAT_Y416, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_NV12 == (TgSINT_E32)DXGI_FORMAT_NV12, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_P010 == (TgSINT_E32)DXGI_FORMAT_P010, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_P016 == (TgSINT_E32)DXGI_FORMAT_P016, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_420_OPAQUE == (TgSINT_E32)DXGI_FORMAT_420_OPAQUE, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_YUY2 == (TgSINT_E32)DXGI_FORMAT_YUY2, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_Y210 == (TgSINT_E32)DXGI_FORMAT_Y210, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_Y216 == (TgSINT_E32)DXGI_FORMAT_Y216, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_NV11 == (TgSINT_E32)DXGI_FORMAT_NV11, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_AI44 == (TgSINT_E32)DXGI_FORMAT_AI44, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_IA44 == (TgSINT_E32)DXGI_FORMAT_IA44, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_P8 == (TgSINT_E32)DXGI_FORMAT_P8, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A8P8 == (TgSINT_E32)DXGI_FORMAT_A8P8, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B4G4R4A4_UNORM == (TgSINT_E32)DXGI_FORMAT_B4G4R4A4_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_P208 == (TgSINT_E32)DXGI_FORMAT_P208, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_V208 == (TgSINT_E32)DXGI_FORMAT_V208, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_V408 == (TgSINT_E32)DXGI_FORMAT_V408, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE == (TgSINT_E32)DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE == (TgSINT_E32)DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE, 0 );

TgCOMPILER_ASSERT( D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT <= 32, 0 );
TgCOMPILER_ASSERT( D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT >= KTgKN_GPU_MS__MAX, 0 );

TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_TOPOLOGY_TYPE_UNDEFINED == (TgSINT_E32)D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_TOPOLOGY_TYPE_POINT == (TgSINT_E32)D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_TOPOLOGY_TYPE_LINE == (TgSINT_E32)D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE == (TgSINT_E32)D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_TOPOLOGY_TYPE_PATCH == (TgSINT_E32)D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH, 0 );

TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_COMMAND_NONE == (TgSINT_E32)D3D12_COMMAND_LIST_TYPE_NONE, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_COMMAND_DIRECT == (TgSINT_E32)D3D12_COMMAND_LIST_TYPE_DIRECT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_COMMAND_BUNDLE == (TgSINT_E32)D3D12_COMMAND_LIST_TYPE_BUNDLE, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_COMMAND_COMPUTE == (TgSINT_E32)D3D12_COMMAND_LIST_TYPE_COMPUTE, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_COMMAND_COPY == (TgSINT_E32)D3D12_COMMAND_LIST_TYPE_COPY, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_COMMAND_VIDEO_DECODE == (TgSINT_E32)D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_COMMAND_VIDEO_PROCESS == (TgSINT_E32)D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_COMMAND_VIDEO_ENCODE == (TgSINT_E32)D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE, 0 );
