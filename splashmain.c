#include"types.h"
#include"x86.h"
/*
(x, y)
   ↓
y * screen_width + x
   ↓
byte offset from 0xA0000
   ↓
   0xA0000 + offset = PA
*/

static void
waitdisk(void)
{
    while ((inb(0x1F7) & 0xC0) != 0x40);
}

static void
readsect(void *dst, uint offset)
{
    waitdisk();

    outb(0x1F2, 1);
    outb(0x1F3, offset);
    outb(0x1F4, offset >> 8);
    outb(0x1F5, offset >> 16);
    outb(0x1F6, (offset >> 24) | 0xE0);
    outb(0x1F7, 0x20);

    waitdisk();

    insl(0x1F0, dst, 512 / 4);
}

void splashmain() {

    unsigned char *screen = (unsigned char *)0xA0000;

    for (int i = 0; i < 125; i++) {
        readsect(screen + i * 512, 1 + i);
    }

    while(1);
}
