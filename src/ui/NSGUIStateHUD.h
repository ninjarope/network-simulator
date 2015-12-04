//
// Created by j on 12/5/15.
//

#ifndef NS1_NSGUISTATEHUD_H
#define NS1_NSGUISTATEHUD_H

#include "INSGUIState.h"
#include "NSGUIStateContext.h"

class NSGUIStateHUD : public INSGUIState {
  public:
    NSGUIStateHUD(NSGUIStateContext* sc) : stateContext(sc) {}
    ~NSGUIStateHUD() {}

    void execute(sf::Event event) override {
        /*
        // check the type of the event...
        switch (event.type)
        {
            // window closed
            case sf::Event::Closed:
                networkSimulator->quit();
                break;

             case sf::Event::MouseMoved:
                checkMouseOverNode(event.mouseMove.x, event.mouseMove.y);
                break;

            case sf::Event::MouseButtonPressed:
                if (altDown) selectedNodes.clear();
                checkMouseOverNode(event.mouseButton.x, event.mouseButton.y);
                if (focusNode.size() > 0) {
                    toggleSelect(focusNode);
                }
                break;

                // key pressed
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Space:
                        sc->switchState();
                        break;

                    case sf::Keyboard::Return:
                        networkSimulator->start();
                        break;

                    case sf::Keyboard::Left:
                        transformX -= 10.0;
                        break;

                    case sf::Keyboard::Right:
                        transformX += 10.0;
                        break;

                    case sf::Keyboard::Up:
                        transformY -= 10.0;
                        break;

                    case sf::Keyboard::Down:
                        transformY += 10.0;
                        break;

                    case sf::Keyboard::Space:
                        networkSimulator->toggleTimer();
                        break;

                    case sf::Keyboard::D:
                        toggleDistributionVisibility();
                        break;

                    case sf::Keyboard::G:
                        generateGraphLayout();
                        break;

                    case sf::Keyboard::S:
                        toggleStatVisibility();
                        break;

                    case sf::Keyboard::M:
                        changeDistributionView();
                        break;

                    case sf::Keyboard::Escape:
                    case sf::Keyboard::Q:
                        networkSimulator->quit();
                        break;

                    case sf::Keyboard::LAlt:
                        altDown = true;
                        break;

                    default:
                        break;
                }
                break;

            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::LAlt:
                        altDown = false;
                        break;
                    default:
                        break;
                }
                break;

                // we don't process other types of events
            default:
                break;
        }
         */
    }
  private:
    NSGUIStateContext* stateContext;
};

#endif //NS1_NSGUISTATEHUD_H
