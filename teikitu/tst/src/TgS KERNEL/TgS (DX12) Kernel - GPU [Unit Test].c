/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Unit Test [GPU].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#include "TgS KERNEL/TgS (DX12) Kernel [GPU].h"
#include "TgS KERNEL/TgS (DX12) Kernel [GPU] - Debug.inl"


/* ---- GPU - Unit Test ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgVOID
tgUnit_Test__KN_GPU__Create_Resources(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgUINT_E32 uiNodeMask );

TgEXTN TgRESULT
tgUnit_Test__KN_GPU__Render(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgRSIZE_C uiTest_Level );

TgEXTN TgRESULT
tgUnit_Test__KN_GPU__Release_Resources(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP );




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

typedef struct
{
    TgVEC_S_F32_04_4                    m_mW2C, m_mC2S;
    TgVEC_S_F32_04_1                    scene_light_ambient;
    struct Light_Data
    {
        TgVEC_S_F32_04_1                    origin_and_range;
        TgVEC_S_F32_04_1                    colour;
    }                                   scene_lights[8];
    UINT                                scene_num_lights;
} SceneConstantBuffer;
static SceneConstantBuffer s_sSceneConstantBuffer;
static const UINT c_alignedSceneConstantBufferSize = (sizeof( SceneConstantBuffer ) + 255) & ~255ULL;

/* These buffers are defined in the shared file with the engine. */
static STg2_KN_GPU_HLSL_CB_Debug_Model_Instance s_sModelConstantBufferInstance;
static const UINT c_alignedModelConstantBufferInstanceSize = (sizeof( STg2_KN_GPU_HLSL_CB_Debug_Model_Instance ) + 255) & ~255ULL;
#if TgCOMPILE__RENDER_DEBUG_OUTPUT
static STg2_KN_GPU_HLSL_CB_Debug_Model s_sModelConstantBuffer;
static STg2_KN_GPU_HLSL_CB_Debug_Line s_sLineConstantBuffer;
#endif
static const UINT c_alignedModelConstantBufferSize = (sizeof( STg2_KN_GPU_HLSL_CB_Debug_Model ) + 255) & ~255ULL;
static STg2_KN_GPU_HLSL_CB_Debug_UI s_sUIConstantBuffer;
static const UINT c_alignedUIConstantBufferSize = (sizeof( STg2_KN_GPU_HLSL_CB_Debug_UI ) + 255) & ~255ULL;

TgTYPE_STRUCT(STg2_UT_KN_GPU_Exec_Resources,)
{
    ID3D12Resource_P                    m_psDX12_Vertex_Buffer__UI;
    ID3D12Resource_P                    m_psDX12_Vertex_Buffer__Gradient;
    ID3D12Resource_P                    m_psDX12_Vertex_Buffer__Cube_00;
    ID3D12Resource_P                    m_psDX12_Vertex_Buffer__Cube_02;

    ID3D12Resource_P                    m_psDX12_Index_Buffer__Cube_and_Gradient;

    TgRSIZE                             m_uiRefCount;
};

