#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include "handlers/call_history_handler.hpp"
#include "handlers/led_handler.hpp"

using namespace Pistache;

void setupRoutes(Rest::Router& router) {
  using namespace Rest;

  Routes::Get(router, "/call_history", Routes::bind(&CallHistoryHandler::getAllCallHistory));
  Routes::Delete(router, "/call_history", Routes::bind(&CallHistoryHandler::deleteAllCallHistory));
  Routes::Get(router, "/call_history/:id", Routes::bind(&CallHistoryHandler::getCallHistory));
  Routes::Delete(router, "/call_history:id", Routes::bind(&CallHistoryHandler::deleteCallHistory));

  Routes::Post(router, "/led", Routes::bind(&LedHandler::createLed));
  Routes::Get(router, "/led", Routes::bind(&LedHandler::getLed));
  Routes::Put(router, "/led", Routes::bind(&LedHandler::updateLed));
  Routes::Delete(router, "/led", Routes::bind(&LedHandler::deleteLed));
}

int main() {
  const Pistache::Address address("localhost", Pistache::Port(8080));
  Rest::Router router;
  Http::Endpoint httpServer(address);

  httpServer.init();
  setupRoutes(router);
  httpServer.setHandler(router.handler());
  httpServer.serve();
}