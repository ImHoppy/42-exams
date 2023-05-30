#define PORT_ERROR "Wrong number of arguments\n"
#define PORT_ERROR_LENGTH 26
#define FATAL_ERROR "Fatal error\n"
#define FATAL_ERROR_LENGTH 12
#define JOIN_MSG "server: client %d just arrived\n"
#define LEFT_MSG "server: client %d just left\n"
#define NEW_MSG "client %d: %s"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/select.h>

int g_sockfd = 0;
int g_id = 0;

typedef struct s_client
{
	int id;
	char *msg;
} t_client;

void fatal(void)
{
	write(2, FATAL_ERROR, FATAL_ERROR_LENGTH);
	close(g_sockfd);
	exit(1);
}

int extract_message(char **buf, char **msg)
{
	char *newbuf;
	int i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				fatal();
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char *newbuf;
	int len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		fatal();
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

int main(int ac, char **av, char **env)
{
	if (ac < 2)
	{
		write(2, PORT_ERROR, PORT_ERROR_LENGTH);
		return (1);
	}
	if ((g_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		fatal();

	struct sockaddr_in servaddr;

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); // 127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));

	if ((bind(g_sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		fatal();
	if (listen(g_sockfd, 10) != 0)
		fatal();

	t_client clients[FD_SETSIZE];
	fd_set rfds, rfds_copy;
	FD_ZERO(&rfds);
	FD_SET(g_sockfd, &rfds);

	while (1)
	{
		rfds_copy = rfds;
		if (select(FD_SETSIZE, &rfds_copy, NULL, NULL, NULL) < 0)
		{
			perror("select");
			fatal();
		}

		for (int i = 0; i < FD_SETSIZE; ++i)
		{
			if (!FD_ISSET(i, &rfds_copy))
				continue;
			if (i == g_sockfd)
			{
				// Server
				int client_socket = accept(g_sockfd, NULL, NULL);
				if (client_socket < 0)
					fatal();
				FD_SET(client_socket, &rfds);
				clients[client_socket].id = g_id;
				clients[client_socket].msg = NULL;
				g_id++;
				char msg[64] = {};
				sprintf(msg, JOIN_MSG, g_id);
				int msg_len = strlen(msg);
				for (int c = 0; c < FD_SETSIZE; ++c)
				{
					if (c != client_socket && c != g_sockfd && FD_ISSET(c, &rfds))
					{
						write(c, msg, msg_len);
					}
				}
			}
			else
			{
				// Client
				char buf[4096] = {0};
				int rec = recv(i, buf, 4095, 0);
				if (rec < 1)
				{
					char msg[64] = {};
					sprintf(msg, LEFT_MSG, clients[i].id);
					int msg_len = strlen(msg);
					for (int c = 0; c < FD_SETSIZE; ++c)
					{
						if (c != i && c != g_sockfd && FD_ISSET(c, &rfds))
						{
							write(c, msg, msg_len);
						}
					}
					FD_CLR(i, &rfds);
					close(i);
				}
				else
				{
					buf[rec] = 0;
					char *msg = NULL;
					clients[i].msg = str_join(clients[i].msg, buf);
					while (extract_message(&(clients[i].msg), &msg) == 1)
					{
						char msg_to_send[64] = {};
						sprintf(msg_to_send, NEW_MSG, clients[i].id, msg);
						int msg_len = strlen(msg_to_send);
						for (int c = 0; c < FD_SETSIZE; ++c)
						{
							if (c != i && c != g_sockfd && FD_ISSET(c, &rfds))
							{
								write(c, msg_to_send, msg_len);
							}
						}
						free(msg);
						msg = NULL;
					}
                    if(strlen(clients[i].msg) == 0)
                    {
                        free(clients[i].msg);
                        clients[i].msg = NULL;
                    }
				}
			}
		}
	}

	return (0);
}
