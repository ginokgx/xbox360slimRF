# xbox360slimRF
This is a project to use the wireless receiver of an Xbox 360 Slim on a PC, while maintaining the synchronization function for new controllers

Unlike other projects that use the receiver from older models (Xbox 360 Fat), this one works with the Slim model. I know there is information on how to connect the module via USB, but I couldn’t find any that implemented the synchronization function for this specific model.

I used the Wemos D1 Mini microcontroller due to its low cost (about 1 USD), and the fact that it works at 3.3V (like the receiver) simplifies things. The code is based on the same one used for FAT models. I only had to change a startup command (so that the LEDs work correctly when synchronizing) and add 1 more bit to the synchronization command, in order to quickly set the data pin to HIGH after sending the command, otherwise it didn't work correctly. 

Although the Wemos can be programmed through its USB interface, an external USB connection is needed to send data from the receiver module.
Just like with old modules, once connected to de PC you will need to install the wireless receiver drivers to work.


The connection scheme would be as follows:
![alt text](https://github.com/ginokgx/xbox360slimRF/blob/main/Scheme.png)


And here’s an example of it working:

![alt text](https://github.com/ginokgx/xbox360slimRF/blob/main/Sync.gif)
