```
make
sudo insmod kworm.ko
# get major number from kernel log
sudo mknod /dev/worm c <major number> 0
cat /dev/worm
```
