#include "logic.h"

//Private variables

int order_matrix[3][4] ={
//	 1 2 3 4   // Floor    
	[0,0,0,0], // Up 
	[0,0,0,0], // Down
	[0,0,0,0]  // Panel
	
};


int current_floor = 0;

int next_floor = 0;

int current_dir = 0;

int last_dir = 0;

void set_current_floor(int floor){
	current_floor = floor;
}

int get_current_floor(){
	return current_floor;
}

void set_next_floor(int floor){
	next_floor = floor;
}

int get_next_floor(){
	return next_floor;
}

void set_current_dir(int dir) {
	current_dir = dir;
}

int get_current_dir(){
	return current_dir;
}

int get_last_dir(){
	return last_dir;
}

int set_order(){
	for (int floor = 0; floor < N_FLOORS-1; floor++){
	    for (int button = 0; button <= BUTTON_COMMAND; button++) {
	        if ((floor == 0 && button == 1) || (floor == 3 && button == 0)) {  //ignoring the undefined button values
	            break;
	        }
	        else if (order_matrix[button][floor] == 0 ){
	        	if (elev_get_button_signal(button,floor) == 1){
	        	order_matrix[button][floor] == 1;
	        	elev_set_button_lamp(button, floor, 1);
	        	return 1;
	        	}
	        }
	    }
	}
    return 0;
}

int check_order_above(){
	if (get_current_floor() == 2 && order_matrix[1][3] == 1){
			set_next_floor(3);
			return 1;
	}
	for (int floor = get_current_floor()+1; floor < N_FLOORS, floor++) {
		if(matrix[0][floor] == 1 || order_matrix[2][floor] == 1)  {
			next_floor = floor;
			return 1;
		}
	}
	return 0;	
}

int check_order_below(){
	if (get_current_floor() == 1 && order_matrix[0][0] == 1){
			set_next_floor(0);
			return 1;
	} 
	for (int floor = get_current_floor()-1; floor >= 0, floor--) {
		if(check_order(floor) == 1) {
			set_next_floor(floor);
			return 1;
		}
	}
	return 0;	
}

void delete_order(){
	for (int order_type = 0; order_type <= BUTTON_COMMAND; order_type++){
		order_matrix[order_type][get_current_floor()] = 0;
	}
}


void delay(int number_of_seconds){
    clock_t start_time = clock();
    while ( (clock() - start_time)/CLOCKS_PER_SEC < number_of_seconds){
        
        if (elev_get_stop_signal()){
            break;
        }
    }
}
//setter next_floor etter hva som er mest gunstig
void set_priority(){
	if (get_current_dir() = DIRN_UP){
		check_order_above();
		return;
	}
	else if (get_current_dir() = DIRN_DOWN){
		check_order_below();
		return;
	}
	else if (get_last_dir() == DIRN_UP && get_current_floor() != 3){
		check_order_above();
	}
	else if (get_last_dir() == DIRN_DOWN && get_current_floor() != 0){
		check_order_below();
	}
	else if (get_current_floor() == 0 && get_current_dir() == DIRN_STOP){
		check_order_above();
	}
	else if (get_current_floor() == 3 && get_current_dir() == DIRN_STOP){
		check_order_below();
	}
}
