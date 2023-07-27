#include "ComPtr.h"
#include <string>
#include <d3dx12.h>

class DescriptorHeap;
class DescriptorHandle;

class Texture2D
{
public:
	static Texture2D* Get(std::string path);  
	static Texture2D* Get(std::wstring path);  
	static Texture2D* GetWhite();  
	bool IsValid();  

	ID3D12Resource* Resource();  
	D3D12_SHADER_RESOURCE_VIEW_DESC ViewDesc();  

private:
	bool m_IsValid;  
	Texture2D(std::string path);
	Texture2D(std::wstring path);
	Texture2D(ID3D12Resource* buffer);
	ComPtr<ID3D12Resource> m_pResource;  
	bool Load(std::string& path);
	bool Load(std::wstring& path);

	static ID3D12Resource* GetDefaultResource(size_t width, size_t height);

	Texture2D(const Texture2D&) = delete;
	void operator = (const Texture2D&) = delete;
};