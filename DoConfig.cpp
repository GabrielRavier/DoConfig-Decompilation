// DoConfig.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DoConfig.h"

/* This file has been generated by the Hex-Rays decompiler.
   Copyright (c) 2007-2015 Hex-Rays <info@hex-rays.com>

   Detected compiler: Visual C++
*/


//-------------------------------------------------------------------------
// Function declarations

int __cdecl openConfig(configDataFile *config);
BOOL __stdcall optionsDialogFunction(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
int __cdecl doFontThing(HWND hDlg);
void __cdecl enableGamepadButtons(HWND hDlg);
void __cdecl makeButtonModes(HWND hDlg, configDataFile *Config_file);
void __cdecl initDialog(HWND hDlg);
int __stdcall fontProcedure(const LOGFONTA *, const TEXTMETRICA *, DWORD, LPARAM);
void __cdecl makeDefaultJoystickButtons(configDataFile *Config_file);
void __cdecl commitChanges(HWND hDlg);
bool __cdecl saveChangesToConfig(configDataFile *Config);
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

//-------------------------------------------------------------------------
// Data declarations

const char *configFileCheck = "DOUKUTSU20041206"; // idb
const char *configFileName = "Config.dat";
const char *fontName = "Courier New";
int y = 16; // idb
int x = 335; // idb
RECT rcWindow = { 0, 0, 0, 0 }; // idb
int dword_40CBF0[6];
int arrowLayoutFlag = 0; // weak
HGDIOBJ images[2] = { nullptr, nullptr };
CHAR exePath[260] = { 0 };


//----- (00401000) --------------------------------------------------------
int __cdecl openConfig(configDataFile *Profile)
{
    char path[272]; // [sp+0h] [bp-118h]@1
    FILE *file; // [sp+114h] [bp-4h]@1

    memset(Profile, 0, sizeof(*Profile));
    sprintf(path, "%s\\%s", exePath, configFileName);
    file = fopen(path, "rb");
    if (file)
    {
        bool isReadSuccesful = fread(Profile, sizeof(*Profile), 1u, file);
        fclose(file);
        if (isReadSuccesful == true && !strcmp(Profile->proof, configFileCheck))
            return true;
        else
        {
            memset(Profile, 0, sizeof(*Profile));
            return true;
        }
    }
    else
        return false;
}

//----- (004010D0) --------------------------------------------------------
BOOL __stdcall optionsDialogFunction(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    configDataFile configFile; // [sp+8h] [bp-F0h]@21
    HDC v6; // [sp+A0h] [bp-58h]@6
    HDC v7; // [sp+A4h] [bp-54h]@6
    struct tagPAINTSTRUCT Paint; // [sp+A8h] [bp-50h]@6
    HGDIOBJ v9; // [sp+F0h] [bp-8h]@6
    HINSTANCE v10; // [sp+F4h] [bp-4h]@5

    if ( Message == WM_PAINT )
    {
        v6 = BeginPaint(hWnd, &Paint);
        v7 = CreateCompatibleDC(v6);
        v9 = SelectObject(v7, images[arrowLayoutFlag]);
        BitBlt(v6, x, y, dword_40CBF0[1], dword_40CBF0[2], v7, 0, 0, 0xCC0020u);
        SelectObject(v7, v9);
        DeleteDC(v7);
        EndPaint(hWnd, &Paint);
    }
    else
    {
        if ( Message != WM_INITDIALOG )
        {
            if ( Message == WM_COMMAND )
            {
                if ( (unsigned __int16)wParam > (signed int)Button_Use_Gamepad )
                {
                    if ( (unsigned __int16)wParam != Button_Restore_Defaults )
                    {
                        if ( (unsigned __int16)wParam == Button_Arrows_Button_Layout )
                        {
                            arrowLayoutFlag = 0;
                            InvalidateRect(hWnd, &rcWindow, 0);
                        }
                        else if ( (unsigned __int16)wParam == Button_Strange_Button_Layout )
                        {
                            arrowLayoutFlag = 1;
                            InvalidateRect(hWnd, &rcWindow, 0);
                        }
                        return 0;
                    }
                    makeDefaultJoystickButtons(&configFile);
                    makeButtonModes(hWnd, &configFile);
                }
                else if ( (unsigned __int16)wParam != Button_Use_Gamepad )
                {
                    if ( (unsigned __int16)wParam == Button_OK )
                    {
                        commitChanges(hWnd);
                        EndDialog(hWnd, 1);
                    }
                    else if ( (unsigned __int16)wParam == Button_Cancel )
                    {
                        EndDialog(hWnd, 0);
                    }
                    else if ( (unsigned __int16)wParam == Button_Font_Dropdown_Box && HIWORD(wParam) == 1 )
                    {
                        doFontThing(hWnd);
                    }
                    return 0;
                }
                enableGamepadButtons(hWnd);
            }
            return 0;
        }
        initDialog(hWnd);
        v10 = (HINSTANCE)GetWindowLongA(hWnd, -6);
        images[0] = LoadImageA(v10, (LPCSTR)NORMAL_LAYOUT, 0, 328, 120, 0);
        images[1] = LoadImageA(v10, (LPCSTR)STRANGE_LAYOUT, 0, 328, 120, 0);
        arrowLayoutFlag = IsDlgButtonChecked(hWnd, Button_Arrows_Button_Layout) == 0;
        GetObjectA(images[arrowLayoutFlag], 24, &dword_40CBF0);
        rcWindow.left = x;
        rcWindow.top = y;
        rcWindow.right = dword_40CBF0[1] + x;
        rcWindow.bottom = dword_40CBF0[2] + y;
    }
    return 1;
}
// 40CC08: using guessed type int Arrow_Layout_Flag;

//----- (004013D0) --------------------------------------------------------
int __cdecl doFontThing(HWND hDlg)
{
    HFONT v1; // eax@4
    HWND v3; // eax@4
    CHAR String[112]; // [sp+0h] [bp-78h]@1
    LPCSTR v7; // [sp+74h] [bp-4h]@2

    GetDlgItemTextA(hDlg, 1007, String, 100);
    if ( !strcmp(String, fontName) )
        v7 = nullptr;
    else
        v7 = String;
    v1 = CreateFontA(20, 10, 0, 0, 400, 0, 0, 0, 0, 4u, 0, 0, 1u, v7);
    v3 = GetDlgItem(hDlg, 1068);
    SendMessageA(v3, 0x30u, (WPARAM)v1, 1);
    return 1;
}

//----- (00401480) --------------------------------------------------------
void __cdecl enableGamepadButtons(HWND hDlg)
{
    BOOL Enable_Flag; // ST0C_4@1
    HWND ret_GetDlgItem; // eax@1 MAPDST

    Enable_Flag = IsDlgButtonChecked(hDlg, Button_Use_Gamepad) != 0;
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Jump_1);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Attack_1);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Plus_1);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Minus_1);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Item_1);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Map_1);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Jump_2);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Attack_2);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Plus_2);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Minus_2);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Item_2);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Map_2);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Jump_3);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Attack_3);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Plus_3);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Minus_3);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Item_3);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Map_3);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Jump_4);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Attack_4);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Plus_4);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Minus_4);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Item_4);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Map_4);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Jump_5);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Attack_5);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Plus_5);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Minus_5);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Item_5);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Map_5);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Jump_6);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Attack_6);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Plus_6);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Minus_6);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Item_6);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Map_6);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Jump_7);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Attack_7);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Plus_7);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Minus_7);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Item_7);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Map_7);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Jump_8);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Attack_8);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Plus_8);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Weapon_Minus_8);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Item_8);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
    ret_GetDlgItem = GetDlgItem(hDlg, Button_Map_8);
    EnableWindow(ret_GetDlgItem, Enable_Flag);
}

