#pragma once
#include "sdk.hpp"
#include <iostream>
#define UCONST_Pi 3.1415926535

#define GLFW_EXPOSE_NATIVE_WIN32
#define RadianToURotation 180.0f / UCONST_Pi

#include "../xorstr.h"
#include <tlHelp32.h>
#include <string>
#include "../../Includes/imgui/imgui.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <tchar.h>
#include <intrin.h>
#include "auth.hpp"
#include <ProcessSnapshot.h>
#include "xor.hpp"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include "auth.hpp"
#include "globals.hpp"
#include "structs.hpp"
using namespace Globals;
using namespace Camera;
using namespace UE4;

void RCS(FVector x);
GWorld* UWorld;
GGameInstance* UGameInstance;
GLocalPlayer* ULocalPlayer;
GPlayerController* APlayerController;
GPawn* APawn;
GPrivatePawn* APrivatePawn;
GULevel* ULevel;
GUSkeletalMeshComponent* USkeletalMeshComponent;
uintptr_t g_local_player_pawn;
uintptr_t g_local_player_controller;
uintptr_t gcameramanager;
bool cached = false;
uintptr_t WorldPtr;
uintptr_t unique_id;
ImVec2 boted_vex_screen;

FVector pRadar;
FVector AimLock(FVector Target);
struct State {
	uintptr_t keys[7];
};
UINT profetrol;

static ImU32 g_esp_color = ImGui::ColorConvertFloat4ToU32(ImVec4(1, 0, 0.4F, 1));
static ImU32 g_color_white = ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1));
struct FLinearColor {
	float R; // 0x00(0x04)
	float G; // 0x04(0x04)
	float B; // 0x08(0x04)
	float A; // 0x0c(0x04)
};


bool test1 = false;
bool test2 = false;
namespace hotkeys
{
	int aimkey;
	int airstuckey;
	int instares;
}

static int keystatus = 0;
static int realkey = 0;

bool GetKey(int key)
{
	realkey = key;
	return true;
}
void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}

static const char* keyNames[] =
{
	"Press any key..",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};

static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = "Select Key";
	else
		aimkeys = preview_value;

	if (status == 1)
	{

		aimkeys = "Press the Key";
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}
auto CacheGame() -> void
{
	auto guardedregion = driver.guarded_region();
	while (true)
	{
		std::vector<ValEntity> CachedList;

		WorldPtr = GetWorld(guardedregion);

		auto ULevelPtr = UWorld->ULevel(WorldPtr);
		auto UGameInstancePtr = UWorld->GameInstance(WorldPtr);

		auto ULocalPlayerPtr = UGameInstance->ULocalPlayer(UGameInstancePtr);
		auto APlayerControllerPtr = ULocalPlayer->APlayerController(ULocalPlayerPtr);
	
		PlayerCameraManager = APlayerController->APlayerCameraManager(APlayerControllerPtr);
		PlayerController = APlayerControllerPtr;

		auto MyHUD = APlayerController->AHUD(APlayerControllerPtr);

		auto APawnPtr = APlayerController->APawn(APlayerControllerPtr);
		uintptr_t local_player_pawn = APlayerController->APawn(APlayerControllerPtr);
		g_local_player_pawn = local_player_pawn;
		g_local_player_controller = APlayerControllerPtr;
		gcameramanager = PlayerCameraManager;
		if (APawnPtr != 0)
		{
			MyUniqueID = APawn->UniqueID(APawnPtr);
			MyTeamID = APawn->TeamID(APawnPtr);
			MyRelativeLocation = APawn->RelativeLocation(APawnPtr);
		}

		if (MyHUD != 0)
		{
			auto PlayerArray = ULevel->AActorArray(ULevelPtr);
			uintptr_t actor_array = driver.readv<uintptr_t>(ULevelPtr + offsets::AActorArray);

			for (uint32_t i = 0; i < PlayerArray.Count; ++i)
			{
				auto Pawns = PlayerArray[i];
				if (Pawns != APawnPtr)
				{
					if (MyUniqueID == APawn->UniqueID(Pawns) && MyTeamID != APawn->TeamID(Pawns))
					{
						ValEntity Entities{ Pawns };
						CachedList.push_back(Entities);
					}
				}
			}

			ValList.clear();
			ValList = CachedList;
			Sleep(1000);
		}
	}
}

