
SLM::ScreenSize SLM::GetScreenSize()
{
	// This is a global managed by Renderer, but not part of the RendererData struct.
	// We pass back the value so users are not tempted to modify this directly.
	REL::Relocation<ScreenSize*> singleton{ RELOCATION_ID(525002, 411483) };
	return *singleton;
}