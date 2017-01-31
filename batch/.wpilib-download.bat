@echo off

REM This scripts downloads the latest version of wpilib.
REM It does not check for the latest version
REM To ensure the installation of the latest version, run nmake -f Makefile.win update

if defined ProgramFiles(x86) (
    for %%x in (wget64.exe) do (SET WGET=%%~$PATH:x)
    if defined WGET (
        wget64.exe http://first.wpi.edu/FRC/roborio/release/eclipse/plugins/edu.wpi.first.wpilib.plugins.cpp_2017.1.1.jar
        ECHO yay
    ) else (
        ECHO ".get-ctre.bat: Please download wget64. Add it to the PATH"
        ECHO 1>wpilib.txt
    )
) else (
    REM assuming 32 bit
    for %%x in (wget.exe) do (SET WGET=%%~$PATH:x)
    if defined WGET (
        wget.exe http://first.wpi.edu/FRC/roborio/release/eclipse/plugins/edu.wpi.first.wpilib.plugins.cpp_2017.1.1.jar
    ) else (
        ECHO ".get-ctre.bat: Please download wget (32 bit). Add it to the PATH"
        ECHO. 1>wpilib.txt
    )
)

REM if there was no error, unzip
if not exist wpilib.txt (
    mkdir wpilib
    CD wpilib
    unzip ..\edu.wpi.first.wpilib.plugins.cpp_2017.1.1.jar
    rmdir edu /S /Q
	rmdir META-INF /S /Q
	rmdir plugin.xml /S /Q
    unzip resources\cpp.zip
    ECHO ".wpilib-download.bat: Cleaning up..."
    rmdir resources\ /S /Q
    CD ..
    del edu.wpi.first.wpilib.plugins.cpp_2017.1.1.jar /Q
)
