#include "g_local.h"

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/*
==================
Cmd_afjAddbot_f

Add a bot
Copy past of g_bot
==================
*/
void Cmd_afjAddbot_f(gentity_t *ent) {
	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amaddbot <botname> [skill 1-5] [team] [msec delay] [altname]\n\"");
		return;
	}
	
	float			skill;
	int				delay;
	char			name[MAX_TOKEN_CHARS];
	char			altname[MAX_TOKEN_CHARS];
	char			string[MAX_TOKEN_CHARS];
	char			team[MAX_TOKEN_CHARS];

	// are bots enabled?
	if (!trap->Cvar_VariableIntegerValue("bot_enable")) {
		return;
	}

	// name
	trap->Argv(1, name, sizeof(name));

	// skill
	trap->Argv(2, string, sizeof(string));
	if (!string[0]) {
		skill = 4;
	}
	else {
		skill = atof(string);
	}

	// team
	trap->Argv(3, team, sizeof(team));

	// delay
	trap->Argv(4, string, sizeof(string));
	if (!string[0]) {
		delay = 0;
	}
	else {
		delay = atoi(string);
	}

	// alternative name
	trap->Argv(5, altname, sizeof(altname));

	G_AddBot(name, skill, team, delay, altname);
}

/*
==================
Cmd_afjAdminStatus_f

Display current admin
==================
*/
qboolean isAdmin(const gentity_t *ent)
{
	char privileges[64];

	Com_sprintf(privileges, sizeof(privileges), "%" PRId64 "", ent->client->pers.afjUser.privileges);

	if (Q_stricmp(afj_logInPrivileges1.string, privileges) == 0)
	{
		return qtrue;
	}
	else if (Q_stricmp(afj_logInPrivileges2.string, privileges) == 0)
	{
		return qtrue;
	}
	else if (Q_stricmp(afj_logInPrivileges3.string, privileges) == 0)
	{
		return qtrue;
	}
	else if (Q_stricmp(afj_logInPrivileges4.string, privileges) == 0)
	{
		return qtrue;
	}
	else if (Q_stricmp(afj_logInPrivileges5.string, privileges) == 0)
	{
		return qtrue;
	}
	else
	{
		return qfalse;
	}
}

char *privilegesString(const gentity_t *ent)
{
	char privileges[64];

	Com_sprintf(privileges, sizeof(privileges), "%" PRId64 "", ent->client->pers.afjUser.privileges);

	if (Q_stricmp(afj_logInPrivileges1.string, privileges) == 0)
	{
		return afj_logInMsg1.string;
	}
	else if (Q_stricmp(afj_logInPrivileges2.string, privileges) == 0)
	{
		return afj_logInMsg2.string;
	}
	else if (Q_stricmp(afj_logInPrivileges3.string, privileges) == 0)
	{
		return afj_logInMsg3.string;
	}
	else if (Q_stricmp(afj_logInPrivileges4.string, privileges) == 0)
	{
		return afj_logInMsg4.string;
	}
	else
	{
		return afj_logInMsg5.string;
	}
}

void Cmd_afjAdminStatus_f(gentity_t *ent)
{
	trap->SendServerCommand(ent - g_entities, "print \"\n\"");
	trap->SendServerCommand(ent - g_entities, "print \"ID Name                 Privileges\n\"");
	trap->SendServerCommand(ent - g_entities, "print \"-- -------------------- --------------------------------------------------\n\"");

	int i;
	
	for (i = 0; i < level.maxclients; ++i)
	{
		if (level.clients[i].pers.connected == CON_DISCONNECTED)
			continue;

		if (isAdmin(&level.gentities[i]))
		{
			trap->SendServerCommand(ent - g_entities, va("print \"%2i %-20.20s %-50.50s\n\"", i, level.clients[i].pers.netname_nocolor, privilegesString(&level.gentities[i])));
		}
	}
}

/*
==================
Cmd_afjBan_f

Ban a client
==================
*/
void AddIP(char *str);

void Cmd_afjBan_f(gentity_t *ent) {
	if (trap->Argc() < 2)
	{
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amban <client>\n\"");
		return;
	}
	char arg1Client[MAX_NETNAME] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));

	const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);

	if (targetClientNum == -1) {
		return;
	}

	if (G_FilterPacket(level.clients[targetClientNum].sess.IP)) {
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is already banned\n\"", level.clients[targetClientNum].sess.IP));
		return;
	}

	AddIP(level.clients[targetClientNum].sess.IP);
	trap->SendServerCommand(ent - g_entities, va("print \"%s (%s) " S_COLOR_YELLOW "is now banned\n\"", level.clients[targetClientNum].pers.netname_nocolor, level.clients[targetClientNum].sess.IP));
}

/*
==================
Cmd_afjBanListIp_f

Display banned ip
==================
*/
void Svcmd_ListIP_ClientPrint_f(gentity_t *ent);

void Cmd_afjBanListIp_f(gentity_t *ent) {
	Svcmd_ListIP_ClientPrint_f(ent);
}

/*
==================
Cmd_afjCapturelimit_f

Change the capturelimit
==================
*/
void Cmd_afjCapturelimit_f(gentity_t *ent) {
	if (trap->Argc() < 2)
	{
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amcapturelimit <limit>\n\"");
		return;
	}

	char arg1Capturelimit[64] = "";

	trap->Argv(1, arg1Capturelimit, sizeof(arg1Capturelimit));

	trap->SendConsoleCommand(EXEC_APPEND, va("capturelimit %s\n", arg1Capturelimit));
}

/*
==================
Cmd_afjClanLogIn_f

Allow a player to log in as a clan member
==================
*/
void Cmd_afjClanLogIn_f(gentity_t *ent) {
	if (trap->Argc() < 2)
	{
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amclanlogin <password>\n\"");
		return;
	}

	char			arg1ClanPassword[64] = "";
	static int		lastTime = 0;

	if (level.time > lastTime + 5000)
	{
		lastTime = level.time;

		trap->Argv(1, arg1ClanPassword, sizeof(arg1ClanPassword));

		if (Q_stricmp(afj_clanPassword.string, arg1ClanPassword) == 0)
		{
			trap->SendServerCommand(-1, va("print \"%s %s\n\"", ent->client->pers.netname, afj_clanLogInMsg.string));
			ent->client->pers.afjUser.isClanMember = qtrue;
		}
	}
	else
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s\n\"", afj_waitBeforeNextTry.string));
	}
}

/*
==================
Cmd_afjClanLogOut_f

Allow a player to log out as a clan member
==================
*/
void Cmd_afjClanLogOut_f(gentity_t *ent) {
	trap->SendServerCommand(-1, va("print \"%s %s\n\"", ent->client->pers.netname, afj_clanLogOutMsg.string));
	ent->client->pers.afjUser.isClanMember = qfalse;
}

/*
==================
Cmd_afjCpMsg_f

From japp (Raz0r)

Display a message in the center of the screen
/afjcpmsg <client (-1 for everyone)> <message>
==================
*/
void Cmd_afjCpMsg_f(gentity_t *ent)
{
	if ( trap->Argc() < 3 ) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amcpmsg <client (-1 for everyone)> <message>\n\"" );
		return;
	}

	char *message, arg1Client[MAX_NETNAME] = "";

	message = ConcatArgs( 2 );
	Q_ConvertLinefeeds(message);

	trap->Argv( 1, arg1Client, sizeof(arg1Client) );

	if (arg1Client[0] == '-' && arg1Client[1] == '1' ) {
		// announce to everyone
		trap->SendServerCommand(-1, va("cp \"%s\"", message));
		if (ent) {
			trap->SendServerCommand(-1, va("print \"%s\n\"", message));
		}
	}
	else {
		// announce to a certain client
		const int targetClientNum = G_ClientFromString( ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT );

		if (targetClientNum == -1 ) {
			return;
		}

		trap->SendServerCommand( targetClientNum, va( "cp \"%s\"", message) );
		trap->SendServerCommand( targetClientNum, va( "print \"%s\n\"", message) );
		
		if (ent) {
			trap->SendServerCommand(ent - g_entities, va("cp\"Relay:\n%s\"", message));
			trap->SendServerCommand(ent - g_entities, va("print \"Relay:\n%s\n\"", message));
		}
	}
}

