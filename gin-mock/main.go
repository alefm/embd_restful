package main

import (
	"gin-mock/routers"
)

func main() {
	r := routers.SetupRoutes()

	r.Run()
}
