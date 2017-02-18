#include "g_local.h"

/*
==================
Cmd_afjAddbot_f

Add a bot
Copy past of g_bot
==================
*/
void Cmd_afjAddbot_f(gentity_t *ent) {
	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjaddbot <botname> [skill 1-5] [team] [msec delay] [altname]\n\"");
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
Cmd_afjCapturelimit_f

Change the capturelimit
==================
*/
void Cmd_afjCapturelimit_f(gentity_t *ent) {
	if (trap->Argc() < 2)
	{
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjcapturelimit <limit>\n\"");
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
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjclanlogin <password>\n\"");
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
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjcpmsg <client (-1 for everyone)> <message>\n" );
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
	if (!ent) {
		trap->Print("Use: /devmap\n");
		return;
	}

	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjdevmap <map>\n");
		return;
	}

	char arg1Map[MAX_QPATH] = "";

	trap->Argv(1, arg1Map, sizeof(arg1Map));

	trap->SendConsoleCommand(EXEC_APPEND, va("devmap %s\n", arg1Map));
}

/*
==================
cmd_afjDropSaber_f

Drop saber self
==================
*/
qboolean saberKnockOutOfHand(gentity_t *saberent, gentity_t *saberOwner, vec3_t velocity);
void cmd_afjDropSaber_f(gentity_t *ent)
{
	if (!afj_allowDropSaber.integer)
	{
		trap->SendServerCommand(ent - g_entities, "print \"" S_COLOR_YELLOW "afjdropsaber not allowed\n");
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
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjforceteam <client> <team>\n");
		return;
	}

	char arg1Client[64] = "", arg2Team[64] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));
	trap->Argv(2, arg2Team, sizeof(arg2Team));
	
	const int targetClientNum = (trap->Argc() > 1) ? G_ClientFromString(ent, arg1Client, FINDCL_SUBSTR | FINDCL_PRINT) : ent - g_entities;

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
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjfraglimit <limit>\n\"");
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
			trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjgametype <gametype>\n\"");
			trap->SendServerCommand(ent - g_entities, va("print \"" S_COLOR_YELLOW "gametype unchanged " S_COLOR_WHITE "%s\n\"", BG_GetGametypeString(level.gametype)));
			return;
		}
		else
		{
			trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjgametype <gametype>\n\"");
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
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjignore <client>\n");
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

	for (int i = 0; i < level.maxclients; ++i)
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
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjkick <client>\n");
		return;
	}
	char	arg1Client[MAX_NETNAME] = "";

	trap->Argv(1, arg1Client, sizeof(arg1Client));

	if (!Q_stricmp(arg1Client, "allbots"))
	{
		if (G_CountBotPlayers(-1) == 0)
		{
			trap->SendServerCommand(ent - g_entities, "print \"" S_COLOR_YELLOW "No bots on this server\n");
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
void Cmd_Kill_f(gentity_t *ent);

void Cmd_afjKill_f(gentity_t *ent) {
	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjkill <client>\n");
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
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].sess.sessionTeam == TEAM_SPECTATOR || level.clients[targetClientNum].tempSpectate >= level.time)
	{
		return;
	}

	/*if (!!(level.clients[targetClientNum].ps.eFlags & EF_INVULNERABLE))
	{
		trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_killProtectMsg.string));
		return;
	}*/

	Cmd_Kill_f(g_entities + targetClientNum);
	trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_killMsg.string));
	trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "killed\n\"", level.clients[targetClientNum].pers.netname_nocolor));
}

/*
==================
cmd_afjKnockMeDown_f

Knock down self
==================
*/
void Cmd_afjKnockMeDown_f(gentity_t *ent)
{
	if (ent->client->ps.pm_type & PM_DEAD)
	{
		trap->SendServerCommand(ent - g_entities, "print \"" S_COLOR_YELLOW "You are dead\n");
		return;
	}
	G_Knockdown(ent);
}

/*
==================
Cmd_afjMap_f

Change the map
==================
*/
void Cmd_afjMap_f(gentity_t *ent) {
	if (!ent) {
		trap->Print("Use: /map\n");
		return;
	}

	if (trap->Argc() < 2) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjmap <map>\n");
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
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].ps.pm_type & PM_DEAD)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n", level.clients[targetClientNum].pers.netname_nocolor));
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
Cmd_afjRename_f

