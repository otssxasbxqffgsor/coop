setlocal
rem Setting up the build
rem MUST DO THIS IN THE DIRECTORY

pushd C:\DD\pr\base
call :do-setup
start "dev-setup"
popd
goto :EOF

:do-setup
  CALL setproj UP
  CALL SETUP32 UP
  CALL cryptopp-lib-build-fetch set-jenkins-job
  rem This isn't really needed, but the only harm is some extra time.
  CALL cryptopp-lib-build-fetch get
  CALL CC:\DD\pr\base\build	
  goto :EOF




