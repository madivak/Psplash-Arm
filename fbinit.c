/*  
 *
Kevin Amadiva <madivak@live.co.uk>
 *
 */
#include "fbinit.h"


#ifndef PAGE_SHIFT
	#define PAGE_SHIFT 12
#endif
#ifndef PAGE_SIZE
	#define PAGE_SIZE (1UL << PAGE_SHIFT)
#endif
#ifndef PAGE_MASK
	#define PAGE_MASK (~(PAGE_SIZE - 1))
#endif

int fb;
struct fb_var_screeninfo fb_var;
struct fb_var_screeninfo fb_screen;
struct fb_fix_screeninfo fb_fix;
unsigned char *fb_mem = NULL;
unsigned char *fb_screenMem = NULL;

int fb_init(char *device) {

	int fb_mem_offset;

	// get current settings (which we have to restore)
	if (-1 == (fb = open(device, O_RDWR))) {
		fprintf(stderr, "Open %s: %s.", device, strerror(errno));
		return 0;
	}
	if (-1 == ioctl(fb, FBIOGET_VSCREENINFO, &fb_var)) {
		fprintf(stderr, "Ioctl FBIOGET_VSCREENINFO error.");
		return 0;
	}
	if (-1 == ioctl(fb, FBIOGET_FSCREENINFO, &fb_fix)) {
		fprintf(stderr, "Ioctl FBIOGET_FSCREENINFO error.");
		return 0;
	}
	if (fb_fix.type != FB_TYPE_PACKED_PIXELS) {
		fprintf(stderr, "Can handle only packed pixel frame buffers.");
		goto err;
	}

	fb_mem_offset = (unsigned long)(fb_fix.smem_start) & (~PAGE_MASK);
	fb_mem = mmap(NULL, fb_fix.smem_len + fb_mem_offset, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
	if (-1L == (long)fb_mem) {
		fprintf(stderr, "Mmap error.");
		goto err;
	}
	// move viewport to upper left corner

	if (fb_var.xoffset != 0 || fb_var.yoffset != 0) {
		fb_var.xoffset = 0;
		fb_var.yoffset = 0;
		if (-1 == ioctl(fb, FBIOPAN_DISPLAY, &fb_var)) {
			fprintf(stderr, "Ioctl FBIOPAN_DISPLAY error.");
			munmap(fb_mem, fb_fix.smem_len);
			goto err;
		}
	}

	fb_screen = fb_var;
	fb_screen.xoffset = 0;
	//fb_screen.yoffset = fb_var.yres - 1; //adds double buffer which is not desired by Psplash, since psplash i think only writes to the 1st buffer.
	fb_screen.yoffset = 0;
	if (-1 == ioctl(fb, FBIOPAN_DISPLAY, &fb_screen)) {
		fprintf(stderr, "Ioctl FBIOPAN_DISPLAY error.");
		munmap(fb_mem, fb_fix.smem_len);
		goto err;
	}

	fb_screenMem = fb_mem + fb_mem_offset + (fb_var.yres * fb_var.xres * (fb_var.bits_per_pixel / 8));
	return 1;

err:
	if (-1 == ioctl(fb, FBIOPUT_VSCREENINFO, &fb_var))
		fprintf(stderr, "Ioctl FBIOPUT_VSCREENINFO error.");
	if (-1 == ioctl(fb, FBIOGET_FSCREENINFO, &fb_fix))
		fprintf(stderr, "Ioctl FBIOGET_FSCREENINFO.");
	return 0;
}

void fb_cleanup(void) {

	if (-1 == ioctl(fb, FBIOPUT_VSCREENINFO, &fb_var))
		fprintf(stderr, "Ioctl FBIOPUT_VSCREENINFO error.");
	if (-1 == ioctl(fb, FBIOGET_FSCREENINFO, &fb_fix))
		fprintf(stderr, "Ioctl FBIOGET_FSCREENINFO.");
	munmap(fb_mem, fb_fix.smem_len);
	close(fb);
}

/*
void main(void) {

	if (!fb_init("/dev/fb0"))
		exit(1);

	//<now you can write directly to fb_screenMem>
	while(1){};

	fb_cleanup();
}
*/