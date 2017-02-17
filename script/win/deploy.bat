@echo off

if exist .build\FRCUserProgram (
    ECHO deploy.bat: Deploying robot code...
    GOTO checkwinscp
) else (
    ECHO deploy.bat: Valid FRCUserProgram not found!
    GOTO end
)

:checkwinscp
for %%x in (winscp.exe) do (SET WINSCP=%%~$PATH:x)
if defined WINSCP (
     GOTO deploy
) else (
    GOTO noscp
)

:deploy
ECHO Enter roborio ip address
SET /p ADDRESS=Usually roborio-TEAM-frc.local, 10.TE.AM.X, or 172.22.11.2 for Static USB:
SET REMOTE_PATH=/home/lvuser/FRCUserProgram
winscp /command ^
    "open lvuser@%ADDRESS%" ^
    "ls %REMOTE_PATH%'" ^
    "exit"
if %ERRORLEVEL% neq 0 (
    GOTO scp
) else (
    GOTO filethere
)

:filethere
winscp /command ^
    "open lvuser@%ADDRESS%" ^
    "rm FRCUserProgram" ^
    "exit"
GOTO scp

:scp
winscp /command ^
    "open lvuser@%ADDRESS%" ^
    "put .build\FRCUserProgram /home/lvuser/" ^
    "chmod 754 FRCUserProgram" ^
    "exit"
ECHO deploy.bat: deployed successfully!
ECHO deploy.bat: remember to restart the robot code on the driver station!
PAUSE
GOTO end

:noscp
REM only runs if winscp isn't found in the path
ECHO deploy.bat: It looks like WinSCP has not been added to your PATH
ECHO deploy.bat: Deploying to the robot from FRC++ Build Tools requires WinSCP
ECHO deploy.bat: If you do not have the intention of deploying using WinSCP, simply copy FRCUserProgram in the .build folder to /home/lvuser on the roborio with your method of choice.
GOTO end

:end
EXIT
