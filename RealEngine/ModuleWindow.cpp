#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	App->console->AddLog("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		App->console->AddLog("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH * SCREEN_SIZE;
		int height = SCREEN_HEIGHT * SCREEN_SIZE;
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if (WIN_FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if (WIN_RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if (WIN_BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if (WIN_FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if (window == NULL)
		{
			App->console->AddLog("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	App->console->AddLog("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

bool ModuleWindow::LoadSettings(JsonParser* data)
{
	return true;
}

bool ModuleWindow::SaveSettings(JsonParser* data) const
{
	data->AddFloat("Brightness", brightness);
	data->AddBool("Fullscreen", fullscreen);
	data->AddBool("Resizable", resizable);
	data->AddBool("Borderless", borderless);
	data->AddBool("Fullscreen Desktop", fullscreenDesktop);

	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}
void ModuleWindow::SetFullScreen(bool fullScreen)
{
	SDL_SetWindowFullscreen(window, fullScreen ? SDL_WINDOW_FULLSCREEN : 0);
}

void ModuleWindow::SetBrightness(float brightness)
{
	SDL_SetWindowBrightness(window, brightness);
}

float ModuleWindow::GetBrightness()
{
	return SDL_GetWindowBrightness(window);
}

void ModuleWindow::SetSize(int w, int h)
{
	SDL_SetWindowSize(window, w, h);

}

void ModuleWindow::SetFullscreenDesktop(bool fullscreenDesk)
{
	fullscreenDesk = fullscreenDesk;
	SDL_DisplayMode dMode;
	SDL_GetDesktopDisplayMode(0, &dMode);

	if (fullscreenDesk)
	{
		SDL_SetWindowSize(window, dMode.w, dMode.h);
		SDL_SetWindowPosition(window, 0, 0);
	}
	else
	{
		SDL_SetWindowSize(window, dMode.w / 2, dMode.h / 2);
		SDL_SetWindowPosition(window, dMode.w / 4, dMode.h / 4);
	}
}

void ModuleWindow::SetName()
{
	name = appName + " - " + orgName;
	SDL_SetWindowTitle(window, name.c_str());
}

void ModuleWindow::SetBorder(bool borderless)
{
	SDL_SetWindowBordered(window, (SDL_bool)borderless);
}

void ModuleWindow::SetResizable(bool resizable)
{
	SDL_SetWindowResizable(window, (SDL_bool)resizable);

}