TgTYPE_STRUCT(STg2_UT_KN_GPU_Swap_Resources,)
{
    ID3D12Resource_P                    m_psDX12_CBV_Gradient_SDR;
    ID3D12Resource_P                    m_psDX12_CBV_Gradient_HDR;
    ID3D12Resource_P                    m_psDX12_CBV_Scene;
    ID3D12Resource_P                    m_psDX12_CBV_Model_00;
    ID3D12Resource_P                    m_psDX12_CBV_Model_01;
    ID3D12Resource_P                    m_psDX12_CBV_Instance_Model;

    TgRSIZE                             m_uiRefCount;
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Clear the screen using the clear screen API. Colour correction will need to be done on the CPU. */
static TgRESULT
tgUnit_Test__KN_GPU__Render_0(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK );

/** @brief Clear the screen using a fullscreen quad, matching the previous clear colours. This will invoke the pixel shader for colour correction instead of CPU correction. */
static TgRESULT
tgUnit_Test__KN_GPU__Render_1(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK );

/** @brief Clear the screen using a fullscreen quad. This will use the colour reference image. */
static TgRESULT
tgUnit_Test__KN_GPU__Render_2(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK );

/** @brief Render 2D Geometry, including SDR, HDR Gradients. */
static TgRESULT
tgUnit_Test__KN_GPU__Render_3(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK );

/** @brief Render 3D Geometry. */
static TgRESULT
tgUnit_Test__KN_GPU__Render_4(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK );

static TgRESULT
tgUnit_Test__KN_GPU__Render_5(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK );

static TgVOID
tgUnit_Test__KN_GPU__Setup_Scene_Constant_Buffer(
    STg2_KN_GPU_HLSL_Output_DESC_CPCU psOutput_DESC, STg2_KN_GPU_Render_Buffer_CPCU psRTBuffer );

static STg2_UT_KN_GPU_Exec_Resources s_saGPU_Exec_Resources[KTgKN_GPU_MAX_EXEC_CONTEXT];
static STg2_UT_KN_GPU_Swap_Resources s_saGPU_Swap_Resources[KTgKN_GPU_MAX_SWAP_CONTEXT];

/* Single quad used for clearing the render target. */
static STg2_KN_GPU_Vertex_UI sVertex_UI[] = {
    { { { 0.0F, 0.0F } }, { { 0.0f, 1.0f } }, { { 1.0f, 1.0f, 1.0f, 1.0f } } }, { { { 0.0F, 1.0F } }, { { 0.0f, 0.0f } }, { { 1.0f, 1.0f, 1.0f, 1.0f } } },
    { { { 1.0F, 0.0F } }, { { 1.0f, 1.0f } }, { { 1.0f, 1.0f, 1.0f, 1.0f } } }, { { { 1.0F, 1.0F } }, { { 1.0f, 0.0f } }, { { 1.0f, 1.0f, 1.0f, 1.0f } } },
};

/** Single quad used for rendering a grey scale, This data copied from the Microsoft DirectX Graphics Samples (D3D12HDR), under the MIT License. */
static STg2_KN_GPU_Vertex_UI sVertex_Gradient[] = {
    { { { 0.0F, 0.0F } }, { { 0.0f, 1.0f } }, { { 0.0f, 0.0f, 0.0f, 1.0f } } }, { { { 0.0F, 1.0F } }, { { 0.0f, 0.0f } }, { { 0.0f, 0.0f, 0.0f, 1.0f } } },
    { { { 1.0F, 0.0F } }, { { 1.0f, 1.0f } }, { { 1.0f, 1.0f, 1.0f, 1.0f } } }, { { { 1.0F, 1.0F } }, { { 1.0f, 0.0f } }, { { 1.0f, 1.0f, 1.0f, 1.0f } } },
};
static unsigned short sIndex_Gradient[] = { 0, 1, 2, 1, 3, 2, 2, 3, 4, 3, 5, 4, 4, 5, 6, 5, 7, 6, 6, 7, 8, 7, 9, 8 };

/* Indexed Cube, where vertices are shared. */
static const STg2_KN_GPU_Vertex_Geom_00 sVertex_Cube[] = {
    { { {  0.5f, -0.5f,  0.5f, 1.0f } } }, { { {  0.5f, -0.5f, -0.5f, 1.0f } } },
    { { {  0.5f,  0.5f, -0.5f, 1.0f } } }, { { {  0.5f,  0.5f,  0.5f, 1.0f } } },
    { { { -0.5f, -0.5f,  0.5f, 1.0f } } }, { { { -0.5f, -0.5f, -0.5f, 1.0f } } },
    { { { -0.5f,  0.5f, -0.5f, 1.0f } } }, { { { -0.5f,  0.5f,  0.5f, 1.0f } } },
};
static unsigned short sIndex_Cube[] = { 4,0,3,  4,3,7,  0,1,2,  0,2,3,  1,5,6,  1,6,2,  5,4,7,  5,7,6,  7,3,2,  7,2,6,  0,5,1,  0,4,5 };

/* Triangle List Cube, where vertices are not shared, allowing for unique normals for each face. */
static STg2_KN_GPU_Vertex_Geom_02 sVertex_List_Cube[] = {
    {{{-0.5f,-0.5f,-0.5f, 1.f}},{{-1.0f, 0.0f, 0.0f, 0.f}}}, {{{-0.5f,-0.5f, 0.5f, 1.f}},{{-1.0f, 0.0f, 0.0f, 0.f}}}, {{{-0.5f, 0.5f, 0.5f, 1.f}},{{-1.0f, 0.0f, 0.0f, 0.f}}},
    {{{ 0.5f, 0.5f,-0.5f, 1.f}},{{ 0.0f, 0.0f,-1.0f, 0.f}}}, {{{-0.5f,-0.5f,-0.5f, 1.f}},{{ 0.0f, 0.0f,-1.0f, 0.f}}}, {{{-0.5f, 0.5f,-0.5f, 1.f}},{{ 0.0f, 0.0f,-1.0f, 0.f}}},
    {{{ 0.5f,-0.5f, 0.5f, 1.f}},{{ 0.0f,-1.0f, 0.0f, 0.f}}}, {{{-0.5f,-0.5f,-0.5f, 1.f}},{{ 0.0f,-1.0f, 0.0f, 0.f}}}, {{{ 0.5f,-0.5f,-0.5f, 1.f}},{{ 0.0f,-1.0f, 0.0f, 0.f}}},
    {{{ 0.5f, 0.5f,-0.5f, 1.f}},{{ 0.0f, 0.0f,-1.0f, 0.f}}}, {{{ 0.5f,-0.5f,-0.5f, 1.f}},{{ 0.0f, 0.0f,-1.0f, 0.f}}}, {{{-0.5f,-0.5f,-0.5f, 1.f}},{{ 0.0f, 0.0f,-1.0f, 0.f}}},
    {{{-0.5f,-0.5f,-0.5f, 1.f}},{{-1.0f, 0.0f, 0.0f, 0.f}}}, {{{-0.5f, 0.5f, 0.5f, 1.f}},{{-1.0f, 0.0f, 0.0f, 0.f}}}, {{{-0.5f, 0.5f,-0.5f, 1.f}},{{-1.0f, 0.0f, 0.0f, 0.f}}},
    {{{ 0.5f,-0.5f, 0.5f, 1.f}},{{ 0.0f,-1.0f, 0.0f, 0.f}}}, {{{-0.5f,-0.5f, 0.5f, 1.f}},{{ 0.0f,-1.0f, 0.0f, 0.f}}}, {{{-0.5f,-0.5f,-0.5f, 1.f}},{{ 0.0f,-1.0f, 0.0f, 0.f}}},
    {{{-0.5f, 0.5f, 0.5f, 1.f}},{{ 0.0f, 0.0f, 1.0f, 0.f}}}, {{{-0.5f,-0.5f, 0.5f, 1.f}},{{ 0.0f, 0.0f, 1.0f, 0.f}}}, {{{ 0.5f,-0.5f, 0.5f, 1.f}},{{ 0.0f, 0.0f, 1.0f, 0.f}}},
    {{{ 0.5f, 0.5f, 0.5f, 1.f}},{{ 1.0f, 0.0f, 0.0f, 0.f}}}, {{{ 0.5f,-0.5f,-0.5f, 1.f}},{{ 1.0f, 0.0f, 0.0f, 0.f}}}, {{{ 0.5f, 0.5f,-0.5f, 1.f}},{{ 1.0f, 0.0f, 0.0f, 0.f}}},
    {{{ 0.5f,-0.5f,-0.5f, 1.f}},{{ 1.0f, 0.0f, 0.0f, 0.f}}}, {{{ 0.5f, 0.5f, 0.5f, 1.f}},{{ 1.0f, 0.0f, 0.0f, 0.f}}}, {{{ 0.5f,-0.5f, 0.5f, 1.f}},{{ 1.0f, 0.0f, 0.0f, 0.f}}},
    {{{ 0.5f, 0.5f, 0.5f, 1.f}},{{ 0.0f, 1.0f, 0.0f, 0.f}}}, {{{ 0.5f, 0.5f,-0.5f, 1.f}},{{ 0.0f, 1.0f, 0.0f, 0.f}}}, {{{-0.5f, 0.5f,-0.5f, 1.f}},{{ 0.0f, 1.0f, 0.0f, 0.f}}},
    {{{ 0.5f, 0.5f, 0.5f, 1.f}},{{ 0.0f, 1.0f, 0.0f, 0.f}}}, {{{-0.5f, 0.5f,-0.5f, 1.f}},{{ 0.0f, 1.0f, 0.0f, 0.f}}}, {{{-0.5f, 0.5f, 0.5f, 1.f}},{{ 0.0f, 1.0f, 0.0f, 0.f}}},
    {{{ 0.5f, 0.5f, 0.5f, 1.f}},{{ 0.0f, 0.0f, 1.0f, 0.f}}}, {{{-0.5f, 0.5f, 0.5f, 1.f}},{{ 0.0f, 0.0f, 1.0f, 0.f}}}, {{{ 0.5f,-0.5f, 0.5f, 1.f}},{{ 0.0f, 0.0f, 1.0f, 0.f}}}
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgUnit_Test__KN_GPU__Create_Resources ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgUnit_Test__KN_GPU__Create_Resources( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgUINT_E32 uiNodeMask )
{
    ID3D12Device10_PC                   psDX12_Device = tgKN_GPU_EXT__Execute__Get_DX12_Device( tiCXT_EXEC );
    TgKN_GPU_CXT_WORK_ID                tiCXT_WORK;

    /* Start an execution frame so that we can do the data uploads. */
    tiCXT_WORK = tgKN_GPU_EXT__Execute__Frame_Start( tiCXT_EXEC );

    /// Constant Buffer
    {
        STg2_UT_KN_GPU_Swap_Resources_P     psSwap_Resource = s_saGPU_Swap_Resources + tiCXT_SWAP.m_uiI;
        D3D12_HEAP_PROPERTIES               uploadHeapProperties;
        D3D12_RESOURCE_DESC                 sResource_Desc;

        tgMM_Set_U08_0x00( &uploadHeapProperties, sizeof( uploadHeapProperties ) );
        uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
        uploadHeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        uploadHeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        uploadHeapProperties.CreationNodeMask = uiNodeMask;
        uploadHeapProperties.VisibleNodeMask = uiNodeMask;



        tgMM_Set_U08_0x00( &sResource_Desc, sizeof( sResource_Desc ) );
        sResource_Desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        sResource_Desc.Alignment = 0;
        sResource_Desc.Width = c_alignedSceneConstantBufferSize;
        sResource_Desc.Height = 1;
        sResource_Desc.DepthOrArraySize = 1;
        sResource_Desc.MipLevels = 1;
        sResource_Desc.Format = DXGI_FORMAT_UNKNOWN;
        sResource_Desc.SampleDesc.Count = 1;
        sResource_Desc.SampleDesc.Quality = 0;
        sResource_Desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        sResource_Desc.Flags = D3D12_RESOURCE_FLAG_NONE;

        TgVERIFY(SUCCEEDED(ID3D12Device10_CreateCommittedResource1( psDX12_Device, &uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &sResource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psSwap_Resource->m_psDX12_CBV_Scene )));
        ID3D12Object_SetName(psSwap_Resource->m_psDX12_CBV_Scene,L"Unit Test Resource: Constant Buffer");



        tgMM_Set_U08_0x00( &sResource_Desc, sizeof( sResource_Desc ) );
        sResource_Desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        sResource_Desc.Alignment = 0;
        sResource_Desc.Width = c_alignedModelConstantBufferInstanceSize;
        sResource_Desc.Height = 1;
        sResource_Desc.DepthOrArraySize = 1;
        sResource_Desc.MipLevels = 1;
        sResource_Desc.Format = DXGI_FORMAT_UNKNOWN;
        sResource_Desc.SampleDesc.Count = 1;
        sResource_Desc.SampleDesc.Quality = 0;
        sResource_Desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        sResource_Desc.Flags = D3D12_RESOURCE_FLAG_NONE;

        TgVERIFY(SUCCEEDED(ID3D12Device10_CreateCommittedResource1( psDX12_Device, &uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &sResource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psSwap_Resource->m_psDX12_CBV_Instance_Model )));
        ID3D12Object_SetName(psSwap_Resource->m_psDX12_CBV_Instance_Model,L"Unit Test Resource: Constant Buffer");



        tgMM_Set_U08_0x00( &sResource_Desc, sizeof( sResource_Desc ) );
        sResource_Desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        sResource_Desc.Alignment = 0;
        sResource_Desc.Width = c_alignedModelConstantBufferSize;
        sResource_Desc.Height = 1;
        sResource_Desc.DepthOrArraySize = 1;
        sResource_Desc.MipLevels = 1;
        sResource_Desc.Format = DXGI_FORMAT_UNKNOWN;
        sResource_Desc.SampleDesc.Count = 1;
        sResource_Desc.SampleDesc.Quality = 0;
        sResource_Desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        sResource_Desc.Flags = D3D12_RESOURCE_FLAG_NONE;

        TgVERIFY(SUCCEEDED(ID3D12Device10_CreateCommittedResource1( psDX12_Device, &uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &sResource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psSwap_Resource->m_psDX12_CBV_Model_00 )));
        ID3D12Object_SetName(psSwap_Resource->m_psDX12_CBV_Model_00,L"Unit Test Resource: Constant Buffer");



        TgVERIFY(SUCCEEDED(ID3D12Device10_CreateCommittedResource1( psDX12_Device, &uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &sResource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                                   nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psSwap_Resource->m_psDX12_CBV_Model_01 )));
        ID3D12Object_SetName(psSwap_Resource->m_psDX12_CBV_Model_01,L"Unit Test Resource: Constant Buffer");



        sResource_Desc.Width = c_alignedModelConstantBufferSize;
        TgVERIFY(SUCCEEDED(ID3D12Device10_CreateCommittedResource1( psDX12_Device, &uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &sResource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                                   nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psSwap_Resource->m_psDX12_CBV_Gradient_SDR )));
        ID3D12Object_SetName(psSwap_Resource->m_psDX12_CBV_Gradient_SDR,L"Unit Test Resource: Constant Buffer");



        TgVERIFY(SUCCEEDED(ID3D12Device10_CreateCommittedResource1( psDX12_Device, &uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &sResource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                                   nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psSwap_Resource->m_psDX12_CBV_Gradient_HDR )));
        ID3D12Object_SetName(psSwap_Resource->m_psDX12_CBV_Gradient_HDR,L"Unit Test Resource: Constant Buffer");
    }




    /// Create a Vertex Buffer
    {
        STg2_UT_KN_GPU_Exec_Resources_P     psExec_Resource = s_saGPU_Exec_Resources + tiCXT_EXEC.m_uiI;

        /* Create and upload cube geometry resources to the GPU. */

        UTg2_KN_GPU_CMD                     uCMD;
        ID3D12Resource_P                    psDX12_Vertex_Buffer_Upload__Cube_00;
        ID3D12Resource_P                    psDX12_Vertex_Buffer_Upload__Gradient;
        ID3D12Resource_P                    psDX12_Vertex_Buffer_Upload__Cube_02;
        ID3D12Resource_P                    psDX12_Vertex_Buffer_Upload__UI;
        ID3D12Resource_P                    psDX12_Index_Buffer_Upload__Geom_and_Gradient;

        D3D12_HEAP_PROPERTIES               sDX12_Default_Heap_Properties;
        D3D12_HEAP_PROPERTIES               sDX12_Upload_Heap_Properties;
        D3D12_RESOURCE_DESC                 sDX12_Resource_Desc;
        D3D12_RESOURCE_BARRIER              sDX12_ResourceBarrier;
        D3D12_SUBRESOURCE_DATA              sDX12_SubResource_Data;
        D3D12_RANGE                         sDX12_Range;

        HRESULT                             iRet;
        TgUINT_E08_P                        puiMapped_Upload;

        if (0 != psExec_Resource->m_uiRefCount)
        {
            ++psExec_Resource->m_uiRefCount;
            tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
            return;
        };

        ++psExec_Resource->m_uiRefCount;

        /* Create the vertex buffer resource in the GPU's default heap and copy vertex data into it using the upload heap. The upload resource must not be released until after
           the GPU has finished using it. */

        /* Initialize the data structures */
        tgMM_Set_U08_0x00( &sDX12_Default_Heap_Properties, sizeof( sDX12_Default_Heap_Properties ) );
        sDX12_Default_Heap_Properties.Type = D3D12_HEAP_TYPE_DEFAULT;
        sDX12_Default_Heap_Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        sDX12_Default_Heap_Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        sDX12_Default_Heap_Properties.CreationNodeMask = uiNodeMask;
        sDX12_Default_Heap_Properties.VisibleNodeMask = uiNodeMask;

        tgMM_Set_U08_0x00( &sDX12_Upload_Heap_Properties, sizeof( sDX12_Upload_Heap_Properties ) );
        sDX12_Upload_Heap_Properties.Type = D3D12_HEAP_TYPE_UPLOAD;
        sDX12_Upload_Heap_Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        sDX12_Upload_Heap_Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        sDX12_Upload_Heap_Properties.CreationNodeMask = uiNodeMask;
        sDX12_Upload_Heap_Properties.VisibleNodeMask = uiNodeMask;

        tgMM_Set_U08_0x00( &sDX12_Resource_Desc, sizeof( sDX12_Resource_Desc ) );
        sDX12_Resource_Desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        sDX12_Resource_Desc.Alignment = 0;
        sDX12_Resource_Desc.Height = 1;
        sDX12_Resource_Desc.DepthOrArraySize = 1;
        sDX12_Resource_Desc.MipLevels = 1;
        sDX12_Resource_Desc.Format = DXGI_FORMAT_UNKNOWN;
        sDX12_Resource_Desc.SampleDesc.Count = 1;
        sDX12_Resource_Desc.SampleDesc.Quality = 0;
        sDX12_Resource_Desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        sDX12_Resource_Desc.Flags = D3D12_RESOURCE_FLAG_NONE;

        tgMM_Set_U08_0x00( &sDX12_ResourceBarrier, sizeof( D3D12_RESOURCE_BARRIER ) );
        sDX12_ResourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        sDX12_ResourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        sDX12_ResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

        tgMM_Set_U08_0x00( &sDX12_SubResource_Data, sizeof( sDX12_SubResource_Data ) );

        tgMM_Set_U08_0x00( &sDX12_Range, sizeof( sDX12_Range ) );

        uCMD = tgKN_GPU_EXT__Execute__Command_List_Acquire( tiCXT_WORK, D3D12_COMMAND_LIST_TYPE_DIRECT );



        /* ** VERTEX BUFFERS ** */

        /* 1.1 Create the vertex buffers for the rendering test. */
        sDX12_Resource_Desc.Width = sizeof( sVertex_Cube );
        iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Default_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_COMMON,
                                                       nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psExec_Resource->m_psDX12_Vertex_Buffer__Cube_00 );
        TgVERIFY(SUCCEEDED(iRet));
        ID3D12Object_SetName(psExec_Resource->m_psDX12_Vertex_Buffer__Cube_00,L"Unit Test Resource: Vertex Buffer Cube 00");
        /* 1.2 Transition the vertex buffers from their general state to a copy destination. */
        sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
        sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
        sDX12_ResourceBarrier.Transition.pResource = psExec_Resource->m_psDX12_Vertex_Buffer__Cube_00;
        ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );
        /* 1.3 Create the vertex upload buffers that will be used for uploading/copying the data to the GPU. */
        sDX12_Resource_Desc.Width = sizeof( sVertex_Cube );
        iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ, 
                                                       nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psDX12_Vertex_Buffer_Upload__Cube_00 );
        TgVERIFY(SUCCEEDED(iRet));
        ID3D12Object_SetName(psDX12_Vertex_Buffer_Upload__Cube_00,L"Unit Test Resource: Vertex Upload Buffer Cube 00");
        /* 1.4 Copy the data from general CPU memory into the CPU upload buffers. */
        TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psDX12_Vertex_Buffer_Upload__Cube_00, 0, &sDX12_Range, (TgVOID_PP)(&puiMapped_Upload) )));
        memcpy( puiMapped_Upload, sVertex_Cube, sizeof( sVertex_Cube ) );
        ID3D12Resource_Unmap( psDX12_Vertex_Buffer_Upload__Cube_00, 0, &sDX12_Range );
        puiMapped_Upload = nullptr;
        ID3D12GraphicsCommandList8_CopyBufferRegion( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, psExec_Resource->m_psDX12_Vertex_Buffer__Cube_00, 0,
                                                     psDX12_Vertex_Buffer_Upload__Cube_00, 0, sizeof( sVertex_Cube ) );
        /* 1.5 Transition the vertex buffers from copy destination to vertex buffer. */
        sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
        sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
        sDX12_ResourceBarrier.Transition.pResource = psExec_Resource->m_psDX12_Vertex_Buffer__Cube_00;
        ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );



        sDX12_Resource_Desc.Width = sizeof( sVertex_Gradient );
        iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Default_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_COMMON,
                                                       nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psExec_Resource->m_psDX12_Vertex_Buffer__Gradient );
        TgVERIFY(SUCCEEDED(iRet));
        ID3D12Object_SetName(psExec_Resource->m_psDX12_Vertex_Buffer__Gradient,L"Unit Test Resource: Vertex Buffer Gradient");
        sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
        sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
        sDX12_ResourceBarrier.Transition.pResource = psExec_Resource->m_psDX12_Vertex_Buffer__Gradient;
        ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );
        sDX12_Resource_Desc.Width = sizeof( sVertex_Gradient );
        iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                       nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psDX12_Vertex_Buffer_Upload__Gradient);
        TgVERIFY(SUCCEEDED(iRet));
        ID3D12Object_SetName(psDX12_Vertex_Buffer_Upload__Gradient,L"Unit Test Resource: Vertex Upload Buffer Gradient");
        TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psDX12_Vertex_Buffer_Upload__Gradient, 0, &sDX12_Range, (TgVOID_PP)(&puiMapped_Upload) )));
        memcpy(puiMapped_Upload, sVertex_Gradient, sizeof(sVertex_Gradient));
        ID3D12Resource_Unmap( psDX12_Vertex_Buffer_Upload__Gradient, 0, &sDX12_Range );
        puiMapped_Upload = nullptr;
        ID3D12GraphicsCommandList8_CopyBufferRegion( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, psExec_Resource->m_psDX12_Vertex_Buffer__Gradient, 0,
                                                     psDX12_Vertex_Buffer_Upload__Gradient, 0, sizeof( sVertex_Gradient ) );
        sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
        sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
        sDX12_ResourceBarrier.Transition.pResource = psExec_Resource->m_psDX12_Vertex_Buffer__Gradient;
        ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );



        sDX12_Resource_Desc.Width = sizeof( sVertex_List_Cube );
        iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Default_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_COMMON,
                                                       nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psExec_Resource->m_psDX12_Vertex_Buffer__Cube_02 );
        TgVERIFY(SUCCEEDED(iRet));
        ID3D12Object_SetName(psExec_Resource->m_psDX12_Vertex_Buffer__Cube_02,L"Unit Test Resource: Vertex Buffer Cube 02");
        sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
        sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
        sDX12_ResourceBarrier.Transition.pResource = psExec_Resource->m_psDX12_Vertex_Buffer__Cube_02;
        ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );
        sDX12_Resource_Desc.Width = sizeof( sVertex_List_Cube );
        iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ, 
                                                       nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psDX12_Vertex_Buffer_Upload__Cube_02 );
        TgVERIFY(SUCCEEDED(iRet));
        ID3D12Object_SetName(psDX12_Vertex_Buffer_Upload__Cube_02,L"Unit Test Resource: Vertex Upload Buffer Cube 02");
        TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psDX12_Vertex_Buffer_Upload__Cube_02, 0, &sDX12_Range, (TgVOID_PP)(&puiMapped_Upload) )));
        memcpy( puiMapped_Upload, sVertex_List_Cube, sizeof( sVertex_List_Cube ) );
        ID3D12Resource_Unmap( psDX12_Vertex_Buffer_Upload__Cube_02, 0, &sDX12_Range );
        puiMapped_Upload = nullptr;
        ID3D12GraphicsCommandList8_CopyBufferRegion( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, psExec_Resource->m_psDX12_Vertex_Buffer__Cube_02, 0,
                                                     psDX12_Vertex_Buffer_Upload__Cube_02, 0, sizeof( sVertex_List_Cube ) );
        sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
        sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
        sDX12_ResourceBarrier.Transition.pResource = psExec_Resource->m_psDX12_Vertex_Buffer__Cube_02;
        ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );



        sDX12_Resource_Desc.Width = sizeof( sVertex_UI );
        iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Default_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_COMMON,
                                                       nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psExec_Resource->m_psDX12_Vertex_Buffer__UI );
        TgVERIFY(SUCCEEDED(iRet));
        ID3D12Object_SetName(psExec_Resource->m_psDX12_Vertex_Buffer__UI,L"Unit Test Resource: Vertex Buffer UI");
        sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
        sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
        sDX12_ResourceBarrier.Transition.pResource = psExec_Resource->m_psDX12_Vertex_Buffer__UI;
        ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );
        sDX12_Resource_Desc.Width = sizeof( sVertex_UI );
        iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                       nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psDX12_Vertex_Buffer_Upload__UI );
        TgVERIFY(SUCCEEDED(iRet));
        ID3D12Object_SetName(psDX12_Vertex_Buffer_Upload__UI,L"Unit Test Resource: Vertex Upload UI");
        TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psDX12_Vertex_Buffer_Upload__UI, 0, &sDX12_Range, (TgVOID_PP)(&puiMapped_Upload) )));
        memcpy( puiMapped_Upload, sVertex_UI, sizeof( sVertex_UI ) );
        ID3D12Resource_Unmap( psDX12_Vertex_Buffer_Upload__UI, 0, &sDX12_Range );
        puiMapped_Upload = nullptr;
        ID3D12GraphicsCommandList8_CopyBufferRegion( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, psExec_Resource->m_psDX12_Vertex_Buffer__UI, 0,
                                                     psDX12_Vertex_Buffer_Upload__UI, 0, sizeof( sVertex_UI ) );
        sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
        sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
        sDX12_ResourceBarrier.Transition.pResource = psExec_Resource->m_psDX12_Vertex_Buffer__UI;
        ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );



        /* ** INDEX BUFFERS ** */
        /* 2.1 Create the vertex buffers for the rendering test. */
        sDX12_Resource_Desc.Width = sizeof( sIndex_Cube ) + sizeof( sIndex_Gradient );
        iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Default_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_COMMON,
                                                       nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psExec_Resource->m_psDX12_Index_Buffer__Cube_and_Gradient );
        TgVERIFY(SUCCEEDED(iRet));
        ID3D12Object_SetName(psExec_Resource->m_psDX12_Index_Buffer__Cube_and_Gradient,L"Unit Test Resource: Index Buffer");

        /* 2.2 Transition the index buffers from their general state to a copy destination. */
        sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
        sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
        sDX12_ResourceBarrier.Transition.pResource = psExec_Resource->m_psDX12_Index_Buffer__Cube_and_Gradient;
        ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );

        /* 2.3 Create the vertex upload buffers that will be used for uploading/copying the data to the GPU. */
        sDX12_Resource_Desc.Width = sizeof( sIndex_Cube ) + sizeof( sIndex_Gradient );
        iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ, 
                                                        nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psDX12_Index_Buffer_Upload__Geom_and_Gradient );
        TgVERIFY(SUCCEEDED(iRet));
        ID3D12Object_SetName( psDX12_Index_Buffer_Upload__Geom_and_Gradient, L"Unit Test Resource: Index Upload Buffer" );

        /* 2.4 Copy the data from general CPU memory into the CPU upload buffers. */
        TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psDX12_Index_Buffer_Upload__Geom_and_Gradient, 0, &sDX12_Range, (TgVOID_PP)(&puiMapped_Upload) )));
        memcpy(puiMapped_Upload, sIndex_Cube, sizeof(sIndex_Cube));
        memcpy(puiMapped_Upload + sizeof(sIndex_Cube), sIndex_Gradient, sizeof(sIndex_Gradient));
        ID3D12Resource_Unmap( psDX12_Index_Buffer_Upload__Geom_and_Gradient, 0, &sDX12_Range );
        puiMapped_Upload = nullptr;
        ID3D12GraphicsCommandList8_CopyBufferRegion( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, psExec_Resource->m_psDX12_Index_Buffer__Cube_and_Gradient, 0,
                                                     psDX12_Index_Buffer_Upload__Geom_and_Gradient, 0, sizeof( sIndex_Cube ) + sizeof( sIndex_Gradient ) );

        /* 2.5 Transition the index buffer from copy destination to index buffer. */
        sDX12_ResourceBarrier.Transition.pResource = psExec_Resource->m_psDX12_Index_Buffer__Cube_and_Gradient;
        sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
        sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_INDEX_BUFFER;
        ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );



        /* ** CLOSE AND EXECUTE THE RESOURCE CREATION ** */

        /* Release the Upload Buffers - Only allowed because of the flush prior to these calls. */
        tgKN_GPU_EXT__Execute__Register_Resource_For_Release( uCMD, psDX12_Vertex_Buffer_Upload__UI );
        tgKN_GPU_EXT__Execute__Register_Resource_For_Release( uCMD, psDX12_Vertex_Buffer_Upload__Cube_02 );
        tgKN_GPU_EXT__Execute__Register_Resource_For_Release( uCMD, psDX12_Vertex_Buffer_Upload__Gradient );
        tgKN_GPU_EXT__Execute__Register_Resource_For_Release( uCMD, psDX12_Vertex_Buffer_Upload__Cube_00 );
        tgKN_GPU_EXT__Execute__Register_Resource_For_Release( uCMD, psDX12_Index_Buffer_Upload__Geom_and_Gradient );

        /* Close the command list and execute it to begin the vertex/index buffer copy into the GPU's default heap. */
        tgKN_GPU_EXT__CMD__Command_List_Close( uCMD );
        uCMD.psEXT = nullptr;
    }




    tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
}


