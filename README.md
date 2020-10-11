# Psplash-Arm


# Challenge

Psplash was being launched but could not Display unless the fb mode was set ("head -1 /sys/class/graphics/fb0/modes > /sys/class/graphics/fb0/mode"). This ended up causing a QT application to crash. fbinit.c and fbinit.h were added to enable psplash to correctly initialize the FB in the standard Linux way(DRM/KMS) using ioctl() and be able to display the splash image.

# Test Device

This patched Psplash was tested on an Allwinner A20 with a 1024X600 LCD Display

# Resources

Original source code: http://github.com/downloads/liquidware/liquidware_beagleboard_linux/psplash-r424.tgz
The Linux FB initialization information from here: https://community.khronos.org/t/write-to-framebuffer-directly/921/3

# Research

Further reading on Linux DRM subsystem KMS essential to understanding the new Linux way of writting to the framebuffer check the following links:
> https://events.static.linuxfound.org/sites/events/files/slides/brezillon-drm-kms.pdf

> https://archive.fosdem.org/2020/schedule/event/fbdev/attachments/slides/3595/export/events/attachments/fbdev/slides/3595/fosdem_2020_nicolas_caramelli_linux_framebuffer.pdf

> https://www.kernel.org/doc/html/v4.15/gpu/drm-kms.html

The PDFs are also included in this repo
