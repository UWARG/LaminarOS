
#ifndef LOS_COMMS_HPP
#define LOS_COMMS_HPP

#include "../Inc/interface_datatypes.hpp"

class LOS_Comms {
    public:
        LOS_Comms();

        void init_FW_CV_comms();

        /**
         * @brief Retrieves latest data from CV, if any.
         *
         * @param dataFromCV Struct in which retrieved data is stored.
         *
         * @return true if data was retrieved, otherwise false
         */
        bool get_from_CV(Data_From_CV_t &dataFromCV);

        /**
         * @brief Sends data to CV.
         *
         * @param dataToCV Data to send.
         */
        void send_to_CV(Data_To_CV_t &dataToCV);


        /**
         * @brief Initiate comms between telemetry manager and attitude manager.
         */
        void init_TM_AM_comms();

        /**
         * @brief Retrieves latest data from AM, if any.
         *
         * @param dataFromAM Struct in which retrieved data is stored.
         *
         * @return true if data was retrieved, otherwise false
         */
        bool get_from_AM(Data_From_AM_t &dataFromAM);

        /**
         * @brief Sends data to AM.
         *
         * @param dataToAM Data to send.
         */
        void send_to_AM(Data_To_AM_t &dataToAM);

    private:
};

#endif /* LOS_COMMS_HPP */
