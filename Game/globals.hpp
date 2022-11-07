#pragma once
#include <Windows.h>
inline ImFont* Proggy = nullptr;

HWND Entryhwnd = NULL;
int processid = 0;
char key[20];


uintptr_t base;

namespace offsets
{
    DWORD
        Gameinstance = 0x1a0,       // no change
        Ulevel = 0x38,              // no change
        LocalPlayers = 0x40,        // good
        PlayerController = 0x38,    // good
        PlayerCameraManager = 0x478,    //good
        MyHUD = 0x470,  //good
        AcknowledgedPawn = 0x460,       //good
        PlayerState = 0x3F0,//good
        TeamComponent = 0x628,//good
        TeamID = 0xf8,//good
        UniqueID = 0x38,//good
        FNameID = 0x18,
        AActorArray = 0xA0, // good
        RootComponent = 0x230,
        RelativeLocation = 0x164,
        MeshComponent = 0x430,
        DamageHandler = 0x9A8,
        bIsDormant = 0x100,
        Health = 0x1b0,
        ComponentToWorld = 0x250,
        BoneArray = 0x5C0,
        BoneArrayCache = BoneArray + 0x10,
        BoneCount = 0x5C8;
  // float   FresnelIntensity = 0x690;
   float   FresnelIntensity = 0x6b8;
   
}

namespace Settings
{
    inline bool bMenu = true;
    int boxMode = 0;

    namespace aimbot
    {
        inline bool aimbot = true;
        inline float fov = 150;
        inline float smoothness = 2.0f;
        inline bool smooth = false;
        inline bool drawfov = false;
        inline bool vischeck = false;
        inline bool filledfov = false;
        inline  int selectedhitbox = 0;
        inline  const char* hitbox[] = { ("Head") ,("Neck"), ("Body") };
        inline bool silent = false;
        inline bool rcs = false;
        inline bool rcscrosshair = false;
        inline bool nazicrosshair = false;
        inline bool rapidfire = false;

    }

    namespace Visuals
    {
        inline bool chams = false;
        inline bool drawRecoil = false;

        inline bool wallhack = false;
        inline bool infobar = false;
        inline bool hitsound = false;

        inline bool outlines = false;
        inline bool glowingChams = false;
        inline bool snapline = false;
        inline bool headcircle = false;
        inline bool skeleton = true;

        inline  int snaplinepos = 2;
        inline  const char* snappos[] = { ("Top") ,("Crosshair"), ("Bottom") };
        inline bool health = false;

        inline  int healthtype = 0;
        inline  const char* healtht[] = { ("Text") ,("Bar"), ("Both") };
        inline  int headboxtype = 0;
        inline  const char* headboxt[] = { ("Circle") ,("Filled Circle"), ("Dot") };
        inline bool visibleesp = false;


        inline bool bones = false;
        inline bool name = false;
        inline bool directional = false;
        inline bool box = true;
        inline bool showEsp = false;
        inline bool glow = false;
        inline bool dormant = false;

        inline bool bDistance = false;
        inline bool crouch = false;
        inline float BoxWidth = 1.0f;
    }
    
    namespace Misc {
        inline bool radar = false;
        inline float fov = 0.0f;
        inline float reset = 100.0f;

        inline bool Exploit = false;
        inline bool FOVChanger = false;
        inline bool BunnyHop = false;
        inline bool Strafe = false;
        inline bool water = true;

    }
}