namespace colors
{
	float chamscol[3] = { 1.0f , 1.0f , 1.0f };
	float espcol[3] = { 1.0f , 1.0f , 1.0f };
	float skelcol[3] = { 1.0f , 1.0f , 1.0f };
	float crosscol[3] = { 1.0f , 10.0f , 0.0f };

	float orecol[3] = { 1.0f , 1.0f , 1.0f };
	float collcol[3] = { 1.0f , 1.0f , 1.0f };
	float cratecol[3] = { 1.0f , 1.0f , 1.0f };
	float scientistcol[3] = { 1.0f , 1.0f , 1.0f };
	float itemscol[3] = { 1.0f , 1.0f , 1.0f };
}

std::wstring s2ws(const std::string& str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

long mod(long a, long b)
{
	return (a % b + b) % b;
}





std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}

std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}
void DrawString(float fontSize, int x, int y, RGBA* color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 2;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), text.c_str());
}

auto isVisible(DWORD_PTR mesh) -> bool
{
	float fLastSubmitTime = driver.readv<float>(mesh + 0x378);
	float fLastRenderTimeOnScreen = driver.readv<float>(mesh + 0x37C);

	const float fVisionTick = 0.06f;
	bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;

	return bVisible;
}
inline void renderBoneLine(FVector first_bone_position, FVector second_bone_position) {
	FVector first_bone_screen_position = UE4::SDK::ProjectWorldToScreen(first_bone_position);
	ImVec2 fist_screen_position = ImVec2(first_bone_screen_position.x, first_bone_screen_position.y);
	FVector second_bone_screen_position = UE4::SDK::ProjectWorldToScreen(second_bone_position);
	ImVec2 second_screen_position = ImVec2(second_bone_screen_position.x, second_bone_screen_position.y);
	ImGui::GetForegroundDrawList()->AddLine(fist_screen_position, second_screen_position, g_color_white);
}


void bhop() {

	INPUT space = { 0 };
	space.ki.wVk = VK_SPACE;

	space.type = INPUT_KEYBOARD;
	SendInput(1, &space, sizeof(INPUT)); // Send KeyDown

	Sleep(rand() % 5 + 1);

	space.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &space, sizeof(INPUT)); // Send KeyUp

}

