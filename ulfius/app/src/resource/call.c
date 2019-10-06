#include "resource/call.h"
#include "resource/call_history.h"
#include "resource/sip_account.h"
#include "database/db_call.h"
#include "database/db_call_history.h"
#include "database/db_sip_account.h"
#include <time.h>
#include <string.h>

void parser_call(json_t * root, Call * call){

    json_t *jsonDestination = json_object_get(root, "destination");
    if(!jsonDestination){
        printf("create call: destination field not found\n");
        return;
    }
    strcpy(call->destination, json_string_value(jsonDestination));

    json_t *jsonSipAccountId = json_object_get(root, "sip_account_id");
    if(!jsonSipAccountId){
        printf("create call: sip_account_id field not found\n");
        return;
    }
    call->sip_account_id = json_integer_value(jsonSipAccountId);
}

int create_call(const struct _u_request * request, struct _u_response * response, void * user_data){
    char body[4096] = {0};
    char id[30] = {0};
    json_error_t error;

    memcpy(body, request->binary_body, request->binary_body_length);
    json_t *root = json_loads(body, 0, &error);

    Call call;
    CallHistory call_history;
    SipAccount sip_account;
    parser_call(root, &call);

    if(!database_create_call(&call)){
        printf("Error to create call\n");
        ulfius_set_string_body_response(response, MHD_HTTP_INTERNAL_SERVER_ERROR, "");
    }

    sprintf(id, "%d", call.sip_account_id);
    if(!database_get_sip_account_data(id, &sip_account)){
        printf("Error to create call invalid sip_account\n");
        ulfius_set_string_body_response(response, MHD_HTTP_INTERNAL_SERVER_ERROR, "");
    }

    call_history.call_id = call.call_id;
    call_history.start_date = (int)time(NULL);
    call_history.end_date = (int)time(NULL);
    call_history.sip_account_id = call.sip_account_id;
    strcpy(call_history.destination, call.destination);
    sprintf(call_history.source, "%s@%s", sip_account.auth_name, sip_account.sip_server);

    if(!database_create_call_history(call_history)){
        printf("Error to create call - callhistory\n");
        ulfius_set_string_body_response(response, MHD_HTTP_INTERNAL_SERVER_ERROR, "");
    }

    ulfius_set_string_body_response(response, MHD_HTTP_OK, "");
    return U_CALLBACK_CONTINUE;
}

int update_call(const struct _u_request * request, struct _u_response * response, void * user_data){
    const char *id = u_map_get(request->map_url, "id");

    CallHistory call_history;
    if(!database_get_call_history_data(id, &call_history)){
        printf("Error to get call\n");
        ulfius_set_string_body_response(response, MHD_HTTP_INTERNAL_SERVER_ERROR, "");
    }

    call_history.end_date = (int)time(NULL); /* Update end time */

    if(!database_update_call_history(id, call_history)){
        printf("Error to update call_history\n");
        ulfius_set_string_body_response(response, MHD_HTTP_INTERNAL_SERVER_ERROR, "");
    }

    ulfius_set_string_body_response(response, MHD_HTTP_OK, "update_call");
    return U_CALLBACK_CONTINUE;
}