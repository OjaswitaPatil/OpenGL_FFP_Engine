#include "ImGUIHelper.h"
#include "TextRendering.h"

//Global variables for imgui UI controls
static float triangleColor[3] = { 1.0f, 0.0f, 0.0f }; // Default red color
bool show_demo_window = true;
bool show_another_window = false;

void setupImGUIContext()
{
    LOG_DEBUG("*************setupImGUIContext() started ***********");

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    LOG_DEBUG("setupImGUIContext() ->ImGui context created.");

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    LOG_DEBUG("setupImGUIContext() ->ImGuiIO retrieved.");

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
    LOG_INFO("setupImGUIContext() -> Input flags set: Keyboard and Gamepad enabled.");

    ImGui::StyleColorsDark();
    LOG_DEBUG("setupImGUIContext() ->ImGui dark theme applied.");


    if(ImGui_ImplWin32_Init(ghwnd) == false) // hWnd is your window handle from Win32.
    {
        LOG_ERROR("setupImGUIContext() -> Failed to initialize ImGui Win32 backend.");
    }
    else
    {
        LOG_INFO("setupImGUIContext() -> ImGui Win32 backend initialized.");
    }

    //ImGui_ImplOpenGL3_Init("#version 460"); // Or whichever GLSL version you prefer.
    if (ImGui_ImplOpenGL3_Init() == false)
    {
        LOG_ERROR("setupImGUIContext() -> Failed to initialize ImGui OpenGL3 backend.");
    }
    else
    {
        LOG_INFO("setupImGUIContext() -> ImGui OpenGL3 backend initialized.");
    }

    LOG_DEBUG("*************setupImGUIContext() completed ***********");
}

void startImGUIFrame()
{
    //LOG_DEBUG("*************startImGUIFrame() started ***********");
    //Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    //LOG_DEBUG("startImGUIFrame() -> ImGui OpenGL3 new frame started.");

    ImGui_ImplWin32_NewFrame();
    //LOG_DEBUG("startImGUIFrame() -> ImGui Win32 new frame started.");

    ImGui::NewFrame();
    //LOG_DEBUG("startImGUIFrame() -> ImGui core frame initialized.");

    //LOG_INFO("startImGUIFrame() -> ImGui OpenGL3 new frame, Win32 new frame, and core frame started.");

    //LOG_DEBUG("*************startImGUIFrame() completed ***********");
}