void renderBones(int boneCount, uintptr_t enemy) 
{
	FVector head_position = UE4::SDK::GetEntityBone(enemy, 8);
	FVector neck_position;
	FVector chest_position = UE4::SDK::GetEntityBone(enemy, 6);
	FVector l_upper_arm_position;
	FVector l_fore_arm_position;
	FVector l_hand_position;
	FVector r_upper_arm_position;
	FVector r_fore_arm_position;
	FVector r_hand_position;
	FVector stomach_position = UE4::SDK::GetEntityBone(enemy, 4);
	FVector pelvis_position = UE4::SDK::GetEntityBone(enemy, 3);
	FVector l_thigh_position;
	FVector l_knee_position;
	FVector l_foot_position;
	FVector r_thigh_position;
	FVector r_knee_position;
	FVector r_foot_position;

	if (boneCount == 103) { // BOT
		neck_position = UE4::SDK::GetEntityBone(enemy, 9);

		l_upper_arm_position = UE4::SDK::GetEntityBone(enemy, 33);
		l_fore_arm_position = UE4::SDK::GetEntityBone(enemy, 30);
		l_hand_position = UE4::SDK::GetEntityBone(enemy, 32);

		r_upper_arm_position = UE4::SDK::GetEntityBone(enemy, 58);
		r_fore_arm_position = UE4::SDK::GetEntityBone(enemy, 55);
		r_hand_position = UE4::SDK::GetEntityBone(enemy, 57);

		l_thigh_position = UE4::SDK::GetEntityBone(enemy, 63);
		l_knee_position = UE4::SDK::GetEntityBone(enemy, 65);
		l_foot_position = UE4::SDK::GetEntityBone(enemy, 69);

		r_thigh_position = UE4::SDK::GetEntityBone(enemy, 77);
		r_knee_position = UE4::SDK::GetEntityBone(enemy, 79);
		r_foot_position = UE4::SDK::GetEntityBone(enemy, 83);

	}
	else if (boneCount == 104) {//MALE

		neck_position = UE4::SDK::GetEntityBone(enemy, 21);

		l_upper_arm_position = UE4::SDK::GetEntityBone(enemy, 23);
		l_fore_arm_position = UE4::SDK::GetEntityBone(enemy, 24);
		l_hand_position = UE4::SDK::GetEntityBone(enemy, 25);

		r_upper_arm_position = UE4::SDK::GetEntityBone(enemy, 49);
		r_fore_arm_position = UE4::SDK::GetEntityBone(enemy, 50);
		r_hand_position = UE4::SDK::GetEntityBone(enemy, 51);

		l_thigh_position = UE4::SDK::GetEntityBone(enemy, 77);
		l_knee_position = UE4::SDK::GetEntityBone(enemy, 78);
		l_foot_position = UE4::SDK::GetEntityBone(enemy, 80);

		r_thigh_position = UE4::SDK::GetEntityBone(enemy, 84);
		r_knee_position = UE4::SDK::GetEntityBone(enemy, 85);
		r_foot_position = UE4::SDK::GetEntityBone(enemy, 87);


	}
	else if (boneCount == 101) {//FEMALE

		neck_position = UE4::SDK::GetEntityBone(enemy, 21);

		l_upper_arm_position = UE4::SDK::GetEntityBone(enemy, 23);
		l_fore_arm_position = UE4::SDK::GetEntityBone(enemy, 24);
		l_hand_position = UE4::SDK::GetEntityBone(enemy, 25);

		r_upper_arm_position = UE4::SDK::GetEntityBone(enemy, 49);
		r_fore_arm_position = UE4::SDK::GetEntityBone(enemy, 50);
		r_hand_position = UE4::SDK::GetEntityBone(enemy, 51);

		l_thigh_position = UE4::SDK::GetEntityBone(enemy, 75);
		l_knee_position = UE4::SDK::GetEntityBone(enemy, 76);
		l_foot_position = UE4::SDK::GetEntityBone(enemy, 78);

		r_thigh_position = UE4::SDK::GetEntityBone(enemy, 82);
		r_knee_position = UE4::SDK::GetEntityBone(enemy, 83);
		r_foot_position = UE4::SDK::GetEntityBone(enemy, 85);
	}
	else {
		return;
	}

	renderBoneLine(head_position, neck_position);
	renderBoneLine(neck_position, chest_position);
	renderBoneLine(neck_position, l_upper_arm_position);
	renderBoneLine(l_upper_arm_position, l_fore_arm_position);
	renderBoneLine(l_fore_arm_position, l_hand_position);
	renderBoneLine(neck_position, r_upper_arm_position);
	renderBoneLine(r_upper_arm_position, r_fore_arm_position);
	renderBoneLine(r_fore_arm_position, r_hand_position);
	renderBoneLine(chest_position, stomach_position);
	renderBoneLine(stomach_position, pelvis_position);
	renderBoneLine(pelvis_position, l_thigh_position);
	renderBoneLine(l_thigh_position, l_knee_position);
	renderBoneLine(l_knee_position, l_foot_position);
	renderBoneLine(pelvis_position, r_thigh_position);
	renderBoneLine(r_thigh_position, r_knee_position);
	renderBoneLine(r_knee_position, r_foot_position);
}

FVector SmoothAngles(FVector rot1, FVector rot2, float smooth)
{
	FVector ret(0, 0, 0);

	ret.x = (rot2.x - rot1.x) / smooth + rot1.x;
	ret.y = (rot2.y - rot1.y) / smooth + rot1.y;
	ret.z = (rot2.z - rot1.z) / smooth + rot1.z;

	return ret;
}


void Aimbotty(FVector Target, FVector Camera_rotation, float SmoothFactor)
{
	FVector ConvertRotation = Camera_rotation;

	auto ControlRotation = driver.readv<FVector>(PlayerController + 0x440);
	FVector DeltaRotation = ConvertRotation - ControlRotation;

	ConvertRotation = Target - (DeltaRotation * SmoothFactor);

	FVector Smoothed = SmoothAngles(Camera_rotation, ConvertRotation, SmoothFactor);
	
	driver.write<FVector>(PlayerController + 0x440, Smoothed);

}


auto CallAimbot(uintptr_t entity) -> void
{

	auto Head = UE4::SDK::GetEntityBone(entity, 8);
	auto neck = UE4::SDK::GetEntityBone(entity, 7);
	auto body = UE4::SDK::GetEntityBone(entity, 5);

	if (Settings::aimbot::selectedhitbox == 2)
	{
		AimAtVector(body, CameraLocation);
	}
	FVector angles_out = AimAtVector(neck, CameraLocation);

#include "cheat.hpp"

	if (Settings::aimbot::selectedhitbox == 0)
	{
		 angles_out = AimAtVector(Head, CameraLocation);
	}
	else if (Settings::aimbot::selectedhitbox == 1)
	{
		 angles_out = AimAtVector(neck, CameraLocation);
	}
	else if (Settings::aimbot::selectedhitbox == 2)
	{
		 angles_out = AimAtVector(body, CameraLocation);
	}

	if (Settings::aimbot::smooth)
	{
		Aimbotty(angles_out, CameraRotation, Settings::aimbot::smoothness);
	}
	else driver.write<FVector>(PlayerController + 0x440, angles_out);


}

