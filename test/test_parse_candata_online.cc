#include "can_data.hpp"

int main(int argc, char *argv[]) {
    string can_name;
    string dbc_path;
    
    if (argc == 3) {
        can_name = argv[1];
        dbc_path = argv[2];
    }

    vector<double> wheel_speed;

    CanData* chassis_data = new CanData(can_name, dbc_path);
    chassis_data->loadDBC();
    
    chassis_data->initCan();
    chassis_data->parseChassisSignal();

}