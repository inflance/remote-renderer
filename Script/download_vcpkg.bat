@echo off

REM Set the vcpkg download link and version
set "vcpkg_url=https://codeload.github.com/microsoft/vcpkg/zip/refs/tags/2023.11.20"

REM Set the extraction path
set "vcpkg_root=C:\vcpkg"


REM Set the VCPKG_ROOT environment variable
setx VCPKG_ROOT "%vcpkg_root%" /M

echo vcpkg installed successfully, and VCPKG_ROOT set to: %vcpkg_root%

REM You can continue with other vcpkg-related operations here, such as installing libraries
REM For example, run vcpkg install <package-name>
vcpkg install <package-name>

echo Press Enter to exit...
pause > nul
