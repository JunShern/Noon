from evdev import InputDevice, list_devices, categorize, ecodes

## Input Devices
devices = list()
for fn in list_devices():
    dev = InputDevice(fn)
    devices.append(dev)

gamepad = devices[0]
for event in gamepad.read_loop():
    print(event)



