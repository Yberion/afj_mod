#include "g_local.h"

/*
==================
Cmd_afjClanLogin_f

Allow a player to log in as a clan member
==================
*/
void Cmd_afjClanLogIn_f(gentity_t *ent) {
	char	clanPassword[64] = "";
	static int		lastTime = 0;

	if (level.time > lastTime + 5000)
	{
		lastTime = level.time;

		if (trap->Argc() > 2)
		{
			return;
		}
		trap->Argv(1, clanPassword, sizeof(clanPassword));

		if (Q_stricmp(afj_clanPassword.string, clanPassword) == 0)
		{
			trap->SendServerCommand(-1, va("print \"%s %s\n\"", ent->client->pers.netname, afj_clanLogInMsg.string));
			ent->client->pers.afjUser.IsClanMember = qtrue;
		}
	}
	else
	{
		trap->SendServerCommand(ent - g_entities, va("print \"%s\n\"", afj_waitBeforeNextTry.string));
	}

}

/*
==================
Cmd_afjClanLogout_f

Allow a player to log out as a clan member
==================
*/
void Cmd_afjClanLogOut_f(gentity_t *ent) {
	if (trap->Argc() > 1)
	{
		return;
	}
	trap->SendServerCommand(-1, va("print \"%s %s\n\"", ent->client->pers.netname, afj_clanLogOutMsg.string));
	ent->client->pers.afjUser.IsClanMember = qfalse;
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

		if (cl->pers.afjUser.IsClanMember)
			strcpy(Member, "Yes");
		else
			memset(Member, 0, sizeof(Member));

		total += 1;

		trap->SendServerCommand(ent - g_entities, va("print \"%2i %4s %-20.20s "S_COLOR_GREEN"%6s\n\"", i, state, cl->pers.netname_nocolor, Member));
	}
	trap->SendServerCommand(ent - g_entities, va("print \"\nTotal: %i\n\"", total));
}