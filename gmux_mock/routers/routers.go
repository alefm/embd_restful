package routers

import (
	"gmux_mock/app/handlers"

	"github.com/gorilla/mux"
)

func SetupRoutes() *mux.Router {
	r := mux.NewRouter()

	r.HandleFunc("/ping", handlers.HandlePing).Methods("GET")

	/* call_history */
	r.HandleFunc("/call_history", handlers.RetrieveAllCallHistory).Methods("GET")
	r.HandleFunc("/call_history", handlers.RemoveAllCallHistory).Methods("DELETE")
	r.HandleFunc("/call_history/:id", handlers.RetrieveCallHistory).Methods("GET")
	r.HandleFunc("/call_history/:id", handlers.RemoveCallHistory).Methods("DELETE")

	return r
}
