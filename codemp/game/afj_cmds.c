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

	char capturelimit[64] = "";

	trap->Argv(1, capturelimit, sizeof(capturelimit));

	trap->SendConsoleCommand(EXEC_APPEND, va("capturelimit %s\n", capturelimit));
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
	
	char	clanPassword[64] = "";
	static int		lastTime = 0;

	if (level.time > lastTime + 5000)
	{
		lastTime = level.time;

		trap->Argv(1, clanPassword, sizeof(clanPassword));

		if (Q_stricmp(afj_clanPassword.string, clanPassword) == 0)
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

	char *msg, arg1[MAX_NETNAME] = "";

	msg = ConcatArgs( 2 );
	Q_ConvertLinefeeds( msg );

	trap->Argv( 1, arg1, sizeof(arg1) );

	if ( arg1[0] == '-' && arg1[1] == '1' ) {
		// announce to everyone
		trap->SendServerCommand(-1, va("cp \"%s\"", msg));
		if (ent) {
			trap->SendServerCommand(-1, va("print \"%s\n\"", msg));
		}
	}
	else {
		// announce to a certain client
		const int targetClient = G_ClientFromString( ent, arg1, FINDCL_SUBSTR | FINDCL_PRINT );

		if ( targetClient == -1 ) {
			return;
		}

		trap->SendServerCommand( targetClient, va( "cp \"%s\"", msg ) );
		trap->SendServerCommand( targetClient, va( "print \"%s\n\"", msg ) );
		
		if (ent) {
			trap->SendServerCommand(ent - g_entities, va("cp\"Relay:\n%s\"", msg));
			trap->SendServerCommand(ent - g_entities, va("print \"Relay:\n%s\n\"", msg));
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

	char map[MAX_QPATH] = "";

	trap->Argv(1, map, sizeof(map));

	trap->SendConsoleCommand(EXEC_APPEND, va("devmap %s\n", map));
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

	char arg1[64] = "", arg2[64] = "";
	int targetClient;
	gentity_t *targ;

	trap->Argv(1, arg1, sizeof(arg1));
	trap->Argv(2, arg2, sizeof(arg2));
	
	targetClient = (trap->Argc() > 1) ? G_ClientFromString(ent, arg1, FINDCL_SUBSTR | FINDCL_PRINT) : ent - g_entities;

	if (targetClient == -1) {
		return;
	}

	targ = &g_entities[targetClient];

	if (targ->inuse && targ->client && targ->client->pers.connected)
	{
		SetTeam(targ, arg2);
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
	
	char fraglimit[64] = "";

	trap->Argv(1, fraglimit, sizeof(fraglimit));

	trap->SendConsoleCommand(EXEC_APPEND, va("fraglimit %s\n", fraglimit));
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

	char argGametype[64] = "";
	int gametypeNum, tempGametype;

	trap->Argv(1, argGametype, sizeof(argGametype));

	gametypeNum = BG_GetGametypeForString(argGametype);

	if (gametypeNum == -1)
	{
		tempGametype = atoi(argGametype);
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
	int clientNum;
	char	arg1[MAX_NETNAME] = "";

	trap->Argv(1, arg1, sizeof(arg1));

	clientNum = G_ClientFromString(ent, arg1, FINDCL_SUBSTR | FINDCL_PRINT);

	if (clientNum == -1) {
		return;
	}
	ent->client->pers.afjUser.ignoredClients ^= (1 << clientNum);
	trap->SendServerCommand(clientNum, va("cp \"%s\n%s\n\"", ent->client->pers.netname, (ent->client->pers.afjUser.ignoredClients & (1 << clientNum)) ?
		afj_ignoreMsg.string : afj_unIgnoreMsg.string));
	
	trap->SendServerCommand(ent - g_entities, va("print \"%s %s\n\"",
		(ent->client->pers.afjUser.ignoredClients & (1 << clientNum)) ? S_COLOR_YELLOW"Ignoring" : S_COLOR_GREEN"Unignoring",
		g_entities[clientNum].client->pers.netname));
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

	for (int i = 0; i < level.maxclients; i++)
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

	const char *reason = afj_kickMsg.string;
	int clientNum;
	char	arg1[MAX_NETNAME] = "";

	trap->Argv(1, arg1, sizeof(arg1));

	if (!Q_stricmp(arg1, "allbots"))
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

	clientNum = G_ClientFromString(ent, arg1, FINDCL_SUBSTR | FINDCL_PRINT);

	if (clientNum == -1) {
		return;
	}
	trap->DropClient(clientNum, reason);
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

	char arg1[MAX_NETNAME] = "";
	int clientNum;
	gentity_t *targetEnt = NULL;

	trap->Argv(1, arg1, sizeof(arg1));

	clientNum = G_ClientFromString(ent, arg1, FINDCL_SUBSTR | FINDCL_PRINT);
	
	if (clientNum == -1) {
		return;
	}

	if (level.clients[clientNum].sess.sessionTeam == TEAM_SPECTATOR || level.clients[clientNum].tempSpectate >= level.time)
	{
		return;
	}

	targetEnt = g_entities + clientNum;

	/*if (!!(targetEnt->client->ps.eFlags & EF_INVULNERABLE))
	{
		trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", targetEnt->client->pers.netname, afj_killProtectMsg.string));
		return;
	}*/

	Cmd_Kill_f(targetEnt);
	trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", targetEnt->client->pers.netname, afj_killMsg.string));
	trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "killed\n\"", targetEnt->client->pers.netname_nocolor));
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

	char map[MAX_QPATH] = "";

	trap->Argv(1, map, sizeof(map));

	trap->SendConsoleCommand(EXEC_APPEND, va("map %s\n", map));
}

/*
==================
Cmd_afjMapRestart_f

Restart the map
==================
*/
void Cmd_afjMapRestart_f(gentity_t *ent) {
	char timeRestart[64] = "";

	if (trap->Argc() == 2)
	{
		trap->Argv(1, timeRestart, sizeof(timeRestart));
	}
	
	trap->SendConsoleCommand(EXEC_APPEND, va("map_restart %s\n", timeRestart));
}

/*
==================
Cmd_afjNoclip_f

Make a player noclip
==================
*/
void Cmd_afjNoclip_f(gentity_t *ent) {
	char arg1[MAX_NETNAME] = "";
	int targetClient;
	gentity_t *targ;

	// can noclip: self, partial name, clientNum
	if (trap->Argc() > 1) {
		trap->Argv(1, arg1, sizeof(arg1));
		targetClient = G_ClientFromString(ent, arg1, FINDCL_SUBSTR | FINDCL_PRINT);
	}
	else
	{
		targetClient = ent - g_entities;
	}

	if (targetClient == -1) {
		return;
	}

	targ = &g_entities[targetClient];

	targ->client->noclip = !targ->client->noclip;
	trap->SendServerCommand(-1, va("cp \"%s\nnoclip %s\n\"", targ->client->pers.netname,
		(targ->client->noclip) ? "ON" : "OFF"));
	trap->SendServerCommand(ent - g_entities, va("print \"%s "S_COLOR_YELLOW"noclip %s\n\"", targ->client->pers.netname_nocolor,
		(targ->client->noclip) ? "ON" : "OFF"));
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
	char arg1[MAX_NETNAME] = "";
	int targetClient;
	gentity_t *targ;

	// can protect: self, partial name, clientNum
	if (trap->Argc() > 1) {
		trap->Argv(1, arg1, sizeof(arg1));
		targetClient = G_ClientFromString(ent, arg1, FINDCL_SUBSTR | FINDCL_PRINT);
	}
	else
	{
		targetClient =  ent - g_entities;
	}
	
	if (targetClient == -1) {
		return;
	}

	targ = &g_entities[targetClient];

	targ->client->ps.eFlags ^= EF_INVULNERABLE;
	targ->client->invulnerableTimer = !!(targ->client->ps.eFlags & EF_INVULNERABLE) ? 0x7FFFFFFF : level.time;

	if (!!(targ->client->ps.eFlags & EF_INVULNERABLE))
	{
		trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", targ->client->pers.netname, afj_protectMsg.string));
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "protected\n\"", targ->client->pers.netname_nocolor));
	}
	else
	{
		trap->SendServerCommand(-1, va("cp \"%s\n%s\n\"", targ->client->pers.netname, afj_unProtectMsg.string));
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "unprotected\n\"", targ->client->pers.netname_nocolor));
	}	
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

	char arg1[MAX_NETNAME] = "", arg2[MAX_NETNAME] = "", oldName[MAX_NETNAME] = "";
	char tempInfo[MAX_INFO_STRING] = "";
	int targetClient;
	gentity_t *targ = NULL;

	trap->Argv(1, arg1, sizeof(arg1));
	trap->Argv(2, arg2, sizeof(arg2));

	/*if (!Q_stricmp(arg2, "allbots"))
	{
		trap->SendServerCommand(ent - g_entities, "print \"The name " S_COLOR_YELLOW "allbots" S_COLOR_WHITE " is reserved\n\"");
		return;
	}*/

	targetClient = G_ClientFromString(ent, arg1, FINDCL_SUBSTR | FINDCL_PRINT);
	
	if (targetClient == -1) {
		return;
	}

	targ = g_entities + targetClient;

	Q_strncpyz(oldName, targ->client->pers.netname, sizeof(oldName));
	ClientCleanName(arg2, targ->client->pers.netname, sizeof(targ->client->pers.netname));

	if (!strcmp(oldName, targ->client->pers.netname)) {
		return;
	}

	trap->GetConfigstring(CS_PLAYERS + targetClient, tempInfo, sizeof(tempInfo));
	Info_SetValueForKey(tempInfo, "n", targ->client->pers.netname);
	trap->SetConfigstring(CS_PLAYERS + targetClient, tempInfo);

	trap->GetUserinfo(targetClient, tempInfo, sizeof(tempInfo));
	Info_SetValueForKey(tempInfo, "name", targ->client->pers.netname);
	trap->SetUserinfo(targetClient, tempInfo);

	trap->SendServerCommand(-1, va("print \"%s" S_COLOR_WHITE " %s %s\n\"", oldName, G_GetStringEdString("MP_SVGAME", "PLRENAME"), targ->client->pers.netname));
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

	char arg1[MAX_NETNAME] = "";
	int targetClient;

	trap->Argv(1, arg1, sizeof(arg1));

	targetClient = G_ClientFromString(ent, arg1, FINDCL_SUBSTR | FINDCL_PRINT);

	if (targetClient == -1) {
		return;
	}
	if (level.clients[targetClient].pers.afjUser.isSilenced)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s already silenced\n", level.clients[targetClient].pers.netname_nocolor));
		return;
	}

	level.clients[targetClient].pers.afjUser.isSilenced = qtrue;

	if(ent != g_entities + targetClient)
		trap->SendServerCommand(ent - g_entities, va("print \"%s %s\n\"", level.clients[targetClient].pers.netname_nocolor, afj_SilenceMsg.string));

	trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClient].pers.netname, afj_SilenceMsg.string));
	trap->SendServerCommand(targetClient, va("print \"%s %s\n\"", level.clients[targetClient].pers.netname_nocolor, afj_SilenceMsg.string));
	trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "silenced\n\"", level.clients[targetClient].pers.netname_nocolor));
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
	char	arg1[MAX_NETNAME] = "";
	int		clientNum;
	gentity_t *targ = NULL;
	vec3_t newDirection = { 0.45, 0, 0 };
	vec3_t angs;

	trap->Argv(1, arg1, sizeof(arg1));

	clientNum = G_ClientFromString(ent, arg1, FINDCL_SUBSTR | FINDCL_PRINT);

	if (clientNum == -1) {
		return;
	}

	targ = g_entities + clientNum;

	if (targ->client->ps.forceHandExtend == HANDEXTEND_KNOCKDOWN)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "already knockdown\n", targ->client->pers.netname_nocolor));
		return;
	}

	if (targ->client->hook) {
		Weapon_HookFree(ent->client->hook);
	}
	
	VectorCopy(targ->client->ps.viewangles, angs);
	AngleVectors(angs, newDirection, NULL, NULL);
	VectorInverse(newDirection);
	//Add a little jump
	newDirection[2] += 0.45;
	G_Knockdown(targ);
	G_Throw(targ, newDirection, 40);

	trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", targ->client->pers.netname, afj_SlapMsg.string));
	trap->SendServerCommand(ent - g_entities, va("print \"%s " S_COLOR_YELLOW "slapped\n\"", targ->client->pers.netname_nocolor));
}

