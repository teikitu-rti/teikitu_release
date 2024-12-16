//*********************************************************
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License (MIT).
//
//*********************************************************

#ifndef __D3DX12_H__
#define __D3DX12_H__

#include "d3d12.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
#include "d3dx12_cplusplus.h"
#else

//------------------------------------------------------------------------------------------------
static inline void D3DX12ResourceDescBuffer(
    _Out_ D3D12_RESOURCE_DESC* pResourceX,
    UINT64 width )
{
    pResourceX->Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    pResourceX->Alignment = 0;
    pResourceX->Width = width;
    pResourceX->Height = 1;
    pResourceX->DepthOrArraySize = 1;
    pResourceX->MipLevels = 1;
    pResourceX->Format = DXGI_FORMAT_UNKNOWN;
    pResourceX->SampleDesc.Count = 1;
    pResourceX->SampleDesc.Quality = 0;
    pResourceX->Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    pResourceX->Flags = D3D12_RESOURCE_FLAG_NONE;
}

static inline void D3DX12ResourceDescTex1D(
    _Out_ D3D12_RESOURCE_DESC* pResourceX,
    DXGI_FORMAT format,
    UINT64 width )
{
    pResourceX->Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE1D;
    pResourceX->Alignment = 0;
    pResourceX->Width = width;
    pResourceX->Height = 1;
    pResourceX->DepthOrArraySize = 1;
    pResourceX->MipLevels = 0;
    pResourceX->Format = format;
    pResourceX->SampleDesc.Count = 1;
    pResourceX->SampleDesc.Quality = 0;
    pResourceX->Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    pResourceX->Flags = D3D12_RESOURCE_FLAG_NONE;
}

static inline void D3DX12ResourceDescTex2D(
    _Out_ D3D12_RESOURCE_DESC* pResourceX,
    DXGI_FORMAT format,
    UINT64 width,
    UINT height )
{
    pResourceX->Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    pResourceX->Alignment = 0;
    pResourceX->Width = width;
    pResourceX->Height = height;
    pResourceX->DepthOrArraySize = 1;
    pResourceX->MipLevels = 0;
    pResourceX->Format = format;
    pResourceX->SampleDesc.Count = 1;
    pResourceX->SampleDesc.Quality = 0;
    pResourceX->Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    pResourceX->Flags = D3D12_RESOURCE_FLAG_NONE;
}

static inline void D3DX12ResourceDescTex3D(
    _Out_ D3D12_RESOURCE_DESC* pResourceX,
    DXGI_FORMAT format,
    UINT64 width,
    UINT height,
    UINT16 depth )
{
    pResourceX->Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
    pResourceX->Alignment = 0;
    pResourceX->Width = width;
    pResourceX->Height = height;
    pResourceX->DepthOrArraySize = depth;
    pResourceX->MipLevels = 0;
    pResourceX->Format = format;
    pResourceX->SampleDesc.Count = 1;
    pResourceX->SampleDesc.Quality = 0;
    pResourceX->Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    pResourceX->Flags = D3D12_RESOURCE_FLAG_NONE;
}

/* -------------------------------------------------------------------------------- */
static inline bool D3DX12HeapPropertiesIsCPUAccessible(
    _In_ D3D12_HEAP_PROPERTIES *pHeap_Property )
{
    return (pHeap_Property->Type == D3D12_HEAP_TYPE_UPLOAD ||
            pHeap_Property->Type == D3D12_HEAP_TYPE_READBACK ||
            (
                pHeap_Property->Type == D3D12_HEAP_TYPE_CUSTOM &&
                (
                    pHeap_Property->CPUPageProperty == D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE ||
                    pHeap_Property->CPUPageProperty == D3D12_CPU_PAGE_PROPERTY_WRITE_BACK
                )
            ));
}


/* -------------------------------------------------------------------------------- */
static inline void D3DX12_TEXTURE_COPY_LOCATION_Init_Footprint(
    _Out_ D3D12_TEXTURE_COPY_LOCATION *pTex_Copy,
    ID3D12Resource* pRes,
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT const *pFootprint )
{
    pTex_Copy->pResource = pRes;
    pTex_Copy->Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
    pTex_Copy->PlacedFootprint = *pFootprint;
}

static inline void D3DX12_TEXTURE_COPY_LOCATION_Init_Sub_Resource(
    _Out_ D3D12_TEXTURE_COPY_LOCATION *pTex_Copy,
    ID3D12Resource* pRes,
    UINT Sub )
{
    pTex_Copy->pResource = pRes;
    pTex_Copy->Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    pTex_Copy->SubresourceIndex = Sub;
}

///* -------------------------------------------------------------------------------- */
//
//TgINLINE TgVOID D3DX12_RESOURCE_DESC_Buffer_From_AllococationInfo(
//    _Out_ D3D12_RESOURCE_DESC* pResourceX,
//    const D3D12_RESOURCE_ALLOCATION_INFO *pResAllocInfo )
//{
//    pResourceX->Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
//    pResourceX->Alignment = pResAllocInfo->Alignment;
//    pResourceX->Width = pResAllocInfo->SizeInBytes;
//    pResourceX->Height = 1;
//    pResourceX->DepthOrArraySize = 1;
//    pResourceX->MipLevels = 1;
//    pResourceX->Format = DXGI_FORMAT_UNKNOWN;
//    pResourceX->SampleDesc.Count = 1;
//    pResourceX->SampleDesc.Quality = 0;
//    pResourceX->Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
//    pResourceX->Flags = D3D12_RESOURCE_FLAG_NONE;
//}
//

