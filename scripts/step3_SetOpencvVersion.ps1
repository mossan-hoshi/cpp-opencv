Push-Location $PSScriptRoot

$SRC_PATH = '../CppOpenCV/CppOpenCV.vcxproj_sample'
$TARGET_PATH = '../CppOpenCV/CppOpenCV.vcxproj'
$SEARCH_STR= '%OPENCV_VERSION%'

$REPLACE_STR=$(Read-Host "Enter OpenCV version string`n(ex. opencvworld451.dll -> enter 451)" )

(Get-Content -Encoding UTF8 $SRC_PATH) -replace $SEARCH_STR,$REPLACE_STR > $TARGET_PATH

Pop-Location