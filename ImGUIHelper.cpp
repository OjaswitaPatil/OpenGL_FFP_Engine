#include "ImGUIHelper.h"

//Global variables for imgui UI controls
static float triangleColor[3] = { 1.0f, 0.0f, 0.0f }; // Default red color
bool show_demo_window = true;
bool show_another_window = false;

void setupImGUIContext()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(ghwnd);  // hWnd is your window handle from Win32.
    //ImGui_ImplOpenGL3_Init("#version 460"); // Or whichever GLSL version you prefer.
    ImGui_ImplOpenGL3_Init();
}

void startImGUIFrame()
{
    //Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void generateUI()
{
    static float scaleAllOffSet = 0.0f;
	{
		ImGui::Begin("Engine's Controls");

		ImGui::Separator();

		ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Add/Delete Shape");
		if (ImGui::Button("Triangle"))  
		{                        
			createModel(TRIANGLE);
			scaleAllOffSet = 0.0f;
		}
		ImGui::SameLine();
		if (ImGui::Button("Quad")) 
		{                   
			createModel(RECTANGLE);
			scaleAllOffSet = 0.0f;
		}
		ImGui::SameLine();
		if (ImGui::Button("Text")) 
		{                   
			createModel(TEXT);
			scaleAllOffSet = 0.0f;
		}
	
		ImGui::NewLine();
		if (ImGui::Button("Delete selected Shape"))  
		{    
            if (selectedmodel != NULL)
            {
               deleteModel(selectedmodel);
            }
		}

		ImGui::NewLine();
		ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Navigation");
		if (ImGui::Button("Next Shape"))  
		{
            if (selectedmodel != NULL && selectedmodel->next != NULL)
            {
                selectedmodel = selectedmodel->next;
            }
		}
		ImGui::SameLine();
		if (ImGui::Button("previous Shape"))  
		{    
            if (selectedmodel != NULL && selectedmodel->pre != NULL)
            {
                selectedmodel = selectedmodel->pre;
            }
		}

		
		if(selectedmodel != NULL) //means linklist has at least one node
		{	
			//--- TRANSLATE------
			ImGui::NewLine();
			ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Shape's placement");
			ImGui::SliderFloat("translateX", &(selectedmodel->model.translate.x), -15.0f, 15.0f);
			ImGui::SliderFloat("translateY", &(selectedmodel->model.translate.y), -15.0f, 15.0f);
			ImGui::SliderFloat("translateZ", &(selectedmodel->model.translate.z), -15.0f, 15.0f);

			//--- SCALE------
			ImGui::NewLine();
			ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "model's Scaling");
			
			float beforeScaleAllOffSet = scaleAllOffSet;
			float scaleAllOffSetChanged = 0.0f;
			if(ImGui::SliderFloat("ScaleAll%", &scaleAllOffSet, -400.0f, 400.0f))
			{
				scaleAllOffSetChanged = scaleAllOffSet-beforeScaleAllOffSet;
				selectedmodel->model.scale.x += selectedmodel->model.scale.x * (scaleAllOffSetChanged / 100);
				selectedmodel->model.scale.y += selectedmodel->model.scale.y * (scaleAllOffSetChanged / 100);
				selectedmodel->model.scale.z += selectedmodel->model.scale.z * (scaleAllOffSetChanged / 100);
			}
     		ImGui::SliderFloat("ScaleX", &(selectedmodel->model.scale.x), -1.0f, 5.0f);
			ImGui::SliderFloat("ScaleY", &(selectedmodel->model.scale.y), -1.0f, 5.0f);
			ImGui::SliderFloat("ScaleZ", &(selectedmodel->model.scale.z), -1.0f, 5.0f);

			//--- Rotation------
			ImGui::NewLine();
			ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "model's Rotation");
			ImGui::SliderFloat("rotationX", &(selectedmodel->model.rotationAngle.x), 0.0f, 360.0f);
			ImGui::SliderFloat("rotationY", &(selectedmodel->model.rotationAngle.y), 0.0f, 360.0f);
			ImGui::SliderFloat("rotationZ", &(selectedmodel->model.rotationAngle.z), 0.0f, 360.0f);

			//--- COlor -----
			ImGui::NewLine();
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
			}
		}


		ImGui::End();
	}
	//--------------------------------------------------------

    //Rendering
    ImGui::Render();
}

void renderGeneratedUI()
{
     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void uninitializeImGUI()
{
    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}


