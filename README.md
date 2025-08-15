# NosieToPBM

A lightweight tool for generating and visualizing procedural noise maps, built with [FastNoiseLite](https://github.com/Auburn/FastNoiseLite).

_This project targets only Windows._ 

## Installation

Clone repository: 

```bash
git clone https://github.com/DeTosis/noise-terrain-generation
```

Currently, the project can only be built using the provided .sln file located in the project root directory.

## Usage

* Build project with Visual Studio
* Build result will be in `"projectRoot"/_build` directory

Now you can run `NosieToPBM.exe` file directly or specify arguments to customise your nosie 

Console arguments:
~~~
Output Image Settings:
-h			| set output image height
-w			| set output image width
-depth		| range for a gradient to be applied
-o			| output file path

Noise Settings:
-seed		| sets noise seed  
-lac		| sets noise lacunarity  
-pers		| sets noise persistence  
-scale		| sets noise scale  
-freq		| sets noise frequency  
-oct		| sets noise octaves count  
-ridge		| enables noise ridge  
-pow		| sets ridge power, does not work if -ridge is not used  
~~~

The program outputs .pgm files in the [Netpbm](https://en.wikipedia.org/wiki/Netpbm) format

These can be viewed in many editors — Visual Studio Code has an extension for it.

## Noise Generation Result

<img width="520" height="520" alt="image_2025-08-16_03-55-00" src="https://github.com/user-attachments/assets/ea2145af-af83-46c3-9979-287e170f1578" />

>Settings used to generate this nosie:
>
>`NosieToPBM.exe -lac 2.1 -pers 0.48 -scale 4.4 -freq 0.01 -oct 8 -depth 128 -ridge -pow 8 -h 512 -w 512`
