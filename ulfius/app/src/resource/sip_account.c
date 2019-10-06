#include "resource/sip_account.h"
#include "database/db_sip_account.h"
#include <string.h>

void parser_sip_account(json_t * root, SipAccount * sip_account){

    json_t *jsonEnabled = json_object_get(root, "enabled");
    if(!jsonEnabled){
        printf("create sip_account: enabled field not found\n");
        return;
    }
    sip_account->enabled = json_boolean_value(jsonEnabled);

    json_t *jsonSendRegister = json_object_get(root, "send_register");
    if(!jsonSendRegister){
        printf("create sip_account: send_register field not found\n");
        return;
    }
    sip_account->send_register = json_boolean_value(jsonSendRegister);

    json_t *jsonAuthName = json_object_get(root, "auth_name");
    if(!jsonSendRegister){
        printf("create sip_account: auth_name field not found\n");
        return;
    }
    strcpy(sip_account->auth_name, json_string_value(jsonAuthName));

    json_t *jsonPassword = json_object_get(root, "password");
    if(!jsonPassword){
        printf("create sip_account: password field not found\n");
        return;
    }
    strcpy(sip_account->password, json_string_value(jsonPassword));

    json_t *jsonSipServer = json_object_get(root, "sip_server");
    if(!jsonSipServer){
        printf("create sip_account: sip_server field not found\n");
        return;
    }
    strcpy(sip_account->sip_server, json_string_value(jsonSipServer));

    json_t *jsonServerPort = json_object_get(root, "server_port");
    if(!jsonServerPort){
        printf("create sip_account: server_port field not found\n");
        return;
    }
    sip_account->server_port = json_integer_value(jsonServerPort);
}

int create_sip_account(const struct _u_request * request, struct _u_response * response, void * user_data){
    char body[4096] = {0};
    json_error_t error;

    memcpy(body, request->binary_body, request->binary_body_length);
    json_t *root = json_loads(body, 0, &error);

    SipAccount sip_account;
    parser_sip_account(root, &sip_account);

    if(!database_create_sip_account(sip_account)){
        printf("Error to create sip_account\n");
        ulfius_set_string_body_response(response, MHD_HTTP_INTERNAL_SERVER_ERROR, "");
    }

    ulfius_set_string_body_response(response, MHD_HTTP_OK, "");
    return U_CALLBACK_CONTINUE;
}

int retrieve_all_sip_account(const struct _u_request * request, struct _u_response * response, void * user_data){
    json_t *root = database_get_all_sip_account();

    char *json_text = json_dumps(root, 2000);
    json_decref(root);

    ulfius_set_string_body_response(response, MHD_HTTP_OK, json_text);

    return U_CALLBACK_CONTINUE;
}

int update_sip_account(const struct _u_request * request, struct _u_response * response, void * user_data){
    const char *id = u_map_get(request->map_url, "id");

    char body[4096] = {0};
    json_error_t error;

    memcpy(body, request->binary_body, request->binary_body_length);
    json_t *root = json_loads(body, 0, &error);

    SipAccount sip_account;
    parser_sip_account(root, &sip_account);

    if(!database_update_sip_account(id, sip_account)){
        printf("Error to update sip_account\n");
        ulfius_set_string_body_response(response, MHD_HTTP_INTERNAL_SERVER_ERROR, "");
    }

    ulfius_set_string_body_response(response, MHD_HTTP_OK, "");
    return U_CALLBACK_CONTINUE;
}

int retrieve_sip_account(const struct _u_request * request, struct _u_response * response, void * user_data){
    const char *id = u_map_get(request->map_url, "id");

    json_t *root = database_get_sip_account(id);

    char *json_text = json_dumps(root, 2000);
    json_decref(root);

    ulfius_set_string_body_response(response, MHD_HTTP_OK, json_text);

    return U_CALLBACK_CONTINUE;
}

int remove_sip_account(const struct _u_request * request, struct _u_response * response, void * user_data){
    const char *id = u_map_get(request->map_url, "id");

    if(!database_remove_sip_account(id)){
        ulfius_set_string_body_response(response, MHD_HTTP_INTERNAL_SERVER_ERROR, "");
    }

    ulfius_set_string_body_response(response, MHD_HTTP_OK, "");
    
    return U_CALLBACK_CONTINUE;
}