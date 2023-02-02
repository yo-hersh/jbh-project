#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LEN 1024

int main(int argc, char **argv)
{
    char *display_option = "\n--please select option: set <value> / select <value> / print\n--use <option> --help to see more\n--type quit to exit\n";
    char *select_help = "--select <value> <operation> <everything>.\n";
    char *set_help = "--set <value> = <everything>.\n";
    char *values_help = "--values: first name, last name, id, phone, dept, date.\n";
    char *massage = "--Enter a 5 messages, to send it enter send. for options enter halp\n";

    int sockfd[5];
    struct sockaddr_in serv_addr;
    char buffer[5][MAX_LEN];
    int n, i;

    if (argc < 3)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[2]));

    printf("%s", massage);
    i = 0;
    while (1)
    {
        char temp_buf[MAX_LEN];
        fgets(temp_buf, MAX_LEN, stdin);
        if (!strcmp(temp_buf, "halp"))
        {
            // help_msg()
        }
        if (!strcmp(temp_buf, "quit\n"))
        {
            puts("see you, lets have a nice day");
            return 0;
        }
        else if (!strcmp(temp_buf, "send\n"))
        {
            break;
        }

        if (i < 5)
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
            return 1;
        }
        if (connect(sockfd[i], (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            perror("Error connecting");
            return 1;
        }
    }

    for (i = 0; buffer[i][0]; i++)
    {
        n = send(sockfd[i], buffer[i], strlen(buffer[i]) - 1, 0);
        if (n < 0)
        {
            perror("Client error sending data");
            return 1;
        }
        shutdown(sockfd[i], SHUT_WR);
    }

    for (i = 0; i < 5 && buffer[i][0]; i++)
    {
        do
        {
            n = recv(sockfd[i], buffer[i], MAX_LEN, 0);
            if (n < 0)
            {
                perror("Client error receiving data");
                return 1;
            }
            else if (n > 0)
            {
                buffer[i][n] = '\0';
                printf("%s", buffer[i]);
            }
        } while (n > 0);
        close(sockfd[i]);
    }

    return 0;
}