#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "tcpinfo.h"
#include "carbonplain.h"

#define	TCP_INFO		0x200	/* retrieve tcp_info structure */

#define T_TIMEOUT		(1000LL * NSEC_PER_MSEC)

int
fd_tcpinfo(int fd, struct tcp_info *info)
{
	socklen_t len = sizeof(*info);
	int rc = getsockopt(fd, IPPROTO_TCP, TCP_INFO, info, &len);
	/*
	 printf("len: %d sizeof %d ", len, sizeof(*info));
	 */
	return rc;
}


static void
fd_tcpinfo_carbon_tick(void *arg)
{
	struct carbon_ctx *ctx = arg;
	dispatch_time_t milestone;
	struct tcp_info i = {0};
	struct tcp_info *info = &i;

	if (ctx->fd < 0) {
		printf("noconn\n");
		goto resched;
	}

	if (fd_tcpinfo(ctx->fd, info) == 0) {
		time_t ts;
		time(&ts);

		const char *qname = dispatch_queue_get_label(ctx->queue);
		char label[1024];

		snprintf(label, sizeof(label), "%s.rtt", qname);
		carbon_dispatch(ctx->queue, ctx->io, label, info->tcpi_rttcur, ts);

		snprintf(label, sizeof(label), "%s.rxpackets", qname);
		carbon_dispatch(ctx->queue, ctx->io, label, info->tcpi_rxpackets, ts);

		snprintf(label, sizeof(label), "%s.txpackets", qname);
		carbon_dispatch(ctx->queue, ctx->io, label, info->tcpi_txpackets, ts);

		printf("%s rtt: %u rxpackets: %llu txpackets: %llu\n", qname, info->tcpi_rttcur, info->tcpi_rxpackets, info->tcpi_txpackets);
	} else {
		perror("getsockopt");
	}

resched:
	milestone = dispatch_time(DISPATCH_TIME_NOW, T_TIMEOUT);
	dispatch_after_f(milestone, ctx->queue, ctx, fd_tcpinfo_carbon_tick);
}

struct carbon_ctx *
fd_tcpinfo_carbon_sched(int fd, char *identifier, char *host, int port)
{
	char *qname = NULL;
	asprintf(&qname, "tcpinfo.%s", identifier);
	assert(strlen(qname) < 1000); /* see label[1024] */

	struct carbon_ctx *ctx = calloc(1, sizeof(*ctx));

	ctx->queue = dispatch_queue_create(qname, NULL);
	free(qname);
	ctx->carbon_fd = carbon_connect_fd(host, port);
	ctx->io = dispatch_io_create(DISPATCH_IO_STREAM, ctx->carbon_fd, ctx->queue,
			^(int error) { if (error) printf("%s: io error %d\n", qname, error); close(fd); });
	ctx->fd = fd;

	dispatch_async_f(ctx->queue, ctx, fd_tcpinfo_carbon_tick);

	return ctx;
}
