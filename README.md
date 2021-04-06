
# CppOpenCV
Template Visual Studio C++ solution using OpenCV.

## Requirements
- Windows 10
- Visual Studio 2019(configurations is x64-Debug or x64-Release)
- C++14 or over
- OpenCV (any version which ready for VS2019 and has opencv_world*.dll)
  - We used 4.5.1

## Installation(windows)
1. Clone Repository
2. Download and Place OpenCV
   - Download OpenCV from [official page](https://opencv.org/releases/)(For example opencv-4.5.1-vc14_vc15.exe)
   - Execute downloaded file and expand files in `lib` folder of this repogitory
![README_step2](https://user-images.githubusercontent.com/52093236/113714619-8cfd6b80-9723-11eb-8aec-967a5ce3e4f4.png)
3. Change Project Setting
   - Execute `scripts/step3_SetOpencvVersion.bat`and change OpenCV version information in project setting file(`CppOpenCV\CppOpenCV.vcxproj`)
     - This batch require the version string of placed OpenCV
     - For example: `lib\opencv\build\x64\vc15\bin\opencv_world451.dll` then input `451`
     - this batch overwrite the project setting file by the replaced template(`CppOpenCV\CppOpenCV.vcxproj_sample`) content.
       - version string pattern `%OPENCV_VERSION%` is replaced to inputted string.
   - This step overwite project setting file.If you already changed project files(added source code/change project setting or etc.), you should do this step by manually(change %OPENCV_VERSION% pattern in project setting file to your placed OpenCV version string).
4. Build and Run
   - x64/Debug or x64/Release are available 
