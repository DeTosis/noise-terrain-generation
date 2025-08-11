#include <format>
#include <iostream>
#include <fstream> 
# include "fastNoise/FastNoiseLite.h"

float RidgeNoise(FastNoiseLite& noise, float x, float y)
{
	return 2 * (0.5f - std::abs((0.5f - noise.GetNoise(x, y))));
}

struct NoiseSettings
{

};


float GetHeight(FastNoiseLite& noise, int x, int y, int octaves, int maxHeight)
{
	float noiseHeight = 0.0f;

	float lacunarity = 2.0f;
	float persistance = 0.55f;

	float frequency = 0.01f;
	float amplitude;

	float ampSum = 0.0f;
	float nearest = 11.0f;
	float scale = 1.1f;

	float bigScale = 1.5f;
	float detailScale = 0.25f;
	float bias = 0.15f;

	noise.SetFrequency(frequency);
	for (int octave = 0; octave < octaves; octave++)
	{
		frequency = (std::powf(lacunarity, octave));
		amplitude = (std::powf(persistance, octave));

		float sampleX = x / scale * frequency;
		float sampleY = y / scale * frequency;

		float perlinValue = noise.GetNoise(sampleX, sampleY);
		noiseHeight += (float)(perlinValue * amplitude);

		ampSum += amplitude;
	}

	noiseHeight /= ampSum;

	noiseHeight = (noiseHeight + 1.0f) / 2.0f;
	noiseHeight *= maxHeight;

	return noiseHeight;
}

int main()
{
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise.SetSeed(1488);


	int h = 400;
	int w = 400;
	int maxHeight = 12;
	
	std::string header = std::format("P2\n\{} {}\n{}\n",h,w, maxHeight);
	std::ofstream outFile("out.pgm");
	if (!outFile.is_open())
	{
		std::cerr << "[ FILE COULD NOT BE OPENED]" << std::endl;
		return -1;
	}

	outFile << header;


	for (int x = 0; x < h; x++)
	{
		for (int y = 0; y < w; y++)
		{
			float noiseH = GetHeight(noise, x, y, 8, maxHeight);
			outFile << static_cast<int>(noiseH) << " ";
		}
		outFile << "\n";
	}
	outFile.close();


	std::cout << "Application ended" << std::endl;
}