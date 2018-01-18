#include "nvwrapper.h"

int NvhostCtrlGpuDevice::ioctl(uint32_t request, void *data) {
	LinuxNvhostCtrlGpuIoctl req = request;
	printf("ioctl to nvhost ctrl gpu! %s\n", ioctl2str(req));
	return pass_ioctl(request, data, true);
}
