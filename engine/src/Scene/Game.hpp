
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_GAME_GAME
#define DUCTTAPE_ENGINE_GAME_GAME

#include <Config.hpp>

#include <Event/Event.hpp>
#include <Event/EventListener.hpp>
#include <Scene/State.hpp>

#include <SFML/System/Clock.hpp>

#include <memory>

namespace dt {

/**
  * The main instance of a game, running the main loop.
  */
class DUCTTAPE_API Game : public EventListener {
public:
    /**
      * Default constructor.
      */
    Game();

    virtual void HandleEvent(std::shared_ptr<Event> e);

    /**
      * The main loop of the Game. Calls OnInitialize().
      * @param start_state The initial state to start with.
      * @param argc Command line param count.
      * @param argv Command line params.
      * @see State
      */
    void Run(State* start_state, int argc, char** argv);

    /**
      * Requests a shutdown. The current frame is being processed, but then the main loop will be cancelled.
      */
    void RequestShutdown();

    /**
      * Returns whether a requested shutdown should be handled. Override this to cancel a shutdown, e.g. when the window was closed.
      * @returns Whether a requested shutdown should be handled.
      */
    virtual bool OnShutdownRequested();

    /**
      * Returns whether the main loop is running.
      * @returns Whether the main loop is running.
      */
    bool IsRunning();

protected:
    sf::Clock mClock;           //!< A clock for timing the frames.
    bool mIsShutdownRequested;  //!< Whether a shutdown has been requested.
    bool mIsRunning;            //!< Whether the game loop is running.
};

} // namespace dt

#endif
