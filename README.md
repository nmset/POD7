##POD7

POD7 is a small utility that listens to HIDRAW USB foot pedals and forwards the events as session DBus signals.

It can also list available HIDRAW USB devices. Using an udev rule to symlink the device is however recommended.

The forwarded signal can then be remotely caught and reacted upon.

The forwarded pedal events can be identified using the -v switch.

Use at your own risks. Work done as a hobbyist, targeting GNU/Linux OS.

####Device access setup

Udev's facilities are used here. A group with read/write access to the 
device must be created, with users added to that group.

$ groupadd transcript

$ usermod -a -G transcript user

Create /etc/udev/rules.d/99-mypedal.rules with (one single line) :

- *KERNEL=="hidraw[0-9]*", ATTRS{idVendor}=="abcd", ATTRS{idProduct}=="efgh",  
MODE="0660", GROUP="transcript"*

Get 'abcd' and 'efgh' with 'lsusb' command or 'dmesg |tail' commands 
after plugging the foot pedal.

Remove the pedal device and plug it again. On next login, users in group 
'transcript' should have read access to the device.