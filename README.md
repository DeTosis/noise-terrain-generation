# NosieToPBM

A lightweight tool for generating and visualizing procedural noise maps, built with [FastNoiseLite](https://github.com/Auburn/FastNoiseLite).

## Installation

Clone repository: 

```bash
git clone https://github.com/DeTosis/noise-terrain-generation
```

_This project targets Windows._ 

Currently, the project can only be built using the provided .sln file located in the project root directory.

## Usage

The program outputs .pgm files in the [Netpbm](https://en.wikipedia.org/wiki/Netpbm) format

These can be viewed in many editors — Visual Studio Code has an extension for it.

> _Console arguments are not yet implemented; noise settings must be changed directly in the code._

Settings are defined in structure `NosieSettings`
```cpp
struct NosieSettings
{
	float lacunarity;
	float persistance;

	float noiseScale;
	float baseFrequency;
	float octaves;

	float maxHeight;
	bool  ridge;
	int	  ridgePower;
};
```

---
## Noise Generation Result [.pbm]
Settings used: `NosieSettings def{ 2.1f, 0.48f, 4.4f, 0.01f, 8, maxHeight / 2, true, 8 };`

<img width="521" height="520" alt="ex" src="https://github.com/user-attachments/assets/57761a87-6b94-4c0c-b6f3-262946aa44cf" />

