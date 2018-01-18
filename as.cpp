#include "nvwrapper.h"

int NvhostAsGpuDevice::ioctl(uint32_t request, void *data) {
	return pass_ioctl(request, data, true);
}
