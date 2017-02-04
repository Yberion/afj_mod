#include "game/g_local.h"
#include "cJSON/cJSON.h"
#include "afj_cJSON_utils.h"

// serialise a JSON object and write it to the specified file
void Q_FSWriteJSON(void *root, fileHandle_t f) {
	const char *serialised = NULL;

	serialised = cJSON_Serialize((cJSON *)root, 1);
	trap->FS_Write(serialised, strlen(serialised), f);
	trap->FS_Close(f);

	free((void *)serialised);
	cJSON_Delete((cJSON *)root);
}