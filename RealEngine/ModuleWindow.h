#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include <string>

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);
	void SetFullScreen(bool fullscreen);
	void SetResizable(bool resizable);
	void SetBrightness(float brightness);
	void SetSize(int w, int h);

	void SetName();



	float GetBrightness();

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;

	std::string appName = "RealEngine";
	std::string orgName = "UPC CITM";
private:
	std::string name;
};

#endif // __ModuleWindow_H__