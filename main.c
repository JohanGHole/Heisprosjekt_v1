#include "elev.h"
#include <stdio.h>
#include <unistd.h>

int dir = DIRN_UP;
int infloor = -1; 

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    init_elevator();
    while (1) {
        // Change direction when we reach top/bottom floor, stop for 3 seconds in each floor
        if ( (elev_get_floor_sensor_signal() == N_FLOORS - 1)  && ((check_last_floor() == 2) || (check_last_floor() == -1)) ) {
            elev_set_floor_indicator(3);
            if (check_order(3) == 1){
            	elev_set_motor_direction(DIRN_STOP);
            	delay(3);
            }
            elev_set_motor_direction(set_direction());


        } else if ( (elev_get_floor_sensor_signal() == 2) && ((check_last_floor() == 3 || check_last_floor() == 1)) ) {
            elev_set_floor_indicator(2);
            if (check_order(2) == 1){
            	elev_set_motor_direction(DIRN_STOP);
            	delay(3);
            }
            elev_set_motor_direction(set_direction());
        } else if ( (elev_get_floor_sensor_signal() == 1) && ((check_last_floor() == 2 || check_last_floor() == 0)) ) {
            elev_set_floor_indicator(1);
           if (check_order(1) == 1){
            	elev_set_motor_direction(DIRN_STOP);
            	delay(3);
            }
            set_direction();		
		} else if (elev_get_floor_sensor_signal() == 0 && check_last_floor() == 1) {
            elev_set_floor_indicator(0);
            if (check_order(0) == 1){
            	elev_set_motor_direction(DIRN_STOP);
            	delay(3);
	    	}
	    	elev_set_motor_direction(set_direction());		
        }

        if (elev_get_stop_signal()) {
            elev_set_stop_lamp(1);
            elev_set_motor_direction(DIRN_STOP);
            break;
        }

    
    }

    return 0;
}

