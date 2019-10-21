package handlers

import (
	"gin-mock/database"

	"github.com/gin-gonic/gin"
)

func RetrieveAllCallHistory(c *gin.Context) {
	history := database.GetAllCallHistory()
	c.JSON(200, history)
}

func RemoveAllCallHistory(c *gin.Context) {
	// fmt.Println("Received RemoveAllCallHistory")
}

func RetrieveCallHistory(c *gin.Context) {
	// id := c.Param("id")
	// fmt.Println("Received RetrieveCallHistory com o id: ", id)

}

func RemoveCallHistory(c *gin.Context) {
	// id := c.Param("id")
	// fmt.Println("Received RetrieveCallHistory com o id: ", id)
}
