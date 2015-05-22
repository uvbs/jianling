@ECHO OFF
TITLE 项目垃圾清理

ECHO 	项目多余文件清理, 像是 *.dlg *.obj

PAUSE

DEL /f /s /a h *.ncb *.plg *.obj *.pch *.pbi *.pbt *._xe *.ilk *.orig *.idb *.user *.sdf *.suo *.dep *.sdf *.tlog *.vcproj



PAUSE