/*
==================
Cmd_afjDevMap_f

Change the map with cheat enabled
==================
*/
void Cmd_afjDevMap_f(gentity_t *ent) {
	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amdevmap <map>\n\"");
		return;
	}

	char arg1Map[MAX_QPATH] = "";

	trap->Argv(1, arg1Map, sizeof(arg1Map));

	trap->SendConsoleCommand(EXEC_APPEND, va("devmap %s\n", arg1Map));
}

/*
==================
Cmd_afjDropSaber_f

Drop saber self
==================
*/
qboolean saberKnockOutOfHand(gentity_t *saberent, gentity_t *saberOwner, vec3_t velocity);
void Cmd_afjDropSaber_f(gentity_t *ent)
{
	if (!afj_allowDropSaber.integer)
	{
		trap->SendServerCommand(ent - g_entities, "print \"" S_COLOR_YELLOW "amdropsaber not allowed\n\"");
		return;
	}
	if (!ent->client->ps.saberEntityNum) {
		return;
	}
	if (ent->client->ps.saberInFlight) {
		// turn it off in midair
		saberKnockDown(g_entities + ent->client->ps.saberEntityNum, ent, ent);
		return;
	}
	saberKnockOutOfHand(g_entities + ent->client->ps.saberEntityNum, ent, ent->client->ps.velocity);
}

/*
==================
Cmd_afjForceTeam_f

Force a player to change his team
==================
*/
void Cmd_afjForceTeam_f(gentity_t *ent) {
	if (trap->Argc() < 3) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amforceteam <client> <team>\n\"");
		return;
	}

	char arg1Client[MAX_NETNAME] = "", arg2Team[64] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));
	trap->Argv(2, arg2Team, sizeof(arg2Team));
	
	const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);

	if (targetClientNum == -1) {
		return;
	}

	if (level.gentities[targetClientNum].inuse && (g_entities + targetClientNum)->client && level.clients[targetClientNum].pers.connected)
	{
		SetTeam(g_entities + targetClientNum, arg2Team);
	}
}

/*
==================
Cmd_afjFraglimit_f

Change the fraglimit
==================
*/
void Cmd_afjFraglimit_f(gentity_t *ent) {
	if (trap->Argc() < 2)
	{
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amfraglimit <limit>\n\"");
		return;
	}
	
	char arg1Fraglimit[64] = "";

	trap->Argv(1, arg1Fraglimit, sizeof(arg1Fraglimit));

	trap->SendConsoleCommand(EXEC_APPEND, va("fraglimit %s\n", arg1Fraglimit));
}

/*
==================
Cmd_afjGametype_f

Change the gametype
==================
*/
void Cmd_afjGametype_f(gentity_t *ent) {
	if (trap->Argc() == 1)
	{
		if (!level.afjLevel.waitingNextGametype)
		{
			trap->SendServerCommand(ent - g_entities, "print \"Usage: /amgametype <gametype>\n\"");
			trap->SendServerCommand(ent - g_entities, va("print \"" S_COLOR_YELLOW "gametype unchanged " S_COLOR_WHITE "%s\n\"", BG_GetGametypeString(level.gametype)));
			return;
		}
		else
		{
			trap->SendServerCommand(ent - g_entities, "print \"Usage: /amgametype <gametype>\n\"");
			trap->SendServerCommand(ent - g_entities, va("print \"" S_COLOR_YELLOW "next gametype after restart " S_COLOR_WHITE "%s\n\"", BG_GetGametypeString(level.afjLevel.nextGametype)));
			return;
		}
	}

	char arg1Gametype[64] = "";

	trap->Argv(1, arg1Gametype, sizeof(arg1Gametype));

	int gametypeNum = BG_GetGametypeForString(arg1Gametype);

	if (gametypeNum == -1)
	{
		int tempGametype = atoi(arg1Gametype);

		if (tempGametype >= 0 && tempGametype < GT_MAX_GAME_TYPE)
		{
			gametypeNum = tempGametype;
		}
		else
		{
			trap->SendServerCommand(ent - g_entities, va("print \"" S_COLOR_YELLOW "invalid gametype " S_COLOR_WHITE "%s\n\"", BG_GetGametypeString(gametypeNum)));
			return;
		}
	}

	trap->SendConsoleCommand(EXEC_APPEND, va("g_gametype %d\n", gametypeNum));
	level.afjLevel.nextGametype = gametypeNum;
	level.afjLevel.waitingNextGametype = qtrue;
	trap->SendServerCommand(ent - g_entities, va("print \"" S_COLOR_YELLOW "gametype changed to " S_COLOR_WHITE "%s " S_COLOR_YELLOW "restart needed\n\"", BG_GetGametypeString(level.afjLevel.nextGametype)));
}

/*
==================
Cmd_afjIgnore_f

Ignore a player
==================
*/
void Cmd_afjIgnore_f(gentity_t *ent) {
	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amignore <client>\n\"");
		return;
	}
	char	arg1Client[MAX_NETNAME] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));

	const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);

	if (targetClientNum == -1) {
		return;
	}
	ent->client->pers.afjUser.ignoredClients ^= (1 << targetClientNum);
	trap->SendServerCommand(targetClientNum, va("cp \"%s\n%s\n\"", ent->client->pers.netname, (ent->client->pers.afjUser.ignoredClients & (1 << targetClientNum)) ?
		afj_ignoreMsg.string : afj_unIgnoreMsg.string));
	
	trap->SendServerCommand(ent - g_entities, va("print \"%s %s\n\"",
		(ent->client->pers.afjUser.ignoredClients & (1 << targetClientNum)) ? S_COLOR_YELLOW"Ignoring" : S_COLOR_GREEN"Unignoring",
		level.clients[targetClientNum].pers.netname));
}

/*
==================
Cmd_afjIgnoreList_f

List of ignored players
==================
*/
void Cmd_afjIgnoreList_f(gentity_t *ent) {
	trap->SendServerCommand(ent - g_entities, "print \""S_COLOR_YELLOW"Ignore list:\n\"");
	trap->SendServerCommand(ent - g_entities, "print \"\n\"");
	trap->SendServerCommand(ent - g_entities, "print \"ID Name                \n\"");
	trap->SendServerCommand(ent - g_entities, "print \"-- --------------------\n\"");
	
	int i;
	
	for (i = 0; i < level.maxclients; ++i)
	{
		if (ent->client->pers.afjUser.ignoredClients & ( 1 << i ))
			trap->SendServerCommand(ent - g_entities, va("print \"%2i %-20.20s\n\"", i, level.clients[i].pers.netname_nocolor));
	}
}

/*
==================
Cmd_afjKick_f

Kick a player
==================
*/
void Cmd_afjKick_f(gentity_t *ent) {
	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amkick <client>\n\"");
		return;
	}
	char	arg1Client[MAX_NETNAME] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));

	if (!Q_stricmp(arg1Client, "allbots"))
	{
		if (G_CountBotPlayers(-1) == 0)
		{
			trap->SendServerCommand(ent - g_entities, "print \"" S_COLOR_YELLOW "No bots on this server\n\"");
		}
		else
		{
			G_KickAllBots();
		}
		//return;
	}

	const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);

	if (targetClientNum == -1) {
		return;
	}

	const char *reasonOfKick = afj_kickMsg.string;

	trap->DropClient(targetClientNum, reasonOfKick);
}

