#include "BookmarkManager.h"
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <iostream>

BookmarkManager::BookmarkManager()
{
	std::ifstream infile("../source/categories.txt");
	{
		std::string category;
		while (infile >> category)
		{
			categories.push_back(category);
		}
		bookmarks.resize(categories.size());
		infile.close();
	}
	for (size_t i = 0, vecSize = categories.size(); i < vecSize; ++i)
	{
		std::string filePath = "../source/" + categories[i] + "/bookmarks.txt";
		infile.open(filePath);

		std::string folderName, url;
		int yPos = 10;
		while (infile >> folderName >> url)
		{
			bookmarks[i].push_back(new Bookmark(categories[i], folderName, url, yPos));
			yPos += 275;
		}
		if (i == 0)
			inCategories.push_back(true);
		else
			inCategories.push_back(false);
		infile.close();
	}
	currentCategory = 0;
}

bool BookmarkManager::addBookmark(const std::string& category, const std::string& folderName, const std::string& url)
{
	auto iter = std::find(categories.begin(), categories.end(), category);
	if (iter != categories.end())
	{
		int idx = iter - categories.begin();
		int yPos = bookmarks[idx].size();
		if (yPos == 0)
		{
			yPos = 10;
		}
		else
		{
			yPos = (yPos + 1) * 275;
		}
		bookmarks[idx].push_back(new Bookmark(category, folderName, url, yPos));
		return true;
	}
	else
	{
		std::cout << "could not find the specified category. Aborting.\n";
		return false;
	}
}

void BookmarkManager::changeList(const std::string& input)
{
	auto iter = std::find(categories.begin(), categories.end(), input);
	if (iter != categories.end())
	{
		inCategories[currentCategory] = false;
		currentCategory = iter - categories.begin();
		inCategories[currentCategory] = true;
	}
}

void BookmarkManager::displayCategories() const
{
	for (auto elem : categories)
	{
		std::cout << elem + "\n";
	}

}

void BookmarkManager::draw(sf::RenderWindow& window)
{
	if (bookmarks.size() != 0)
	{
		for (auto elem : bookmarks[currentCategory])
		{
			elem->draw(window);
		}
	}
}

const std::vector<Bookmark*>& BookmarkManager::getBookmarks() const
{
	return bookmarks[currentCategory];
}

bool BookmarkManager::isEmpty() const
{
	return (bookmarks.size() == 0 ? true : false);

}

void BookmarkManager::refreshBookmarks()
{
	for (auto elem : bookmarks[currentCategory])
	{
		delete elem;
	}
	bookmarks[currentCategory].erase(bookmarks[currentCategory].begin(), bookmarks[currentCategory].end());

	std::ifstream infile;
	std::string path = "../source/" + categories[currentCategory] + "/bookmarks.txt";
	infile.open(path);

	std::string folderName, url;
	int yPos = 10;
	while (infile >> folderName >> url)
	{
		bookmarks[currentCategory].push_back(new Bookmark(categories[currentCategory], folderName, url, yPos));
		yPos += 275;
	}
	infile.close();
}

BookmarkManager::~BookmarkManager()
{
	for (auto elem : bookmarks)
	{
		for (auto item : elem)
			delete item;
	}
}