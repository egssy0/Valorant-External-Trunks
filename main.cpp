#include "CompPkgSup.h"

#pragma once

#include <Windows.h>
#include <iostream>
#include <thread>
#include <string>
#include <filesystem>

#include "overlay/render.hpp"
#include "overlay/menu.hpp"
#include "auth.hpp"
#include "game/cheat.hpp"
#include <TlHelp32.h>
#include <string>
#include "includes.h"
#include "driver/driver.hpp"
#include "../kdmapper/kdmapper.hpp"
#include "xorstr.h"
#include "xor.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include "mapdriver.h"

#include "psapi.h"
#include "./Overlay/menu.hpp"
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);



std::string name = _xor_("TrunksPrivate"); // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = _xor_("92cAcc8qwB"); // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = _xor_("398c1e4bea9ea2fd47889d5c9d698016b83570c73bc774c96efe329000e9d2ad"); // app secret, the blurred text on licenses tab and other tabs
std::string version = _xor_("1.0"); // leave alone unless you've changed version on website
std::string url = _xor_("https://keyauth.win/api/1.2/"); // change if you're self-hosting
std::string sslPin = _xor_("ssl pin key (optional)"); // don't change unless you intend to pin public certificate key. you can get here in the "Pin SHA256" field https://www.ssllabs.com/ssltest/analyze.html?d=keyauth.win&latest. If you do this you need to be aware of when SSL key expires so you can update it
using namespace KeyAuth;
api KeyAuthApp(name, ownerid, secret, version, url);

namespace Utilities
{
	inline bool ReadFileToMemory(const std::string& file_path, std::vector<uint8_t>* out_buffer);
	inline bool CreateFileFromMemory(const std::string& desired_file_path, const char* address, size_t size);
}

inline bool Utilities::ReadFileToMemory(const std::string& file_path, std::vector<uint8_t>* out_buffer)
{
	std::ifstream file_ifstream(file_path, std::ios::binary);

	if (!file_ifstream)
		return false;

	out_buffer->assign((std::istreambuf_iterator<char>(file_ifstream)), std::istreambuf_iterator<char>());
	file_ifstream.close();

	return true;
}

inline bool Utilities::CreateFileFromMemory(const std::string& desired_file_path, const char* address, size_t size)
{
	std::ofstream file_ofstream(desired_file_path, std::ios_base::out | std::ios_base::binary);

	if (!file_ofstream.write(address, size))
	{
		file_ofstream.close();
		return false;
	}
	file_ofstream.close();
	return true;
}

DWORD GetProcessID(const std::wstring processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}
auto getprocessid(std::wstring processname) -> uintptr_t
{
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32W entry;
	entry.dwSize = sizeof(entry);
	if (!Process32First(snapshot, &entry)) {
		return 0;
	}
	while (Process32Next(snapshot, &entry)) {
		if (std::wstring(entry.szExeFile) == processname) {
			return entry.th32ProcessID;
		}
	}
	return 0;
}
HANDLE iqvw64e_device_handle;
LONG WINAPI SimplestCrashHandler(EXCEPTION_POINTERS* ExceptionInfo)
{
	if (ExceptionInfo && ExceptionInfo->ExceptionRecord)
		Log(L"[!!] Crash at addr 0x" << ExceptionInfo->ExceptionRecord->ExceptionAddress << L" by 0x" << std::hex << ExceptionInfo->ExceptionRecord->ExceptionCode << std::endl);
	else
		Log(L"[!!] Crash" << std::endl);

	if (iqvw64e_device_handle)
		intel_driver::Unload(iqvw64e_device_handle);

	return EXCEPTION_EXECUTE_HANDLER;
}
int paramExists(const int argc, wchar_t** argv, const wchar_t* param) {
	size_t plen = wcslen(param);
	for (int i = 1; i < argc; i++) {
		if (wcslen(argv[i]) == plen + 1ull && _wcsicmp(&argv[i][1], param) == 0 && argv[i][0] == '/') { // with slash
			return i;
		}
		else if (wcslen(argv[i]) == plen + 2ull && _wcsicmp(&argv[i][2], param) == 0 && argv[i][0] == '-' && argv[i][1] == '-') { // with double dash
			return i;
		}
	}
	return -1;
}
bool callbackExample(ULONG64* param1, ULONG64* param2, ULONG64 allocationPtr, ULONG64 allocationSize, ULONG64 mdlptr) {
	UNREFERENCED_PARAMETER(param1);
	UNREFERENCED_PARAMETER(param2);
	UNREFERENCED_PARAMETER(allocationPtr);
	UNREFERENCED_PARAMETER(allocationSize);
	UNREFERENCED_PARAMETER(mdlptr);
	Log("[+] Callback example called" << std::endl);
	return true;
}

