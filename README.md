# Psplash-Arm

## Task

Psplash was being launched but could not Display unless the fb mode was set ("head -1 /sys/class/graphics/fb0/modes > /sys/class/graphics/fb0/mode"). fbinit.c and fbinit.h were added to enable psplash to correctly initialize the framebuffer in the standard Linux way(DRM/KMS) using ioctl() and be able to display the splash image.

## Test Device

This patched Psplash was tested on an Allwinner A20 with an attached RGB LCD Display

## Resources

Original source code: http://github.com/downloads/liquidware/liquidware_beagleboard_linux/psplash-r424.tgz

The Linux FB initialization information from here: https://community.khronos.org/t/write-to-framebuffer-directly/921/3

## Research

Further reading on Linux DRM subsystem KMS essential to understanding the new Linux way of writting to the framebuffer check the following links:
> https://events.static.linuxfound.org/sites/events/files/slides/brezillon-drm-kms.pdf

> https://archive.fosdem.org/2020/schedule/event/fbdev/attachments/slides/3595/export/events/attachments/fbdev/slides/3595/fosdem_2020_nicolas_caramelli_linux_framebuffer.pdf

> https://www.kernel.org/doc/html/v4.15/gpu/drm-kms.html

The PDFs are also included in this repo

## Building Psplash

### Requirements

```apt-get install libgtk2.0-dev```

### Source the repo & Get into directory

```cd psplash-r424```

### Generate your Image header

**_(Assuming you have put your image.png in the current directory with the correct pixel size matching your display)_**

```make-image-header.sh image.png POKY```

```cp image-img.h psplash-poky-img.h```

~~(The following step is not necessary since the bar feature was removed as progress bar feature was not desired)~~

~~($make-image-header.sh barblack.png BAR ; mv barblack-img.h psplash-bar-img.h)~~

### Build Psplash 

**_(Assuming arm-linux-gnueabihf-gcc is the correct CC for your device and the header files are in /usr/arm-linux-gnueabihf)_**

```arm-linux-gnueabihf-gcc -o psplash  psplash.c psplash.h fbinit.c fbinit.h  psplash-fb.c psplash-fb.h psplash-console.c psplash-console.h psplash-poky-img.h psplash-bar-img.h -I/usr/arm-linux-gnueabihf```

## END: 

You should have psplash generated. Copy it to your target and test it.
