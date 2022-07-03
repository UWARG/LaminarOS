
#ifndef LOS_TELEM_HPP
#define LOS_TELEM_HPP

#include "../Inc/interface_datatypes.hpp"


class LOS_Telem {
    public:
        LOS_Telem();

        void init_telemetry();

        /**
         * @brief Retrieves latest data from ground, if any.
         *
         * @param ... Struct in which retrieved data is stored.
         *
         * @return true if data was retrieved, otherwise false
         */
        bool get_from_ground(Data_From_Ground_t &dataFromGround);

        /**
         * @brief Sends data to ground.
         *
         * @param dataToGround Data to send.
         */
        bool send_to_ground(Data_To_Ground_t &dataToGround);

    private:
};


#endif /* LOS_TELEM_HPP */
