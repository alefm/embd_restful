package routers

import (
	"gin-mock/app/handlers"

	"github.com/gin-gonic/gin"
)

func SetupRoutes() *gin.Engine {
	r := gin.New()

	r.GET("/ping", handlers.HandlePing)

	/* call_history */
	r.GET("/call_history", handlers.RetrieveAllCallHistory)
	r.DELETE("/call_history", handlers.RemoveAllCallHistory)
	r.GET("/call_history/:id", handlers.RetrieveCallHistory)
	r.DELETE("/call_history/:id", handlers.RemoveCallHistory)

	return r
}
