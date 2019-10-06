#include <stdio.h>
#include <ulfius.h>
#include <stdbool.h>
#include <signal.h>

#include "resource/call.h"
#include "resource/call_history.h"
#include "resource/sip_account.h"
#include "resource/led.h"

#define PORT 8080

#define API_PREFIX "/api/v1"

static volatile bool keepRunning = true;

/**
 * Callback function for the web application on /helloworld url call
 */
int callback_hello_world (const struct _u_request * request, struct _u_response * response, void * user_data) {
    ulfius_set_string_body_response(response, MHD_HTTP_OK, "Hello World!");
    return U_CALLBACK_CONTINUE;
}

void handleSignal(int dummy){
    printf("Received a SIGINT signal...\n Stopping process...\n");
    keepRunning = false;
}

bool init_endpoints(struct _u_instance * instance){
    /* call */
    ulfius_add_endpoint_by_val(instance, "POST", "/call", NULL, 0, &create_call, NULL);
    ulfius_add_endpoint_by_val(instance, "PUT", NULL, "/call/:id", 0, &update_call, NULL);

    /* call_history */
    ulfius_add_endpoint_by_val(instance, "GET", "/call_history", NULL, 0, &retrieve_all_call_history, NULL);
    ulfius_add_endpoint_by_val(instance, "DELETE", "/call_history", NULL, 0, &remove_all_call_history, NULL);

    /* call_history/:id */
    ulfius_add_endpoint_by_val(instance, "GET", NULL, "/call_history/:id", 0, &retrieve_call_history, NULL);
    ulfius_add_endpoint_by_val(instance, "DELETE", NULL, "/call_history/:id", 0, &remove_call_history, NULL);

    /* sip_account */
    ulfius_add_endpoint_by_val(instance, "POST", "/sip_account", NULL, 0, &create_sip_account, NULL);
    ulfius_add_endpoint_by_val(instance, "GET", "/sip_account", NULL, 0, &retrieve_all_sip_account, NULL);

    /* sip_account/:id */
    ulfius_add_endpoint_by_val(instance, "GET", NULL, "/sip_account/:id", 0, &retrieve_sip_account, NULL);
    ulfius_add_endpoint_by_val(instance, "PUT", NULL, "/sip_account/:id", 0, &update_sip_account, NULL);
    ulfius_add_endpoint_by_val(instance, "DELETE", NULL, "/sip_account/:id", 0, &remove_sip_account, NULL);
    
    /* led */
    ulfius_add_endpoint_by_val(instance, "POST", "/led", NULL, 0, &create_led, NULL);
    ulfius_add_endpoint_by_val(instance, "GET", "/led", NULL, 0, &retrieve_led, NULL);
    ulfius_add_endpoint_by_val(instance, "PUT", "/led", NULL, 0, &update_led, NULL);
    ulfius_add_endpoint_by_val(instance, "DELETE", "/led", NULL, 0, &remove_led, NULL);
    
    return true;
}
/**
 * main function
 */
int main(void) {
    struct _u_instance instance;

    signal(SIGINT, handleSignal);

    // Initialize instance with the port number
    if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
        fprintf(stderr, "Error ulfius_init_instance, abort\n");
        return false;
    }

    // Endpoint list declaration
    init_endpoints(&instance);

    // Start the framework
    if (ulfius_start_framework(&instance) == U_OK) {
        printf("Start framework on port %d\n", instance.port);
    } else {
        fprintf(stderr, "Error starting framework\n");
    }

    while(keepRunning);

    printf("End framework\n");

    ulfius_stop_framework(&instance);
    ulfius_clean_instance(&instance);

    return true;
}