/*
==================
Cmd_afjKill_f

Kill a player
==================
*/
void G_Kill(gentity_t *ent);

void Cmd_afjKill_f(gentity_t *ent) {
	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amkill <client>\n\"");
		return;
	}

	char arg1Client[MAX_NETNAME] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));

	const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);
	
	if (targetClientNum == -1) {
		return;
	}

	if (level.clients[targetClientNum].ps.pm_type & PM_DEAD)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].sess.sessionTeam == TEAM_SPECTATOR || level.clients[targetClientNum].tempSpectate >= level.time)
	{
		return;
	}

	if (level.clients[targetClientNum].pers.afjUser.isSlept)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is slept, you can't kill this client\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	/*if (!!(level.clients[targetClientNum].ps.eFlags & EF_INVULNERABLE))
	{
		trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_killProtectMsg.string));
		return;
	}*/

	G_Kill(g_entities + targetClientNum);

	trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_killMsg.string));
	trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "killed\n\"", level.clients[targetClientNum].pers.netname_nocolor));
}

/*
==================
Cmd_afjKnockMeDown_f

Knock down self
==================
*/
void Cmd_afjKnockMeDown_f(gentity_t *ent)
{
	G_Knockdown(ent);
}

/*
==================
Cmd_afjLogIn_f

Admin log in
==================
*/

static void Cmd_afjLogin_f(gentity_t *ent) {
	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amlogin <password>\n\"");
		return;
	}

	char			arg1LogInPassword[64] = "";
	static int		lastTime = 0;

	if (level.time > lastTime + 5000)
	{
		lastTime = level.time;

		trap->Argv(1, arg1LogInPassword, sizeof(arg1LogInPassword));

		uint64_t privileges = 0u;

		if (Q_stricmp(afj_logInPassword1.string, arg1LogInPassword) == 0)
		{
			sscanf(afj_logInPrivileges1.string, "%" PRId64, &privileges);
			ent->client->pers.afjUser.privileges = privileges;
			ent->client->ps.electrifyTime = level.time + afj_logInElectrifyTime.integer * 1000;
			trap->SendServerCommand(-1, va("print \"%s " S_COLOR_WHITE "%s\n\"", ent->client->pers.netname, afj_logInMsg1.string));
		}
		else if (Q_stricmp(afj_logInPassword2.string, arg1LogInPassword) == 0)
		{
			sscanf(afj_logInPrivileges2.string, "%" PRId64, &privileges);
			ent->client->pers.afjUser.privileges = privileges;
			ent->client->ps.electrifyTime = level.time + afj_logInElectrifyTime.integer * 1000;
			trap->SendServerCommand(-1, va("print \"%s " S_COLOR_WHITE "%s\n\"", ent->client->pers.netname, afj_logInMsg2.string));
		}
		else if (Q_stricmp(afj_logInPassword3.string, arg1LogInPassword) == 0)
		{
			sscanf(afj_logInPrivileges3.string, "%" PRId64, &privileges);
			ent->client->pers.afjUser.privileges = privileges;
			ent->client->ps.electrifyTime = level.time + afj_logInElectrifyTime.integer * 1000;
			trap->SendServerCommand(-1, va("print \"%s " S_COLOR_WHITE "%s\n\"", ent->client->pers.netname, afj_logInMsg3.string));
		}
		else if (Q_stricmp(afj_logInPassword4.string, arg1LogInPassword) == 0)
		{
			sscanf(afj_logInPrivileges4.string, "%" PRId64, &privileges);
			ent->client->pers.afjUser.privileges = privileges;
			ent->client->ps.electrifyTime = level.time + afj_logInElectrifyTime.integer * 1000;
			trap->SendServerCommand(-1, va("print \"%s " S_COLOR_WHITE "%s\n\"", ent->client->pers.netname, afj_logInMsg4.string));
		}
		else if (Q_stricmp(afj_logInPassword5.string, arg1LogInPassword) == 0)
		{
			sscanf(afj_logInPrivileges5.string, "%" PRId64, &privileges);
			ent->client->pers.afjUser.privileges = privileges;
			ent->client->ps.electrifyTime = level.time + afj_logInElectrifyTime.integer * 1000;
			trap->SendServerCommand(-1, va("print \"%s " S_COLOR_WHITE "%s\n\"", ent->client->pers.netname, afj_logInMsg5.string));
		}
		else
		{
			trap->SendServerCommand(-1, va("print \"" S_COLOR_YELLOW "%s\n\"", afj_logInWrongPwMsg.string));
		}
	}
	else
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s\n\"", afj_waitBeforeNextTry.string));
	}
}

/*
==================
Cmd_afjLogOut_f

Admin log out
==================
*/
static void Cmd_afjLogOut_f(gentity_t *ent) {
	ent->client->pers.afjUser.privileges = 0u;
	trap->SendServerCommand(ent - g_entities, "print \"You have logged out\n\"");
}

/*
==================
Cmd_afjMap_f

Change the map
==================
*/
void Cmd_afjMap_f(gentity_t *ent) {
	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /ammap <map>\n\"");
		return;
	}

	char arg1Map[MAX_QPATH] = "";

	trap->Argv(1, arg1Map, sizeof(arg1Map));

	trap->SendConsoleCommand(EXEC_APPEND, va("map %s\n", arg1Map));
}

/*
==================
Cmd_afjMapRestart_f

Restart the map
==================
*/
void Cmd_afjMapRestart_f(gentity_t *ent) {
	char arg1TimeRestart[64] = "";

	if (trap->Argc() == 2)
	{
		trap->Argv(1, arg1TimeRestart, sizeof(arg1TimeRestart));
	}
	
	trap->SendConsoleCommand(EXEC_APPEND, va("map_restart %s\n", arg1TimeRestart));
}

/*
==================
Cmd_afjNoclip_f

Make a player noclip
==================
*/
void Cmd_afjNoclip_f(gentity_t *ent) {
	char arg1Client[MAX_NETNAME] = "";
	int targetClientNum;

	// can noclip: self, partial name, clientNum
	if (trap->Argc() > 1)
	{
		trap->Argv(1, arg1Client, sizeof(arg1Client));
		targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);
	}
	else
	{
		targetClientNum = ent - g_entities;
	}

	if (targetClientNum == -1) {
		return;
	}

	level.clients[targetClientNum].noclip = !level.clients[targetClientNum].noclip;
	trap->SendServerCommand(-1, va("cp \"%s\nnoclip %s\n\"", level.clients[targetClientNum].pers.netname,
		(level.clients[targetClientNum].noclip) ? "ON" : "OFF"));
	trap->SendServerCommand(ent - g_entities, va("print \"%s "S_COLOR_YELLOW"noclip %s\n\"", level.clients[targetClientNum].pers.netname_nocolor,
		(level.clients[targetClientNum].noclip) ? "ON" : "OFF"));
}

/*
==================
Cmd_afjNotarget_f

Make a player notarget
==================
*/
void Cmd_afjNotarget_f(gentity_t *ent) {
	char arg1Client[MAX_NETNAME] = "";
	int targetClientNum;

	// can notarget: self, partial name, clientNum
	if (trap->Argc() > 1)
	{
		trap->Argv(1, arg1Client, sizeof(arg1Client));
		targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);
	}
	else
	{
		targetClientNum = ent - g_entities;
	}

	if (targetClientNum == -1) {
		return;
	}

	level.gentities[targetClientNum].flags ^= FL_NOTARGET;

	if (!!(level.gentities[targetClientNum].flags & FL_NOTARGET))
	{
		trap->SendServerCommand(-1, va("cp \"%s\nnotarget ON\n\"", level.clients[targetClientNum].pers.netname));
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "notarget ON\n\"", level.clients[targetClientNum].pers.netname_nocolor));
	}
	else
	{
		trap->SendServerCommand(-1, va("cp \"%s\nnotarget OFF\n\"", level.clients[targetClientNum].pers.netname));
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "notarget OFF\n\"", level.clients[targetClientNum].pers.netname_nocolor));
	}
	trap->LinkEntity((sharedEntity_t *)&level.gentities[targetClientNum]);
}

