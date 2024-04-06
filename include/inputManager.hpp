#pragma once

namespace SLM
{
	class InputManager :
		public RE::BSTEventSink<RE::InputEvent*>
	{
	public:
		static ImGuiKey ToImGuiKey(RE::BSWin32KeyboardDevice::Key a_key);
		static ImGuiKey ToImGuiKey(RE::BSWin32GamepadDevice::Key a_key);

	private:
		RE::BSEventNotifyControl ProcessEvent(
			RE::InputEvent* const* ppEvent,
			RE::BSTEventSource<RE::InputEvent*>*) override;

		void HandleKeyboardEvent(uint32_t key, RE::INPUT_DEVICE device, bool isPressed) const;

		void HandleMouseEvent(uint32_t key, float value, bool isPressed) const;
	};
}