#include "nvwrapper.h"

int ChannelDevice::ioctl(uint32_t request, void *data) {
	printf("ioctl to channel device! %08x\n", request);
	return pass_ioctl(request, data, true);
}
