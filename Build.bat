::clean
cls
del *.obj
del *.exe
del *.res

::compililation: to create obj files
cl.exe /c /EHsc EngineMain.c Models.c

::compiling resource file
rc.exe EngineMain.rc    

::Linking: To create exe file
link.exe EngineMain.obj Models.obj EngineMain.res User32.lib GDI32.LIB /SUBSYSTEM:WINDOWS