//TgINLINE UINT16 D3DX12_RESOURCE_DESC_Depth( _In_ const D3D12_RESOURCE_DESC* pResourceX )
//{
//    return (pResourceX->Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE3D ? pResourceX->DepthOrArraySize : 1u);
//}
//
//TgINLINE UINT16 D3DX12_RESOURCE_DESC_ArraySize( _In_ const D3D12_RESOURCE_DESC* pResourceX )
//{
//    return (pResourceX->Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE3D ? pResourceX->DepthOrArraySize : 1u);
//}
//
//TgINLINE UINT8 D3DX12_RESOURCE_DESC_PlaneCount( _In_ const D3D12_RESOURCE_DESC* pResourceX, _In_ ID3D12Device* pDevice )
//{
//    return D3D12GetFormatPlaneCount(pDevice, pResourceX->Format);
//}
//
//TgINLINE UINT D3DX12_RESOURCE_DESC_Subresources( _In_ const D3D12_RESOURCE_DESC* pResourceX, _In_ ID3D12Device* pDevice )
//{
//    return (UINT)(pResourceX->MipLevels * D3DX12_RESOURCE_DESC_ArraySize( pResourceX ) * D3DX12_RESOURCE_DESC_PlaneCount( pResourceX, pDevice ));
//}
//
//TgINLINE UINT D3DX12_RESOURCE_DESC_CalcSubresource( _In_ D3D12_RESOURCE_DESC* pResourceX, UINT MipSlice, UINT ArraySlice, UINT PlaneSlice )
//{
//    return D3D12CalcSubresource(MipSlice, ArraySlice, PlaneSlice, pResourceX->MipLevels, D3DX12_RESOURCE_DESC_ArraySize( pResourceX ));
//}
//
//
///* -------------------------------------------------------------------------------- */
//TgINLINE TgVOID _CD3DX12_DESCRIPTOR_RANGE_Init(
//    _Out_ D3D12_DESCRIPTOR_RANGE *pRange,
//    D3D12_DESCRIPTOR_RANGE_TYPE rangeType,
//    UINT numDescriptors,
//    UINT baseShaderRegister )
//{
//    pRange->RangeType = rangeType;
//    pRange->NumDescriptors = numDescriptors;
//    pRange->BaseShaderRegister = baseShaderRegister;
//    pRange->RegisterSpace = 0;
//    pRange->OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
//}
//
///* -------------------------------------------------------------------------------- */
//TgINLINE TgVOID _CD3DX12_ROOT_DESCRIPTOR_TABLE_Init(
//    _Out_ D3D12_ROOT_DESCRIPTOR_TABLE *pRootDescriptorTable,
//    UINT numDescriptorRanges,
//    _In_reads_opt_( numDescriptorRanges ) const D3D12_DESCRIPTOR_RANGE* _pDescriptorRanges )
//{
//    pRootDescriptorTable->NumDescriptorRanges = numDescriptorRanges;
//    pRootDescriptorTable->pDescriptorRanges = _pDescriptorRanges;
//}
//
///* -------------------------------------------------------------------------------- */
//TgINLINE TgVOID _CD3DX12_ROOT_CONSTANTS_Init(
//    _Out_ D3D12_ROOT_CONSTANTS *pRootConstants,
//    UINT num32BitValues,
//    UINT shaderRegister )
//{
//    pRootConstants->Num32BitValues = num32BitValues;
//    pRootConstants->ShaderRegister = shaderRegister;
//    pRootConstants->RegisterSpace = 0;
//}
//
///* -------------------------------------------------------------------------------- */
//TgINLINE TgVOID _CD3DX12_ROOT_DESCRIPTOR_Init(
//    _Out_ D3D12_ROOT_DESCRIPTOR *pTable,
//    UINT shaderRegister )
//{
//    pTable->ShaderRegister = shaderRegister;
//    pTable->RegisterSpace = 0;
//}
//
///* -------------------------------------------------------------------------------- */
//TgINLINE TgVOID _CD3DX12_ROOT_PARAMETER_InitAsDescriptorTable(
//    _Out_ D3D12_ROOT_PARAMETER *pRootParam,
//    UINT numDescriptorRanges,
//    _In_reads_(numDescriptorRanges) const D3D12_DESCRIPTOR_RANGE* pDescriptorRanges )
//{
//    pRootParam->ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
//    pRootParam->ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
//    _CD3DX12_ROOT_DESCRIPTOR_TABLE_Init( &pRootParam->DescriptorTable, numDescriptorRanges, pDescriptorRanges);
//}
//
//TgINLINE TgVOID _CD3DX12_ROOT_PARAMETER_InitAsConstants(
//    _Out_ D3D12_ROOT_PARAMETER *pRootParam,
//    UINT num32BitValues,
//    UINT shaderRegister )
//{
//    pRootParam->ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
//    pRootParam->ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
//    _CD3DX12_ROOT_CONSTANTS_Init( &pRootParam->Constants, num32BitValues, shaderRegister );
//}
//
//TgINLINE TgVOID _CD3DX12_ROOT_PARAMETER_InitAsConstantBufferView(
//    _Out_ D3D12_ROOT_PARAMETER *pRootParam,
//    UINT shaderRegister )
//{
//    pRootParam->ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
//    pRootParam->ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
//    _CD3DX12_ROOT_DESCRIPTOR_Init( &pRootParam->Descriptor, shaderRegister );
//}
//
//TgINLINE TgVOID _CD3DX12_ROOT_PARAMETER_InitAsShaderResourceView(
//    _Out_ D3D12_ROOT_PARAMETER *pRootParam,
//    UINT shaderRegister )
//{
//    pRootParam->ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV;
//    pRootParam->ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
//    _CD3DX12_ROOT_DESCRIPTOR_Init( &pRootParam->Descriptor, shaderRegister );
//}
//
//TgINLINE TgVOID _CD3DX12_ROOT_PARAMETER_InitAsUnorderedAccessView(
//    _Out_ D3D12_ROOT_PARAMETER *pRootParam,
//    UINT shaderRegister )
//{
//    pRootParam->ParameterType = D3D12_ROOT_PARAMETER_TYPE_UAV;
//    pRootParam->ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
//    _CD3DX12_ROOT_DESCRIPTOR_Init( &pRootParam->Descriptor, shaderRegister );
//}
//
///* -------------------------------------------------------------------------------- */
//TgINLINE TgVOID _CD3DX12_ROOT_SIGNATURE_DESC_Init(
//    _Out_ D3D12_ROOT_SIGNATURE_DESC *pDesc,
//    UINT numParameters,
//    _In_reads_opt_(numParameters) const D3D12_ROOT_PARAMETER* _pParameters )
//{
//    pDesc->NumParameters = numParameters;
//    pDesc->pParameters = _pParameters;
//    pDesc->NumStaticSamplers = 0;
//    pDesc->pStaticSamplers = nullptr;
//    pDesc->Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
//}
//
///* -------------------------------------------------------------------------------- */
//TgINLINE TgVOID _CD3DX12_SHADER_BYTECODE_Init_Blob(
//    _Out_ D3D12_SHADER_BYTECODE *pShader,
//    ID3DBlob* pShaderBlob )
//{
//    pShader->pShaderBytecode = ID3D10Blob_GetBufferPointer( pShaderBlob );
//    pShader->BytecodeLength = ID3D10Blob_GetBufferSize( pShaderBlob );
//}
//
//TgINLINE TgVOID _CD3DX12_SHADER_BYTECODE_Init_Shader_Code(
//    _Out_ D3D12_SHADER_BYTECODE *pShader,
//    void* _pShaderBytecode,
//    SIZE_T bytecodeLength )
//{
//    pShader->pShaderBytecode = _pShaderBytecode;
//    pShader->BytecodeLength = bytecodeLength;
//}
//
///* -------------------------------------------------------------------------------- */
//TgINLINE TgVOID _CD3DX12_DEPTH_STENCIL_DESC_Init_Default(
//    _Out_ D3D12_DEPTH_STENCIL_DESC *pDS )
//{
//    const D3D12_DEPTH_STENCILOP_DESC defaultStencilOp =
//    { D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS };
//
//    pDS->DepthEnable = TRUE;
//    pDS->DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
//    pDS->DepthFunc = D3D12_COMPARISON_FUNC_LESS;
//    pDS->StencilEnable = FALSE;
//    pDS->StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
//    pDS->StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
//    pDS->FrontFace = defaultStencilOp;
//    pDS->BackFace = defaultStencilOp;
//}

