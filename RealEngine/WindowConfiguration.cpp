#include "WindowConfiguration.h"

WindowConfiguration::WindowConfiguration()
{
	showWindow = true;
}

WindowConfiguration::~WindowConfiguration()
{
}

void WindowConfiguration::SetShowWindow(bool value)
{
	showWindow = value;
}

void WindowConfiguration::SetShowWindow()
{
	showWindow = !showWindow;
}

bool WindowConfiguration::GetShowWindow()
{
	return showWindow;
}

