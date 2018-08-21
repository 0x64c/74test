# 74test
Standalone 74 Series IC Testbench for AVR 

## Progress:
### Implemented:
#### DIP14:
* 7406
* 7408

### Todo:
#### DIP14:
* 7474
#### DIP16:
* 74139
* 74193
* 74257
* 74258
* 74629
##### DIP20:
* 74373

## Pin configuration (Mega2560)

| Pin Name | Pin No. | Function       | I/O |
|----------|---------|----------------|-----|
| PB7      | D13     | LED            | O   |
| PB6      | D12     | Button         | I   |
| PF0-PF7  | A0-A7   | DIP Selector   | I   |
| PA0-PA7  | D22-D29 | L Test Byte    | I/O |
| PC0-PC7  | D37-D30 | H Test Byte    | I/O |
| PD0-PD3  | D21-D18 | G Test Nybble  | I/O |

### DIP20
```
L0  1 | v |20 VCC
L1  2 |   |19 L6
L2  3 |   |18 L7
L3  4 |   |17 H0
L4  5 |   |16 H1
L5  6 |   |15 H2
H5  7 |   |14 H3
H6  8 |   |13 H4
H7  9 |   |12 G0
GND 10|   |11 G1
```
### DIP16
```
L0  1| v |16  VCC
L1  2|   |15  L6
L2  3|   |14  L7
L3  4|   |13  H0
L4  5|   |12  H1
L5  6|   |11  H2
H5  7|   |10  H3
GND 8|   |9   H4
```
### DIP14
```
L0  1| v |14  VCC
L1  2|   |13  L6
L2  3|   |12  L7
L3  4|   |11  H0
L4  5|   |10  H1
L5  6|   |9   H2
GND 7|   |8   H3
```
