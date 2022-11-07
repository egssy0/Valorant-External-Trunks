#pragma once
#include "../Game/cheat.hpp"
#include "xor.hpp"
#include "icons.h"
#include "xorstr.h"
#include "iconcpp.h"
#include "font.h"
//EndSceneFn oEndScene;
int iTab;
string expiryDate;
std::string ip;
std::string hwid;
std::string lastlogin;
std::string onlineUsers;
char displayHWID[50];
char displayExpiry[50];
char harwareID[50];
char date[50];

static const char* boxStyle[] =
{
	"Off",
	"2D",
	"Corner Box",
	"2D Filled",
};


void color()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	style.Colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15, 255);
	style.Colors[ImGuiCol_ChildBg] = ImColor(10, 10, 10, 255);
	style.Colors[ImGuiCol_Border] = ImColor(15, 15, 15, 255);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.70f, 0.02f, 0.60f, 0.22f);
	//style.Colors[ImGuiCol_CloseButton] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	//style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
}

void styled()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.f;
	style.FramePadding = ImVec2(4, 0);
	style.WindowPadding = ImVec2(0, 0);
	style.ItemSpacing = ImVec2(0, 0);
	style.ScrollbarSize = 10.f;
	style.ScrollbarRounding = 0.f;
	style.GrabMinSize = 5.f;
}

void ButtonColor(int r, int g, int b)
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Button] = ImColor(r, g, b);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(r, g, b);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(r, g, b);
}
class GradientLine {
public:

