@REM ::clean
@REM cls
@REM del *.obj
@REM del "imgui\\*.obj"
@REM del *.exe
@REM del *.res

@REM ::compililation: to create obj files
@REM cl.exe /c /EHsc EngineMain.cpp Models.cpp linkedList.cpp imGUIHelper.cpp

@REM cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui.cpp" /Fo"imgui\\imgui.obj"
@REM cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_demo.cpp" /Fo"imgui\\imgui_demo.obj"
@REM cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_draw.cpp" /Fo"imgui\\imgui_draw.obj"
@REM cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_widgets.cpp" /Fo"imgui\\imgui_widgets.obj"
@REM cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_tables.cpp" /Fo"imgui\\imgui_tables.obj"
@REM cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_impl_win32.cpp" /Fo"imgui\\imgui_impl_win32.obj"
@REM cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_impl_opengl3.cpp" /Fo"imgui\\imgui_impl_opengl3.obj"

@REM ::compiling resource file
@REM rc.exe EngineMain.rc    

@REM ::Linking: To create exe file
@REM ::link.exe EngineMain.obj Models.obj linkedList.obj EngineMain.res User32.lib GDI32.LIB /SUBSYSTEM:WINDOWS
@REM link.exe "EngineMain.obj" "Models.obj" "linkedList.obj" "imGUIHelper.obj" "imgui\\imgui.obj" "imgui\\imgui_demo.obj" "imgui\\imgui_draw.obj" "imgui\\imgui_widgets.obj" "imgui\\imgui_tables.obj" "imgui\\imgui_impl_win32.obj" "imgui\\imgui_impl_opengl3.obj" EngineMain.res User32.lib GDI32.lib /LIBPATH:"C:\\glew-2.1.0\\lib\\Release\\x64" /SUBSYSTEM:WINDOWS

@echo off
cls

REM ====================
REM CLEANUP SECTION
REM ====================

echo ====================================================================================================
echo Deleting .obj files...
del /s /q *.obj

echo Deleting .exe files...
del /s /q *.exe
echo.
echo Clean-up complete!
echo ====================================================================================================
echo.
pause

REM ====================
REM COMPILATION SECTION
REM ====================
echo ====================================================================================================
echo Starting compilation...

cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" EngineMain.cpp Models.cpp linkedList.cpp imGUIHelper.cpp TextRendering.cpp
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui.cpp" /Fo"imgui\\imgui.obj"
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_demo.cpp" /Fo"imgui\\imgui_demo.obj"
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_draw.cpp" /Fo"imgui\\imgui_draw.obj"
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_widgets.cpp" /Fo"imgui\\imgui_widgets.obj"
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_tables.cpp" /Fo"imgui\\imgui_tables.obj"
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_impl_win32.cpp" /Fo"imgui\\imgui_impl_win32.obj"
cl.exe /c /EHsc /I "C:\\glew-2.1.0\\include" "imgui\\imgui_impl_opengl3.cpp" /Fo"imgui\\imgui_impl_opengl3.obj"

echo.
echo Compilation complete!
echo ====================================================================================================
echo.
pause

REM ====================
REM LINKING SECTION
REM ====================

echo ====================================================================================================
echo Starting linking...

rc.exe EngineMain.rc  

link.exe "EngineMain.obj" "Models.obj" "TextRendering.obj" "linkedList.obj" "imGUIHelper.obj" "imgui\\imgui.obj" "imgui\\imgui_demo.obj" "imgui\\imgui_draw.obj" "imgui\\imgui_widgets.obj" "imgui\\imgui_tables.obj" "imgui\\imgui_impl_win32.obj" "imgui\\imgui_impl_opengl3.obj" EngineMain.res User32.lib GDI32.lib /LIBPATH:"C:\\glew-2.1.0\\lib\\Release\\x64" /SUBSYSTEM:WINDOWS

echo.
echo Linking complete!
echo.
echo ====================================================================================================
pause

REM ====================
REM RUN SECTION
REM ====================
echo ====================================================================================================
echo Running Application...
EngineMain.exe
echo.
echo Application Closed/Terminated...
echo ====================================================================================================