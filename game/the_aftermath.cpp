#include <Windows.h>

#include <donut/app/DeviceManager.h>

using namespace donut;

class HelloWindow : public app::IRenderPass {
public:
	using IRenderPass::IRenderPass;

	bool Init() {
		return true;
	}

	void Animate(float fElapsedTimeSeconds) override {
		GetDeviceManager()->SetInformativeWindowTitle("Hello Window");
	}
};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	app::DeviceManager* deviceManager = app::DeviceManager::Create(nvrhi::GraphicsAPI::D3D12);
	app::DeviceCreationParameters deviceParams;
#ifdef _DEBUG
	deviceParams.enableDebugRuntime = true;
	deviceParams.enableNvrhiValidationLayer = true;
#endif
	if (!deviceManager->CreateWindowDeviceAndSwapChain(deviceParams, "Hello Window"))
	{
		log::fatal("Cannot initialize a graphics device with the requested parameters");
		return 1;
	}

	{
		HelloWindow example(deviceManager);
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