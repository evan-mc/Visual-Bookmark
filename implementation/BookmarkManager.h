#ifndef BOOKMARKMANAGER_H
#define BOOKMARKMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Bookmark.h"

class BookmarkManager
{
public:
	BookmarkManager();

	bool addBookmark(const std::string& category, const std::string& folderName, const std::string& url);

	void changeList(const std::string& input);

	void displayCategories() const;

	void draw(sf::RenderWindow& window);

	const std::vector<Bookmark*>& getBookmarks() const;

	bool isEmpty() const;

	void refreshBookmarks();

	~BookmarkManager();
private:
	std::vector<std::string> categories;
	std::vector<std::vector<Bookmark*>> bookmarks;
	std::vector<bool> inCategories;
	int currentCategory;
};

#endif