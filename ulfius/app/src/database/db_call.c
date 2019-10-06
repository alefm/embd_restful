#include "database/db_call.h"
#include "resource/call.h"

#define CREATE_CALL "INSERT INTO call (sip_account_id, destination) VALUES (%d, \"%s\");"

bool database_create_call(Call * call){
    sqlite3* db;
    char sql[4096] = { 0 };
    char *err_msg = 0;

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");
    sprintf(sql, CREATE_CALL, call->sip_account_id, call->destination);
    if(sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK){
        printf("SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        return false;
    }

    call->call_id = sqlite3_last_insert_rowid(db);

    sqlite3_close(db);

    return true;
}
