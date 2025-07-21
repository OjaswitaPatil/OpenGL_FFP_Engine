#include "ImGUIHelper.h"
#include "TextRendering.h"
#include "SaveAndLoadModels.h"

//Global variables for imgui UI controls
// static float triangleColor[3] = { 1.0f, 0.0f, 0.0f }; // Default red color
// bool show_demo_window = true;
// bool show_another_window = false;

int *selectedTextureIndex = NULL;
bool *isTextureEnabled = NULL;

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

		ImGui::Text("Number of active LL nodes: %d", NumOfActiveLLNodesInMemory);


		if (ImGui::Button("Exit"))
			{
				gbEscapeKeyIsPress = TRUE;
                LOG_INFO("generateUI() -> Exit button triggered.");
			}

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
				createModel(masterLinkedList, TRIANGLE, NULL);
				scaleAllOffSet = 0.0f;
                LOG_INFO("generateUI() -> Triangle model created.");
			}

			ImGui::SameLine();
			if (ImGui::Button("Quad"))
			{
				createModel(masterLinkedList, RECTANGLE, NULL);
				scaleAllOffSet = 0.0f;
                LOG_INFO("generateUI() -> Rectangle model created.");
			}

			ImGui::SameLine();
			if (ImGui::Button("Pyramid"))
			{
				createModel(masterLinkedList, PYRAMID, NULL);
				scaleAllOffSet = 0.0f;
                LOG_INFO("generateUI() -> Pyramid model created.");
			}

			ImGui::SameLine();
			if (ImGui::Button("Cube"))
			{
				createModel(masterLinkedList, CUBE, NULL);
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
					createModel(masterLinkedList, TEXT, NULL);
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

			if (ImGui::Button("CYLINDER"))
			{
				createModel(masterLinkedList, CYLINDER, NULL);
				scaleAllOffSet = 0.0f;
                LOG_DEBUG("generateUI() -> CYALINDER model created.");
			}

			ImGui::SameLine();
			if (ImGui::Button("SPHERE"))
			{
				createModel(masterLinkedList, SPHERE, NULL);
				scaleAllOffSet = 0.0f;
                LOG_DEBUG("generateUI() -> Sphere model created.");
			}

			ImGui::SameLine();
			if (ImGui::Button("DISK"))
			{
				createModel(masterLinkedList, DISK, NULL);
				scaleAllOffSet = 0.0f;
                LOG_DEBUG("generateUI() -> disk model created.");
			}

			if (ImGui::Button("ReadyModel"))
			{
				LOG_DEBUG("generateUI() -> ReadyModel model creation started.");
				createModel(masterLinkedList, READYMODEL, "testreadymodel.csv");
				scaleAllOffSet = 0.0f;
                LOG_DEBUG("generateUI() -> ReadyModel model created successfully.");
			}


			ImGui::NewLine();
			if (ImGui::Button("Delete selected Shape"))
			{
                if (selectedmodel != NULL)
                {
                    LOG_INFO("generateUI() -> Deleting model: modeltype=%d", selectedmodel->model.modeltype);
                    deleteModel(masterLinkedList, selectedmodel);
                }
                else
                {
                    LOG_WARN("generateUI() -> Attempted to delete model, but none is selected.");
                }
			}

			//save model
			ImGui::NewLine();
			if (ImGui::Button("SaveModel"))
			{
				ImGui::OpenPopup("SaveModelPopUp");
                LOG_DEBUG("generateUI() -> SaveModelPopUp popup opened.");
			}

			if (ImGui::BeginPopup("SaveModelPopUp"))
			{
				static char inputText[128] = "";
				ImGui::InputText(".csv", inputText, IM_ARRAYSIZE(inputText));

				if (ImGui::Button("OK"))
				{
					char *saveModelFileName = (char*)malloc((strlen("resources/CsvModels/") + IM_ARRAYSIZE(inputText) + strlen(".csv")) * sizeof(char));
					strcpy(saveModelFileName,"resources/CsvModels/");
					strcat(saveModelFileName, inputText);
					strcat(saveModelFileName, ".csv");
					
					if(saveModel(masterLinkedList, saveModelFileName) == TRUE)
					{
						LOG_INFO("generateUI() -> model saved with file name: %s", saveModelFileName);
					}
					else
					{
						ImGui::Text("Model save with file: %s.csv failed", saveModelFileName);
						LOG_INFO("generateUI() -> model saving with file name failed: %s", saveModelFileName);
					}
					if(saveModelFileName)
					{
						free(saveModelFileName);
						saveModelFileName = NULL;
					}
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel"))
				{
					ImGui::CloseCurrentPopup();
                    LOG_DEBUG("generateUI() ->  model saving canceled.");
				}

				ImGui::EndPopup();
			}

			//load model
			if (ImGui::Button("LoadModel"))
			{
				ImGui::OpenPopup("LoadModelPopUp");
                LOG_DEBUG("generateUI() -> LoadModelPopUp popup opened.");
			}
			if (ImGui::BeginPopup("LoadModelPopUp"))
			{
				static char inputText[128] = "";
				ImGui::InputText(".csv", inputText, IM_ARRAYSIZE(inputText));

				if (ImGui::Button("OK"))
				{
					char *loadModelFileName = (char*)malloc((strlen("resources/CsvModels/") + IM_ARRAYSIZE(inputText) + strlen(".csv")) * sizeof(char));
					strcpy(loadModelFileName,"resources/CsvModels/");
					strcat(loadModelFileName, inputText);
					strcat(loadModelFileName, ".csv");
					
					if(loadCSVModel(masterLinkedList, loadModelFileName) == TRUE)
					{
						LOG_INFO("generateUI() -> model loaded with file name: %s", loadModelFileName);
					}
					else
					{
						LOG_INFO("generateUI() -> model loading with file name failed: %s", loadModelFileName);
					}
					if(loadModelFileName)
					{
						free(loadModelFileName);
						loadModelFileName = NULL;
					}
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel"))
				{
					ImGui::CloseCurrentPopup();
                    LOG_DEBUG("generateUI() ->  model loading canceled.");
				}

				ImGui::EndPopup();
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
				if(ImGui::TreeNode("Shape's Colors and textures"))
				{
                    //initialzed needed array for fuirst time when program starts
                    if(selectedTextureIndex == NULL || isTextureEnabled == NULL)
                    {
                        isTextureEnabled = (bool*)malloc(sizeof(bool) * MAX_NUMBER_OF_LOADED_TEXTURES);

                        selectedTextureIndex = (int*)malloc(sizeof(int) * MAX_NUMBER_OF_LOADED_TEXTURES);
                    }
					if(selectedTextureIndex == NULL || isTextureEnabled == NULL)
					{
						LOG_ERROR("generateUI() -> Memory allocation failed for isTextureEnabled or selectedTextureIndex.");
						return;
					}
					else
					{
						LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("generateUI() -> Memory allocation is available for isTextureEnabled or selectedTextureIndex.");
					}

					for(int i = 0; i < selectedmodel->model.numberOfFaces; i++)
					{
                        // Initialize texture enabled state based on existing textureVariables values of selectedModel
                        if(selectedmodel->model.textureVariables[i] && selectedmodel->model.textureVariables[i] > 0)
                        {
                            isTextureEnabled[i] = true;

                            //search already applied texture index in Global names texture array and set selectedTextureIndex[i] to that index
                            selectedTextureIndex[i] = 0;//initialize to first texture index
                            for(int j = 0; j < numberOfTextureAvailablesinallTexturesArray; j++)
                            {
                                if(allLoadedTextureIdentifiers_Array[j] == selectedmodel->model.textureVariables[i])
                                {
                                    selectedTextureIndex[i] = j; // Find the index of the currently selected texture
                                    break;
                                }
                            }

                        }
                        else
                        {
                            isTextureEnabled[i] = false;
                            selectedTextureIndex[i] = 0;//initialize to first texture index
                        }

                        //texture checkbox
                        char TextureEnableForFace[64];
                        sprintf(TextureEnableForFace, "EnableTexture%d", i+1); // Format label per Face
                        ImGui::Text("Face: %d", i+1); // Format label per Face
                        ImGui::Checkbox(TextureEnableForFace, &isTextureEnabled[i]);

                        //if texture checkbox is enabled then show texture selection combo box and apply selected texture in per model textureVariables array
                        if(isTextureEnabled[i] == true)
                        {
                            char TextureForFace[64];
                            sprintf(TextureForFace, "Texture%d", i+1); // Format label per Face
                            ImGui::Combo(TextureForFace, &selectedTextureIndex[i], allTextureNames_Array, numberOfTextureAvailablesinallTexturesArray);
                            ImGui::Text("Currently selected Texture: %s", allTextureNames_Array[selectedTextureIndex[i]]);

                            selectedmodel->model.textureVariables[i] = allLoadedTextureIdentifiers_Array[selectedTextureIndex[i]];//added texture id from global texture array to per model textureVariables array
                        }
                        //Do not show combobox as texture checkbox is unchecked. In this case color UI per face should be shown
                        else
                        {
                            if(selectedmodel->model.textureVariables[i])
                                selectedmodel->model.textureVariables[i]= 0;//apply 0 on disabling texture checkbox

                            //per face color logic
                            ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Per face vertex Color");
                            for(int j=0, k=i*selectedmodel->model.numberOfVerticesPerFace*4; j<selectedmodel->model.numberOfVerticesPerFace; j++, k+=4)
                            {
                                char faceColor[] = "Face";
                                char index[3];//2 digit index support(max number of vertex per face 999 and max faces 999)
                                sprintf(index, "%d", i+1);
                                strcat(faceColor, index);
                                char color[] = "-Color";
                                sprintf(index, "%d", j+1);
                                strcat(color, index);
                                strcat(faceColor, color);


                                ImGui::ColorEdit3(faceColor, (float*)(&selectedmodel->model.colors[k]));
                            }


                        }
					}

                    ImGui::NewLine();

                    // changing entire model color at once
					int numberOfColorVertices = selectedmodel->model.colorsSize / 4.0f;

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

				//custom attributes
				if(selectedmodel->model.customModelAttributes != NULL)
				{
					if(ImGui::TreeNode("Shape's Custom attributes"))
					{
						static bool enableWireframe = false;
						ImGui::Checkbox("Enable Wireframe", &enableWireframe);
						if(enableWireframe == true)
							selectedmodel->model.customModelAttributes[0]= 0.0f;
						else
							selectedmodel->model.customModelAttributes[0]= 1.0f;

						//SPHERE
						if(selectedmodel->model.modeltype == SPHERE)
						{
							ImGui::SliderFloat("Slices", &(selectedmodel->model.customModelAttributes[1]), 1.0f, 60.0f);
							ImGui::SliderFloat("Stacks", &(selectedmodel->model.customModelAttributes[2]), 1.0f, 60.0f);
						}
						//CYLINDER
						if(selectedmodel->model.modeltype == CYLINDER)
						{
							ImGui::SliderFloat("1st opening radius", &(selectedmodel->model.customModelAttributes[1]), 0.0f, 10.0f);
							ImGui::SliderFloat("2nd opening radius", &(selectedmodel->model.customModelAttributes[2]), 0.0f, 10.0f);
							ImGui::SliderFloat("Length", &(selectedmodel->model.customModelAttributes[3]), 0.0f, 20.0f);
							ImGui::SliderFloat("Slices", &(selectedmodel->model.customModelAttributes[4]), 1.0f, 60.0f);
							ImGui::SliderFloat("Stacks", &(selectedmodel->model.customModelAttributes[5]), 1.0f, 60.0f);
						}
						//DISK
						if(selectedmodel->model.modeltype == DISK)
						{
							ImGui::SliderFloat("Inner radius", &(selectedmodel->model.customModelAttributes[1]), 0.0f, 10.0f);
							ImGui::SliderFloat("Outer radius", &(selectedmodel->model.customModelAttributes[2]), 0.0f, 10.0f);
							ImGui::SliderFloat("Slices", &(selectedmodel->model.customModelAttributes[3]), 1.0f, 60.0f);
							ImGui::SliderFloat("Stacks", &(selectedmodel->model.customModelAttributes[4]), 1.0f, 60.0f);
						}
						ImGui::Text("currently selected shape= %d", selectedmodel->model.modeltype);
						ImGui::TreePop();
					}
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

    //free up allocated memory
    free(selectedTextureIndex);
    selectedTextureIndex = NULL;
    free(isTextureEnabled);
    isTextureEnabled = NULL;

    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    LOG_DEBUG("*************uninitializeImGUI() Completed ***********");
}


