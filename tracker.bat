@echo off
setlocal

chcp 65001 > nul

rem заменить на путь к BOOST на компьютере
set BOOST_PATH=D:\boost_1_87_0\boost_1_87_0
rem заменить на путь расположения
call "D:\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"

Cl.exe /EHsc /I"%BOOST_PATH%" /c /Zi /nologo /W3 /WX- /O2 /Oi /Oy- /D WIN32 /D NDEBUG /D _CONSOLE /D _UNICODE /D UNICODE /Gm- /MD /GS /Gy /fp:precise /Zc:wchar_t /Zc:forScope /Fo"" /Fd"vc140.pdb" /Gd /TP /analyze- %~dp0src\tracker(client)\Tracker.cpp
Link.exe /OUT:tracker.exe /NOLOGO /PDB:"v140.pdb" /SUBSYSTEM:CONSOLE /MACHINE:X86 tracker.obj

del %~dp0*.pdb
del %~dp0*.obj

if errorlevel 1 (
    echo Ошибка компиляции!
    exit /b 1
)

start tracker.exe

endlocal
