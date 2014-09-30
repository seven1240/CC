if exist output rd /q /s output
if not exist output\log mkdir .\output\log
if not exist output\conf mkdir .\output\conf

"c:/Program Files/Microsoft Visual Studio .NET 2003/Common7/IDE/Devenv" "ApServer.vcproj" /rebuild Release /project ApServer
"c:/Program Files/Microsoft Visual Studio .NET 2003/Common7/IDE/Devenv" "ApServer.vcproj" /rebuild Debug /project ApServer

copy .\Release\ApServer.exe output\
copy .\conf output\conf
