#include "inputManager.hpp"

ImGuiKey SLM::InputManager::ToImGuiKey(RE::BSWin32KeyboardDevice::Key key)
{
	using KEY = RE::BSWin32KeyboardDevice::Key;
	switch (key)
	{
	case KEY::kTab:
		return ImGuiKey_Tab;
	case KEY::kLeft:
		return ImGuiKey_LeftArrow;
	case KEY::kRight:
		return ImGuiKey_RightArrow;
	case KEY::kUp:
		return ImGuiKey_UpArrow;
	case KEY::kDown:
		return ImGuiKey_DownArrow;
	case KEY::kPageUp:
		return ImGuiKey_PageUp;
	case KEY::kPageDown:
		return ImGuiKey_PageDown;
	case KEY::kHome:
		return ImGuiKey_Home;
	case KEY::kEnd:
		return ImGuiKey_End;
	case KEY::kInsert:
		return ImGuiKey_Insert;
	case KEY::kDelete:
		return ImGuiKey_Delete;
	case KEY::kBackspace:
		return ImGuiKey_Backspace;
	case KEY::kSpacebar:
		return ImGuiKey_Space;
	case KEY::kEnter:
		return ImGuiKey_Enter;
	case KEY::kEscape:
		return ImGuiKey_Escape;
	case KEY::kApostrophe:
		return ImGuiKey_Apostrophe;
	case KEY::kComma:
		return ImGuiKey_Comma;
	case KEY::kMinus:
		return ImGuiKey_Minus;
	case KEY::kPeriod:
		return ImGuiKey_Period;
	case KEY::kSlash:
		return ImGuiKey_Slash;
	case KEY::kSemicolon:
		return ImGuiKey_Semicolon;
	case KEY::kEquals:
		return ImGuiKey_Equal;
	case KEY::kBracketLeft:
		return ImGuiKey_LeftBracket;
	case KEY::kBackslash:
		return ImGuiKey_Backslash;
	case KEY::kBracketRight:
		return ImGuiKey_RightBracket;
	case KEY::kTilde:
		return ImGuiKey_GraveAccent;
	case KEY::kCapsLock:
		return ImGuiKey_CapsLock;
	case KEY::kScrollLock:
		return ImGuiKey_ScrollLock;
	case KEY::kNumLock:
		return ImGuiKey_NumLock;
	case KEY::kPrintScreen:
		return ImGuiKey_PrintScreen;
	case KEY::kPause:
		return ImGuiKey_Pause;
	case KEY::kKP_0:
		return ImGuiKey_Keypad0;
	case KEY::kKP_1:
		return ImGuiKey_Keypad1;
	case KEY::kKP_2:
		return ImGuiKey_Keypad2;
	case KEY::kKP_3:
		return ImGuiKey_Keypad3;
	case KEY::kKP_4:
		return ImGuiKey_Keypad4;
	case KEY::kKP_5:
		return ImGuiKey_Keypad5;
	case KEY::kKP_6:
		return ImGuiKey_Keypad6;
	case KEY::kKP_7:
		return ImGuiKey_Keypad7;
	case KEY::kKP_8:
		return ImGuiKey_Keypad8;
	case KEY::kKP_9:
		return ImGuiKey_Keypad9;
	case KEY::kKP_Decimal:
		return ImGuiKey_KeypadDecimal;
	case KEY::kKP_Divide:
		return ImGuiKey_KeypadDivide;
	case KEY::kKP_Multiply:
		return ImGuiKey_KeypadMultiply;
	case KEY::kKP_Subtract:
		return ImGuiKey_KeypadSubtract;
	case KEY::kKP_Plus:
		return ImGuiKey_KeypadAdd;
	case KEY::kKP_Enter:
		return ImGuiKey_KeypadEnter;
	case KEY::kLeftShift:
		return ImGuiKey_LeftShift;
	case KEY::kLeftControl:
		return ImGuiKey_LeftCtrl;
	case KEY::kLeftAlt:
		return ImGuiKey_LeftAlt;
	case KEY::kLeftWin:
		return ImGuiKey_LeftSuper;
	case KEY::kRightShift:
		return ImGuiKey_RightShift;
	case KEY::kRightControl:
		return ImGuiKey_RightCtrl;
	case KEY::kRightAlt:
		return ImGuiKey_RightAlt;
	case KEY::kRightWin:
		return ImGuiKey_RightSuper;
	/*case KEY::kAPPS:
			return ImGuiKey_Menu; - doesn't fire*/
	case KEY::kNum0:
		return ImGuiKey_0;
	case KEY::kNum1:
		return ImGuiKey_1;
	case KEY::kNum2:
		return ImGuiKey_2;
	case KEY::kNum3:
		return ImGuiKey_3;
	case KEY::kNum4:
		return ImGuiKey_4;
	case KEY::kNum5:
		return ImGuiKey_5;
	case KEY::kNum6:
		return ImGuiKey_6;
	case KEY::kNum7:
		return ImGuiKey_7;
	case KEY::kNum8:
		return ImGuiKey_8;
	case KEY::kNum9:
		return ImGuiKey_9;
	case KEY::kA:
		return ImGuiKey_A;
	case KEY::kB:
		return ImGuiKey_B;
	case KEY::kC:
		return ImGuiKey_C;
	case KEY::kD:
		return ImGuiKey_D;
	case KEY::kE:
		return ImGuiKey_E;
	case KEY::kF:
		return ImGuiKey_F;
	case KEY::kG:
		return ImGuiKey_G;
	case KEY::kH:
		return ImGuiKey_H;
	case KEY::kI:
		return ImGuiKey_I;
	case KEY::kJ:
		return ImGuiKey_J;
	case KEY::kK:
		return ImGuiKey_K;
	case KEY::kL:
		return ImGuiKey_L;
	case KEY::kM:
		return ImGuiKey_M;
	case KEY::kN:
		return ImGuiKey_N;
	case KEY::kO:
		return ImGuiKey_O;
	case KEY::kP:
		return ImGuiKey_P;
	case KEY::kQ:
		return ImGuiKey_Q;
	case KEY::kR:
		return ImGuiKey_R;
	case KEY::kS:
		return ImGuiKey_S;
	case KEY::kT:
		return ImGuiKey_T;
	case KEY::kU:
		return ImGuiKey_U;
	case KEY::kV:
		return ImGuiKey_V;
	case KEY::kW:
		return ImGuiKey_W;
	case KEY::kX:
		return ImGuiKey_X;
	case KEY::kY:
		return ImGuiKey_Y;
	case KEY::kZ:
		return ImGuiKey_Z;
	case KEY::kF1:
		return ImGuiKey_F1;
	case KEY::kF2:
		return ImGuiKey_F2;
	case KEY::kF3:
		return ImGuiKey_F3;
	case KEY::kF4:
		return ImGuiKey_F4;
	case KEY::kF5:
		return ImGuiKey_F5;
	case KEY::kF6:
		return ImGuiKey_F6;
	case KEY::kF7:
		return ImGuiKey_F7;
	case KEY::kF8:
		return ImGuiKey_F8;
	case KEY::kF9:
		return ImGuiKey_F9;
	case KEY::kF10:
		return ImGuiKey_F10;
	case KEY::kF11:
		return ImGuiKey_F11;
	case KEY::kF12:
		return ImGuiKey_F12;
	default:
		return ImGuiKey_None;
	}
}