/*
==================
Cmd_afjNpc_f

NPC command
==================
*/
void Cmd_NPC_f(gentity_t *ent);
void Cmd_afjNpc_f(gentity_t *ent) {
	Cmd_NPC_f(ent);
}

/*
==================
Cmd_afjOrigin_f

Display current player origin
==================
*/
void Cmd_afjOrigin_f(gentity_t *ent) {
	trap->SendServerCommand(ent - g_entities, va("print \"Origin: %s\n\"", vtos(ent->client->ps.origin)));
}

/*
==================
Cmd_afjEmpower_f

Give or remove all power to a player
==================
*/
static void removeAllWeaponsStatus(gentity_t *target);
static void giveAllPowerStatus(gentity_t *target)
{
	target->client->pers.afjUser.oldForcePowersKnown = target->client->ps.fd.forcePowersKnown;
	
	int i;
	
	for (i = 0; i < NUM_FORCE_POWERS; ++i)
	{
		target->client->pers.afjUser.oldForcePowerBaseLevel[i] = target->client->ps.fd.forcePowerBaseLevel[i];
		target->client->ps.fd.forcePowerBaseLevel[i] = 3;
		target->client->pers.afjUser.oldForcePowerLevel[i] = target->client->ps.fd.forcePowerLevel[i];
		target->client->ps.fd.forcePowerLevel[i] = 3;
		target->client->ps.fd.forcePowersKnown |= (1 << i);
	}

	if (target->client->pers.afjUser.hasWeapons)
	{
		removeAllWeaponsStatus(target);
	}

	target->client->pers.afjUser.hasPowers = qtrue;
	target->client->ps.eFlags |= EF_BODYPUSH;
}

static void removeAllPowerStatus(gentity_t *target)
{
	target->client->ps.fd.forcePowersKnown = target->client->pers.afjUser.oldForcePowersKnown;
	
	int i;
	
	for (i = 0; i < NUM_FORCE_POWERS; ++i)
	{
		target->client->ps.fd.forcePowerBaseLevel[i] = target->client->pers.afjUser.oldForcePowerBaseLevel[i];
		target->client->ps.fd.forcePowerLevel[i] = target->client->pers.afjUser.oldForcePowerLevel[i];
	}

	target->client->pers.afjUser.hasPowers = qfalse;
	target->client->ps.eFlags &= ~EF_BODYPUSH;
}

void Cmd_afjEmpower_f(gentity_t *ent) {
	char arg1Client[MAX_NETNAME] = "";
	int targetClientNum;

	trap->Argv(1, arg1Client, sizeof(arg1Client));

	if (trap->Argc() > 1)
	{
		trap->Argv(1, arg1Client, sizeof(arg1Client));
		targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);
	}
	else
	{
		targetClientNum = ent - g_entities;
	}

	if (targetClientNum == -1) {
		return;
	}

	if (level.clients[targetClientNum].sess.sessionTeam == TEAM_SPECTATOR || level.clients[targetClientNum].tempSpectate >= level.time)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (!level.clients[targetClientNum].pers.afjUser.hasPowers)
	{
		giveAllPowerStatus(&level.gentities[targetClientNum]);
		trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_empowerMsg.string));
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "%s\n\"", level.clients[targetClientNum].pers.netname_nocolor, afj_empowerMsg.string));
	}
	else
	{
		removeAllPowerStatus(&level.gentities[targetClientNum]);
		trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_remEmpowerMsg.string));
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "%s\n\"", level.clients[targetClientNum].pers.netname_nocolor, afj_remEmpowerMsg.string));
	}
}

/*
==================
Cmd_afjProtect_f

Protect or unprotect a player
==================
*/
void Cmd_afjProtect_f(gentity_t *ent) {
	char arg1Client[MAX_NETNAME] = "";
	int targetClientNum;

	// can protect: self, partial name, clientNum
	if (trap->Argc() > 1)
	{
		trap->Argv(1, arg1Client, sizeof(arg1Client));
		targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);
	}
	else
	{
		targetClientNum =  ent - g_entities;
	}
	
	if (targetClientNum == -1) {
		return;
	}

	if (level.clients[targetClientNum].sess.sessionTeam == TEAM_SPECTATOR || level.clients[targetClientNum].tempSpectate >= level.time)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].ps.pm_type & PM_DEAD)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	level.clients[targetClientNum].ps.eFlags ^= EF_INVULNERABLE;
	level.clients[targetClientNum].invulnerableTimer = !!(level.clients[targetClientNum].ps.eFlags & EF_INVULNERABLE) ? 0x7FFFFFFF : level.time;

	if (!!(level.clients[targetClientNum].ps.eFlags & EF_INVULNERABLE))
	{
		trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_protectMsg.string));
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "protected\n\"", level.clients[targetClientNum].pers.netname_nocolor));
	}
	else
	{
		trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_unProtectMsg.string));
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "unprotected\n\"", level.clients[targetClientNum].pers.netname_nocolor));
	}	
}

/*
==================
Cmd_afjRefuseTele_f

Refuse futur teleport
==================
*/
void Cmd_afjRefuseTele_f(gentity_t *ent) {
	ent->client->pers.afjUser.refuseTele = !ent->client->pers.afjUser.refuseTele;
	trap->SendServerCommand(ent - g_entities, va("print \"refusetele "S_COLOR_YELLOW"%s\n\"", (ent->client->pers.afjUser.refuseTele) ? "ON" : "OFF"));
}

/*
==================
Cmd_afjRemoveIp_f

Remove a banned ip
==================
*/
void Cmd_afjRemoveIp_f(gentity_t *ent) {
	if (trap->Argc() < 2)
	{
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amremoveip <client>\n\"");
		return;
	}
	char arg1Ip[48] = "";

	trap->Argv(1, arg1Ip, sizeof(arg1Ip));

	if (!G_FilterPacket(arg1Ip)) {
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "isn't banned\n\"", arg1Ip));
		return;
	}

	trap->SendConsoleCommand(EXEC_APPEND, va("removeip %s\n", arg1Ip));
	trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is now unbanned\n\"", arg1Ip));
}

/*
==================
Cmd_afjRename_f

Rename a player
==================
*/
void Cmd_afjRename_f(gentity_t *ent) {
	if (trap->Argc() != 3) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amrename <client> <name>\n\"");
		return;
	}

	char arg1Client[MAX_NETNAME] = "", arg2Name[MAX_NETNAME] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));
	trap->Argv(2, arg2Name, sizeof(arg2Name));

	/*if (!Q_stricmp(arg2, "allbots"))
	{
		trap->SendServerCommand(ent - g_entities, "print \"The name " S_COLOR_YELLOW "allbots" S_COLOR_WHITE " is reserved\n\"");
		return;
	}*/

	const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);
	
	if (targetClientNum == -1) {
		return;
	}

	char tempInfo[MAX_INFO_STRING] = "", oldName[MAX_NETNAME] = "";

	Q_strncpyz(oldName, level.clients[targetClientNum].pers.netname, sizeof(oldName));
	ClientCleanName(arg2Name, level.clients[targetClientNum].pers.netname, sizeof(level.clients[targetClientNum].pers.netname));

	if (!strcmp(oldName, level.clients[targetClientNum].pers.netname)) {
		return;
	}

	trap->GetConfigstring(CS_PLAYERS + targetClientNum, tempInfo, sizeof(tempInfo));
	Info_SetValueForKey(tempInfo, "n", level.clients[targetClientNum].pers.netname);
	trap->SetConfigstring(CS_PLAYERS + targetClientNum, tempInfo);

	trap->GetUserinfo(targetClientNum, tempInfo, sizeof(tempInfo));
	Info_SetValueForKey(tempInfo, "name", level.clients[targetClientNum].pers.netname);
	trap->SetUserinfo(targetClientNum, tempInfo);

	trap->SendServerCommand(-1, va("print \"%s" S_COLOR_WHITE " %s %s\n\"", oldName, G_GetStringEdString("MP_SVGAME", "PLRENAME"), level.clients[targetClientNum].pers.netname));
	trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", oldName, afj_renameMsg.string));
}

