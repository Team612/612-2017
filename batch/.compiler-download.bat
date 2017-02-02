@echo off

REM Doesn't actually download compiler because on windows its a nice installer already.

for %%x in (arm-frc-linux-gnueabi-g++.exe) do (SET FOUND=%%~$PATH:x)
if defined FOUND (
    ECHO ^.compiler-download.bat: Valid FRC Compiler found in PATH!
    GOTO end
) else (
    GOTO no-compiler
)

:no-compiler
ECHO ^.compiler-download.bat: Valid FRC Compiler not found in PATH!
ECHO ^.compiler-download.bat: Please download the FRC Compiler from: http://first.wpi.edu/FRC/roborio/toolchains/
ECHO. 1>Error.txt
GOTO end

ECHO .compiler-download.bat: Exiting...
GOTO end

:end
