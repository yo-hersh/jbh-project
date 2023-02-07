#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "str_handling.h"
#include "users_input.h"
#include "DB.h"

#define MAX_LEN 1024

void *conn_handler(void *args);
void send_error_invalid(int socket_id);
void send_to_client(int socket_id, char *str);
void print_to_stdin(int socket_id, char *str);
void int_handler(int sig);

int main(int argc, char **argv)
{
    signal(SIGINT, int_handler);
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t len = sizeof(cli_addr);

    if (argc < 4)
    {
        printf("Usage: %s <db file> <ip> <port>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("Error: file %s not found\n", argv[1]);
        return 1;
    }

    create_list(file, print_to_stdin, 0);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[3]));
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error binding socket");
        return 1;
    }

    if (listen(sockfd, 5) < 0)
    {
        perror("Error listening");
        return 1;
    }

    while (1)
    {
        pthread_t tid;
        int new_sock = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&len);
        if (new_sock < 0)
        {
            perror("accept failed");
            return 1;
        }

        pthread_create(&tid, NULL, conn_handler, (void *)new_sock);
        pthread_join(tid, NULL);
    }
    free_all();

    return 0;
}

void *conn_handler(void *args)
{
    char buffer[MAX_LEN] = {0};
    int new_sock = (int)args;
    int n, r = 0;

    do
    {
        n = recv(new_sock, buffer + r, MAX_LEN - r, 0);
        if (n < 0)
        {
            perror("Server error receiving data");
            goto exit;
        }
        r += n;
    } while (n > 0);
    remove_white_spaces(buffer);

    buffer[r] = '\0';
    if (strlen(buffer) == 0)
    {
        send_error_invalid(new_sock);
    }
    else if (strstr(buffer, "print"))
    {
        print_all(send_to_client, new_sock);
    }
    else
    {
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }
        if (buffer[0])
        {
            user_str(buffer, send_to_client, new_sock);
        }
    }

exit:
    close(new_sock);
    return NULL;
}

void send_to_client(int socket_id, char *str)
{
    int n;
    n = send(socket_id, str, strlen(str), 0);
    if (n < 0)
    {
        perror("Server error sending data");
        return;
    }
}

void send_error_invalid(int socket_id)
{
    char *str = "invalid value";
    send_to_client(socket_id, str);
}

void print_to_stdin(int socket_id, char *str)
{
    printf("%s", str);
}

void int_handler(int sig)
{
    free_all();
    printf("\nexiting....\n");
    exit(0);
}