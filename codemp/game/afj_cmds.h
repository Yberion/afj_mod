#pragma once

// WARNING: COMMANDS MUST BE SORTED IN ALPHABETICAL ORDER AND START WITH "afj"
#define AFJ_COMMANDS_JAMPGAME	{ "afjaddbot",				Cmd_afjAddbot_f,			CMD_NOINTERMISSION },\
								{ "afjban",					Cmd_afjBan_f,				CMD_NOINTERMISSION },\
								{ "afjbanlistip",			Cmd_afjBanListIp_f,			0 },\
								{ "afjcapturelimit",		Cmd_afjCapturelimit_f,		CMD_NOINTERMISSION },\
								{ "afjclanlogin",			Cmd_afjClanLogIn_f,			0 },\
								{ "afjclanlogout",			Cmd_afjClanLogOut_f,		0 },\
								{ "afjcpmsg",				Cmd_afjCpMsg_f,				CMD_NOINTERMISSION },\
								{ "afjdevmap",				Cmd_afjDevMap_f,			CMD_NOINTERMISSION },\
								{ "afjdropsaber",			Cmd_afjDropSaber_f,			CMD_NOINTERMISSION|CMD_ALIVE },\
								{ "afjforceteam",			Cmd_afjForceTeam_f,			CMD_NOINTERMISSION },\
								{ "afjfraglimit",			Cmd_afjFraglimit_f,			CMD_NOINTERMISSION },\
								{ "afjgametype",			Cmd_afjGametype_f,			CMD_NOINTERMISSION },\
								{ "afjignore",				Cmd_afjIgnore_f,			0 },\
								{ "afjignorelist",			Cmd_afjIgnoreList_f,		0 },\
								{ "afjkick",				Cmd_afjKick_f,				0 },\
								{ "afjkill",				Cmd_afjKill_f,				CMD_NOINTERMISSION },\
								{ "afjknockmedown",			Cmd_afjKnockMeDown_f,		CMD_NOINTERMISSION|CMD_ALIVE },\
								{ "afjmap",					Cmd_afjMap_f,				CMD_NOINTERMISSION },\
								{ "afjmap_restart",			Cmd_afjMapRestart_f,		CMD_NOINTERMISSION },\
								{ "afjnoclip",				Cmd_afjNoclip_f,			CMD_NOINTERMISSION|CMD_ALIVE },\
								{ "afjnotarget",			Cmd_afjNotarget_f,			CMD_NOINTERMISSION|CMD_ALIVE },\
								{ "afjnpc",					Cmd_NPC_f,					CMD_NOINTERMISSION|CMD_ALIVE },\
								{ "afjorigin",				Cmd_afjOrigin_f,			CMD_NOINTERMISSION|CMD_ALIVE },\
								{ "afjempower",				Cmd_afjEmpower_f,			CMD_NOINTERMISSION },\
								{ "afjprotect",				Cmd_afjProtect_f,			CMD_NOINTERMISSION },\
								{ "afjrefusetele",			Cmd_afjRefuseTele_f,		0 },\
								{ "afjremoveip",			Cmd_afjRemoveIp_f,			CMD_NOINTERMISSION },\
								{ "afjrename",				Cmd_afjRename_f,			CMD_NOINTERMISSION },\
								{ "afjsilence",				Cmd_afjSilence_f,			0 },\
								{ "afjslap",				Cmd_afjSlap_f,				CMD_NOINTERMISSION },\
								{ "afjsleep",				Cmd_afjSleep_f,				CMD_NOINTERMISSION },\
								{ "afjstatus",				Cmd_afjStatus_f,			0 },\
								{ "afjstatusip",			Cmd_afjStatusIp_f,			0 },\
								{ "afjtele",				Cmd_afjTele_f,				CMD_NOINTERMISSION },\
								{ "afjtimelimit",			Cmd_afjTimelimit_f,			CMD_NOINTERMISSION },\
								{ "afjunignoreall",			Cmd_afjUnIgnoreAll_f,		0 },\
								{ "afjunsilence",			Cmd_afjUnSilence_f,			0 },\
								{ "afjwake",				Cmd_afjWake_f,				0 },\
								{ "afjweapon",				Cmd_afjWeapon_f,			CMD_NOINTERMISSION },

typedef struct afjUser_s {
	qboolean	isClanMember;
	int			ignoredClients;
	qboolean	isSilenced;
	qboolean	refuseTele;
	qboolean	isSlept;
	qboolean	hasWeapons;
	int			oldWeapons;
	int			oldAmmo[MAX_AMMO];
	qboolean	hasPowers;
	int			oldForcePowerBaseLevel[NUM_FORCE_POWERS];
	int			oldForcePowerLevel[NUM_FORCE_POWERS];
	int			oldForcePowersKnown;
	int			armorBeforeDuel;
	int			healthBeforeDuel;
} afjUser_t;

typedef struct afjLevel_s {
	gametype_t	nextGametype;
	qboolean	waitingNextGametype;
} afjLevel_t;


void Cmd_afjAddbot_f(gentity_t *ent);
void Cmd_afjBan_f(gentity_t *ent);
void Cmd_afjBanListIp_f(gentity_t *ent);
void Cmd_afjCapturelimit_f(gentity_t *ent);
void Cmd_afjClanLogIn_f(gentity_t *ent);
void Cmd_afjClanLogOut_f(gentity_t *ent);
void Cmd_afjCpMsg_f(gentity_t *ent);
void Cmd_afjDevMap_f(gentity_t *ent);
void Cmd_afjDropSaber_f(gentity_t *ent);
void Cmd_afjForceTeam_f(gentity_t *ent);
void Cmd_afjFraglimit_f(gentity_t *ent);
void Cmd_afjGametype_f(gentity_t *ent);
void Cmd_afjIgnore_f(gentity_t *ent);
void Cmd_afjIgnoreList_f(gentity_t *ent);
void Cmd_afjKick_f(gentity_t *ent);
void Cmd_afjKill_f(gentity_t *ent);
void Cmd_afjKnockMeDown_f(gentity_t *ent);
void Cmd_afjMap_f(gentity_t *ent);
void Cmd_afjMapRestart_f(gentity_t *ent);
void Cmd_afjNoclip_f(gentity_t *ent);
void Cmd_afjNotarget_f(gentity_t *ent);
void Cmd_NPC_f(gentity_t *ent);
void Cmd_afjOrigin_f(gentity_t *ent);
void Cmd_afjEmpower_f(gentity_t *ent);
void Cmd_afjProtect_f(gentity_t *ent);
void Cmd_afjRefuseTele_f(gentity_t *ent);
void Cmd_afjRemoveIp_f(gentity_t *ent);
void Cmd_afjRename_f(gentity_t *ent);
void Cmd_afjSilence_f(gentity_t *ent);
void Cmd_afjSlap_f(gentity_t *ent);
void Cmd_afjSleep_f(gentity_t *ent);
void Cmd_afjStatus_f(gentity_t *ent);
void Cmd_afjStatusIp_f(gentity_t *ent);
void Cmd_afjTele_f(gentity_t *ent);
void Cmd_afjTimelimit_f(gentity_t *ent);
void Cmd_afjUnIgnoreAll_f(gentity_t *ent);
void Cmd_afjUnSilence_f(gentity_t *ent);
void Cmd_afjWake_f(gentity_t *ent);
void Cmd_afjWeapon_f(gentity_t *ent);
#define EMOTE( x ) void Cmd_Emote_##x( gentity_t *ent );
#include "afj_emotes.h"
#undef EMOTE