/* ---- tgUnit_Test__KN_GPU__Render ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__KN_GPU__Render( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgRSIZE_C uiTest_Level )
{
    switch (uiTest_Level) {
    case 0: return (tgUnit_Test__KN_GPU__Render_0( tiCXT_EXEC, tiCXT_SWAP, tiCXT_WORK ));
    case 1: return (tgUnit_Test__KN_GPU__Render_1( tiCXT_EXEC, tiCXT_SWAP, tiCXT_WORK ));
    case 2: return (tgUnit_Test__KN_GPU__Render_2( tiCXT_EXEC, tiCXT_SWAP, tiCXT_WORK ));
    case 3: return (tgUnit_Test__KN_GPU__Render_3( tiCXT_EXEC, tiCXT_SWAP, tiCXT_WORK ));
    case 4: return (tgUnit_Test__KN_GPU__Render_4( tiCXT_EXEC, tiCXT_SWAP, tiCXT_WORK ));
    case 5: return (tgUnit_Test__KN_GPU__Render_5( tiCXT_EXEC, tiCXT_SWAP, tiCXT_WORK ));
    }

    return (KTgS_OK);
}


/* ---- tgUnit_Test__KN_GPU__Release_Resources ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__KN_GPU__Release_Resources( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    STg2_UT_KN_GPU_Exec_Resources_P     psExec_Resource = s_saGPU_Exec_Resources + tiCXT_EXEC.m_uiI;
    STg2_UT_KN_GPU_Swap_Resources_P     psSwap_Resource = s_saGPU_Swap_Resources + tiCXT_SWAP.m_uiI;

    --psExec_Resource->m_uiRefCount;

    if (0 == psExec_Resource->m_uiRefCount)
    {
        tgKN_GPU_EXT__Execute__Flush( tiCXT_EXEC );

        if (psExec_Resource->m_psDX12_Index_Buffer__Cube_and_Gradient)
        {
            TgVERIFY( 0 == ID3D12Heap_Release( psExec_Resource->m_psDX12_Index_Buffer__Cube_and_Gradient ) );
        };

        if (psExec_Resource->m_psDX12_Vertex_Buffer__Cube_02)
        {
            TgVERIFY( 0 == ID3D12Resource_Release( psExec_Resource->m_psDX12_Vertex_Buffer__Cube_02 ) );
        };

        if (psExec_Resource->m_psDX12_Vertex_Buffer__Cube_00)
        {
            TgVERIFY( 0 == ID3D12Resource_Release( psExec_Resource->m_psDX12_Vertex_Buffer__Cube_00 ) );
        };

        if (psExec_Resource->m_psDX12_Vertex_Buffer__Gradient)
        {
            TgVERIFY( 0 == ID3D12Resource_Release( psExec_Resource->m_psDX12_Vertex_Buffer__Gradient ) );
        };

        if (psExec_Resource->m_psDX12_Vertex_Buffer__UI)
        {
            TgVERIFY( 0 == ID3D12Resource_Release( psExec_Resource->m_psDX12_Vertex_Buffer__UI ) );
        };
    }

    if (psSwap_Resource->m_psDX12_CBV_Instance_Model)
    {
        TgVERIFY( 0 == ID3D12Resource_Release( psSwap_Resource->m_psDX12_CBV_Instance_Model ) );
    };

    if (psSwap_Resource->m_psDX12_CBV_Model_01)
    {
        TgVERIFY( 0 == ID3D12Resource_Release( psSwap_Resource->m_psDX12_CBV_Model_01 ) );
    };

    if (psSwap_Resource->m_psDX12_CBV_Model_00)
    {
        TgVERIFY( 0 == ID3D12Resource_Release( psSwap_Resource->m_psDX12_CBV_Model_00 ) );
    };

    if (psSwap_Resource->m_psDX12_CBV_Scene)
    {
        TgVERIFY( 0 == ID3D12Resource_Release( psSwap_Resource->m_psDX12_CBV_Scene ) );
    };

    if (psSwap_Resource->m_psDX12_CBV_Gradient_SDR)
    {
        TgVERIFY( 0 == ID3D12Resource_Release( psSwap_Resource->m_psDX12_CBV_Gradient_SDR ) );
    };

    if (psSwap_Resource->m_psDX12_CBV_Gradient_HDR)
    {
        TgVERIFY( 0 == ID3D12Resource_Release( psSwap_Resource->m_psDX12_CBV_Gradient_HDR ) );
    };

    return (KTgS_OK);
}


/* ---- tgUnit_Test__KN_GPU__Render_0 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgUnit_Test__KN_GPU__Render_0( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK )
{
    TgBOOL                              bEndFrame = false;
    UTg2_KN_GPU_CMD                     uCMD;
    TgVEC_S_F32_04_1                    vClearColor;

    D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_RTV;
    D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_DSV;
    STg2_KN_GPU_HLSL_Output_DESC        sOutput_DESC;
    STg2_KN_GPU_Render_Buffer           sRTBuffer, sDSBuffer;

    if (KTgKN_GPU_CXT_WORK_ID__INVALID.m_uiKI == tiCXT_WORK.m_uiKI)
    {
        tiCXT_WORK = tgKN_GPU_EXT__Execute__Frame_Start( tiCXT_EXEC );
        bEndFrame = true;
    }
    uCMD = tgKN_GPU_EXT__Execute__Command_List_Acquire( tiCXT_WORK, D3D12_COMMAND_LIST_TYPE_DIRECT );
    tgKN_GPU_EXT__CMD__Set_Graphics_Root_Signature_From_Default( uCMD, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG );

    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Get_Back_Buffer( &shHeap_RTV, &shHeap_DSV, &sOutput_DESC, tiCXT_SWAP )))
    {
        return (KTgE_FAIL);
    };
    tgKN_GPU__SwapChain__Get_Target_Buffers( &sRTBuffer, &sDSBuffer, tiCXT_SWAP );

    // Define the clear colour in G10 P709, scale when in HDR by the ratio of HDR Max Luminance / SDR Max Luminance, and convert to values in the correct colour space.

    vClearColor.r = 0.5F * tgPM_SIN_F32(                         KTgPI_F32 * tgTM_Query_Time() * 0.0005F ) + 0.5F;
    vClearColor.g = 0.5F * tgPM_SIN_F32( (2.F/3.F) * KTgPI_F32 + KTgPI_F32 * tgTM_Query_Time() * 0.0005F ) + 0.5F;
    vClearColor.b = 0.5F * tgPM_SIN_F32( (4.F/3.F) * KTgPI_F32 + KTgPI_F32 * tgTM_Query_Time() * 0.0005F ) + 0.5F;
    vClearColor.a = 1.0F;

    vClearColor = tgKN_GPU_Colour_Grading_CPU( vClearColor, &sOutput_DESC );

    /* Phase Zero Test: Clear the render and depth buffer. */
    ID3D12GraphicsCommandList8_OMSetRenderTargets( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &shHeap_RTV, FALSE, &shHeap_DSV );
    tgKN_GPU_EXT__SwapChain__Set_Viewport_and_Scissor( tiCXT_SWAP, uCMD );
    ID3D12GraphicsCommandList8_ClearRenderTargetView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, shHeap_RTV, &vClearColor.r, 0, nullptr );
    ID3D12GraphicsCommandList8_ClearDepthStencilView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, shHeap_DSV, D3D12_CLEAR_FLAG_DEPTH, 1.0F, 0, 0, nullptr );

    tgKN_GPU_EXT__CMD__Command_List_Close( uCMD );
    uCMD.ps = nullptr;
    tgKN_GPU_EXT__SwapChain__Present( tiCXT_WORK, tiCXT_SWAP );
    if (bEndFrame)
    {
        tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
    }
    return (KTgS_OK);
}


