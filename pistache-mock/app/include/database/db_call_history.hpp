#include <jansson.h>
#include <string>
#include <sqlite3.h>
#include <stdbool.h>

#define DB_NAME "/tmp/tcc.db"

#define GET_ALL_CALL_HISTORY "SELECT * FROM call_history;"
#define GET_CALL_HISTORY "SELECT * FROM call_history WHERE call_id = %s"
#define DELETE_CALL_HISTORY "DELETE FROM call_history WHERE call_id = %s"
#define DELETE_ALL_CALL_HISTORY "DELETE FROM call_history"

class DatabaseCallHistory {
private:

public:
    DatabaseCallHistory() {}
    ~DatabaseCallHistory() {}

    static json_t * database_get_all_call_history();

    static bool database_remove_all_call_history();

    static json_t * database_get_call_history(std::string id);

    static bool database_remove_call_history(std::string id);
};


