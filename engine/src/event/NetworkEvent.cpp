#include "NetworkEvent.hpp"

#include "Root.hpp"

namespace dt {

NetworkEvent::NetworkEvent() {
    ConnectionsManager* cm = Root::get_mutable_instance().GetNetworkManager()->GetConnectionsManager();
    for(Connection* c: cm->GetAllConnections()) {
        AddRecipient(cm->GetConnectionID(*c));
    }
}

bool NetworkEvent::IsNetworkEvent() const {
    return true;
}

void NetworkEvent::AddRecipient(uint16_t id) {
    mRecipients.push_back(id);
}

void NetworkEvent::RemoveRecipient(uint16_t id) {
    for(auto iter = mRecipients.begin(); iter != mRecipients.end(); ++iter) {
        if(*iter == id) {
            iter = mRecipients.erase(iter);
        }
    }
}

void NetworkEvent::ClearRecipients() {
    mRecipients.clear();
}

const std::vector<uint16_t>& NetworkEvent::GetRecipients() const {
    return mRecipients;
}

bool NetworkEvent::HasRecipient(uint16_t id) {
    for(uint16_t i: mRecipients)
        if(i == id)
            return true;
    return false;
}

}
