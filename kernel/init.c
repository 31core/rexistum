#include <utils.h>
#include <config.h>
#include <arch/x86/cpu.h>
#include <device/interrupt/init.h>
#include <device/input/keyboard.h>
#include <kernel/page.h>
#include <kernel/user.h>
#include <kernel/task.h>
#include <kernel/pipe.h>
#include <kernel/memory.h>
#include <kernel/timer.h>
#include <kernel/random.h>
#include <kernel/sysinfo.h>
#include <kernel/fs/fs.h>
#include <device/video/cli_print.h>

/* 初始化内核 */
void kernel_init(void)
{
	cpu_init(); //初始化cpu相关设定
	sysinfo_init();
	/* 初始化内存碎片管理 */
	memfrag_init();
	memfrag_alloc_with_addr((void*)GDT_ADDR, 8 * 0x2000);
	memfrag_alloc_with_addr((void*)IDT_ADDR, 8 * 0x100);
	memfrag_alloc_with_addr((void*)KERNEL_ADDR, KERNEL_SIZE); //为内核分配4MB空间
	memfrag_alloc_with_addr((void*)KERNEL_STACK_ADDR, KERNEL_STACK_SIZE);
	fifo_init(&key_fifo, memfrag_alloc_4k(1), 0x1000);
	page_init();
	task_init(); //初始化多任务
	PIC_init(); //初始化PIC
	io_sti(); //启用中断
	random_init();
	fs_init(); //初始化文件系统
	user_init();
}
