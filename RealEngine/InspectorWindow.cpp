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
    ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
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

