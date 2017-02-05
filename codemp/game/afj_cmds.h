// WARNING: COMMANDS MUST BE SORTED IN ALPHABETICAL ORDER AND START WITH "afj"
#define AFJ_COMMANDS_JAMPGAME	{ "afjclanlogin",			Cmd_afjClanLogIn_f,			0 },\
								{ "afjclanlogout",			Cmd_afjClanLogOut_f,		0 },\
								{ "afjcpmsg",				Cmd_afjCpMsg_f,				CMD_NOINTERMISSION },\
								{ "afjkick",				Cmd_afjKick_f,				0 },\
								{ "afjorigin",				Cmd_afjOrigin_f,			CMD_NOINTERMISSION|CMD_ALIVE },\
								{ "afjprotect",				Cmd_afjProtect_f,			CMD_NOINTERMISSION|CMD_ALIVE },\
								{ "afjstatus",				Cmd_afjStatus_f,			0 },

typedef struct afjUser_s {
	qboolean IsClanMember;
} afjUser_t;

void Cmd_afjClanLogIn_f(gentity_t *ent);
void Cmd_afjClanLogOut_f(gentity_t *ent);
void Cmd_afjCpMsg_f(gentity_t *ent);
void Cmd_afjKick_f(gentity_t *ent);
void Cmd_afjOrigin_f(gentity_t *ent);
void Cmd_afjProtect_f(gentity_t *ent);
void Cmd_afjStatus_f(gentity_t *ent);