POD7 is a small utility that listens to HIDRAW USB foot pedals and forwards the events as session DBus signals.

It can also list available HIDRAW USB devices. Using an udev rule to symlink the device is however recommended.

The forwarded signal can then be remotely caught and reacted upon.

The forwarded pedal events can be identified using the -v switch.

Use at your own risks. Work done as a hobbyist, targeting GNU/Linux OS.
