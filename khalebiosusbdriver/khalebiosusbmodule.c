#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h> //file_operations structure. which of course allows use to open
#include <linux/cdev.h>// this is a char driver; makes cdev available
#include <linux/semaphore.h>//used to acces semaphores; sychronization behaviors
#include <asm/uaccess.h>//copy_to_user; copy_from_user;

#include <linux/usb.h>
#include <linux/slab.h> //for kmalloc

MODULE_AUTHOR("khalebios");
MODULE_DESCRIPTION("module de controle d'un usb");
MODULE_SUPPORTED_DEVICE("none");
MODULE_LICENSE("GPL");


//(2) To later register our device we need a cdev object and some other variables
struct cdev *mcdev;		//m stands for 'my'
int major_number;		//will store our major number- extracted from dev_t using macro - mknod /director/file c major minor
int ret;				//will be used to hold return values of functions; this is because the kernel tack is very small
						//so declaring variables all over the pass in our module functions eats up the stack very fast
dev_t dev_num;			//will hold major number that kernel gives use				
						//name--> appears in /proc/devices
#define DEVICE_NAME		"khalebiosusbdevice"
#define DEVICE_NAME_APP		"khalebiosusbdeviceApp"

/******************************************************************************/


//(1) create a structure for our fake device
struct fake_device{
	char data[100];
	struct semaphore sem;
}virtual_device;

struct usb_game {
	struct usb_device *	udev;

};




//(7) called on device_file open
//		inode reference to the file on disk
//		and contains information about that file
//		struct file is represents an abstract open file
int device_open(struct inode *inode,struct file *filp){
		
		//only allow one process to open this device by using a semaphore as mutual exclusive lock mutex 
		if(down_interruptible(&virtual_device.sem)!=0){
			printk(KERN_ALERT "khalebiosusbdeviceApp: could not lock device during open");
			return -1;
		}
		
		printk(KERN_INFO "khalebiosusbdeviceApp: opened device");
		return 0;
}

//(8) called when user wants to get information from the device 
ssize_t device_read(struct file* filp, char* bufStoreData, size_t bufCount, loff_t* curOffset){
		//take data from kernel space(device) to user space (process)
		//copy_to_user(destination, source,sizeToTransfer)
		printk(KERN_INFO "khalebiosusbdeviceApp: Reading from device");
		ret=copy_to_user(bufStoreData,virtual_device.data,bufCount);
		return ret;
}
//(9) called when user wants tosend information to the device 
ssize_t device_write(struct file* filp, const char* bufSourceData, size_t bufCount, loff_t* curOffset){
		//send data from user space to kernel space
		//copy_from_user(destination, source,count
		printk(KERN_INFO "khalebiosusbdeviceApp: Writing to device");
		ret=copy_from_user(virtual_device.data,bufSourceData,bufCount);
		return ret;
}

//(10) called upon user close
int device_close(struct inode *inode,struct file *filp){
		//by calling up, which i opposite of down for semaphore, we release the mutex that we obtained at device open
		//this has the effect of allowing other processs to use the device now
		up(&virtual_device.sem);
		printk(KERN_INFO "khalebiosusbdeviceApp: close device");
		return 0;
}

//HERE
//(6) Tell the kernel which functions to call when user operates on our device file
struct file_operations fops={
	//.owner=THIS_MODULE,		//prevent unloading of this module 
	.open=device_open,		//points to the method to call when openning the device
	.release=device_close,	//points to the method to call when closing the device 
	.write=device_write,	//points to the method to call when writing to device
	.read=device_read		//points to the method to call when reading from device
};

/*********************************************************************************/


//probe function
//called on device insertion if and only if no other driver has beat us to the punch
static int pen_probe (struct usb_interface *interface, const struct usb_device_id *id)
{
	printk(KERN_INFO "[*] khalebiosusbdevice USBDRIVER (%04X:%04X) plugged\n",id->idVendor, id->idProduct);
	printk(KERN_INFO "khalebiosusbdevice: Minor obtained: %d\n", interface->minor);
	//return 0;//return 0 indicates we will manage this device


	struct usb_device *udev = interface_to_usbdev(interface);
	struct usb_game *dev = NULL;
	int retval = -ENOMEM;

	dev = kmalloc(sizeof(struct usb_game), GFP_KERNEL);
	if (dev == NULL) {
		dev_err(&interface->dev, "Out of memory\n");
		goto error;
	}
	memset (dev, 0x00, sizeof (*dev));

	dev->udev = usb_get_dev(udev);

	usb_set_intfdata (interface, dev);


	dev_info(&interface->dev, "khalebiosusbdevise: USB GAME device now attached\n");
	return 0;

error:
	kfree(dev);
	return retval;

	
}


//discoonnect
static void pen_disconnect (struct usb_interface *interface)
{
	printk(KERN_INFO "[*] khalebiosUSBCode PENDRIVER removed\n");
	
}


static struct usb_device_id pen_table[]={
	//0e8f:0003
	{USB_DEVICE(0x0e8f,0x0003)},//information is obtained using "lsusb" at the command line
	{USB_DEVICE(0x044f,0xb315)},//044f:b315 ThrustMaster, Inc. Firestorm Dual Analog 3

	{},/*terminating entry*/
};

//usb driver
static struct usb_driver pen_driver=
{
	//.owner =THIS_MODULE,
	.name ="khalebiosusbdriver",
	.id_table=pen_table,//usb_device_id
	.probe=pen_probe,
	.disconnect =pen_disconnect,
};

MODULE_DEVICE_TABLE(usb,pen_table);


static int __init pen_init(void)
{
	int ret=-1;
	printk(KERN_INFO "khalebiosUSBdriver: Constructor of driver\n");
	printk(KERN_INFO "khalebiosUSBdriver:Registering Driver with kernel\n");
	ret= usb_register(&pen_driver);
    	printk(KERN_INFO "khalebiosUSBdriver:\tRegistration is completen\n");


	return ret;
}

static void __exit pen_exit(void)
{
	//deregister
	printk(KERN_INFO "khalebiosUSBdriver: DesConstructor of driver\n");
	usb_deregister(&pen_driver);
    	printk(KERN_INFO "khalebiosUSBdriver: \tUnRegistration is complete\n");

}
	
//Inform the kernel where to start and stop with our module/driver
module_init(pen_init);
module_exit(pen_exit);
