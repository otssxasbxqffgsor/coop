@echo off
setlocal
if (%1) == (make-release-build) goto _make-release-build
if (%1) == (make-release-controlled) goto _make-release-controlled
if (%1) == (build) goto _build
if (%1) == (package-build) goto _package-build
if (%1) == (package-controlled) goto _package-controlled
if (%1) == (publish) goto _publish
if (%1) == (help) goto _help
if (%1) == () goto _help
echo %1?
:_help
echo usage jenkins-build command...
echo full-process commands
echo  make-release-build path-to-target: build, package, and publish
echo  make-release-controlled path-to-target: package controlled, and publish
echo component commands:
echo  build: build from source
echo  package-build: copy artifacts and create zip
echo  package-controlled: svn-export artifacts and create zip
echo  publish path-to-target: publish to specified location
if (%1) == (help) exit /b 0
exit /b 1

:_make-release-build
  call %~dpf0 build
  if errorlevel 1 exit /b 1
  call %~dpf0 package-build
  if errorlevel 1 exit /b 1
  call %~dpf0 publish %2
  if errorlevel 1 exit /b 1
  goto :EOF

:_make-release-controlled
  call %~dpf0 package-controlled
  if errorlevel 1 exit /b 1
  call %~dpf0 publish %2
  if errorlevel 1 exit /b 1
  goto :EOF

:_build
  echo build at %date% %time%
  call :_build-setup-vcvars
  if errorlevel 1 exit /b 1
  pushd build
  call build
  popd
  goto :EOF

:_build-setup-vcvars
  goto _build-setup-vcvars-vs8

:_build-setup-vcvars-vs8
  if ("%VS90COMNTOOLS%") == ("") goto :EOF
  echo setting up VS8 tools at %date% %time%
  call "%VS80COMNTOOLS%\..\..\VC\vcvarsall.bat"
  goto :EOF

:_build-setup-vcvars-vs9
  if ("%VS90COMNTOOLS%") == ("") goto :EOF
  echo setting up VS9 tools at %date% %time%
  call "%VS90COMNTOOLS%\..\..\VC\vcvarsall.bat"
  goto :EOF

:_package-controlled
:_package-build
  echo packaging at %date% %time%
  if exist tmp rd /s/q tmp
  mkdir tmp
  mkdir tmp\info
  call :_%1-artifacts
  if errorlevel 1 exit /b 1
  svn info build > tmp\info\svn-info.txt
  set > tmp\info\environment.txt
  echo %1 at %date% %time% > tmp\info\package-time.txt
  if exist target.new rd /s/q target.new
  mkdir target.new
  pushd tmp
  7z.exe a -r ..\target.new\cryptopp-lib.zip *
  popd
  if errorlevel 1 exit /b 1
  7z.exe l    target.new\cryptopp-lib.zip > target.new\cryptopp-lib.zip.manifest.txt
  if errorlevel 1 exit /b 1
  if exist target rd /s/q target
  ren target.new target
  rd /s/q tmp
  echo done at %date% %time%
  goto :EOF

:_package-controlled-artifacts
  svn export build\artifacts tmp\artifacts
  goto :EOF
:_package-build-artifacts
  mkdir tmp\artifacts
  xcopy /s /e /i build\artifacts\*.* tmp\artifacts
  goto :EOF

:_publish
  if exist tools path %cd%\tools;%PATH%
  if (%2) == () goto _help
  set origin=%cd%
  pushd %2
  if errorlevel 1 exit /b 1
  call :_publish-here %*
  popd
  if not errorlevel 1 goto :EOF
  echo error in copy!
  exit /b 1
:_publish-here
  call :_publish-build-info
  if not exist crypto-lib mkdir crypto-lib
  cd crypto-lib
  if not exist %PACKAGE% mkdir %PACKAGE%
  cd %PACKAGE%
  copy /y %origin%\target\cryptopp-lib.* .
  copy /y %origin%\target\cryptopp-lib.zip .\cryptopp-lib.%REVISION%.zip
  goto :EOF
 
:_publish-build-info
  7z e -so %origin%\target\cryptopp-lib.zip info\package-time.txt | awk "{ print \"set PACKAGE=\" $1; }" > _xxx.bat
  call _xxx
  7z e -so %origin%\target\cryptopp-lib.zip info\svn-info.txt | awk "$1 ~ /Revision:/ { print \"set REVISION=\" $2; }" > _xxx.bat
  call _xxx
  del _xxx.bat
  goto :EOF

