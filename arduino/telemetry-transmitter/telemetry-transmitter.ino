#include <SPI.h>
#include <SD.h>
#include <string.h>

/*
Global Variable Definitions
*/
File SENSOR_DATA; // SD card file obj

void setup() {
  /*
  
  */
  Serial.begin(9600);

  // Setup SD SS Low
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  
  if (!SD.begin()){ // SS=10, MOSI=11, MISO=12, SCK=13
    Serial.println("SD Card Initialisation failed!");
    while(true); //Loop forever its failed to connect
  }else{
    Serial.println("SD Card Connected!");
  }
  advanced_test_write_to_sd();
}

void loop() {
  /*
  Runs in a loop
  */

}

String append_to_string_csv(String one, String two, String three){
  one+=",";
  one+=two;
  one+=",";
  one+=three;
  return one;
}

bool write_to_sd(String datetime, uint8_t sensor_id, int sensor_data){
  /*
  Write SD Card the following data.

  Parameters:
  String datetime - Read from the RTC and dumped so that we know when data has been taken.
  uint8_t sensor_id - 8 bit unsigned integer used to represent the ID of the sensor. 
  int sensor_data - 32 bit signed integer representing the data retrieved from the sensor.
  */
}

bool advanced_test_write_to_sd(){
  /*
  Example more advanced sd_card write test
  */
  String datetime = "2024-01-18-00:00";
  String sensor_id = String(0x01); //Example Sensor ID
  String sensor_data = String(4096); //Example Sensor Data
  SENSOR_DATA = SD.open("20240118.csv", FILE_WRITE); //TODO: The name of the CSV file should be RTC date.
  String line = append_to_string_csv(datetime, sensor_id, sensor_data);
  Serial.println(line);
  // Open and write data
  if (SENSOR_DATA){
    SENSOR_DATA.println(line);
    SENSOR_DATA.close();
    Serial.println("Write Success");
    return true;
  }else{
    return false; //The write was not successful.
  }
}


