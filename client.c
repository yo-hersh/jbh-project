#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "str_handling.h"

#define CONNECT_NUM 5

int main(int argc, char **argv)
{
    int sockfd[CONNECT_NUM];
    struct sockaddr_in serv_addr;
    char buffer[CONNECT_NUM][BUF_LEN] = {0};
    int n, i;

    if (argc < 3)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    printf("%s", massage);
    i = 0;
    while (1)
    {
        char temp_buf[BUF_LEN];
        fgets(temp_buf, BUF_LEN, stdin);
        if (buf_overflow(temp_buf,print_to_stdout,0))
        {
            continue;
        }
        
        if (!strcmp(temp_buf, "halp"))
        {
            printf("%s", display_option);
        }
        else if (!strcmp(temp_buf, "select --help"))
        {
            printf("%s%s", select_help, values_help);
        }
        else if (!strcmp(temp_buf, "set --help"))
        {
            printf("%s%s", set_help, values_help);
        }
        else if (!strcmp(temp_buf, "quit"))
        {
            puts("See you, thanks for using the DB program");
            return EXIT_SUCCESS;
        }
        else if (!strcmp(temp_buf, "send"))
        {
            break;
        }
        else if (i < CONNECT_NUM)
        {
            strcpy(buffer[i++], temp_buf);
        }
    }

    for (i = 0; buffer[i][0]; i++)
    {
        sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd[i] < 0)
        {
            perror("Error creating socket");
            return EXIT_FAILURE;
        }
        if (connect(sockfd[i], (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            perror("Error connecting");
            return EXIT_FAILURE;
        }
    }

    for (i = 0; buffer[i][0]; i++)
    {
        n = send(sockfd[i], buffer[i], strlen(buffer[i]), 0);
        if (n < 0)
        {
            perror("Client error sending data");
            return EXIT_FAILURE;
        }
        shutdown(sockfd[i], SHUT_WR);
    }

    for (i = 0; i < CONNECT_NUM && buffer[i][0]; i++)
    {
        do
        {
            n = recv(sockfd[i], buffer[i], BUF_LEN, 0);
            if (n < 0)
            {
                perror("Client error receiving data");
                return EXIT_FAILURE;
            }
            else if (n > 0)
            {
                buffer[i][n] = '\0';
                printf("%s", buffer[i]);
            }
        } while (n > 0);
        close(sockfd[i]);
    }

    return EXIT_SUCCESS;
}