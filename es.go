package main
import "gopkg.in/olivere/elastic.v2"


func main() {
    type Tweet struct {
        User string `json:"user"`
        Message string `json:"message"`
    }
    client, err := elastic.NewClient()
    if err != nil {
        // Handle error
    }

    // Create an index
   /* _, err = client.CreateIndex("zwitter").Do()
    if err != nil {
        // Handle error
        panic(err)
    }*/

    // Add a document to the index
    tweet := Tweet{User: "Avijit", Message: "HELLO WOLRD!"}
    _, err = client.Index().
        Index("twitter").
        Type("tweet").
        Id("1").
        BodyJson(tweet).
        Do()

    if err != nil {
        // Handle error
        panic(err)
    }
}
