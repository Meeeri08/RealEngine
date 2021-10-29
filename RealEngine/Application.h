#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModulePhysics3D.h"
#include "ModuleEditor.h"
#include "ModuleConsole.h"
#include "FBXLoader.h"
class ModuleScene;

#include <vector>

struct HardwareSpecs
{
	int cpuCount;
	int cpuCache;
	float ram;
	bool RDTSC = false;
	bool MMX = false;
	bool SSE = false;
	bool SSE2 = false;
	bool SSE3 = false;
	bool SSE41 = false;
	bool SSE42 = false;
	bool AVX = false;
	bool AVX2 = false;
	bool AltiVec = false;
	bool Has3DNow = false;

	const char* gpu;
	const char* gpuBrand;
	float vramBudget;
	float vramUsage;
	float vramAvailable;
	float vramReserved;

	std::string caps;
};

class Module;

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModulePhysics3D* physics;
	ModuleEditor* editor;
	ModuleConsole* console;
	ModuleScene* scene;
	FBXLoader* fbx_loader;

private:

	Timer	ms_timer;
	float	dt;
	std::vector<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	bool Load();
	bool Save() const;
	void RequestBrowser(const char* link);
	float GetFps();
	float GetMs();
	HardwareSpecs GetHardware();
	//Configuration
	int capFPS = 60;
	//Hardware
	SDL_version SDL_version;
	

private:

	void AddModule(Module* mod);

	update_status PrepareUpdate();
	update_status FinishUpdate();
};

extern Application* App;