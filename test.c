#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <dispatch/dispatch.h>
#include <dispatch/time.h>

#include <libssh2.h>

#include "tcpinfo.h"

#define T_TIMEOUT 50LL * NSEC_PER_MSEC

static dispatch_queue_t statq;

struct tick_ctx {
	int fd;
} ctx = {-1};

void
tick_stat(void *arg)
{
	struct tick_ctx *ctx = arg;
	dispatch_time_t milestone;

	if (ctx->fd < 0) {
		printf("noconn\n");
		goto resched;
	}

	struct tcp_info *info;
	info = calloc(1, sizeof(*info));
	if (ats_tcpinfo(ctx->fd, info) == 0) {
		char *buf = tcp_info_str(info);
		printf("rtt: %u rxpackets: %llu txpackets: %llu\n", info->tcpi_rttcur, info->tcpi_rxpackets, info->tcpi_txpackets);
		free(buf);
	} else {
		perror("getsockopt");
	}
	free(info);

resched:
	milestone = dispatch_time(DISPATCH_TIME_NOW, T_TIMEOUT);
	dispatch_after_f(milestone, statq, ctx, tick_stat);
}

void
mainloop(void *arg)
{
	struct tick_ctx *ctx = arg;
	libssh2_init(0);
	
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(22);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(fd, (struct sockaddr*)(&sin),
				sizeof(struct sockaddr_in)) != 0) {
		fprintf(stderr, "failed to connect!\n");
	}

	LIBSSH2_SESSION *session;
	session = libssh2_session_init();

	ctx->fd = fd;
	libssh2_session_handshake(session, fd);
}

int
main(int argc, char **argv)
{
	statq = dispatch_queue_create("wow.statq", NULL);

	tick_stat(&ctx);
	dispatch_async_f(dispatch_get_main_queue(), &ctx, mainloop);

	dispatch_main();
	return 0;
}
