
if exist output rd /q /s output
if not exist output mkdir output
set CMD_VC2003="c:/Program Files/Microsoft Visual Studio .NET 2003/Common7/IDE/Devenv"

chmod +x bin/*.exe

rem "build image plugin "
%CMD_VC2003% "ccl_imgex\ccl_imgex.vcproj" /clean Release /project ccl_imgex

rem "build main activex "
%CMD_VC2003% "agentbarsrc\CCAgentBar.vcproj" /clean Release /project CCAgentBar
%CMD_VC2003% "agentbarsrc\CCAgentBar.vcproj" /clean Debug /project CCAgentBar

rem "build test project"
%CMD_VC2003% "agentbartest\CCAgentBarTest.vcproj" /clean Debug /project CCAgentBarTest
%CMD_VC2003% "agentbartest\CCAgentBarTest.vcproj" /clean Release /project CCAgentBarTest
