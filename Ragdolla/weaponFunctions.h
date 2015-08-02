#ifndef WEAPONFUNCTIONS
#define WEAPONFUNCTIONS

#include "drawmenu.h"

static Hash silencerHashes[5] = { 0x65EA7EBB, 0x837445AA, 0xA73D4664, 0xC304849A, 0xE608B35E };
static Hash magazineHashes[22] = { 0x249A17D5, 0x64F9C62B, 0x7B0033B3, 0x7C8BD10E, 0x86BD7F72, 0x8EC1C979, 0xB3688B0F, 0xD6C59CD6, 0xED265A1C, 0xD67B4F2D, 0xD9D3AC92, 0x33BA12E8, 0x10E6BA2B, 0x350966FB, 
	0xBB46E417, 0x334A5203, 0x82158B47, 0xEAC8C270, 0xB1214F9B, 0x91109691, 0xCCFD2AC5, 0x971CF6FD };
static Hash gripHash = 0xC164F53;
static Hash flashlightHashes[2] = { 0x359B7AAE, 0x7BC4CDDC };
static Hash scopeHashes[7] = { 0x9D2FBF29, 0xA0D89C42, 0xAA2C45B4, 0xD2443DDC, 0x3CC6BA57, 0x3C00AFED, 0xBC54DA77 };
static Hash skinHashes[12] = { 0x4ead7533, 0x377cd377, 0xd89b9658, 0x9b76c72c, 0xd7391086, 0x77b8ab2f, 0x7a6a7b7b, 0x27872c90, 0x487aae09, 0x85a64df9, 0x4032b5e7, 0x161e9241 };

extern bool featureWeaponSilencer;
extern bool featureWeaponMagazine;
extern bool featureWeaponGrip;
extern bool featureWeaponFlashlight;
extern bool featureWeaponScope;
extern bool featureWeaponTint[];
extern bool featureWeaponSkinDLC;


void toggleSilencer();
void toggleMagazine();
void toggleGrip();
void toggleFlashlight();
void toggleScope();
void toggleWeaponSkin();
void changeWeaponTint(int tintSelection);
void checkWeaponTint();
void weaponSanityCheck();


#endif WEAPONFUNCTIONS