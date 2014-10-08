
if exist output rd /q /s output
if not exist output mkdir output

set LIBINIT="C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
set CMD_VC2003="C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\IDE\Devenv"

rem "build image plugin "
%CMD_VC2003% "ccl_imgex\ccl_imgex.vcproj" /rebuild Release /project ccl_imgex

rem "build main activex "
%CMD_VC2003% "agentbarsrc\CCAgentBar.vcproj" /rebuild Release /project CCAgentBar

rem "build test project"
%CMD_VC2003% "agentbartest\CCAgentBarTest.vcproj" /rebuild Debug /project CCAgentBarTest
%CMD_VC2003% "agentbartest\CCAgentBarTest.vcproj" /rebuild Release /project CCAgentBarTest

call %LIBINIT%
rem "create cab package"
cabarc.exe -s 6144 n bin\CCAgentBar.cab bin\CCAgentBar.inf bin\CCAgentBar.ocx bin\ccl_imgex.dll
signcode.exe -spc bin\CCAgentBar.spc -v bin\CCAgentBar.pvk bin\CCAgentBar.cab

copy .\bin\CCAgentBar.ocx output\
copy .\bin\ccl_imgex.dll output\
copy .\bin\CCAgentBar.cab output\
copy .\bin\CCAgentBar.pdb output\
copy .\doc\develop_manual.doc output\
