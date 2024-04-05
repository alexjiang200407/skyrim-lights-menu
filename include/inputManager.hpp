#pragma once

namespace SLM
{
	class InputManager :
		public RE::BSTEventSink<RE::InputEvent*>
	{
	public:
		static ImGuiKey ToImGuiKey(RE::BSWin32KeyboardDevice::Key a_key);

	private:
		RE::BSEventNotifyControl ProcessEvent(
			RE::InputEvent* const* ppEvent,
			RE::BSTEventSource<RE::InputEvent*>*) override;
	};
}