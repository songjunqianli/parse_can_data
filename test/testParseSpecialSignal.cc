#include "can_data.hpp"
#define TEST_RADAR 0

int main(int argc, char *argv[]) {
    string can_name;
    string dbc_path;
    
    if (argc == 3) {
        can_name = argv[1];
        dbc_path = argv[2];
    }


  #if TEST_RADAR
    canfd_frame data_bo32;
    data_bo32.len = char(8);
    data_bo32.can_id = 0x20;
    data_bo32.data[0] = 0x80;
    data_bo32.data[1] = 0x0E;
    data_bo32.data[2] = 0x51;
    data_bo32.data[3] = 0x1E;
    data_bo32.data[4] = 0x04;
    data_bo32.data[5] = 0x80;
    data_bo32.data[6] = 0x0D;
    data_bo32.data[7] = 0x69;

    canfd_frame data_bo80;
    data_bo80.len = char(8);
    data_bo80.can_id = 0x50;
    data_bo80.data[0] = 0x02;
    data_bo80.data[1] = 0x84;
    data_bo80.data[2] = 0x88;
    data_bo80.data[3] = 0x16;
    data_bo80.data[4] = 0x7E;
    data_bo80.data[5] = 0x1E;
    data_bo80.data[6] = 0xED;
    data_bo80.data[7] = 0x50;


    CanData* radar_data = new CanData(can_name, dbc_path);
    radar_data->loadDBC();

    double result_measFlag = radar_data->test_parseSpecifiedSignal(data_bo32.can_id, "FRS_P2_00_Obj_MeasFlag", data_bo32);
    double result_type = radar_data->test_parseSpecifiedSignal(data_bo32.can_id, "FRS_P2_00_Obj_Type", data_bo32);
    double result_XPos = radar_data->test_parseSpecifiedSignal(data_bo32.can_id, "FRS_P2_00_Obj_XPos", data_bo32);
    double result_XVelRel = radar_data->test_parseSpecifiedSignal(data_bo32.can_id, "FRS_P2_00_Obj_XVelRel", data_bo32);
    double result_YPos = radar_data->test_parseSpecifiedSignal(data_bo32.can_id, "FRS_P2_00_Obj_YPos", data_bo32);
    double result_YVelRel = radar_data->test_parseSpecifiedSignal(data_bo32.can_id, "FRS_P2_00_Obj_YVelRel", data_bo32);   
    LOG(INFO) << "obj_measFlag: " << result_measFlag;
    LOG(INFO) << "obj_type: " << result_type;
    LOG(INFO) << "obj_xpos: " << result_XPos<< ", " << "obj_xvel: " << result_XVelRel;
    LOG(INFO) << "obj_ypos: " << result_YPos<< ", " << "obj_yvel: " << result_YVelRel;

    double result_MotionPattern = radar_data->test_parseSpecifiedSignal(data_bo80.can_id, "FRS_P1_00_Obj_MotionPattern", data_bo80);
    LOG(INFO) << "MotionPattern: " << result_MotionPattern;
    double result_ObstacleProb = radar_data->test_parseSpecifiedSignal(data_bo80.can_id, "FRS_P1_00_Obj_ObstacleProb", data_bo80);
    LOG(INFO) << "ObstacleProb: " << result_ObstacleProb;
    double result_Obj_ID = radar_data->test_parseSpecifiedSignal(data_bo80.can_id, "FRS_P1_00_Obj_ID", data_bo80);
    LOG(INFO) << "Obj_ID: " << result_Obj_ID;
    double result_ExstProb = radar_data->test_parseSpecifiedSignal(data_bo80.can_id, "FRS_P1_00_Obj_ExstProb", data_bo80);
    LOG(INFO) << "ExstProb: " << result_ExstProb;

    double YPos_Stdev = radar_data->test_parseSpecifiedSignal(data_bo80.can_id, "FRS_P1_00_Obj_YPos_Stdev", data_bo80);
    LOG(INFO) << "YPos_Stdev: " << YPos_Stdev;
    double XVelRel_Stdev = radar_data->test_parseSpecifiedSignal(data_bo80.can_id, "FRS_P1_00_Obj_XVelRel_Stdev", data_bo80);
    LOG(INFO) << "XVelRel_Stdev: " << XVelRel_Stdev;
    double XPos_Stdev = radar_data->test_parseSpecifiedSignal(data_bo80.can_id, "FRS_P1_00_Obj_XPos_Stdev", data_bo80);
    LOG(INFO) << "XPos_Stdev: " << XPos_Stdev;
    double XAccRel = radar_data->test_parseSpecifiedSignal(data_bo80.can_id, "FRS_P1_00_Obj_XAccRel", data_bo80);
    LOG(INFO) << "XAccRel: " << XAccRel;
    double ValidFlag = radar_data->test_parseSpecifiedSignal(data_bo80.can_id, "FRS_P1_00_Obj_ValidFlag", data_bo80);
    LOG(INFO) << "ValidFlag: " << ValidFlag;

  #endif


  #if not TEST_RADAR
    canfd_frame chassis_data_bo546;
    chassis_data_bo546.len = char(8);
    chassis_data_bo546.can_id = 0x222;
    chassis_data_bo546.data[0] = 0xD8;
    chassis_data_bo546.data[1] = 0xD3;
    chassis_data_bo546.data[2] = 0x03;
    chassis_data_bo546.data[3] = 0x80;
    chassis_data_bo546.data[4] = 0xC1;
    chassis_data_bo546.data[5] = 0xFF;
    chassis_data_bo546.data[6] = 0xF3;
    chassis_data_bo546.data[7] = 0x1E;

    CanData* chassis_data = new CanData(can_name, dbc_path);
    chassis_data->loadDBC();

    double Yaw_Rate = chassis_data->test_parseSpecifiedSignal(chassis_data_bo546.can_id, "Yaw_Rate_Signal_S", chassis_data_bo546);   
    LOG(INFO) << "Yaw_Rate: " << Yaw_Rate;

  #endif

}