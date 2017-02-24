#ifdef XCVAR_PROTO
	#define XCVAR_DEF( name, defVal, update, flags, announce ) extern vmCvar_t name;
#endif

#ifdef XCVAR_DECL
	#define XCVAR_DEF( name, defVal, update, flags, announce ) vmCvar_t name;
#endif

#ifdef XCVAR_LIST
	#define XCVAR_DEF( name, defVal, update, flags, announce ) { & name , #name , defVal , update , flags , announce },
#endif

XCVAR_DEF( afj_allowDropSaber,				"1",												NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_clanLogInMsg,				"is now logged as a member of the clan",			NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_clanLogOutMsg,				"logged out of the clan",							NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_clanPassword,				"",													NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qfalse)
XCVAR_DEF( afj_duelCustomArmor,				"100",												NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_duelCustomHealth,			"100",												NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_empowerMsg,					"Has gain all powers",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_hookSpeed,					"5000",												NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_ignoreMsg,					"Ignored you",										NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_kickMsg,						"You've been kicked from the server",				NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_killMsg,						"You've been killed",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_logInElectrifyTime,			"3",												NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_logInMsg1,					"Admin level 1",									NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_logInMsg2,					"Admin level 2",									NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_logInMsg3,					"Admin level 3",									NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_logInMsg4,					"Admin level 4",									NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_logInMsg5,					"Admin level 5",									NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_logInPassword1,				"",													NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qfalse)
XCVAR_DEF( afj_logInPassword2,				"",													NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qfalse)
XCVAR_DEF( afj_logInPassword3,				"",													NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qfalse)
XCVAR_DEF( afj_logInPassword4,				"",													NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qfalse)
XCVAR_DEF( afj_logInPassword5,				"",													NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qfalse)
XCVAR_DEF( afj_logInPrivileges1,			"0",												NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qfalse)
XCVAR_DEF( afj_logInPrivileges2,			"0",												NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qfalse)
XCVAR_DEF( afj_logInPrivileges3,			"0",												NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qfalse)
XCVAR_DEF( afj_logInPrivileges4,			"0",												NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qfalse)
XCVAR_DEF( afj_logInPrivileges5,			"0",												NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qfalse)
XCVAR_DEF( afj_logInWrongPwMsg,				"Wrong password",									NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_noPrivilegesMsg,				"You have no privileges",							NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
//XCVAR_DEF( afj_killProtectMsg,			"The Death himself can't kill him",					NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_privilegesChangedMsg,		"Privileges have changed, log in again",			NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_privilegesMsg,				"You don't have enough privileges",					NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_protectMsg,					"You've been protected",							NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_refuseTeleportMsg,			"Teleport refused",									NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_remEmpowerMsg,				"Has lost all powers",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_remWeaponMsg,				"Has lost all weapons",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_renameMsg,					"Got renamed",										NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_silenceMsg,					"Has been silenced",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_slapMsg,						"Has been slapped",									NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_sleepMsg,					"Has been slept",									NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_teleportMsg,					"Has been teleported",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_unIgnoreMsg,					"Not ignoring you anymore",							NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_unProtectMsg,				"You've been unprotected",							NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_unSilenceMsg,				"Has been unsilenced",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_waitBeforeNextTry,			"Wait before the next try",							NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_wakeMsg,						"Has been woken up",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_weaponMsg,					"Has gain all weapons",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_yourPrivilegesMsg,			"Your privileges are",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)

#undef XCVAR_DEF
