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
XCVAR_DEF( afj_EmpowerMsg,					"Has gain all powers",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_hookSpeed,					"5000",												NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_ignoreMsg,					"Ignored you",										NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_kickMsg,						"You've been kicked from the server",				NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_killMsg,						"You've been killed",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
//XCVAR_DEF( afj_killProtectMsg,			"The Death himself can't kill him",					NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_protectMsg,					"You've been protected",							NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_RefuseTeleportMsg,			"Teleport refused",									NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_RemEmpowerMsg,				"Has lost all powers",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_RemWeaponMsg,				"Has lost all weapons",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_renameMsg,					"Got renamed",										NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_SilenceMsg,					"Has been silenced",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_SlapMsg,						"Has been slapped",									NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_SleepMsg,					"Has been slept",									NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_TeleportMsg,					"Has been teleported",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_unIgnoreMsg,					"Not ignoring you anymore",							NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_unProtectMsg,				"You've been unprotected",							NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_UnSilenceMsg,				"Has been unsilenced",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_waitBeforeNextTry,			"Wait before the next try",							NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_WakeMsg,						"Has been woken up",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)
XCVAR_DEF( afj_WeaponMsg,					"Has gain all weapons",								NULL,				CVAR_ARCHIVE | CVAR_NORESTART,					qtrue)

#undef XCVAR_DEF
