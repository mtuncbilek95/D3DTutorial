#include "GraphicsDevice.h"

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Framebuffer/Framebuffer.h>
#include <Runtime/Graphics/Framebuffer/FramebufferDesc.h>

#include <Runtime/Graphics/Swapchain/Swapchain.h>
#include <Runtime/Graphics/Swapchain/SwapchainDesc.h>

#include <Runtime/Graphics/Texture/Texture.h>
#include <Runtime/Graphics/Texture/TextureDesc.h>

#include <Runtime/Graphics/Texture/TextureView.h>
#include <Runtime/Graphics/Texture/TextureViewDesc.h>

#include <Runtime/Graphics/Shader/Shader.h>
#include <Runtime/Graphics/Shader/ShaderDesc.h>

GraphicsDevice::GraphicsDevice(const GraphicsDeviceDesc& desc)
{
	DEV_ASSERT(SUCCEEDED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
		&mD3D11Device, nullptr, &mD3D11ImmediateContext)), "GraphicsDevice",
		"Failed to create D3D11 device.");

	DEV_LOG(TE_VERBOSE, "GraphicsDevice", "Created GraphicsDevice successfully.");
}

std::shared_ptr<Swapchain> GraphicsDevice::CreateSwapchain(const SwapchainDesc& desc)
{
	mSwapchain = std::make_shared<Swapchain>(shared_from_this(), desc);
	mDeviceObjects.push_back(mSwapchain);

	return mSwapchain;
}

std::shared_ptr<Framebuffer> GraphicsDevice::CreateFramebuffer(const FramebufferDesc& desc)
{
	auto framebuffer = std::make_shared<Framebuffer>(shared_from_this(), desc);
	mDeviceObjects.push_back(framebuffer);

	return framebuffer;
}

std::shared_ptr<Texture> GraphicsDevice::CreateTexture(const TextureDesc& desc)
{
	auto texture = std::make_shared<Texture>(shared_from_this(), desc);
	mDeviceObjects.push_back(texture);

	return texture;
}

std::shared_ptr<TextureView> GraphicsDevice::CreateTextureView(const TextureViewDesc& desc)
{
	auto textureView = std::make_shared<TextureView>(shared_from_this(), desc);
	mDeviceObjects.push_back(textureView);

	return textureView;
}

std::shared_ptr<Shader> GraphicsDevice::CreateShader(const ShaderDesc& desc)
{
	auto shader = std::make_shared<Shader>(shared_from_this(), desc);
	mDeviceObjects.push_back(shader);

	return shader;
}
