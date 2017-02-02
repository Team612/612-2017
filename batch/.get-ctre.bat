@echo off

ECHO ^.get-ctre^.bat: Downloading CTRE^.^.^.

if defined ProgramFiles(x86) (
    for %%x in (wget64.exe) do (SET WGET=%%~$PATH:x)
    if defined WGET (
        wget64.exe -r -nd --progress=bar http://www.ctr-electronics.com//downloads/lib/CTRE_FRCLibs_NON-WINDOWS.zip
        GOTO get-ctre
    ) else (
        ECHO ^.get-ctre^.bat: Please download wget64 and add it to the PATH
        GOTO error
    )
) else (
    REM assuming 32 bit
    for %%x in (wget.exe) do (SET WGET=%%~$PATH:x)
    if defined WGET (
        wget.exe -r -nd --progress=bar http://www.ctr-electronics.com//downloads/lib/CTRE_FRCLibs_NON-WINDOWS.zip
        GOTO get-ctre
    ) else (
        ECHO ^.get-ctre^.bat: Please download wget ^(32 bit^)^. Add it to the PATH
        GOTO error
    )
)

REM if there was no error, unzip
REM lol downloading the non-windows even though this is windows
:get-ctre
mkdir ctre_full
CD ctre_full
unzip ..\CTRE_FRCLibs_NON-WINDOWS.zip
ECHO ^.get-ctre^.bat: Cleaning up^.^.^.
CD ..
ECHO D | xcopy ctre_full\cpp CTRE /s/e
rmdir ctre_full\ /S /Q
del CTRE_FRCLibs_NON-WINDOWS^.zip /Q
GOTO end

:error
ECHO. 1>CTRE^.txt
GOTO end

:end
