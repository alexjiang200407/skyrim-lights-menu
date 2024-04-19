#pragma once

namespace SLM
{
	typedef std::tuple<uint8_t, uint8_t, uint8_t> Rgb;
	typedef std::tuple<std::string, Rgb>          Color;

	class Palette
	{
	public:
		Rgb                 DrawControlWindow();
		int                 GetColorCount() const { return colorCount; }
		static const char*  GetColorsNames(size_t index);
		static const Color* GetColors() { return colors.get(); }
		static void         LoadPaletteFile();

	private:
		int                               chosenPresetIndex = 0;
		int                               chooseCustomColor = 0;
		float                             customColor[3]    = { 0.0f, 0.0f, 0.0f };
		static int                        colorCount;
		static std::unique_ptr<Color[]>   colors;
		static constexpr std::string_view filePath = "./Data/SKSE/Plugins/SkyrimLightsMenu.json"sv;
	};
}