#include "elev.h"
#include "fsm.h"
#include "logic.h"
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
    printf("Kom forbi init");
    while (1) {
        elevator_control();
        printf("Kom forbi elevator_control");
        arrived_floor();
        printf("Kom forbi arrived_floor");
        if (elev_get_stop_signal()) {
            for (int floor = 0; floor < N_FLOORS; floor++){
                delete_order(floor);
            }
            elev_set_stop_lamp(1);
            elev_set_motor_direction(DIRN_STOP);
            break;
        }

    
    }

    return 0;
}

