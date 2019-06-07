#include <SFML/Graphics.hpp>
#include "BookmarkManager.h"

#include <iostream>

int main()
{

	sf::RenderWindow window(sf::VideoMode(1024, 600), "Visual Bookmark", sf::Style::Close); //320 by 230
	sf::View windowView(sf::FloatRect(0, 0, 1024, 600));
	window.setView(windowView);

	BookmarkManager bookmarks;

	sf::Font buttonFont;
	sf::Text buttonAddBookmark;
	sf::Text buttonRefreshBookmark;
	sf::Text changeCategory;

	sf::RectangleShape bar;
	sf::Color color(0, 1, 130);
	bar.setFillColor(color);
	bar.setPosition(0, 0);
	bar.setSize(sf::Vector2f(1024.f, 37.f));

	buttonFont.loadFromFile("arial.ttf");
	buttonAddBookmark.setFont(buttonFont);
	buttonAddBookmark.setPosition(440, 0);
	buttonAddBookmark.setFillColor(sf::Color::White);
	buttonAddBookmark.setString("Add");

	buttonRefreshBookmark.setFont(buttonFont);
	buttonRefreshBookmark.setPosition(530, 0);
	buttonRefreshBookmark.setFillColor(sf::Color::White);
	buttonRefreshBookmark.setString("Refresh");

	changeCategory.setFont(buttonFont);
	changeCategory.setPosition(70, 0);
	changeCategory.setFillColor(sf::Color::White);
	changeCategory.setString("Change Category");

	int newBookmarks = 0;
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
					windowView.move(0, 80 * -evnt.mouseWheelScroll.delta);

					bar.move(0, 80 * -evnt.mouseWheelScroll.delta);
					buttonAddBookmark.move(0, 80 * -evnt.mouseWheelScroll.delta);
					buttonRefreshBookmark.move(0, 80 * -evnt.mouseWheelScroll.delta);
					changeCategory.move(0, 80 * -evnt.mouseWheelScroll.delta);
				}
				window.setView(windowView);
				break;
			case sf::Event::MouseButtonPressed:
				sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
				sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);

				if (buttonAddBookmark.getGlobalBounds().contains(coord_pos))
				{
					std::string folderNameTemp;
					std::string urlTemp;
					std::string category;
					std::cout << "Please enter the category: ";
					std::cin >> category;
					if (category != ".")
					{
						std::cout << "Please enter the folder name: ";
						std::cin >> folderNameTemp;
						std::cout << "Please enter the url: ";
						std::cin >> urlTemp;

						bookmarks.addBookmark(category, folderNameTemp, urlTemp);
						++newBookmarks;
					}
					else
					{
						std::cout << "Did not create the directory\n";
					}
				}
				else if (buttonRefreshBookmark.getGlobalBounds().contains(coord_pos))
				{
					if (newBookmarks != 0)
					{
						newBookmarks = 0;
						bookmarks.refreshBookmarks();
					}
					else
					{
						std::cout << "No new bookmarks to add\n";
					}
				}
				else if (changeCategory.getGlobalBounds().contains(coord_pos))
				{
					std::cout << "Which category would you like to change to?\n"
						<< "type list for the list of categories: ";
					std::string input;
					std::cin >> input;
					if (input == "list")
					{
						std::cout << "Categories:\n";
						bookmarks.displayCategories();
					}
					else
					{
						bookmarks.changeList(input);
					}
				}
				else
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
				break;
			}
		}

		window.clear();
		bookmarks.draw(window);
		window.draw(bar);
		window.draw(changeCategory);
		window.draw(buttonAddBookmark);
		window.draw(buttonRefreshBookmark);
		window.display();
	}
}