/*
==================
Cmd_afjStatus_f

Display current player
==================
*/
void Cmd_afjStatus_f(gentity_t *ent) {
	gclient_t	*cl;
	int	i, total = 0;
	char state[32] = "", Member[2] = "";

	trap->SendServerCommand(ent - g_entities, "print \"\n\"");
	trap->SendServerCommand(ent - g_entities, "print \"ID Ping Name                 Member\n\"");
	trap->SendServerCommand(ent - g_entities, "print \"-- ---- -------------------- ------\n\"");

	for (i = 0, cl = level.clients; i < level.maxclients; i++, cl++)
	{
		if (cl->pers.connected == CON_DISCONNECTED)
			continue;

		if (cl->pers.connected == CON_CONNECTING)
			strcpy(state, "CNCT");
		else
			strcpy(state, va("%4i", cl->ps.ping < 999 ? cl->ps.ping : 999));

		if (cl->pers.afjUser.isClanMember)
			strcpy(Member, "Yes");
		else
			memset(Member, 0, sizeof(Member));

		total += 1;

		trap->SendServerCommand(ent - g_entities, va("print \"%2i %4s %-20.20s "S_COLOR_GREEN"%6s\n\"", i, state, cl->pers.netname_nocolor, Member));
	}
	trap->SendServerCommand(ent - g_entities, va("print \"\nTotal: %d\n\"", total));
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
	char timelimit[64] = "";

	trap->Argv(1, timelimit, sizeof(timelimit));

	trap->SendConsoleCommand(EXEC_APPEND, va("timelimit %s\n", timelimit));
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

	char arg1[MAX_NETNAME] = "";
	int targetClient;

	trap->Argv(1, arg1, sizeof(arg1));

	targetClient = G_ClientFromString(ent, arg1, FINDCL_SUBSTR | FINDCL_PRINT);

	if (targetClient == -1) {
		return;
	}
	if (!level.clients[targetClient].pers.afjUser.isSilenced)
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s already unsilenced\n", level.clients[targetClient].pers.netname_nocolor));
		return;
	}

	level.clients[targetClient].pers.afjUser.isSilenced = qfalse;

	if (ent != g_entities + targetClient)
		trap->SendServerCommand(ent - g_entities, va("print \"%s %s\n\"", level.clients[targetClient].pers.netname_nocolor, afj_UnSilenceMsg.string));

	trap->SendServerCommand(-1, va("cp \"%s" S_COLOR_WHITE "\n%s\n\"", level.clients[targetClient].pers.netname, afj_UnSilenceMsg.string));
	trap->SendServerCommand(targetClient, va("print \"%s %s\n\"", level.clients[targetClient].pers.netname_nocolor, afj_UnSilenceMsg.string));
}