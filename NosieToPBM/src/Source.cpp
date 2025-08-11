#include <format>
#include <iostream>
#include <fstream> 
# include "fastNoise/FastNoiseLite.h"
#include "NoiseGen.h"

int main()
{
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise.SetSeed(1488);

	int h = 512;
	int w = 512;
	int maxHeight = 16;

	NosieSettings def{4.0f, 0.55f, 1.1f, 0.01f, 8, maxHeight, true, 3};
	NosieSettings biom{2.5f, 0.3f, 0.4f, 0.001f, 4, maxHeight, false, 0};

	std::string header = std::format("P2\n\{} {}\n{}\n", h, w, maxHeight);
	std::ofstream outFile("out.pgm");
	if (!outFile.is_open())
		return -1;
	
	outFile << header;

	NoiseGenerator noiseGen;

	for (int x = 0; x < h; x++)
	{
		for (int y = 0; y < w; y++)
		{
			float noiseH = noiseGen.GetHeight(noise, x, y, biom);
			outFile << static_cast<int>(noiseH) << " ";
		}
		outFile << "\n";
	}
	outFile.close();

	std::cout << "Application ended" << std::endl;
}