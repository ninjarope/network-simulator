//
// Created by j on 12/5/15.
//

#ifndef NS1_NSGUISTATE_H
#define NS1_NSGUISTATE_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class INSGUIState {
  public:
    virtual void execute(sf::Event) = 0;
};
#endif //NS1_NSGUISTATE_H
