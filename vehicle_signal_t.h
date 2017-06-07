#include <stdint.h>

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
