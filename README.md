if on wsl:
\
`cp Makefile-wsl Makefile`
\
then clone the WSL kernel, build it and set $WSLKERN to the kernel folder


if on linux:
\
`cp Makefile-linux Makefile`


```
make

sudo insmod kworm.ko

sudo mknod /dev/worm c "$(cat /proc/devices | grep worm | cut -d' ' -f1)" 0

cat /dev/worm
```

