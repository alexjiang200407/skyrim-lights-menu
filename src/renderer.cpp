#include "renderer.hpp"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <dxgi.h>
#include "logger.hpp"


std::atomic<bool> SLM::Renderer::initialized{ false };

LRESULT SLM::Renderer::WndProc::thunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto& io = ImGui::GetIO();
	if (uMsg == WM_KILLFOCUS)
	{
		io.ClearInputCharacters();
		io.ClearInputKeys();
	}

	return func(hWnd, uMsg, wParam, lParam);
}

inline void SLM::Renderer::CreateD3DAndSwapChain::thunk()
{
	func();
	const auto renderer = RE::BSGraphics::Renderer::GetSingleton();

	if (!renderer)
	{
		return;
	}

	const auto swapChain = renderer->data.renderWindows[0].swapChain;
	if (!swapChain)
	{
		logger::error("couldn't find swapChain");
		return;
	}
	DXGI_SWAP_CHAIN_DESC desc{};
	if (FAILED(swapChain->GetDesc(std::addressof(desc))))
	{
		logger::error("IDXGISwapChain::GetDesc failed.");
		return;
	}

	const auto device  = renderer->data.forwarder;
	const auto context = renderer->data.context;

	logger::info("Initializing ImGui...");

	ImGui::CreateContext();

	auto& io       = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;
	io.IniFilename = nullptr;

	// ImGui::StyleVanilla();

	if (!ImGui_ImplWin32_Init(desc.OutputWindow))
	{
		logger::error("ImGui initialization failed (Win32)");
		return;
	}
	if (!ImGui_ImplDX11_Init(device, context))
	{
		logger::error("ImGui initialization failed (DX11)");
		return;
	}

	logger::info("ImGui initialized.");

	WndProc::func = reinterpret_cast<WNDPROC>(
		SetWindowLongPtrA(
			desc.OutputWindow,
			GWLP_WNDPROC,
			reinterpret_cast<LONG_PTR>(WndProc::thunk)));

	if (!WndProc::func)
	{
		logger::error("SetWindowLongPtrA failed!");
	}
}

inline void SLM::Renderer::StopTimer::thunk(std::uint32_t a_timer)
{
	func(a_timer);

	// Skip if Imgui is not loaded
	if (!initialized.load())
	{
		return;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//{
	//	// disable windowing
	//	GImGui->NavWindowingTarget = nullptr;

	//	photoMode->Draw();
	//}
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void SLM::Renderer::Init()
{
	//logger::info("asdasdasdasd");
	REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(75595, 77226), OFFSET(0x9, 0x275) };  // BSGraphics::InitD3D
	stl::write_thunk_call<CreateD3DAndSwapChain>(target.address());

	REL::Relocation<std::uintptr_t> target2{ RELOCATION_ID(75461, 77246), 0x9 };  // BSGraphics::Renderer::End
	stl::write_thunk_call<StopTimer>(target2.address());
}