//----- (00401980) --------------------------------------------------------
void __cdecl makeButtonModes(HWND hDlg, configDataFile *Config_file)
{
    int v3; // [sp+20h] [bp-10h]@11
    int v4; // [sp+24h] [bp-Ch]@6
    int v5; // [sp+28h] [bp-8h]@1
    LONG wParam; // [sp+2Ch] [bp-4h]@16

    SendDlgItemMessageA(hDlg, 1070, 0x14Eu, Config_file->display_mode, 0);
    v5 = Config_file->move_button_mode;
    if ( v5 )
    {
        if ( v5 == 1 )
            CheckRadioButton(hDlg, 1071, 1072, 1072);
    }
    else
    {
        CheckRadioButton(hDlg, 1071, 1072, 1071);
    }
    v4 = Config_file->attack_button_mode;
    if ( v4 )
    {
        if ( v4 == 1 )
            CheckRadioButton(hDlg, 1066, 1067, 1067);
    }
    else
    {
        CheckRadioButton(hDlg, 1066, 1067, 1066);
    }
    v3 = Config_file->ok_button_mode;
    if ( v3 )
    {
        if ( v3 == 1 )
            CheckRadioButton(hDlg, 1073, 1074, 1074);
    }
    else
    {
        CheckRadioButton(hDlg, 1073, 1074, 1073);
    }
    wParam = SendDlgItemMessageA(hDlg, 1007, 0x14Cu, 0xFFFFFFFF, (LPARAM)Config_file->font_name);
    if ( wParam == -1 )
        wParam = 0;
    SendDlgItemMessageA(hDlg, 1007, 0x14Eu, wParam, 0);
    doFontThing(hDlg);
    CheckDlgButton(hDlg, 1008, Config_file->joystick_mode != 0);
    switch ( Config_file->joystick_button[0] )
    {
    case 1:
        CheckRadioButton(hDlg, 1012, 1017, 1012);
        break;
    case 2:
        CheckRadioButton(hDlg, 1012, 1017, 1013);
        break;
    case 3:
        CheckRadioButton(hDlg, 1012, 1017, 1014);
        break;
    case 6:
        CheckRadioButton(hDlg, 1012, 1017, 1015);
        break;
    case 4:
        CheckRadioButton(hDlg, 1012, 1017, 1016);
        break;
    case 5:
        CheckRadioButton(hDlg, 1012, 1017, 1017);
        break;
    default:
        break;
    }
    switch ( Config_file->joystick_button[1] )
    {
    case 1:
        CheckRadioButton(hDlg, 1018, 1023, 1018);
        break;
    case 2:
        CheckRadioButton(hDlg, 1018, 1023, 1019);
        break;
    case 3:
        CheckRadioButton(hDlg, 1018, 1023, 1020);
        break;
    case 6:
        CheckRadioButton(hDlg, 1018, 1023, 1021);
        break;
    case 4:
        CheckRadioButton(hDlg, 1018, 1023, 1022);
        break;
    case 5:
        CheckRadioButton(hDlg, 1018, 1023, 1023);
        break;
    default:
        break;
    }
    switch ( Config_file->joystick_button[2] )
    {
    case 1:
        CheckRadioButton(hDlg, 1024, 1029, 1024);
        break;
    case 2:
        CheckRadioButton(hDlg, 1024, 1029, 1025);
        break;
    case 3:
        CheckRadioButton(hDlg, 1024, 1029, 1026);
        break;
    case 6:
        CheckRadioButton(hDlg, 1024, 1029, 1027);
        break;
    case 4:
        CheckRadioButton(hDlg, 1024, 1029, 1028);
        break;
    case 5:
        CheckRadioButton(hDlg, 1024, 1029, 1029);
        break;
    default:
        break;
    }
    switch ( Config_file->joystick_button[3] )
    {
    case 1:
        CheckRadioButton(hDlg, 1030, 1035, 1030);
        break;
    case 2:
        CheckRadioButton(hDlg, 1030, 1035, 1031);
        break;
    case 3:
        CheckRadioButton(hDlg, 1030, 1035, 1032);
        break;
    case 6:
        CheckRadioButton(hDlg, 1030, 1035, 1033);
        break;
    case 4:
        CheckRadioButton(hDlg, 1030, 1035, 1034);
        break;
    case 5:
        CheckRadioButton(hDlg, 1030, 1035, 1035);
        break;
    default:
        break;
    }
    switch ( Config_file->joystick_button[4] )
    {
    case 1:
        CheckRadioButton(hDlg, 1036, 1041, 1036);
        break;
    case 2:
        CheckRadioButton(hDlg, 1036, 1041, 1037);
        break;
    case 3:
        CheckRadioButton(hDlg, 1036, 1041, 1038);
        break;
    case 6:
        CheckRadioButton(hDlg, 1036, 1041, 1039);
        break;
    case 4:
        CheckRadioButton(hDlg, 1036, 1041, 1040);
        break;
    case 5:
        CheckRadioButton(hDlg, 1036, 1041, 1041);
        break;
    default:
        break;
    }
    switch ( Config_file->joystick_button[5] )
    {
    case 1:
        CheckRadioButton(hDlg, 1042, 1047, 1042);
        break;
    case 2:
        CheckRadioButton(hDlg, 1042, 1047, 1043);
        break;
    case 3:
        CheckRadioButton(hDlg, 1042, 1047, 1044);
        break;
    case 6:
        CheckRadioButton(hDlg, 1042, 1047, 1045);
        break;
    case 4:
        CheckRadioButton(hDlg, 1042, 1047, 1046);
        break;
    case 5:
        CheckRadioButton(hDlg, 1042, 1047, 1047);
        break;
    default:
        break;
    }
    switch ( Config_file->joystick_button[6] )
    {
    case 1:
        CheckRadioButton(hDlg, 1048, 1053, 1048);
        break;
    case 2:
        CheckRadioButton(hDlg, 1048, 1053, 1049);
        break;
    case 3:
        CheckRadioButton(hDlg, 1048, 1053, 1050);
        break;
    case 6:
        CheckRadioButton(hDlg, 1048, 1053, 1051);
        break;
    case 4:
        CheckRadioButton(hDlg, 1048, 1053, 1052);
        break;
    case 5:
        CheckRadioButton(hDlg, 1048, 1053, 1053);
        break;
    default:
        break;
    }
    switch ( Config_file->joystick_button[7] )
    {
    case 1:
        CheckRadioButton(hDlg, 1060, 1065, 1060);
        break;
    case 2:
        CheckRadioButton(hDlg, 1060, 1065, 1061);
        break;
    case 3:
        CheckRadioButton(hDlg, 1060, 1065, 1062);
        break;
    case 6:
        CheckRadioButton(hDlg, 1060, 1065, 1063);
        break;
    case 4:
        CheckRadioButton(hDlg, 1060, 1065, 1064);
        break;
    case 5:
        CheckRadioButton(hDlg, 1060, 1065, 1065);
        break;
    default:
        break;
    }
    enableGamepadButtons(hDlg);
}