/*
==================
Cmd_afjSilence_f

Silence a player
==================
*/
void Cmd_afjSilence_f(gentity_t *ent) {
	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amsilence <client>\n\"");
		return;
	}

	char arg1Client[MAX_NETNAME] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));

	const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);

	if (targetClientNum == -1) {
		return;
	}
	if (level.clients[targetClientNum].pers.afjUser.isSilenced)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s already silenced\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	level.clients[targetClientNum].pers.afjUser.isSilenced = qtrue;

	if(ent != g_entities + targetClientNum)
		trap->SendServerCommand(ent - g_entities, va("print \"%s %s\n\"", level.clients[targetClientNum].pers.netname_nocolor, afj_silenceMsg.string));

	trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_silenceMsg.string));
	trap->SendServerCommand(targetClientNum, va("print \"%s %s\n\"", level.clients[targetClientNum].pers.netname_nocolor, afj_silenceMsg.string));
	trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "silenced\n\"", level.clients[targetClientNum].pers.netname_nocolor));
}

/*
==================
Cmd_afjSlap_f

Slap a player
==================
*/
void Cmd_afjSlap_f(gentity_t *ent) {
	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amslap <client>\n\"");
		return;
	}
	char	arg1Client[MAX_NETNAME] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));

	const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);

	if (targetClientNum == -1) {
		return;
	}

	if (level.clients[targetClientNum].sess.sessionTeam == TEAM_SPECTATOR || level.clients[targetClientNum].tempSpectate >= level.time)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].ps.pm_type & PM_DEAD)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].pers.afjUser.isSlept)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is slept, you can't slap this client\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].ps.forceHandExtend == HANDEXTEND_KNOCKDOWN)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "already knockdown\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].hook) {
		Weapon_HookFree(level.clients[targetClientNum].hook);
	}

	vec3_t	newDirection = { 0.45, 0, 0 };
	vec3_t	angles;
	
	VectorCopy(level.clients[targetClientNum].ps.viewangles, angles);
	AngleVectors(angles, newDirection, NULL, NULL);
	VectorInverse(newDirection);
	//Add a little jump
	newDirection[2] += 0.45;
	G_Knockdown(g_entities + targetClientNum);
	G_Throw(g_entities + targetClientNum, newDirection, 40);

	trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_slapMsg.string));
	trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "slapped\n\"", level.clients[targetClientNum].pers.netname_nocolor));
}

/*
==================
Cmd_afjSleep_f

Sleep a player
==================
*/
void WP_DeactivateSaber(gentity_t *self, qboolean clearLength);

void Cmd_afjSleep_f(gentity_t *ent)
{
	if (trap->Argc() < 2)
	{
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amsleep <client>\n\"");
		return;
	}
	char	arg1Client[MAX_NETNAME] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));

	const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);

	if (targetClientNum == -1) {
		return;
	}

	if (level.clients[targetClientNum].sess.sessionTeam == TEAM_SPECTATOR || level.clients[targetClientNum].tempSpectate >= level.time)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].ps.pm_type & PM_DEAD)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].pers.afjUser.isSlept)
	{
		trap->SendServerCommand(ent - g_entities, "print \"" S_COLOR_YELLOW "Player is already slept\n\"");
		return;
	}

	WP_DeactivateSaber(&level.gentities[targetClientNum], qtrue);

	if (level.clients[targetClientNum].hook) {
		Weapon_HookFree(level.clients[targetClientNum].hook);
	}

	VectorScale(level.clients[targetClientNum].ps.velocity, 0.5, level.clients[targetClientNum].ps.velocity);

	BG_ClearRocketLock(&level.clients[targetClientNum].ps);

	level.clients[targetClientNum].ps.forceHandExtend = HANDEXTEND_KNOCKDOWN;
	level.clients[targetClientNum].ps.forceHandExtendTime = INT32_MAX;
	level.clients[targetClientNum].ps.forceDodgeAnim = 0;
	level.clients[targetClientNum].pers.afjUser.isSlept = qtrue;

	trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_sleepMsg.string));
	trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "slept\n\"", level.clients[targetClientNum].pers.netname_nocolor));
}

/*
==================
Cmd_afjStatus_f

Display current player
==================
*/
void Cmd_afjStatus_f(gentity_t *ent) {
	int		total = 0;

	trap->SendServerCommand(ent - g_entities, "print \"\n\"");
	trap->SendServerCommand(ent - g_entities, "print \"ID Ping Name                 Member\n\"");
	trap->SendServerCommand(ent - g_entities, "print \"-- ---- -------------------- ------\n\"");
	
	int i;
	
	for (i = 0; i < level.maxclients; ++i)
	{
		char	state[32] = "", member[32] = "";

		if (level.clients[i].pers.connected == CON_DISCONNECTED)
			continue;

		if (level.clients[i].pers.connected == CON_CONNECTING)
			Q_strncpyz(state, "CNCT", sizeof(state));
		else
			Q_strncpyz(state, va("%4i", level.clients[i].ps.ping < 999 ? level.clients[i].ps.ping : 999), sizeof(state));

		if (level.clients[i].pers.afjUser.isClanMember)
			Q_strncpyz(member, "Yes", sizeof(member));
		else
			memset(member, 0, sizeof(member));

		total += 1;

		trap->SendServerCommand(ent - g_entities, va("print \"%2i %4s %-20.20s "S_COLOR_GREEN"%6s\n\"", i, state, level.clients[i].pers.netname_nocolor, member));
	}
	trap->SendServerCommand(ent - g_entities, va("print \"\nTotal: %d\n\"", total));
}

/*
==================
Cmd_afjStatusIp_f

Display current player ip
==================
*/
void Cmd_afjStatusIp_f(gentity_t *ent)
{
	trap->SendServerCommand(ent - g_entities, "print \"\n\"");
	trap->SendServerCommand(ent - g_entities, "print \"ID Name                 IP\n\"");
	trap->SendServerCommand(ent - g_entities, "print \"-- -------------------- ------------------------------------------------\n\"");
	
	int i;
	
	for (i = 0; i < level.maxclients; ++i)
	{
		if (level.clients[i].pers.connected == CON_DISCONNECTED)
			continue;

		trap->SendServerCommand(ent - g_entities, va("print \"%2i %-20.20s %-48.48s\n\"", i, level.clients[i].pers.netname_nocolor, level.clients[i].sess.IP));
	}
}

/*
==================
Cmd_afjTele_f

Teleport a player
==================
*/
static qboolean isTeleportAllowed_f(gentity_t *player)
{
	if (player->client->pers.afjUser.refuseTele)
	{
		trap->SendServerCommand(player - g_entities, va("print \"%s: "S_COLOR_YELLOW"%s\n\"", player->client->pers.netname_nocolor, afj_refuseTeleportMsg.string));
		return qfalse;
	}
	else
	{
		return qtrue;
	}
}

