rem Setting up the build

CALL C:\DD\pr\base\setproj UP
CALL C:\DD\pr\base\SETUP32 UP
CALL C:\DD\pr\base\cryptopp-lib-build-fetch set-jenkins-job
CALL C:\DD\pr\base\cryptopp-lib-fetch jenkins-job
CALL start notepad++ C:\DD\pr\base\Source\Views\error

