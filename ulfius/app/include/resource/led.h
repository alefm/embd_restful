#ifndef LED_H
#define LED_H

#include <ulfius.h>
#include <jansson.h>

int create_led(const struct _u_request * request, struct _u_response * response, void * user_data);
int retrieve_led(const struct _u_request * request, struct _u_response * response, void * user_data);
int update_led(const struct _u_request * request, struct _u_response * response, void * user_data);
int remove_led(const struct _u_request * request, struct _u_response * response, void * user_data);

#endif //LED_H