#include "Bookmark.h"

#include <iostream>
#include <direct.h>
#include <fstream>

Bookmark::Bookmark(const std::string& category, const std::string& folderName, const std::string& url, int yPos)
{
	title = folderName;
	this->url = url;

	std::string fileName = "../source/" + category + "/" + folderName;
	if (_mkdir(fileName.data()) != 0) //this means the folder already exists
	{
		previewImg.loadFromFile(fileName + "/img.png");
		imgSprite.setTexture(previewImg);
		imgSprite.setPosition(10, yPos);

		titleFont.loadFromFile("arial.ttf");
		titleText.setFont(titleFont);
		titleText.setFillColor(sf::Color::White);
		titleText.setString(title);
		titleText.setPosition(400, yPos + 115);
	}
	else
	{
		std::ofstream outfile;
		std::string bookmark = "../source/" + category + "/" + "bookmarks.txt";
		outfile.open(bookmark, std::ios::app);
		outfile << "\n" << folderName << "\n" << url;
		outfile.close();
	}

}

void Bookmark::draw(sf::RenderWindow& window)
{
	window.draw(imgSprite);
	window.draw(titleText);
}

const sf::Sprite& Bookmark::getSprite() const
{
	return imgSprite;
}

const std::string& Bookmark::getUrl() const
{
	return url;
}

Bookmark::~Bookmark()
{
}