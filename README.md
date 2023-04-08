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
| Relays 1 to 2   |  0x006C to 0x006D | 1 5 15 |

## 1.2 - Holding Registers Addresses (16 bits)
| Component | Address | Available Functions|
|---------------|------------------|--------------|
| Current temperature    |  0x0078 | 3 |
| Temperature threshold   |  0x0088 | 3 6 16 |
| Engine startup time   |  0x0098 | 3 6 16 |

# 2 - Implemented Functions

## 2.1 - 01 (0x01) Read Coils

## 2.2 - 03 (0x03) Read Holding Registers

## 2.3 - 05 (0x05) Write Single Coil

## 2.4 - 06 (0x06) Write Single Register

## 2.5 - 15 (0x0F) Write Multiple Coils

## 2.6 - 16 (0x10) Write Multiple Registers