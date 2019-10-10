package models

type CallHistory struct {
	CallId       int    `json:"call_id" bson:"call_id"`
	SipAccountID int    `json:"sip_account_id" bson:"sip_account_id"`
	Source       string `json:"source" bson:"source"`
	Destination  string `json:"destination" bson:"destination"`
	StartDate    int64  `json:"start_date" bson:"start_date"`
	EndDate      int64  `json:"end_date" bson:"end_date"`
}
