# Spell Absorption Rework DLL

Spell Absorption Function is sourced from Magic Tweaks by SeaSparrow. Big Thanks to them!
https://github.com/SeaSparrowOG/MagicTweaks

1.5 Version is based on the conversion made by Fuzzlesz.
https://github.com/Fuzzlesz/MagicTweaks-1.5/tree/7d953632dbeb3f73ebbeb7433f24fb986c301805


## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++

## Register Visual Studio as a Generator
* Open `x64 Native Tools Command Prompt`
* Run `cmake`
* Close the cmd window

## Building
```
git clone https://github.com/tomnGithub/SpellAbsorptionRework_DLL
cd SpellAbsorptionRework_DLL
cmake --preset vs2022-windows-vcpkg-release
cmake --build build --config Release

```

