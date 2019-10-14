#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

using namespace Pistache;

class CallHistoryHandler {
    private:
    public:
        CallHistoryHandler() {}
        ~CallHistoryHandler() {}
        static void getAllCallHistory(const Rest::Request& request, Http::ResponseWriter response);
        static void deleteAllCallHistory(const Rest::Request& request, Http::ResponseWriter response);
        static void getCallHistory(const Rest::Request& request, Http::ResponseWriter response);
        static void deleteCallHistory(const Rest::Request& request, Http::ResponseWriter response);
};