//----- (00402220) --------------------------------------------------------
void __cdecl initDialog(HWND hDlg)
{
    HDC hDC; // ST14_4@6
    configDataFile Profile; // [sp+4h] [bp-B8h]@4
    int i; // [sp+A4h] [bp-18h]@1
    const char *lParam[5]; // [sp+A8h] [bp-14h]@1

    SetDlgItemTextA(
        hDlg,
        1010,
        "-- The map is not usable unless you have the \"Map System\" item.\r\n"
        "\r\n"
        "-- If you have problems with getting two arrow keys to work at once, please use the < > ? settings.\r\n"
        "\r\n"
        "-- Please use Courier New as the font. Others cannot be guaranteed to work.\r\n"
        "\r\n"
        "-- Also, hi to the CSMC !!!");
    lParam[0] = "Full Screen";
    lParam[1] = "320x240 Windowed ";
    lParam[2] = "640x480 Windowed ";
    lParam[3] = "Full 24-Bit ";
    lParam[4] = "Full 32-Bit ";
    for ( i = 0; i < 5; ++i )
        SendDlgItemMessageA(hDlg, 1070, 0x143u, 0, (LPARAM)lParam[i]);
    if ( !openConfig(&Profile) )
    {
        Profile.joystick_mode = 1;
        Profile.joystick_button[0] = 2;
        Profile.joystick_button[1] = 1;
        Profile.joystick_button[2] = 5;
        Profile.joystick_button[3] = 6;
        Profile.joystick_button[4] = 3;
        Profile.joystick_button[5] = 4;
        Profile.joystick_button[6] = 6;
        Profile.joystick_button[7] = 3;
    }
    SendDlgItemMessageA(hDlg, 1007, 0x143u, 0, (LPARAM)fontName);
    hDC = GetDC(hDlg);
    EnumFontFamiliesA(hDC, nullptr, fontProcedure, (LPARAM)hDlg);
    SendDlgItemMessageA(hDlg, 1007, 0x14Eu, 0, 0);
    ReleaseDC(hDlg, hDC);
    makeButtonModes(hDlg, &Profile);
}

