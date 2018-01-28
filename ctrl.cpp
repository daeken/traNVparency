#include "nvwrapper.h"

int NvhostCtrlDevice::ioctl(uint32_t request, void *data) {
	auto req = (LinuxNvhostCtrlIoctl) request;
	printf("ioctl to nvhost ctrl! %s\n", ioctl2str(req));
	switch(req) {
	}
	return pass_ioctl(request, data, true);
}
