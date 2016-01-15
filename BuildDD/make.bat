setlocal
rem Setting up the build
rem MUST DO THIS IN THE DIRECTORY


pushd C:\DD\pr\base

	 CALL setproj UP
	 CALL SETUP32 UP

	pushd C:\DD\pr\base\Source\Views
	call make -a prddfun
	start notepad++ error
	
	XCOPY  C:\DD\pr\base\UP32\RUNTIME\UPDDFUN.* "C:\Program Files (x86)\Sage\Sage 300 ERP\UP72A" /s /y
	XCOPY  C:\DD\pr\base\UP32\RUNTIME\ROTO.DAT "C:\Program Files (x86)\Sage\Sage 300 ERP\UP72A" /s /y
	
	cd C:\GitHub\CrackingCodingInterview\BuildDD\
	echo "Finished!"

