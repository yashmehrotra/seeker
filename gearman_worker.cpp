#include<libgearman/gearman.h>
#include<iostream>
#include<string.h>
using namespace std;
void* gworker_fn_demon(gearman_job_st *job, void *context, size_t *result_size, gearman_return_t *ret_ptr)
{
    char* msg;
    const void* jobptr = gearman_job_workload(job);//this takes the data from the client
    if (jobptr) {
        std::cout << "job: " << (char*) jobptr << std::endl;
    }
    *ret_ptr = GEARMAN_SUCCESS ;
    *result_size = 6;
    msg=strdup((char *)jobptr);
    cout<<"job received"<<endl;
    cout<<"Message"<<msg;
    return msg; 
}

int main()
{
    gearman_worker_st* worker = gearman_worker_create(NULL);
    gearman_return_t ret;

    const char* ghost = "127.0.0.1";
    in_port_t gport = 4730;
    gearman_return_t gm_func;
    gearman_return_t gs_code = gearman_worker_add_server(worker, ghost, gport);
    
    const char* function_name = "reverse";
    uint32_t timeout= 0;
    void* job_context =NULL;
    gm_func = gearman_worker_add_function(worker,function_name, timeout, gworker_fn_demon, job_context);
    while (1) {
        ret = gearman_worker_work(worker);
        if (ret == GEARMAN_SUCCESS) {
            cout<<"Success";
        }
    }
    return 0;
}
