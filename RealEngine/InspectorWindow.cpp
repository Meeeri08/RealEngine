#include "InspectorWindow.h"

InspectorWindow::InspectorWindow()
{
    isActive = true;
}

InspectorWindow::~InspectorWindow()
{
    isActive = false;
}

void InspectorWindow::Draw(Application* App)
{
    ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	GameObject* gameObject = App->scene_intro->selectedGameObject; 

	if (gameObject == nullptr)
	{
		ImGui::End();
		return;
	}

	strcpy(name, gameObject->name.c_str());

	if (ImGui::InputText(" ", name, IM_ARRAYSIZE(name)))
		gameObject->name.assign(name);

	if (gameObject->transformation != nullptr) DrawTransform(gameObject->transformation);
	if (gameObject->mesh != nullptr) DrawMesh(gameObject->mesh);

	ImGui::End();
}

void InspectorWindow::DrawTransform(Transformation* transformation)
{
	if (ImGui::CollapsingHeader("Transformation"), ImGuiTreeNodeFlags_DefaultOpen) {
		float3 pos = transformation->GetPosition();
		float3 scale = transformation->GetScale();
		float3 rotation = transformation->GetEulerRotation();
		int columnNum = 4;

		ImGui::Columns(columnNum, "Transformation");

		ImGui::NextColumn();
		ImGui::Text("X"); ImGui::NextColumn();
		ImGui::Text("Y"); ImGui::NextColumn();
		ImGui::Text("Z"); ImGui::NextColumn();
		ImGui::Separator();

		// Position
		ImGui::AlignTextToFramePadding();
		ImGui::Text("Position"); ImGui::NextColumn();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("##PositionX", &pos.x, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetPosition(pos);
		}
		ImGui::NextColumn();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("##PositionY", &pos.y, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetPosition(pos);
		}
		ImGui::NextColumn();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("##PositionZ", &pos.z, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetPosition(pos);
		}
		ImGui::NextColumn();

		// Rotation
		ImGui::AlignTextToFramePadding();
		ImGui::Text("Rotation"); ImGui::NextColumn();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);

		if (ImGui::DragFloat("##RotationX", &rotation.x, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetRotation(rotation);
		}
		ImGui::NextColumn();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("##RotationY", &rotation.y, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetRotation(rotation);
		}
		ImGui::NextColumn();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("##RotationZ", &rotation.z, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetRotation(rotation);
		}
		ImGui::NextColumn();
		// Scale
		ImGui::AlignTextToFramePadding();
		ImGui::Text("Scale"); ImGui::NextColumn();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("##ScaleX", &scale.x, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetScale(scale);
		}
		ImGui::NextColumn();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("##ScaleY", &scale.y, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetScale(scale);
		}
		ImGui::NextColumn();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("##ScaleZ", &scale.z, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetScale(scale);
		}

		ImGui::NextColumn();
		ImGui::Columns(1);
	}

}

void InspectorWindow::DrawMesh(Mesh* mesh)
{
	if (ImGui::CollapsingHeader("Mesh"))
	{
		ImGui::Checkbox("Active", &mesh->isActive);

		ImGui::Text("Index: %i", mesh->id_index); ImGui::NewLine();
		ImGui::Text("Normals: %f", mesh->normals); ImGui::NewLine();
		ImGui::Text("Vertices: %i", mesh->num_vertex); ImGui::NewLine();
		
	}
}
