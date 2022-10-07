#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/slab.h>

#define MAX_DATA_SIZE 100

static ssize_t caesar_cipher(void);
static int caesar_dev_open(struct inode *inode, struct file *file);
static int caesar_dev_close(struct inode *inode, struct file *file);
static ssize_t caesar_dev_read(struct file *file, char __user *buf, size_t count, loff_t *offset);
static ssize_t caesar_dev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset);

// initialize file_operations
static const struct file_operations caesar_fops = {
    .owner      = THIS_MODULE,
    .open       = caesar_dev_open,
    .release    = caesar_dev_close,
    .read       = caesar_dev_read,
    .write       = caesar_dev_write
};

// for the direction, + is encryption, and - is decription
struct caesar_device_data {
    struct cdev cdev;
    uint32_t key;
    uint32_t size;
    char direction;
    char message[MAX_DATA_SIZE];
    // ADD FIELDS HERE FOR ADDITIONNAL DATA
};




// DEVICE MAJOR NUMBER
static int dev_major = 0;

// SYSFS_CLASS_STRUCTURE
static struct class *caesardev_class = NULL;

//CAESAR DEVICE DATA
static struct caesar_device_data caesardev_data;

//caesar cipher function 
//this function returns the size of the encrypted message or -1 if there was an error
static ssize_t caesar_cipher() {
	char ch;
	int i;
	if(caesardev_data.direction == '-') {
		for(i = 0; caesardev_data.message[i] != '\0'; ++i){
			ch = caesardev_data.message[i];
			if(ch >= 'a' && ch <= 'z'){
				ch = ch - caesardev_data.key;
				if(ch < 'a'){
					ch = ch + 'z' - 'a' + 1;
				}
				caesardev_data.message[i] = ch;
			}
			else if(ch >= 'A' && ch <= 'Z'){
				ch = ch - caesardev_data.key;
				if(ch < 'A'){
					ch = ch + 'Z' - 'A' + 1;
				}
			caesardev_data.message[i] = ch;
			} else {
				return -1;
			}
		}
	} else {
		for(i = 0; caesardev_data.message[i] != '\0'; ++i){
			ch = caesardev_data.message[i];
			if(ch >= 'a' && ch <= 'z'){
				ch = ch + caesardev_data.key;
				if(ch > 'z'){
					ch = ch - 'z' + 'a' - 1;
				}
				caesardev_data.message[i] = ch;
			}
			else if(ch >= 'A' && ch <= 'Z'){
				ch = ch + caesardev_data.key;
				if(ch > 'Z'){
					ch = ch - 'Z' + 'A' - 1;
				}
			caesardev_data.message[i] = ch;
			} else {
				return -1;
			}
		}
	}
	printk("The new message is : %s", caesardev_data.message);
		return 0;
}

//FUNCTION THAT GIVES PERMISSIONS TO THE DEVICE
static int caesardev_uevent(struct device *dev, struct kobj_uevent_env *env)
{
    add_uevent_var(env, "DEVMODE=%#o", 0666);
    return 0;
}

//SYSFS FUNCTIONS TEMPLATE
static ssize_t name_show(struct device *dev, struct device_attribute *attr,
                        char *buf)
{
        //SHOW NAME
}

static ssize_t name_store(struct device *dev, struct device_attribute *attr,
                        const char *buf, size_t count)
{
        //STORE <NAME> SOMEWHERE
}

//DEVINE SYSFS ATTRIBUTES HERE



//ATTRIBUTES REGISTRATION
struct attribute *caesar_attrs[] = {
    &dev_attr_key.attr,
    &dev_attr_size.attr,
    NULL,
};


static const struct attribute_group caesar_attr_group = {
    .name = "caesardev", /* directory's name */
    .attrs = caesar_attrs,
};
static const struct attribute_group *attrs_groups[] = {&caesar_attr_group, NULL};

static int __init caesardev_init(void)
{
	int err;
	dev_t dev;
	// ADD YOUR CODE HERE
}

static void __exit caesardev_destroy(void)
{
	// ADD YOUR CODE HERE   
}
	

	
static int caesar_dev_open(struct inode *inode, struct file *file)
{
    //FEEL FREE TO ADD WHATEVER YOU WANT HERE :)
    printk("CAESARDEV: Device open\n");
    return 0;
}

static int caesar_dev_close(struct inode *inode, struct file *file)
{
    //FEEL FREE TO ADD WHATEVER YOU WANT HERE :)
    printk("CAESARDEV: Device close\n");
    return 0;
}

static ssize_t caesar_dev_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    //ADD YOUR CODE HERE
    printk("CAESARDEV: Device read\n");
    return 0;
}

static ssize_t caesar_dev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    //ADD YOUR CODE HERE
    printk("CAESARDEV: Device write\n");
    return 0;
}
	
MODULE_LICENSE("GPL");
MODULE_AUTHOR("you <your email>");	

module_init(caesardev_init);
module_exit(caesardev_destroy);	
	
	
