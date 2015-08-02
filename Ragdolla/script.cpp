#include "drawMenu.h"
#include "trainerFunctions.h"
#include "weaponFunctions.h"
#include <ctime>

#pragma warning(disable : 4244 4305 4800) // double <-> float conversions (and some bool conversion bullshit that I don't care about)

BOOL niceFlyToggle = true;

bool featureNiceFly = GetPrivateProfileInt("Toggles", "NiceFly", 0, "./Ragdolla.ini");
bool featureGTAIVCarExit = GetPrivateProfileInt("Toggles", "GTAIVCarExit", 0, "./Ragdolla.ini");
bool featureRagdoll = GetPrivateProfileInt("Toggles", "Ragdoll", 0, "./Ragdolla.ini");
bool featureAlwaysRadio = GetPrivateProfileInt("Toggles", "AlwaysRadio", 1, "./Ragdolla.ini");
bool featureAlwaysRadioUpdated = false;
bool featureCarUpgrade = GetPrivateProfileInt("Toggles", "CarUpgrade", 1, "./Ragdolla.ini");
bool featureSilencerToggle = GetPrivateProfileInt("Toggles", "SilencerToggle", 1, "./Ragdolla.ini");
bool featureWeaponSilencer = false;
bool featureWeaponMagazine = false;
bool featureWeaponGrip = false;
bool featureWeaponFlashlight = false;
bool featureWeaponScope = false;
bool featureWeaponTint[8] = { false, false, false, false, false, false, false, false };
bool featureWeaponSkinDLC = false;

	/*
	BOOL HAS_PED_GOT_WEAPON_COMPONENT(Ped ped, Hash weaponHash, Hash componentHash)
	BOOL IS_PED_WEAPON_COMPONENT_ACTIVE(Ped ped, Hash weaponHash, Hash componentHash)
	BOOL _CAN_WEAPON_HAVE_COMPONENT(Hash weaponHash, Hash componentHash)
	void REMOVE_WEAPON_COMPONENT_FROM_PED(Ped ped, Hash weaponHash, Hash componentHash)
	void GIVE_WEAPON_COMPONENT_TO_PED(Ped ped, Hash weaponHash, Hash componentHash)
	Hash GET_SELECTED_PED_WEAPON(Ped ped)


	Advanced scope - 0xBC54DA77: Sniper Rifle, Heavy Sniper,
	Extended clip - 0x249A17D5: AP Pistol,
	Extended clip - 0x64F9C62B: Heavy Pistol,
	Extended clip - 0x7B0033B3: SNS Pistol,
	Extended clip - 0x7C8BD10E: Special Carbine,
	Extended clip - 0x86BD7F72: Assault Shotgun,
	Extended clip - 0x8EC1C979: Advanced Rifle,
	Extended clip - 0xB3688B0F: Bullpup Rifle,
	Extended clip - 0xD6C59CD6: Combat MG,
	Extended clip - 0xED265A1C: Pistol,
	Extended clip - 0xD67B4F2D: Combat Pistol,
	Extended clip - 0xD9D3AC92: .50 Pistol,
	Extended clip - 0x33BA12E8: Vintage Pistol,
	Extended clip - 0x10E6BA2B: Micro SMG,
	Extended clip - 0x350966FB: SMG,
	Extended clip - 0xBB46E417: Assault SMG,
	Extended clip - 0x334A5203: Combat PDW,
	Extended clip - 0x82158B47: MG,
	Extended clip - 0xEAC8C270: Gusenberg,
	Extended clip - 0xB1214F9B: Assault Rifle,
	Extended clip - 0x91109691: Carbine Rifle,
	Extended clip - 0xCCFD2AC5: Marksman Rifle,
	Extended clip - 0x971CF6FD: Heavy Shotgun,
	Flashlight - 0x359B7AAE: Pistol, Combat Pistol, AP Pistol, Heavy Pistol, .50 Pistol, Micro SMG,
	Flashlight - 0x7BC4CDDC: SMG, Assault SMG, Combat PDW, Assault Rifle, Carbine Rifle, Advanced Rifle, Special Carbine, Bullpup Rifle, Pump Shotgun, Assault Shotgun, Bullpup Shotgun, Heavy Shotgun, Marksman Rifle, Grenade Launcher, Smoke Grenade Launcher,
	Grip - 0xC164F53: Combat PDW, Assault Rifle, Carbine Rifle, Special Carbine, Bullpup Rifle, Combat MG, Assault Shotgun, Bullpup Shotgun, Heavy Shotgun, Marksman Rifle, Grenade Launcher, Smoke Grenade Launcher,
	Regular clip - 0xC5A12F80: Bullpup Rifle,
	Regular clip - 0xC6C7E581: Special Carbine,
	Regular clip - 0xD4A969A: Heavy Pistol,
	Regular clip - 0xE1FFB34A: Combat MG,
	Regular clip - 0xF8802ED9: SNS Pistol,
	Scope - 0x9D2FBF29: Micro SMG, Assault SMG, Assault Rifle,
	Scope - 0xA0D89C42: Carbine Rifle, Special Carbine, Combat MG,
	Scope - 0xAA2C45B4: Combat PDW, Advanced Rifle, Bullpup Rifle, Grenade Launcher, Smoke Grenade Launcher,
	Scope - 0xD2443DDC: Sniper Rifle, Heavy Sniper,
	Scope - 0x3CC6BA57: SMG,
	Scope - 0x3C00AFED: MG,
	Suppressor - 0x65EA7EBB: Pistol,
	Suppressor - 0x837445AA: Carbine Rifle, Advanced Rifle, Bullpup Rifle, Assault Shotgun, Marksman Rifle,
	Suppressor - 0xA73D4664: .50 Pistol, Micro SMG, Assault SMG, Assault Rifle, Special Carbine, Bullpup Shotgun, Heavy Shotgun, Sniper Rifle,
	Suppressor - 0xC304849A: Combat Pistol, AP Pistol, Heavy Pistol, Vintage Pistol, SMG,
	Suppressor - 0xE608B35E: Pump Shotgun,
	Special finish - 0x27872C90: SMG,
	Special finish - 0xD7391086: Pistol,
	Special finish - 0x9B76C72C: AP Pistol,
	Special finish - 0x487AAE09: Micro SMG,
	Special finish - 0x85A64DF9: Sawed-off Shotgun,
	Special finish - 0x377CD377: Advanced Rifle,
	Special finish - 0xD89B9658: Carbine Rifle,
	Special finish - 0x4EAD7533: Assault Rifle,
	Special finish - 0x4032B5E7: Sniper Rifle,
	Special finish - 0x77B8AB2F: .50 Pistol,
	Special finish - 0x7A6A7B7B: Heavy Pistol,
	Special finish - 0x161E9241: Marksman Rifle,
	??? - 0x9BC64089: Sniper Rifle,
	*/