ImGuiKey SLM::InputManager::ToImGuiKey(RE::BSWin32GamepadDevice::Key key)
{
	using GAMEPAD_DIRECTX = RE::BSWin32GamepadDevice::Key;
	switch (key)
	{
	case GAMEPAD_DIRECTX::kUp:
		return ImGuiKey_GamepadDpadUp;
	case GAMEPAD_DIRECTX::kDown:
		return ImGuiKey_GamepadDpadDown;
	case GAMEPAD_DIRECTX::kLeft:
		return ImGuiKey_GamepadDpadLeft;
	case GAMEPAD_DIRECTX::kRight:
		return ImGuiKey_GamepadDpadRight;
	case GAMEPAD_DIRECTX::kStart:
		return ImGuiKey_GamepadStart;
	case GAMEPAD_DIRECTX::kBack:
		return ImGuiKey_GamepadBack;
	case GAMEPAD_DIRECTX::kLeftThumb:
		return ImGuiKey_GamepadL3;
	case GAMEPAD_DIRECTX::kRightThumb:
		return ImGuiKey_GamepadR3;
	case GAMEPAD_DIRECTX::kLeftShoulder:
		return ImGuiKey_GamepadL1;
	case GAMEPAD_DIRECTX::kRightShoulder:
		return ImGuiKey_GamepadR1;
	case GAMEPAD_DIRECTX::kA:
		return ImGuiKey_GamepadFaceDown;
	case GAMEPAD_DIRECTX::kB:
		return ImGuiKey_GamepadFaceRight;
	case GAMEPAD_DIRECTX::kX:
		return ImGuiKey_GamepadFaceLeft;
	case GAMEPAD_DIRECTX::kY:
		return ImGuiKey_GamepadFaceUp;
	default:
		return ImGuiKey_None;
	}
}

