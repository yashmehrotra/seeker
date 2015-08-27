#include <iostream>
#include <string>
#include <string.h>

#include <curl/curl.h>
#include <libgearman/gearman.h>

using namespace std;

// Currently defining settings here

const char* gearman_host = "127.0.0.1";
in_port_t gearman_port = 4730;

const char* gearman_index_name = "index";
uint32_t gearman_timeout = 0;
void* job_context = NULL;

// Temp, first try hardcoding, then debug
const char* elasticsearch_bulk_url = "http://localhost:9200/_bulk";


void* gearman_index(gearman_job_st *job, void *context, size_t *result_size, gearman_return_t *ret_ptr)
{
    char* msg;
    CURL *curl;
    CURLcode curl_response;
    curl_global_init(CURL_GLOBAL_ALL);
    const char* es_string;
    curl = curl_easy_init();
    const void* jobptr = gearman_job_workload(job);//this takes the data from the client
    if (jobptr && curl) {
        cout << "job: " << (char*) jobptr << std::endl;
        es_string = (char*)jobptr;

        curl_easy_setopt(curl, CURLOPT_URL, elasticsearch_bulk_url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, es_string);

        curl_response = curl_easy_perform(curl);
        if (curl_response != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl_response));
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
    }
    *ret_ptr = GEARMAN_SUCCESS ;
    *result_size = 6;
    // return something smaller
    msg=strdup((char *)jobptr);
    cout<<"job received"<<endl;
    return msg; 
}


int main()
{
    // Init gearman
    gearman_worker_st* gearman_worker = gearman_worker_create(NULL);
    gearman_return_t gearman_return;

    gearman_return = gearman_worker_add_server(gearman_worker,
                                               gearman_host,
                                               gearman_port);

    gearman_return = gearman_worker_add_function(gearman_worker,
                                                 gearman_index_name,
                                                 gearman_timeout,
                                                 gearman_index,
                                                 job_context);
    
    cout<<"Server Started";
    // Try while true
    while(1) {
        gearman_return = gearman_worker_work(gearman_worker);
    }

    return 0;
}
