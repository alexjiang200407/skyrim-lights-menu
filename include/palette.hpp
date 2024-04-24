#pragma once

namespace SLM
{
	typedef std::tuple<uint8_t, uint8_t, uint8_t> Rgb;
	typedef std::tuple<std::string, Rgb>          Color;

	class Palette
	{
	private:
		enum SelectionMode : int
		{
			kPresetColor = 0,
			kCustomColor = 1,
		};

	public:
		Rgb                 DrawControlWindow();
		int                 GetColorCount() const { return colorCount; }
		int                 GetCurrentPresetIndex() const { return chosenPresetIndex; }
		void                Serialize(SKSE::SerializationInterface* intfc) const;
		void                Deserialize(SKSE::SerializationInterface* intfc);
		static const char*  GetColorsNames(size_t index);
		static const Color* GetColors() { return colors.get(); }
		static void         LoadPaletteFile();
		Rgb                 GetCurrentColor() const;

	private:
		int                               chosenPresetIndex  = 0;
		enum SelectionMode                colorSelectionMode = kPresetColor;
		float                             customColor[3]     = { 0.0f, 0.0f, 0.0f };
		static int                        colorCount;
		static std::unique_ptr<Color[]>   colors;
		static constexpr std::string_view filePath = "./Data/SKSE/Plugins/SkyrimLightsMenuPresets.json"sv;
	};
}