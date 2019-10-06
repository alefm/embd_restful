#include "database/db_sip_account.h"
#include "resource/sip_account.h"
#include <string.h>

#define CREATE_SIP_ACCOUNT "INSERT INTO sip_account (enabled, send_register, auth_name, password, sip_server, server_port) VALUES (%d, %d, \"%s\", \"%s\", \"%s\", %d);"
#define UPDATE_SIP_ACCOUNT "UPDATE sip_account SET enabled = %d, send_register = %d, auth_name = \"%s\", password = \"%s\", sip_server = \"%s\", server_port = %d WHERE sip_account_id = \"%s\";"
#define SELECT_ALL_SIP_ACCOUNT "SELECT * FROM sip_account;"
#define SELECT_SIP_ACCOUNT "SELECT * FROM sip_account WHERE sip_account_id = %s;"
#define DELETE_SIP_ACCOUNT "DELETE FROM sip_account WHERE sip_account_id = %s"

bool database_create_sip_account(SipAccount sip_account){
    sqlite3* db;
    char sql[4096] = { 0 };
    char *err_msg = 0;

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");
    sprintf(sql, CREATE_SIP_ACCOUNT, sip_account.enabled, sip_account.send_register, sip_account.auth_name, sip_account.password, sip_account.sip_server, sip_account.server_port);
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

bool database_update_sip_account(const char * id, SipAccount sip_account){
    sqlite3* db;
    char sql[4096] = { 0 };
    char *err_msg = 0;

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");
    sprintf(sql, UPDATE_SIP_ACCOUNT, sip_account.enabled, sip_account.send_register, sip_account.auth_name, sip_account.password, sip_account.sip_server, sip_account.server_port, id);
    if(sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK){
        printf("SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);

    return true;
}

json_t * database_get_all_sip_account(){
    sqlite3* db;
    sqlite3_stmt *res;
    json_t *root = json_array();

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");

    if(sqlite3_prepare_v2(db, SELECT_ALL_SIP_ACCOUNT, 128, &res, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        printf("Can't retrieve data: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    while(sqlite3_step(res) != SQLITE_DONE) {
        json_t * object = json_object();

        json_object_set_new(object, "sip_account_id", json_integer(sqlite3_column_int(res, 0)));
        json_object_set_new(object, "enabled", json_boolean(sqlite3_column_int(res, 1)));
        json_object_set_new(object, "send_register", json_boolean(sqlite3_column_int(res, 2)));
        json_object_set_new(object, "auth_name", json_string((const char *)sqlite3_column_text(res, 3)));
        json_object_set_new(object, "password", json_string((const char *)sqlite3_column_text(res, 4)));
        json_object_set_new(object, "sip_server", json_string((const char *)sqlite3_column_text(res, 5)));
        json_object_set_new(object, "server_port", json_integer(sqlite3_column_int(res, 6)));

        json_array_append_new(root, object);
    }

    sqlite3_finalize(res);

    sqlite3_close(db);

    return root;
}

json_t * database_get_sip_account(const char * id){

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

    sprintf(sql, SELECT_SIP_ACCOUNT, id);
    if(sqlite3_prepare_v2(db, sql, 128, &res, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        printf("Can't retrieve data: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    int step = sqlite3_step(res);
    if(step == SQLITE_ROW){
        json_object_set_new(root, "sip_account_id", json_integer(sqlite3_column_int(res, 0)));
        json_object_set_new(root, "enabled", json_boolean(sqlite3_column_int(res, 1)));
        json_object_set_new(root, "send_register", json_boolean(sqlite3_column_int(res, 2)));
        json_object_set_new(root, "auth_name", json_string((const char *)sqlite3_column_text(res, 3)));
        json_object_set_new(root, "password", json_string((const char *)sqlite3_column_text(res, 4)));
        json_object_set_new(root, "sip_server", json_string((const char *)sqlite3_column_text(res, 5)));
        json_object_set_new(root, "server_port", json_integer(sqlite3_column_int(res, 6)));

    }

    sqlite3_finalize(res);

    sqlite3_close(db);

    return root;
}

bool database_remove_sip_account(const char * id){
    sqlite3* db;
    char sql[100] = { 0 };
    char *err_msg = 0;

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");
    sprintf(sql, DELETE_SIP_ACCOUNT, id);
    if(sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK){
        printf("SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);

    return true;
}

bool database_get_sip_account_data(const char * id, SipAccount * output){
    sqlite3* db;
    sqlite3_stmt *res;
    char sql[100] = { 0 };

    if(sqlite3_open(DB_NAME, &db)){
        sqlite3_close(db);
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("Database connection okay!\n");

    sprintf(sql, SELECT_SIP_ACCOUNT, id);
    if(sqlite3_prepare_v2(db, sql, 128, &res, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        printf("Can't retrieve data: %s\n", sqlite3_errmsg(db));
        return false;
    }

    int step = sqlite3_step(res);
    if(step == SQLITE_ROW){

        output->sip_account_id = sqlite3_column_int(res, 0);
        output->enabled = sqlite3_column_int(res, 1);
        output->send_register = sqlite3_column_int(res, 2);
        strcpy(output->auth_name, (const char *)sqlite3_column_text(res, 3));
        strcpy(output->password, (const char *)sqlite3_column_text(res, 4));
        strcpy(output->sip_server, (const char *)sqlite3_column_text(res, 5));
        output->server_port = sqlite3_column_int(res, 6);
    }

    sqlite3_finalize(res);

    sqlite3_close(db);

    return true;
}