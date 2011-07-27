
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include "Root.hpp"
#include "game/Game.hpp"
#include "scene/Scene.hpp"
#include "scene/Node.hpp"

class Main: public dt::State {
public:
    Main() {
        mRuntime = 0;
    }

    void HandleEvent(std::shared_ptr<dt::Event> e) {
        if(e->GetType() == "DT_BEGINFRAMEEVENT") {
            mRuntime += std::dynamic_pointer_cast<dt::BeginFrameEvent>(e)->GetFrameTime();

            if(mRuntime >= 0 && mStep == 0) {
                mStep = 1;
                dt::Logger::Get().Debug("Mode: Hidden");
                dt::InputManager::Get()->SetMouseCursorMode(dt::InputManager::HIDDEN);
            } else if(mRuntime >= 2.0 && mStep == 1) {
                mStep = 2;
                dt::Logger::Get().Debug("Mode: Graphical");
                dt::InputManager::Get()->SetMouseCursorMode(dt::InputManager::GRAPHICAL);
            } else if(mRuntime >= 4.0 && mStep == 2) {
                mStep = 3;
                dt::Logger::Get().Debug("Mode: System");
                dt::InputManager::Get()->SetMouseCursorMode(dt::InputManager::SYSTEM);
            } else if(mRuntime >= 6.0 && mStep == 3) {
                mStep = 4;
                dt::Logger::Get().Debug("Mode: Graphical again");
                dt::InputManager::Get()->SetMouseCursorMode(dt::InputManager::GRAPHICAL);
            } else if(mRuntime >= 8.0 && mStep == 4) {
               mStep = 5;
               dt::Logger::Get().Debug("Mode: Hidden again");
               dt::InputManager::Get()->SetMouseCursorMode(dt::InputManager::HIDDEN);
            }
            if(mRuntime > 10.0) {
                dt::StateManager::Get()->Pop(1);
            }
        }
    }

    void OnInitialize() {
        mStep = 0;

        dt::InputManager::Get()->SetJailInput(false);
        dt::ResourceManager::Get()->AddResourceLocation("gui","FileSystem", true);

        // need to create a camera so we have a window
        dt::Scene* scene = AddScene(new dt::Scene("testscene"));
        scene->AddChildNode(new dt::Node("camnode"))->AddComponent<dt::CameraComponent>(new dt::CameraComponent("cam"));
    }

private:
    double mRuntime;
    int mStep;

};

int main(int argc, char** argv) {
    dt::Game game;
    game.Run(new Main(), argc, argv);
    return 0;
}