void update_features()
{
	update_status_text();

	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);

	if (featureNiceFly && CONTROLS::IS_CONTROL_PRESSED(0, 21))
		niceFly();

	if (featureGTAIVCarExit && CONTROLS::IS_CONTROL_PRESSED(2, 75))
		gtaivCarExit();

	if (featureRagdoll && IsKeyDown(0x55)) // Keyboard 'U'
		ragdoller();

	if (featureAlwaysRadioUpdated)
	{
		if (bPlayerExists && !featureAlwaysRadio)
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
		featureAlwaysRadioUpdated = false;
	}
	if (featureAlwaysRadio)
	{
		if (bPlayerExists)
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
	}

	if (featureCarUpgrade && IsKeyJustUp(0x12))
		carModder();

	Hash playerWeapon = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);

	if (featureSilencerToggle && IsKeyJustUp(0x4F)) //keyboard 'O' (O as in your mom saying "oh my god ken gimme dat cack")
	{
		toggleSilencer();
	}
}

int activeLineIndexWeaponTint = 0;

void process_weapontint_menu()
{
	const float lineWidth = 300.0;
	const int lineCount = 9;

	std::string caption = "Weapon Tints";

	static struct {
		LPCSTR		text;
		bool		*pState;
		bool		*pUpdated;
	} lines[lineCount] = {
		{ "Normal", &featureWeaponTint[0], NULL },
		{ "Green", &featureWeaponTint[1], NULL },
		{ "Gold", &featureWeaponTint[2], NULL },
		{ "Pink", &featureWeaponTint[3], NULL },
		{ "Army", &featureWeaponTint[4], NULL },
		{ "LSPD", &featureWeaponTint[5], NULL },
		{ "Orange", &featureWeaponTint[6], NULL },
		{ "Platinum", &featureWeaponTint[7], NULL },
		{ "DLC Weapon Skin", &featureWeaponSkinDLC, NULL }
	};
	DWORD waitTime = 150;
	while (true)
	{
		weaponSanityCheck();
		checkWeaponTint();
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(caption, lineWidth, 15.0, 18.0, 15.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexWeaponTint)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
					lineWidth, 9.0, 60.0 + i * 36.0, 15.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexWeaponTint].text, lines[activeLineIndexWeaponTint].pState),
				lineWidth + 1.0, 11.0, 56.0 + activeLineIndexWeaponTint * 36.0, 15.0, 7.0, true, false);

			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		// process buttons
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();
			switch (activeLineIndexWeaponTint)
			{
			case 0:
			{
				if (featureWeaponSkinDLC)
					break;
				changeWeaponTint(0);
				break;
			}
			case 1:
			{
				if (featureWeaponSkinDLC)
					break;
				changeWeaponTint(1);
				break;
			}
			case 2:
			{
				if (featureWeaponSkinDLC)
					break;
				changeWeaponTint(2);
				break;
			}
			case 3:
			{
				if (featureWeaponSkinDLC)
					break;
				changeWeaponTint(3);
				break;
			}
			case 4:
			{
				if (featureWeaponSkinDLC)
					break;
				changeWeaponTint(4);
				break;
			}
			case 5:
			{
				if (featureWeaponSkinDLC)
					break;
				changeWeaponTint(5);
				break;
			}
			case 6:
			{
				if (featureWeaponSkinDLC)
					break;
				changeWeaponTint(6);
				break;
			}
			case 7:
			{
				if (featureWeaponSkinDLC)
					break;
				changeWeaponTint(7);
				break;
			}
			case 8:
			{
				toggleWeaponSkin();
				featureWeaponSkinDLC = !featureWeaponSkinDLC;
			}
			default:
				if (lines[activeLineIndexWeaponTint].pState)
					*lines[activeLineIndexWeaponTint].pState = !(*lines[activeLineIndexWeaponTint].pState);
				if (lines[activeLineIndexWeaponTint].pUpdated)
					*lines[activeLineIndexWeaponTint].pUpdated = true;
			}
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexWeaponTint == 0)
						activeLineIndexWeaponTint = lineCount;
					activeLineIndexWeaponTint--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexWeaponTint++;
						if (activeLineIndexWeaponTint == lineCount)
							activeLineIndexWeaponTint = 0;
						waitTime = 150;
					}
	}
}

