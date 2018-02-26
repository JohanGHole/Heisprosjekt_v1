
// her kommer koden knytt til tilstandsmaskinen
#include "fsm.h"
#include "logic.h"
#include "elev.h"
#include <stdio.h>

#include "channels.h"
#include "io.h"


void elevator_control(){
    if(get_next_floor()== get_current_floor()){
        elev_set_motor_direction(DIRN_STOP);
        set_current_dir(DIRN_STOP);
        return;
    }

    else if (get_next_floor() > get_current_floor()){
        set_current_dir(DIRN_UP);
        elev_set_motor_direction(DIRN_UP);    }

    else if(get_next_floor() < get_current_floor()){
        set_current_dir(DIRN_DOWN);
        elev_set_motor_direction(DIRN_DOWN);    
    }

    while(get_next_floor() != get_current_floor()) {
        if (elev_get_stop_signal() == 1){
            return;
        }
        
        if (elev_get_floor_sensor_signal() != -1){
            set_current_floor(elev_get_floor_sensor_signal());
            elev_set_floor_indicator(elev_get_floor_sensor_signal());
        }
        check_order();
        set_priority();
    }

    set_last_dir(get_current_dir());
    set_current_dir(DIRN_STOP);
    set_current_floor(elev_get_floor_sensor_signal());
    elev_set_motor_direction(DIRN_STOP);


}

void arrived_floor(){
    elev_set_door_open_lamp(1);
    delete_order(get_current_floor());
    delay(3);
    elev_set_door_open_lamp(0);
    while (sum_of_orders() == 0){
        if (elev_get_stop_signal()){
            return;
        }
        check_order();
    }
    set_priority();
}


