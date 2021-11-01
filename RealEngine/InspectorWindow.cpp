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
    ImGui::Begin("Inspector", &isActive, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	GameObject* gameObject = App->scene_intro->selectedGameObject; 

	if (gameObject == nullptr)
	{
		ImGui::End();
		return;
	}

	const char* tmp_name = gameObject->name.c_str();
	strcpy(name, tmp_name);

	if (ImGui::InputText(" ", name, IM_ARRAYSIZE(name)))
		gameObject->name.assign(name);

	if (gameObject->transformation != nullptr) {
		DrawTransform(gameObject->transformation);
	}
	if (gameObject->mesh != nullptr) {
		DrawMesh(gameObject->mesh);
	}
	ImGui::End();
}

void InspectorWindow::DrawTransform(Transformation* transformation)
{
	if (ImGui::CollapsingHeader("Transformation")) {

		float3 position = transformation->GetPosition();
		float3 scale = transformation->GetScale();
		float3 rotation = transformation->GetEulerRotation();
		int columnNumber = 4;

		ImGui::Columns(columnNumber, "Transformation");

		ImGui::NextColumn();
		ImGui::Text("X"); ImGui::NextColumn();
		ImGui::Text("Y"); ImGui::NextColumn();
		ImGui::Text("Z"); ImGui::NextColumn();
		ImGui::Separator();

		ImGui::Text("Position"); ImGui::NextColumn();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("PositionX", &position.x, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetPosition(position);
		}
		ImGui::NextColumn();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("PositionY", &position.y, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetPosition(position);
		}
		ImGui::NextColumn();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("PositionZ", &position.z, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetPosition(position);
		}
		ImGui::NextColumn();

		ImGui::Text("Scale"); ImGui::NextColumn();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("ScaleX", &scale.x, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetScale(scale);
		}
		ImGui::NextColumn();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("ScaleY", &scale.y, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetScale(scale);
		}
		ImGui::NextColumn();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("ScaleZ", &scale.z, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetScale(scale);
		}
		ImGui::NextColumn();

		ImGui::Text("Rotation"); ImGui::NextColumn();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);

		if (ImGui::DragFloat("RotationX", &rotation.x, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetRotation(rotation);
		}
		ImGui::NextColumn();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("RotationY", &rotation.y, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetRotation(rotation);
		}
		ImGui::NextColumn();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
		if (ImGui::DragFloat("RotationZ", &rotation.z, 0.05f, 0.f, 0.f, "%.2f"))
		{
			transformation->SetRotation(rotation);
		}
		ImGui::Columns(1);
	}
}

void InspectorWindow::DrawMesh(Mesh* mesh)
{
	if (ImGui::CollapsingHeader("Mesh"))
	{
		//ImGui::Text("Index: %i", mesh.); ImGui::NewLine();
		ImGui::Text("Normals: %f", mesh->normal_id); ImGui::NewLine();
		ImGui::Text("Vertices: %i", mesh->num_vertex); ImGui::NewLine();
	}
}