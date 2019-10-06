#ifndef CALL_HISTORY_H
#define CALL_HISTORY_H

#include <ulfius.h>
#include <jansson.h>

typedef struct CallHistory_t {
    int call_id;
    int sip_account_id;
    char source[200];
    char destination[50];
    unsigned long start_date;
    unsigned long end_date;
} CallHistory;

int retrieve_all_call_history(const struct _u_request * request, struct _u_response * response, void * user_data);
int remove_all_call_history(const struct _u_request * request, struct _u_response * response, void * user_data);
int retrieve_call_history(const struct _u_request * request, struct _u_response * response, void * user_data);
int remove_call_history(const struct _u_request * request, struct _u_response * response, void * user_data);

#endif //CALL_HISTORY_H