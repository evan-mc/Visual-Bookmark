#ifndef BUTTONBAR_H
#define BUTTONBAR_H

#include <SFML/Graphics.hpp>
#include "BookmarkManager.h"

class ButtonBar
{
public:
	ButtonBar();

	void draw(sf::RenderWindow& window);

	void moveButtonPositions(float offsetY);

	bool playerClickedButton(const sf::Vector2f& coord_pos, BookmarkManager& bookmarks);

	~ButtonBar();

private:
	void clickedAddBookmark(BookmarkManager& bookmarks);
	void clickedRefreshBookmark(BookmarkManager& bookmarks);
	void clickedChangeCategory(BookmarkManager& bookmarks) const;

	int countOfNewBookmarks;

	sf::Font buttonFont;
	sf::Text buttonAddBookmark;
	sf::Text buttonRefreshBookmark;
	sf::Text buttonChangeCategory;

	sf::RectangleShape bar;

};

#endif