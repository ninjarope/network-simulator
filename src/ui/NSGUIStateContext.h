//
// Created by j on 12/5/15.
//

#ifndef NS1_NSGUISTATECONTEXT_H
#define NS1_NSGUISTATECONTEXT_H

#include "INSGUIState.h"
#include "NSGUIStateHUD.h"
#include "NSGUIStateNoHUD.h"
#include <vector>

class NSGUIStateContext : public INSGUIState {
  public:
    /**
     * Constructor instanciates the states and stores them
     */
    NSGUIStateContext() : statePool() {
        statePool.push_back(new NSGUIStateHUD(this));
        statePool.push_back(new NSGUIStateNoHUD(this));
        state = statePool[0];
        nextToggleState = 1;
    }
    ~NSGUIStateContext() {
        for (auto s : statePool) {
            delete s;
        }
    }

    /**
     * Switch the state object to another.
     *
     * Currently just toggles between two states.
     */
    void switchState() {
        state = statePool[nextToggleState];
        nextToggleState = nextToggleState == 0 ? 1 : 0;
    }

    /**
     * Defines the interface / delegates the execution to the
     * current state object
     */
    override void execute(sf::Event event) {
        state.execute(event);
    }
  private:
    INSGUIState* state;
    std::vector<INSGUIState*> statePool;
    int nextToggleState;
};
#endif //NS1_NSGUISTATECONTEXT_H
