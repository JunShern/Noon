1. RESET the 16u2 by physically shorting the two headers closest to the USB port.

2. Clear the 16u2 using
sudo dfu-programmer atmega16u2 erase

3. Flash the new firmware using
sudo dfu-programmer atmega16u2 flash arduino_midi.hex 

4. Reset the newly updated board using
sudo dfu-programmer atmega16u2 reset

5. Plug cycle the Arduino, the new firmware should be working now!
