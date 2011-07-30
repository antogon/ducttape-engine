
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include "FreezePhysicsEvent.hpp"

namespace dt {

FreezePhysicsEvent::FreezePhysicsEvent() {}

const std::string FreezePhysicsEvent::GetType() const {
    return "DT_FREEZEPHYSICS";
}

std::shared_ptr<Event> FreezePhysicsEvent::Clone() const {
    std::shared_ptr<Event> ptr(new FreezePhysicsEvent());
    return ptr;
}

}
