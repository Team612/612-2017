@echo off

if exist .build\FRCUserProgram (
    ECHO deploy.bat: Deploying robot code...
    GOTO checkwinscp
) else (
    ECHO deploy.bat: Valid FRCUserProgram not found!
    GOTO noscp
)

:checkwinscp
for %%x in (winscp.exe) do (SET WINSCP=%%~$PATH:x)
if defined WINSCP GOTO deploy

:deploy
ECHO Enter roborio ip address
SET /p ADDRESS=Usually roborio-TEAM-frc.local, 10.TE.AM.X, or 172.22.11.2 for Static USB:
winscp lvuser@%ADDRESS% /upload .build\FRCUserProgram
ECHO deploy.bat: deployed successfully!
PAUSE
GOTO end

:noscp
REM only runs if winscp isn't found in the path
ECHO .deploy.bat: It looks like WinSCP has not been added to your PATH
ECHO .deploy.bat: Deploying to the robot from FRC++ Build Tools requires WinSCP
ECHO .deploy.bat: If you do not have the intention of deploying using WinSCP, simply copy FRCUserProgram in the .build folder to /home/lvuser on the roborio with your method of choice.
GOTO end

:end
EXIT