void Cmd_afjTele_f(gentity_t *ent) {
	if (trap->Argc() == 2)
	{
		char arg1Client[MAX_NETNAME] = "";

		trap->Argv(1, arg1Client, sizeof(arg1Client));

		const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);

		if (targetClientNum == -1 || ent == (g_entities + targetClientNum)) {
			return;
		}

		if (level.clients[targetClientNum].sess.sessionTeam == TEAM_SPECTATOR || level.clients[targetClientNum].tempSpectate >= level.time)
		{
			trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n\"", level.clients[targetClientNum].pers.netname_nocolor));
			return;
		}

		if (level.clients[targetClientNum].ps.pm_type & PM_DEAD)
		{
			trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n\"", level.clients[targetClientNum].pers.netname_nocolor));
			return;
		}

		if (level.gentities[targetClientNum].inuse)
		{
			vec3_t teleportPosition, angles;
			trace_t tr;
			VectorCopy(level.clients[targetClientNum].ps.viewangles, angles);
			angles[0] = angles[2] = 0.0f;
			AngleVectors(angles, angles, NULL, NULL);
			VectorMA(level.clients[targetClientNum].ps.origin, 64.0f, angles, teleportPosition);
			trap->Trace(&tr, level.clients[targetClientNum].ps.origin, NULL, NULL, teleportPosition, targetClientNum, CONTENTS_SOLID, qfalse, 0, 0);
			if (tr.fraction < 1.0f) {
				VectorMA(tr.endpos, 32.0f, tr.plane.normal, teleportPosition);
			}
			else
			{
				VectorCopy(tr.endpos, teleportPosition);
			}
			TeleportPlayer(ent, teleportPosition, ent->client->ps.viewangles);
			trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", ent->client->pers.netname, afj_teleportMsg.string));
			trap->SendServerCommand(ent - g_entities, va("print \"Teleporting to %s\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		}
	}
	else if (trap->Argc() == 3)
	{
		char arg1Client1[MAX_NETNAME] = "", arg2Client2[MAX_NETNAME] = "";

		trap->Argv(1, arg1Client1, sizeof(arg1Client1));
		trap->Argv(2, arg2Client2, sizeof(arg2Client2));

		const int targetClientNum1 = G_ClientFromString(ent, arg1Client1, FINDCL_SUBSTR | FINDCL_PRINT);
		const int targetClientNum2 = G_ClientFromString(ent, arg2Client2, FINDCL_SUBSTR | FINDCL_PRINT);

		if (targetClientNum1 == -1 || targetClientNum2 == -1 || targetClientNum1 == targetClientNum2) {
			return;
		}

		if (level.clients[targetClientNum1].sess.sessionTeam == TEAM_SPECTATOR || level.clients[targetClientNum1].tempSpectate >= level.time)
		{
			trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n\"", level.clients[targetClientNum1].pers.netname_nocolor));
			return;
		}

		if (level.clients[targetClientNum1].ps.pm_type & PM_DEAD)
		{
			trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n\"", level.clients[targetClientNum1].pers.netname_nocolor));
			return;
		}

		if (!isTeleportAllowed_f(g_entities + targetClientNum1))
		{
			return;
		}

		if (level.gentities[targetClientNum1].inuse && level.gentities[targetClientNum2].inuse)
		{
			vec3_t teleportPosition, angles;
			trace_t tr;
			VectorCopy(level.clients[targetClientNum2].ps.viewangles, angles);
			angles[0] = angles[2] = 0.0f;
			AngleVectors(angles, angles, NULL, NULL);
			VectorMA(level.clients[targetClientNum2].ps.origin, 64.0f, angles, teleportPosition);
			trap->Trace(&tr, level.clients[targetClientNum2].ps.origin, NULL, NULL, teleportPosition, targetClientNum2, CONTENTS_SOLID, qfalse, 0, 0);
			if (tr.fraction < 1.0f) {
				VectorMA(tr.endpos, 32.0f, tr.plane.normal, teleportPosition);
			}
			else
			{
				VectorCopy(tr.endpos, teleportPosition);
			}
			TeleportPlayer(g_entities + targetClientNum1, teleportPosition, level.clients[targetClientNum1].ps.viewangles);
			trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", level.clients[targetClientNum1].pers.netname, afj_teleportMsg.string));
			trap->SendServerCommand(ent - g_entities, va("print \"Teleporting %s to %s\n\"", level.clients[targetClientNum1].pers.netname_nocolor, level.clients[targetClientNum2].pers.netname_nocolor));
		}
	}
	else if (trap->Argc() == 4 && ent)
	{
		if (ent->client->sess.sessionTeam == TEAM_SPECTATOR || ent->client->tempSpectate >= level.time)
		{
			trap->SendServerCommand(ent - g_entities, "print \"" S_COLOR_YELLOW "You are a spectator\n\"");
			return;
		}

		if (ent->client->ps.pm_type & PM_DEAD)
		{
			trap->SendServerCommand(ent - g_entities, "print \"" S_COLOR_YELLOW "You are dead\n\"");
			return;
		}

		vec3_t teleportPosition;
		char arg1PositionX[8] = "", arg2PositionY[8] = "", arg3PositionZ[8] = "";

		trap->Argv(1, arg1PositionX, sizeof(arg1PositionX));
		trap->Argv(2, arg2PositionY, sizeof(arg2PositionY));
		trap->Argv(3, arg3PositionZ, sizeof(arg3PositionZ));

		VectorSet(teleportPosition, (float)atof(arg1PositionX), (float)atof(arg2PositionY), (float)atof(arg3PositionZ));

		TeleportPlayer(ent, teleportPosition, ent->client->ps.viewangles);
		trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", ent->client->pers.netname, afj_teleportMsg.string));
	}
	else if (trap->Argc() >= 5)
	{
		char arg1Client[MAX_NETNAME] = "";

		trap->Argv(1, arg1Client, sizeof(arg1Client));

		const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);

		if (targetClientNum == -1) {
			return;
		}

		if (level.clients[targetClientNum].sess.sessionTeam == TEAM_SPECTATOR || level.clients[targetClientNum].tempSpectate >= level.time)
		{
			trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n\"", level.clients[targetClientNum].pers.netname_nocolor));
			return;
		}

		if (level.clients[targetClientNum].ps.pm_type & PM_DEAD)
		{
			trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n\"", level.clients[targetClientNum].pers.netname_nocolor));
			return;
		}

		if (!isTeleportAllowed_f(g_entities + targetClientNum))
		{
			return;
		}

		if (level.gentities[targetClientNum].inuse)
		{
			vec3_t teleportPosition;
			char arg2PositionX[8] = "", arg3PositionY[8] = "", arg4PositionZ[8] = "";

			trap->Argv(2, arg2PositionX, sizeof(arg2PositionX));
			trap->Argv(3, arg3PositionY, sizeof(arg3PositionY));
			trap->Argv(4, arg4PositionZ, sizeof(arg4PositionZ));

			VectorSet(teleportPosition, (float)atof(arg2PositionX), (float)atof(arg3PositionY), (float)atof(arg4PositionZ));

			TeleportPlayer(g_entities + targetClientNum, teleportPosition, level.clients[targetClientNum].ps.viewangles);
			trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_teleportMsg.string));
			trap->SendServerCommand(ent - g_entities, va("print \"Teleporting %s to %s\n\"", level.clients[targetClientNum].pers.netname_nocolor, vtos(teleportPosition)));
		}
	}
}

/*
==================
Cmd_afjTimelimit_f

Change the timelimit
==================
*/
void Cmd_afjTimelimit_f(gentity_t *ent) {
	if (trap->Argc() < 2)
	{
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amtimelimit <limit>\n\"");
		return;
	}
	char arg1Timelimit[64] = "";

	trap->Argv(1, arg1Timelimit, sizeof(arg1Timelimit));

	trap->SendConsoleCommand(EXEC_APPEND, va("timelimit %s\n", arg1Timelimit));
}

