package models

type SipAccount struct {
	SipAccountID int    `json:"sip_account_id" bson:"sip_account_id"`
	Enabled      bool   `json:"enabled" bson:"enabled"`
	SendRegister bool   `json:"send_register" bson:"send_register"`
	AuthName     string `json:"auth_name" bson:"auth_name"`
	Password     string `json:"password" bson:"password"`
	SipServer    string `json:"sip_server" bson:"sip_server"`
	ServerPort   int    `json:"server_port" bson:"server_port"`
}
