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
	bool LoadSettings(JsonParser* data)override;
	bool SaveSettings(JsonParser* data)const override;

	//Window functions
	void SetTitle(const char* title);
	void SetFullScreen(bool fullscreen);
	void SetBrightness(float brightness);
	void SetSize(int w, int h);
	void SetFullscreenDesktop(bool fullscreenDesk);
	bool IsFullscreenDesktop() const { return fullscreenDesktop; }
	void SetName();
	void SetBorder(bool borderless);
	void SetResizable(bool resizable);

	float GetBrightness();

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;

	std::string appName = "RealEngine";
	std::string orgName = "UPC CITM";

	//Screen properties slides
	int height = 720;
	int width = 1200;
	int max_fps = 60;
	float brightness = 1.0f;


	//screen variables
	bool fullscreenDesktop = false;
	bool resizable = false;
	bool borderless = false;
	bool fullscreen = false;
	bool active = false;
private:
	std::string name;

};

#endif // __ModuleWindow_H__