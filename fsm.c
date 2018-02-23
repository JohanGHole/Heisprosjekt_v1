// her kommer koden knytt til tilstandsmaskinen
#include "fsm.h"
#include "logic.h"


void init_elevator(void) {
    while(elev_get_floor_sensor_signal() == -1) {
        elev_set_motor_direction(DIRN_UP);  
    }
    elev_set_motor_direction(DIRN_STOP);
    set_current_floor(elev_get_floor_sensor_signal() );
}
