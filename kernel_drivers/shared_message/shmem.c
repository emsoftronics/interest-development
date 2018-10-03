/*
 * =====================================================================================
 *
 *       Filename:  shmem.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Tuesday 28 August 2018 09:33:58  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */
#include <linux/kernel.h>  // for KERN_INFO
#include <linux/module.h>   // module_init, module_exit
#include <linux/init.h>   // __init and __exit macro
#include <linux/slab.h>   //kmalloc
#include <linux/cdev.h>    // alloc_cdev
#include <linux/fs.h>    // fs_operation
#include <linux/uaccess.h>          // Required for the copy to user function
#include <linux/kdev_t.h>          // Required for the copy to user function
#include <linux/mutex.h>          // Required for the copy to user function

#define SHMEM_MODULE    "shmem"
#define SHARED_BUFF_SIZE    256

MODULE_LICENSE("GPL");


struct shmem_data{
    dev_t dev;
    struct cdev cdev;
    int minors;
    int wi;
    int ri;
    int count;
    struct mutex lock;
    unsigned char shared_buffer[SHARED_BUFF_SIZE];
};

static struct shmem_data *smdata;

/**
 * This function is called when shm dev file is opened
 *
 */
static int shm_open(struct inode *inode_p, struct file *file_p)
{
    printk(KERN_INFO "SHM open funtion is called!!\n");
    return 0;
}

/**
 * This function is called when shm dev  file is closed
 *
 */
static int shm_release(struct inode *inode_p, struct file *file_p)
{
    printk(KERN_INFO "SHM close funtion is called!!\n");
    return 0;
}


/**
 * This function is called when shm dev file is read
 *
 */
static ssize_t shm_read(struct file *file_p, char *buffer_p, size_t size_p, loff_t *shift_p)
{
//    printk(KERN_INFO "SHM read funtion is called!!\n");
    int len = 0, tlen = 0;

    if (!smdata) return -1;
    mutex_lock(&smdata->lock);
    len = (size_p < smdata->count) ? size_p : smdata->count;

    if (len <= SHARED_BUFF_SIZE - smdata->ri) {
        copy_to_user(buffer_p, &smdata->shared_buffer[smdata->ri], len);
        smdata->ri = (smdata->ri + len) % SHARED_BUFF_SIZE;
    }
    else {
        tlen = SHARED_BUFF_SIZE - smdata->ri;
        copy_to_user(buffer_p, &smdata->shared_buffer[smdata->ri], tlen);
        smdata->ri = 0;
        copy_to_user(buffer_p + tlen, &smdata->shared_buffer[smdata->ri], len - tlen);
        smdata->ri = (smdata->ri + len - tlen) % SHARED_BUFF_SIZE;
    }
    smdata->count -= len;
    mutex_unlock(&smdata->lock);

    return len;
}

/**
 * This function is called when shm dev file is written
 *
 */
static ssize_t shm_write(struct file *file_p, const char *buffer_p, size_t size_p, loff_t *shift_p)
{
    //printk(KERN_INFO "SHM write funtion is called!!\n");
    int len = 0, rlen = 0;

    if (!smdata) return -1;

    mutex_lock(&smdata->lock);
    rlen = SHARED_BUFF_SIZE - smdata->count;
    len = (size_p < rlen) ? size_p : rlen;

    if (len <= SHARED_BUFF_SIZE - smdata->wi) {
        copy_from_user(&smdata->shared_buffer[smdata->wi], buffer_p, len);
        smdata->wi = (smdata->wi + len) % SHARED_BUFF_SIZE;
    }
    else {
        rlen = SHARED_BUFF_SIZE - smdata->wi;
        copy_from_user(&smdata->shared_buffer[smdata->wi], buffer_p, rlen);
        smdata->wi = 0;
        copy_from_user(&smdata->shared_buffer[smdata->wi], buffer_p + rlen, len - rlen);
        smdata->wi = (smdata->wi + len - rlen) % SHARED_BUFF_SIZE;
    }
    smdata->count += len;
    mutex_unlock(&smdata->lock);

    return len;
}

/* the structure for the driver */
static struct file_operations shm_fops = {
    .owner      = THIS_MODULE,
    .read       = shm_read,
    .write      = shm_write,
    .open       = shm_open,
    .release    = shm_release
};

struct shmem_data *alloc_shmem_data(void)
{
    struct shmem_data *sd = kmalloc(sizeof(struct shmem_data), GFP_KERNEL);
    if (!sd) return NULL;

    sd->wi = 0;
    sd->ri = 0;
    sd->count = 0;
    sd->minors = 1;
    mutex_init(&sd->lock);
    if (alloc_chrdev_region(&(sd->dev), 0, sd->minors, SHMEM_MODULE) < 0) {
        kfree(sd);
        return NULL;
    }

    printk(KERN_INFO "Driver: %s (Major: %d, Minor: %d)\n", SHMEM_MODULE, MAJOR(sd->dev), MINOR(sd->dev));

    /* init cdev struct */
    cdev_init(&sd->cdev, &shm_fops);
    sd->cdev.owner = THIS_MODULE;

    /* add cdev to the system */
    if (cdev_add (&sd->cdev,  sd->dev, sd->minors) < 0) {
        printk(KERN_WARNING "can't add cdev\n");
        unregister_chrdev_region(sd->dev, sd->minors);
        kfree(sd);
        return NULL;
    }

    return sd;
}

void free_shmem_data(struct shmem_data *sdata)
{
    if (!sdata) {
        cdev_del(&sdata->cdev);
        unregister_chrdev_region(sdata->dev, sdata->minors);
        kfree(sdata);
    }
}




int __init shmem_init(void)
{
    smdata = alloc_shmem_data();
    if (!smdata) {
        printk(KERN_INFO "Shmem initialization failed!!\n");
        return -1;
    }
    printk(KERN_INFO "Shmem initialized!!\n");
    return 0;
}

void __exit shmem_exit(void)
{
    free_shmem_data(smdata);
    printk(KERN_INFO "Shmem exited!!\n");
}

module_init(shmem_init);
module_exit(shmem_exit);

