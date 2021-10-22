#include "Application.h"
#include "Module.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	physics = new ModulePhysics3D(this);
	editor = new ModuleEditor(this);
	console = new ModuleConsole();

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	AddModule(physics);
	AddModule(editor);

	// Scenes
	AddModule(scene_intro);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	for (int i = 0; i < list_modules.size(); i++) {
		delete list_modules[i];
	}

	list_modules.clear();

}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules

	for (int i = 0; i < list_modules.size(); i++) {
		ret = list_modules[i]->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("-------------- Application Start --------------");
	console->AddLog("-------------- Application Start --------------");

	for (int i = 0; i < list_modules.size(); i++) {
		ret = list_modules[i]->Start();
	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
update_status Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();

	update_status ret = UPDATE_CONTINUE;
	
	if (ret == UPDATE_CONTINUE)
	{
		for (int i = 0; i < list_modules.size(); i++) {
			ret = list_modules[i]->PreUpdate(dt);
		}
	}

	return ret;

}

// ---------------------------------------------
update_status Application::FinishUpdate()
{

	update_status ret = UPDATE_CONTINUE;

	if (ret == UPDATE_CONTINUE)
	{
		for (int i = 0; i < list_modules.size(); i++) {
			ret = list_modules[i]->PostUpdate(dt);
		}
	}
	
	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();


	if(ret == UPDATE_CONTINUE)
	{
		for (int i = 0; i < list_modules.size(); i++) {
			ret = list_modules[i]->Update(dt);
		}
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	if (ret == true)
	{
		for (int i = 0; i < list_modules.size(); i++) {
			ret = list_modules[i]->CleanUp();
		}
	}

	return ret;
}

bool Application::Load()
{
	return false;
}

bool Application::Save() const
{
	return false;
}

void Application::RequestBrowser(const char* link)
{
	ShellExecuteA(NULL, "open", link, NULL, NULL, SW_SHOWNORMAL);
}

float Application::GetFps()
{
	return 1.0f/dt;
}

float Application::GetMs()
{
	return dt*1000.0f;
}

HardwareSpecs Application::GetHardware()
{
	HardwareSpecs specs;
	specs.cpuCount = SDL_GetCPUCount();
	specs.cpuCache = SDL_GetCPUCacheLineSize();
	specs.ram = SDL_GetSystemRAM() / 1000.0f;
	specs.RDTSC = SDL_HasRDTSC();
	specs.MMX = SDL_HasMMX();
	specs.SSE = SDL_HasSSE();
	specs.SSE2 = SDL_HasSSE2();
	specs.SSE3 = SDL_HasSSE3();
	specs.SSE41 = SDL_HasSSE41();
	specs.SSE42 = SDL_HasSSE42();
	specs.AVX = SDL_HasAVX();
	specs.AVX2 = SDL_HasAVX2();
	specs.AltiVec = SDL_HasAltiVec();
	specs.Has3DNow = SDL_Has3DNow();

	if (specs.RDTSC) { specs.caps += "SDTSC"; }
	if (specs.MMX) { specs.caps += ", MMX"; }
	if (specs.SSE) { specs.caps += ", SSE"; }
	if (specs.SSE2) { specs.caps += ", SSE2"; }
	if (specs.SSE3) { specs.caps += ", SSE3"; }
	if (specs.SSE41) { specs.caps += ", SSE41"; }
	if (specs.SSE42) { specs.caps += ", SSE42"; }
	if (specs.AVX) { specs.caps += ", AVX2"; }
	if (specs.AltiVec) { specs.caps += ", AltiVec"; }
	if (specs.Has3DNow) { specs.caps += ", 3DNow"; }


	specs.gpu = (const char*)glGetString(GL_VENDOR);
	specs.gpuBrand = (const char*)glGetString(GL_RENDERER);

	return specs;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