static std::string utf8_encode(const std::wstring& wstr)
{
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}
void drawRecoil() {
	float screen_width = GetSystemMetrics(SM_CXSCREEN);
	float screen_height = GetSystemMetrics(SM_CYSCREEN);

	FVector punchAngle = (CameraRotation - CameraRotation).Normalize();

	float centerX = screen_width / 2; // may need to add or subtract to make perfect
	float centerY = screen_height / 2;

	int dx = screen_width / 90;
	int dy = screen_height / 90;

	centerX += (dx * (punchAngle.y));
	centerY -= (dy * (punchAngle.x));

	ImColor White = { 255, 255, 255, 255 };
	auto draw = ImGui::GetForegroundDrawList();
	draw->AddCircle({ centerX, centerY }, 5, White, 0, 2);
}

void DrawCrossNazi(int buyukluk, DWORD color)
{
	float screen_width = GetSystemMetrics(SM_CXSCREEN);
	float screen_height = GetSystemMetrics(SM_CYSCREEN);
	//ImVec2 window_pos = ImGui::GetWindowPos();
	ImVec2 window_size = ImGui::GetWindowSize();
	int crosspozisyon = screen_width/2;
	int crosspozisyony = screen_height/2;
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(crosspozisyon, crosspozisyony - buyukluk), ImVec2(crosspozisyon, crosspozisyony + buyukluk), ImColor(color));
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(crosspozisyon - buyukluk, crosspozisyony), ImVec2(crosspozisyon + buyukluk, crosspozisyony), ImColor(color));
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(crosspozisyon, crosspozisyony + buyukluk), ImVec2(crosspozisyon - buyukluk, crosspozisyony + buyukluk), ImColor(color));
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(crosspozisyon, crosspozisyony - buyukluk), ImVec2(crosspozisyon + buyukluk, crosspozisyony - buyukluk), ImColor(color));
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(crosspozisyon - buyukluk, crosspozisyony), ImVec2(crosspozisyon - buyukluk, crosspozisyony - buyukluk), ImColor(color));
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(crosspozisyon + buyukluk, crosspozisyony), ImVec2(crosspozisyon + buyukluk, crosspozisyony + buyukluk), ImColor(color));
}

inline auto DrawLineNew(int x1, int y1, int x2, int y2, RGBA* color, int thickness) -> void
{
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}
inline auto DrawCircleFilled2(int x, int y, int radius, RGBA* color) -> void
{
	ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
}

void DrawCrossNazi1(int buyukluk, DWORD color)
{
	ImVec2 window_pos = ImGui::GetWindowPos();
	ImVec2 window_size = ImGui::GetWindowSize();
	int crosspozisyon = window_pos.x + window_size.x * 0.5f;
	int crosspozisyony = window_pos.y + window_size.y * 0.5f;
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(crosspozisyon, crosspozisyony - buyukluk), ImVec2(crosspozisyon, crosspozisyony + buyukluk), ImColor(color));
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(crosspozisyon - buyukluk, crosspozisyony), ImVec2(crosspozisyon + buyukluk, crosspozisyony), ImColor(color));
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(crosspozisyon, crosspozisyony + buyukluk), ImVec2(crosspozisyon - buyukluk, crosspozisyony + buyukluk), ImColor(color));
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(crosspozisyon, crosspozisyony - buyukluk), ImVec2(crosspozisyon + buyukluk, crosspozisyony - buyukluk), ImColor(color));
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(crosspozisyon - buyukluk, crosspozisyony), ImVec2(crosspozisyon - buyukluk, crosspozisyony - buyukluk), ImColor(color));
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(crosspozisyon + buyukluk, crosspozisyony), ImVec2(crosspozisyon + buyukluk, crosspozisyony + buyukluk), ImColor(color));
}


