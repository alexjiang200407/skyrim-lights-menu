#include "palette.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include "imguiUtil.hpp"

std::unique_ptr<SLM::Color[]> SLM::Palette::colors;
int                           SLM::Palette::colorCount;

SLM::Rgb SLM::Palette::DrawControlWindow()
{
	ImGui::RadioButton("Preset Color", &chooseCustomColor, 0);
	ImGui::SameLine();
	ImGui::RadioButton("Custom Color", &chooseCustomColor, 1);

	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
	ImGui::Combo(
		"Preset", &chosenPresetIndex, [](void*, int idx, const char** out_pcstr)
		{ 
			*out_pcstr = GetColorsNames(idx);

			return true;
		}, nullptr,
		GetColorCount()
	);

	ImGui::ColorEdit3("Color", customColor);

	if (chooseCustomColor == 1)
	{
		return Rgb{ uint8_t(customColor[0] * 255), uint8_t(customColor[1] * 255), uint8_t(customColor[2] * 255) };
	}
	ImGui::PopItemWidth();
	return std::get<1>(colors[chosenPresetIndex]);
}

const char* SLM::Palette::GetColorsNames(size_t index)
{
	assert(index < colorCount);
	return std::get<0>(colors.get()[index]).c_str();
}

void SLM::Palette::LoadPaletteFile()
{
	using json = nlohmann::json;

	std::ifstream file{ filePath.data() };

	if (file.fail())
	{
		logger::warn("File at {} does not exist", filePath);
		return;
	}

	try
	{
		json data = json::parse(file);

		colors.reset();

		json colorsJson = data["colors"];

		colorCount = static_cast<int>(colorsJson.size());
		logger::info("found {} colors in JSON file", colorCount);
		colors = std::make_unique<Color[]>(colorCount);

		int i = 0;
		for (const json color : colorsJson)
		{
			const auto rgb  = color["rgb"];
			colors.get()[i] = std::make_tuple(color["name"], std::make_tuple(rgb[0], rgb[1], rgb[2]));
			i++;
		}
	}
	catch (json::parse_error e)
	{
		logger::error("{} at byte {}", e.what(), e.byte);
	}
	catch (json::exception e)
	{
		logger::error("{}", e.what());
	}
}
