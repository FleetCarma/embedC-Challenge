# embedC-Challenge

The following problem is a (heavily simplified) version of a feature implemented in our vehicle telematics devices.

A vehicle telematics device needs to read a set of signals over a period of time and compile a "trip event summary". For an electric vehicle, this summary may include:

* Trip Start Time [seconds since unix epoch]
* Trip Duration [seconds]
* Trip Distance Travelled [meters]
* Trip Total Energy Consumed [Watt-hours]
* Trip Starting Battery State-of-Charge (SOC) Value [%]
* Trip Ending Battery State-of-Charge (SOC) Value [%]

Someone has already written the code to retrieve signals from the vehicle and make each one available as a ```vehicle_signal_t```. This data structure contains the signal type, the time when the signal was received, and the signal value.

```javascript
typedef enum {
    VEHICLE_SIGNAL_TYPE_VEHICLE_SPEED,		// unsigned vehicle speed in kilometers per hour
    VEHICLE_SIGNAL_TYPE_HV_BATTERY_VOLTAGE,	// unsigned battery voltage in volts
    VEHICLE_SIGNAL_TYPE_HV_BATTERY_CURRENT,	// signed battery current in amps
    VEHICLE_SIGNAL_TYPE_HV_BATTERY_SOC		// unsigned battery state of charge in percent
}vehicle_signal_type_t;

typedef struct {
    vehicle_signal_type_t signal_type;
    uint64_t unix_timestamp_milliseconds;
    float value;
}vehicle_signal_t;
```

Your job is to write a small code library to receive each signal and maintain the following trip event summary:

```javascript
typedef struct {
    uint32_t start_time_since_unix_epoch_seconds;
    uint32_t duration_seconds;
    uint32_t distance_travelled_meters;
    uint32_t total_energy_consumed_wh;
    float starting_soc;
    float ending_soc;
}trip_event_summary_t;
```

Specifically, you must:

1) Create a code library containing at least one C file and one or more functions that receive a ```vehicle_signal_t``` and update the appropriate fields of ```trip_event_summary_t```.
	* the start time is the time that the first signal of any type is received
	* the duration is the difference in time between the first signal (of any type) received and the last signal (of any type) received
	* the distance travelled is the numerical integration of the VEHICLE_SIGNAL_TYPE_VEHICLE_SPEED signal
	* the total energy consumed is the numerical integration of the product of VEHICLE_SIGNAL_TYPE_HV_BATTERY_VOLTAGE and VEHICLE_SIGNAL_TYPE_HV_BATTERY_CURRENT
	* the starting SOC is the first VEHICLE_SIGNAL_TYPE_HV_BATTERY_SOC signal received
	* the ending SOC is the last VEHICLE_SIGNAL_TYPE_HV_BATTERY_SOC signal received
	
2) Write (at least one) unit test that feeds your library a set of ```vehicle_signal_t``` and checks that the resulting ```trip_event_summary_t``` is correct.
	* Use the included CSV file with data from one of our employee's vehicles to generate a set of vehicle_signal_t for your unit test(s).
	* A good unit test asserts a result that was derived from an independent source. How did you arrive at the "correct value" for each field in trip_event_summary_t?
	* Note that VEHICLE_SIGNAL_TYPE_HV_BATTERY_CURRENT is signed. An electric vehicle consumes energy from the battery for driving (positive current), but also charges the battery during deceleration to recover kinetic energy (negative current). The total energy is the sum of the net POSITIVE energy consumed.

Your code library should result in (at least one) C file and an accompanying header file. Make sure to use comments to describe what your code does (and, more importantly, why).

You should also include another C file that runs your unit test. A simple main.c is fine. If you have a favourite C unit test library, by all means use it.

You may create new types and variables as needed to support your calculations. Try to keep your code library file(s) from containing any state, so that they can be used in parallel by multiple processes.

Remember that this code has to execute in an embedded environment (a low-cost 32-bit micro-controller). Be cognizant of this when choosing the data types and mathematical operations for your calculations.
