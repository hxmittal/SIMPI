// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>
#include <array>
#define PORT 8080 
int main(int argc, char const *argv[]) 
{
    //while (true) 
    //{
        int server_fd, new_socket, valread; 
        struct sockaddr_in address; 
        int opt = 1; 
        int addrlen = sizeof(address); 
        int numprocess = 0;
        int nummachines = 0;
        int workstationid = 0;
        
           
        // Creating socket file descriptor 
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
        { 
            perror("socket failed"); 
            exit(EXIT_FAILURE); 
        } 
           
        // Forcefully attaching socket to the port 8080 
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , 
                                                      &opt, sizeof(opt))) 
        { 
            perror("setsockopt"); 
            exit(EXIT_FAILURE); 
        } 
        address.sin_family = AF_INET; 
        address.sin_addr.s_addr = INADDR_ANY; 
        address.sin_port = htons( PORT ); 
           
        // Forcefully attaching socket to the port 8080 
        if (bind(server_fd, (struct sockaddr *)&address,  
                                     sizeof(address))<0) 
        { 
            perror("bind failed"); 
            exit(EXIT_FAILURE); 
        } 
        if (listen(server_fd, 3) < 0) 
        { 
            perror("listen"); 
            exit(EXIT_FAILURE); 
        } 
        ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                           (socklen_t*)&addrlen))>0);
            /*{ 
                perror("accept"); 
                exit(EXIT_FAILURE); 
            } */
            read( new_socket , &numprocess, sizeof(int)); 
            read( new_socket , &nummachines, sizeof(int)); 
            read( new_socket, &workstationid, sizeof(int));
            printf("%d", numprocess);
            printf("\n");
            char progname[100];
            strcpy(progname, "mpi");
            char user[100];
            strcpy(user, "user");
            std::string worker_count_str = std::to_string(numprocess);
            std::string machine_count_str = std::to_string(nummachines);
            std::string workstation_id_str = std::to_string(workstationid);
            char * args[6] = {progname, user,  const_cast<char*>(worker_count_str.c_str()), const_cast<char*>(machine_count_str.c_str()), const_cast<char*>(workstation_id_str.c_str()),  NULL};
            if(fork()==0)
            {
                std::cout << progname << "\n";
                std::cout << user << "\n";
                std::cout << numprocess << "\n";
                execv(progname, args);
            }

            close(new_socket);
        }
        
    //} 
