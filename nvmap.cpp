#include "nvwrapper.h"

int NvmapDevice::ioctl(uint32_t request, void *data) {
	printf("ioctl to nvmap! %08x\n", request);
	return pass_ioctl(request, data, true);
}