/* -------------------------------------------------------------------------------- */
static inline void D3DX12BlendDescInitDefault(
    _Out_ D3D12_BLEND_DESC *pBlend )
{
    const D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc =
    {
        FALSE,FALSE,
        D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
        D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
        D3D12_LOGIC_OP_NOOP,
        D3D12_COLOR_WRITE_ENABLE_ALL,
    };

    pBlend->AlphaToCoverageEnable = FALSE;
    pBlend->IndependentBlendEnable = FALSE;
    for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
        pBlend->RenderTarget[i] = defaultRenderTargetBlendDesc;
}

/* -------------------------------------------------------------------------------- */
static inline void D3DX12RasterizerDescInitDefault(
    _Out_ D3D12_RASTERIZER_DESC *pRast )
{
    pRast->FillMode = D3D12_FILL_MODE_SOLID;
    pRast->CullMode = D3D12_CULL_MODE_BACK;
    pRast->FrontCounterClockwise = FALSE;
    pRast->DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
    pRast->DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
    pRast->SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
    pRast->DepthClipEnable = TRUE;
    pRast->MultisampleEnable = FALSE;
    pRast->AntialiasedLineEnable = FALSE;
    pRast->ForcedSampleCount = 0;
    pRast->ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
}



//------------------------------------------------------------------------------------------------
// Row-by-row memcpy
inline void D3DX12MemcpySubresource(
    _In_ const D3D12_MEMCPY_DEST* pDest,
    _In_ const D3D12_SUBRESOURCE_DATA* pSrc,
    SIZE_T RowSizeInBytes,
    UINT NumRows,
    UINT NumSlices)
{
    for (UINT z = 0; z < NumSlices; ++z)
    {
        auto pDestSlice = (BYTE*)(pDest->pData) + pDest->SlicePitch * z;
        auto pSrcSlice = (const BYTE*)(pSrc->pData) + pSrc->SlicePitch * (LONG_PTR)(z);
        for (UINT y = 0; y < NumRows; ++y)
        {
            memcpy(pDestSlice + pDest->RowPitch * y,
                   pSrcSlice + pSrc->RowPitch * (LONG_PTR)(y),
                   RowSizeInBytes);
        }
    }
}

//------------------------------------------------------------------------------------------------
// Row-by-row memcpy
inline void D3DX12MemcpySubresourceWithSource(
    _In_ const D3D12_MEMCPY_DEST* pDest,
    _In_ const void* pResourceData,
    _In_ const D3D12_SUBRESOURCE_INFO* pSrc,
    SIZE_T RowSizeInBytes,
    UINT NumRows,
    UINT NumSlices)
{
    for (UINT z = 0; z < NumSlices; ++z)
    {
        auto pDestSlice = (BYTE*)(pDest->pData) + pDest->SlicePitch * z;
        auto pSrcSlice = ((const BYTE*)(pResourceData) + pSrc->Offset) + pSrc->DepthPitch * (ULONG_PTR)(z);
        for (UINT y = 0; y < NumRows; ++y)
        {
            memcpy(pDestSlice + pDest->RowPitch * y,
                pSrcSlice + pSrc->RowPitch * (ULONG_PTR)(y),
                RowSizeInBytes);
        }
    }
}

//------------------------------------------------------------------------------------------------
// Returns required size of a buffer to be used for data upload
inline UINT64 D3DX12GetRequiredIntermediateSize(
    _In_ ID3D12Resource* pDestinationResource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources)
{
    #if !defined(_WIN32)
        const auto Desc = ID3D12Resource_GetDesc(pDestinationResource);
    #else
        D3D12_RESOURCE_DESC Desc;
        ID3D12Resource_GetDesc(pDestinationResource, &Desc);
    #endif
    UINT64 RequiredSize = 0;

    ID3D12Device* pDevice = nullptr;
    ID3D12Resource_GetDevice(pDestinationResource, MS_REF IID_ID3D12Device, (void**)(&pDevice));
    ID3D12Device_GetCopyableFootprints(pDevice,&Desc, FirstSubresource, NumSubresources, 0, nullptr, nullptr, nullptr, &RequiredSize);
    ID3D12Device_Release(pDevice);

    return RequiredSize;
}

