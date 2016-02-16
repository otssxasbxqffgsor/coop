@echo off
set _arg=%1
call :up.arg
goto :EOF

:up.arg
REM STEP 1: COPY the C:\CC\yp\base\mysetproj.bat to C:\CC\yp\base\mysetproj.bat
XCOPY C:\GitHub\CrackingCodingInterview\BuildCC\mysetproj.bat C:\CC\yp\base\ /s /y
pushd C:\CC\yp\base
call  mysetproj.bat

@echo on 
echo "Calling Build"
@echo off
pushd C:\CC\yp\base\
call  build.bat


goto :EOF


