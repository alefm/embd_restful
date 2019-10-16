#include "database/db_call_history.hpp"

json_t * DatabaseCallHistory::database_get_all_call_history(){
    sqlite3* db;
    sqlite3_stmt *res;
    json_t *root = json_array();

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    printf("Database connection okay!\n");

    if(sqlite3_prepare_v2(db, GET_ALL_CALL_HISTORY, 128, &res, NULL) != SQLITE_OK) {
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

bool DatabaseCallHistory::database_remove_all_call_history(){
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

json_t * DatabaseCallHistory::database_get_call_history(std::string id){
    sqlite3* db;
    sqlite3_stmt *res;
    char sql[100] = { 0 };

    json_t *root = json_object();

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    printf("Database connection okay!\n");

    sprintf(sql, GET_CALL_HISTORY, id.c_str());
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

bool DatabaseCallHistory::database_remove_call_history(std::string id){
    sqlite3* db;
    char sql[100] = { 0 };
    char *err_msg = 0;

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");
    sprintf(sql, DELETE_CALL_HISTORY, id.c_str());
    if(sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK){
        printf("SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);

    return true;
}