RE::BSEventNotifyControl SLM::InputManager::ProcessInputEvent(RE::InputEvent* const* ppEvent)
{
	if (!ppEvent || !(*ppEvent))
		return RE::BSEventNotifyControl::kContinue;

	RE::InputEvent* event = *ppEvent;

	if (const auto buttonEvt = event->AsButtonEvent())
	{
		switch (event->GetDevice())
		{
		case RE::INPUT_DEVICE::kKeyboard:
			{
				HandleKeyboardEvent(buttonEvt->GetIDCode(), buttonEvt->GetDevice(), buttonEvt->IsPressed());

				if (buttonEvt->GetEventType() == RE::INPUT_EVENT_TYPE::kChar)
					logger::info("CHar event");
				//	HandleCharEvent(buttonEvt->GetIDCode(), buttonEvt->GetDevice());
			}
			break;
		case RE::INPUT_DEVICE::kMouse:
			HandleMouseEvent(buttonEvt->GetIDCode(), buttonEvt->Value(), buttonEvt->IsPressed());
			break;
		default:
			break;
		}
	}

	return RE::BSEventNotifyControl::kContinue;
}

void SLM::InputManager::HandleKeyboardEvent(uint32_t key, RE::INPUT_DEVICE device, bool isPressed) const
{
	using DEVICE = RE::INPUT_DEVICE;

	auto&    io = ImGui::GetIO();
	ImGuiKey imguiKey;

	switch (device)
	{
	case DEVICE::kKeyboard:
		imguiKey = ToImGuiKey(static_cast<RE::BSWin32KeyboardDevice::Key>(key));
		break;
	case DEVICE::kGamepad:
		imguiKey = ToImGuiKey(static_cast<RE::BSWin32GamepadDevice::Key>(key));
		break;
	default:
		imguiKey = ImGuiKey_None;
		break;
	}

	if (imguiKey != ImGuiKey_None)
		io.AddKeyEvent(imguiKey, isPressed);
}

void SLM::InputManager::HandleCharEvent(uint32_t key, RE::INPUT_DEVICE device) const
{
	using DEVICE = RE::INPUT_DEVICE;
	auto& io = ImGui::GetIO();

	logger::info("Handling char event");

	if (device == DEVICE::kKeyboard)
	{
		io.AddInputCharacter(SKSE::InputMap::GetKeyboardKeyName(key).c_str()[0]);
	}
}

void SLM::InputManager::HandleMouseEvent(uint32_t key, float value, bool isPressed) const
{
	using MOUSE = RE::BSWin32MouseDevice::Key;

	auto& io = ImGui::GetIO();

	switch (auto mouseKey = static_cast<MOUSE>(key))
	{
	case MOUSE::kWheelUp:
		io.AddMouseWheelEvent(0, value);
		break;
	case MOUSE::kWheelDown:
		io.AddMouseWheelEvent(0, value * -1.0f);
		break;
	default:
		io.AddMouseButtonEvent(mouseKey, isPressed);
		break;
	}
}
