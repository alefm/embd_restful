package handlers

import (
	"encoding/json"
	"gmux_mock/database"
	"net/http"
)

func RetrieveAllCallHistory(w http.ResponseWriter, r *http.Request) {
	history := database.GetAllCallHistory()
	// fmt.Println("Received RetrieveAllCallHistory")
	// todos := Todos{
	// 	Todo{Name: "Write presentation"},
	// 	Todo{Name: "Host meetup"},
	// }

	json.NewEncoder(w).Encode(history)
}

func RemoveAllCallHistory(w http.ResponseWriter, r *http.Request) {
	// fmt.Println("Received RemoveAllCallHistory")
}

func RetrieveCallHistory(w http.ResponseWriter, r *http.Request) {
	// id := c.Param("id")
	// fmt.Println("Received RetrieveCallHistory com o id: ", id)

}

func RemoveCallHistory(w http.ResponseWriter, r *http.Request) {
	// id := c.Param("id")
	// fmt.Println("Received RetrieveCallHistory com o id: ", id)
}
