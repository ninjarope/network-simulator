#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  int x=0;
  int y=0;
  std::cout<<"Please enter size of window"<<std::endl;
  std::cout<<"x length = ";
  std::cin >>x;
  std::cout<<"y length = ";
  std::cin >>y;
  sf::RenderWindow window(sf::VideoMode(x, y), "ns1");
  while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed){
              window.close();
            }
      window.clear(sf::Color::White);
      window.display();
      }

  }
    return 0;
}
