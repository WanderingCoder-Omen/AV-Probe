#include <iostream>
#include <curl/curl.h>
#include <string>

using namespace std;

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

int main(int argc, char** argv) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto curl = curl_easy_init();
    CURLcode res;
    if (curl) {
        struct curl_slist *headers = NULL;
    	headers = curl_slist_append(headers, "Accept: application/json");
    	headers = curl_slist_append(headers, "Content-Type: application/json");
    	headers = curl_slist_append(headers, "charset: utf-8");
    	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, "https://avrequest-catcher.herokuapp.com/posts");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"ip\":\"1.1.1.1\", \"content\":\"ContentFromProbe\"}");
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        
        /* Perform the request, res will get the return code */ 
    	res = curl_easy_perform(curl);
    	/* Check for errors */ 
    	if(res != CURLE_OK)
      		fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
    	else
      		printf("All OK");
        //cout << response_string;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        curl = NULL;
    }
}
