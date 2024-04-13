#include "palette.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

std::unique_ptr<SLM::Color[]> SLM::Palette::colors;
int                           SLM::Palette::colorCount;

void SLM::Palette::DrawPaletteControlWindow()
{
	ImGui::SliderInt("Choose a color", &chosenColor, 0, GetColorCount() - 1, GetColorsNames(chosenColor));
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

		colorCount = colorsJson.size();
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
