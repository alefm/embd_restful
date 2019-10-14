#include "handlers/call_history_handler.hpp"
#include "database/db_call_history.hpp"
#include <jansson.h>

void CallHistoryHandler::getAllCallHistory(const Rest::Request& request, Http::ResponseWriter response){
    json_t *root = DatabaseCallHistory::database_get_all_call_history();

    char *json_text = json_dumps(root, 2000);
    json_decref(root);

    response.send(Http::Code::Ok, json_text);
}

void CallHistoryHandler::deleteAllCallHistory(const Rest::Request& request, Http::ResponseWriter response){
    response.send(Http::Code::Ok, "Hello, Call History!");
}

void CallHistoryHandler::getCallHistory(const Rest::Request& request, Http::ResponseWriter response){
    auto id = request.param(":id").as<std::string>();
    response.send(Http::Code::Ok, "Hello, Call History " + id);
}

void CallHistoryHandler::deleteCallHistory(const Rest::Request& request, Http::ResponseWriter response){
    auto id = request.param(":id").as<std::string>();
    response.send(Http::Code::Ok, "Hello, Call History!");
}


