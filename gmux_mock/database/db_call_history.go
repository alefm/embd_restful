package database

import (
	"database/sql"
	"gmux_mock/app/models"

	_ "github.com/mattn/go-sqlite3"
)

func GetAllCallHistory() []models.CallHistory {
	dbtcc, _ := sql.Open("sqlite3", "/tmp/tcc.db")

	rows, _ := dbtcc.Query("SELECT * FROM call_history;")

	history := []models.CallHistory{}

	for rows.Next() {
		var callHistory models.CallHistory
		_ = rows.Scan(&callHistory.CallId, &callHistory.SipAccountID, &callHistory.Source, &callHistory.Destination, &callHistory.StartDate, &callHistory.EndDate)
		history = append(history, callHistory)
	}

	return history
}