/* ---- tgUnit_Test__KN_GPU__Render_1 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgUnit_Test__KN_GPU__Render_1( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK )
{
    TgBOOL                              bEndFrame = false;

    UTg2_KN_GPU_CMD                     uCMD;
    STg2_KN_GPU_Render_Buffer           sRTBuffer, sDSBuffer;
    STg2_KN_GPU_HLSL_Output_DESC        sOutput_DESC;
    TgFLOAT32                           afClearColor[4];

    D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_RTV;
    D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_DSV;

    afClearColor[0] = afClearColor[1] = afClearColor[2] = 0.0F;
    afClearColor[3] = 1.0F;

    if (KTgKN_GPU_CXT_WORK_ID__INVALID.m_uiKI == tiCXT_WORK.m_uiKI)
    {
        tiCXT_WORK = tgKN_GPU_EXT__Execute__Frame_Start( tiCXT_EXEC );
        bEndFrame = true;
    }
    uCMD = tgKN_GPU_EXT__Execute__Command_List_Acquire( tiCXT_WORK, D3D12_COMMAND_LIST_TYPE_DIRECT );
    tgKN_GPU_EXT__CMD__Set_Graphics_Root_Signature_From_Default( uCMD, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG );

    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Get_Back_Buffer( &shHeap_RTV, &shHeap_DSV, &sOutput_DESC, tiCXT_SWAP )))
    {
        return (KTgE_FAIL);
    };
    tgKN_GPU__SwapChain__Get_Target_Buffers( &sRTBuffer, &sDSBuffer, tiCXT_SWAP );

    /* Phase Zero Test: Clear the render and depth buffer. */
    ID3D12GraphicsCommandList8_OMSetRenderTargets( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &shHeap_RTV, FALSE, &shHeap_DSV );
    tgKN_GPU_EXT__SwapChain__Set_Viewport_and_Scissor( tiCXT_SWAP, uCMD );
    /* Do not execute a render target clear. */
    ID3D12GraphicsCommandList8_ClearRenderTargetView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, shHeap_RTV, afClearColor, 0, nullptr );
    ID3D12GraphicsCommandList8_ClearDepthStencilView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, shHeap_DSV, D3D12_CLEAR_FLAG_DEPTH, 1.0F, 0, 0, nullptr );

    /* Clear the render target using a full screen quad. */
    #if TgCOMPILE__RENDER_DEBUG_OUTPUT
    {
        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw UI - Clear Viewport" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_UI, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );
        s_sUIConstantBuffer.m_sDESC = sOutput_DESC;
        s_sUIConstantBuffer.m_vRect_UI.x = -1.0F;
        s_sUIConstantBuffer.m_vRect_UI.y =  1.0F;
        s_sUIConstantBuffer.m_vRect_UI.z =  1.0F;
        s_sUIConstantBuffer.m_vRect_UI.w = -1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.r = 0.5F * tgPM_SIN_F32(                         KTgPI_F32 * tgTM_Query_Time() * 0.0005F ) + 0.5F;
        s_sUIConstantBuffer.m_vUI_Colour.g = 0.5F * tgPM_SIN_F32( (2.F/3.F) * KTgPI_F32 + KTgPI_F32 * tgTM_Query_Time() * 0.0005F ) + 0.5F;
        s_sUIConstantBuffer.m_vUI_Colour.b = 0.5F * tgPM_SIN_F32( (4.F/3.F) * KTgPI_F32 + KTgPI_F32 * tgTM_Query_Time() * 0.0005F ) + 0.5F;
        s_sUIConstantBuffer.m_vUI_Colour.a = 1.0F;
        s_sUIConstantBuffer.m_uiSelect_Default_Texture_Index = 1;
        tgKN_GPU_EXT__CMD__Render_Debug_UI( uCMD, &s_sUIConstantBuffer );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif

    tgKN_GPU_EXT__CMD__Command_List_Close( uCMD );
    uCMD.ps = nullptr;
    tgKN_GPU_EXT__SwapChain__Present( tiCXT_WORK, tiCXT_SWAP );
    if (bEndFrame)
    {
        tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
    }
    return (KTgS_OK);
}


/* ---- tgUnit_Test__KN_GPU__Render_2 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgUnit_Test__KN_GPU__Render_2( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK )
{
    TgBOOL                              bEndFrame = false;

    UTg2_KN_GPU_CMD                     uCMD;
    STg2_KN_GPU_Render_Buffer           sRTBuffer, sDSBuffer;
    STg2_KN_GPU_HLSL_Output_DESC        sOutput_DESC;
    TgFLOAT32                           afClearColor[4];

    D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_RTV;
    D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_DSV;

    afClearColor[0] = afClearColor[1] = afClearColor[2] = 0.0F;
    afClearColor[3] = 1.0F;

    if (KTgKN_GPU_CXT_WORK_ID__INVALID.m_uiKI == tiCXT_WORK.m_uiKI)
    {
        tiCXT_WORK = tgKN_GPU_EXT__Execute__Frame_Start( tiCXT_EXEC );
        bEndFrame = true;
    }
    uCMD = tgKN_GPU_EXT__Execute__Command_List_Acquire( tiCXT_WORK, D3D12_COMMAND_LIST_TYPE_DIRECT );
    tgKN_GPU_EXT__CMD__Set_Graphics_Root_Signature_From_Default( uCMD, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG );

    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Get_Back_Buffer( &shHeap_RTV, &shHeap_DSV, &sOutput_DESC, tiCXT_SWAP )))
    {
        return (KTgE_FAIL);
    };
    tgKN_GPU__SwapChain__Get_Target_Buffers( &sRTBuffer, &sDSBuffer, tiCXT_SWAP );

    /* Phase Zero Test: Clear the render and depth buffer. */
    ID3D12GraphicsCommandList8_OMSetRenderTargets( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &shHeap_RTV, FALSE, &shHeap_DSV );
    tgKN_GPU_EXT__SwapChain__Set_Viewport_and_Scissor( tiCXT_SWAP, uCMD );
    /* Do not execute a render target clear. */
    ID3D12GraphicsCommandList8_ClearDepthStencilView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, shHeap_DSV, D3D12_CLEAR_FLAG_DEPTH, 1.0F, 0, 0, nullptr );

    /* Clear the render target using a full screen quad. */
    #if TgCOMPILE__RENDER_DEBUG_OUTPUT
    {
        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw UI - Clear Viewport" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_UI, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );
        s_sUIConstantBuffer.m_sDESC = sOutput_DESC;
        s_sUIConstantBuffer.m_vRect_UI.x = -1.0F;
        s_sUIConstantBuffer.m_vRect_UI.y =  1.0F;
        s_sUIConstantBuffer.m_vRect_UI.z =  1.0F;
        s_sUIConstantBuffer.m_vRect_UI.w = -1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.r = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.g = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.b = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.a = 1.0F;
        s_sUIConstantBuffer.m_uiSelect_Default_Texture_Index = 15;
        tgKN_GPU_EXT__CMD__Render_Debug_UI( uCMD, &s_sUIConstantBuffer );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif

    tgKN_GPU_EXT__CMD__Command_List_Close( uCMD );
    uCMD.psEXT = nullptr;
    tgKN_GPU_EXT__SwapChain__Present( tiCXT_WORK, tiCXT_SWAP );
    if (bEndFrame)
    {
        tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
    }
    return (KTgS_OK);
}


