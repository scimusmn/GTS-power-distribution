
#define min_in_millis 41  //how many millis pass realtime for each min in the simulation
#define num_pixels_source 20  //number of neopixels for power source types.

// Sources
#define s1_down_pin A0  // button pin down
#define s1_up_pin A1    // button pin up
#define s1_neo_pin A2   // output pin for neopixel bargraph
#define s1_react_time 100 //millis to increase 5%
#define s1_max_pwr 1    // capacity of power source. TODO define units

#define s2_down_pin 2
#define s2_up_pin 3
#define s2_neo_pin 4
#define s2_react_time 300
#define s2_max_pwr 1

#define s3_down_pin 5
#define s3_up_pin 6
#define s3_neo_pin 7
#define s3_react_time 200
#define s3_max_pwr 1

#define s4_down_pin 8
#define s4_up_pin 9
#define s4_neo_pin 10
#define s4_react_time 1300
#define s4_max_pwr 1

#define s5_down_pin 11
#define s5_up_pin 12
#define s5_neo_pin 13
#define s5_react_time 2000
#define s5_max_pwr 1

#define prod_neo_pin A5     //output pin for neopixels production bar graph
#define demand_neo_pin A4   //output pin for neopixels demand bar graph
