#include "resource/call_history.h"
#include "database/db_call_history.h"

int retrieve_all_call_history(const struct _u_request * request, struct _u_response * response, void * user_data){
    
    json_t *root = database_get_all_call_history();

    char *json_text = json_dumps(root, 2000);
    json_decref(root);

    ulfius_set_string_body_response(response, MHD_HTTP_OK, json_text);

    return U_CALLBACK_CONTINUE;
}

int remove_all_call_history(const struct _u_request * request, struct _u_response * response, void * user_data){
    
    if(!database_remove_all_call_history()){
        ulfius_set_string_body_response(response, MHD_HTTP_INTERNAL_SERVER_ERROR, "");
    }

    ulfius_set_string_body_response(response, MHD_HTTP_OK, "");
    
    return U_CALLBACK_CONTINUE;
}

int retrieve_call_history(const struct _u_request * request, struct _u_response * response, void * user_data){
    const char *id = u_map_get(request->map_url, "id");

    json_t *root = database_get_call_history(id);

    char *json_text = json_dumps(root, 2000);
    json_decref(root);

    ulfius_set_string_body_response(response, MHD_HTTP_OK, json_text);

    return U_CALLBACK_CONTINUE;
}

int remove_call_history(const struct _u_request * request, struct _u_response * response, void * user_data){
    const char *id = u_map_get(request->map_url, "id");

    if(!database_remove_call_history(id)){
        ulfius_set_string_body_response(response, MHD_HTTP_INTERNAL_SERVER_ERROR, "");
    }

    ulfius_set_string_body_response(response, MHD_HTTP_OK, "");
    
    return U_CALLBACK_CONTINUE;
}