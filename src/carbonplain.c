#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "carbonplain.h"

#define MAX_MSG_PATH 100
#define MAX_MSG_LEN_PLAIN 130

int
carbon_connect_fd(const char *host, int port)
{
	int sockfd;
	struct sockaddr_in serv_addr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0) {
		perror("inet_pton");
		return -1;
	}

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("connect");
		return -1;
	}

	return sockfd;
}

void
carbon_dispatch(dispatch_queue_t queue, dispatch_io_t chan, const char *path, float value, unsigned long timestamp)
{
	char *buf = NULL;
	int len = asprintf(&buf, "%s %.2f %lu\n", path, value, timestamp);

	dispatch_data_t data = dispatch_data_create(buf, len, queue, DISPATCH_DATA_DESTRUCTOR_FREE);
	dispatch_io_write(chan, 0, data, queue,
			^(bool done, dispatch_data_t data, int error) {
				if (!error) return;
				printf("carbon_dispatch failed: data %p, done %d error %d\n", data, done, error);
			});
}
