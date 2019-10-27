#include "ButtonBar.h"
#include <iostream>

ButtonBar::ButtonBar()
{
	countOfNewBookmarks = 0;

	bar.setFillColor(sf::Color(0, 1, 130));
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

	buttonChangeCategory.setFont(buttonFont);
	buttonChangeCategory.setPosition(70, 0);
	buttonChangeCategory.setFillColor(sf::Color::White);
	buttonChangeCategory.setString("Change Category");
}

void ButtonBar::draw(sf::RenderWindow& window)
{
	window.draw(bar);
	window.draw(buttonChangeCategory);
	window.draw(buttonAddBookmark);
	window.draw(buttonRefreshBookmark);
}

void ButtonBar::moveButtonPositions(float offsetY)
{
	bar.move(0, 80 * offsetY);
	buttonAddBookmark.move(0, 80 * offsetY);
	buttonRefreshBookmark.move(0, 80 * offsetY);
	buttonChangeCategory.move(0, 80 * offsetY);
}

bool ButtonBar::playerClickedButton(const sf::Vector2f& coord_pos, BookmarkManager& bookmarks)
{
	bool buttonWasClicked = false;

	if(buttonAddBookmark.getGlobalBounds().contains(coord_pos))
	{
		buttonWasClicked = true;
		clickedAddBookmark(bookmarks);
	}
	else if(buttonRefreshBookmark.getGlobalBounds().contains(coord_pos))
	{
		buttonWasClicked = true;
		clickedRefreshBookmark(bookmarks);
	}
	else if(buttonChangeCategory.getGlobalBounds().contains(coord_pos))
	{
		buttonWasClicked = true;
		clickedChangeCategory(bookmarks);
	}

	return buttonWasClicked;
}

void ButtonBar::clickedAddBookmark(BookmarkManager& bookmarks)
{
	std::string folderNameTemp;
	std::string urlTemp;
	std::string category;

	std::cout << "Please enter the category: ";
	std::cin >> category;
	std::cout << "Please enter the folder name: ";
	std::cin >> folderNameTemp;
	std::cout << "Please enter the url: ";
	std::cin >> urlTemp;

	if(bookmarks.addBookmark(category, folderNameTemp, urlTemp))
		++countOfNewBookmarks;
}

void ButtonBar::clickedRefreshBookmark(BookmarkManager& bookmarks)
{
	if (countOfNewBookmarks != 0)
	{
		countOfNewBookmarks = 0;
		bookmarks.refreshBookmarks();
	}
	else
	{
		std::cout << "No new bookmarks to add\n";
	}
}

void ButtonBar::clickedChangeCategory(BookmarkManager& bookmarks) const
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

ButtonBar::~ButtonBar()
{
}