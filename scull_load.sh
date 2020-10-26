#https://static.lwn.net/images/pdf/LDD3/ch03.pdf

#!/bin/sh
module="src/holamundoMK"
device="holamundoMK"
mode="664"
# invoke insmod with all arguments we got
# and use a pathname, as newer modutils don't look in . by default
insmod $module.ko
echo "$module was inserted"

major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices)
if [ -n "$major" ]; then
    echo "major was found: $major"
    # remove stale nodes
    rm -f /dev/${device}[0-3]

    echo $major
    mknod /dev/${device}0 c $major 0
    mknod /dev/${device}1 c $major 1
    mknod /dev/${device}2 c $major 2
    mknod /dev/${device}3 c $major 3

    # give appropriate group/permissions, and change the group.
    # Not all distributions have staff, some have "wheel" instead.
    group="staff"
    grep -q '^staff:' /etc/group || group="wheel"
    chgrp $group /dev/${device}[0-3]
    chmod $mode /dev/${device}[0-3] 
else
    echo "major was not found"
    rmmod $module.ko
    echo "$module was removed"
fi
