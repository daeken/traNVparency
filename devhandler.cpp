#include "nvwrapper.h"
#define ioctl old_ioctl
#include <linux/ioctl.h>
#undef ioctl

int BaseDevice::pass_ioctl(uint32_t request, void *data) {
	return real_ioctl(fd, request, data);
}

unordered_map<int, shared_ptr<BaseDevice>> devices;

int add_device(const char *name, int flags, shared_ptr<BaseDevice> dev) {
	auto fd = real_open(name, flags);
	printf("Adding device %i from %s\n", fd, name);
	dev->name = strdup(name);
	dev->fd = fd;
	devices[fd] = dev;
	return fd;
}

int handle_open(const char *pathname, int flags, bool &handled) {
	handled = true;
	if(!strcmp(pathname, "/dev/nvmap"))
		return add_device(pathname, flags, make_shared<NvmapDevice>());
	else if(!strncmp(pathname, "/dev/", 5))
		printf("Attempted device open %s\n", pathname);
	handled = false;
	return 0;
}

int handle_ioctl(int fd, unsigned long request, void *data, bool &handled) {
	handled = true;
	if(devices.find(fd) != devices.end())
		return devices[fd]->ioctl((uint32_t) request, data);
	printf("0x%x byte (%s%s) Ioctl 0x%08X to %i\n", (uint32_t) _IOC_SIZE(request), (_IOC_DIR(request) & _IOC_READ) == _IOC_READ ? "IN" : "", (_IOC_DIR(request) & _IOC_WRITE) == _IOC_WRITE ? "OUT" : "", (uint32_t) request, fd);
	if((_IOC_DIR(request) & _IOC_WRITE) == _IOC_WRITE) {
		printf("Outgoing:\n");
		hexdump((unsigned char *) data, _IOC_SIZE(request));
	}
	int ret = real_ioctl(fd, request, data);
	if((_IOC_DIR(request) & _IOC_READ) == _IOC_READ) {
		printf("Incoming:\n");
		hexdump((unsigned char *) data, _IOC_SIZE(request));
	}
	printf("Ioctl returned %i\n", ret);
	return ret;
}

int handle_close(int fd, bool &handled) {
	handled = false;
	return 0;
}
