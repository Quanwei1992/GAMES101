git submodule init
git submodule update
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg install opencv:x64-windows eigen3:x64-windows
echo done