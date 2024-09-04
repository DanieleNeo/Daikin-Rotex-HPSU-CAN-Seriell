#pragma once

#include "esphome/components/daikin_rotex_can/request.h"
#include <vector>

namespace esphome {
namespace daikin_rotex_can {

class Accessor;

class TRequests {
public:
    TRequests(std::vector<esphome::daikin_rotex_can::TRequest> const& requests);

    void removeInvalidRequests(Accessor const& accessor);

    void setCanbus(esphome::esp32_can::ESP32Can* pCanBus);

    uint32_t size() const;
    TRequest const& get(uint32_t index) const;

    bool sendNextPendingGet();
    void sendGet(std::string const& request_name, Accessor const& accessor);
    void sendSet(std::string const& request_name, float value);
    void handle(uint32_t can_id, std::vector<uint8_t> const& responseData, Accessor&);

private:
    TRequest* getNextRequestToSend();

    std::vector<TRequest> m_requests;
    esphome::esp32_can::ESP32Can* m_pCanBus;
};

inline void TRequests::setCanbus(esphome::esp32_can::ESP32Can* pCanBus) {
    m_pCanBus = pCanBus;
}

inline uint32_t TRequests::size() const {
    return m_requests.size();
}

inline TRequest const& TRequests::get(uint32_t index) const {
    return m_requests[index];
}


}
}