//----- (00402380) --------------------------------------------------------
int __stdcall fontProcedure(const LOGFONTA *a1, const TEXTMETRICA *a2, DWORD a3, LPARAM hWnd)
{
    signed int v5; // [sp+0h] [bp-8h]@3
    signed int i; // [sp+4h] [bp-4h]@3

    if ( a3 & 4 && IsWindow((HWND)hWnd) )
    {
        v5 = strlen(a1->lfFaceName);
        for ( i = 0; i < v5 && a1->lfFaceName[i] != 64; ++i )
        {
            if ( a1->lfFaceName[i] & 0x80 )
            {
                SendDlgItemMessageA((HWND)hWnd, 1007, 0x143u, 0, (LPARAM)a1->lfFaceName);
                return 1;
            }
        }
    }
    return 1;
}

//----- (00402420) --------------------------------------------------------
void __cdecl makeDefaultJoystickButtons(configDataFile *Config_file)
{
    memset(Config_file, 0, sizeof(*Config_file));
    Config_file->joystick_mode = 1;
    Config_file->joystick_button[0] = 2;
    Config_file->joystick_button[1] = 1;
    Config_file->joystick_button[2] = 5;
    Config_file->joystick_button[3] = 6;
    Config_file->joystick_button[4] = 3;
    Config_file->joystick_button[5] = 4;
    Config_file->joystick_button[6] = 6;
    Config_file->joystick_button[7] = 3;
}

