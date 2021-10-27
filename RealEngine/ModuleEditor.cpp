#include "glew/include/glew.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "Primitive.h"
#include "InspectorWindow.h"
#include "HierarchyWindow.h"
#include "VidMemViaDDraw.h"

#include <Windows.h>
#include <string>
#include <iostream>


ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    fps_log.resize(100);
    ms_log.resize(100);

    inspectorWindow = new InspectorWindow();
    hierarchyWindow = new HierarchyWindow();
}

ModuleEditor::~ModuleEditor()
{}

// Load assets
bool ModuleEditor::Start()
{
    LOG("Loading Intro assets");
    App->console->AddLog("Loading Intro assets");
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
    App->console->AddLog("Unloading Intro scene");

    return true;
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
            ImGui::MenuItem("Console", NULL, &show_console);
            ImGui::MenuItem("Inspector", NULL, &show_inspector);
            ImGui::MenuItem("Hierarchy", NULL, &show_hierarchy);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", NULL, &about_us);
            ImGui::MenuItem("About ImGui", NULL, &show_about_us);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Assets"))
        {
            if (ImGui::MenuItem(""))
            {
                
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Exit"))
        {
            if (ImGui::MenuItem("Close App"))
            {
                exit(0);
            }
            ImGui::EndMenu();
        }
       

        ImGui::EndMainMenuBar();
    }
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_toolbar)
        ImGui::ShowDemoWindow(&show_demo_window);
    if(show_console)
        App->console->DrawConsole("Console", &show_console);
    if (show_inspector)
        inspectorWindow->Draw();
    if (show_hierarchy)
        hierarchyWindow->Draw();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        ImGui::Begin("Configuration");
            ImGui::Text("Options");
            if (ImGui::CollapsingHeader("Application"))
            {
                //App name
                std::strcpy(appName, App->window->appName.c_str());
                ImGui::InputText("App name", appName, IM_ARRAYSIZE(appName));
                if (appName != (std::string)appName)
                {
                    App->window->appName = appName;
                    App->window->SetName();
                }
                //Org title
                std::strcpy(orgName, App->window->orgName.c_str());
                ImGui::InputText("Organitzation", orgName, IM_ARRAYSIZE(orgName));
                if (orgName != (std::string)orgName)
                {
                    App->window->orgName = orgName;
                    App->window->SetName();
                }

                //Fps cap
                ImGui::SliderInt("Max FPS", &App->capFPS, 1, 60);
                std::string str = std::to_string(App->capFPS);
                ImGui::Text("Limit Framerate:");
                ImGui::SameLine();
                ImGui::Text("%d", App->capFPS);

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
                ////Screen Config
                ////Active
                ////TODO
                //if (ImGui::Checkbox("Active", &App->window->active)) {}

                //ImGui::Text("Icon: *default!*");
                //Brightness
                if (ImGui::SliderFloat("Brightness", &App->window->brightness, 0.0f, 1.0f))
                    App->window->SetBrightness(App->window->brightness);

                //Width and Height

                if (!App->window->fullscreen && !App->window->fullscreenDesktop)
                {
                    if (ImGui::SliderInt("Width", &App->window->width, 480, 2000))
                        App->window->SetSize(App->window->width, App->window->height);

                    if (ImGui::SliderInt("Height", &App->window->height, 480, 2048))
                        App->window->SetSize(App->window->width, App->window->height);
                }

                //Refresh Rate
                ImGui::Text("Refresh Rate %i", (int)ImGui::GetIO().Framerate);

                ImGui::Separator();

                //FullScreen
                if (!App->window->fullscreenDesktop)
                {
                    if (ImGui::Checkbox("FullScreen", &App->window->fullscreen)) 
                    {
                        App->window->SetFullScreen(App->window->fullscreen);
                    }
                    ImGui::SameLine();
                }
              
                //TODO
                //Resizable
             
                ImGui::Checkbox("Resizable", &App->window->resizable); 
                {
                    App->window->SetResizable(App->window->resizable);
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip("Restart to apply");
                }
        
                //Borderless

                if (ImGui::Checkbox("Borderless", &App->window->borderless))
                {
                    App->window->SetBorder(!App->window->borderless);
                }

                //TODO
                //Full Desktop
          
                if ( !App->window->fullscreen )
                {
                    ImGui::SameLine();
                    if (ImGui::Checkbox("Full Desktop", &App->window->fullscreenDesktop))
                    {
                        App->window->SetFullscreenDesktop(App->window->fullscreenDesktop);
                        SDL_GetWindowSize(App->window->window, &App->window->width, &App->window->height);
                    }
                }
              
                ImGui::Separator();
            }
   


            if (ImGui::CollapsingHeader("Renderer"))
            {

                ImGui::Checkbox("VSync", &App->renderer3D->vsync);
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("Restart to apply");

            }
            if (ImGui::CollapsingHeader("Input"))
            {
                ImVec4 values_color(1.0f, 1.0f, 0.0f, 1.0f);

                ImGuiIO& io = ImGui::GetIO();

                    //Mouse Pos
                if (ImGui::IsMousePosValid())
                    ImGui::Text("Mouse pos:"); 
                    ImGui::SameLine();
                    ImGui::TextColored(values_color, "% g, % g", io.MousePos.x, io.MousePos.y);
            
                    ImGui::Text("Mouse down:");     for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseDown(i)) { ImGui::SameLine(); ImGui::TextColored(values_color,"b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
                   
                    //Mouse Motion
                    ImGui::Text("Mouse Motion: "); ImGui::SameLine();
                    ImGui::TextColored(values_color, "%i, %i", App->input->GetMouseXMotion(), App->input->GetMouseYMotion());

                    //Mouse Clicked
                    ImGui::Text("Mouse clicked:");  for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseClicked(i)) { ImGui::SameLine(); ImGui::TextColored(values_color, "b%d", i); }

                    //Mouse Released
                    ImGui::Text("Mouse released:"); for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseReleased(i)) { ImGui::SameLine(); ImGui::TextColored(values_color, "b%d", i); }
          
  
                    //Mouse Wheel
                    ImGui::Text("Mouse Wheel: "); ImGui::SameLine();
                    ImGui::TextColored(values_color, "%i", App->input->GetMouseZ());
                    ImGui::Separator();

            }
            if (ImGui::CollapsingHeader("Audio"))
            {

            }
            if (ImGui::CollapsingHeader("Camera"))
            {

            }
            if (ImGui::CollapsingHeader("Hardware"))
            {
                ImVec4 values_color(1.0f, 1.0f, 0.0f, 1.0f);
                //SDL Version
                SDL_version version;
                SDL_GetVersion(&version);
                ImGui::Text("SDL Version:");
                ImGui::SameLine();
                ImGui::TextColored(values_color, "%d.%d.%d", version.major, version.minor, version.patch);

  
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                //Hardware
                static HardwareSpecs specs = App->GetHardware();

                //CPU
                ImGui::Text("CPUs:");
                ImGui::SameLine();
                ImGui::TextColored(values_color, "%d (Cache: %dkb)", specs.cpuCount, specs.cpuCache);

                //RAM
                ImGui::Text("System RAM:");
                ImGui::SameLine();
                ImGui::TextColored(values_color, "%.1f Gb", specs.ram);

                //CAPS
                ImGui::Text("Caps:");
                ImGui::SameLine();
                ImGui::TextColored(values_color, "%s", specs.caps.c_str());

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                //GPU
                ImGui::Text("GPU:");
                ImGui::SameLine();
                ImGui::TextColored(values_color, "%s", specs.gpu);

                ImGui::Text("Brand:");
                ImGui::SameLine();
                ImGui::TextColored(values_color, "%s", specs.gpuBrand);

                //VRAM

           ImGui::Text("VRAM Budget:");
                ImGui::SameLine();
                ImGui::TextColored(values_color, "%.1f Mb", vramBudget());

                ImGui::Text("VRAM Usage:");
                ImGui::SameLine();
                ImGui::TextColored(values_color, "%.1f Mb", vramBudget() - vramAvailable());

                ImGui::Text("VRAM Available:");
                ImGui::SameLine();
                ImGui::TextColored(values_color, "%.1f Mb", vramAvailable());

                ImGui::Text("VRAM Reserved:");
                ImGui::SameLine();
                ImGui::TextColored(values_color, "%.1f Mb", vramReserved ());

        

            }

            if (ImGui::CollapsingHeader("OpenGL"))

                //TODO: ADD 2 MORE GL_
            {
                
                if (ImGui::Checkbox("Depth Test", &App->renderer3D->depth_test))
                {
                    if (App->renderer3D->depth_test) glEnable(GL_DEPTH_TEST);
                    else glDisable(GL_DEPTH_TEST);
                }

                ImGui::SameLine();
                if (ImGui::Checkbox("Cull Face", &App->renderer3D->cull_face))
                {
                    if (App->renderer3D->cull_face) glEnable(GL_CULL_FACE);
                    else glDisable(GL_CULL_FACE);
                }

                if (ImGui::Checkbox("Texture 2D", &App->renderer3D->texture_2D))
                {
                    if (App->renderer3D->texture_2D) glEnable(GL_TEXTURE_2D);
                    else glDisable(GL_TEXTURE_2D);
                }

                ImGui::SameLine();
                if (ImGui::Checkbox("Lighting", &App->renderer3D->lighting))
                {
                    if (App->renderer3D->lighting) glEnable(GL_LIGHTING);
                    else glDisable(GL_LIGHTING);
                }


                if (ImGui::Checkbox("Color Material", &App->renderer3D->color_material))
                {
                    if (App->renderer3D->color_material) glEnable(GL_COLOR_MATERIAL);
                    else glDisable(GL_COLOR_MATERIAL);
                }


                if (ImGui::Checkbox("Wireframe", &App->renderer3D->wireframe))
                {
                    App->renderer3D->SetWireframeMode(App->renderer3D->wireframe);
                }


                
            }
        }

        // 3. Show another simple window.
       

        if (about_us)
        {
            if (ImGui::Begin("About us", &about_us))
            {
                ImGui::Text("RealEngine v0.1");
                ImGui::Text("The next generation 3D Game Engine");
                ImGui::Text("Made by: ");
                if (ImGui::SmallButton("Magdalena Ostrowska"))
                    ShellExecuteA(NULL, "open", "https://github.com/magdaostrowska", NULL, NULL, SW_SHOWNORMAL);
                if (ImGui::SmallButton("Maria Garrigolas Ledo"))
                    ShellExecuteA(NULL, "open", "https://github.com/Meeeri08", NULL, NULL, SW_SHOWNORMAL);
              
                ImGui::Separator();

                if (ImGui::Button("Press here to go to our github repository")) {
                    App->RequestBrowser("https://github.com/Meeeri08/RealEngine");
                }
                ImGui::Separator();

                ImGui::Text("3rd Party Libraries used:");
                ImVec4 values_color(1.0f, 1.0f, 0.0f, 1.0f);
                //SDL Version
                SDL_version sdl_version;
                SDL_GetVersion(&sdl_version);
                ImGui::BulletText("SDL Version:");
                ImGui::SameLine();
                ImGui::TextColored(values_color, "%d.%d.%d", sdl_version.major, sdl_version.minor, sdl_version.patch); ImGui::SameLine();
                if (ImGui::SmallButton("Open SDL Website"))
                    ShellExecuteA(NULL, "open", "https://libsdl.org/", NULL, NULL, SW_SHOWNORMAL);

                //OpenGL
                int major = 0;
                int minor = 0;
                glGetIntegerv(GL_MAJOR_VERSION, &major);
                glGetIntegerv(GL_MINOR_VERSION, &minor);

                ImGui::BulletText("OpenGL ", major, minor); ImGui::SameLine();
                ImGui::TextColored(values_color, "%d.%d.%d", sdl_version.major, sdl_version.minor, sdl_version.patch); ImGui::SameLine();
                if (ImGui::SmallButton("Open OpenGL Website"))
                    ShellExecuteA(NULL, "open", "https://www.opengl.org/", NULL, NULL, SW_SHOWNORMAL);

                //ImGui Version
                ImGui::BulletText("ImGui "); ImGui::SameLine();
                ImGui::TextColored(values_color, "%s", ImGui::GetVersion()); ImGui::SameLine();
                if (ImGui::SmallButton("Open ImGui Website"))
                    ShellExecuteA(NULL, "open", "https://github.com/ocornut/imgui", NULL, NULL, SW_SHOWNORMAL);

                ////MathGeoLib
                ImGui::BulletText("MathGeoLib "); ImGui::SameLine();
                ImGui::TextColored(values_color, "1.5"); ImGui::SameLine();
                if (ImGui::SmallButton("Open MathGeoLib Website"))
                    ShellExecuteA(NULL, "open", "https://github.com/juj/MathGeoLib", NULL, NULL, SW_SHOWNORMAL);

                //Glew
                ImGui::BulletText("Glew "); ImGui::SameLine();
                ImGui::TextColored(values_color, "%d.%d.%d", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO); ImGui::SameLine();
                if (ImGui::SmallButton("Open Glew Website"))
                    ShellExecuteA(NULL, "open", "https://github.com/nigels-com/glew", NULL, NULL, SW_SHOWNORMAL);

                //DevIL
                ImGui::BulletText("DevIL "); ImGui::SameLine();
                ImGui::TextColored(values_color, "1.8.0"); ImGui::SameLine();
                if (ImGui::SmallButton("Open DevIL Website"))
                    ShellExecuteA(NULL, "open", "http://openil.sourceforge.net/", NULL, NULL, SW_SHOWNORMAL);

                //Assimp
                ImGui::BulletText("Assimp "); ImGui::SameLine();
                ImGui::TextColored(values_color, "3.1.1"); ImGui::SameLine();
                if (ImGui::SmallButton("Open Assimp Website"))
                    ShellExecuteA(NULL, "open", "http://openil.sourceforge.net/", NULL, NULL, SW_SHOWNORMAL);

                ImGui::Separator();

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
        ImGui::End();

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