	static bool Render(ImVec2 size)
	{
		static ImColor gradient_colors[] =
		{
			//https://txwes.libguides.com/c.php?g=978475&p=7075536

			//Red
			ImColor(255, 0, 0),
			//Yellow
			ImColor(255,255,0),
			//Lime
			ImColor(0, 255, 0),
			//Cyan / Aqua
			ImColor(0, 255, 255),
			//Blue
			ImColor(0, 0, 255),
			//Magenta / Fuchsia
			ImColor(255, 0, 255),
			//Red
			ImColor(255, 0, 0)
		};

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImVec2      screen_pos = ImGui::GetCursorScreenPos();

		static int pos = 0;

		if (size.x - pos == 0)
			pos = 0;
		else
			pos++;

		for (int i = 0; i < 6; ++i)
		{
			ImVec2 item_spacing = ImGui::GetStyle().ItemSpacing;

			auto render = [&](int displacement)
			{
				draw_list->AddRectFilledMultiColor
				(
					ImVec2((screen_pos.x - item_spacing.x - displacement) + (i) * (size.x / 6), (screen_pos.y - item_spacing.y)),
					ImVec2((screen_pos.x - item_spacing.x + (item_spacing.x * 2) - displacement) + (i + 1) * (size.x / 6), (screen_pos.y - item_spacing.y) + (size.y)),

					//add one to color to create a skuffed blend
					gradient_colors[i], gradient_colors[i + 1], gradient_colors[i + 1], gradient_colors[i]
				);
			};

			render((pos)); render((pos - size.x));
		}
		return true;
	}
};
void background()
{
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Once);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.09f, 0.09f, 0.09f, 0.40f / 1.f * 2.f));
	static const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove;
	ImGui::Begin("##background", nullptr, flags);
	ImGui::End();
	ImGui::PopStyleColor();
}
auto drawmenu() -> void
{
	ImGui_ImplDX9_NewFrame();
	CheatLoop();
	
	bool one = false;
	bool two = false;
	if (GetAsyncKeyState(VK_INSERT) & 1) { Settings::bMenu = !Settings::bMenu; }

	if (Settings::bMenu)
	{
		background();
		
		ImGuiIO& io = ImGui::GetIO();

		static int tabb = 0;
		io.IniFilename = nullptr;


		static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
		ImFontConfig icons_config;

		ImFontConfig CustomFont;
		CustomFont.FontDataOwnedByAtlas = false;


		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		icons_config.OversampleH = 2.5;
		icons_config.OversampleV = 2.5;
		io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 21.f, &CustomFont);
		io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 19.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontDefault();
		ImGuiStyle& style = ImGui::GetStyle();

		ImVec2 pos;

		//ImGui::SetWindowSize(ImVec2(840, 560));
		ImGui::SetNextWindowSize(ImVec2(840, 560));

		ImGui::Begin("", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
		GradientLine::Render(ImVec2(ImGui::GetContentRegionAvail().x * 2, 3));
		{

			pos = ImGui::GetWindowPos();

			ImGui::Columns(2, nullptr, false);
			ImGui::SetColumnOffset(1, 135);

			ButtonColor(15, 15, 15);
			ImGui::Button("##upprtabs", ImVec2(114, 20));

			ImGui::SameLine();
			styled();
			color();
			ButtonColor(50, 50, 50);
			ImGui::Button("##rageupline", ImVec2(1, 20));

			/*rage*/
			{
				ImGui::SameLine();

				ButtonColor(50, 50, 50);
				ImGui::Button("##fgfgfg", ImVec2(1, 1));
				ImGui::SameLine();

				ButtonColor(50, 50, 50);
				ImGui::Button("##fgfgfg", ImVec2(1, 1));

				if (iTab == 0) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##rageupline", ImVec2(118, 1));

				ImGui::SameLine();

				ButtonColor(50, 50, 50);
				ImGui::Button("##fgfgfg", ImVec2(1, 1));

				ButtonColor(15, 15, 15);
				if (iTab == 0) style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200); else style.Colors[ImGuiCol_Text] = ImColor(80, 80, 80);
				if (ImGui::Button( "aimbot", ImVec2(118, 100))) iTab = 0;

				ImGui::SameLine();

				if (iTab != 0)ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##gfgfgfgfgfgf", ImVec2(1, 100));

				if (iTab == 0) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##ragedownline", ImVec2(118, 1));

				ImGui::SameLine();

				ButtonColor(50, 50, 50);
				ImGui::Button("##fgfgfg", ImVec2(1, 1));

			}

			/*legit*/
			{
				if (iTab == 1) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##lupline", ImVec2(118, 1));

				ImGui::SameLine();

				ButtonColor(50, 50, 50);
				ImGui::Button("##fgfgfg", ImVec2(1, 1));

				ButtonColor(15, 15, 15);
				if (iTab == 1) style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200); else style.Colors[ImGuiCol_Text] = ImColor(80, 80, 80);
				if (ImGui::Button("visuals", ImVec2(118, 100))) iTab = 1;

				ImGui::SameLine();

				if (iTab != 1)ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##gfgfgfgfgfgf", ImVec2(1, 100));

				if (iTab == 1) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##ldownline", ImVec2(118, 1));

				ImGui::SameLine();

				ButtonColor(50, 50, 50);
				ImGui::Button("##fgfgfg", ImVec2(1, 1));
			
			}

			/*visuals*/
			{
				if (iTab == 2) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##vupline", ImVec2(118, 1));

				ImGui::SameLine();

				ButtonColor(50, 50, 50);
				ImGui::Button("##fgfgfg", ImVec2(1, 1));

				ButtonColor(15, 15, 15);
				if (iTab == 2) style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200); else style.Colors[ImGuiCol_Text] = ImColor(80, 80, 80);
				if (ImGui::Button("misc", ImVec2(118, 100))) iTab = 2;
				ImGui::SameLine();

				if (iTab != 2)ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##gfgfgfgfgfgf", ImVec2(1, 100));

				if (iTab == 2) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##vdownline", ImVec2(118, 1));

				ImGui::SameLine();

				ButtonColor(50, 50, 50);
				ImGui::Button("##fgfgfg", ImVec2(1, 1));
			}

			/*misc*/
			{
				if (iTab == 3) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##mupline", ImVec2(118, 1));

				ImGui::SameLine();

				ButtonColor(50, 50, 50);
				ImGui::Button("##fgfgfg", ImVec2(1, 1));

				ButtonColor(15, 15, 15);
				if (iTab == 3) style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200); else style.Colors[ImGuiCol_Text] = ImColor(80, 80, 80);
				if (ImGui::Button("config", ImVec2(118, 100))) iTab = 3;
				ImGui::SameLine();

				if (iTab != 3)ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##gfgfgfgfgfgf", ImVec2(1, 100));

				if (iTab == 3) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##mdownline", ImVec2(118, 1));

				ImGui::SameLine();

				ButtonColor(50, 50, 50);
				ImGui::Button("##fgfgfg", ImVec2(1, 1));
			}
			
			/*misc*/
			{
				if (iTab == 4) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##mupline", ImVec2(118, 1));

				ImGui::SameLine();

				ButtonColor(50, 50, 50);
				ImGui::Button("##fgfgfg", ImVec2(1, 1));

				ButtonColor(15, 15, 15);
				if (iTab == 4) style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200); else style.Colors[ImGuiCol_Text] = ImColor(80, 80, 80);
				if (ImGui::Button("about", ImVec2(118, 100))) iTab = 4;
				ImGui::SameLine();

				if (iTab != 4)ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##gfgfgfgfgfgf", ImVec2(1, 100));

				if (iTab == 4) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Button("##mdownline", ImVec2(118, 1));

				ImGui::SameLine();

				ButtonColor(50, 50, 50);
				ImGui::Button("##fgfgfg", ImVec2(1, 1));
			}

			ButtonColor(15, 15, 15);
			ImGui::Button("##upprtabs", ImVec2(118, 20));

			ImGui::SameLine();

			ButtonColor(50, 50, 50);
			ImGui::Button("##rageupline", ImVec2(1, 20));

			ImGui::NextColumn();
			style.WindowPadding = ImVec2(8, 8);
			style.ItemSpacing = ImVec2(4, 4);
			style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
			style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
			style.Colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15, 255);

			style.Colors[ImGuiCol_Border] = ImColor(15, 15, 15, 255);
			style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
			style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
			style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
			style.Colors[ImGuiCol_TitleBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
			style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
			style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
			style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.78f);
			style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
			style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
			
			
			style.Colors[ImGuiCol_Button] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
			style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);

			style.Colors[ImGuiCol_Header] = ImVec4(15, 15, 15, 255);
			style.Colors[ImGuiCol_HeaderHovered] = ImVec4(15, 15, 15, 255);
			style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);

			ImGui::BeginChild("main", ImVec2(700, 540));
			{
				if (iTab == 0) {

					ImGui::Spacing();
					ImGui::Text(skCrypt("   "));
					ImGui::Checkbox(skCrypt("Memory Aimbot"), &Settings::aimbot::aimbot);
				//	ImGui::Text(skCrypt("   "));
					if (Settings::aimbot::aimbot) Settings::aimbot::silent = false;
					ImGui::Checkbox(skCrypt("Silent Aimbot"), &Settings::aimbot::silent);
					//ImGui::Text(skCrypt("   "));
					if (Settings::aimbot::silent) Settings::aimbot::aimbot = false;
					ImGui::Combo(skCrypt("Hitbox"), &Settings::aimbot::selectedhitbox, Settings::aimbot::hitbox, IM_ARRAYSIZE(Settings::aimbot::hitbox));
					//ImGui::Text(skCrypt("   "));

					ImGui::Spacing();
					ImGui::Checkbox(skCrypt("Nazi Crosshair"), &Settings::aimbot::nazicrosshair);
					//ImGui::Text(skCrypt("   "));
					ImGui::Checkbox(skCrypt("Visiblity Check"), &Settings::aimbot::vischeck);
					//ImGui::Text(skCrypt("   "));
					ImGui::Checkbox(skCrypt("Smoothing"), &Settings::aimbot::smooth);
					//ImGui::Text(skCrypt("   "));

					ImGui::Checkbox(skCrypt("Show FOV Circle"), &Settings::aimbot::drawfov);
					//ImGui::Text(skCrypt("   "));

					ImGui::Checkbox(skCrypt("Filled FOV"), &Settings::aimbot::filledfov);
					//ImGui::Text(skCrypt("   "));

					ImGui::Checkbox(skCrypt("Recoil Control (Standalone)"), &Settings::aimbot::rcs);
					//ImGui::Text(skCrypt("   "));
					ImGui::Spacing();
					ImGui::Text(skCrypt("FOV Size"));
					//ImGui::Text(skCrypt("   "));
					ImGui::SliderFloat("    ", &Settings::aimbot::fov, 10, 900);
					ImGui::Text(skCrypt("Smoothing "));
					//ImGui::Text(skCrypt("   "));

					ImGui::SliderFloat("  ", &Settings::aimbot::smoothness, 1, 100);
				//	ImGui::Text(skCrypt("   "));
					ImGui::Text(skCrypt("Aimbot Key: "));
					ImGui::SameLine();
					//ImGui::Text(skCrypt("   "));
					HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);
				}
				if (iTab == 1)
				{
					ImGui::Text("   ");

					ImGui::Checkbox(skCrypt("Enable ESP"), &Settings::Visuals::showEsp);
					if (Settings::Visuals::showEsp)
					{
						ImGui::Text(skCrypt("   "));
						ImGui::Text(skCrypt("ESP Style"));
					//	ImGui::Text(skCrypt("   "));
						ImGui::Combo("", &Settings::boxMode, boxStyle, IM_ARRAYSIZE(boxStyle));
						//ImGui::Text(skCrypt("   "));
						ImGui::Checkbox(skCrypt("Snaplines"), &Settings::Visuals::snapline);
						if (Settings::Visuals::snapline == true)
						{
							ImGui::Combo(skCrypt("Position"), &Settings::Visuals::snaplinepos, Settings::Visuals::snappos, IM_ARRAYSIZE(Settings::Visuals::snappos));
						}
						//ImGui::Text(skCrypt("   "));

						ImGui::Checkbox(skCrypt("Health ESP"), &Settings::Visuals::health);
						if (Settings::Visuals::health == true)
						{
							ImGui::Combo(skCrypt("Health Type"), &Settings::Visuals::healthtype, Settings::Visuals::healtht, IM_ARRAYSIZE(Settings::Visuals::healtht));
						}
						//ImGui::Text(skCrypt("   "));

						ImGui::Checkbox(skCrypt("HeadCircle ESP"), &Settings::Visuals::headcircle);
						if (Settings::Visuals::headcircle == true)
						{
							ImGui::Combo(skCrypt("HeadCircle Type"), &Settings::Visuals::headboxtype, Settings::Visuals::headboxt, IM_ARRAYSIZE(Settings::Visuals::headboxt));
						}
						//ImGui::Text(skCrypt("   "));
						ImGui::Checkbox(skCrypt("Visible Check"), &Settings::Visuals::visibleesp);
					//	ImGui::Text(skCrypt("   "));
						ImGui::Checkbox(skCrypt("Skeleton ESP"), &Settings::Visuals::skeleton);
						//ImGui::Text(skCrypt("   "));
						ImGui::Checkbox(skCrypt("Distance"), &Settings::Visuals::bDistance);
					//	ImGui::Text(skCrypt("   "));
						ImGui::Checkbox(skCrypt("Glow"), &Settings::Visuals::glow);
					//	ImGui::Text(skCrypt("   "));
						ImGui::Checkbox(skCrypt("Agent Name"), &Settings::Visuals::name);
					//	ImGui::Text(skCrypt("   "));
						ImGui::Checkbox(skCrypt("Dormant ESP"), &Settings::Visuals::dormant);
					//	ImGui::Text(skCrypt("   "));
						ImGui::Checkbox(skCrypt("Cham"), &Settings::Visuals::outlines);
					//	ImGui::Text(skCrypt("   "));
						ImGui::Checkbox(skCrypt("Glowing-Chams"), &Settings::Visuals::glowingChams);
						ImGui::Checkbox(skCrypt("Radar"), &Settings::Visuals::directional);
						
						ImGui::Checkbox(skCrypt("Info Bar"), &Settings::Visuals::infobar);
						ImGui::Checkbox(skCrypt("Hit Sound"), &Settings::Visuals::hitsound);
						ImGui::Checkbox(skCrypt("Draw Recoil"), &Settings::Visuals::drawRecoil);

						//	ImGui::Text(skCrypt("   "));

					}
					else {
						Settings::Visuals::snapline = false;
						Settings::Visuals::headcircle = false;
						Settings::Visuals::skeleton = false;

					
						Settings::Visuals::health = false;
						Settings::Visuals::visibleesp = false;


						Settings::Visuals::name = false;

						Settings::Visuals::box = true;
						Settings::Visuals::showEsp = false;
						Settings::Visuals::dormant = false;

						Settings::Visuals::bDistance = false;
						Settings::Visuals::crouch = false;
					}
						

					
				}
				if (iTab == 2) {
					ImGui::Text(skCrypt("   "));
					ImGui::Checkbox(skCrypt("Enable Exploits"), &Settings::Misc::Exploit);
					if (Settings::Misc::Exploit) 
					{
						ImGui::Text(skCrypt("   "));

						ImGui::Checkbox(skCrypt("Radar"), &Settings::Misc::radar);

						if (ImGui::Button(skCrypt("Switch Team")))
						{
							uintptr_t playetstatelocal = driver.readv<uintptr_t>(g_local_player_pawn + offsets::PlayerState);
							uintptr_t teamComponent = driver.readv<uintptr_t>(playetstatelocal + offsets::TeamComponent);
							int teamID = driver.readv<int>(teamComponent + offsets::TeamID);

							teamID = !(bool)teamID;

							driver.write<int>(teamComponent + offsets::TeamID, teamID);
						}
						ImGui::Checkbox(skCrypt("Fast Crouch"), &Settings::Visuals::crouch);
						ImGui::Checkbox(skCrypt("FOV Changer"), &Settings::Misc::FOVChanger);
						if (Settings::Misc::FOVChanger) 
						{
							ImGui::SliderFloat("Fov", &Settings::Misc::fov, 1, 360);

						}
						ImGui::Checkbox(skCrypt("Bunny Hop"), &Settings::Misc::BunnyHop);
						ImGui::Checkbox(skCrypt("Auto Strafe"), &Settings::Misc::Strafe);

						ImGui::Text(skCrypt("   "));
						
					}
					

				}
				if (iTab == 3) {
					ImGui::Text(skCrypt("   "));
					if (ImGui::Button(skCrypt(" Save Config "))) {
						ImGui::Text(skCrypt(" Config Saved  "));

					}
					ImGui::Text(skCrypt("   "));
					if (ImGui::Button(skCrypt(" Load Config "))) {
						ImGui::Text(skCrypt(" Config Loaded  "));

					}
					ImGui::Text(skCrypt("   "));



				}
				if (iTab == 4) {
					
					int n = hwid.length();
					displayHWID[n + 1];
					strcpy(displayHWID, hwid.c_str());

					int z = expiryDate.length();
					displayExpiry[z + 1];
					strcpy(displayExpiry, hwid.c_str());


					ImGui::Text(skCrypt("   "));
					char usr[20] = "user: ";
					ImGui::InputText(key, usr, 32);
					

					ImGui::Text(skCrypt("   "));
					char x[20] = "hwid: ";
					ImGui::InputText(displayHWID, x, 32);

					ImGui::Text(skCrypt("   "));
					char y[20] = "expiry: ";
					ImGui::InputText(displayExpiry, y, 32);

					ImGui::Text(skCrypt("   "));


					ImGui::Text(skCrypt("   "));
					char status[20] = "Status: ";
					char nothing[20] = "";
					char ud[20] = "Undetected";
					ImGui::InputText(nothing, status, sizeof(status));
					ImGui::SameLine();
					ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
					ImGui::Text(ud);
					ImGui::PopStyleColor();

					ImGui::Checkbox(skCrypt("Water Mark"), &Settings::Misc::water);
					ImGui::Text(skCrypt(" "));

					if (ImGui::Button(skCrypt("Uninject Cheat")))
					{
						exit(0);
					}


				}

			}ImGui::EndChild();
		}
		
		ImGui::End();
	}

		
	
}

