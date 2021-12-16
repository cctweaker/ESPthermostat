There are 3 options to use Tasmota as the main firmware for the ESPThermostat PCB.

# no PCA
This usage option is ommiting the PCA9536D IO expander. Up to two relays can be controlled by GPIO 0 and GPIO 1 (active low). GPIO2 and GPIO0 can be strapped to any of the MOSFET gates instead of mounting the expander. All pins are close to each other on the U2 SO8 footprint of the expander.
Use the following configuration template in Tasmota:
<code>{"NAME":"ESPthermostat","GPIO":[256,0,256,1312,0,0,0,0,0,0,0,0,0,0],"FLAG":0,"BASE":18}</code>

# PCA
This usage option is using the PCA9536D IO expander. At the moment Tasmota has no driver for this I2C device. When it will be available, simply use the following configuration to scan and detect the expander.
<code>{"NAME":"ESPthermostat","GPIO":[640,0,608,1312,0,0,0,0,0,0,0,0,0,0],"FLAG":0,"BASE":18}</code>