/* ---- tgUnit_Test__KN_GPU__Render_Background_And_Gradient ---------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static UTg2_KN_GPU_CMD tgUnit_Test__KN_GPU__Render_Background_And_Gradient( STg2_KN_GPU_Render_Buffer_PC psRTBuffer, STg2_KN_GPU_Render_Buffer_PC psDSBuffer, 
                                                                            STg2_KN_GPU_HLSL_Output_DESC_PC psOutput_DESC, TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC,
                                                                            TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK )
{
    STg2_UT_KN_GPU_Exec_Resources_P     psExec_Resource = s_saGPU_Exec_Resources + tiCXT_EXEC.m_uiI;
    STg2_UT_KN_GPU_Swap_Resources_P     psSwap_Resource = s_saGPU_Swap_Resources + tiCXT_SWAP.m_uiI;

    UTg2_KN_GPU_CMD                     uCMD;

    D3D12_GPU_DESCRIPTOR_HANDLE         shDX12_GPU;
    D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_RTV;
    D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_DSV;

    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Get_Back_Buffer( &shHeap_RTV, &shHeap_DSV, psOutput_DESC, tiCXT_SWAP )))
    {
        uCMD.ps = nullptr;
        return (uCMD);
    };

    uCMD = tgKN_GPU_EXT__Execute__Command_List_Acquire( tiCXT_WORK, D3D12_COMMAND_LIST_TYPE_DIRECT );
    tgKN_GPU_EXT__CMD__Set_Graphics_Root_Signature_From_Default( uCMD, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG );
    tgKN_GPU__SwapChain__Get_Target_Buffers( psRTBuffer, psDSBuffer, tiCXT_SWAP );

    {
        D3D12_GPU_VIRTUAL_ADDRESS           uiGpuAddress;
        D3D12_CONSTANT_BUFFER_VIEW_DESC     sDX12_KBV;

        /* Create constant buffer views to access the upload buffer. */
        uiGpuAddress = ID3D12Resource_GetGPUVirtualAddress( psSwap_Resource->m_psDX12_CBV_Gradient_SDR );
        sDX12_KBV.BufferLocation = uiGpuAddress;
        sDX12_KBV.SizeInBytes = c_alignedModelConstantBufferSize;
        ID3D12Device10_CreateConstantBufferView( uCMD.psEXT->m_psDX12_Device, &sDX12_KBV, uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_sDX12_CPU_Handle );
        uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_sDX12_CPU_Handle.ptr += uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_uiDescriptor_Size;

        uiGpuAddress = ID3D12Resource_GetGPUVirtualAddress( psSwap_Resource->m_psDX12_CBV_Gradient_HDR );
        sDX12_KBV.BufferLocation = uiGpuAddress;
        sDX12_KBV.SizeInBytes = c_alignedModelConstantBufferSize;
        ID3D12Device10_CreateConstantBufferView( uCMD.psEXT->m_psDX12_Device, &sDX12_KBV, uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_sDX12_CPU_Handle );
        uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_sDX12_CPU_Handle.ptr += uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_uiDescriptor_Size;
    }

    ID3D12GraphicsCommandList8_OMSetRenderTargets( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &shHeap_RTV, FALSE, &shHeap_DSV );
    tgKN_GPU_EXT__SwapChain__Set_Viewport_and_Scissor( tiCXT_SWAP, uCMD );
    ID3D12GraphicsCommandList8_ClearDepthStencilView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, shHeap_DSV, D3D12_CLEAR_FLAG_DEPTH, 1.0F, 0, 0, nullptr );

    tgUnit_Test__KN_GPU__Setup_Scene_Constant_Buffer( psOutput_DESC, psRTBuffer );

    /* Clear the render target using a full screen quad. */
    #if TgCOMPILE__RENDER_DEBUG_OUTPUT
    {
        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw UI - Clear Viewport" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_UI, psRTBuffer->m_enFormat, psDSBuffer->m_enFormat );
        s_sUIConstantBuffer.m_sDESC = *psOutput_DESC;
        s_sUIConstantBuffer.m_vRect_UI.x = -1.0F;
        s_sUIConstantBuffer.m_vRect_UI.y =  1.0F;
        s_sUIConstantBuffer.m_vRect_UI.z =  1.0F;
        s_sUIConstantBuffer.m_vRect_UI.w = -1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.r = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.g = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.b = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.a = 1.0F;
        s_sUIConstantBuffer.m_uiSelect_Default_Texture_Index = 15;
        tgKN_GPU_EXT__CMD__Render_Debug_UI( uCMD, &s_sUIConstantBuffer );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif

    /* Phase One Test: Render a mesh using vertex buffer, constant buffer, shaders */
    {
        D3D12_VERTEX_BUFFER_VIEW            sVertex_Buffer_View;
        UINT8*                              puiMappedConstantBuffer;
        D3D12_RANGE                         sRead_Range;

        sVertex_Buffer_View.BufferLocation = ID3D12Resource_GetGPUVirtualAddress( psExec_Resource->m_psDX12_Vertex_Buffer__Gradient );
        sVertex_Buffer_View.StrideInBytes = sizeof( STg2_KN_GPU_Vertex_UI );
        sVertex_Buffer_View.SizeInBytes = sizeof( sVertex_Gradient );

        tgMM_Set_U08_0x00( &sRead_Range, sizeof( sRead_Range ) );

        s_sUIConstantBuffer.m_sDESC = *psOutput_DESC;
        s_sUIConstantBuffer.m_vRect_UI.x = -1.0F + 20.0F / (float)psRTBuffer->m_uiWidth;
        s_sUIConstantBuffer.m_vRect_UI.y = -1.0F + 35.0F / (float)psRTBuffer->m_uiHeight;
        s_sUIConstantBuffer.m_vRect_UI.z =  1.0F - 20.0F / (float)psRTBuffer->m_uiWidth;
        s_sUIConstantBuffer.m_vRect_UI.w = -1.0F + 5.0F / (float)psRTBuffer->m_uiHeight;
        s_sUIConstantBuffer.m_vUI_Colour.r = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.g = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.b = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.a = 1.0F;
        s_sUIConstantBuffer.m_uiSelect_Default_Texture_Index = 1;

        TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psSwap_Resource->m_psDX12_CBV_Gradient_SDR, 0, &sRead_Range, (TgVOID_PP)&puiMappedConstantBuffer )));
        tgMM_Copy( puiMappedConstantBuffer, c_alignedUIConstantBufferSize, &s_sUIConstantBuffer, sizeof( s_sUIConstantBuffer ) );
        ID3D12Resource_Unmap( psSwap_Resource->m_psDX12_CBV_Gradient_SDR, 0, &sRead_Range );

        s_sUIConstantBuffer.m_vRect_UI.x = -1.0F + 20.0F / (float)psRTBuffer->m_uiWidth;
        s_sUIConstantBuffer.m_vRect_UI.y = -1.0F + 75.0F / (float)psRTBuffer->m_uiHeight;
        s_sUIConstantBuffer.m_vRect_UI.z =  1.0F - 20.0F / (float)psRTBuffer->m_uiWidth;
        s_sUIConstantBuffer.m_vRect_UI.w = -1.0F + 45.0F / (float)psRTBuffer->m_uiHeight;
        s_sUIConstantBuffer.m_vUI_Colour.r = 3.0F;
        s_sUIConstantBuffer.m_vUI_Colour.g = 3.0F;
        s_sUIConstantBuffer.m_vUI_Colour.b = 3.0F;
        s_sUIConstantBuffer.m_vUI_Colour.a = 1.0F;

        TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psSwap_Resource->m_psDX12_CBV_Gradient_HDR, 0, &sRead_Range, (TgVOID_PP)&puiMappedConstantBuffer )));
        tgMM_Copy( puiMappedConstantBuffer, c_alignedUIConstantBufferSize, &s_sUIConstantBuffer, sizeof( s_sUIConstantBuffer ) );
        ID3D12Resource_Unmap( psSwap_Resource->m_psDX12_CBV_Gradient_HDR, 0, &sRead_Range );

        /* Draw the Gradients as a Triangle Strip */
        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw Gradient (Strip)" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_UI_WITH_GAMMA, psRTBuffer->m_enFormat, psDSBuffer->m_enFormat );
        ID3D12GraphicsCommandList8_IASetVertexBuffers( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, 1, &sVertex_Buffer_View );
        ID3D12GraphicsCommandList8_IASetIndexBuffer( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, nullptr );
        ID3D12GraphicsCommandList8_IASetPrimitiveTopology( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
        ID3D12GraphicsCommandList8_SetGraphicsRootConstantBufferView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0,
                                                                      ID3D12Resource_GetGPUVirtualAddress( psSwap_Resource->m_psDX12_CBV_Gradient_SDR ) );
        ID3D12DescriptorHeap_GetGPUDescriptorHandleForHeapStart( uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_psDX12_Heap, &shDX12_GPU );
        ID3D12GraphicsCommandList8_SetGraphicsRootDescriptorTable( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, shDX12_GPU );
        ID3D12GraphicsCommandList8_DrawInstanced( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 4, 1, 0, 0 );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );

        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw Gradient (Strip)" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_UI_WITH_GAMMA, psRTBuffer->m_enFormat, psDSBuffer->m_enFormat );
        ID3D12GraphicsCommandList8_SetGraphicsRootConstantBufferView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0,
                                                                      ID3D12Resource_GetGPUVirtualAddress( psSwap_Resource->m_psDX12_CBV_Gradient_HDR ) );
        ID3D12GraphicsCommandList8_DrawInstanced( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 4, 1, 0, 0 );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }

    return (uCMD);
}


