#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include <dispatch/dispatch.h>
#include <dispatch/time.h>

#include <libssh2.h>

#include "tcpinfo.h"
#include "carbonplain.h"

struct loop_ctx {
	int fd;
	char *host;
} ctx = {-1};

void
mainloop(void *arg)
{
	struct loop_ctx *ctx = arg;
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

	fd_tcpinfo_carbon_sched(fd, "test.ssh", ctx->host, 2003);

	LIBSSH2_SESSION *session;
	session = libssh2_session_init();

	ctx->fd = fd;
	libssh2_session_handshake(session, fd);
}

int
main(int argc, char **argv)
{
	assert(argc == 2 && "usage: ./test ip-of-carbon-server");
	ctx.host = argv[1];
	dispatch_async_f(dispatch_get_main_queue(), &ctx, mainloop);
	dispatch_main();
	return 0;
}

