#include "nvwrapper.h"

int ChannelDevice::ioctl(uint32_t request, void *data) {
	auto req = (LinuxNvhostChannelIoctl) request;
	printf("ioctl to channel device! %s\n", ioctl2str(req));
	switch(req) {
		case NVGPU_IOCTL_CHANNEL_OPEN: {
			auto ret = pass_ioctl(request, data, true);
			auto nfd = *(int *) data;
			char str[strlen(name) + 7 + 8];
			sprintf(str, "%s#%x", name, nfd);
			add_device(str, 0, construct(), nfd);
			return ret;
		}
	}
	return pass_ioctl(request, data, true);
}

shared_ptr<ChannelDevice> NvhostGpuDevice::construct() {
	return make_shared<NvhostGpuDevice>();
}
