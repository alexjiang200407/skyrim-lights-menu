#pragma once

namespace SLM
{
	class InputManager
	{
	public:
	public:
		static ImGuiKey          ToImGuiKey(RE::BSWin32KeyboardDevice::Key key);
		static ImGuiKey          ToImGuiKey(RE::BSWin32GamepadDevice::Key key);
		RE::BSEventNotifyControl ProcessInputEvent(RE::InputEvent* const* ppEvent);

		virtual bool AllowGameInput(RE::InputEvent* event) = 0;
		virtual bool AllowImGuiInput(RE::InputEvent* event) = 0;

		RE::InputEvent* const* FilterGameInput(RE::InputEvent* const* events);

	private:
		void HandleKeyboardEvent(uint32_t key, RE::INPUT_DEVICE device, bool isPressed) const;
		void HandleCharEvent(uint32_t key, RE::INPUT_DEVICE device) const;
		void HandleMouseEvent(uint32_t key, float value, bool isPressed) const;
	};
}