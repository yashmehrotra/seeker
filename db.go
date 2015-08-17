package main
import (
    "fmt"
    "os"
    "database/sql"
    "encoding/json"
    _ "github.com/lib/pq"
)

func main() {

    type DbUser struct {
        name string
        smail string
    }

    type DbConfig struct {
        USER string
        PASSWORD string
        HOST string
        PORT int
        DATABASE string
    }
    type Config struct {
        PGSQL DbConfig
    }
    file, _ := os.Open("config.json")
    decoder := json.NewDecoder(file)
    config := Config{}
    err := decoder.Decode(&config)
    if err != nil {
        fmt.Println(err)
    }
    fmt.Println("user - ",config.PGSQL.USER)
    postgres_conf := fmt.Sprintf("postgres://%s:%s@%s:%d/%s", config.PGSQL.USER,
                                                              config.PGSQL.PASSWORD,
                                                              config.PGSQL.HOST,
                                                              config.PGSQL.PORT,
                                                              config.PGSQL.DATABASE)

    dbUser := DbUser{}
    db, _ := sql.Open("postgres", postgres_conf)
    _ = db.QueryRow("SELECT first_name, email FROM db_user WHERE id = 1").Scan(&dbUser.name, &dbUser.smail)
    fmt.Println(dbUser.name)
    fmt.Println(dbUser.smail)
}
