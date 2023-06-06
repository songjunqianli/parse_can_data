#include "can_data.hpp"

int main(int argc, char *argv[]) {
    string can_name;
    string dbc_path;
    
    if (argc == 3) {
        can_name = argv[1];
        dbc_path = argv[2];
    }
    CanData* chassis_data = new CanData(can_name, dbc_path);
    chassis_data->loadDBC();

    // 获取指定报文的数据
    auto signals = chassis_data->BO_messages_[BOEachWheelSpeed]->getSignals();
    LOG(INFO)  << "BO SIZE:" << chassis_data->BO_messages_.size() << ", ";
    LOG(INFO)  << "BO NAME: " << chassis_data->BO_messages_[BOEachWheelSpeed]->getName() << ", "
                << "BO DLC: " << chassis_data->BO_messages_[BOEachWheelSpeed]->getDlc() << ", "
                << "BO Signals num: " << signals.size() << ", "
                << "    signal name: " << signals[SIG_FL_WHEEL_SPEED]->getName() << "\n"
                << "                 start_bit: " << static_cast<unsigned int>(signals[SIG_FL_WHEEL_SPEED]->getStartBit()) << "\n"
                << "                 length: " << static_cast<unsigned int>(signals[SIG_FL_WHEEL_SPEED]->getLength()) << "\n"
                << "                 factor: " << signals[SIG_FL_WHEEL_SPEED]->getFactor() << "\n"
                << "                 offset: " << signals[SIG_FL_WHEEL_SPEED]->getOffset() << "\n"
                << "                 endianness: " << (signals[SIG_FL_WHEEL_SPEED]->getEndianness() == Order::BE ? "Moto big-endian" : "Intel little-endian") << "\n"
                << "                 unit: " << signals[SIG_FL_WHEEL_SPEED]->getUnit() << endl;

    // 获取所有报文的数据
    LOG(INFO)  << "BOS SIZE:" << chassis_data->BO_messages_.size() << endl;
    int count = 1;
    for (auto &msg : chassis_data->BO_messages_) {
        auto msg_id = msg.second->getId();
        auto msg_name = msg.second->getName();
        auto msg_DLC = msg.second->getDlc();
        auto signals = msg.second->getSignals();
        LOG(INFO) << "BO ID: " << msg_id << ", name: " << msg_name << ", DLC: " << msg_DLC << ", sig_nums: " << signals.size() << ", count: " << count << endl;


        for (auto & sig : signals) {
        auto sig_name =  sig.second->getName();
        auto start_bit = static_cast<unsigned int>(sig.second->getStartBit());
        auto length = static_cast<unsigned int>(sig.second->getLength());
        auto factor = sig.second->getFactor();
        auto offset = sig.second->getOffset();
        auto unit = sig.second->getUnit();
        LOG(INFO) << "      sig_name: " << sig_name << endl;
        LOG(INFO) << "          start_bit: " << start_bit << endl;
        LOG(INFO) << "          length: " << length << endl;
        LOG(INFO) << "          factor: " << factor << endl;
        LOG(INFO) << "          offset: " << offset << endl;
        LOG(INFO) << "          unit: " << unit << endl;
        LOG(INFO) << "          endianness: " << (sig.second->getEndianness() == Order::BE ? "big-endian" : "little-endian") << endl;
        LOG(INFO) << "          is signed: " << (sig.second->isSigned() ? "true" : "false") << endl;
      }
      count++;
    }

}