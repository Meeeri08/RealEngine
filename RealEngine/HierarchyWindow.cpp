#include "HierarchyWindow.h"

HierarchyWindow::HierarchyWindow()
{
	openPopUp = false;
}

HierarchyWindow::~HierarchyWindow()
{
}

void HierarchyWindow::Draw(Application* App)
{
	ImGui::Begin("Hierarchy");

	ImGuiTreeNodeFlags default_flags = ImGuiTreeNodeFlags_NoTreePushOnOpen;
	DrawGameObject(App->scene_intro->GetRoot(), default_flags, App->scene_intro->GetRoot());

	ImGui::End();
}

void HierarchyWindow::DrawGameObject(GameObject* gameObject, ImGuiTreeNodeFlags default_flags, GameObject* root)
{
	bool drawAgain = true;

	ImGuiTreeNodeFlags flags = default_flags;

	if (gameObject->children.empty()) {
		flags |= ImGuiTreeNodeFlags_Leaf;
	}

	if (gameObject->isSelected)
	{
		flags |= ImGuiTreeNodeFlags_Selected;
	}

	if (gameObject != root)
		drawAgain = ImGui::TreeNodeEx(gameObject, flags, gameObject->name.c_str());
	else
		drawAgain = true;


	if (ImGui::IsItemClicked(0))
	{
		//App->scene->selectGameObject(gameObject);
	}

	if (ImGui::BeginPopupContextItem((gameObject->name + "rightClick").c_str(), 1))
	{
		if (ImGui::Button("Delete"))
		{
			gameObject->wantToDelete = true;
		}
		ImGui::EndPopup();
	}

	/*

	if (App->scene->selected_GO != nullptr)
	{
		if (App->scene->selected_GO->to_delete == true)
		{
			App->scene->DestroyGameObject(gameObject);
		}
	}
	*/

	if (ImGui::BeginDragDropSource())
	{
		uint gameObject_UUID = gameObject->GetUUID();
		ImGui::SetDragDropPayload("Reparenting", &gameObject_UUID, sizeof(uint));
		ImGui::Text(gameObject->name.c_str());
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Reparenting", ImGuiDragDropFlags_SourceAllowNullID))
		{
			//GameObject* draggedGameobject = App->scene->GetGameObjectByUUID(*(uint*)payload->Data);
			//if (draggedGameobject != nullptr)
				//draggedGameobject->SetParent(gameObject);
		}
		ImGui::EndDragDropTarget();
	}

	if (drawAgain)
	{
		for (uint i = 0; i < gameObject->children.size(); i++)
		{
			DrawGameObject(gameObject->children[i], flags, root);
		}
	}
}

void HierarchyWindow::SetShowWindow()
{
	showWindow = !showWindow;
}

bool HierarchyWindow::GetShowWindow()
{
	return showWindow;
}
