#define __LIBRARY__
#include <asm/segment.h>
#include <errno.h>
#include <unistd.h>

#define MAX_SIZE 23

int username_size = 0;
char username[MAX_SIZE + 1];

int sys_iam(const char *name)
{
    /* Get the name length */
    int i = 0;
    while(get_fs_byte(name+i) != '\0') i++;
    printk("sys_iam:\n name size is %d \n", i);
    if(i>MAX_SIZE)
        return -EINVAL;
    else
        username_size = i;
    /* Copy bytes from user space */
    int j;
    for(j = 0; j <= username_size; j++)
        username[j] = get_fs_byte(name + j);
    return username_size;
}

int sys_whoami(char *name, unsigned int size)
{
    if(username_size > size)
        return -EINVAL;
    /* Copy char val to the user space */
    int i;
    for(i = 0; i <= username_size; i++)
        put_fs_byte(username[i], name + i);
    return username_size;
}
