#ifndef SIP_ACCOUNT_H
#define SIP_ACCOUNT_H

#include <ulfius.h>
#include <jansson.h>
#include <stdbool.h>

typedef struct SipAccount_t {
    int sip_account_id;
    bool enabled;
    bool send_register;
    char auth_name[100];
    char password[100];
    char sip_server[100];
    int server_port;
} SipAccount;

int create_sip_account(const struct _u_request * request, struct _u_response * response, void * user_data);
int retrieve_all_sip_account(const struct _u_request * request, struct _u_response * response, void * user_data);
int update_sip_account(const struct _u_request * request, struct _u_response * response, void * user_data);
int retrieve_sip_account(const struct _u_request * request, struct _u_response * response, void * user_data);
int remove_sip_account(const struct _u_request * request, struct _u_response * response, void * user_data);

#endif //SIP_ACCOUNT_H