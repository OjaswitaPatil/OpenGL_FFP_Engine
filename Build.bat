::clean
cls
del *.obj
del "imgui\\*.obj"
del *.exe
del *.res

::compililation: to create obj files
cl.exe /c /EHsc EngineMain.cpp Models.cpp linkedList.cpp imGUIHelper.cpp

cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui.cpp" /Fo"imgui\\imgui.obj"
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_demo.cpp" /Fo"imgui\\imgui_demo.obj"
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_draw.cpp" /Fo"imgui\\imgui_draw.obj"
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_widgets.cpp" /Fo"imgui\\imgui_widgets.obj"
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_tables.cpp" /Fo"imgui\\imgui_tables.obj"
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_impl_win32.cpp" /Fo"imgui\\imgui_impl_win32.obj"
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_impl_opengl3.cpp" /Fo"imgui\\imgui_impl_opengl3.obj"

::compiling resource file
rc.exe EngineMain.rc    

::Linking: To create exe file
::link.exe EngineMain.obj Models.obj linkedList.obj EngineMain.res User32.lib GDI32.LIB /SUBSYSTEM:WINDOWS
link.exe "EngineMain.obj" "Models.obj" "linkedList.obj" "imGUIHelper.obj" "imgui\\imgui.obj" "imgui\\imgui_demo.obj" "imgui\\imgui_draw.obj" "imgui\\imgui_widgets.obj" "imgui\\imgui_tables.obj" "imgui\\imgui_impl_win32.obj" "imgui\\imgui_impl_opengl3.obj" EngineMain.res User32.lib GDI32.lib /LIBPATH:"C:\\glew-2.1.0\\lib\\Release\\x64" /SUBSYSTEM:WINDOWS



