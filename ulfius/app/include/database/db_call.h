#ifndef DB_CALL_H
#define DB_CALL_H

#include <jansson.h>
#include <stdbool.h>
#include <sqlite3.h>
#include "resource/call.h"
#include "database/database.h"

bool database_create_call(Call *call);

#endif //DB_CALL_H