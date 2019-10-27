#include <SFML/Graphics.hpp>
#include "BookmarkManager.h"
#include "ButtonBar.h"

#include <iostream>

int main()
{

	sf::RenderWindow window(sf::VideoMode(1024, 600), "Visual Bookmark", sf::Style::Close); //320 by 230
	sf::View windowView(sf::FloatRect(0, 0, 1024, 600));
	window.setView(windowView);

	BookmarkManager bookmarks;
	ButtonBar buttonBar;

	while (window.isOpen())
	{

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{

			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseWheelScrolled:
				if (evnt.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					float offsetY = -evnt.mouseWheelScroll.delta;

					windowView.move(0, 80 * offsetY);
					buttonBar.moveButtonPositions(offsetY);
				}
				window.setView(windowView);
				break;
			case sf::Event::MouseButtonPressed:
				sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
				sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);

				if (!buttonBar.playerClickedButton(coord_pos, bookmarks))
				{
					if (!bookmarks.isEmpty())
					{
						bool found = false;
						for (size_t i = 0, vecSize = bookmarks.getBookmarks().size(); i < vecSize && !found; ++i)
						{
							if (bookmarks.getBookmarks().at(i)->getSprite().getGlobalBounds().contains(coord_pos))
							{
								found = true;
								std::string link = "start C:\\PROGRA~2\\MOZILL~1\\firefox.exe " + bookmarks.getBookmarks().at(i)->getUrl();
								system(link.data());
							}
						}
					}
				}
				break;
			}
		}

		window.clear();
		bookmarks.draw(window);
		buttonBar.draw(window);
		window.display();
	}
}