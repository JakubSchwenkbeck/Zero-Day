#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>


// Symmetirc encryption: 

// XOR 
std::string XOR(const std::string& msg,const std::string& key){

    if(msg.length() < key.length()){
        throw std::invalid_argument("msg length insufficent"); 
    }


    std::string result; 
    //(msg.length(),"\0"); // init result string
    
    for(size_t i = 0;i < msg.length(); i++ ){
        result[i] = msg[i] ^ key[i % key.length()]; // bit wise XOR , handling padding of key
    }

   

}
int main(){

    std::cout << XOR("Hello","monkey") << std::endl;

    return 0;
}