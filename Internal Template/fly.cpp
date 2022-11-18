#include "fly.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


Fly::Fly(Cheats* cheatsIn)
{
	name = "Fly";
	vertSpeedMult = 0.1;
	enable = false;
	cheats = cheatsIn;
}


bool Fly::tick()
{
	
	return true;
}

void Fly::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Fly", ImGuiTreeNodeFlags_Leaf);
}

void Fly::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Fly"))
	{
		ImGui::Checkbox("Enable##Fly", &enable);
		ImGui::DragFloat("Vertical Speed##Fly", &vertSpeedMult, 0.01, 0, 2);
	}
}