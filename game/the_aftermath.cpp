#include <Windows.h>

#include <donut/app/DeviceManager.h>
#include <nvrhi/nvrhi.h>
#include <GLFW/glfw3.h>

using namespace donut;

struct GameState {

};

class TheAftermath : public app::IRenderPass {
	nvrhi::CommandListHandle m_CommandList;
public:
	using IRenderPass::IRenderPass;

	bool Init() {
		m_CommandList = GetDevice()->createCommandList();
		return true;
	}

	void Render() {

	}
};

void freezeWindow(GLFWwindow *window) {
	bool enable = false;
	glfwSetWindowAttrib(window, GLFW_RESIZABLE, enable);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	app::DeviceManager* deviceManager = app::DeviceManager::Create(nvrhi::GraphicsAPI::D3D12);
	app::DeviceCreationParameters deviceParams;
#ifdef _DEBUG
	deviceParams.enableDebugRuntime = true;
	deviceParams.enableNvrhiValidationLayer = true;
#endif
	if (!deviceManager->CreateWindowDeviceAndSwapChain(deviceParams, "The Aftermath"))
	{
		log::fatal("Cannot initialize a graphics device with the requested parameters");
		return 1;
	}

	freezeWindow(deviceManager->GetWindow());

	{
		TheAftermath example(deviceManager);
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