package handlers

import (
	"github.com/gin-gonic/gin"
)

func HandlePing(c *gin.Context) {
	c.JSON(200, gin.H{"message": "pong"})
}
