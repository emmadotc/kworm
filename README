if on wsl:
	`cp Makefile-wsl Makefile`
then clone the WSL kernel, build it and set $WSLKERN to the kernel folder

if on linux:
	`cp Makefile-linux Makefile`

```
make
sudo insmod kworm.ko
# get major number from kernel log
sudo mknod /dev/worm c <major number> 0
cat /dev/worm
```

