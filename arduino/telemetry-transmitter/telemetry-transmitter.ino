#include <SPI.h>
#include <SD.h>
#include <string.h>
#include <DS3231.h>
#include <Wire.h>

/*
Global Variable Definitions
*/
File SENSOR_DATA; // SD card file obj
DS3231 RTC; // Real time clock object
bool century = false;
bool h12Flag;
bool pmFlag;

void setup() {
  /*
  One time run functions that must be configured before the sketch begins to loop
  */
  Serial.begin(9600);
  Wire.begin(); // Begin I2C comms with RTC (A5 SCL & A4 SDA)

  //configure_RTC(); //Only used if you are updating the time on the RTC.

  // Setup SD SS Low
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  
  if (!SD.begin()){ // SS=10, MOSI=11, MISO=12, SCK=13
    Serial.println("SD Card Initialisation failed!");
    while(true); //Loop forever its failed to connect
  }else{
    Serial.println("SD Card Connected!");
  }
}

void loop() {
  /*
  Runs in a loop
  */
}

void configure_RTC(){
  /*
  Configure RTC with values such as date, 12h mode etc.
  
  Parameters: N/A
  Returns: N/A
  */
  RTC.setClockMode(false); //Sets to 24H clock
  RTC.setSecond(0);
  RTC.setMinute(30);
  RTC.setHour(14);
  RTC.setDoW(1);
  RTC.setDate(21);
  RTC.setMonth(1);
  RTC.setYear(24);
}

String read_RTC(){
  /*
  Read the datetime from the RTC and format into useable datetime format
  that python should be able to interpret using strftime

  Parameters: N/A
  Returns datetime style string
  */
  String date = read_RTC_date(true);
  String hour = String(RTC.getHour(h12Flag, pmFlag));
  String minute = String(RTC.getMinute());
  String second = String(RTC.getSecond());
  
  String RTC_reading = date + " " + hour + ":" + minute + ":" + second;
  return RTC_reading;
}

String read_RTC_date(bool slash){
  /*
  Function to only read the date from the RTC

  Parameters: Slash (bool) - Used to indicate if you want the slash between ddmmyyyy or not.
  Returns: date - datetime in the form of dd-mm-yyyy or ddmmyyyy
  */
  String day = String(RTC.getDate());
  String month = String(RTC.getMonth(century));
  String year = String(RTC.getYear());

  //Convert year into correct format (For years up to 2100)
  year = "20" + year;
  String date;
  if (slash){
    date = day + "-" + month + "-" + year;
  }else{
    date = day+month+year;
  }
  return date;
}

void test_RTC(){
	/*
  Used for RTC debug
  */
	
	// Start with the year
	Serial.print("2");
	if (century) {			// Won't need this for 89 years.
		Serial.print("1");
	} else {
		Serial.print("0");
	}
	Serial.print(RTC.getYear(), DEC);
	Serial.print(' ');
	
	// then the month
	Serial.print(RTC.getMonth(century), DEC);
	Serial.print(" ");
  
	// then the date
	Serial.print(RTC.getDate(), DEC);
	Serial.print(" ");
  
	// and the day of the week
	Serial.print(RTC.getDoW(), DEC);
	Serial.print(" ");
  
	// Finally the hour, minute, and second
	Serial.print(RTC.getHour(h12Flag, pmFlag), DEC);
	Serial.print(" ");
	Serial.print(RTC.getMinute(), DEC);
	Serial.print(" ");
	Serial.print(RTC.getSecond(), DEC);
 
	// Add AM/PM indicator
	if (h12Flag) {
		if (pmFlag) {
			Serial.print(" PM ");
		} else {
			Serial.print(" AM ");
		}
	} else {
		Serial.print(" 24h ");
	}
}

String append_to_string_csv(String one, String two, String three){
  /*
  Appends three strings together in CSV format
  Parameters: 
  one, two, three (Strings to append)

  Returns: 
  one (Singular string)
  */
  one+=",";
  one+=two;
  one+=",";
  one+=three;
  return one;
}

bool write_to_sd(uint8_t sensor_id, int sensor_data){
  /*
  Write SD Card the following data.

  Parameters:
  uint8_t sensor_id - 8 bit unsigned integer used to represent the ID of the sensor. 
  int sensor_data - 32 bit signed integer representing the data retrieved from the sensor.

  Returns:
  True - If write was successful
  False - If write was not successful
  */
  String id = String(sensor_id); //Cast uint_8t to string for csv file
  String data = String(sensor_data); //Cast int to string for csv file
  String datetime = read_RTC();
  String csv_line = append_to_string_csv(datetime, id, data); // Add all of these strings into a singular csv file
  String filename = read_RTC_date(false) + ".csv";

  SENSOR_DATA = SD.open(filename, FILE_WRITE); //TODO: The name of the CSV file should be RTC date.

  if (SENSOR_DATA){
    SENSOR_DATA.println(csv_line); //Write line to CSV file
    SENSOR_DATA.close();
    return true; // If this has completed then success
  }else{
    return false; // If sensor data is not true file never opened & thus failed.
  }
}

int measure_wheel_speed(){
  /*
  Measure wheel speed from hall effect sensors.

  Parameters:
  N/A

  Returns:
  Wheel speed in meters/s
  */
}

bool advanced_test_write_to_sd(){
  /*
  Example more advanced sd_card write test with fake sensor data and RTC time implemented
  */
  String datetime = read_RTC();
  String sensor_id = String(0x01); //Example Sensor ID
  String sensor_data = String(4096); //Example Sensor Data

  String filename = read_RTC_date(false) + ".csv";
  Serial.println(filename);

  SENSOR_DATA = SD.open(filename, FILE_WRITE); //TODO: The name of the CSV file should be RTC date.
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


