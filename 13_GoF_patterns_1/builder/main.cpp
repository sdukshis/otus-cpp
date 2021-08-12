#include <iostream>

#include "HTTPRequest.h"
#include "HTTPRequestBuilder.h"

int main() {
    
    auto request = HTTPRequestBuilder()
        .method("GET")
        .path("/client")
        .param("id", "42")
        .param("format", "json")
        .header("Host", "www.example.com")
        .header("Authorization", "Bearer ...")
        .build();
    
    std::cout << request;
}