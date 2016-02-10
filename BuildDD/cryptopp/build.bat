md artifacts
md artifacts\includes
md artifacts\libs

cd cryptopp563                                                    ||  goto :EOF
devenv cryptest.sln /rebuild "Release|Win32" /project "cryptlib"  ||  goto :EOF
copy Win32\output\release\*.lib ..\artifacts\libs                 ||  goto :EOF
copy *.h ..\artifacts\includes                                    ||  goto :EOF

cd ..
