//
// Created by Алексей Михайлов on 12/12/2018.
//

#ifndef STAR_PLATINUM_HIEROPHANT_GREEN_H
#define STAR_PLATINUM_HIEROPHANT_GREEN_H

#endif //STAR_PLATINUM_HIEROPHANT_GREEN_H

#include <winsock2.h>

void stand(){




    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char *message, stp[]="stop" , server_reply[2000], rep[]="XY";
    int recv_size;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");


    ///server.sin_addr.s_addr = inet_addr("192.168.250.1");
    server.sin_addr.s_addr = inet_addr("10.0.75.200");
    server.sin_family = AF_INET;
    server.sin_port = htons(8000);

    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        //system("pause");

        return 1;
    }

    puts("Connected");

    //Send some data
    char buff[14];
    FILE *fin;
    fin=fopen("Gcod_out.txt","r");
    while(TRUE) {
        fscanf(fin,"%s",&buff,"\n");
        //fgets(buff, 14, fin);
        if (buff == EOF) {
            printf("End the line!");
        } else {
            //gets(buff);
            if (*buff == *stp) break;
            if (send(s, buff, 13, 0) < 0) {
                puts("Send failed");
                return 1;
            }
            puts("Data Send\n");

            //Receive a reply from the server
            if ((recv_size = recv(s, server_reply, 2000, 0)) == SOCKET_ERROR) {
                puts("recv failed");
            }

            puts("Reply received\n");
            //Add a NULL terminating character to make it a proper string before printing
            server_reply[recv_size] = '\0';
            puts(server_reply);
            while (!(*server_reply == *rep)) {
                recv_size = recv(s, server_reply, 2000, 0);
                puts(server_reply);

            }
        }

    }
    closesocket(s);
    WSACleanup();
    return 0;
};