#ifndef IMGUIHELPER_H
#define IMGUIHELPER_H

#include "globalHeaders.h"
#include "linkedList.h"

//imgui related headers
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"

//Global variables for imgui UI controls
extern float triangleColor[3]; // Default red color
extern bool show_demo_window;
extern bool show_another_window;

void setupImGUIContext();
void startImGUIFrame();
void generateUI();
void renderGeneratedUI();
void uninitializeImGUI();

#endif

