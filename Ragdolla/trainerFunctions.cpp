#include "trainerFunctions.h"

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

void ragdoller()
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
	if (CONTROLS::IS_CONTROL_PRESSED(0, 21))
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
