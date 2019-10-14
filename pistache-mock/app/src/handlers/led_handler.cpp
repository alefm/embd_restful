#include "handlers/led_handler.hpp"

void LedHandler::createLed(const Rest::Request& request, Http::ResponseWriter response){
    response.send(Http::Code::Ok, "Create led");
}

void LedHandler::updateLed(const Rest::Request& request, Http::ResponseWriter response){
    response.send(Http::Code::Ok, "Update Led");
}

void LedHandler::getLed(const Rest::Request& request, Http::ResponseWriter response){
    response.send(Http::Code::Ok, "Get Led");
}

void LedHandler::deleteLed(const Rest::Request& request, Http::ResponseWriter response){
    response.send(Http::Code::Ok, "Delete Led");
}


