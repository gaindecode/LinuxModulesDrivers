#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xe0788817, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x6dc0c9dc, __VMLINUX_SYMBOL_STR(down_interruptible) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x78e739aa, __VMLINUX_SYMBOL_STR(up) },
	{ 0xfdaa9379, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x72bd131c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x32f0c463, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x10feafe7, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0x41a5057e, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xb6fa20e4, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x9e63bde6, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0E8Fp0003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v044FpB315d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "BAEAE6CE2B557DC7D03EE70");