Rename a player
==================
*/
void Cmd_afjRename_f(gentity_t *ent) {
	if (trap->Argc() != 3) {
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjrename <client> <name>\n");
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
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjsilence <client>\n");
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
		trap->SendServerCommand(ent - g_entities, va("print \"%s already silenced\n", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	level.clients[targetClientNum].pers.afjUser.isSilenced = qtrue;

	if(ent != g_entities + targetClientNum)
		trap->SendServerCommand(ent - g_entities, va("print \"%s %s\n\"", level.clients[targetClientNum].pers.netname_nocolor, afj_SilenceMsg.string));

	trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_SilenceMsg.string));
	trap->SendServerCommand(targetClientNum, va("print \"%s %s\n\"", level.clients[targetClientNum].pers.netname_nocolor, afj_SilenceMsg.string));
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
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjslap <client>\n");
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
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].ps.pm_type & PM_DEAD)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	if (level.clients[targetClientNum].ps.forceHandExtend == HANDEXTEND_KNOCKDOWN)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "already knockdown\n", level.clients[targetClientNum].pers.netname_nocolor));
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

	trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_SlapMsg.string));
	trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "slapped\n\"", level.clients[targetClientNum].pers.netname_nocolor));
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

	for (int i = 0; i < level.maxclients; ++i)
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
Cmd_afjTele_f

Teleport a player
==================
*/
qboolean isTeleportAllowed_f(gentity_t *player)
{
	if (player->client->pers.afjUser.refuseTele)
	{
		trap->SendServerCommand(player - g_entities, va("print \"%s: "S_COLOR_YELLOW"%s\n\"", player->client->pers.netname_nocolor, afj_RefuseTeleportMsg.string));
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
			trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n", level.clients[targetClientNum].pers.netname_nocolor));
			return;
		}

		if (level.clients[targetClientNum].ps.pm_type & PM_DEAD)
		{
			trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n", level.clients[targetClientNum].pers.netname_nocolor));
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
			trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", ent->client->pers.netname, afj_TeleportMsg.string));
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
			trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n", level.clients[targetClientNum1].pers.netname_nocolor));
			return;
		}

		if (level.clients[targetClientNum1].ps.pm_type & PM_DEAD)
		{
			trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n", level.clients[targetClientNum1].pers.netname_nocolor));
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
			trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", level.clients[targetClientNum1].pers.netname, afj_TeleportMsg.string));
			trap->SendServerCommand(ent - g_entities, va("print \"Teleporting %s to %s\n\"", level.clients[targetClientNum1].pers.netname_nocolor, level.clients[targetClientNum2].pers.netname_nocolor));
		}
	}
	else if (trap->Argc() == 4 && ent)
	{
		if (ent->client->sess.sessionTeam == TEAM_SPECTATOR || ent->client->tempSpectate >= level.time)
		{
			trap->SendServerCommand(ent - g_entities, "print \"" S_COLOR_YELLOW "You are a spectator\n");
			return;
		}

		if (ent->client->ps.pm_type & PM_DEAD)
		{
			trap->SendServerCommand(ent - g_entities, "print \"" S_COLOR_YELLOW "You are dead\n");
			return;
		}

		vec3_t teleportPosition;
		char arg1PositionX[8] = "", arg2PositionY[8] = "", arg3PositionZ[8] = "";

		trap->Argv(1, arg1PositionX, sizeof(arg1PositionX));
		trap->Argv(2, arg2PositionY, sizeof(arg2PositionY));
		trap->Argv(3, arg3PositionZ, sizeof(arg3PositionZ));

		VectorSet(teleportPosition, (float)atof(arg1PositionX), (float)atof(arg2PositionY), (float)atof(arg3PositionZ));

		TeleportPlayer(ent, teleportPosition, ent->client->ps.viewangles);
		trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", ent->client->pers.netname, afj_TeleportMsg.string));
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
			trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is a spectator\n", level.clients[targetClientNum].pers.netname_nocolor));
			return;
		}

		if (level.clients[targetClientNum].ps.pm_type & PM_DEAD)
		{
			trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "is dead\n", level.clients[targetClientNum].pers.netname_nocolor));
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
			trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_TeleportMsg.string));
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
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjtimelimit <limit>\n\"");
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
	for (int i = 0; i < level.maxclients; i++)
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
		trap->SendServerCommand(ent - g_entities, "print \"Usage: /afjunsilence <client>\n");
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
		trap->SendServerCommand(ent - g_entities, va("print \"%s already unsilenced\n", level.clients[targetClientNum].pers.netname_nocolor));
		return;
	}

	level.clients[targetClientNum].pers.afjUser.isSilenced = qfalse;

	if (ent != g_entities + targetClientNum)
		trap->SendServerCommand(ent - g_entities, va("print \"%s %s\n\"", level.clients[targetClientNum].pers.netname_nocolor, afj_UnSilenceMsg.string));

	trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClientNum].pers.netname, afj_UnSilenceMsg.string));
	trap->SendServerCommand(targetClientNum, va("print \"%s %s\n\"", level.clients[targetClientNum].pers.netname_nocolor, afj_UnSilenceMsg.string));
}