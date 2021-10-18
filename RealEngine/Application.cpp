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
	LOG("Application Start --------------");

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

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}
