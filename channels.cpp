#include "nvwrapper.h"

int ChannelDevice::ioctl(uint32_t request, void *data) {
	auto req = (LinuxNvhostChannelIoctl) request;
	printf("ioctl to channel device! %s\n", ioctl2str(req));
	return pass_ioctl(request, data, true);
}
