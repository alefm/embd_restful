#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

using namespace Pistache;

class LedHandler {
    private:
    public:
        LedHandler() {}
        ~LedHandler() {}
        static void createLed(const Rest::Request& request, Http::ResponseWriter response);
        static void updateLed(const Rest::Request& request, Http::ResponseWriter response);
        static void getLed(const Rest::Request& request, Http::ResponseWriter response);
        static void deleteLed(const Rest::Request& request, Http::ResponseWriter response);
};