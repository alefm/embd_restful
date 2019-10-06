#ifndef DB_CALL_HISTORY_H
#define DB_CALL_HISTORY_H

#include <jansson.h>
#include <stdbool.h>
#include <sqlite3.h>
#include "resource/call_history.h"
#include "resource/call.h"
#include "database/database.h"

json_t * database_get_all_call_history();

bool database_remove_all_call_history();

json_t * database_get_call_history(const char * id);

bool database_get_call_history_data(const char * id, CallHistory * output);

bool database_remove_call_history(const char * id);

bool database_update_call_history(const char * id, CallHistory call);

bool database_create_call_history(CallHistory call_history);

#endif //DB_CALL_HISTORY_H