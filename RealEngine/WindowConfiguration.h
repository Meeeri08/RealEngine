#pragma once

#include "Globals.h"
#include "imgui/imconfig.h"

class WindowConfiguration
{
public:
	WindowConfiguration();
	~WindowConfiguration();

	virtual void Draw() { ; };

	virtual void SetShowWindow(bool new_value);
	virtual void SetShowWindow();
	virtual bool GetShowWindow(); 

protected:
	bool showWindow;
};