/*
==================
Cmd_afjUnIgnoreAll_f

Unignore all player
==================
*/
void Cmd_afjUnIgnoreAll_f(gentity_t *ent) {
	int nbUnIgnored = 0;
	
	int i;
	
	for (i = 0; i < level.maxclients; ++i)
	{
		if (ent->client->pers.afjUser.ignoredClients & (1 << i))
		{
			ent->client->pers.afjUser.ignoredClients &= ~(1 << i);
			++nbUnIgnored;
		}
	}
	trap->SendServerCommand(ent - g_entities, va("print \"\n%d player(s) unignored\n\"", nbUnIgnored));
}

/*
==================
Cmd_afjUnSilence_f

Unsilence a player
==================
*/
void Cmd_afjUnSilence_f(gentity_t *ent) {
	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amunsilence <client>\n\"");
		return;
	}

	char arg1Client[MAX_NETNAME] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));

	const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);

	if (targetClientNum == -1) {
		return;
	}
	if (!level.clients[targetClientNum].pers.afjUser.isSilenced)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s already unsilenced\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	level.clients[targetClientNum].pers.afjUser.isSilenced = qfalse;

	if (ent != g_entities + targetClientNum)
		trap->SendServerCommand(ent - g_entities, va("print \"%s %s\n\"", level.clients[targetClientNum].pers.netname_nocolor, afj_unSilenceMsg.string));

	trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_unSilenceMsg.string));
	trap->SendServerCommand(targetClientNum, va("print \"%s %s\n\"", level.clients[targetClientNum].pers.netname_nocolor, afj_unSilenceMsg.string));
}

/*
==================
Cmd_afjWake_f

Awake a player
==================
*/
void Cmd_afjWake_f(gentity_t *ent)
{
	if (trap->Argc() < 2)
	{
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /amwake <client>\n\"");
		return;
	}
	char	arg1Client[MAX_NETNAME] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));

	const int targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);

	if (targetClientNum == -1) {
		return;
	}

	if (level.clients[targetClientNum].sess.sessionTeam == TEAM_SPECTATOR || level.clients[targetClientNum].tempSpectate >= level.time)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].ps.pm_type & PM_DEAD)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (!level.clients[targetClientNum].pers.afjUser.isSlept)
	{
		trap->SendServerCommand(ent - g_entities, "print \"" S_COLOR_YELLOW "Player is already awake\n\"");
		return;
	}

	level.clients[targetClientNum].ps.forceHandExtendTime = level.time + BG_AnimLength(level.gentities[targetClientNum].localAnimIndex, BOTH_GETUP1);
	level.clients[targetClientNum].ps.forceDodgeAnim = BOTH_GETUP1;
	level.clients[targetClientNum].pers.afjUser.isSlept = qfalse;

	trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_wakeMsg.string));
	trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is now awake\n\"", level.clients[targetClientNum].pers.netname_nocolor));
}

/*
==================
Cmd_afjWeapon_f

Give or remove all weapon with 999 ammo to a player
==================
*/
void giveAllWeaponsStatus(gentity_t *target)
{
	target->client->pers.afjUser.oldWeapons = target->client->ps.stats[STAT_WEAPONS];
	target->client->ps.stats[STAT_WEAPONS] = (1 << (LAST_USEABLE_WEAPON + 1)) - (1 << WP_NONE);

	int i;
	
	for (i = AMMO_BLASTER; i < AMMO_MAX; ++i)
	{
		target->client->pers.afjUser.oldAmmo[i] = target->client->ps.ammo[i];
		target->client->ps.ammo[i] = 999;
	}

	target->client->pers.afjUser.hasWeapons = qtrue;
}

static void removeAllWeaponsStatus(gentity_t *target)
{
	target->client->ps.weapon = WP_SABER;
	target->client->ps.stats[STAT_WEAPONS] = target->client->pers.afjUser.oldWeapons;
	
	int i;
	
	for (i = AMMO_BLASTER; i < AMMO_MAX; ++i)
	{
		target->client->ps.ammo[i] = target->client->pers.afjUser.oldAmmo[i];
	}

	target->client->pers.afjUser.hasWeapons = qfalse;
}

void Cmd_afjWeapon_f(gentity_t *ent) {
	char arg1Client[MAX_NETNAME] = "";
	int targetClientNum;

	trap->Argv(1, arg1Client, sizeof(arg1Client));

	if (trap->Argc() > 1)
	{
		trap->Argv(1, arg1Client, sizeof(arg1Client));
		targetClientNum = G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT);
	}
	else
	{
		targetClientNum = ent - g_entities;
	}

	if (targetClientNum == -1) {
		return;
	}

	if (level.clients[targetClientNum].sess.sessionTeam == TEAM_SPECTATOR || level.clients[targetClientNum].tempSpectate >= level.time)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n\"", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (!level.clients[targetClientNum].pers.afjUser.hasWeapons)
	{
		giveAllWeaponsStatus(&level.gentities[targetClientNum]);
		trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_weaponMsg.string));
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "%s\n\"", level.clients[targetClientNum].pers.netname_nocolor, afj_weaponMsg.string));
	}
	else
	{
		removeAllWeaponsStatus(&level.gentities[targetClientNum]);
		trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_remWeaponMsg.string));
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "%s\n\"", level.clients[targetClientNum].pers.netname_nocolor, afj_remWeaponMsg.string));
	}
}

#define CMD_NOINTERMISSION		(0x0001u)
#define CMD_CHEAT				(0x0002u)
#define CMD_ALIVE				(0x0004u)

#define CMDFAIL_NOINTERMISSION	(0x0001u)
#define CMDFAIL_CHEAT			(0x0002u)
#define CMDFAIL_ALIVE			(0x0004u)

typedef struct adminCommand_s {
	const char		*cmd;
	uint64_t		privilege;
	void			(*func)(gentity_t *ent);
	int				flags;
} adminCommand_t;

