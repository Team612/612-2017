call batch\.compiler-download.bat

REM Exit if FRC C++ Toolchain not found
if exist Error.txt (
    ECHO batch\build.bat: Compiler not found
    ECHO batch\build.bat: Exiting...
    del Error.txt /Q
    GOTO error
)

ECHO build.bat: Checking internet...

Ping www.google.com -n 2 -w 1000
if errorlevel 1 (
    ECHO build.bat: Offline
) else (
    ECHO build.bat: Online
    if not exist CTRE call batch\.get-ctre.bat
    if exist CTRE.txt (
        del CTRE.txt /Q
        GOTO error
    )
    if not exist wpilib call batch\.wpilib-download.bat
    if exist wpilib.txt (
        del wpilib.txt /Q
        GOTO error
    )
    REM exit early if unable to get required materials
)

CD .build

del CMakeCache.txt cmake_install.cmake Makefile
rmdir CMakeFiles\ /S /Q

ECHO build.bat: Generating Makefiles...
cmake .. -G "NMake Makefiles" -DCMAKE_TOOLCHAIN_FILE=arm.cmake -DCMAKE_TOOLCHAIN_FILE=robot.cmake

nmake

ECHO build.bat: Deleting CMakeFiles...
rmdir CMakeFiles\ /S /Q

ECHO build.sh: Re-naming outfile...
if exist FRCUserProgram del FRCUserProgram /Q
move FRC FRCUserProgram

if exist FRCUserProgram (
    ECHO Build successfully!
    CD ..
    PAUSE
    GOTO end
) else (
    ECHO Build failed!
    CD ..
    PAUSE
    GOTO error
)

:end
EXIT

:error
EXIT /b 1
