#ifndef DB_SIP_ACCOUNT_H
#define DB_SIP_ACCOUNT_H

#include <jansson.h>
#include <sqlite3.h>
#include <stdbool.h>
#include "database/database.h"
#include "resource/sip_account.h"

bool database_create_sip_account(SipAccount sip_account);

bool database_update_sip_account(const char * id, SipAccount sip_account);

json_t * database_get_all_sip_account();

json_t * database_get_sip_account(const char * id);

bool database_get_sip_account_data(const char * id, SipAccount * output);

bool database_remove_sip_account(const char * id);

#endif //DB_SIP_ACCOUNT_H