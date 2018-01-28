#include "nvwrapper.h"

int NvhostCtrlGpuDevice::ioctl(uint32_t request, void *data) {
	auto req = (LinuxNvhostCtrlGpuIoctl) request;
	printf("ioctl to nvhost ctrl gpu! %s\n", ioctl2str(req));
	switch(req) {
		case NVGPU_GPU_IOCTL_ALLOC_AS: {
			auto ret = pass_ioctl(request, data, true);
			auto nfd = ((int *) data)[1];
			add_device("/dev/nvhost-as-gpu.faux", 0, make_shared<NvhostAsGpuDevice>(), nfd);
			return ret;
		}
	}
	return pass_ioctl(request, data, true);
}
