#ifndef CALL_H
#define CALL_H

#include <ulfius.h>
#include <jansson.h>

typedef struct Call_t {
    int call_id;
    int sip_account_id;
    char destination[100];
} Call;

int create_call(const struct _u_request * request, struct _u_response * response, void * user_data);
int update_call(const struct _u_request * request, struct _u_response * response, void * user_data);

#endif //CALL_H