#include <iostream>
#include <curl/curl.h>
#include <string>
using namespace std;
int main()
{
    CURL *curl;
    CURLcode res;

    string post_data = "{ \"index\" : { \"_index\" : \"tindex\", \"_type\" : \"type1\", \"_id\" : \"2\" } }\n{\"name\" : \"yash\" }\n";
    cout <<post_data;
    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */ 
    curl = curl_easy_init();
    if(curl) {
                  /* First set the URL that is about to receive our POST. This URL can
                   *        just as well be a https:// URL if that is what should receive the
                   *               data. */ 
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:9200/_bulk");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
        }

        // Cleaning Up
        curl_global_cleanup();
    }
    return 0;
}
