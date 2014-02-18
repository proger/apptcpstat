#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdio.h>

#include "tcpinfo.h"

#define	TCP_INFO		0x200	/* retrieve tcp_info structure */

int
ats_tcpinfo(int fd, struct tcp_info *info)
{
	socklen_t len = sizeof(*info);
	int rc = getsockopt(fd, IPPROTO_TCP, TCP_INFO, info, &len);
	printf("len: %d  sizeof %d ", len, sizeof(*info));
	return rc;
}
