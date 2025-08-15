#include "NoiseGen.h"

#include <format>
#include <iostream>
#include <fstream> 
#include "ImageSettings.h"


int main(int argc, char* argv[])
{
	image imgSet;
	
	float lacunarity = 2.0f;
	float persistance = 0.5f;
	float scale = 1.0f;
	float freq = 0.01f;
	float octaves = 4;
	bool ridge = false;
	int ridgePower = 1;
	int seed = 1234;

	for (int i = 0; i < argc;)
	{
		if (argc == 1)
			break;
		
		std::string arg = argv[i];
		if (i + 1 < argc)
		{
			if (arg == "-o")
			{
				arg = argv[i + 1];
				imgSet.outPath = arg;
				i += 2;
			}
			else if (arg == "-h")

			{
				arg = argv[i + 1];
				imgSet.height = std::stoi(arg);
				i += 2;
			}
			else if (arg == "-w")
			{
				arg = argv[i + 1];
				imgSet.width = std::stoi(arg);
				i += 2;
			}
			// Noise Settings
			else if (arg == "-depth")
			{
				arg = argv[i + 1];
				imgSet.colorDepth = std::stoi(arg);
				i += 2;
			}
			else if (arg == "-lac")
			{
				arg = argv[i + 1];
				lacunarity = std::stof(arg);
				i += 2;
			}
			else if (arg == "-pers")
			{
				arg = argv[i + 1];
				persistance = std::stof(arg);
				i += 2;
			}
			else if (arg == "-scale")
			{
				arg = argv[i + 1];
				scale = std::stof(arg);
				i += 2;
			}
			else if (arg == "-freq")
			{
				arg = argv[i + 1];
				freq = std::stof(arg);
				i += 2;
			}
			else if (arg == "-oct")
			{
				arg = argv[i + 1];
				octaves = std::stoi(arg);
				i += 2;
			}
			else if (arg == "-pow")
			{
				arg = argv[i + 1];
				ridgePower = std::stoi(arg);
				i += 2;
			}
			else if (arg == "-seed")
			{
				arg = argv[i + 1];
				seed = std::stoi(arg);
				i += 2;
			}
			else if (arg == "-ridge")
			{
				ridge = true;
				i++;
				continue;
			}
			else
			{
				i++;
			}
		}
		else if (arg == "--h")
		{
			std::cout << "Image Settings:" << std::endl;
			std::cout << "-h		| set output image height" << std::endl;
			std::cout << "-w		| set output image width" << std::endl;
			std::cout << "-depth		| range for a gradient to be applied" << std::endl;
			std::cout << "-o		| output file path" << std::endl;

			std::cout << "Noise Settings:" << std::endl;
			std::cout << "-seed		| sets noise seed" << std::endl;
			std::cout << "-lac		| sets noise lacunarity" << std::endl;
			std::cout << "-pers		| sets noise persistence" << std::endl;
			std::cout << "-scale		| sets noise scale" << std::endl;
			std::cout << "-freq		| sets noise frequency" << std::endl;
			std::cout << "-oct		| sets noise octaves count" << std::endl;
			std::cout << "-ridge		| enables noise ridge" << std::endl;
			std::cout << "-pow		| sets ridge power, does not work if -ridge is not used" << std::endl;
			return 0;
		}
		else
		{
			std::cerr << "Incorrect arguments provided, see usage [--h]" << std::endl;
			return 1;
		}
	}


	NosieSettings settings(1222, FastNoiseLite::NoiseType_Perlin, imgSet.height);
	settings.noiseMaxHeight = imgSet.colorDepth;
	settings.noiseSeed = seed;
	settings.lacunarity = lacunarity;
	settings.persistance = persistance;
	settings.noiseScale = scale;
	settings.baseFrequency = freq;
	settings.octaves = octaves;
	settings.ridge = ridge;
	settings.ridgePower = ridgePower;

	std::string header = std::format("P2\n\{} {}\n{}\n", imgSet.height, imgSet.width, imgSet.colorDepth);
	std::ofstream outFile(imgSet.outPath);
	if (!outFile.is_open())
		return -1;
	
	outFile << header;

	NoiseGenerator noiseGen(settings);
	for (int x = 0; x < imgSet.width; x++)
	{
		for (int y = 0; y < imgSet.height; y++)
		{
			float noiseH = noiseGen.GetHeight(x, y);
			outFile << static_cast<int>(noiseH) << " ";
		}
		outFile << "\n";
	}
	outFile.close();
}