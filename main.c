#include "elev.h"
#include <stdio.h>

int dir = DIRN_UP;

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);

    while (1) {
	set_elevator_lamps();
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_STOP);
            elev_set_floor_indicator(3);
	    dir = DIRN_DOWN;
	    waitFor(3);
	    elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 2) {
            elev_set_floor_indicator(2);
        } else if (elev_get_floor_sensor_signal() == 1) {
            elev_set_floor_indicator(1);
	} else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
            elev_set_floor_indicator(0);
	    dir = DIRN_UP;
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
	    elev_set_stop_lamp(1);
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    return 0;
}

