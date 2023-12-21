@echo off
SETLOCAL
for /r %%i in (*.sln) do (
    echo %%i is building...
    msbuild "%%i" -nologo -consoleLoggerParameters:ErrorsOnly -p:WarningLevel=4;Configuration=Debug -target:Rebuild
    IF ERRORLEVEL 1 (
        ECHO Result: failure
    ) ELSE (
        ECHO Result: success
    )
)
echo.
echo.
for /r %%i in (*.exe) do (
    "%%i" -tests
    IF ERRORLEVEL 1 (
        ECHO %%i tests were not passed
    ) ELSE (
        ECHO %%i tests were passed
    )
)
