setlocal
rem Setting up the build
rem MUST DO THIS IN THE DIRECTORY


pushd C:\DD\pr\base

	

	pushd C:\DD\pr\base\Source\Views
	call maked -a prddfun
	
	
	XCOPY  C:\DD\pr\base\UP32\RUNTIME\UPDDFUN.* "C:\Program Files (x86)\Sage\Sage 300 ERP\UP72A" /s /y
	XCOPY  C:\DD\pr\base\UP32\RUNTIME\ROTO.DAT "C:\Program Files (x86)\Sage\Sage 300 ERP\UP72A" /s /y
	
	cd C:\GitHub\CrackingCodingInterview\BuildDD\
	echo "Finished!"