bool startDriver() 
{
	BlockInput(true);
	printf(skCrypt("[+] Creating driver from memory\n"));
	SetUnhandledExceptionFilter(SimplestCrashHandler);
	auto DrvPath = "C:\\Windows\\SysWOW64\\win34.sys";

	Utilities::CreateFileFromMemory(DrvPath, reinterpret_cast<const char*>(binary), sizeof(binary));
	auto driver_path = _xor_(L"C:\\Windows\\SysWOW64\\win34.sys").c_str();


	printf(skCrypt("[+] Wait\n"));
	

	if (!std::filesystem::exists(driver_path)) {
		printf(skCrypt("[+]File does not exist\n"));
		return false;
	}

	iqvw64e_device_handle = intel_driver::Load();

	if (iqvw64e_device_handle == INVALID_HANDLE_VALUE)
		return false;

	std::vector<uint8_t> raw_image = { 0 };
	if (!utils::ReadFileToMemory(driver_path, &raw_image)) {
		Log(L"[-] Failed to read image to memory" << std::endl);
		intel_driver::Unload(iqvw64e_device_handle);
		return false;
	}

	NTSTATUS exitCode = 0;
	if (!kdmapper::MapDriver(iqvw64e_device_handle, raw_image.data())) {
		Log(L"[-] Failed to map " << driver_path << std::endl);
		intel_driver::Unload(iqvw64e_device_handle);
		return false;
	}

	if (!intel_driver::Unload(iqvw64e_device_handle)) {
		Log(L"[-] Warning failed to fully unload vulnerable driver " << std::endl);
	}
	BlockInput(false);
}
void suspend(DWORD processId)
{
	HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

	THREADENTRY32 threadEntry;
	threadEntry.dwSize = sizeof(THREADENTRY32);

	Thread32First(hThreadSnapshot, &threadEntry);

	do
	{
		if (threadEntry.th32OwnerProcessID == processId)
		{
			HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE,
				threadEntry.th32ThreadID);

			SuspendThread(hThread);
			CloseHandle(hThread);
		}
	} while (Thread32Next(hThreadSnapshot, &threadEntry));

	CloseHandle(hThreadSnapshot);
}
DWORD FindProcessId(const std::wstring& processName)
{
	HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare((LPCWSTR)processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare((LPCWSTR)processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(hThreadSnapshot);
	return 0;
}

std::string gen_string(const int length)
{
	std::string GeneratedString;
	static const char Alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	srand((unsigned)time(NULL) * 5);
	for (int i = 0; i < length; i++)
		GeneratedString += Alphabet[rand() % (sizeof(Alphabet) - 1)];
	return GeneratedString;
}
// Gets base address of specified module in process from PID, if no module given, returns process base address (x86 & x64)
DWORD64 FindModuleBaseAddrInProcess(DWORD targetPID, std::wstring moduleToFind) {
	HANDLE snapshotModules = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, targetPID);
	if (snapshotModules == INVALID_HANDLE_VALUE)
		return NULL;

	MODULEENTRY32 me32;
	me32.dwSize = sizeof(MODULEENTRY32); // Set the size of the structure before using it.

	if (!Module32First(snapshotModules, &me32)) {
		CloseHandle(snapshotModules);
		return 0x0;
	}

	// For Case insensitive search
	std::wstring moduleToFindUp = moduleToFind;
	std::transform(moduleToFindUp.begin(), moduleToFindUp.end(), moduleToFindUp.begin(), ::towupper);

	DWORD64 baseAddr = NULL;
	do {
		if (moduleToFind == L"") { // No module specified, returning process base address
			baseAddr = (DWORD64)me32.modBaseAddr;
			break;
		}
		// For Case insensitive search
		std::wstring moduleName = me32.szModule;
		std::wstring moduleNameUp = moduleName;
		std::transform(moduleNameUp.begin(), moduleNameUp.end(), moduleNameUp.begin(), ::towupper);
		if (moduleNameUp == moduleToFindUp) {
			baseAddr = (DWORD64)me32.modBaseAddr;
			break;
		}
	} while (Module32Next(snapshotModules, &me32));

	CloseHandle(snapshotModules);
	return baseAddr;
}
std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}
void art() {
	printf(R"(

ooooooooooooo                                  oooo        o8o          
8'   888   `8                                  `888        `YP          
     888      oooo d8b oooo  oooo  ooo. .oo.    888  oooo   '   .oooo.o 
     888      `888""8P `888  `888  `888P"Y88b   888 .8P'       d88(  "8 
     888       888      888   888   888   888   888888.        `"Y88b.  
     888       888      888   888   888   888   888 `88b.      o.  )88b 
    o888o     d888b     `V88V"V8P' o888o o888o o888o o888o     8""888P' 
																	V5.
)"
);

}
void license() {
	art();
	SetConsoleTitleA(gen_string(25).c_str());

	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	int x = screen_rect.right / 2 - 150;
	int y = screen_rect.bottom / 3 - 75;

	//art();
	HWND hWnd = GetConsoleWindow();
	MoveWindow(hWnd, x, y, 900, 600, TRUE);
	system("color 05");
	// bullshit
	KeyAuthApp.init();
	std::cout << skCrypt("[+] Key: ");
	std::cin >> key;
	KeyAuthApp.license(key);

	KeyAuthApp.check();
	const std::wstring driver = _xor_(L"C:\\Windows\\SysWOW64\\win34.sys").c_str();

	if (KeyAuthApp.data.success) 
	{
		DeleteFileW(L"C:\\Windows\\SysWOW64\\trunks.sys");
		DeleteFileW(L"C:\\Windows\\SysWOW64\\win34.sys");
		printf(skCrypt("[+] Creating driver from memory\n"));
		Sleep(1000);
		printf(skCrypt("[+] Mapping into process!\n"));
		Sleep(1000);
		startDriver();
		DeleteFileW(L"C:\\Windows\\SysWOW64\\trunks.sys");
		DeleteFileW(L"C:\\Windows\\SysWOW64\\win34.sys");
		return;
	}
	else {
		std::cout << skCrypt("Error");
		Sleep(1000);
		exit(0);
	}

}



int main()
{
	
	SetConsoleTitleA(gen_string(25).c_str());
	license();
	
	
	system("cls");
	art();
	printf("[+] sucess");
	system("cls");
	art();
	Sleep(200);
		while (Entryhwnd == NULL)
		{
			printf(skCrypt("Waiting for Valorant\r"));
			Sleep(1);
			processid = GetProcessID(L"VALORANT-Win64-Shipping.exe");
			Entryhwnd = get_process_wnd(processid);

			Sleep(1);
		}
		DeleteFileW(L"C:\\Windows\\SysWOW64\\trunks.sys");
		DeleteFileW(L"C:\\Windows\\SysWOW64\\win34.sys");
		hwid = KeyAuthApp.data.hwid;
		ip = KeyAuthApp.data.ip;
		expiryDate = KeyAuthApp.data.expiry;

		ShowWindow(GetConsoleWindow(), SW_HIDE);

		driver.initdriver(processid);
		base = driver.getBase();

		setup_window();
		init_wndparams(MyWnd);

		std::thread(CacheGame).detach();	
		while (true) main_loop();

		exit(0);
}

auto render() -> void 
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	drawmenu();

	ImGui::EndFrame();
	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (p_Device->BeginScene() >= 0) 
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		p_Device->EndScene();
	}

	HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) 
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		p_Device->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

auto main_loop() -> WPARAM
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT) 
	{
		if (PeekMessage(&Message, MyWnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();
		if (GetAsyncKeyState(0x23) & 1)
			exit(8);

		if (hwnd_active == GameWnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(0x1)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom) {

			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			p_Params.BackBufferWidth = Width;
			p_Params.BackBufferHeight = Height;
			SetWindowPos(MyWnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}

		render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	cleanup_d3d();
	DestroyWindow(MyWnd);

	return Message.wParam;
}