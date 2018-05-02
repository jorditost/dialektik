{\rtf1\ansi\ansicpg1252\cocoartf1561\cocoasubrtf400
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww14660\viewh14420\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\f0\b\fs40 \cf0 DIALEKTIK
\b0\fs24 \
\
\
2x Arduino UNO Rev3 (16MHz Processor) - Arduino MEGA?\
2x Ultrasonic Sensor HC-SR04\
\
_______\
\
\

\b Option 1\

\b0 LED Matrix
\b \

\b0 32x32 (167.6mm x 167.6mm): {\field{\*\fldinst{HYPERLINK "https://www.adafruit.com/product/2026"}}{\fldrslt https://www.adafruit.com/product/2026}}\
64x32 (385mm x 190mm): {\field{\*\fldinst{HYPERLINK "https://www.adafruit.com/product/2276"}}{\fldrslt https://www.adafruit.com/product/2276}}\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0
{\field{\*\fldinst{HYPERLINK "https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/"}}{\fldrslt \cf0 https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/}}\
\
Pros\
- {\field{\*\fldinst{HYPERLINK "https://github.com/adafruit/RGB-matrix-Panel"}}{\fldrslt Arduino Library}}\
\
Cons\
- Price (about $90)\
- Needs all 13 digital pins. We should find a workaround to set up the ultrasonic sensor {\field{\*\fldinst{HYPERLINK "https://www.arduino.cc/en/Tutorial/AnalogInputPins"}}{\fldrslt using analog pins}}. There is {\field{\*\fldinst{HYPERLINK "https://www.quora.com/Can-we-connect-the-ultrasonic-sensor-HC-SR04-to-an-analog-pin-in-Arduino-Uno-If-yes-how-do-we-get-the-distance-measurements"}}{\fldrslt this workaround}} in the net.\
- Size too small!\
 \
_______\
\
\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\b \cf0 Option 2\

\b0 LEDs + Breadboards\
\
Pros\
- We don\'92t need special features\
- Construction more flexible\
- Cheap\
\
Cons\
- Find a workaround to manage such an amount of LEDs in serie. \
- Tricky construction, not so robust\
\
_______\
\
\

\b Option 3\

\b0 RGB LED Strips\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0
{\field{\*\fldinst{HYPERLINK "https://www.digikey.de/short/q3bwc1"}}{\fldrslt \cf0 https://www.digikey.de/short/q3bwc1}}\
\
Pros\
- More flexible and robust than options 1 and 2\
\
Cons\
- How to build a circle using the strip?\
\
_______\
\
\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\b \cf0 Option 4\

\b0 Electroluminiscent Wire + EL Sequencer + EL inverter?\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0
{\field{\*\fldinst{HYPERLINK "https://learn.adafruit.com/el-wire"}}{\fldrslt \cf0 https://learn.adafruit.com/el-wire}}\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0
{\field{\*\fldinst{HYPERLINK "https://www.sparkfun.com/products/12781"}}{\fldrslt \cf0 https://www.sparkfun.com/products/12781}}\
{\field{\*\fldinst{HYPERLINK "https://www.sparkfun.com/products/10201"}}{\fldrslt https://www.sparkfun.com/products/10201}}\
\
Tutorial: {\field{\*\fldinst{HYPERLINK "https://learn.sparkfun.com/tutorials/heartbeat-straight-jacket"}}{\fldrslt https://learn.sparkfun.com/tutorials/heartbeat-straight-jacket}}\
Price: about $12 per wire (2x?) + $35 for the sequenzer + $10 for the EL inverter)\
\
Pros\
- Flexible construction\
- Cold. The wires generate no heat.\
\
Cons\
- Tricky usage with Arduino, since EL wire needs more voltage than the Arduino board can supply. Then, it needs a relay, power inverter, etc. ({\field{\*\fldinst{HYPERLINK "https://forum.arduino.cc/index.php?topic=50534.0"}}{\fldrslt Source 1}} | {\field{\*\fldinst{HYPERLINK "https://blog.adafruit.com/2010/12/07/tutorial-el-wire-electroluminescent-wire/"}}{\fldrslt Adafruit Tutorial}} | {\field{\*\fldinst{HYPERLINK "https://arduino.stackexchange.com/questions/4645/controlling-el-wire-or-panels-with-arduino"}}{\fldrslt How-to}} | {\field{\*\fldinst{HYPERLINK "http://www.instructables.com/id/Control-EL-Wire-with-an-Arduino/"}}{\fldrslt How-to build guide}})\
\
\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\b \cf0 Option 5\

\b0 LED Circle / Stripes\
\
4x 1/4 ring ($12 each)	 {\field{\*\fldinst{HYPERLINK "https://www.adafruit.com/product/2875"}}{\fldrslt https://www.adafruit.com/product/2875}} ($48)\
4x stripes ($8 each) {\field{\*\fldinst{HYPERLINK "https://www.adafruit.com/product/2869"}}{\fldrslt https://www.adafruit.com/product/2869}} ($32)\
\
or\
8x 4LEDs ($8 each) {\field{\*\fldinst{HYPERLINK "https://www.adafruit.com/product/2375"}}{\fldrslt https://www.adafruit.com/product/1312}} ($64)\
\
\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0
{\field{\*\fldinst{HYPERLINK "https://www.adafruit.com/category/168"}}{\fldrslt \cf0 https://www.adafruit.com/category/168}}\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0
{\field{\*\fldinst{HYPERLINK "https://shop.pimoroni.de/products/neopixel-1-4-60-ring-ws2812-5050-rgb-led-w-integrated-drivers?utm_medium=cpc&utm_source=googlepla&variant=6983955268&gclid=Cj0KCQjw_ODWBRCTARIsAE2_EvVe4HwFnqigtpyPgWRoeC1xidiMRL_cumx7xV4WfqjWc-2buYYa9AQaAn0MEALw_wcB"}}{\fldrslt \cf0 https://shop.pimoroni.de/products/neopixel-1-4-60-ring-ws2812-5050-rgb-led-w-integrated-drivers}}\
\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0
{\field{\*\fldinst{HYPERLINK "https://github.com/adafruit/Adafruit_NeoPixel"}}{\fldrslt \cf0 NeoPixel Lib}}\
\
\
\

\b LINEAR MOTOR\
\

\b0 Firgelli Linear Actuator
\b \
{\field{\*\fldinst{HYPERLINK "https://www.youtube.com/watch?v=uiux6fTB06w"}}{\fldrslt 
\b0 https://www.youtube.com/watch?v=uiux6fTB06w}}
\b0 \
{\field{\*\fldinst{HYPERLINK "https://www.youtube.com/watch?v=OkrL8AR7klo"}}{\fldrslt https://www.youtube.com/watch?v=OkrL8AR7klo}}\
\
{\field{\*\fldinst{HYPERLINK "https://www.youtube.com/watch?v=mp6cbTtiQzU"}}{\fldrslt https://www.youtube.com/watch?v=mp6cbTtiQzU}}\
{\field{\*\fldinst{HYPERLINK "https://www.actuonix.com/RC-linear-servos-s/1853.htm"}}{\fldrslt https://www.actuonix.com/RC-linear-servos-s/1853.htm}}}