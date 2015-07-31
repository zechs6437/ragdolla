#include "script.h"
#include "keyboard.h"
#include <string>
#include <ctime>

#pragma warning(disable : 4244 4305) // double <-> float conversions

//BOOL toggleRagdoll = false;
BOOL toggleRagdoll = GetPrivateProfileInt("Ragdoll", "toggleRagdoll", 0, "./Ragdolla.ini");
int ragdollKeyCode = GetPrivateProfileInt("Ragdoll", "RagdollKeyCode", 0x55, "./Ragdolla.ini"); //0x55 = U
int toggleKeyCode = GetPrivateProfileInt("Ragdoll", "ToggleKeyCode", 0x49, "./Ragdolla.ini"); //0x49 = I
BOOL toggleAlwaysRadio = GetPrivateProfileInt("Radio", "AlwaysRadio", 1, "./Ragdolla.ini");
BOOL niceFlyToggle = true;

std::string statusText;
DWORD statusTextDrawTicksMax;
bool statusTextGxtEntry;

void update_status_text()
{
	if (GetTickCount() < statusTextDrawTicksMax)
	{
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(0.55, 0.55);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
		if (statusTextGxtEntry)
		{
			UI::_SET_TEXT_ENTRY((char *)statusText.c_str());
		}
		else
		{
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((char *)statusText.c_str());
		}
		UI::_DRAW_TEXT(0.5, 0.5);
	}
}

void set_status_text(std::string str, DWORD time = 2500, bool isGxtEntry = false)
{
	statusText = str;
	statusTextDrawTicksMax = GetTickCount() + time;
	statusTextGxtEntry = isGxtEntry;
}

void radioChecker()
{
	toggleAlwaysRadio = false;
	AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
}

void gtaivCarExit()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	//Player player = PLAYER::GET_PLAYER_PED(playerPed);
	Any playerVehicle = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	//float playerVehicleSpeed = ENTITY::GET_ENTITY_SPEED(playerVehicle);
	Any isPlayerDriving = (VEHICLE::GET_PED_IN_VEHICLE_SEAT(playerVehicle, -1) == playerPed);
	
	if (isPlayerDriving)
	{
		for (int i = 0; i < 10; i++)
		{
			VEHICLE::SET_VEHICLE_ENGINE_ON(playerVehicle, true, true);
			WAIT(0);
		}
		WAIT(240);
		if (CONTROLS::IS_CONTROL_PRESSED(2, 75))
		{
			VEHICLE::SET_VEHICLE_ENGINE_ON(playerVehicle, false, true);
		}
		else
		{
			VEHICLE::SET_VEHICLE_ENGINE_ON(playerVehicle, true, true);
		}
		//WAIT(1000);
	}
}

void carModder()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Any player = PLAYER::GET_PLAYER_PED(playerPed);
	BOOL playerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);

	if (playerExists) {
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
			Any veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, true);
			VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_USING(playerPed));
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			//VEHICLE::SET_VEHICLE_COLOURS(veh, 120, 120); //color
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, true); //turbo
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, true); //xenon
			VEHICLE::SET_VEHICLE_MOD(veh, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 0) - 1, true); //spoiler
			VEHICLE::SET_VEHICLE_MOD(veh, 1, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 1) - 1, true); //frontbumper
			VEHICLE::SET_VEHICLE_MOD(veh, 2, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 2) - 1, true); //rearbumper
			VEHICLE::SET_VEHICLE_MOD(veh, 3, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 3) - 1, true); //side skirt
			VEHICLE::SET_VEHICLE_MOD(veh, 4, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 4) - 1, true); //exhaust
			VEHICLE::SET_VEHICLE_MOD(veh, 5, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 5) - 1, true); //frame
			VEHICLE::SET_VEHICLE_MOD(veh, 6, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 6) - 1, true); //grill
			VEHICLE::SET_VEHICLE_MOD(veh, 7, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 7) - 1, true); //hood
			VEHICLE::SET_VEHICLE_MOD(veh, 8, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 8) - 1, true); //fender
			VEHICLE::SET_VEHICLE_MOD(veh, 9, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 9) - 1, true); //right fender
			VEHICLE::SET_VEHICLE_MOD(veh, 10, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 10) - 1, true); //roof
			VEHICLE::SET_VEHICLE_MOD(veh, 11, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 11) - 1, true); //engine
			VEHICLE::SET_VEHICLE_MOD(veh, 12, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 12) - 1, true); //brakes
			VEHICLE::SET_VEHICLE_MOD(veh, 13, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 13) - 1, true); //tranny
			//VEHICLE::SET_VEHICLE_MOD(veh, 14, 14, true); //horn
			VEHICLE::SET_VEHICLE_MOD(veh, 15, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 15) - 1, true); //suspension
			VEHICLE::SET_VEHICLE_MOD(veh, 16, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 16) - 1, true); //armor
			//printf("Armor Mods:%d\n", VEHICLE::GET_NUM_VEHICLE_MODS(veh, 16));
			//VEHICLE::SET_VEHICLE_MOD(veh, 23, 19, true); //front wheels
			//VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, 3, 0, 0);
			//VEHICLE::SET_VEHICLE_MOD_COLOR_2(veh, 3, 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, 6); //rims
			VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);
			set_status_text("Car Fully Upgraded");
		}
	}
	
}

