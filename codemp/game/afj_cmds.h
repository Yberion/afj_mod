#pragma once

#define PRIV_ADDBOT			(0x0000000000000001u)
#define PRIV_ADMINSTATUS	(0x0000000000000002u)
#define PRIV_BAN			(0x0000000000000004u)
#define PRIV_BANLISTIP		(0x0000000000000008u)
#define PRIV_CAPTURELIMIT	(0x0000000000000010u)
#define PRIV_CLANLOGIN		(0x0000000000000020u)
#define PRIV_CLANLOGOUT		(0x0000000000000040u)
#define PRIV_CPMSG			(0x0000000000000080u)
#define PRIV_DEVMAP			(0x0000000000000100u)
#define PRIV_DROPSABER		(0x0000000000000200u)
#define PRIV_FORCETEAM		(0x0000000000000400u)
#define PRIV_EMPOWER		(0x0000000000000800u)
#define PRIV_FRAGLIMIT		(0x0000000000001000u)
#define PRIV_GAMETYPE		(0x0000000000002000u)
#define PRIV_IGNORE			(0x0000000000004000u)
#define PRIV_IGNORELIST		(0x0000000000008000u)
#define PRIV_KICK			(0x0000000000010000u)
#define PRIV_KILL			(0x0000000000020000u)
#define PRIV_KNOCKMEDOWN	(0x0000000000040000u)
#define PRIV_LOGOUT			(0x0000000000080000u)
#define PRIV_MAP			(0x0000000000100000u)
#define PRIV_MAP_RESTART	(0x0000000000200000u)
#define PRIV_NOTCLIP		(0x0000000000400000u)
#define PRIV_NOTARGET		(0x0000000000800000u)
#define PRIV_NPC			(0x0000000001000000u)
#define PRIV_ORIGIN			(0x0000000002000000u)
#define PRIV_PROTECT		(0x0000000004000000u)
#define PRIV_REFUSETELE		(0x0000000008000000u)
#define PRIV_REMOVEIP		(0x0000000010000000u)
#define PRIV_RENAME			(0x0000000020000000u)
#define PRIV_SILENCE		(0x0000000040000000u)
#define PRIV_SLAP			(0x0000000080000000u)
#define PRIV_SLEEP			(0x0000000100000000u)
#define PRIV_STATUS			(0x0000000200000000u)
#define PRIV_STATUSIP		(0x0000000400000000u)
#define PRIV_TELE			(0x0000000800000000u)
#define PRIV_TIMELIMIT		(0x0000001000000000u)
#define PRIV_UNIGNOREALL	(0x0000002000000000u)
#define PRIV_UNSILENCE		(0x0000004000000000u)
#define PRIV_WAKE			(0x0000008000000000u)
#define PRIV_WEAPON			(0x0000010000000000u)

typedef struct afjUser_s {
	uint64_t	privileges;
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

qboolean	 AFJ_HasPrivilege(const gentity_t *ent, uint64_t privilege);
qboolean	 AFJ_HandleCommands(gentity_t *ent, const char *cmd);

const size_t	getNumEmotes();
const char		*getNameEmotesByIndex(const int index);

#define EMOTE( x ) void Cmd_Emote_##x( gentity_t *ent );
#include "afj_emotes.h"
#undef EMOTE