// WARNING: COMMANDS MUST BE SORTED IN ALPHABETICAL ORDER AND START WITH "afj"
#define AFJ_COMMANDS_JAMPGAME	{ "afjaddbot",				Cmd_afjAddbot_f,			CMD_NOINTERMISSION },\
								{ "afjcapturelimit",		Cmd_afjCapturelimit_f,		CMD_NOINTERMISSION },\
								{ "afjclanlogin",			Cmd_afjClanLogIn_f,			0 },\
								{ "afjclanlogout",			Cmd_afjClanLogOut_f,		0 },\
								{ "afjcpmsg",				Cmd_afjCpMsg_f,				CMD_NOINTERMISSION },\
								{ "afjdevmap",				Cmd_afjDevMap_f,			CMD_NOINTERMISSION },\
								{ "afjforceteam",			Cmd_afjForceTeam_f,			CMD_NOINTERMISSION },\
								{ "afjfraglimit",			Cmd_afjFraglimit_f,			CMD_NOINTERMISSION },\
								{ "afjgametype",			Cmd_afjGametype_f,			CMD_NOINTERMISSION },\
								{ "afjignore",				Cmd_afjIgnore_f,			0 },\
								{ "afjignorelist",			Cmd_afjIgnoreList_f,		0 },\
								{ "afjkick",				Cmd_afjKick_f,				0 },\
								{ "afjkill",				Cmd_afjKill_f,				CMD_NOINTERMISSION },\
								{ "afjmap",					Cmd_afjMap_f,				CMD_NOINTERMISSION },\
								{ "afjmap_restart",			Cmd_afjMapRestart_f,		CMD_NOINTERMISSION },\
								{ "afjorigin",				Cmd_afjOrigin_f,			CMD_NOINTERMISSION|CMD_ALIVE },\
								{ "afjprotect",				Cmd_afjProtect_f,			CMD_NOINTERMISSION|CMD_ALIVE },\
								{ "afjrename",				Cmd_afjRename_f,			CMD_NOINTERMISSION },\
								{ "afjsilence",				Cmd_afjSilence_f,			0 },\
								{ "afjslap",				Cmd_afjSlap_f,				CMD_NOINTERMISSION },\
								{ "afjstatus",				Cmd_afjStatus_f,			0 },\
								{ "afjtimelimit",			Cmd_afjTimelimit_f,			CMD_NOINTERMISSION },\
								{ "afjunignoreall",			Cmd_afjUnIgnoreAll_f,		0 },\
								{ "afjunsilence",			Cmd_afjUnSilence_f,			0 },

typedef struct afjUser_s {
	qboolean	isClanMember;
	int			ignoredClients;
	qboolean	isSilenced;
} afjUser_t;

typedef struct afjLevel_s {
	gametype_t	nextGametype;
	qboolean	waitingNextGametype;
} afjLevel_t;


void Cmd_afjAddbot_f(gentity_t *ent);
void Cmd_afjCapturelimit_f(gentity_t *ent);
void Cmd_afjClanLogIn_f(gentity_t *ent);
void Cmd_afjClanLogOut_f(gentity_t *ent);
void Cmd_afjCpMsg_f(gentity_t *ent);
void Cmd_afjDevMap_f(gentity_t *ent);
void Cmd_afjForceTeam_f(gentity_t *ent);
void Cmd_afjFraglimit_f(gentity_t *ent);
void Cmd_afjGametype_f(gentity_t *ent);
void Cmd_afjIgnore_f(gentity_t *ent);
void Cmd_afjIgnoreList_f(gentity_t *ent);
void Cmd_afjKick_f(gentity_t *ent);
void Cmd_afjKill_f(gentity_t *ent);
void Cmd_afjMap_f(gentity_t *ent);
void Cmd_afjMapRestart_f(gentity_t *ent);
void Cmd_afjOrigin_f(gentity_t *ent);
void Cmd_afjProtect_f(gentity_t *ent);
void Cmd_afjRename_f(gentity_t *ent);
void Cmd_afjSilence_f(gentity_t *ent);
void Cmd_afjSlap_f(gentity_t *ent);
void Cmd_afjStatus_f(gentity_t *ent);
void Cmd_afjTimelimit_f(gentity_t *ent);
void Cmd_afjUnIgnoreAll_f(gentity_t *ent);
void Cmd_afjUnSilence_f(gentity_t *ent);