void ragDoller()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	BOOL playerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);
	if (!playerExists) return;
	PED::SET_PED_CAN_RAGDOLL(playerPed, true);
	PED::SET_PED_TO_RAGDOLL(playerPed, 0, 0, 0, false, false, false);
}

void niceFly()
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	//Any player = PLAYER::GET_PLAYER_PED(playerPed);
	if (niceFlyToggle && CONTROLS::IS_CONTROL_PRESSED(0, 21))
	{
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
		if (!WEAPON::HAS_PED_GOT_WEAPON(playerPed, 4222310262, 0))
		{
			WEAPON::GIVE_WEAPON_TO_PED(playerPed, 4222310262, 1, true, true);
		}
		if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(playerPed) > 1.5)
		{
			if (PED::GET_PED_PARACHUTE_STATE(playerPed) != 3)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, 0, 0, 10000, 0, 0, 0, 0, 0, true, false, false, false, false);
			}
			if (CONTROLS::IS_CONTROL_PRESSED(0, 31))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, 0, 0, 0, 10000, 0, 0, 0, 0, true, false, false, false, false);
			}
		}
	}
}

void weaponModder()
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	Hash silencerHashes[5] = { 0x65EA7EBB, 0x837445AA, 0xA73D4664, 0xC304849A, 0xE608B35E };
	Hash magazineHashes[22] = { 0x249A17D5, 0x64F9C62B, 0x7B0033B3, 0x7C8BD10E, 0x86BD7F72, 0x8EC1C979, 0xB3688B0F, 0xD6C59CD6, 0xED265A1C, 0xD67B4F2D, 0xD9D3AC92, 0x33BA12E8, 0x10E6BA2B, 0x350966FB,
		0xBB46E417, 0x334A5203, 0x82158B47, 0xEAC8C270, 0xB1214F9B, 0x91109691, 0xCCFD2AC5, 0x971CF6FD };
	Hash gripHash = 0xC164F53;
	Hash flashlightHashes[2] = { 0x359B7AAE, 0x7BC4CDDC };
	Hash scopeHashes[7] = { 0x9D2FBF29, 0xA0D89C42, 0xAA2C45B4, 0xD2443DDC, 0x3CC6BA57, 0x3C00AFED, 0xBC54DA77 };

	Hash playerWeapon = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);

	for (int a = 0; a < 5; a = a + 1)
	{
		if (WEAPON::_CAN_WEAPON_HAVE_COMPONENT(playerWeapon, silencerHashes[a]))
		{
			if (WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, playerWeapon, silencerHashes[a]))
			{
				WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(playerPed, playerWeapon, silencerHashes[a]);
				set_status_text("Silencer Removed");
			}
			else
			{
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, playerWeapon, silencerHashes[a]);
				set_status_text("Silencer Attached");
			}
		}
	}
	
	for (int a = 0; a < 22; a = a + 1)
	{
		if (WEAPON::_CAN_WEAPON_HAVE_COMPONENT(playerWeapon, magazineHashes[a]))
		{
			if (!WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, playerWeapon, magazineHashes[a]))
			{
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, playerWeapon, magazineHashes[a]);
			}
		}
	}

	for (int a = 0; a < 2; a = a + 1)
	{
		if (WEAPON::_CAN_WEAPON_HAVE_COMPONENT(playerWeapon, flashlightHashes[a]))
		{
			if (!WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, playerWeapon, flashlightHashes[a]))
			{
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, playerWeapon, flashlightHashes[a]);
			}
		}
	}

	for (int a = 0; a < 7; a = a + 1)
	{
		if (WEAPON::_CAN_WEAPON_HAVE_COMPONENT(playerWeapon, scopeHashes[a]))
		{
			if (!WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, playerWeapon, scopeHashes[a]))
			{
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, playerWeapon, scopeHashes[a]);
			}
		}
	}

	if (WEAPON::_CAN_WEAPON_HAVE_COMPONENT(playerWeapon, gripHash)) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, playerWeapon, gripHash);
	
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
}

void update()
{
	update_status_text();
	if (IsKeyJustUp(0x12)) carModder();
	if (CONTROLS::IS_CONTROL_PRESSED(2, 75)) gtaivCarExit();
	if (IsKeyDown(ragdollKeyCode)) ragDoller();
	if (toggleAlwaysRadio) radioChecker();
	if (niceFlyToggle && CONTROLS::IS_CONTROL_PRESSED(0, 21)) niceFly();
	
	if (IsKeyJustUp(0x4F)) weaponModder();

	if (IsKeyJustUp(toggleKeyCode)){
		niceFlyToggle = !niceFlyToggle;
		if (niceFlyToggle){
			set_status_text("Nice Fly ON");
//			printf("Nice Fly ON");
		}
		else {
			set_status_text("Nice Fly OFF");
//			printf("Nice Fly OFF");
		}
	}




}

void main()
{
	while (true)
	{
		update();
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