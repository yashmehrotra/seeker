#include <iostream>
#include <curl/curl.h>
#include <string>
#include <typeinfo>
using namespace std;
int main()
{
    CURL *curl;
    CURLcode res;
    const char* x="yash";
    const char* post_data = "{ \"index\" : { \"_index\" : \"tindex\", \"_type\" : \"type1\", \"_id\" : \"3\" } }\n{\"name\" : \"batman\" }\n";

    cout <<post_data;
    const char* es_host = "http://localhost:9200/_bulk";
    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */ 
    curl = curl_easy_init();
    if(curl) {
                  /* First set the URL that is about to receive our POST. This URL can
                   *        just as well be a https:// URL if that is what should receive the
                   *               data. */ 
        curl_easy_setopt(curl, CURLOPT_URL, es_host);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

        res = curl_easy_perform(curl);
        cout<<"Type -> "<<typeid(x).name()<<endl;
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
        }

        // Cleaning Up
        curl_global_cleanup();
    }
    return 0;
}
