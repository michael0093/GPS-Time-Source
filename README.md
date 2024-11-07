# GPS-Time-Source
GPS Time Source based on Quectel LC29T EVB

The LC29T EVB provides a 1pps and 10MHz output (but no lock indication). This project adds a supervisor CPU (Ti MSPM0) which monitors the LC29 output data stream to idenitfy when it is locked (and also displays the UTC time). There is another PCB which is a 10MHz clock distribution board.
The monitoring PCB is designed to be connected as follows (refer to photos for EVB connections):
- 3.3V/GND from the LC29 EVB
- UART RX (into CPU) from the LC29 EVB
- 0.91" OLED display on the CPU board's I2C pins
The CPU board is designed to also double as a super compact reusable breakout board for Ti MSPM0L110x series ARM M0 CPUs.
