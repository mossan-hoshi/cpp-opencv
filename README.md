# CppOpenCV
Template Visual Studio C++ solution using OpenCV.

## Requirements
- Windows 10
- Visual Studio 2019(configurations is x64-Debug or x64-Release)
- [p-ranav/argparse](https://github.com/p-ranav/argparse)(submodule in `lib/argparse`)
  - It requires C++17
- OpenCV (any version which ready for VS2019 and has opencv_world*.dll)
  - We used 4.5.1

## Installation(windows)
1. Clone Repository
2. Download and Place OpenCV
   - Download OpenCV from [official page](https://opencv.org/releases/)(For example opencv-4.5.1-vc14_vc15.exe)
   - Execute downloaded file and expand files in `lib` folder of this repogitory
3. Change Project Setting
   - Execute `scripts/step3_SetOpencvVersion.bat`and change OpenCV version information in project setting file(`CppOpenCV\CppOpenCV.vcxproj`)
     - This batch require the version string of placed OpenCV
     - For example: `lib\opencv\build\x64\vc15\bin\opencv_world451.dll` then input `451`
     - this batch overwrite the project setting file by the replaced template(`CppOpenCV\CppOpenCV.vcxproj_sample`) content.
       - version string pattern `%OPENCV_VERSION%` is replaced to inputted string.
   - This step overwite project setting file.If you manually changed project setting file, you should do this step by manually.
4. Build and Run