#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "Primitive.h"
#include <Windows.h>
#include <string>
#include <iostream>

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    fps_log.resize(100);
    ms_log.resize(100);
}

ModuleEditor::~ModuleEditor()
{}

// Load assets
bool ModuleEditor::Start()
{
    LOG("Loading Intro assets");
    bool ret = true;


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
    ImGui_ImplOpenGL2_Init();

    return ret;
}

// Load assets
bool ModuleEditor::CleanUp()
{
    LOG("Unloading Intro scene");

    return true;
}

void ModuleEditor::capFps()
{
    //Cap Fps-> 60
    float frameDelay = 1000 / App->capFPS;
    Uint32 frameStart = SDL_GetTicks();
    int frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime)
        SDL_Delay(frameDelay - frameTime);
}

// Update: draw background
update_status ModuleEditor::Update(float dt)
{
    Plane p(0, 1, 0, 0);
    p.axis = true;
    p.Render();

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    fps_log[fps_log.size()-1] = App->GetFps();

    for (int i = 0; i < fps_log.size()-1; i++) {
        fps_log[i] = fps_log[i+1];
    }

    ms_log[ms_log.size() - 1] = App->GetMs();

    for (int i = 0; i < ms_log.size()-1; i++) {
        ms_log[i] = ms_log[i + 1];
    }

    //Toolbar
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Configuration", NULL, &show_toolbar);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", NULL, &about_us);
            ImGui::MenuItem("About ImGui", NULL, &show_about_us);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_toolbar)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        //ImGui::Begin("Configuration");                          // Create a window called "Hello, world!" and append into it.

        //ImGui::Text("RealEngine");               // Display some text (you can use a format strings too)
        //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        //ImGui::Checkbox("Another Window", &show_another_window);

        //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        //ImGui::Checkbox("Debug Window", &show_debug_window);
        //if (ImGui::Button("Close Engine"))
        //// Buttons return true when clicked (most widgets return true when edited/activated)
     

        ///*if (ImGui::Checkbox("FullScreen", &fullscreen))
        //    App->window->SetFullscreen(fullscreen);*/

        //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //    counter++;
        //ImGui::SameLine();
        //ImGui::Text("counter = %d", counter);

        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Options");
        if (ImGui::CollapsingHeader("Application"))
        {
            //App name
            std::strcpy(appName,App->window->appName.c_str());
            ImGui::InputText("App name", appName, IM_ARRAYSIZE(appName));
            if (appName != (std::string)appName)
            {
                App->window->appName = appName;
                App->window->SetName();
            }
            //Org title
            std::strcpy(orgName, App->window->orgName.c_str());
            ImGui::InputText("Organitzation Name", orgName, IM_ARRAYSIZE(orgName));
            if (orgName != (std::string)orgName)
            {
                App->window->orgName = orgName;
                App->window->SetName();
            }

            ImGui::SliderInt("Max FPS", &App->capFPS, 1, 60);
            std::string str = std::to_string(App->capFPS);
            ImGui::Text("Fps Limit: ");
            ImGui::SameLine();
            ImGui::Text("%d", App->capFPS);
            
            capFps();
           

            char title[25] = "";

            if (fps_log.size() > 0) {
                
                sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
                ImGui::PlotHistogram("##FRAMERATE", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));

            }

            if (ms_log.size() > 0) {

                sprintf_s(title, 25, "Miliseconds %.1f", ms_log[ms_log.size() - 1]);
                ImGui::PlotHistogram("##MILISECONDS", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
            }
        }

        if (ImGui::CollapsingHeader("Window"))
        {
            //Screen Config
       
            //Brightness
         
            if (ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f)) 
            App->window->SetBrightness(brightness);

            //FullScreen
            if (ImGui::Checkbox("FullScreen", &fullscreen)) {}
            App->window->SetFullScreen(fullscreen);

           



       

        }
    
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

    if (about_us)
    {
        if (ImGui::Begin("About us", &about_us))
        {
            ImGui::TextWrapped("You are using RealEngine, \n The next generation 3D Game Engine \nBy Magdalena Ostrowska and Maria Garrigolas Ledo");
            if (ImGui::Button("Press here to go to our github repository")) {
                App->RequestBrowser("https://github.com/Meeeri08/RealEngine");
            }
            ImGui::TextWrapped("3rd Party Libraries Used:");
            ImGui::Text("SDL2");
            ImGui::Text("OpenGL");
            ImGui::Text("Imgui");
            ImGui::Text("MathGeoLib");
            ImGui::Text("GLEW");

            ImGui::TextWrapped("MIT License:\n");
            ImGui::Text("");
            ImGui::TextWrapped("Copyright (c) 2021 Meeeri08\n");
            ImGui::Text("");

            ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy");
            ImGui::Text("of this softwareand associated documentation files(the \"Software\"), to deal");
            ImGui::Text("in the Software without restriction, including without limitation the rights");
            ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and /or sell");
            ImGui::Text("copies of the Software, and to permit persons to whom the Software is");
            ImGui::Text("furnished to do so, subject to the following conditions :");
            ImGui::Text("");

            ImGui::Text("The above copyright notice and this permission notice shall be included in all");
            ImGui::Text("copies or substantial portions of the Software.");
            ImGui::Text("");

            ImGui::Text("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
            ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
            ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE");
            ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
            ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
            ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE");
            ImGui::Text("SOFTWARE.");
        }
        ImGui::End();
    }

    if (show_about_us)
    {
        ImGui::ShowAboutWindow();
    }


    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    return UPDATE_CONTINUE;
}



