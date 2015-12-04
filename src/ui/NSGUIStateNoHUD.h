//
// Created by j on 12/5/15.
//

#ifndef NS1_NSGUISTATENOHUD_H
#define NS1_NSGUISTATENOHUD_H

#include "INSGUIState.h"
#include "NSGUIStateContext.h"

class NSGUIStateNoHUD : public INSGUIState {
  public:
    NSGUIStateNoHUD(NSGUIStateContext* sc) : stateContext(sc) {}
    ~NSGUIStateNoHUD() {}

    override void execute(sf::Event event) {
        /*
        // check the type of the event...
        switch (event.type) {
            // window closed
            case sf::Event::Closed:
                networkSimulator->quit();
                break;

                // key pressed
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Space:
                        sc->switchState();
                        break;
                }
        }
         */
    }
  private:
    NSGUIStateContext* stateContext;
};

#endif //NS1_NSGUISTATENOHUD_H
