#include "InspectorWindow.h"

InspectorWindow::InspectorWindow()
{
    isActive = true;
}

InspectorWindow::~InspectorWindow()
{
    isActive = false;
}

void InspectorWindow::Draw()
{
    ImGui::Begin("Inspector", &isActive, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoFocusOnAppearing);
    ImGui::End();

}

void InspectorWindow::SetShowWindow()
{
    showWindow = !showWindow;
}

bool InspectorWindow::GetShowWindow()
{
    return showWindow;
}