/* ---- tgUnit_Test__KN_GPU__Render_3 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgUnit_Test__KN_GPU__Render_3( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK )
{
    STg2_KN_GPU_Render_Buffer           sRTBuffer, sDSBuffer;
    STg2_KN_GPU_HLSL_Output_DESC        sOutput_DESC;
    UTg2_KN_GPU_CMD                     uCMD;
    TgBOOL                              bEndFrame;

    bEndFrame = false;
    if (KTgKN_GPU_CXT_WORK_ID__INVALID.m_uiKI == tiCXT_WORK.m_uiKI)
    {
        tiCXT_WORK = tgKN_GPU_EXT__Execute__Frame_Start( tiCXT_EXEC );
        bEndFrame = true;
    }

    uCMD = tgUnit_Test__KN_GPU__Render_Background_And_Gradient( &sRTBuffer, &sDSBuffer, &sOutput_DESC, tiCXT_EXEC, tiCXT_SWAP, tiCXT_WORK );
    if (nullptr == uCMD.ps)
    {
        if (bEndFrame)
        {
            tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
        }
        return (KTgE_FAIL);
    }

    #if TgCOMPILE__RENDER_DEBUG_OUTPUT
    {
        TgVEC_S_F32_04_4                    mScale, mRotation;
        TgSINT_E32                          iPM;

        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw Debug Sphere" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_02, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );
        tgMH_CLI_S_F32_04_4( &mScale );
        mScale._11 = 3.0F;
        mScale._22 = 3.0F;
        mScale._33 = 3.0F;
        tgMH_Init_Euler_ELEM_S_F32_04_4( &mRotation, -45.0f * KTgPI_F32 / 180.0f * tgTM_Query_Time() * 0.005F, 0.0F, 0.0F );
        tgMH_CAT_S_F32_04_4( &s_sModelConstantBuffer.m_vModel_Transform, &mScale, &mRotation );
        s_sModelConstantBuffer.m_sDESC = sOutput_DESC;
        tgMM_Copy( &s_sModelConstantBuffer.m_mW2C, sizeof(s_sModelConstantBuffer.m_mW2C), &s_sSceneConstantBuffer.m_mW2C, sizeof(s_sSceneConstantBuffer.m_mW2C) );
        tgMM_Copy( &s_sModelConstantBuffer.m_mC2S, sizeof(s_sModelConstantBuffer.m_mC2S), &s_sSceneConstantBuffer.m_mC2S, sizeof(s_sSceneConstantBuffer.m_mC2S) );
        s_sModelConstantBuffer.m_vModel_Colour = tgMH_Init_ELEM_S_F32_04_1( 1.0F, 1.0F, 1.0F, 1.0F );
        s_sModelConstantBuffer.m_vLight_Ambient = tgMH_Init_ELEM_S_F32_04_1( 0.1F, 0.1F, 0.1F, 1.0F );
        s_sModelConstantBuffer.m_vLight_Direction = tgMH_Init_ELEM_S_F32_04_1( -1.0F/1.73205081F, 1.0F/1.73205081F, -1.0F/1.73205081F, 0.0F );
        s_sModelConstantBuffer.m_vLight_Direction_Colour = tgMH_Init_ELEM_S_F32_04_1( 0.4F, 0.6F, 0.6F, 1.0F );
        iPM = (TgSINT_E32)(tgPM_FLOOR_F32( tgPM_FMOD_F32( tgTM_Query_Time(), (float)ETgKN_GPU_DEBUG_PM_3D_COUNT*1600.0F ) / 1600.0F ));
        tgKN_GPU_EXT__CMD__Render_Debug_Geom( uCMD, ETgKN_GPU_DEBUG_PM_3D_START + iPM, &s_sModelConstantBuffer );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif

    tgKN_GPU_EXT__CMD__Command_List_Close( uCMD );
    uCMD.ps = nullptr;
    tgKN_GPU_EXT__SwapChain__Present( tiCXT_WORK, tiCXT_SWAP );
    if (bEndFrame)
    {
        tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
    }
    return (KTgS_OK);
}


/* ---- tgUnit_Test__KN_GPU__Render_4 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgUnit_Test__KN_GPU__Render_4( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK )
{
    STg2_KN_GPU_Render_Buffer           sRTBuffer, sDSBuffer;
    STg2_KN_GPU_HLSL_Output_DESC        sOutput_DESC;
    UTg2_KN_GPU_CMD                     uCMD;
    TgBOOL                              bEndFrame;

    bEndFrame = false;
    if (KTgKN_GPU_CXT_WORK_ID__INVALID.m_uiKI == tiCXT_WORK.m_uiKI)
    {
        tiCXT_WORK = tgKN_GPU_EXT__Execute__Frame_Start( tiCXT_EXEC );
        bEndFrame = true;
    }

    uCMD = tgUnit_Test__KN_GPU__Render_Background_And_Gradient( &sRTBuffer, &sDSBuffer, &sOutput_DESC, tiCXT_EXEC, tiCXT_SWAP, tiCXT_WORK );
    if (nullptr == uCMD.ps)
    {
        if (bEndFrame)
        {
            tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
        }
        return (KTgE_FAIL);
    }

    #if TgCOMPILE__RENDER_DEBUG_OUTPUT
    {
        TgUINT_E32                          uiPM;
        TgVEC_S_F32_04_1                    avGraph_Points[5];
        TgVEC_F32_04_1                      avColour[4];
        TgUN_V128                           uS0, uS1;
        TgRSIZE                             uiIndex;
        TgVEC_S_F32_04_4                    mS2C, mC2W;
        TgRSIZE_C                           uiMax_Value = 20;

        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw Debug Lines" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_LINE, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );
        s_sLineConstantBuffer.m_sDESC = sOutput_DESC;
        tgMM_Copy( &s_sLineConstantBuffer.m_mW2C, sizeof(s_sLineConstantBuffer.m_mW2C), &s_sSceneConstantBuffer.m_mW2C, sizeof(s_sSceneConstantBuffer.m_mW2C) );
        tgMM_Copy( &s_sLineConstantBuffer.m_mC2S, sizeof(s_sLineConstantBuffer.m_mC2S), &s_sSceneConstantBuffer.m_mC2S, sizeof(s_sSceneConstantBuffer.m_mC2S) );
        uiPM = (TgUINT_E32)(tgPM_FLOOR_F32( tgPM_FMOD_F32( tgTM_Query_Time(), 2.0F*1600.0F ) / 1600.0F ));

        tgMH_INV_S_F32_04_4( &mS2C, &s_sSceneConstantBuffer.m_mC2S );
        tgMH_INV_S_F32_04_4( &mC2W, &s_sSceneConstantBuffer.m_mW2C );

        avGraph_Points[0] = tgMH_TX_S_F32_04_4( tgMH_Init_Point_ELEM_S_F32_04_1( 0.0F, 0.0F, 0.5F ), &mS2C );
        avGraph_Points[0] = tgMH_DIV_S_F32_04_1( avGraph_Points[0], tgMH_SET1_S_F32_04_1(avGraph_Points[0].w) );
        avGraph_Points[0] = tgMH_TX_S_F32_04_4( avGraph_Points[0], &mC2W );

        avGraph_Points[1] = tgMH_TX_S_F32_04_4( tgMH_Init_Point_ELEM_S_F32_04_1( -0.75F, 0.0F, 0.5F ), &mS2C );
        avGraph_Points[1] = tgMH_DIV_S_F32_04_1( avGraph_Points[1], tgMH_SET1_S_F32_04_1(avGraph_Points[1].w) );
        avGraph_Points[1] = tgMH_TX_S_F32_04_4( avGraph_Points[1], &mC2W );

        avGraph_Points[2] = tgMH_TX_S_F32_04_4( tgMH_Init_Point_ELEM_S_F32_04_1( 0.75F, 0.0F, 0.5F ), &mS2C );
        avGraph_Points[2] = tgMH_DIV_S_F32_04_1( avGraph_Points[2], tgMH_SET1_S_F32_04_1(avGraph_Points[2].w) );
        avGraph_Points[2] = tgMH_TX_S_F32_04_4( avGraph_Points[2], &mC2W );

        avGraph_Points[3] = tgMH_TX_S_F32_04_4( tgMH_Init_Point_ELEM_S_F32_04_1( 0.0F, -0.75F, 0.5F ), &mS2C );
        avGraph_Points[3] = tgMH_DIV_S_F32_04_1( avGraph_Points[3], tgMH_SET1_S_F32_04_1(avGraph_Points[3].w) );
        avGraph_Points[3] = tgMH_TX_S_F32_04_4( avGraph_Points[3], &mC2W );

        avGraph_Points[4] = tgMH_TX_S_F32_04_4( tgMH_Init_Point_ELEM_S_F32_04_1( 0.0F, 0.75F, 0.5F ), &mS2C );
        avGraph_Points[4] = tgMH_DIV_S_F32_04_1( avGraph_Points[4], tgMH_SET1_S_F32_04_1(avGraph_Points[4].w) );
        avGraph_Points[4] = tgMH_TX_S_F32_04_4( avGraph_Points[4], &mC2W );

        avColour[0] = tgMH_Init_ELEM_F32_04_1( 1.0F, 0.0F, 0.0F, 1.0F );
        avColour[1] = tgMH_Init_ELEM_F32_04_1( 1.0F, 1.0F, 0.0F, 1.0F );
        avColour[2] = tgMH_Init_ELEM_F32_04_1( 0.0F, 0.0F, 1.0F, 1.0F );
        avColour[3] = tgMH_Init_ELEM_F32_04_1( 0.0F, 1.0F, 1.0F, 1.0F );

        for( uiIndex = 0; uiIndex <= uiMax_Value; ++uiIndex)
        {
            uS0.m_vS_F32_04_1 = tgMH_SUB_S_F32_04_1(avGraph_Points[1],avGraph_Points[0]);
            uS0.m_vS_F32_04_1 = tgMH_MUL_S_F32_04_1(uS0.m_vS_F32_04_1, tgMH_SET1_S_F32_04_1( (float)(uiMax_Value - uiIndex) / (float)uiMax_Value ));
            uS0.m_vS_F32_04_1 = tgMH_ADD_S_F32_04_1(uS0.m_vS_F32_04_1,avGraph_Points[0]);

            uS1.m_vS_F32_04_1 = tgMH_SUB_S_F32_04_1(avGraph_Points[4],avGraph_Points[0]);
            uS1.m_vS_F32_04_1 = tgMH_MUL_S_F32_04_1(uS1.m_vS_F32_04_1, tgMH_SET1_S_F32_04_1( (float)(uiIndex) / (float)uiMax_Value ));
            uS1.m_vS_F32_04_1 = tgMH_ADD_S_F32_04_1(uS1.m_vS_F32_04_1,avGraph_Points[0]);

            tgKN_GPU__CMD__Render_Debug_Line( uCMD, uS0.m_vF32_04_1, avColour[(uiPM+0u)%TgARRAY_COUNT(avColour)], uS1.m_vF32_04_1,
                                              avColour[(uiPM+1u)%TgARRAY_COUNT(avColour)], &s_sLineConstantBuffer );

            uS0.m_vS_F32_04_1 = tgMH_SUB_S_F32_04_1(avGraph_Points[2],avGraph_Points[0]);
            uS0.m_vS_F32_04_1 = tgMH_MUL_S_F32_04_1(uS0.m_vS_F32_04_1, tgMH_SET1_S_F32_04_1( (float)(uiMax_Value - uiIndex) / (float)uiMax_Value ));
            uS0.m_vS_F32_04_1 = tgMH_ADD_S_F32_04_1(uS0.m_vS_F32_04_1,avGraph_Points[0]);

            uS1.m_vS_F32_04_1 = tgMH_SUB_S_F32_04_1(avGraph_Points[4],avGraph_Points[0]);
            uS1.m_vS_F32_04_1 = tgMH_MUL_S_F32_04_1(uS1.m_vS_F32_04_1, tgMH_SET1_S_F32_04_1( (float)(uiIndex) / (float)uiMax_Value ));
            uS1.m_vS_F32_04_1 = tgMH_ADD_S_F32_04_1(uS1.m_vS_F32_04_1,avGraph_Points[0]);

            tgKN_GPU__CMD__Render_Debug_Line( uCMD, uS0.m_vF32_04_1, avColour[(uiPM+0u)%TgARRAY_COUNT(avColour)], uS1.m_vF32_04_1,
                                              avColour[(uiPM+1u)%TgARRAY_COUNT(avColour)], &s_sLineConstantBuffer );

            uS0.m_vS_F32_04_1 = tgMH_SUB_S_F32_04_1(avGraph_Points[1],avGraph_Points[0]);
            uS0.m_vS_F32_04_1 = tgMH_MUL_S_F32_04_1(uS0.m_vS_F32_04_1, tgMH_SET1_S_F32_04_1( (float)(uiMax_Value - uiIndex) / (float)uiMax_Value ));
            uS0.m_vS_F32_04_1 = tgMH_ADD_S_F32_04_1(uS0.m_vS_F32_04_1,avGraph_Points[0]);

            uS1.m_vS_F32_04_1 = tgMH_SUB_S_F32_04_1(avGraph_Points[3],avGraph_Points[0]);
            uS1.m_vS_F32_04_1 = tgMH_MUL_S_F32_04_1(uS1.m_vS_F32_04_1, tgMH_SET1_S_F32_04_1( (float)(uiIndex) / (float)uiMax_Value ));
            uS1.m_vS_F32_04_1 = tgMH_ADD_S_F32_04_1(uS1.m_vS_F32_04_1,avGraph_Points[0]);

            tgKN_GPU__CMD__Render_Debug_Line( uCMD, uS0.m_vF32_04_1, avColour[(uiPM+2u)%TgARRAY_COUNT(avColour)], uS1.m_vF32_04_1,
                                              avColour[(uiPM+3u)%TgARRAY_COUNT(avColour)], &s_sLineConstantBuffer );

            uS0.m_vS_F32_04_1 = tgMH_SUB_S_F32_04_1(avGraph_Points[2],avGraph_Points[0]);
            uS0.m_vS_F32_04_1 = tgMH_MUL_S_F32_04_1(uS0.m_vS_F32_04_1, tgMH_SET1_S_F32_04_1( (float)(uiMax_Value - uiIndex) / (float)uiMax_Value ));
            uS0.m_vS_F32_04_1 = tgMH_ADD_S_F32_04_1(uS0.m_vS_F32_04_1,avGraph_Points[0]);

            uS1.m_vS_F32_04_1 = tgMH_SUB_S_F32_04_1(avGraph_Points[3],avGraph_Points[0]);
            uS1.m_vS_F32_04_1 = tgMH_MUL_S_F32_04_1(uS1.m_vS_F32_04_1, tgMH_SET1_S_F32_04_1( (float)(uiIndex) / (float)uiMax_Value ));
            uS1.m_vS_F32_04_1 = tgMH_ADD_S_F32_04_1(uS1.m_vS_F32_04_1,avGraph_Points[0]);

            tgKN_GPU__CMD__Render_Debug_Line( uCMD, uS0.m_vF32_04_1, avColour[(uiPM+2u)%TgARRAY_COUNT(avColour)], uS1.m_vF32_04_1,
                                              avColour[(uiPM+3u)%TgARRAY_COUNT(avColour)], &s_sLineConstantBuffer );
        }
        tgKN_GPU__CMD__Render_Debug_Line_Flush( uCMD, &s_sLineConstantBuffer );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif

    tgKN_GPU_EXT__CMD__Command_List_Close( uCMD );
    uCMD.ps = nullptr;
    tgKN_GPU_EXT__SwapChain__Present( tiCXT_WORK, tiCXT_SWAP );
    if (bEndFrame)
    {
        tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
    }
    return (KTgS_OK);

}


/* ---- tgUnit_Test__KN_GPU__Render_5 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgUnit_Test__KN_GPU__Render_5( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK )
{
    STg2_UT_KN_GPU_Swap_Resources_P     psSwap_Resource = s_saGPU_Swap_Resources + tiCXT_SWAP.m_uiI;
    TgBOOL                              bEndFrame = false;
    TgFLOAT32_C                         fInter_Cube_Space = 1.5F;

    STg2_KN_GPU_Render_Buffer           sRTBuffer, sDSBuffer;
    STg2_KN_GPU_HLSL_Output_DESC        sOutput_DESC;
    UTg2_KN_GPU_CMD                     uCMD;

    D3D12_GPU_VIRTUAL_ADDRESS           uiGpuAddress;
    D3D12_CONSTANT_BUFFER_VIEW_DESC     sDX12_KBV;

    bEndFrame = false;
    if (KTgKN_GPU_CXT_WORK_ID__INVALID.m_uiKI == tiCXT_WORK.m_uiKI)
    {
        tiCXT_WORK = tgKN_GPU_EXT__Execute__Frame_Start( tiCXT_EXEC );
        bEndFrame = true;
    }

    uCMD = tgUnit_Test__KN_GPU__Render_Background_And_Gradient( &sRTBuffer, &sDSBuffer, &sOutput_DESC, tiCXT_EXEC, tiCXT_SWAP, tiCXT_WORK );
    if (nullptr == uCMD.ps)
    {
        if (bEndFrame)
        {
            tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
        }
        return (KTgE_FAIL);
    }

    /* Create constant buffer views to access the upload buffer. */
    uiGpuAddress = ID3D12Resource_GetGPUVirtualAddress( psSwap_Resource->m_psDX12_CBV_Scene );
    sDX12_KBV.BufferLocation = uiGpuAddress;
    sDX12_KBV.SizeInBytes = c_alignedSceneConstantBufferSize;
    ID3D12Device10_CreateConstantBufferView( uCMD.psEXT->m_psDX12_Device, &sDX12_KBV, uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_sDX12_CPU_Handle );
    uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_sDX12_CPU_Handle.ptr += uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_uiDescriptor_Size;

    /* Create constant buffer views to access the upload buffer. */
    uiGpuAddress = ID3D12Resource_GetGPUVirtualAddress( psSwap_Resource->m_psDX12_CBV_Instance_Model );
    sDX12_KBV.BufferLocation = uiGpuAddress;
    sDX12_KBV.SizeInBytes = c_alignedModelConstantBufferInstanceSize;
    ID3D12Device10_CreateConstantBufferView( uCMD.psEXT->m_psDX12_Device, &sDX12_KBV, uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_sDX12_CPU_Handle );
    uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_sDX12_CPU_Handle.ptr += uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_uiDescriptor_Size;

    /* Create constant buffer views to access the upload buffer. */
    uiGpuAddress = ID3D12Resource_GetGPUVirtualAddress( psSwap_Resource->m_psDX12_CBV_Model_00 );
    sDX12_KBV.BufferLocation = uiGpuAddress;
    sDX12_KBV.SizeInBytes = c_alignedModelConstantBufferSize;
    ID3D12Device10_CreateConstantBufferView( uCMD.psEXT->m_psDX12_Device, &sDX12_KBV, uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_sDX12_CPU_Handle );
    uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_sDX12_CPU_Handle.ptr += uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_uiDescriptor_Size;

    /* Create constant buffer views to access the upload buffer. */
    uiGpuAddress = ID3D12Resource_GetGPUVirtualAddress( psSwap_Resource->m_psDX12_CBV_Model_01 );
    sDX12_KBV.BufferLocation = uiGpuAddress;
    sDX12_KBV.SizeInBytes = c_alignedModelConstantBufferSize;
    ID3D12Device10_CreateConstantBufferView( uCMD.psEXT->m_psDX12_Device, &sDX12_KBV, uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_sDX12_CPU_Handle );
    uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_sDX12_CPU_Handle.ptr += uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_uiDescriptor_Size;

    /* Set the Scene Constant Buffer */
    tgUnit_Test__KN_GPU__Setup_Scene_Constant_Buffer( &sOutput_DESC, &sRTBuffer );

    {
        UINT8*                              puiMappedConstantBuffer;
        D3D12_RANGE                         sRead_Range;
        TgRSIZE                             uiModel;
        TgVEC_S_F32_04_4                    mTranslation, mRotation, mTemp, mTranslation2;

        /* Constant buffer for sixty-four cubes using a Triangle List. */

        tgMH_CLI_S_F32_04_4( &mTranslation );
        tgMH_CLI_S_F32_04_4( &mRotation );
        tgMH_CLI_S_F32_04_4( &mTranslation2 );

        s_sModelConstantBufferInstance.m_sDESC = sOutput_DESC;
        tgMM_Copy( &s_sModelConstantBufferInstance.m_mW2C, sizeof(s_sModelConstantBufferInstance.m_mW2C), &s_sSceneConstantBuffer.m_mW2C, sizeof(s_sSceneConstantBuffer.m_mW2C) );
        tgMM_Copy( &s_sModelConstantBufferInstance.m_mC2S, sizeof(s_sModelConstantBufferInstance.m_mC2S), &s_sSceneConstantBuffer.m_mC2S, sizeof(s_sSceneConstantBuffer.m_mC2S) );

        for (uiModel= 0; uiModel < 64; ++uiModel)
        {

            mTranslation._41 = fInter_Cube_Space * ((TgFLOAT32)(uiModel % 4) - 1.5F);
            mTranslation._42 = fInter_Cube_Space * ((TgFLOAT32)((uiModel / 4) % 4) - 1.5F);
            mTranslation._43 = fInter_Cube_Space * ((TgFLOAT32)(uiModel / 16) - 1.5F);

            tgMH_Set_Euler_ELEM_S_F32_04_4( &mRotation,
                -45.0f * KTgPI_F32 / 180.0f * tgTM_Query_Time() * 0.0005F,
                 45.0f * KTgPI_F32 / 180.0f,
                 45.0f * KTgPI_F32 / 180.0f );
            tgMH_CAT_S_F32_04_4( &mTemp, &mTranslation, &mRotation );
            tgMH_CAT_S_F32_04_4( &s_sModelConstantBufferInstance.m_vModel_Transform[uiModel], &mTemp, &mTranslation2 );

            s_sModelConstantBufferInstance.m_vModel_Colour[uiModel].r = 0.1F + 0.3F * (TgFLOAT32)((uiModel / 1) % 4);
            s_sModelConstantBufferInstance.m_vModel_Colour[uiModel].r *= s_sModelConstantBufferInstance.m_vModel_Colour[uiModel].r;
            s_sModelConstantBufferInstance.m_vModel_Colour[uiModel].g = 0.1F + 0.3F * (TgFLOAT32)((uiModel / 4) % 4);
            s_sModelConstantBufferInstance.m_vModel_Colour[uiModel].g *= s_sModelConstantBufferInstance.m_vModel_Colour[uiModel].g;
            s_sModelConstantBufferInstance.m_vModel_Colour[uiModel].b = 0.1F + 0.3F * (TgFLOAT32)((uiModel / 16) % 4);
            s_sModelConstantBufferInstance.m_vModel_Colour[uiModel].b *= s_sModelConstantBufferInstance.m_vModel_Colour[uiModel].b;
            s_sModelConstantBufferInstance.m_vModel_Colour[uiModel].a = 1.0F;
        }

        TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psSwap_Resource->m_psDX12_CBV_Scene, 0, &sRead_Range, (TgVOID_PP)&puiMappedConstantBuffer )));
        tgMM_Copy( puiMappedConstantBuffer, c_alignedSceneConstantBufferSize, &s_sSceneConstantBuffer, sizeof( s_sSceneConstantBuffer ) );
        ID3D12Resource_Unmap( psSwap_Resource->m_psDX12_CBV_Scene, 0, &sRead_Range );

        TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psSwap_Resource->m_psDX12_CBV_Instance_Model, 0, &sRead_Range, (TgVOID_PP)&puiMappedConstantBuffer )));
        tgMM_Copy( puiMappedConstantBuffer, c_alignedModelConstantBufferInstanceSize, &s_sModelConstantBufferInstance, sizeof( s_sModelConstantBufferInstance ) );
        ID3D12Resource_Unmap( psSwap_Resource->m_psDX12_CBV_Instance_Model, 0, &sRead_Range );
    }

    /* Draw sixty-four Cubes with a Triangle List. */
    #if TgCOMPILE__RENDER_DEBUG_OUTPUT
    {
        tgKN_GPU_EXT__CMD__Set_Graphics_Root_Signature_From_Default( uCMD, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_UNIT_TEST );
        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw Cube (Instanced, List)" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_UNIT_TEST_SCENE, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );
        ID3D12GraphicsCommandList8_SetGraphicsRootConstantBufferView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 2,
                                                                      ID3D12Resource_GetGPUVirtualAddress( psSwap_Resource->m_psDX12_CBV_Scene ) );
        tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance( uCMD, ETgKN_GPU_DEBUG_PM_3D_BOX, 64, &s_sModelConstantBufferInstance );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
        tgKN_GPU_EXT__CMD__Set_Graphics_Root_Signature_From_Default( uCMD, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG );
    }
    #endif

    /* Draw two spheres using debug draw routines. */
    #if TgCOMPILE__RENDER_DEBUG_OUTPUT
    {
        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw Two Debug Sphere" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_02_INSTANCE, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );
        s_sModelConstantBufferInstance.m_sDESC = sOutput_DESC;
        tgMM_Copy( &s_sModelConstantBufferInstance.m_mW2C, sizeof(s_sModelConstantBufferInstance.m_mW2C), &s_sSceneConstantBuffer.m_mW2C, sizeof(s_sSceneConstantBuffer.m_mW2C) );
        tgMM_Copy( &s_sModelConstantBufferInstance.m_mC2S, sizeof(s_sModelConstantBufferInstance.m_mC2S), &s_sSceneConstantBuffer.m_mC2S, sizeof(s_sSceneConstantBuffer.m_mC2S) );
        s_sModelConstantBufferInstance.m_vLight_Ambient = tgMH_Init_ELEM_S_F32_04_1( 0.1F, 0.1F, 0.1F, 1.0F );
        s_sModelConstantBufferInstance.m_vLight_Direction = tgMH_Init_ELEM_S_F32_04_1( -1.0F/1.73205081F, 1.0F/1.73205081F, -1.0F/1.73205081F, 0.0F );
        s_sModelConstantBufferInstance.m_vLight_Direction_Colour = tgMH_Init_ELEM_S_F32_04_1( 0.4F, 0.6F, 0.6F, 1.0F );
        s_sModelConstantBufferInstance.m_vModel_Colour[0] = tgMH_Init_ELEM_S_F32_04_1( 2.0F, 2.0F, 2.0F, 1.0F );
        tgMH_CLI_S_F32_04_4( s_sModelConstantBufferInstance.m_vModel_Transform + 0 );
        s_sModelConstantBufferInstance.m_vModel_Transform[0]._41 = s_sSceneConstantBuffer.scene_lights[0].origin_and_range.x;
        s_sModelConstantBufferInstance.m_vModel_Transform[0]._42 = s_sSceneConstantBuffer.scene_lights[0].origin_and_range.y;
        s_sModelConstantBufferInstance.m_vModel_Transform[0]._43 = s_sSceneConstantBuffer.scene_lights[0].origin_and_range.z;
        s_sModelConstantBufferInstance.m_vModel_Colour[1] = tgMH_Init_ELEM_S_F32_04_1( 2.0F, 2.0F, 2.0F, 1.0F );
        tgMH_CLI_S_F32_04_4( s_sModelConstantBufferInstance.m_vModel_Transform + 1 );
        s_sModelConstantBufferInstance.m_vModel_Transform[1]._41 = s_sSceneConstantBuffer.scene_lights[1].origin_and_range.x;
        s_sModelConstantBufferInstance.m_vModel_Transform[1]._42 = s_sSceneConstantBuffer.scene_lights[1].origin_and_range.y;
        s_sModelConstantBufferInstance.m_vModel_Transform[1]._43 = s_sSceneConstantBuffer.scene_lights[1].origin_and_range.z;
        tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance( uCMD, ETgKN_GPU_DEBUG_PM_3D_SPHERE, 2, &s_sModelConstantBufferInstance );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif

    tgKN_GPU_EXT__CMD__Command_List_Close( uCMD );
    uCMD.psEXT = nullptr;
    tgKN_GPU_EXT__SwapChain__Present( tiCXT_WORK, tiCXT_SWAP );
    if (bEndFrame)
    {
        tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
    }
    return (KTgS_OK);
}


