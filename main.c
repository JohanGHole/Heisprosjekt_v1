#include "elev.h"
#include "fsm.h"
#include "logic.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");
    printf("Funker dette?\n");
    printf("Kom inn i init");
    if(elev_get_floor_sensor_signal() == -1) {
        elev_set_motor_direction(DIRN_UP);
    }
    while(1){
        if (elev_get_floor_sensor_signal() != -1){
            set_current_floor(elev_get_floor_sensor_signal());
            set_next_floor(get_current_floor());
            set_last_dir(DIRN_UP);
            elev_set_motor_direction(DIRN_STOP);
        }
    }
    printf("Kom forbi init\n");
    print_current();
    while (1) {
        check_order();
        set_priority();
        if (elev_get_stop_signal()) {
            for (int floor = 0; floor < N_FLOORS; floor++){
                delete_order(floor);
            }
            elev_set_stop_lamp(1);
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
        if(get_next_floor()== get_current_floor()){
            elev_set_motor_direction(DIRN_STOP);
            set_current_dir(DIRN_STOP);
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
        if (get_current_dir() != DIRN_STOP){
            set_current_dir(DIRN_STOP);
            elev_set_motor_direction(DIRN_STOP);
            elev_set_door_open_lamp(1);
            delete_order(get_current_floor());
            delay(3);
            elev_set_door_open_lamp(0);
        }
        

    
    }

    return 0;
}

