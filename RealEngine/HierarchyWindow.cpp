#include "HierarchyWindow.h"

HierarchyWindow::HierarchyWindow(){}

HierarchyWindow::~HierarchyWindow() {}

void HierarchyWindow::Draw(Application* App)
{
	ImGui::Begin("Hierarchy");

	ImGuiTreeNodeFlags default_flags = ImGuiTreeNodeFlags_NoTreePushOnOpen;
	DrawGameObject(App, App->scene_intro->GetRoot(), default_flags, App->scene_intro->GetRoot());

	ImGui::End();
}

void HierarchyWindow::DrawGameObject(Application* App, GameObject* gameObject, ImGuiTreeNodeFlags default_flags, GameObject* root)
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

	if (gameObject == root)
		drawAgain = true;
	else
		drawAgain = ImGui::TreeNodeEx(gameObject, flags, gameObject->name.c_str());

	if (ImGui::IsItemClicked(0))
		App->scene_intro->SelectGameObject(gameObject);

	if (ImGui::BeginPopupContextItem((gameObject->name + "rightClick").c_str(), 1))
	{
		if (ImGui::Button("Delete"))
		{
			gameObject->wantToDelete = true;
		}
		ImGui::EndPopup();
	}

	if (App->scene_intro->selectedGameObject != nullptr)
	{
		if (App->scene_intro->selectedGameObject->wantToDelete == true)
		{
			App->scene_intro->DestroyGameObject(gameObject);
		}
	}
	
	if (ImGui::BeginDragDropSource())
	{
		const char* tmp_name = gameObject->name.c_str();

		uint gameObject_UUID = gameObject->GetUUID();
		ImGui::SetDragDropPayload("Reparenting", &gameObject_UUID, sizeof(uint));
		ImGui::Text(tmp_name);
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Reparenting", ImGuiDragDropFlags_SourceAllowNullID))
		{
			GameObject* draggedGameobject = App->scene_intro->GetGameObjectByUUID(*(uint*)payload->Data);
			if (draggedGameobject != nullptr)
				draggedGameobject->SetParent(gameObject);
		}
		ImGui::EndDragDropTarget();
	}

	if (drawAgain == true)
	{
		for (uint i = 0; i < gameObject->children.size(); i++)
		{
			DrawGameObject(App, gameObject->children[i], flags, root);
		}
	}
}
