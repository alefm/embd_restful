package models

type Call struct {
	CallId       int    `json:"call_id" bson:"call_id"`
	SipAccountID int    `json:"sip_account_id" bson:"sip_account_id"`
	Destination  string `json:"destination" bson:"destination"`
}