int activeLineIndexWeapons = 0;

void process_weaponupgrade_menu()
{
	const float lineWidth = 300.0;
	const int lineCount = 7;

	std::string caption = "Weapon Attachment Trainer by Gumshoe";

	static struct {
		LPCSTR		text;
		bool		*pState;
		bool		*pUpdated;
	} lines[lineCount] = {
		{ "Silencer EZ Toggle (Default: 'O')", &featureSilencerToggle, NULL },
		{ "Silencer Attachment", &featureWeaponSilencer, NULL },
		{ "Magazine Attachment", &featureWeaponMagazine, NULL },
		{ "Grip Attachment", &featureWeaponGrip, NULL },
		{ "Flashlight Attachment", &featureWeaponFlashlight, NULL },
		{ "Scope Attachment", &featureWeaponScope, NULL },
		{ "Weapon Tint", NULL, NULL }
	};
	DWORD waitTime = 150;
	while (true)
	{
		weaponSanityCheck();
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(caption, lineWidth, 15.0, 18.0, 15.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexWeapons)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
					lineWidth, 9.0, 60.0 + i * 36.0, 15.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexWeapons].text, lines[activeLineIndexWeapons].pState),
				lineWidth + 1.0, 11.0, 56.0 + activeLineIndexWeapons * 36.0, 15.0, 7.0, true, false);

			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		// process buttons
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();
			switch (activeLineIndexWeapons)
			{
			case 1:
			{
				toggleSilencer();
				featureWeaponSilencer = !featureWeaponSilencer;
				break;
			}
			case 2:
			{
				toggleMagazine();
				featureWeaponMagazine = !featureWeaponMagazine;
				break;
			}
			case 3:
			{
				toggleGrip();
				featureWeaponGrip = !featureWeaponGrip;
				break;
			}
			case 4:
			{
				toggleFlashlight();
				featureWeaponFlashlight = !featureWeaponFlashlight;
				break;
			}
			case 5:
			{
				toggleScope();
				featureWeaponScope = !featureWeaponScope;
				break;
			}
			case 6:
			{
				process_weapontint_menu();
				break;
			}
			case 0:
			{
				if (featureSilencerToggle)
					WritePrivateProfileString("Toggles", "SilencerToggle", " 0", "./WeaponAttachmentTrainer.ini");
				else
					WritePrivateProfileString("Toggles", "SilencerToggle", " 1", "./WeaponAttachmentTrainer.ini");
			}
			default:
				if (lines[activeLineIndexWeapons].pState)
					*lines[activeLineIndexWeapons].pState = !(*lines[activeLineIndexWeapons].pState);
				if (lines[activeLineIndexWeapons].pUpdated)
					*lines[activeLineIndexWeapons].pUpdated = true;
			}
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexWeapons == 0)
						activeLineIndexWeapons = lineCount;
					activeLineIndexWeapons--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexWeapons++;
						if (activeLineIndexWeapons == lineCount)
							activeLineIndexWeapons = 0;
						waitTime = 150;
					}
	}
}

