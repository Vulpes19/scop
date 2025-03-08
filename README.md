# scop

$env:PATH = "$env:VCPKG_ROOT;$env:PATH"
$env:VCPKG_ROOT = "C:\Users\asus\vcpkg"

rm -rf build
cmake --preset vpckg
cmake --build build