/* ---- tgUnit_Test__KN_GPU__Setup_Scene_Constant_Buffer ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgUnit_Test__KN_GPU__Setup_Scene_Constant_Buffer( STg2_KN_GPU_HLSL_Output_DESC_CPCU psOutput_DESC, STg2_KN_GPU_Render_Buffer_CPCU psRTBuffer )
{
    TgFLOAT32_C                         fInter_Cube_Space = 1.5F;
    TgFLOAT32_C                         fRadius = 1.73205081F * (2.0F * fInter_Cube_Space + 0.5F);
    TgFLOAT32_C                         fAspect_Ratio = (float)psRTBuffer->m_uiWidth / (float)psRTBuffer->m_uiHeight;
    TgFLOAT32_C                         fFoV = 35.0F * KTgPI_F32 / 180.0f;
    TgFLOAT32_C                         fFoVy = 1.0F / tgPM_TAN_F32( 0.5F * fFoV );
    TgFLOAT32_C                         fFoVx = fFoVy / fAspect_Ratio;
    TgFLOAT32_C                         fZR = 100.0F - 0.01F;
    TgFLOAT32_C                         fFoVz = 100.0F / fZR;

    TgFLOAT32                           fModelX, fModelY;
    TgVEC_S_F32_04_4                    mModel_Transform[2];
    D3D12_RANGE                         sRead_Range;
    TgVEC_S_F32_04_1                    vEye, vAt, vUp;
    TgFLOAT32                           fCam_Dist_Max;
    TgVEC_S_F32_04_4                    mS2C;
    TgVEC_S_F32_04_1                    vNNP;
    TgVEC_S_F32_04_4                    mTranslation, mRotation, mTemp, mTranslation2;

    tgMM_Set_U08_0x00( &sRead_Range, sizeof( sRead_Range ) );

    tgMH_CLI_S_F32_04_4( &mTranslation );
    tgMH_CLI_S_F32_04_4( &mRotation );
    tgMH_CLI_S_F32_04_4( &mTranslation2 );

    tgMH_CLR_S_F32_04_4(&s_sSceneConstantBuffer.m_mC2S);

    if (fAspect_Ratio < 1.0F)
    {
        s_sSceneConstantBuffer.m_mC2S._11 = fFoVy / fAspect_Ratio;
        s_sSceneConstantBuffer.m_mC2S._22 = fFoVx * fAspect_Ratio;
    }
    else
    {
        s_sSceneConstantBuffer.m_mC2S._11 = fFoVx;
        s_sSceneConstantBuffer.m_mC2S._22 = fFoVy;
    }
    s_sSceneConstantBuffer.m_mC2S._33 = fFoVz;
    s_sSceneConstantBuffer.m_mC2S._34 = 1.0F;
    s_sSceneConstantBuffer.m_mC2S._43 = -fFoVz * 0.01F;

    tgMH_INV_S_F32_04_4( &mS2C, &s_sSceneConstantBuffer.m_mC2S );
    vNNP = tgMH_TX_S_F32_04_4( tgMH_Init_Point_ELEM_S_F32_04_1( -1.0F, -1.0F, +1.0F ), &mS2C );
    vNNP = tgMH_DIV_S_F32_04_1( vNNP, tgMH_SET1_S_F32_04_1(vNNP.w) );

    if (fAspect_Ratio < 1.0F)
    {
        fCam_Dist_Max = 100.0F * fRadius / fAspect_Ratio / -vNNP.y;
        fModelX = fModelY = 0.0F;
    }
    else
    {
        TgFLOAT32_C                         fF0 = 3.0F * (2.0F * fRadius) + 2.0f*(2.0F*fRadius*tgPM_COS_F32(0.5F*KTgPI_F32 - 0.5F*fFoV) - fRadius);

        fCam_Dist_Max = 100.0F * 0.5F * fF0 / -vNNP.y;
        fModelX = -vNNP.x * fCam_Dist_Max / 100.0F - fRadius;
        fModelY = -vNNP.y * fCam_Dist_Max / 100.0F - fRadius;
    };

    vEye = tgMH_Init_Point_ELEM_S_F32_04_1( 0.0F, fCam_Dist_Max, 0.0F );
    vAt = tgMH_Init_Point_ELEM_S_F32_04_1( 0.0F, 0.0f, 0.0F );
    vUp = tgMH_Init_Vector_ELEM_S_F32_04_1( 0.0f, 1.0f, 0.0f );

    tgMH_LookLH_S_F32_04_4( &s_sSceneConstantBuffer.m_mW2C, vEye, vAt, vUp );

    s_sSceneConstantBuffer.scene_light_ambient.r = 0.1F;
    s_sSceneConstantBuffer.scene_light_ambient.g = 0.1F;
    s_sSceneConstantBuffer.scene_light_ambient.b = 0.1F;
    s_sSceneConstantBuffer.scene_light_ambient.a = 1.0F;

    s_sSceneConstantBuffer.scene_lights[0].colour.r = psOutput_DESC->m_bHDR_Enabled ? 3.0F : 1.0F;
    s_sSceneConstantBuffer.scene_lights[0].colour.g = psOutput_DESC->m_bHDR_Enabled ? 3.0F : 1.0F;
    s_sSceneConstantBuffer.scene_lights[0].colour.b = psOutput_DESC->m_bHDR_Enabled ? 3.0F : 1.0F;
    s_sSceneConstantBuffer.scene_lights[0].colour.a = 1.0F;

    s_sSceneConstantBuffer.scene_lights[1].colour.r = psOutput_DESC->m_bHDR_Enabled ? 3.0F : 1.0F;
    s_sSceneConstantBuffer.scene_lights[1].colour.g = psOutput_DESC->m_bHDR_Enabled ? 3.0F : 1.0F;
    s_sSceneConstantBuffer.scene_lights[1].colour.b = psOutput_DESC->m_bHDR_Enabled ? 3.0F : 1.0F;
    s_sSceneConstantBuffer.scene_lights[1].colour.a = 1.0F;

    mTranslation2._41 = fModelY;
    mTranslation2._42 = 0.0F;
    mTranslation2._43 = fModelX;

    /* Constant buffer for two emissive cubes using a Triangle Strip. */

    s_sSceneConstantBuffer.scene_num_lights = 2;

    mTranslation._11 = 1.0f;
    mTranslation._22 = 1.0f;
    mTranslation._33 = 1.0f;
    mTranslation._41 = fRadius;

    tgMH_Set_Euler_ELEM_S_F32_04_4( &mRotation,
            45.0f * KTgPI_F32 / 180.0f,
            45.0f * KTgPI_F32 / 180.0f * tgTM_Query_Time() * 0.005F,
            0.0F );
    tgMH_CAT_S_F32_04_4( &mTemp, &mTranslation, &mRotation );
    tgMH_CAT_S_F32_04_4( mModel_Transform + 0, &mTemp, &mTranslation2 );

    s_sSceneConstantBuffer.scene_lights[0].origin_and_range.x = mModel_Transform[0]._41;
    s_sSceneConstantBuffer.scene_lights[0].origin_and_range.y = mModel_Transform[0]._42;
    s_sSceneConstantBuffer.scene_lights[0].origin_and_range.z = mModel_Transform[0]._43;
    s_sSceneConstantBuffer.scene_lights[0].origin_and_range.w = 6.0F;

    mTranslation._41 = -mTranslation._41;
    tgMH_CAT_S_F32_04_4( &mTemp, &mTranslation, &mRotation );
    tgMH_CAT_S_F32_04_4( mModel_Transform + 1, &mTemp, &mTranslation2 );

    s_sSceneConstantBuffer.scene_lights[1].origin_and_range.x = mModel_Transform[1]._41;
    s_sSceneConstantBuffer.scene_lights[1].origin_and_range.y = mModel_Transform[1]._42;
    s_sSceneConstantBuffer.scene_lights[1].origin_and_range.z = mModel_Transform[1]._43;
    s_sSceneConstantBuffer.scene_lights[1].origin_and_range.w = 6.0F;
}