//------------------------------------------------------------------------------------------------
// All arrays must be populated (e.g. by calling GetCopyableFootprints)
inline UINT64 D3DX12UpdateSubresourcesRows(
    _In_ ID3D12GraphicsCommandList8* pCmdList,
    _In_ ID3D12Resource* pDestinationResource,
    _In_ ID3D12Resource* pIntermediate,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources,
    UINT64 RequiredSize,
    _In_reads_(NumSubresources) const D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts,
    _In_reads_(NumSubresources) const UINT* pNumRows,
    _In_reads_(NumSubresources) const UINT64* pRowSizesInBytes,
    _In_reads_(NumSubresources) const D3D12_SUBRESOURCE_DATA* pSrcData)
{
    // Minor validation
#if defined(_MSC_VER) || !defined(_WIN32)
    const auto IntermediateDesc = ID3D12Resource_GetDesc( pIntermediate );
    const auto DestinationDesc = ID3D12Resource_GetDesc( pDestinationResource );
#else
    D3D12_RESOURCE_DESC tmpDesc1,tmpDesc2;
    const auto& IntermediateDesc = *ID3D12Resource_GetDesc( pIntermediate, GetDesc(&tmpDesc1) );
    const auto& DestinationDesc = *ID3D12Resource_GetDesc( pDestinationResource, GetDesc(&tmpDesc2) );
#endif
    if (IntermediateDesc.Dimension != D3D12_RESOURCE_DIMENSION_BUFFER ||
        IntermediateDesc.Width < RequiredSize + pLayouts[0].Offset ||
        RequiredSize > (SIZE_T)(-1) ||
        (DestinationDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER &&
            (FirstSubresource != 0 || NumSubresources != 1)))
    {
        return 0;
    }

    BYTE* pData;
    HRESULT hr = ID3D12Resource_Map(pIntermediate,0, nullptr, (void**)(&pData));
    if (FAILED(hr))
    {
        return 0;
    }

    for (UINT i = 0; i < NumSubresources; ++i)
    {
        if (pRowSizesInBytes[i] > (SIZE_T)(-1)) return 0;
        D3D12_MEMCPY_DEST DestData = { pData + pLayouts[i].Offset, pLayouts[i].Footprint.RowPitch, (SIZE_T)(pLayouts[i].Footprint.RowPitch) * (SIZE_T)(pNumRows[i]) };
        __D3DX12_MemcpySubresource(&DestData, &pSrcData[i], (SIZE_T)(pRowSizesInBytes[i]), pNumRows[i], pLayouts[i].Footprint.Depth);
    }
    ID3D12Resource_Unmap(pIntermediate,0, nullptr);

    if (DestinationDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
    {
        ID3D12GraphicsCommandList8_CopyBufferRegion( pCmdList,
            pDestinationResource, 0, pIntermediate, pLayouts[0].Offset, pLayouts[0].Footprint.Width);
    }
    else
    {
        for (UINT i = 0; i < NumSubresources; ++i)
        {
            D3D12_TEXTURE_COPY_LOCATION Dst;
            D3D12_TEXTURE_COPY_LOCATION Src;

            D3DX12_TEXTURE_COPY_LOCATION_Init_Sub_Resource( &Dst, pDestinationResource, i + FirstSubresource );
            D3DX12_TEXTURE_COPY_LOCATION_Init_Footprint( &Src, pIntermediate, pLayouts + i );
            ID3D12GraphicsCommandList8_CopyTextureRegion(pCmdList,&Dst, 0, 0, 0, &Src, nullptr);
        }
    }
    return RequiredSize;
}

//------------------------------------------------------------------------------------------------
// All arrays must be populated (e.g. by calling GetCopyableFootprints)
inline UINT64 D3DX12UpdateSubresourcesRowsWithSource(
    _In_ ID3D12GraphicsCommandList8* pCmdList,
    _In_ ID3D12Resource* pDestinationResource,
    _In_ ID3D12Resource* pIntermediate,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources,
    UINT64 RequiredSize,
    _In_reads_(NumSubresources) const D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts,
    _In_reads_(NumSubresources) const UINT* pNumRows,
    _In_reads_(NumSubresources) const UINT64* pRowSizesInBytes,
    _In_ const void* pResourceData,
    _In_reads_(NumSubresources) const D3D12_SUBRESOURCE_INFO* pSrcData)
{
    // Minor validation
#if defined(_MSC_VER) || !defined(_WIN32)
    const auto IntermediateDesc = ID3D12Resource_GetDesc( pIntermediate );
    const auto DestinationDesc = ID3D12Resource_GetDesc( pDestinationResource );
#else
    D3D12_RESOURCE_DESC tmpDesc1,tmpDesc2;
    const auto& IntermediateDesc = *ID3D12Resource_GetDesc( pIntermediate, GetDesc(&tmpDesc1) );
    const auto& DestinationDesc = *ID3D12Resource_GetDesc( pDestinationResource, GetDesc(&tmpDesc2) );
#endif
    if (IntermediateDesc.Dimension != D3D12_RESOURCE_DIMENSION_BUFFER ||
        IntermediateDesc.Width < RequiredSize + pLayouts[0].Offset ||
        RequiredSize > (SIZE_T)(-1) ||
        (DestinationDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER &&
            (FirstSubresource != 0 || NumSubresources != 1)))
    {
        return 0;
    }

    BYTE* pData;
    HRESULT hr = ID3D12Resource_Map(pIntermediate,0, nullptr, (void**)(&pData));
    if (FAILED(hr))
    {
        return 0;
    }

    for (UINT i = 0; i < NumSubresources; ++i)
    {
        if (pRowSizesInBytes[i] > (SIZE_T)(-1)) return 0;
        D3D12_MEMCPY_DEST DestData = { pData + pLayouts[i].Offset, pLayouts[i].Footprint.RowPitch, (SIZE_T)(pLayouts[i].Footprint.RowPitch) * (SIZE_T)(pNumRows[i]) };
        D3DX12MemcpySubresourceWithSource(&DestData, pResourceData, &pSrcData[i], (SIZE_T)(pRowSizesInBytes[i]), pNumRows[i], pLayouts[i].Footprint.Depth);
    }
    ID3D12Resource_Unmap(pIntermediate,0, nullptr);

    if (DestinationDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
    {
        ID3D12GraphicsCommandList8_CopyBufferRegion(pCmdList,
            pDestinationResource, 0, pIntermediate, pLayouts[0].Offset, pLayouts[0].Footprint.Width);
    }
    else
    {
        for (UINT i = 0; i < NumSubresources; ++i)
        {
            D3D12_TEXTURE_COPY_LOCATION Dst;
            D3D12_TEXTURE_COPY_LOCATION Src;

            D3DX12_TEXTURE_COPY_LOCATION_Init_Sub_Resource( &Dst, pDestinationResource, i + FirstSubresource );
            D3DX12_TEXTURE_COPY_LOCATION_Init_Footprint( &Src, pIntermediate, pLayouts + i );
            ID3D12GraphicsCommandList8_CopyTextureRegion(pCmdList,&Dst, 0, 0, 0, &Src, nullptr);
        }
    }
    return RequiredSize;
}

//------------------------------------------------------------------------------------------------
// Heap-allocating UpdateSubresources implementation
inline UINT64 D3DX12UpdateSubresources(
    _In_ ID3D12GraphicsCommandList8* pCmdList,
    _In_ ID3D12Resource* pDestinationResource,
    _In_ ID3D12Resource* pIntermediate,
    UINT64 IntermediateOffset,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources,
    _In_reads_(NumSubresources) const D3D12_SUBRESOURCE_DATA* pSrcData)
{
    UINT64 RequiredSize = 0;
    const auto MemToAlloc = (UINT64)(sizeof(D3D12_PLACED_SUBRESOURCE_FOOTPRINT) + sizeof(UINT) + sizeof(UINT64)) * NumSubresources;
    if (MemToAlloc > SIZE_MAX)
    {
       return 0;
    }
    void* pMem = HeapAlloc(GetProcessHeap(), 0, (SIZE_T)(MemToAlloc));
    if (pMem == nullptr)
    {
       return 0;
    }
    auto pLayouts = (D3D12_PLACED_SUBRESOURCE_FOOTPRINT*)(pMem);
    auto pRowSizesInBytes = (UINT64*)(pLayouts + NumSubresources);
    auto pNumRows = (UINT*)(pRowSizesInBytes + NumSubresources);

#if !defined(_WIN32)
    const auto Desc = ID3D12Resource_GetDesc(pDestinationResource);
#else
    D3D12_RESOURCE_DESC Desc;
    ID3D12Resource_GetDesc(pDestinationResource, &Desc);
#endif
    ID3D12Device* pDevice = nullptr;
    ID3D12Resource_GetDevice(pDestinationResource, MS_REF IID_ID3D12Device, (void**)(&pDevice));
    ID3D12Device_GetCopyableFootprints(pDevice,&Desc, FirstSubresource, NumSubresources, IntermediateOffset, pLayouts, pNumRows, pRowSizesInBytes, &RequiredSize);
    ID3D12Device_Release(pDevice);

    const UINT64 Result = __D3DX12_UpdateSubresources_Rows(pCmdList, pDestinationResource, pIntermediate, FirstSubresource, NumSubresources, RequiredSize, pLayouts,
                                                           pNumRows, pRowSizesInBytes, pSrcData);
    HeapFree(GetProcessHeap(), 0, pMem);
    return Result;
}

//------------------------------------------------------------------------------------------------
// Heap-allocating UpdateSubresources implementation
inline UINT64 D3DX12UpdateSubresourcesWithSource(
    _In_ ID3D12GraphicsCommandList8* pCmdList,
    _In_ ID3D12Resource* pDestinationResource,
    _In_ ID3D12Resource* pIntermediate,
    UINT64 IntermediateOffset,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources,
    _In_ const void* pResourceData,
    _In_reads_(NumSubresources) const D3D12_SUBRESOURCE_INFO* pSrcData)
{
    UINT64 RequiredSize = 0;
    const auto MemToAlloc = (UINT64)(sizeof(D3D12_PLACED_SUBRESOURCE_FOOTPRINT) + sizeof(UINT) + sizeof(UINT64)) * NumSubresources;
    if (MemToAlloc > SIZE_MAX)
    {
        return 0;
    }
    void* pMem = HeapAlloc(GetProcessHeap(), 0, (SIZE_T)(MemToAlloc));
    if (pMem == nullptr)
    {
        return 0;
    }
    auto pLayouts = (D3D12_PLACED_SUBRESOURCE_FOOTPRINT*)(pMem);
    auto pRowSizesInBytes = (UINT64*)(pLayouts + NumSubresources);
    auto pNumRows = (UINT*)(pRowSizesInBytes + NumSubresources);

#if !defined(_WIN32)
    const auto Desc = ID3D12Resource_GetDesc(pDestinationResource);
#else
    D3D12_RESOURCE_DESC Desc;
    ID3D12Resource_GetDesc(pDestinationResource, &Desc);
#endif
    ID3D12Device* pDevice = nullptr;
    ID3D12Resource_GetDevice(pDestinationResource, MS_REF IID_ID3D12Device, (void**)(&pDevice));
    ID3D12Device_GetCopyableFootprints(pDevice,&Desc, FirstSubresource, NumSubresources, IntermediateOffset, pLayouts, pNumRows, pRowSizesInBytes, &RequiredSize);
    ID3D12Device_Release(pDevice);

    const UINT64 Result = D3DX12UpdateSubresourcesRowsWithSource( pCmdList, pDestinationResource, pIntermediate, FirstSubresource, NumSubresources, RequiredSize, pLayouts,
                                                                  pNumRows, pRowSizesInBytes, pResourceData, pSrcData);
    HeapFree(GetProcessHeap(), 0, pMem);
    return Result;
}

//------------------------------------------------------------------------------------------------
// Row-by-row memcpy
inline void MemcpySubresource(
    _In_ const D3D12_MEMCPY_DEST* pDest,
    _In_ const D3D12_SUBRESOURCE_DATA* pSrc,
    SIZE_T RowSizeInBytes,
    UINT NumRows,
    UINT NumSlices) noexcept
{
    for (UINT z = 0; z < NumSlices; ++z)
    {
        auto pDestSlice = static_cast<BYTE*>(pDest->pData) + pDest->SlicePitch * z;
        auto pSrcSlice = static_cast<const BYTE*>(pSrc->pData) + pSrc->SlicePitch * LONG_PTR(z);
        for (UINT y = 0; y < NumRows; ++y)
        {
            memcpy(pDestSlice + pDest->RowPitch * y,
                   pSrcSlice + pSrc->RowPitch * LONG_PTR(y),
                   RowSizeInBytes);
        }
    }
}

//------------------------------------------------------------------------------------------------
// Row-by-row memcpy
inline void MemcpySubresource(
    _In_ const D3D12_MEMCPY_DEST* pDest,
    _In_ const void* pResourceData,
    _In_ const D3D12_SUBRESOURCE_INFO* pSrc,
    SIZE_T RowSizeInBytes,
    UINT NumRows,
    UINT NumSlices) noexcept
{
    for (UINT z = 0; z < NumSlices; ++z)
    {
        auto pDestSlice = static_cast<BYTE*>(pDest->pData) + pDest->SlicePitch * z;
        auto pSrcSlice = (static_cast<const BYTE*>(pResourceData) + pSrc->Offset) + pSrc->DepthPitch * ULONG_PTR(z);
        for (UINT y = 0; y < NumRows; ++y)
        {
            memcpy(pDestSlice + pDest->RowPitch * y,
                pSrcSlice + pSrc->RowPitch * ULONG_PTR(y),
                RowSizeInBytes);
        }
    }
}

//------------------------------------------------------------------------------------------------
// Returns required size of a buffer to be used for data upload
inline UINT64 GetRequiredIntermediateSize(
    _In_ ID3D12Resource* pDestinationResource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources) noexcept
{
#if defined(_MSC_VER) || !defined(_WIN32)
    const auto Desc = ID3D12Resource_GetDesc( pDestinationResource );
#else
    D3D12_RESOURCE_DESC tmpDesc;
    const auto& Desc = *ID3D12Resource_GetDesc( pDestinationResource, GetDesc(&tmpDesc) );
#endif
    UINT64 RequiredSize = 0;

    ID3D12Device* pDevice = nullptr;
    pDestinationResource->GetDevice(IID_ID3D12Device, reinterpret_cast<void**>(&pDevice));
    pDevice->GetCopyableFootprints(&Desc, FirstSubresource, NumSubresources, 0, nullptr, nullptr, nullptr, &RequiredSize);
    pDevice->Release();

    return RequiredSize;
}

//------------------------------------------------------------------------------------------------
// All arrays must be populated (e.g. by calling GetCopyableFootprints)
inline UINT64 UpdateSubresources(
    _In_ ID3D12GraphicsCommandList* pCmdList,
    _In_ ID3D12Resource* pDestinationResource,
    _In_ ID3D12Resource* pIntermediate,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources,
    UINT64 RequiredSize,
    _In_reads_(NumSubresources) const D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts,
    _In_reads_(NumSubresources) const UINT* pNumRows,
    _In_reads_(NumSubresources) const UINT64* pRowSizesInBytes,
    _In_reads_(NumSubresources) const D3D12_SUBRESOURCE_DATA* pSrcData) noexcept
{
    // Minor validation
#if defined(_MSC_VER) || !defined(_WIN32)
    const auto IntermediateDesc = ID3D12Resource_GetDesc( pIntermediate );
    const auto DestinationDesc = ID3D12Resource_GetDesc( pDestinationResource );
#else
    D3D12_RESOURCE_DESC tmpDesc1,tmpDesc2;
    const auto& IntermediateDesc = *ID3D12Resource_GetDesc( pIntermediate, GetDesc(&tmpDesc1) );
    const auto& DestinationDesc = *ID3D12Resource_GetDesc( pDestinationResource, GetDesc(&tmpDesc2) );
#endif
    if (IntermediateDesc.Dimension != D3D12_RESOURCE_DIMENSION_BUFFER ||
        IntermediateDesc.Width < RequiredSize + pLayouts[0].Offset ||
        RequiredSize > SIZE_T(-1) ||
        (DestinationDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER &&
            (FirstSubresource != 0 || NumSubresources != 1)))
    {
        return 0;
    }

    BYTE* pData;
    HRESULT hr = pIntermediate->Map(0, nullptr, reinterpret_cast<void**>(&pData));
    if (FAILED(hr))
    {
        return 0;
    }

    for (UINT i = 0; i < NumSubresources; ++i)
    {
        if (pRowSizesInBytes[i] > SIZE_T(-1)) return 0;
        D3D12_MEMCPY_DEST DestData = { pData + pLayouts[i].Offset, pLayouts[i].Footprint.RowPitch, SIZE_T(pLayouts[i].Footprint.RowPitch) * SIZE_T(pNumRows[i]) };
        MemcpySubresource(&DestData, &pSrcData[i], static_cast<SIZE_T>(pRowSizesInBytes[i]), pNumRows[i], pLayouts[i].Footprint.Depth);
    }
    pIntermediate->Unmap(0, nullptr);

    if (DestinationDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
    {
        pCmdList->CopyBufferRegion(
            pDestinationResource, 0, pIntermediate, pLayouts[0].Offset, pLayouts[0].Footprint.Width);
    }
    else
    {
        for (UINT i = 0; i < NumSubresources; ++i)
        {
            const CD3DX12_TEXTURE_COPY_LOCATION Dst(pDestinationResource, i + FirstSubresource);
            const CD3DX12_TEXTURE_COPY_LOCATION Src(pIntermediate, pLayouts[i]);
            pCmdList->CopyTextureRegion(&Dst, 0, 0, 0, &Src, nullptr);
        }
    }
    return RequiredSize;
}

//------------------------------------------------------------------------------------------------
// All arrays must be populated (e.g. by calling GetCopyableFootprints)
inline UINT64 UpdateSubresources(
    _In_ ID3D12GraphicsCommandList* pCmdList,
    _In_ ID3D12Resource* pDestinationResource,
    _In_ ID3D12Resource* pIntermediate,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources,
    UINT64 RequiredSize,
    _In_reads_(NumSubresources) const D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts,
    _In_reads_(NumSubresources) const UINT* pNumRows,
    _In_reads_(NumSubresources) const UINT64* pRowSizesInBytes,
    _In_ const void* pResourceData,
    _In_reads_(NumSubresources) const D3D12_SUBRESOURCE_INFO* pSrcData) noexcept
{
    // Minor validation
#if defined(_MSC_VER) || !defined(_WIN32)
    const auto IntermediateDesc = ID3D12Resource_GetDesc( pIntermediate );
    const auto DestinationDesc = ID3D12Resource_GetDesc( pDestinationResource );
#else
    D3D12_RESOURCE_DESC tmpDesc1,tmpDesc2;
    const auto& IntermediateDesc = *ID3D12Resource_GetDesc( pIntermediate, GetDesc(&tmpDesc1) );
    const auto& DestinationDesc = *ID3D12Resource_GetDesc( pDestinationResource, GetDesc(&tmpDesc2) );
#endif
    if (IntermediateDesc.Dimension != D3D12_RESOURCE_DIMENSION_BUFFER ||
        IntermediateDesc.Width < RequiredSize + pLayouts[0].Offset ||
        RequiredSize > SIZE_T(-1) ||
        (DestinationDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER &&
            (FirstSubresource != 0 || NumSubresources != 1)))
    {
        return 0;
    }

    BYTE* pData;
    HRESULT hr = pIntermediate->Map(0, nullptr, reinterpret_cast<void**>(&pData));
    if (FAILED(hr))
    {
        return 0;
    }

    for (UINT i = 0; i < NumSubresources; ++i)
    {
        if (pRowSizesInBytes[i] > SIZE_T(-1)) return 0;
        D3D12_MEMCPY_DEST DestData = { pData + pLayouts[i].Offset, pLayouts[i].Footprint.RowPitch, SIZE_T(pLayouts[i].Footprint.RowPitch) * SIZE_T(pNumRows[i]) };
        MemcpySubresource(&DestData, pResourceData, &pSrcData[i], static_cast<SIZE_T>(pRowSizesInBytes[i]), pNumRows[i], pLayouts[i].Footprint.Depth);
    }
    pIntermediate->Unmap(0, nullptr);

    if (DestinationDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
    {
        pCmdList->CopyBufferRegion(
            pDestinationResource, 0, pIntermediate, pLayouts[0].Offset, pLayouts[0].Footprint.Width);
    }
    else
    {
        for (UINT i = 0; i < NumSubresources; ++i)
        {
            const CD3DX12_TEXTURE_COPY_LOCATION Dst(pDestinationResource, i + FirstSubresource);
            const CD3DX12_TEXTURE_COPY_LOCATION Src(pIntermediate, pLayouts[i]);
            pCmdList->CopyTextureRegion(&Dst, 0, 0, 0, &Src, nullptr);
        }
    }
    return RequiredSize;
}

//------------------------------------------------------------------------------------------------
// Heap-allocating UpdateSubresources implementation
inline UINT64 UpdateSubresources(
    _In_ ID3D12GraphicsCommandList* pCmdList,
    _In_ ID3D12Resource* pDestinationResource,
    _In_ ID3D12Resource* pIntermediate,
    UINT64 IntermediateOffset,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources,
    _In_reads_(NumSubresources) const D3D12_SUBRESOURCE_DATA* pSrcData) noexcept
{
    UINT64 RequiredSize = 0;
    const auto MemToAlloc = static_cast<UINT64>(sizeof(D3D12_PLACED_SUBRESOURCE_FOOTPRINT) + sizeof(UINT) + sizeof(UINT64)) * NumSubresources;
    if (MemToAlloc > SIZE_MAX)
    {
       return 0;
    }
    void* pMem = HeapAlloc(GetProcessHeap(), 0, static_cast<SIZE_T>(MemToAlloc));
    if (pMem == nullptr)
    {
       return 0;
    }
    auto pLayouts = static_cast<D3D12_PLACED_SUBRESOURCE_FOOTPRINT*>(pMem);
    auto pRowSizesInBytes = reinterpret_cast<UINT64*>(pLayouts + NumSubresources);
    auto pNumRows = reinterpret_cast<UINT*>(pRowSizesInBytes + NumSubresources);

#if defined(_MSC_VER) || !defined(_WIN32)
    const auto Desc = ID3D12Resource_GetDesc( pDestinationResource );
#else
    D3D12_RESOURCE_DESC tmpDesc;
    const auto& Desc = *ID3D12Resource_GetDesc( pDestinationResource, GetDesc(&tmpDesc) );
#endif

    ID3D12Device* pDevice = nullptr;
    pDestinationResource->GetDevice(IID_ID3D12Device, reinterpret_cast<void**>(&pDevice));
    pDevice->GetCopyableFootprints(&Desc, FirstSubresource, NumSubresources, IntermediateOffset, pLayouts, pNumRows, pRowSizesInBytes, &RequiredSize);
    pDevice->Release();

    const UINT64 Result = UpdateSubresources(pCmdList, pDestinationResource, pIntermediate, FirstSubresource, NumSubresources, RequiredSize, pLayouts, pNumRows, pRowSizesInBytes, pSrcData);
    HeapFree(GetProcessHeap(), 0, pMem);
    return Result;
}

//------------------------------------------------------------------------------------------------
// Heap-allocating UpdateSubresources implementation
inline UINT64 UpdateSubresources(
    _In_ ID3D12GraphicsCommandList* pCmdList,
    _In_ ID3D12Resource* pDestinationResource,
    _In_ ID3D12Resource* pIntermediate,
    UINT64 IntermediateOffset,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources,
    _In_ const void* pResourceData,
    _In_reads_(NumSubresources) const D3D12_SUBRESOURCE_INFO* pSrcData) noexcept
{
    UINT64 RequiredSize = 0;
    const auto MemToAlloc = static_cast<UINT64>(sizeof(D3D12_PLACED_SUBRESOURCE_FOOTPRINT) + sizeof(UINT) + sizeof(UINT64)) * NumSubresources;
    if (MemToAlloc > SIZE_MAX)
    {
        return 0;
    }
    void* pMem = HeapAlloc(GetProcessHeap(), 0, static_cast<SIZE_T>(MemToAlloc));
    if (pMem == nullptr)
    {
        return 0;
    }
    auto pLayouts = static_cast<D3D12_PLACED_SUBRESOURCE_FOOTPRINT*>(pMem);
    auto pRowSizesInBytes = reinterpret_cast<UINT64*>(pLayouts + NumSubresources);
    auto pNumRows = reinterpret_cast<UINT*>(pRowSizesInBytes + NumSubresources);

#if defined(_MSC_VER) || !defined(_WIN32)
    const auto Desc = ID3D12Resource_GetDesc( pDestinationResource );
#else
    D3D12_RESOURCE_DESC tmpDesc;
    const auto& Desc = *ID3D12Resource_GetDesc( pDestinationResource, GetDesc(&tmpDesc) );
#endif

    ID3D12Device* pDevice = nullptr;
    pDestinationResource->GetDevice(IID_ID3D12Device, reinterpret_cast<void**>(&pDevice));
    pDevice->GetCopyableFootprints(&Desc, FirstSubresource, NumSubresources, IntermediateOffset, pLayouts, pNumRows, pRowSizesInBytes, &RequiredSize);
    pDevice->Release();

    const UINT64 Result = UpdateSubresources(pCmdList, pDestinationResource, pIntermediate, FirstSubresource, NumSubresources, RequiredSize, pLayouts, pNumRows, pRowSizesInBytes, pResourceData, pSrcData);
    HeapFree(GetProcessHeap(), 0, pMem);
    return Result;
}

//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// D3D12 exports a new method for serializing root signatures in the Windows 10 Anniversary Update.
// To help enable root signature 1.1 features when they are available and not require maintaining
// two code paths for building root signatures, this helper method reconstructs a 1.0 signature when
// 1.1 is not supported.
inline HRESULT D3DX12SerializeVersionedRootSignature(
    _In_ const D3D12_VERSIONED_ROOT_SIGNATURE_DESC* pRootSignatureDesc,
    D3D_ROOT_SIGNATURE_VERSION MaxVersion,
    _Outptr_ ID3DBlob** ppBlob,
    _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorBlob) noexcept
{
    if (ppErrorBlob != nullptr)
    {
        *ppErrorBlob = nullptr;
    }

    switch (MaxVersion)
    {
        case D3D_ROOT_SIGNATURE_VERSION_1_0:
            switch (pRootSignatureDesc->Version)
            {
                case D3D_ROOT_SIGNATURE_VERSION_1_0:
                    return D3D12SerializeRootSignature(&pRootSignatureDesc->Desc_1_0, D3D_ROOT_SIGNATURE_VERSION_1, ppBlob, ppErrorBlob);

                case D3D_ROOT_SIGNATURE_VERSION_1_1:
                {
                    HRESULT hr = S_OK;
                    const D3D12_ROOT_SIGNATURE_DESC1& desc_1_1 = pRootSignatureDesc->Desc_1_1;

                    const SIZE_T ParametersSize = sizeof(D3D12_ROOT_PARAMETER) * desc_1_1.NumParameters;
                    void* pParameters = (ParametersSize > 0) ? HeapAlloc(GetProcessHeap(), 0, ParametersSize) : nullptr;
                    if (ParametersSize > 0 && pParameters == nullptr)
                    {
                        hr = E_OUTOFMEMORY;
                    }
                    auto pParameters_1_0 = static_cast<D3D12_ROOT_PARAMETER*>(pParameters);

                    if (SUCCEEDED(hr))
                    {
                        for (UINT n = 0; n < desc_1_1.NumParameters; n++)
                        {
                            __analysis_assume(ParametersSize == sizeof(D3D12_ROOT_PARAMETER) * desc_1_1.NumParameters);
                            pParameters_1_0[n].ParameterType = desc_1_1.pParameters[n].ParameterType;
                            pParameters_1_0[n].ShaderVisibility = desc_1_1.pParameters[n].ShaderVisibility;

                            switch (desc_1_1.pParameters[n].ParameterType)
                            {
                            case D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS:
                                pParameters_1_0[n].Constants.Num32BitValues = desc_1_1.pParameters[n].Constants.Num32BitValues;
                                pParameters_1_0[n].Constants.RegisterSpace = desc_1_1.pParameters[n].Constants.RegisterSpace;
                                pParameters_1_0[n].Constants.ShaderRegister = desc_1_1.pParameters[n].Constants.ShaderRegister;
                                break;

                            case D3D12_ROOT_PARAMETER_TYPE_CBV:
                            case D3D12_ROOT_PARAMETER_TYPE_SRV:
                            case D3D12_ROOT_PARAMETER_TYPE_UAV:
                                pParameters_1_0[n].Descriptor.RegisterSpace = desc_1_1.pParameters[n].Descriptor.RegisterSpace;
                                pParameters_1_0[n].Descriptor.ShaderRegister = desc_1_1.pParameters[n].Descriptor.ShaderRegister;
                                break;

                            case D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE:
                                const D3D12_ROOT_DESCRIPTOR_TABLE1& table_1_1 = desc_1_1.pParameters[n].DescriptorTable;

                                const SIZE_T DescriptorRangesSize = sizeof(D3D12_DESCRIPTOR_RANGE) * table_1_1.NumDescriptorRanges;
                                void* pDescriptorRanges = (DescriptorRangesSize > 0 && SUCCEEDED(hr)) ? HeapAlloc(GetProcessHeap(), 0, DescriptorRangesSize) : nullptr;
                                if (DescriptorRangesSize > 0 && pDescriptorRanges == nullptr)
                                {
                                    hr = E_OUTOFMEMORY;
                                }
                                auto pDescriptorRanges_1_0 = static_cast<D3D12_DESCRIPTOR_RANGE*>(pDescriptorRanges);

                                if (SUCCEEDED(hr))
                                {
                                    for (UINT x = 0; x < table_1_1.NumDescriptorRanges; x++)
                                    {
                                        __analysis_assume(DescriptorRangesSize == sizeof(D3D12_DESCRIPTOR_RANGE) * table_1_1.NumDescriptorRanges);
                                        pDescriptorRanges_1_0[x].BaseShaderRegister = table_1_1.pDescriptorRanges[x].BaseShaderRegister;
                                        pDescriptorRanges_1_0[x].NumDescriptors = table_1_1.pDescriptorRanges[x].NumDescriptors;
                                        pDescriptorRanges_1_0[x].OffsetInDescriptorsFromTableStart = table_1_1.pDescriptorRanges[x].OffsetInDescriptorsFromTableStart;
                                        pDescriptorRanges_1_0[x].RangeType = table_1_1.pDescriptorRanges[x].RangeType;
                                        pDescriptorRanges_1_0[x].RegisterSpace = table_1_1.pDescriptorRanges[x].RegisterSpace;
                                    }
                                }

                                D3D12_ROOT_DESCRIPTOR_TABLE& table_1_0 = pParameters_1_0[n].DescriptorTable;
                                table_1_0.NumDescriptorRanges = table_1_1.NumDescriptorRanges;
                                table_1_0.pDescriptorRanges = pDescriptorRanges_1_0;
                            }
                        }
                    }

                    if (SUCCEEDED(hr))
                    {
                        const CD3DX12_ROOT_SIGNATURE_DESC desc_1_0(desc_1_1.NumParameters, pParameters_1_0, desc_1_1.NumStaticSamplers, desc_1_1.pStaticSamplers, desc_1_1.Flags);
                        hr = D3D12SerializeRootSignature(&desc_1_0, D3D_ROOT_SIGNATURE_VERSION_1, ppBlob, ppErrorBlob);
                    }

                    if (pParameters)
                    {
                        for (UINT n = 0; n < desc_1_1.NumParameters; n++)
                        {
                            if (desc_1_1.pParameters[n].ParameterType == D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
                            {
                                auto pDescriptorRanges_1_0 = pParameters_1_0[n].DescriptorTable.pDescriptorRanges;
                                HeapFree(GetProcessHeap(), 0, reinterpret_cast<void*>(const_cast<D3D12_DESCRIPTOR_RANGE*>(pDescriptorRanges_1_0)));
                            }
                        }
                        HeapFree(GetProcessHeap(), 0, pParameters);
                    }
                    return hr;
                }
            }
            break;

        case D3D_ROOT_SIGNATURE_VERSION_1_1:
            return D3D12SerializeVersionedRootSignature(pRootSignatureDesc, ppBlob, ppErrorBlob);
    }

    return E_INVALIDARG;
}


#endif // defined(__cplusplus) && !defined(CINTERFACE)
#endif //__D3DX12_H__

