/* 
 * Kevin Amadiva <madivak@live.co.uk>
 */

#ifndef _HAVE_FBINIT_H
#define _HAVE_FBINIT_H

#include <linux/kd.h>
#include <linux/vt.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> //for strerror
#include <sys/user.h>
#include <errno.h> //for stderr
#include <fcntl.h> //for open
#include <unistd.h> //for close
#include <sys/mman.h> //for PROT_WRITE/READ & MAP_SHARED
#include <sys/stat.h>

int fb_init(char *device);
void fb_cleanup(void);


#endif