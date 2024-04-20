#include "hooks.hpp"
#include <dxgi.h>

LRESULT SLM::Hooks::WndProc::thunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto& io = ImGui::GetIO();
	if (uMsg == WM_KILLFOCUS)
	{
		io.ClearInputCharacters();
		io.ClearInputKeys();
	}

	return func(hWnd, uMsg, wParam, lParam);
}

inline void SLM::Hooks::CreateD3DAndSwapChain::thunk()
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

	auto& io = ImGui::GetIO();
	io.ConfigFlags |= (ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad | ImGuiConfigFlags_NoMouseCursorChange);

	io.IniFilename                       = nullptr;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.MousePos                          = { io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f };

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
	Hooks::GetSingleton()->installedHooks.store(true);

	{
		static const auto screenSize         = SLM::GetScreenSize();
		io.DisplaySize.x                     = static_cast<float>(screenSize.width);
		io.DisplaySize.y                     = static_cast<float>(screenSize.height);
		io.ConfigWindowsMoveFromTitleBarOnly = true;
	}

	WndProc::func = reinterpret_cast<WNDPROC>(
		SetWindowLongPtrA(
			desc.OutputWindow,
			GWLP_WNDPROC,
			reinterpret_cast<LONG_PTR>(WndProc::thunk)));

	if (!WndProc::func)
	{
		logger::error("SetWindowLongPtrA failed!");
	}

	SkyrimLightsMenu::SetImGuiStyle();
	logger::info("Set ImGui Style");
}

inline void SLM::Hooks::StopTimer::thunk(std::uint32_t timer)
{
	func(timer);

	// Skip draw if hooks haven't been registered
	if (!Hooks::GetSingleton()->installedHooks.load())
	{
		return;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	{
		static const auto screenSize = SLM::GetScreenSize();
		auto&             io         = ImGui::GetIO();
		io.DisplaySize.x             = static_cast<float>(screenSize.width);
		io.DisplaySize.y             = static_cast<float>(screenSize.height);
	}

	ImGui::NewFrame();

	SkyrimLightsMenu::GetSingleton()->DoFrame();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void SLM::Hooks::Install()
{
	REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(75595, 77226), OFFSET(0x9, 0x275) };  // BSGraphics::InitD3D
	stl::write_thunk_call<CreateD3DAndSwapChain>(target.address());

	REL::Relocation<std::uintptr_t> target2{ RELOCATION_ID(75461, 77246), 0x9 };  // BSGraphics::Renderer::End
	stl::write_thunk_call<StopTimer>(target2.address());

	REL::Relocation<std::uintptr_t> target3{ RELOCATION_ID(67315, 68617), OFFSET(0x7B, 0x7B) };
	stl::write_thunk_call<SendInputEvent>(target3.address());
}

void SLM::Hooks::SendInputEvent::thunk(RE::BSTEventSource<RE::InputEvent*>* dispatcher, RE::InputEvent* const* ppEvent)
{
	if (ppEvent)
	{
		SLM::SkyrimLightsMenu::GetSingleton()->GetInputManager().ProcessInputEvent(ppEvent);
	}

	if (!SLM::SkyrimLightsMenu::GetSingleton()->IsMenuVisible())
	{
		func(dispatcher, ppEvent);
	}
	// Menu is visible but allow player movement to be handled
	else if (ppEvent)
	{
		bool flag = true;
		RE::InputEvent* prev = nullptr;

		RE::InputEvent** eventsList = const_cast<RE::InputEvent**>(ppEvent);

		for (auto* it = *ppEvent; it; it = it->next)
		{
			if (!SLM::SkyrimLightsMenu::GetSingleton()->AllowInput(it))
			{
				if (prev != nullptr)
				{
					prev->next = it->next;
				}
				else
				{
					*eventsList = it->next;
				}
			}
			else
			{
				prev = it;
			}
		}

		//				logger::info("Can process this!!");
		//auto* tmp = it->next;
		//logger::info("{}", (void*)tmp);
		//it->next = nullptr;
		//func(dispatcher, &it);
		//it->next = tmp;
		//logger::info("{}", (void*)tmp);

		func(dispatcher, eventsList);
	}
	else
	{
		constexpr RE::InputEvent* const dummy[] = { nullptr };
		func(dispatcher, dummy);
	}
}
