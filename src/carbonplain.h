#include <dispatch/dispatch.h>

int carbon_connect_fd(const char *host, int port);
void carbon_dispatch(dispatch_queue_t queue, dispatch_io_t chan, const char *path, float value, unsigned long timestamp);

struct carbon_ctx {
	dispatch_io_t io;
	dispatch_queue_t queue;
	int fd;
	int carbon_fd;
};
