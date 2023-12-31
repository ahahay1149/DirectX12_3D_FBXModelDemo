#include "PipelineState.h"
#include "Engine.h"
#include <d3dx12.h>
#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

PipelineState::PipelineState()
{
	desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);	
	desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;	
	desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);	
	desc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);	
	desc.SampleMask = UINT_MAX;
	desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;	
	desc.NumRenderTargets = 1;	
	desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	desc.SampleDesc.Count = 1;	
	desc.SampleDesc.Quality = 0;
}

bool PipelineState::IsValid()
{
	return m_IsValid;
}

void PipelineState::SetInputLayout(D3D12_INPUT_LAYOUT_DESC layout)
{
	desc.InputLayout = layout;
}

void PipelineState::SetRootSignature(ID3D12RootSignature* rootSignature)
{
	desc.pRootSignature = rootSignature;
}

void PipelineState::SetVS(std::wstring filePath)
{
	auto hr = D3DReadFileToBlob(filePath.c_str(), m_pVsBlob.GetAddressOf());
	if (FAILED(hr))
	{
		printf("頂点シェーダーの読み込みに失敗");
		return;
	}

	desc.VS = CD3DX12_SHADER_BYTECODE(m_pVsBlob.Get());
}

void PipelineState::SetPS(std::wstring filePath)
{
	auto hr = D3DReadFileToBlob(filePath.c_str(), m_pPsBlob.GetAddressOf());
	if (FAILED(hr))
	{
		printf("ピクセルシェーダーの読み込みに失敗");
		return;
	}

	desc.PS = CD3DX12_SHADER_BYTECODE(m_pPsBlob.Get());
}

void PipelineState::Create()
{
	auto hr = g_Engine->Device()->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(m_pPipelineState.ReleaseAndGetAddressOf()));
	if (FAILED(hr))
	{
		printf("パイプラインステートの生成に失敗");
		return;
	}

	m_IsValid = true;
}

ID3D12PipelineState* PipelineState::Get()
{
	return m_pPipelineState.Get();
}