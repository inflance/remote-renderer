@echo off
setlocal enabledelayedexpansion

REM Set variables
set "progress="
set "total=14"
set "current=1"

REM Function to update progress bar
:UpdateProgress
set "progress="
for /L %%A in (1,1,%current%) do set "progress=!progress!#"
for /L %%A in (%current%,1,%total%) do set "progress=!progress! "

REM Clear the screen
cls

REM Display progress bar
echo Progress: [!progress!]

REM Check if Python is installed
python --version >nul 2>&1
if %errorlevel% equ 0 (
    echo Python is already installed
) else (
    echo Python not found, downloading and installing Python
    REM Download Python installer
    powershell -Command "(New-Object System.Net.WebClient).DownloadFile('https://www.python.org/ftp/python/3.9.7/python-3.9.7-amd64.exe', 'python_installer.exe')"

    REM Install Python
    echo Installing Python...
    start /wait python_installer.exe /quiet InstallAllUsers=1 PrependPath=1

    REM Delete the downloaded installer
    del python_installer.exe

    REM Verify Python installation
    python --version >nul 2>&1
    if %errorlevel% equ 0 (
        echo Python installed successfully
    ) else (
        echo Python installation failed. Please install Python manually and make sure to add it to the system path.
        exit /b 1
    )

    set /a "current+=1"
    goto :RunPythonScript
)

:RunPythonScript
REM Run the Python script
echo Running the Python script...
python download_vcpkg.py

set /a "current+=1"
goto :CheckVCPKGRoot

:CheckVCPKGRoot
REM Check if VCPKG_ROOT environment variable is set
if not defined VCPKG_ROOT (
    echo VCPKG_ROOT environment variable is not set. Please set it manually.
    exit /b 1
)

set /a "current+=1"
goto :Completion

:Completion
echo VCPKG download and setup completed
exit /b 0
