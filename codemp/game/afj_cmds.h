// WARNING: COMMANDS MUST BE SORTED IN ALPHABETICAL ORDER AND START WITH "afj"
#define AFJ_COMMANDS_JAMPGAME	{ "afjclanlogin",			Cmd_afjClanLogIn_f,			0 },\
								{ "afjclanlogout",			Cmd_afjClanLogOut_f,		0 },\
								{ "afjcpmsg",				Cmd_afjCpMsg_f,				CMD_NOINTERMISSION },\
								{ "afjignore",				Cmd_afjIgnore_f,			0 },\
								{ "afjignorelist",			Cmd_afjIgnoreList_f,		0 },\
								{ "afjkick",				Cmd_afjKick_f,				0 },\
								{ "afjkill",				Cmd_afjKill_f,				CMD_NOINTERMISSION },\
								{ "afjorigin",				Cmd_afjOrigin_f,			CMD_NOINTERMISSION|CMD_ALIVE },\
								{ "afjprotect",				Cmd_afjProtect_f,			CMD_NOINTERMISSION|CMD_ALIVE },\
								{ "afjrename",				Cmd_afjRename_f,			CMD_NOINTERMISSION },\
								{ "afjstatus",				Cmd_afjStatus_f,			0 },

typedef struct afjUser_s {
	qboolean	isClanMember;
	int			ignoreClient;
} afjUser_t;

void Cmd_afjClanLogIn_f(gentity_t *ent);
void Cmd_afjClanLogOut_f(gentity_t *ent);
void Cmd_afjCpMsg_f(gentity_t *ent);
void Cmd_afjIgnore_f(gentity_t *ent);
void Cmd_afjIgnoreList_f(gentity_t *ent);
void Cmd_afjKick_f(gentity_t *ent);
void Cmd_afjKill_f(gentity_t *ent);
void Cmd_afjOrigin_f(gentity_t *ent);
void Cmd_afjProtect_f(gentity_t *ent);
void Cmd_afjRename_f(gentity_t *ent);
void Cmd_afjStatus_f(gentity_t *ent);