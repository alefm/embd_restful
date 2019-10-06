#include "resource/led.h"

int create_led(const struct _u_request * request, struct _u_response * response, void * user_data){
    ulfius_set_string_body_response(response, MHD_HTTP_OK, "create_led");
    return U_CALLBACK_CONTINUE;
}

int retrieve_led(const struct _u_request * request, struct _u_response * response, void * user_data){
    ulfius_set_string_body_response(response, MHD_HTTP_OK, "retrieve_led");
    return U_CALLBACK_CONTINUE;
}

int update_led(const struct _u_request * request, struct _u_response * response, void * user_data){
    ulfius_set_string_body_response(response, MHD_HTTP_OK, "update_led");
    return U_CALLBACK_CONTINUE;
}

int remove_led(const struct _u_request * request, struct _u_response * response, void * user_data){
    ulfius_set_string_body_response(response, MHD_HTTP_OK, "remove_led");
    return U_CALLBACK_CONTINUE;
}