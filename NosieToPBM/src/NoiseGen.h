#pragma once
# include "fastNoise/FastNoiseLite.h"

struct NosieSettings
{
	NosieSettings(int seed, FastNoiseLite::NoiseType type, float maxHeight)
		: noiseSeed(seed), noiseType(type), noiseMaxHeight(maxHeight)
	{}

	int noiseSeed;
	FastNoiseLite::NoiseType noiseType;

	float lacunarity;
	float persistance;

	float noiseScale;
	float baseFrequency;
	int octaves;

	float noiseMaxHeight;
	bool  ridge;
	int	  ridgePower;
};

FastNoiseLite m_Noise;

class NoiseGenerator
{
private:
	FastNoiseLite m_Noise;
	NosieSettings m_Set;
public:
	NoiseGenerator(NosieSettings set)
		: m_Set(set)
	{
		m_Noise.SetNoiseType(set.noiseType);
		m_Noise.SetSeed(set.noiseSeed);
	}

	inline float GetHeight(int x, int y)
	{
		float frequency = m_Set.baseFrequency;
		float amplitude;
		float ampSum = 0.0f;

		float noiseHeight = 0.0f;
		m_Noise.SetFrequency(frequency);
		for (int octave = 0; octave < m_Set.octaves; octave++)
		{
			frequency = (std::powf(m_Set.lacunarity, octave));
			amplitude = (std::powf(m_Set.persistance, octave));

			float sampleX = x / m_Set.noiseScale * frequency;
			float sampleY = y / m_Set.noiseScale * frequency;

			float perlinValue = m_Noise.GetNoise(sampleX, sampleY);

			if (m_Set.ridge)
			{
				perlinValue = 1.0 - fabs(perlinValue);
				perlinValue = pow(perlinValue, m_Set.ridgePower);
			}

			noiseHeight += perlinValue * amplitude;
			ampSum += amplitude;
		}
		noiseHeight /= ampSum;

		noiseHeight = (noiseHeight + 1.0f) * 0.75f - 0.5f;
		noiseHeight *= m_Set.noiseMaxHeight;

		return noiseHeight;
	}
};