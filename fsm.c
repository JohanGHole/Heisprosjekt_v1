
// her kommer koden knytt til tilstandsmaskinen
#include "fsm.h"
#include "logic.h"
#include "elev.h"
#include "stdio.h"

void init_elevator() {
    printf("Kom inn i init");
    while(elev_get_floor_sensor_signal() == -1) {
        elev_set_motor_direction(DIRN_UP);

    }
    elev_set_motor_direction(DIRN_STOP);
    set_current_floor(elev_get_floor_sensor_signal() );
    set_current_dir(DIRN_STOP);
    set_last_dir(DIRN_UP);
}


void elevator_control(){
    check_order();
    set_priority();
    if(get_next_floor()== get_current_floor()){
        elev_set_motor_direction(DIRN_STOP);
        set_current_dir(DIRN_STOP);
        return;
    }
    else if (get_next_floor() > get_current_floor()){
        set_current_dir(DIRN_UP);
        set_last_dir(DIRN_UP);
    }
    else if(get_next_floor() < get_current_floor()){
        set_current_dir(DIRN_DOWN);
        set_last_dir(DIRN_DOWN);     
    }
    while(get_next_floor() != get_current_floor()) {
        elev_set_motor_direction(get_current_dir());
        check_order();
        set_priority();
    }

}

void arrived_floor(){
    if (get_current_dir() != DIRN_STOP){
        set_current_dir(DIRN_STOP);
        elev_set_motor_direction(DIRN_STOP);
        elev_set_door_open_lamp(1);
        delete_order(get_current_floor());
        delay(3);
        elev_set_door_open_lamp(0);
    }
}

