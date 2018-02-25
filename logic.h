

extern int order_matrix[3][4];

void set_current_floor(int floor);

int get_current_floor();

void set_next_floor(int floor);

int get_next_floor();

void set_current_dir(int dir);

int get_current_dir();

void set_last_dir(int dir);

int get_last_dir();

int check_order();

int check_order_above();

int check_order_below();

void delete_order(int floor);

void delay(int number_of_seconds);

void set_priority();

void print_current();

