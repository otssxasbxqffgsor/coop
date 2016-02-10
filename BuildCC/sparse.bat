svn co --depth immediates --non-interactive --force --ignore-externals ^
	https://gaq300m-svn01.gs.adinternal.com/svn/Accpac6/trunk CC ^
	--username pgoertz --password vR4kRsqUJdb
cd CC
pause

call :up.XX ar
call :up.XX ew
call :up.XX oe
call :up.XX yp
call :build

goto :EOF


:up.XX  :  XX
if not exist %1 (
    echo>&2 Skipped %1
    goto :EOF
)
echo>&2 Setting up %1
svn up --set-depth immediates  --non-interactive  --force  %1		--username pgoertz --password vR4kRsqUJdb
svn up --set-depth infinity    --non-interactive  --force  %1\base	--username pgoertz --password vR4kRsqUJdb
svn up --set-depth immediates  --non-interactive  --force  %1\main	--username pgoertz --password vR4kRsqUJdb
if exist %1\build (
    svn up --set-depth infinity    --non-interactive  --force  %1\build	--username pgoertz --password vR4kRsqUJdb
)
if exist %1\portlets (
    svn up --set-depth immediates  --non-interactive  --force  %1\portlets		--username pgoertz --password vR4kRsqUJdb
    svn up --set-depth infinity    --non-interactive  --force  %1\portlets\common	--username pgoertz --password vR4kRsqUJdb
)
goto :EOF

:build
call build.bat
goto :EOF