void generateUI()
{
    //LOG_DEBUG("*************generateUI() started ***********");

	static float scaleAllOffSet = 0.0f;
    if(ImGui::Begin("Engine's Controls"));
    {
        //LOG_DEBUG("generateUI() -> ImGui UI opened: Engine's Controls");

		if(ImGui::CollapsingHeader("ScreenRotation"))
		{

			ImGui::SliderFloat("SceneRotationX", &(screenRotate.rotate.x),-360.0f, 360.0f);
			ImGui::SliderFloat("SceneRotationY", &(screenRotate.rotate.y),-360.0f, 360.0f);
			ImGui::SliderFloat("SceneRotationZ", &(screenRotate.rotate.z),-360.0f, 360.0f);

			if (ImGui::Button("Reset Scene Rotation"))
			{
				screenRotate.rotate.x = 9.0f;
				screenRotate.rotate.y = 12.0f;
				screenRotate.rotate.z = 0.0f;
                LOG_INFO("generateUI() -> Scene rotation reset to default values.");
			}

		}

        if(ImGui::CollapsingHeader("Add/Delete Shape"))
		{
			if (ImGui::Button("Triangle"))
			{
				createModel(TRIANGLE);
				scaleAllOffSet = 0.0f;
                LOG_INFO("generateUI() -> Triangle model created.");
			}

			ImGui::SameLine();
			if (ImGui::Button("Quad"))
			{
				createModel(RECTANGLE);
				scaleAllOffSet = 0.0f;
                LOG_INFO("generateUI() -> Rectangle model created.");
			}

			ImGui::SameLine();
			if (ImGui::Button("Pyramid"))
			{
				createModel(PYRAMID);
				scaleAllOffSet = 0.0f;
                LOG_INFO("generateUI() -> Pyramid model created.");
			}

			ImGui::SameLine();
			if (ImGui::Button("Cube"))
			{
				createModel(CUBE);
				scaleAllOffSet = 0.0f;
                LOG_INFO("generateUI() -> Cube model created.");
			}

			ImGui::SameLine();
			if (ImGui::Button("TEXT"))
			{
				ImGui::OpenPopup("MyPopup");
                LOG_DEBUG("generateUI() -> TEXT popup opened.");
			}

			if (ImGui::BeginPopup("MyPopup"))
			{
				static char inputText[128] = "";
				ImGui::InputText("Enter Text", inputText, IM_ARRAYSIZE(inputText));

				if (ImGui::Button("OK"))
				{
                    strncpy(textString, inputText, sizeof(textString));
					LOG_INFO("generateUI() -> Text model created with input: %s", textString);
					createModel(TEXT);
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel"))
				{
					ImGui::CloseCurrentPopup();
                    LOG_DEBUG("generateUI() -> Text model creation canceled.");
				}

				ImGui::EndPopup();
			}

			ImGui::NewLine();
			if (ImGui::Button("Delete selected Shape"))
			{
                if (selectedmodel != NULL)
                {
                    LOG_INFO("generateUI() -> Deleting model: modeltype=%d", selectedmodel->model.modeltype);
                    deleteModel(selectedmodel);
                }
                else
                {
                    LOG_WARN("generateUI() -> Attempted to delete model, but none is selected.");
                }
			}
		}

		if(ImGui::CollapsingHeader("Navigation"))
		{
			if (ImGui::Button("Next Shape"))
			{
				if (selectedmodel != NULL && selectedmodel->next != NULL)
				{
					selectedmodel = selectedmodel->next;
                    LOG_INFO("generateUI() -> Navigated to next model: modeltype=%d", selectedmodel->model.modeltype);
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("previous Shape"))
			{
				if (selectedmodel != NULL && selectedmodel->pre != NULL)
				{
					selectedmodel = selectedmodel->pre;
                    LOG_INFO("generateUI() -> Navigated to previous model: modeltype=%d", selectedmodel->model.modeltype);
				}
			}
		}

		if(selectedmodel != NULL) //means linklist has at least one node
		{
			if(ImGui::CollapsingHeader("Transformations"))
			{
				//--- TRANSLATE------
				if (ImGui::TreeNode("Shape's placement"))
				{
					//--- TRANSLATE------
					ImGui::SliderFloat("translateX", &(selectedmodel->model.translate.x), -15.0f, 15.0f);
					ImGui::SliderFloat("translateY", &(selectedmodel->model.translate.y), -15.0f, 15.0f);
					ImGui::SliderFloat("translateZ", &(selectedmodel->model.translate.z), -15.0f, 15.0f);
					ImGui::TreePop();
                    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("generateUI() -> Model translation updated.");
				}

				//--- SCALE------
				if(ImGui::TreeNode("Shape's Scaling"))
				{
					float beforeScaleAllOffSet = scaleAllOffSet;
					float scaleAllOffSetChanged = 0.0f;
					if(ImGui::SliderFloat("ScaleAll%", &scaleAllOffSet, -400.0f, 400.0f))
					{
						scaleAllOffSetChanged = scaleAllOffSet-beforeScaleAllOffSet;
						selectedmodel->model.scale.x += selectedmodel->model.scale.x * (scaleAllOffSetChanged / 100);
						selectedmodel->model.scale.y += selectedmodel->model.scale.y * (scaleAllOffSetChanged / 100);
						selectedmodel->model.scale.z += selectedmodel->model.scale.z * (scaleAllOffSetChanged / 100);
                        LOG_DEBUG("generateUI() -> Model scaled: scaleAll=%.2f", scaleAllOffSetChanged);
					}
					ImGui::SliderFloat("ScaleX", &(selectedmodel->model.scale.x), -1.0f, 5.0f);
					ImGui::SliderFloat("ScaleY", &(selectedmodel->model.scale.y), -1.0f, 5.0f);
					ImGui::SliderFloat("ScaleZ", &(selectedmodel->model.scale.z), -1.0f, 5.0f);
					ImGui::TreePop();
				}

				//--- Rotation------
				if(ImGui::TreeNode("Shape's Rotation"))
				{
					ImGui::SliderFloat("rotationX", &(selectedmodel->model.rotationAngle.x), 0.0f, 360.0f);
					ImGui::SliderFloat("rotationY", &(selectedmodel->model.rotationAngle.y), 0.0f, 360.0f);
					ImGui::SliderFloat("rotationZ", &(selectedmodel->model.rotationAngle.z), 0.0f, 360.0f);
                    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("generateUI() -> Model rotation updated.");
					ImGui::TreePop();
				}

				//--- Color and texture -----
				// if(ImGui::TreeNode("Shape's Color"))
				// {
				// 	ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Individual model vertex Color");
				// 	int numberOfColorVertices = selectedmodel->model.colorsSize / 4.0f;
				// 	for(int i=0, j=0; i<numberOfColorVertices; i++, j+=4)
				// 	{
				// 		char color[] = "color";
				// 		char index[2];
				// 		sprintf(index, "%d", i);
				// 		strcat(color, index);
				// 		ImGui::ColorEdit3(color, (float*)(&selectedmodel->model.colors[j]));
				// 	}
				// 	ImGui::NewLine();

				// 	ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Entire model's Color");
				// 	static GLfloat colorsForAllVertices[] = {1.0f, 1.0f, 1.0f, 1.0f};
				// 	GLfloat beforeChangeColor[] = {colorsForAllVertices[0],colorsForAllVertices[1],colorsForAllVertices[2],colorsForAllVertices[3]};
				// 	ImGui::ColorEdit3("colorAll", (float*)colorsForAllVertices);

				// 	if(colorsForAllVertices[0]!=beforeChangeColor[0] || colorsForAllVertices[1]!=beforeChangeColor[1] || colorsForAllVertices[2]!=beforeChangeColor[2])
				// 	{
				// 		for(int i=0, j=0; i<numberOfColorVertices; i++, j+=4)
				// 		{
				// 			selectedmodel->model.colors[j+0] = colorsForAllVertices[0];
				// 			selectedmodel->model.colors[j+1] = colorsForAllVertices[1];
				// 			selectedmodel->model.colors[j+2] = colorsForAllVertices[2];
				// 			selectedmodel->model.colors[j+3] = colorsForAllVertices[3];
				// 		}
                //         LOG_DEBUG("generateUI() -> Model color changed to RGB(%.2f, %.2f, %.2f)",colorsForAllVertices[0], colorsForAllVertices[1], colorsForAllVertices[2]);
				// 	}
				// 	ImGui::TreePop();
		        // }

				if(ImGui::TreeNode("Shape's Colors and textures"))
				{
					
					//Dropdown Logic
					// const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };
					// static int item_current = 0;
					// ImGui::Combo("combo drowndown", &item_current, items, IM_ARRAYSIZE(items));
					// ImGui::Text("Currently selected: %s", items[item_current]);

					// for(int i = 0; i < selectedmodel->model.numberOfFaces; i++)
					// {
					// 	static int selectedTextureIndex = 0;
					// 	ImGui::Combo("Select Texture", &selectedTextureIndex, allTextureNames_Array, numberOfTextureAvailablesinallTexturesArray);
					// 	ImGui::Text("Currently selected Texture: %s", allTextureNames_Array[selectedTextureIndex]);
					// }


					ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Individual model vertex Color");
					int numberOfColorVertices = selectedmodel->model.colorsSize / 4.0f;
					for(int i=0, j=0; i<numberOfColorVertices; i++, j+=4)
					{
						char color[] = "color";
						char index[2];
						sprintf(index, "%d", i);
						strcat(color, index);
						ImGui::ColorEdit3(color, (float*)(&selectedmodel->model.colors[j]));
					}
					ImGui::NewLine();

					ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Entire model's Color");
					static GLfloat colorsForAllVertices[] = {1.0f, 1.0f, 1.0f, 1.0f};
					GLfloat beforeChangeColor[] = {colorsForAllVertices[0],colorsForAllVertices[1],colorsForAllVertices[2],colorsForAllVertices[3]};
					ImGui::ColorEdit3("colorAll", (float*)colorsForAllVertices);

					if(colorsForAllVertices[0]!=beforeChangeColor[0] || colorsForAllVertices[1]!=beforeChangeColor[1] || colorsForAllVertices[2]!=beforeChangeColor[2])
					{
						for(int i=0, j=0; i<numberOfColorVertices; i++, j+=4)
						{
							selectedmodel->model.colors[j+0] = colorsForAllVertices[0];
							selectedmodel->model.colors[j+1] = colorsForAllVertices[1];
							selectedmodel->model.colors[j+2] = colorsForAllVertices[2];
							selectedmodel->model.colors[j+3] = colorsForAllVertices[3];
						}
                        LOG_DEBUG("generateUI() -> Model color changed to RGB(%.2f, %.2f, %.2f)",colorsForAllVertices[0], colorsForAllVertices[1], colorsForAllVertices[2]);
					}
					ImGui::TreePop();
		        }

				if (ImGui::TreeNode("Blending"))
				{
					static float blendValue = 1.0f;

					ImGui::SliderFloat("blend", &blendValue, 0.0f, 1.0f);

					for (GLint i = 3; i < selectedmodel->model.colorsSize; i += 4)
					{
						selectedmodel->model.colors[i] = blendValue;
					}
                    //LOG_DEBUG("generateUI() -> Blend alpha updated to %.2f", blendValue);
					ImGui::TreePop();
				}
			}
		}
        ImGui::End();
	}

    //Rendering
    ImGui::Render();

    //LOG_DEBUG("*************generateUI() Completed ***********");
}

void renderGeneratedUI()
{
     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void uninitializeImGUI()
{
    LOG_DEBUG("*************uninitializeImGUI() started ***********");
    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    LOG_DEBUG("*************uninitializeImGUI() Completed ***********");
}


