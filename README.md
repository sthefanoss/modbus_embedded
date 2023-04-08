# Modbus RTU Implementation

Project for PIC pic16f877a 
With MPLAB 5.45, PICSimLab 0.8.12 


You may use the bellow commnad to commit on this repository.
```shell
git config core.autocrlf false
```

# 1 - Componenets
## 1.1 - Coils and Relays Addresses (1 bit)
| Component | Address | Available Functions|
|---------------|------------------|--------------|
| Coils 1 to 8    |  0x0064 to 0x006B | 1 5 15 |
| Relays 1 (Star) to 2 (Delta)  |  0x006C to 0x006D | 1 5 15 |

## 1.2 - Holding Registers Addresses (16 bits)
| Component | Address | Available Functions|
|---------------|------------------|--------------|
| Current temperature    |  0x0078 | 3 |
| Temperature threshold   |  0x0088 | 3 6 16 |
| Engine startup time   |  0x0098 | 3 6 16 |

# 2 - Implemented Functions
 TODO
## 2.1 - 01 (0x01) Read Coils
 TODO
## 2.2 - 03 (0x03) Read Holding Registers
 TODO
## 2.3 - 05 (0x05) Write Single Coil
 TODO
## 2.4 - 06 (0x06) Write Single Register
 TODO
## 2.5 - 15 (0x0F) Write Multiple Coils
 TODO
## 2.6 - 16 (0x10) Write Multiple Registers
 TODO

# 3 - Features
## 3.1 - Temperature Control
This board reads its temperature and compare it with the desired value set by user on Temperature threshold holding register (0x0088).  There are a heater, a fan and a temperature sensor.

If the temperature is below desired, the fan will turn of and the heater will turn on. The opposite will happen when the demperature is above desired.


## 3.2 - Star Delta Starter Control
There are two relays at 0x006C (Star) and 0x006D (Delta). If both are turn of and you turn on 0x006C, the engine will start with Star configuration and will change to Delta after time specified at Engine startup time holding register (0x0098).

You cannot set both registers at same time. This board will turn of Star relay if you try so.

If Star relay is already on and you turn on Delta relay, it will disable the first for security as well.

You must turn off Delta bofore turn on Star again. 

