========================================================================
    ACTIVEX 控件 OCX : CCAgentBar 项目概况
========================================================================

ACD客户端程序

/////////////////////////////////////////////////////////////////////////////
MFC工程控件的基本文件:

CCAgentBar.vcproj
    工程文件。

CCAgentBar.h
    程序入口的头文件。

CCAgentBar.cpp
    程序入口的实现文件。

CCAgentBar.rc
    资源文件。
    包含65张图片，其中62张bmp文件，3张ico文件

CCAgentBar.def
    此文件包含有关运行 Microsoft Windows 所需的 ActiveX 控件 DLL 的信息。

CCAgentBar.idl
    接口文件：此文件包含控件类型库的对象描述语言源代码。
    CCAgentBar_i.c和CCAgentBaridl.h是接口文件生成的动态文件。

/////////////////////////////////////////////////////////////////////////////
添加控件的文件:

CCAgentBarCtrl.h
    此文件包含 CCCAgentBarCtrl C++ 类的声明。

CCAgentBarCtrl.cpp
    此文件包含 CCCAgentBarCtrl C++ 类的实现。

CCAgentBarPropPage.h
    此文件包含 CCCAgentBarPropPage C++ 类的声明。

CCAgentBarPropPage.cpp
    此文件包含 CCCAgentBarPropPage C++ 类的实现。

CCCAgentBarCtrl.bmp
    此文件包含一个位图，容器将在
    CCCAgentBarCtrl 控件出现在工具面板上时使用它来表示该控件。此位图
    位于主资源文件 CCAgentBar.rc 中。

/////////////////////////////////////////////////////////////////////////////
其他标准文件:

stdafx.h、stdafx.cpp
    这些文件用于生成名为 CCAgentBar.pch
    的预编译头(PCH)文件以及名为 stdafx.obj 的预编译类型(PCT)文件。

resource.h
    这是标准的头文件，它定义了新的资源 ID。
    Visual C++ 资源编辑器读取和更新此文件。

/////////////////////////////////////////////////////////////////////////////
bgcc:

acd.bidl、acd.h、acd.cpp
    acd接口文件。

acdcallback.bidl、acdcallback.h、acdcallback.cpp
    acd回调接口文件。

acdcommon.bidl、acdcommon.h、acdcommon.cpp
    acd数据定义文件。

/////////////////////////////////////////////////////////////////////////////
json:

json的实现

/////////////////////////////////////////////////////////////////////////////
Common文件:

constder.h
	数据定义文件

locker.h
	同步封装

logger.h、logger.cpp
	日志封装

safequeue.h
	安全队列封装

/////////////////////////////////////////////////////////////////////////////
control:

staticex.h、staticex.cpp
	文本显示框的扩展

buttonxp.h、buttonxp.cpp
	xp风格按钮

buttonicon.h、buttonicon.cpp
	图标按钮

buttonex.h、buttonex.cpp
	按钮的扩展

/////////////////////////////////////////////////////////////////////////////
对话框:

info.h、info.cpp
	信息显示对话框

callout.h、callout.cpp
	呼出提示对话框

ccbar.h、ccbar.cpp
	控件界面对话框

/////////////////////////////////////////////////////////////////////////////
其他注释:

tool.h、tool.cpp
	静态工具类

acdclient.h、acdclient.cpp
	bgcc接口的封装类

有9张bmp图片未使用，分别是“鼠标经过_待机.bmp”、“无效-待机.bmp”、“有效-待机.bmp”、“鼠标经过_后处理.bmp”、“无效-后处理.bmp”、“有效-后处理.bmp”、
“鼠标经过_离席.bmp”、“无效-离席.bmp”、“有效-离席.bmp”