auto CheatLoop() -> void
{
	float closestDistance = FLT_MAX;
	uintptr_t closestPawn = NULL;

	if (Settings::aimbot::drawfov)
	{
		DWORD ScreenCenterX = GetSystemMetrics(SM_CXSCREEN);
		DWORD ScreenCenterY = GetSystemMetrics(SM_CYSCREEN);
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(ScreenCenterX / 2, ScreenCenterY / 2), Settings::aimbot::fov, (ImU32)&Col.white, 10000);
	}
	if (Settings::aimbot::filledfov)
	{
		 DWORD ScreenCenterX = GetSystemMetrics(SM_CXSCREEN);
		DWORD ScreenCenterY = GetSystemMetrics(SM_CYSCREEN);
		ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(ScreenCenterX/2, ScreenCenterY/2), Settings::aimbot::fov, (ImU32) & Col.filled, 10000);
	}
	
	if (Settings::aimbot::nazicrosshair)
	{
		ImColor Red = { 255, 0, 0, 255 };
		DrawCrossNazi(10, Red);
	}
	if (Settings::Misc::water)
	{
		static ULONG w = GetSystemMetrics(SM_CXSCREEN);
		static ULONG h = GetSystemMetrics(SM_CYSCREEN);
		ImGui::PushFont(Proggy);
		ImColor Red = { 255, 255, 255, 255 };
		std::string Watermark = "Private";
		ImGui::GetForegroundDrawList()->AddText(ImVec2(Width / 2 - 45, Height / 2 - 400), Red, Watermark.c_str());

	}
	if (Settings::Visuals::drawRecoil)
	{
		drawRecoil();
	}
	for (ValEntity ValEntityList : ValList)
	{
		auto SkeletalMesh = APrivatePawn->USkeletalMeshComponent(ValEntityList.Actor);
		auto RelativeLocation = APawn->RelativeLocation(ValEntityList.Actor);
		auto RelativeLocationProjected = UE4::SDK::ProjectWorldToScreen(RelativeLocation);
		auto RelativePosition = RelativeLocation - CameraLocation;
		auto RelativeDistance = RelativePosition.Length() / 10000 * 2;
		auto HeadBone = UE4::SDK::GetEntityBone(SkeletalMesh, 8);
		auto HeadBoneProjected = UE4::SDK::ProjectWorldToScreen(HeadBone);

		auto vHeadBoneOut2 = UE4::SDK::ProjectWorldToScreen(FVector(HeadBone.x, HeadBone.y, HeadBone.z + 15));
		auto RootBone = UE4::SDK::GetEntityBone(SkeletalMesh, 0);
		auto RootBoneProjected = UE4::SDK::ProjectWorldToScreen(RootBone);
		auto RootBoneProjected2 = UE4::SDK::ProjectWorldToScreen(FVector(RootBone.x, RootBone.y, RootBone.z - 15));
		
		boted_vex_screen = ImVec2(HeadBoneProjected.x, HeadBoneProjected.y);
		
		auto Distance = MyRelativeLocation.Distance(RelativeLocation);
		float BoxHeight = abs(HeadBoneProjected.y - RootBoneProjected.y);
		float BoxWidth = BoxHeight * 0.40;
		auto Inventory = driver.readv<intptr_t>(ValEntityList.Actor + 0x948);
		intptr_t CurrentEquip = driver.readv<intptr_t>(Inventory + 0x238);
		int weaponObj = driver.readv<int>(CurrentEquip + 0x18);
		auto ee = ImColor(255, 255, 255);
		auto PlayerState = driver.readv<uintptr_t>(ValEntityList.Actor + offsets::PlayerState);
		auto Health = APawn->Health(ValEntityList.Actor);
		auto IsVisible = isVisible(APrivatePawn->USkeletalMeshComponent(ValEntityList.Actor));
		ImColor ez; if (IsVisible) { ez = ImColor(0, 255, 0); }
		else { ez = ImColor(255, 0, 0); }
		ImColor ez2; if (APawn->bIsDormant(ValEntityList.Actor)) { ez2 = ImColor(0, 255, 0); }
		else { ez2 = ImColor(255, 0, 0); }
		if (Health <= 0) continue;
		if (APawn->bIsDormant(ValEntityList.Actor) || BoneCount == 103)
		{
			if (Settings::Visuals::dormant) {
				auto SkeletalMesh = APrivatePawn->USkeletalMeshComponent(ValEntityList.Actor);

				float last_render_time = driver.readv<float>(SkeletalMesh + 0x378);
				float last_submit_time = driver.readv<float>(SkeletalMesh + 0x37C);
				bool is_visible = last_render_time + 0.06F >= last_submit_time;
				bool dormant = driver.readv<bool>(ValEntityList.Actor + offsets::bIsDormant);
				if (!dormant || !is_visible) {
					char Text[64];
					sprintf_s(Text, "Dormant");
					std::string Out1337777 = Text;
					ImVec2 TextSize = ImGui::CalcTextSize(Out1337777.c_str());
					ImGui::GetForegroundDrawList()->AddText(ImVec2(RootBoneProjected2.x - TextSize.x / 2, RootBoneProjected2.y + 5 - TextSize.y / 2), ez2, Out1337777.c_str());
					continue;
				}
				else {
					char Text[64];
					sprintf_s(Text, "Moving");
					std::string Out1337777 = Text;
					ImVec2 TextSize = ImGui::CalcTextSize(Out1337777.c_str());
					//ImGui::GetForegroundDrawList()->AddText(ImVec2(RootBoneProjected2.x - 15, RootBoneProjected2.y - 15), ez2, Out1337777.c_str());
					ImGui::GetForegroundDrawList()->AddText(ImVec2(RootBoneProjected2.x - TextSize.x / 2, RootBoneProjected2.y + 5 - TextSize.y / 2), ez2, Out1337777.c_str());

				}
			}
			if (Settings::Visuals::visibleesp)
			{
				if (IsVisible)
				{
					char Text[64];
					sprintf_s(Text, "Visible");
					std::string Out133777 = Text;
					ImVec2 TextSize = ImGui::CalcTextSize(Out133777.c_str());


					ImGui::GetForegroundDrawList()->AddText(ImVec2(HeadBoneProjected.x - 15, HeadBoneProjected.y - 15), ez, Out133777.c_str());

				}
				else
				{
					char Text[64];
					sprintf_s(Text, "Behind Wall");
					std::string Out1337777 = Text;
					ImVec2 TextSize = ImGui::CalcTextSize(Out1337777.c_str());


					ImGui::GetForegroundDrawList()->AddText(ImVec2(HeadBoneProjected.x - 15, HeadBoneProjected.y - 15), ez, Out1337777.c_str());
				}
			}

			if (Settings::Visuals::snapline)
			{


				if (Settings::Visuals::snaplinepos == 0)
				{
					DrawLine(ImVec2(Width / 2, Height - 1075), ImVec2(vHeadBoneOut2.x, vHeadBoneOut2.y - 30), ee, 0.5f);
				}

				else if (Settings::Visuals::snaplinepos == 1)
				{
					DrawLine(ImVec2(Width / 2, Height - 400), ImVec2(HeadBoneProjected.x, HeadBoneProjected.y-10), ee, 0.5f);
				}

				else if (Settings::Visuals::snaplinepos == 2)
				{
					DrawLine(ImVec2(Width / 2, Height), ImVec2(RootBoneProjected.x, RootBoneProjected.y), ee, 0.5f);
				}
			}
			if (Settings::Visuals::health)
			{

				int G1 = (255 * Health / 100);
				int R1 = 255 - G1;
				ImColor healthcol = { R1, G1, 0, 255 };
				std::string Out69 = "[H: " + std::to_string(static_cast<int32_t>(Health)) + "]";
				ImVec2 TextSize = ImGui::CalcTextSize(Out69.c_str());
				//ImGui::GetOverlayDrawList()->AddText(ImVec2(vBaseBoneOut2.x - TextSize.x / 2, vBaseBoneOut2.y + 5 - TextSize.y / 2), healthcol, Out69.c_str());

				if (Settings::Visuals::healthtype == 0)
				{
					ImGui::GetForegroundDrawList()->AddText(ImVec2(RootBoneProjected2.x - TextSize.x / 2, RootBoneProjected2.y + 5 - TextSize.y / 2), healthcol, Out69.c_str());
				}

				else if (Settings::Visuals::healthtype == 1)
				{
					DrawRightProgressBar(RootBoneProjected.x + 30, HeadBoneProjected.y, BoxWidth, BoxHeight, 2, Health);
				}

				else if (Settings::Visuals::healthtype == 2)

				{
					DrawRightProgressBar(RootBoneProjected.x + 30, HeadBoneProjected.y, BoxWidth, BoxHeight, 2, Health);
					ImGui::GetForegroundDrawList()->AddText(ImVec2(RootBoneProjected2.x - TextSize.x / 2, RootBoneProjected2.y + 5 - TextSize.y / 2), healthcol, Out69.c_str());
				}
			}
			if (Settings::Visuals::bDistance)
				DrawDistance(RootBoneProjected2, Distance);
			if (Settings::Visuals::box)
			{
				RGBA ESPColor = { colors::espcol[0] * 255, colors::espcol[1] * 255, colors::espcol[2] * 255, 255 };

				float BoxHeight = abs(HeadBoneProjected.y - RootBoneProjected.y);
				float BoxWidth = BoxHeight / 3.0f;
				if (Settings::boxMode == 0) {
					!Settings::Visuals::box;   //off
				}
				if (Settings::boxMode == 1)   //2d box
				{
					DrawNormalBox(RootBoneProjected.x - BoxWidth / 2 + 1, HeadBoneProjected.y, BoxWidth, BoxHeight, 1, &Col.black);
					DrawNormalBox(RootBoneProjected.x - BoxWidth / 2 - 1, HeadBoneProjected.y, BoxWidth, BoxHeight, 1, &Col.black);
					DrawNormalBox(RootBoneProjected.x - BoxWidth / 2, HeadBoneProjected.y + 1, BoxWidth, BoxHeight, 1, &Col.black);
					DrawNormalBox(RootBoneProjected.x - BoxWidth / 2, HeadBoneProjected.y - 1, BoxWidth, BoxHeight, 1, &Col.black);
					DrawNormalBox(RootBoneProjected.x - (BoxWidth / 2), HeadBoneProjected.y, BoxWidth, BoxHeight, 1, &ESPColor);
				}
				if (Settings::boxMode == 2)   // corner box
				{
					DrawCornerBox(RootBoneProjected.x - BoxWidth / 2 + 1, HeadBoneProjected.y, BoxWidth, BoxHeight, 1, &Col.black);
					DrawCornerBox(RootBoneProjected.x - BoxWidth / 2 - 1, HeadBoneProjected.y, BoxWidth, BoxHeight, 1, &Col.black);
					DrawCornerBox(RootBoneProjected.x - BoxWidth / 2, HeadBoneProjected.y + 1, BoxWidth, BoxHeight, 1, &Col.black);
					DrawCornerBox(RootBoneProjected.x - BoxWidth / 2, HeadBoneProjected.y - 1, BoxWidth, BoxHeight, 1, &Col.black);
					DrawCornerBox(RootBoneProjected.x - (BoxWidth / 2), HeadBoneProjected.y, BoxWidth, BoxHeight, 1, &ESPColor);
				}
				if (Settings::boxMode == 3)

				{

					DrawFilledRect(RootBoneProjected.x - (BoxWidth / 2), HeadBoneProjected.y, BoxWidth, BoxHeight, &Col.filled);
					DrawNormalBox(RootBoneProjected.x - BoxWidth / 2 + 1, HeadBoneProjected.y, BoxWidth, BoxHeight, 1, &Col.black);
					DrawNormalBox(RootBoneProjected.x - BoxWidth / 2 - 1, HeadBoneProjected.y, BoxWidth, BoxHeight, 1, &Col.black);
					DrawNormalBox(RootBoneProjected.x - BoxWidth / 2, HeadBoneProjected.y + 1, BoxWidth, BoxHeight, 1, &Col.black);
					DrawNormalBox(RootBoneProjected.x - BoxWidth / 2, HeadBoneProjected.y - 1, BoxWidth, BoxHeight, 1, &Col.black);
					DrawNormalBox(RootBoneProjected.x - (BoxWidth / 2), HeadBoneProjected.y, BoxWidth, BoxHeight, 1, &ESPColor);
				
				}

			}
			
			if (Settings::Visuals::infobar) {

				char dist[64];
				std::string Out = "[ " + std::to_string(static_cast<int32_t>(Distance)) + " meters ]";
				ImVec2 TextSize = ImGui::CalcTextSize(Out.c_str());

				std::string healthValue = (std::to_string((int)Health) + " Health").c_str();
				ImVec2 HealthTextSize = ImGui::CalcTextSize(healthValue.c_str());

				ImGui::PushFont(Proggy);
				ImGui::GetForegroundDrawList()->AddText(ImVec2(vHeadBoneOut2.x - HealthTextSize.x / 2, (vHeadBoneOut2.y - 5) - HealthTextSize.y / 2), ImGui::GetColorU32({ 255, 255, 255, 255 }), healthValue.c_str()); //TOPBOX
				ImGui::GetForegroundDrawList()->AddText(ImVec2(vHeadBoneOut2.x - HealthTextSize.x / 2, (vHeadBoneOut2.y - 20) - HealthTextSize.y / 2), ImGui::GetColorU32({ 255, 255, 255, 255 }), Out.c_str()); //BOTTOMBOX
				ImGui::PopFont();
			}
			if (Settings::Visuals::headcircle)
			{
				if (Settings::Visuals::headboxtype == 0)
				{
					ImGui::GetForegroundDrawList()->AddCircle(ImVec2(RootBoneProjected.x, HeadBoneProjected.y), BoxHeight / 10, (ImU32)&Col.white, 100);
				}

				else if (Settings::Visuals::headboxtype == 1)
				{
					ImGui::GetForegroundDrawList()->AddCircle(ImVec2(RootBoneProjected.x, HeadBoneProjected.y), BoxHeight / 10, (ImU32)&Col.white, 100);
					ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(RootBoneProjected.x, HeadBoneProjected.y), BoxHeight / 10, (ImU32)&Col.filled, 100);
				}

				else if (Settings::Visuals::headboxtype == 2)

				{
					ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(RootBoneProjected.x, HeadBoneProjected.y), BoxHeight / 20, (ImU32)&Col.white, 100);
					ImGui::GetForegroundDrawList()->AddCircle(ImVec2(RootBoneProjected.x, HeadBoneProjected.y), BoxHeight / 20, (ImU32)&Col.white, 100);
				}

				//DrawCircle(vBaseBoneOut.x, vHeadBoneOut.y, BoxHeight / 10, &Col.white, 100);
			}
			if (Settings::Visuals::glow) {
				driver.write<float>(ValEntityList.Actor + 0x6b8, 100000);
				driver.write<float>(ValEntityList.Actor + 0x6c0, 100000);
				driver.write<float>(ValEntityList.Actor + 0x6b4, 100000);

			}
			if (Settings::Visuals::skeleton)
			{
				auto SkeletalMesh = APrivatePawn->USkeletalMeshComponent(ValEntityList.Actor);
				int count = driver.read<uintptr_t>(SkeletalMesh + offsets::BoneCount);
				renderBones(count, APrivatePawn->USkeletalMeshComponent(ValEntityList.Actor));
			}

			if (MyUniqueID == APawn->UniqueID(ValEntityList.Actor) && MyTeamID != APawn->TeamID(ValEntityList.Actor))
			{
				if (Settings::Visuals::outlines) {
					auto outline_3p1 = driver.readv<uintptr_t>(ValEntityList.Actor + 0x10b8);
					driver.write<int>(outline_3p1 + 0x2B1, 1);
				}
				if (Settings::Visuals::glowingChams) 
				{
					driver.write<FLinearColor>(base + 0x919D470, { 2.093f, 0.019f, 20.0f, 5.9f });
					driver.write<FLinearColor>(base + 0x919DB00, { 2.093f, 0.019f, 20.0f, 5.9f });
				}//2.093f, 0.019f, 20.0f, 5.9f
			}
					
			if (Settings::Visuals::crouch) {

				driver.write<float>(g_local_player_pawn + 0xd58, 0);

			}
			if (Settings::Misc::FOVChanger) {

				FMinimalViewInfo camera = driver.readv<FMinimalViewInfo>(PlayerCameraManager + 0x510 + 0x10);
				FVector camera_location = camera.Location;
				driver.write<float>(PlayerCameraManager + 0x3f4, Settings::Misc::fov);
			}
			static ULONG w = GetSystemMetrics(SM_CXSCREEN);
			static ULONG h = GetSystemMetrics(SM_CYSCREEN);
			auto dx = HeadBoneProjected.x - (w / 2);
			auto dy = HeadBoneProjected.y - (h / 2);
			auto dist = sqrtf(dx * dx + dy * dy);
			if (dist < Settings::aimbot::fov && dist < closestDistance)
			{
				if (Settings::aimbot::vischeck)
				{
					if (IsVisible)
					{
						closestDistance = dist;
						closestPawn = ValEntityList.Actor;
					}
				}
				else
				{
					closestDistance = dist;
					closestPawn = ValEntityList.Actor;
				}
			}



			

		}
	}
			if (Settings::aimbot::aimbot)
			{
				if (closestPawn && GetAsyncKeyState(hotkeys::aimkey) < 0)
				{
					auto ez = APrivatePawn->USkeletalMeshComponent(closestPawn);
					CallAimbot(ez);
				}
			}
}
