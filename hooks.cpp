#define HOOKS_DEF
#include "nvwrapper.h"

#define ioctl old_ioctl
#include <linux/ioctl.h>
#undef ioctl

#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#define open old_open
#include <fcntl.h>
#undef open
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define RTLD_NEXT ((void *) -1L)

int (*real_open)(const char *, int);
int (*real_ioctl)(int, unsigned long, void *);

extern "C" {
	extern void *_dl_sym(void *, const char *, void *);
	void *orig_dlsym(void *handle, const char *name) {
		static void * (*real_dlsym)(void *, const char *) = NULL;
		if (real_dlsym == NULL)
			real_dlsym = (void* (*)(void*, const char*)) _dl_sym(RTLD_NEXT, "dlsym", (void *) orig_dlsym);
		return real_dlsym(handle, name);
	}

	void fuckfds() {
		static bool has_fucked = false;
		if(has_fucked)
			return;
		has_fucked = true;

		int pfd[2];
		for(int i = 0; i < 0xdea2; i += 2)
			pipe(pfd);
	}

	int open(const char *pathname, int flags) {
		fuckfds();

		if(real_open == NULL)
			real_open = (int (*)(const char *, int)) orig_dlsym(RTLD_NEXT, "open");

		bool handled;
		auto hfd = handle_open(pathname, flags, handled);
		if(handled)
			return hfd;
		return real_open(pathname, flags);
	}

	int export_open(const char *pathname, int flags) {
		return open(pathname, flags);
	}

	int ioctl(int fd, unsigned long request, void *data) {
		if(real_ioctl == NULL)
			real_ioctl = (int (*)(int, unsigned long, void *)) orig_dlsym(RTLD_NEXT, "ioctl");
		bool handled;
		auto ret = handle_ioctl(fd, request, data, handled);
		if(!handled)
			ret = real_ioctl(fd, request, data);
		return ret;
	}

	int close(int fd) {
		printf("Closing %i\n", fd);
		static int (*real_close)(int) = NULL;
		if(real_close == NULL)
			real_close = (int (*)(int)) orig_dlsym(RTLD_NEXT, "close");
		bool handled;
		auto ret = handle_close(fd, handled);
		if(handled)
			return ret;
		return real_close(fd);
	}

	extern void *dlsym(void *handle, const char *name) {
		printf("dlsym for %s\n", name);
		return orig_dlsym(handle, name);
	}
}
