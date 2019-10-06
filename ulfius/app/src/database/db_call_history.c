#include "database/db_call_history.h"
#include <string.h>

#define SELECT_ALL_CALL_HISTORY "SELECT * FROM call_history;"
#define SELECT_CALL_HISTORY "SELECT * FROM call_history WHERE call_id = %s"
#define DELETE_CALL_HISTORY "DELETE FROM call_history WHERE call_id = %s"
#define DELETE_ALL_CALL_HISTORY "DELETE FROM call_history"
#define UPDATE_CALL_HISTORY "UPDATE call_history SET end_date = %d WHERE call_id = %s"
#define CREATE_CALL_HISTORY "INSERT INTO call_history (sip_account_id, source, destination, start_date, end_date) values (%d,\"%s\",\"%s\",%d,%d)"

json_t * database_get_all_call_history(){
    sqlite3* db;
    sqlite3_stmt *res;
    json_t *root = json_array();

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");

    if(sqlite3_prepare_v2(db, SELECT_ALL_CALL_HISTORY, 128, &res, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        printf("Can't retrieve data: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    while(sqlite3_step(res) != SQLITE_DONE) {
        json_t * object = json_object();

        json_object_set_new(object, "call_id", json_integer(sqlite3_column_int(res, 0)));
        json_object_set_new(object, "sip_account_id", json_integer(sqlite3_column_int(res, 1)));
        json_object_set_new(object, "source", json_string((const char *)sqlite3_column_text(res, 2)));
        json_object_set_new(object, "destination", json_string((const char *)sqlite3_column_text(res, 3)));
        json_object_set_new(object, "start_date", json_integer(sqlite3_column_int(res, 4)));
        json_object_set_new(object, "end_date", json_integer(sqlite3_column_int(res, 5)));

        json_array_append_new(root, object);
    }

    sqlite3_finalize(res);

    sqlite3_close(db);

    return root;
}

bool database_remove_all_call_history(){
    sqlite3* db;
    char *err_msg = 0;

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");

    if(sqlite3_exec(db, DELETE_ALL_CALL_HISTORY, 0, 0, &err_msg) != SQLITE_OK){
        printf("SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);

    return true;
}

json_t * database_get_call_history(const char * id){
    sqlite3* db;
    sqlite3_stmt *res;
    char sql[100] = { 0 };

    json_t *root = json_object();

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");

    sprintf(sql, SELECT_CALL_HISTORY, id);
    if(sqlite3_prepare_v2(db, sql, 128, &res, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        printf("Can't retrieve data: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    int step = sqlite3_step(res);
    if(step == SQLITE_ROW){
        json_object_set_new(root, "call_id", json_integer(sqlite3_column_int(res, 0)));
        json_object_set_new(root, "sip_account_id", json_integer(sqlite3_column_int(res, 1)));
        json_object_set_new(root, "source", json_string((const char *)sqlite3_column_text(res, 2)));
        json_object_set_new(root, "destination", json_string((const char *)sqlite3_column_text(res, 3)));
        json_object_set_new(root, "start_date", json_integer(sqlite3_column_int(res, 4)));
        json_object_set_new(root, "end_date", json_integer(sqlite3_column_int(res, 5)));

    }

    sqlite3_finalize(res);

    sqlite3_close(db);

    return root;
}

bool database_get_call_history_data(const char * id, CallHistory * output){
    sqlite3* db;
    sqlite3_stmt *res;
    char sql[100] = { 0 };

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");

    sprintf(sql, SELECT_CALL_HISTORY, id);
    if(sqlite3_prepare_v2(db, sql, 128, &res, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        printf("Can't retrieve data: %s\n", sqlite3_errmsg(db));
        return false;
    }

    int step = sqlite3_step(res);
    if(step == SQLITE_ROW){
        output->call_id = sqlite3_column_int(res, 0);
        output->sip_account_id = sqlite3_column_int(res, 1);
        strcpy(output->source, (const char *)sqlite3_column_text(res, 2));
        strcpy(output->destination, (const char *)sqlite3_column_text(res, 3));
        output->start_date = sqlite3_column_int(res, 4);
        output->end_date = sqlite3_column_int(res, 5);
    }

    sqlite3_finalize(res);

    sqlite3_close(db);

    return true;
}

bool database_remove_call_history(const char * id){
    
    sqlite3* db;
    char sql[100] = { 0 };
    char *err_msg = 0;

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");
    sprintf(sql, DELETE_CALL_HISTORY, id);
    if(sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK){
        printf("SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);

    return true;
}

bool database_update_call_history(const char * id, CallHistory call){
    sqlite3* db;
    char sql[4096] = { 0 };
    char *err_msg = 0;

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");
    sprintf(sql, UPDATE_CALL_HISTORY, (int)call.end_date, id);
    if(sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK){
        printf("SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);

    return true;
}

bool database_create_call_history(CallHistory call_history){
    sqlite3* db;
    char sql[4096] = { 0 };
    char *err_msg = 0;

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");
    sprintf(sql, CREATE_CALL_HISTORY, call_history.sip_account_id, call_history.source, call_history.destination, (int)call_history.start_date, (int)call_history.end_date);
    printf("%s", sql);
    if(sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK){
        printf("SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);

    return true;
}