int activeLineIndexMain = 0;

void process_main_menu()
{
	const float lineWidth = 250.0;
	const int lineCount = 6;

	std::string caption = "Maarek's Awesome Shit";

	static struct {
		LPCSTR		text;
		bool		*pState;
		bool		*pUpdated;
	} lines[lineCount] = {
		{ "Nice Fly", &featureNiceFly, NULL },
		{ "GTAIV Car Exit", &featureGTAIVCarExit, NULL },
		{ "Ragdoll (U)", &featureRagdoll, NULL },
		{ "Always Radio", &featureAlwaysRadio, &featureAlwaysRadioUpdated },
		{ "Car Upgrade (ALT)", &featureCarUpgrade, NULL },
		{ "Weapon Upgrades", NULL, NULL }
	};

	DWORD waitTime = 150;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(caption, lineWidth, 15.0, 18.0, 15.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexMain)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
					lineWidth, 9.0, 60.0 + i * 36.0, 15.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexMain].text, lines[activeLineIndexMain].pState),
				lineWidth + 1.0, 11.0, 56.0 + activeLineIndexMain * 36.0, 15.0, 7.0, true, false);

			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		// process buttons
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();
			switch (activeLineIndexMain)
			{
			case 0:
				if (!featureNiceFly)
					WritePrivateProfileString("Toggles", "NiceFly", " 1", "./Ragdolla.ini");
				else
					WritePrivateProfileString("Toggles", "NiceFly", " 0", "./Ragdolla.ini");
				goto GHETTOJUMP;
			case 1:
				if (!featureGTAIVCarExit)
					WritePrivateProfileString("Toggles", "GTAIVCarExit", " 1", "./Ragdolla.ini");
				else
					WritePrivateProfileString("Toggles", "GTAIVCarExit", " 0", "./Ragdolla.ini");
				goto GHETTOJUMP;
			case 2:
				if (!featureRagdoll)
					WritePrivateProfileString("Toggles", "Ragdoll", " 1", "./Ragdolla.ini");
				else
					WritePrivateProfileString("Toggles", "Ragdoll", " 0", "./Ragdolla.ini");
				goto GHETTOJUMP;
			case 3:
				if (!featureAlwaysRadio)
					WritePrivateProfileString("Toggles", "AlwaysRadio", " 1", "./Ragdolla.ini");
				else
					WritePrivateProfileString("Toggles", "AlwaysRadio", " 0", "./Ragdolla.ini");
				goto GHETTOJUMP;
			case 4:
				if (!featureCarUpgrade)
					WritePrivateProfileString("Toggles", "CarUpgrade", " 1", "./Ragdolla.ini");
				else
					WritePrivateProfileString("Toggles", "CarUpgrade", " 0", "./Ragdolla.ini");
				goto GHETTOJUMP;
			case 5:
				weaponSanityCheck();
				process_weaponupgrade_menu();
				break;
GHETTOJUMP: //this is so bad
			default:
				if (lines[activeLineIndexMain].pState)
					*lines[activeLineIndexMain].pState = !(*lines[activeLineIndexMain].pState);
				if (lines[activeLineIndexMain].pUpdated)
					*lines[activeLineIndexMain].pUpdated = true;
			}
			waitTime = 200;
		}
		else
		if (bBack || trainer_switch_pressed())
		{
			menu_beep();
			break;
		}
		else
		if (bUp)
		{
			menu_beep();
			if (activeLineIndexMain == 0)
				activeLineIndexMain = lineCount;
			activeLineIndexMain--;
			waitTime = 150;
		}
		else
		if (bDown)
		{
			menu_beep();
			activeLineIndexMain++;
			if (activeLineIndexMain == lineCount)
				activeLineIndexMain = 0;
			waitTime = 150;
		}
	}
}

void main()
{
	while (true)
	{
		if (trainer_switch_pressed())
		{
			menu_beep();
			process_main_menu();
		}
		update_features();
		WAIT(0);
	}
}

void ScriptMain()
{
//	AllocConsole();
//	freopen("CONIN$", "r", stdin);
//	freopen("CONOUT$", "w", stdout);
//	freopen("CONOUT$", "w", stderr);
	srand(GetTickCount());
	main();
}