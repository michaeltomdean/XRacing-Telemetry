# XRacing-Telemetry
X-Racings Telemetry project including all code for the transmitter and receivers, documentation, example datasets, schematics and supporting python scripts. 
## Development
Current stage of development
| Task  | Progress |
| ------------- | ------------- |
| Integrate SD Card into transmitter circuit and test data can be written  | Complete  |
| Level Shift RTC from 3.3V to 5V to work with Arduino logic  | WIP  |
| Integrate ZF GS100502 hall effect wheel speed sensors into telemetry system  | WIP  |
| Integrate RTC into transmitter circuit and add to SD card writes  | TODO  |
| Draw up schematic of transmitter system  | WIP  |
| Find and test 2.4GHz transceivers  | TODO  |
| Complete transmitter PCB  | TODO  |
## Project
### Arduino Scripts
Includes a set of arduino scripts to run on a transmitter and receiver arduino that will be used to log data from sensors on the card and dump to an SD card. Data from each day will be stored in a dedicated CSV file, with data dumped into the file time-stampped via the RTC. 
### Python Scripts
Used to decode sensor data stored in the CSV files.
### Schematics
Files designed to show how to wire up components. A dedicated PCB will be designed for the transmitter circuit so it can be securely mounted into the car.
### Datasets
Useful location to store specific datasets that are of interest. For example, a particular track day that resulted in interesting data that should be shared with those working on the model.
### Documents
Any useful documentation on components or any documentation created to explain how files and code works.
