package main

import (
	"gmux_mock/routers"
	"net/http"
)

func main() {
	r := routers.SetupRoutes()
	http.ListenAndServe(":8080", r)
}
