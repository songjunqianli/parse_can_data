#include "can_data.hpp"

int main(int argc, char *argv[]) {
    string can_name;
    string dbc_path;
    
    if (argc == 3) {
        can_name = argv[1];
        dbc_path = argv[2];
    }

    CanData* can_data = new CanData(can_name, dbc_path);
    can_data->loadDBC();
    can_data->initCan();
    
    while(int num_bytes = read(can_data->socket_canfd_, &can_data->canfd_data_, sizeof(can_data->canfd_data_)) > 0) {
    // LOG(INFO) << "--------Receive " << num_bytes << " Bytes from can frame--------";

    // for(int i=0; i < static_cast<unsigned int>(can_data->canfd_data_.len); i++) {
    //     LOG(INFO) << "            DATA" << "[" << i << "] : " << std::hex << (int)can_data->canfd_data_.data[i];
    // }

    if (can_data->canfd_data_.can_id == BOEachWheelSpeed) {
        LOG(INFO) << "=========BO ID : " << can_data->canfd_data_.can_id << ", " 
                                         << "BO DLC : " << static_cast<unsigned int>(can_data->canfd_data_.len);
        auto BOInfo_wheel = can_data->BO_messages_[BOEachWheelSpeed];
        auto SGInfos_wheels = BOInfo_wheel->getSignals();

        signal_ST sig_fl_wheel, sig_fr_wheel, sig_rl_wheel, sig_rr_wheel;
        can_data->getSignalDBCInfo(SGInfos_wheels, SIG_FL_WHEEL_SPEED, sig_fl_wheel);
        can_data->getSignalDBCInfo(SGInfos_wheels, SIG_FR_WHEEL_SPEED, sig_fr_wheel);
        can_data->getSignalDBCInfo(SGInfos_wheels, SIG_RL_WHEEL_SPEED, sig_rl_wheel);
        can_data->getSignalDBCInfo(SGInfos_wheels, SIG_RR_WHEEL_SPEED, sig_rr_wheel);


        LOG(INFO) << "          wheel speed: "  << can_data->calSignalValue(can_data->canfd_data_, sig_fl_wheel) <<", "
                                                    << can_data->calSignalValue(can_data->canfd_data_, sig_fr_wheel) <<", "
                                                    << can_data->calSignalValue(can_data->canfd_data_, sig_rl_wheel) <<", "
                                                    << can_data->calSignalValue(can_data->canfd_data_, sig_rr_wheel);


    }else if (can_data->canfd_data_.can_id == BOCurrentVehicleSpeed) {
        LOG(INFO) << "=========BO ID : " << can_data->canfd_data_.can_id << ", " 
                                         << "BO DLC : " << static_cast<unsigned int>(can_data->canfd_data_.len);
        auto BOInfo_vehicle_speed = can_data->BO_messages_[BOCurrentVehicleSpeed];
        auto SGInfos_vehicle_speed = BOInfo_vehicle_speed->getSignals();
        signal_ST sig_vehicle_speed;
        
        can_data->getSignalDBCInfo(SGInfos_vehicle_speed, SIG_VEHICLE_SPEED, sig_vehicle_speed);
        LOG(INFO) << "          vehicle speed: "  << can_data->calSignalValue(can_data->canfd_data_, sig_vehicle_speed);

    } else if (can_data->canfd_data_.can_id == BOYawRate) {
        LOG(INFO) << "=========BO ID : " << can_data->canfd_data_.can_id << ", " 
                                         << "BO DLC : " << static_cast<unsigned int>(can_data->canfd_data_.len);

        auto BOInfo_yaw_rate = can_data->BO_messages_[BOYawRate];
        auto SGInfos_yaw_rate = BOInfo_yaw_rate->getSignals();
        signal_ST sig_yaw_rate;

        can_data->getSignalDBCInfo(SGInfos_yaw_rate, SIG_YAW_RATE, sig_yaw_rate);
        LOG(INFO) << "          yaw rate: "  << can_data->calSignalValue(can_data->canfd_data_, sig_yaw_rate);
        
    }






}
}