//----- (004024B0) --------------------------------------------------------
void __cdecl commitChanges(HWND hDlg)
{
    configDataFile Config; // [sp+0h] [bp-A0h]@1

    memset(&Config, 0, sizeof(Config));
    if ( IsDlgButtonChecked(hDlg, Button_Use_Gamepad) )
        Config.joystick_mode = 1;
    if ( IsDlgButtonChecked(hDlg, Button_Jump_1) )
        Config.joystick_button[0] = 1;
    if ( IsDlgButtonChecked(hDlg, Button_Attack_1) )
        Config.joystick_button[0] = 2;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Plus_1) )
        Config.joystick_button[0] = 3;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Minus_1) )
        Config.joystick_button[0] = 6;
    if ( IsDlgButtonChecked(hDlg, Button_Item_1) )
        Config.joystick_button[0] = 4;
    if ( IsDlgButtonChecked(hDlg, Button_Map_1) )
        Config.joystick_button[0] = 5;
    if ( IsDlgButtonChecked(hDlg, Button_Jump_2) )
        Config.joystick_button[1] = 1;
    if ( IsDlgButtonChecked(hDlg, Button_Attack_2) )
        Config.joystick_button[1] = 2;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Plus_2) )
        Config.joystick_button[1] = 3;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Minus_2) )
        Config.joystick_button[1] = 6;
    if ( IsDlgButtonChecked(hDlg, Button_Item_2) )
        Config.joystick_button[1] = 4;
    if ( IsDlgButtonChecked(hDlg, Button_Map_2) )
        Config.joystick_button[1] = 5;
    if ( IsDlgButtonChecked(hDlg, Button_Jump_3) )
        Config.joystick_button[2] = 1;
    if ( IsDlgButtonChecked(hDlg, Button_Attack_3) )
        Config.joystick_button[2] = 2;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Plus_3) )
        Config.joystick_button[2] = 3;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Minus_3) )
        Config.joystick_button[2] = 6;
    if ( IsDlgButtonChecked(hDlg, Button_Item_3) )
        Config.joystick_button[2] = 4;
    if ( IsDlgButtonChecked(hDlg, Button_Map_3) )
        Config.joystick_button[2] = 5;
    if ( IsDlgButtonChecked(hDlg, Button_Jump_4) )
        Config.joystick_button[3] = 1;
    if ( IsDlgButtonChecked(hDlg, Button_Attack_4) )
        Config.joystick_button[3] = 2;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Plus_4) )
        Config.joystick_button[3] = 3;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Minus_4) )
        Config.joystick_button[3] = 6;
    if ( IsDlgButtonChecked(hDlg, Button_Item_4) )
        Config.joystick_button[3] = 4;
    if ( IsDlgButtonChecked(hDlg, Button_Map_4) )
        Config.joystick_button[3] = 5;
    if ( IsDlgButtonChecked(hDlg, Button_Jump_5) )
        Config.joystick_button[4] = 1;
    if ( IsDlgButtonChecked(hDlg, Button_Attack_5) )
        Config.joystick_button[4] = 2;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Plus_5) )
        Config.joystick_button[4] = 3;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Minus_5) )
        Config.joystick_button[4] = 6;
    if ( IsDlgButtonChecked(hDlg, Button_Item_5) )
        Config.joystick_button[4] = 4;
    if ( IsDlgButtonChecked(hDlg, Button_Map_5) )
        Config.joystick_button[4] = 5;
    if ( IsDlgButtonChecked(hDlg, Button_Jump_6) )
        Config.joystick_button[5] = 1;
    if ( IsDlgButtonChecked(hDlg, Button_Attack_6) )
        Config.joystick_button[5] = 2;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Plus_6) )
        Config.joystick_button[5] = 3;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Minus_6) )
        Config.joystick_button[5] = 6;
    if ( IsDlgButtonChecked(hDlg, Button_Item_6) )
        Config.joystick_button[5] = 4;
    if ( IsDlgButtonChecked(hDlg, Button_Map_6) )
        Config.joystick_button[5] = 5;
    if ( IsDlgButtonChecked(hDlg, Button_Jump_7) )
        Config.joystick_button[6] = 1;
    if ( IsDlgButtonChecked(hDlg, Button_Attack_7) )
        Config.joystick_button[6] = 2;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Plus_7) )
        Config.joystick_button[6] = 3;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Minus_7) )
        Config.joystick_button[6] = 6;
    if ( IsDlgButtonChecked(hDlg, Button_Item_7) )
        Config.joystick_button[6] = 4;
    if ( IsDlgButtonChecked(hDlg, Button_Map_7) )
        Config.joystick_button[6] = 5;
    if ( IsDlgButtonChecked(hDlg, Button_Jump_8) )
        Config.joystick_button[7] = 1;
    if ( IsDlgButtonChecked(hDlg, Button_Attack_8) )
        Config.joystick_button[7] = 2;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Plus_8) )
        Config.joystick_button[7] = 3;
    if ( IsDlgButtonChecked(hDlg, Button_Weapon_Minus_8) )
        Config.joystick_button[7] = 6;
    if ( IsDlgButtonChecked(hDlg, Button_Item_8) )
        Config.joystick_button[7] = 4;
    if ( IsDlgButtonChecked(hDlg, Button_Map_8) )
        Config.joystick_button[7] = 5;
    Config.attack_button_mode = IsDlgButtonChecked(hDlg, Button_Z_Jump_X_Attack) == 0;
    Config.move_button_mode = IsDlgButtonChecked(hDlg, Button_Arrows_Button_Layout) == 0;
    Config.ok_button_mode = IsDlgButtonChecked(hDlg, Button_Jump_OK) == 0;
    Config.display_mode = SendDlgItemMessageA(hDlg, Button_Screen_Resolution, 0x147u, 2u, 0);
    GetDlgItemTextA(hDlg, 1007, Config.font_name, 64);
    saveChangesToConfig(&Config);
}

//----- (00402A90) --------------------------------------------------------
bool __cdecl saveChangesToConfig(configDataFile *Config)
{
    char path[272]; // [sp+0h] [bp-118h]@1
    bool wasWriteSuccesful; // [sp+110h] [bp-8h]@3
    FILE *configFile; // [sp+114h] [bp-4h]@1

    memset(Config, 0, 0x20u);
    strcpy(Config->proof, configFileCheck);
    sprintf(path, "%s\\%s", exePath, configFileName);
    configFile = fopen(path, "wb");
    if ( !configFile )
    {
        return false;
    }
    else
    {
        wasWriteSuccesful = fwrite(Config, sizeof(*Config), 1u, configFile);
        fclose(configFile);
        return wasWriteSuccesful == true;
    }
}

//----- (00402B50) --------------------------------------------------------
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    size_t i; // [sp+0h] [bp-4h]@1

    GetModuleFileNameA(nullptr, exePath, sizeof(exePath));
    for ( i = strlen(exePath); exePath[i] != '\\'; --i )
        ;
    exePath[i] = '\0';
    // Make options dialog
    DialogBoxParamA(hInstance, "DLG_CONFIG", nullptr, optionsDialogFunction, 0);
    return 1;
}
