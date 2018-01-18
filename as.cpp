#include "nvwrapper.h"

int NvhostAsGpuDevice::ioctl(uint32_t request, void *data) {
	auto req = (LinuxNvhostAsGpuIoctl) request;
	printf("ioctl to nvhost-as-gpu! %s\n", ioctl2str(req));
	return pass_ioctl(request, data, true);
}
