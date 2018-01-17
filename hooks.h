#pragma once

#ifndef HOOKS_DEF

extern "C" {
	extern int (*real_open)(const char *, int);
	extern int (*real_ioctl)(int, unsigned long, void *);
}

#endif
