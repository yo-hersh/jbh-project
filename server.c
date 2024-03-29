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

void *conn_handler(void *args);
void send_error_invalid(int socket_id);
void send_to_client(int socket_id, const char *str);
void int_handler(int sig);

int main(int argc, char **argv)
{
    // handle ctrl+c interrupter
    signal(SIGINT, int_handler);
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t len = sizeof(cli_addr);

    if (argc < 4)
    {
        printf("Usage: %s <db file> <ip> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("Error: file %s not found\n", argv[1]);
        return EXIT_FAILURE;
    }

    create_list(file);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return EXIT_FAILURE;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[3]));
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error binding socket");
        return EXIT_FAILURE;
    }

    if (listen(sockfd, 5) < 0)
    {
        perror("Error listening");
        return EXIT_FAILURE;
    }

    while (1)
    {
        pthread_t tid;
        int new_sock = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&len);
        if (new_sock < 0)
        {
            perror("accept failed");
            return EXIT_FAILURE;
        }

        // send the location of new_sock because I'm using a join, so it's safe to say it won't change throughout the thread
        pthread_create(&tid, NULL, conn_handler, &new_sock);
        pthread_join(tid, NULL);
    }
    free_all();

    return EXIT_SUCCESS;
}

void *conn_handler(void *args)
{
    char buf[BUF_LEN] = {0};
    int new_sock = *((int *)args);
    int n, r = 0;

    do
    {
        n = recv(new_sock, buf + r, BUF_LEN - r, 0);
        if (n < 0)
        {
            perror("Server error receiving data");
            goto exit;
        }
        r += n;
    } while (n > 0);
    remove_white_spaces(buf);

    buf[r] = '\0';
    if (strlen(buf) == 0)
    {
        send_error_invalid(new_sock);
    }
    else if (strstr(buf, "print"))
    {
        print_all(send_to_client, new_sock);
    }
    else
    {
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = '\0';
        }
        if (buf[0])
        {
            input_handling(buf, send_to_client, new_sock);
        }
    }

exit:
    close(new_sock);
    return NULL;
}

void send_to_client(int socket_id, const char *str)
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

void int_handler(int sig)
{
    free_all();
    printf("\nexiting....\n");
    exit(0);
}