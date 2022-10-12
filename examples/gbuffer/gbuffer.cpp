#include <Windows.h>

#include <donut/app/DeviceManager.h>
#include <nvrhi/nvrhi.h>
#include <nvrhi/utils.h>

using namespace donut;

class GBuffer : public app::IRenderPass {
	nvrhi::CommandListHandle commandList;
	nvrhi::ShaderHandle gbuffer_vs;
	nvrhi::ShaderHandle gbuffer_ps;
	// base color
	nvrhi::TextureHandle gbuffer_channel0;

public:
	using IRenderPass::IRenderPass;

	bool Init() {
		int width;
		int height;
		GetDeviceManager()->GetWindowDimensions(width, height);

		commandList = GetDevice()->createCommandList();
		return true;
	}

	void BackBufferResizing() override {
	}

	void BackBufferResized(const uint32_t width, const uint32_t height, const uint32_t sampleCount) {

	}

	void Animate(float fElapsedTimeSeconds) override {
		GetDeviceManager()->SetInformativeWindowTitle("GBuffer");
	}

	void Render(nvrhi::IFramebuffer* framebuffer) override {
		commandList->open();
		nvrhi::utils::ClearColorAttachment(commandList, framebuffer, 0, nvrhi::Color(0.f));

		commandList->close();
		GetDevice()->executeCommandList(commandList);
	}

};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	app::DeviceManager* deviceManager = app::DeviceManager::Create(nvrhi::GraphicsAPI::D3D12);
	app::DeviceCreationParameters deviceParams;
#ifdef _DEBUG
	deviceParams.enableDebugRuntime = true;
	deviceParams.enableNvrhiValidationLayer = true;
#endif
	if (!deviceManager->CreateWindowDeviceAndSwapChain(deviceParams, "GBuffer"))
	{
		log::fatal("Cannot initialize a graphics device with the requested parameters");
		return 1;
	}

	{
		GBuffer example(deviceManager);
		if (example.Init())
		{
			deviceManager->AddRenderPassToBack(&example);
			deviceManager->RunMessageLoop();
			deviceManager->RemoveRenderPass(&example);
		}
	}
	deviceManager->Shutdown();
	delete deviceManager;
	return 0;
}