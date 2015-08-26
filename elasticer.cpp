#include <iostream>
#include <curl/curl.h>
#include <string>
using namespace std;
int main()
{
    CURL *curl;
    CURLcode res;

    string post_data = "{ \"index\" : { \"_index\" : \"tindex\", \"_type\" : \"type1\", \"_id\" : \"1\" } }\n{\"field1\" : \"value1\" }\n";
    cout <<post_data;
    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */ 
    curl = curl_easy_init();
    if(curl) {
                  /* First set the URL that is about to receive our POST. This URL can
                   *        just as well be a https:// URL if that is what should receive the
                   *               data. */ 
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:9200/_bulk");
                          /* Now specify the POST data */ 
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());
//curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, size);                            
                              /* Perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);
                                  /* Check for errors */ 
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                                   /* always cleanup */ 
    
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
    }
    return 0;
}
