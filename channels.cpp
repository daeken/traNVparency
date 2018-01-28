#include "nvwrapper.h"

struct nvgpu_fence {
	uint32_t id;        /* syncpoint id or sync fence fd */
	uint32_t value;     /* syncpoint value (discarded when using sync fence) */
};

struct gpfifo_entry {
   uint32_t entry0;                           // gpu_va_lo
   uint32_t entry1;                           // gpu_va_hi | (unk_0x02 << 0x08) | (size << 0x0A) | (unk_0x01 << 0x1F)
 };

struct nvgpu_submit_gpfifo_args {
	uint64_t gpfifo;
	uint32_t num_entries;
	uint32_t flags;
	struct nvgpu_fence fence;
};

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
		case NVGPU_IOCTL_CHANNEL_SUBMIT_GPFIFO: {
			auto arg = (nvgpu_submit_gpfifo_args *) data;
			printf("gpfifo submission from %p of %i entries\n", (void *) arg->gpfifo, arg->num_entries);
			auto entries = (gpfifo_entry *) arg->gpfifo;
			for(auto i = 0; i < arg->num_entries; ++i) {
				printf("entry %i %08x %08x\n", i, entries[i].entry0, entries[i].entry1);
			}
			break;
		}
	}
	return pass_ioctl(request, data, true);
}

shared_ptr<ChannelDevice> NvhostGpuDevice::construct() {
	return make_shared<NvhostGpuDevice>();
}
