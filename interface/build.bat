set CMD_VC2003="c:\Program Files\Microsoft Visual Studio .NET 2003\Common7\IDE\Devenv"

rem "build acd..."
cd acd\bidl\
call build.bat %CMD_VC2003%
cd ..
cd ..

rem "build ap..."
cd ap\bidl\
call build.bat %CMD_VC2003%
cd ..
cd ..

rem "build json-cpp..."
cd third\json-cpp
call build.bat %CMD_VC2003%
cd ..
cd ..

rem "build bgcc..."
xcopy ..\..\bgcc\output output\bgcc /E /H /I /R /Y
