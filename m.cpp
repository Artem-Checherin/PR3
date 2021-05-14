#include <iostream>
#include <string>
#include <cstdlib> 
#include <cstring> 
#include <unistd.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
using namespace std;
void Exception(const string & why, const int exitCode ) 
{
    cout << "ErrorCode:"<<exitCode <<endl<< why << endl;
    exit(exitCode);
}
int main()
{
    
    
    sockaddr_in * CHICHA = new (sockaddr_in);
    CHICHA->sin_family = AF_INET; 
    CHICHA->sin_port = 0;         
    CHICHA->sin_addr.s_addr = 0;  

    
    sockaddr_in * NECHICHA = new (sockaddr_in);
    NECHICHA->sin_family = AF_INET;     
    NECHICHA->sin_port = htons(7);  
    NECHICHA->sin_addr.s_addr = inet_addr("82.179.90.12"); 
    
    
    char *buffer = new char[4096];
    strcpy(buffer,"LILCHICHA");   
    int msgLen = strlen(buffer);          
   
    
    int mySocket = socket(AF_INET, SOCK_STREAM, 0); 
    if (mySocket == -1) {
        close(mySocket);
        Exception("Error open socket",11);
    }
    
    int rc = bind(mySocket,(const sockaddr *) CHICHA, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        Exception("Error bind socket with local address",12);
        }

   
    rc = connect(mySocket, (const sockaddr*) NECHICHA, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        Exception("Error connect socket with remote server.", 13);
    }

   
    rc = send(mySocket, buffer, msgLen, 0);
    if (rc == -1) {
        close(mySocket);
        Exception("Error send mesCHICHAge", 14);
    }
    cout << " send: " << buffer << endl; 
      
    
    rc = recv(mySocket, buffer, 4096, 0);
    if (rc == -1) {
        close(mySocket);
       Exception("Error receive answer.", 15);
    }
    buffer[rc] = '\0'; 
    cout << " receive: " << buffer << endl; 
    
    close(mySocket);

    delete CHICHA;
    delete NECHICHA;
    delete[] buffer;
    return 0;
}