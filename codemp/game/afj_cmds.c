#include "g_local.h"

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
Cmd_afjClanLogOut_f

Allow a player to log out as a clan member
==================
*/
void Cmd_afjClanLogOut_f(gentity_t *ent) {
	trap->SendServerCommand(-1, va("print \"%s %s\n\"", ent->client->pers.netname, afj_clanLogOutMsg.string));
	ent->client->pers.afjUser.IsClanMember = qfalse;
}

/*
==================
Cmd_afjCpMsg_f

From japp (Raz0r)

Display a message in the center of the screen
/afjcpmsg <clientnum (-1 for everyone)> <message>
==================
*/
void Cmd_afjCpMsg_f(gentity_t *ent)
{
	char *msg, arg1[MAX_NETNAME] = "";

	if ( trap->Argc() < 3 ) {
		trap->SendServerCommand(ent - g_entities, "Usage:  /afjcpmsg <clientnum (-1 for everyone)> <message>\n" );
		return;
	}

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
Cmd_afjKick_f

Kick a player
==================
*/
void Cmd_afjKick_f(gentity_t *ent) {
	if (trap->Argc() == 1) {
		trap->SendServerCommand(ent - g_entities, "Usage:  /afjkick <clientnum>\n");
		return;
	}

	const char *reason = afj_kickMsg.string;
	int clientNum;
	char	arg1[64] = "";

	trap->Argv(1, arg1, sizeof(arg1));

	clientNum = G_ClientFromString(ent, arg1, FINDCL_SUBSTR | FINDCL_PRINT);

	if (clientNum == -1) {
		return;
	}
	trap->DropClient(clientNum, reason);
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