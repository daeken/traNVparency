#pragma once

#include "nvwrapper.h"

class BaseDevice {
public:
	BaseDevice() {
	}

	virtual ~BaseDevice() {
		free((void *) name);
	}

	int pass_ioctl(uint32_t request, void *data, bool debug = false);

	virtual int ioctl(uint32_t request, void *data) = 0;

	const char *name;
	int fd;
};

class NvmapDevice : public BaseDevice {
public:
	virtual int ioctl(uint32_t request, void *data);
};

class NvhostCtrlGpuDevice : public BaseDevice {
public:
	virtual int ioctl(uint32_t request, void *data);
};

class NvhostAsGpuDevice : public BaseDevice {
public:
	virtual int ioctl(uint32_t request, void *data);
};

class ChannelDevice : public BaseDevice {
public:
	virtual int ioctl(uint32_t request, void *data);
};

class NvhostGpuDevice : public ChannelDevice {
};

int handle_open(const char *pathname, int flags, bool &handled);
int handle_ioctl(int fd, unsigned long request, void *data, bool &handled);
int handle_close(int fd, bool &handled);

int add_device(const char *name, int flags, shared_ptr<BaseDevice> dev, int fd = -1);