static const adminCommand_t adminCommands[] = {
								{ "amaddbot",				PRIV_ADDBOT,				Cmd_afjAddbot_f,			CMD_NOINTERMISSION },
								{ "amadminstatus",			PRIV_ADMINSTATUS,			Cmd_afjAdminStatus_f,		CMD_NOINTERMISSION },
								{ "amban",					PRIV_BAN,					Cmd_afjBan_f,				CMD_NOINTERMISSION },
								{ "ambanlistip",			PRIV_BANLISTIP,				Cmd_afjBanListIp_f,			0 },
								{ "amcapturelimit",			PRIV_CAPTURELIMIT,			Cmd_afjCapturelimit_f,		CMD_NOINTERMISSION },
								{ "amclanlogin",			PRIV_CLANLOGIN,				Cmd_afjClanLogIn_f,			0 },
								{ "amclanlogout",			PRIV_CLANLOGOUT,			Cmd_afjClanLogOut_f,		0 },
								{ "amcpmsg",				PRIV_CPMSG,					Cmd_afjCpMsg_f,				CMD_NOINTERMISSION },
								{ "amdevmap",				PRIV_DEVMAP,				Cmd_afjDevMap_f,			CMD_NOINTERMISSION },
								{ "amdropsaber",			PRIV_DROPSABER,				Cmd_afjDropSaber_f,			CMD_NOINTERMISSION|CMD_ALIVE },
								{ "amforceteam",			PRIV_FORCETEAM,				Cmd_afjForceTeam_f,			CMD_NOINTERMISSION },
								{ "amfraglimit",			PRIV_FRAGLIMIT,				Cmd_afjFraglimit_f,			CMD_NOINTERMISSION },
								{ "amgametype",				PRIV_GAMETYPE,				Cmd_afjGametype_f,			CMD_NOINTERMISSION },
								{ "amignore",				PRIV_IGNORE,				Cmd_afjIgnore_f,			0 },
								{ "amignorelist",			PRIV_IGNORELIST,			Cmd_afjIgnoreList_f,		0 },
								{ "amkick",					PRIV_KICK,					Cmd_afjKick_f,				0 },
								{ "amkill",					PRIV_KILL,					Cmd_afjKill_f,				CMD_NOINTERMISSION },
								{ "amknockmedown",			PRIV_KNOCKMEDOWN,			Cmd_afjKnockMeDown_f,		CMD_NOINTERMISSION|CMD_ALIVE },
								{ "amlogout",				PRIV_LOGOUT,				Cmd_afjLogOut_f,			CMD_NOINTERMISSION },
								{ "ammap",					PRIV_MAP,					Cmd_afjMap_f,				CMD_NOINTERMISSION },
								{ "ammap_restart",			PRIV_MAP_RESTART,			Cmd_afjMapRestart_f,		CMD_NOINTERMISSION },
								{ "amnoclip",				PRIV_NOTCLIP,				Cmd_afjNoclip_f,			CMD_NOINTERMISSION|CMD_ALIVE },
								{ "amnotarget",				PRIV_NOTARGET,				Cmd_afjNotarget_f,			CMD_NOINTERMISSION|CMD_ALIVE },
								{ "amnpc",					PRIV_NPC,					Cmd_afjNpc_f,				CMD_NOINTERMISSION|CMD_ALIVE },
								{ "amorigin",				PRIV_ORIGIN,				Cmd_afjOrigin_f,			CMD_NOINTERMISSION|CMD_ALIVE },
								{ "amempower",				PRIV_EMPOWER,				Cmd_afjEmpower_f,			CMD_NOINTERMISSION },
								{ "amprotect",				PRIV_PROTECT,				Cmd_afjProtect_f,			CMD_NOINTERMISSION },
								{ "amrefusetele",			PRIV_REFUSETELE,			Cmd_afjRefuseTele_f,		0 },
								{ "amremoveip",				PRIV_REMOVEIP,				Cmd_afjRemoveIp_f,			CMD_NOINTERMISSION },
								{ "amrename",				PRIV_RENAME,				Cmd_afjRename_f,			CMD_NOINTERMISSION },
								{ "amsilence",				PRIV_SILENCE,				Cmd_afjSilence_f,			0 },
								{ "amslap",					PRIV_SLAP,					Cmd_afjSlap_f,				CMD_NOINTERMISSION },
								{ "amsleep",				PRIV_SLEEP,					Cmd_afjSleep_f,				CMD_NOINTERMISSION },
								{ "amstatus",				PRIV_STATUS,				Cmd_afjStatus_f,			0 },
								{ "amstatusip",				PRIV_STATUSIP,				Cmd_afjStatusIp_f,			0 },
								{ "amtele",					PRIV_TELE,					Cmd_afjTele_f,				CMD_NOINTERMISSION },
								{ "amtimelimit",			PRIV_TIMELIMIT,				Cmd_afjTimelimit_f,			CMD_NOINTERMISSION },
								{ "amunignoreall",			PRIV_UNIGNOREALL,			Cmd_afjUnIgnoreAll_f,		0 },
								{ "amunsilence",			PRIV_UNSILENCE,				Cmd_afjUnSilence_f,			0 },
								{ "amwake",					PRIV_WAKE,					Cmd_afjWake_f,				0 },
								{ "amweapon",				PRIV_WEAPON,				Cmd_afjWeapon_f,			CMD_NOINTERMISSION },
};
static const size_t numAdminCommands = ARRAY_LEN(adminCommands);

static int cmdcmp(const void *a, const void *b)
{
	return Q_stricmp((const char *)a, ((adminCommand_t*)b)->cmd);
}

qboolean AFJ_HasPrivilege(const gentity_t *ent, uint64_t privilege)
{
	if (ent->client->pers.afjUser.privileges & privilege)
	{
		return qtrue;
	}
	return qfalse;
}

qboolean AFJ_PrivilegesHaveChanged(gentity_t *ent)
{
	char privileges[64];

	Com_sprintf(privileges, sizeof(privileges), "%" PRId64 "", ent->client->pers.afjUser.privileges);

	if (Q_stricmp(afj_logInPrivileges1.string, privileges) == 0)
	{
		return qfalse;
	}
	else if (Q_stricmp(afj_logInPrivileges2.string, privileges) == 0)
	{
		return qfalse;
	}
	else if (Q_stricmp(afj_logInPrivileges3.string, privileges) == 0)
	{
		return qfalse;
	}
	else if (Q_stricmp(afj_logInPrivileges4.string, privileges) == 0)
	{
		return qfalse;
	}
	else if (Q_stricmp(afj_logInPrivileges5.string, privileges) == 0)
	{
		return qfalse;
	}
	else
	{
		ent->client->pers.afjUser.privileges = 0u;
		trap->SendServerCommand(ent - g_entities, va("print \"%s\n\"", afj_privilegesChangedMsg.string));
		return qtrue;
	}
}

// returns the flags that failed to pass, or 0 if the command is allowed to be executed
uint32_t G_AfjCmdValid(const gentity_t *ent, const adminCommand_t *cmd)
{
	if ((cmd->flags & CMD_NOINTERMISSION) && level.intermissiontime)
	{
		return CMDFAIL_NOINTERMISSION;
	}

	if ((cmd->flags & CMD_CHEAT) && !sv_cheats.integer)
	{
		return CMDFAIL_CHEAT;
	}

	if ((cmd->flags & CMD_ALIVE) && (ent->health <= 0 || ent->client->tempSpectate >= level.time || ent->client->sess.sessionTeam == TEAM_SPECTATOR))
	{
		return CMDFAIL_ALIVE;
	}
	return 0u;
}

// handle admin related commands.
// return true if the command exists and/or everything was handled fine.
// return false if command didn't exist, so we can tell them.
qboolean AFJ_HandleCommands(gentity_t *ent, const char *cmd)
{
	adminCommand_t *command = NULL;

	/*
	if (ent == NULL)
	{ // call from console
		command = (adminCommand_t *)bsearch(cmd, adminCommands, numAdminCommands, sizeof(adminCommands[0]), cmdcmp);
		
		if (command)
		{
			command->func(NULL);
			return qtrue;
		}
	}
	else
	*/

	if (!Q_stricmp(cmd, "amlogin"))
	{
		Cmd_afjLogin_f(ent);
		return qtrue;
	}

	command = (adminCommand_t *)bsearch(cmd, adminCommands, numAdminCommands, sizeof(adminCommands[0]), cmdcmp);

	if (!command)
	{
		return qfalse;
	}
	else if (!AFJ_HasPrivilege(ent, command->privilege))
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s\n\"", afj_privilegesMsg.string));
		return qtrue;
	}

	if (AFJ_PrivilegesHaveChanged(ent))
	{
		return qtrue;
	}

	switch (G_AfjCmdValid(ent, command))
	{
	case 0:
		command->func(ent);
		break;

	case CMDFAIL_NOINTERMISSION:
		trap->SendServerCommand(ent - g_entities, va("print \"%s (%s)\n\"", G_GetStringEdString("MP_SVGAME", "CANNOT_TASK_INTERMISSION"), cmd));
		break;

	case CMDFAIL_CHEAT:
		trap->SendServerCommand(ent - g_entities, va("print \"%s\n\"", G_GetStringEdString("MP_SVGAME", "NOCHEATS")));
		break;

	case CMDFAIL_ALIVE:
		trap->SendServerCommand(ent - g_entities, va("print \"%s\n\"", G_GetStringEdString("MP_SVGAME", "MUSTBEALIVE")));
		break;

	default:
		break;
	}
	return qtrue;
}
