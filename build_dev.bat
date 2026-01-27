@echo off
echo Building Quake 2 Muffmode DLL (DEBUG/DEV BUILD)...
echo.
echo WARNING: This build includes developer-only weapon balance cvars!
echo.

REM Find Visual Studio Build Tools
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64

REM Build the project in Debug configuration
msbuild src\MuffMode.sln /p:Configuration=Debug /p:Platform=x64

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! 
    echo Game DLL created: game_x64.dll (DEBUG BUILD)
    echo.
    echo NOTE: This DLL contains developer-only cvars for weapon balance testing.
    echo Do NOT distribute this build to players!
    echo.
    
    REM Copy DLL to Quake 2 directory
    echo Copying game_x64.dll to Quake 2 directory...
    copy /Y "game_x64.dll" "g:\Program Files (x86)\Steam\steamapps\common\Quake 2\rerelease\muffmode\"
    
    if %ERRORLEVEL% EQU 0 (
        echo DLL copied successfully!
        echo.
        echo Press Enter to launch Quake 2, or close this window to skip...
        pause >nul
        echo.
        echo Launching Quake 2...
        start "" "g:\Program Files (x86)\Steam\steamapps\common\Quake 2\rerelease\quake2ex_steam.exe" +set game muffmode +set deathmatch 1 +set timelimit 10 +set cheats 1 +map 2box4
    ) else (
        echo Warning: Failed to copy DLL. Check permissions.
    )
    
    echo.
) else (
    echo.
    echo Build failed. Check the output above for errors.
)

