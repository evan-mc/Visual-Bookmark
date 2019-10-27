#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <SFML/Graphics.hpp>

#include <string>

class Bookmark
{
public:
	Bookmark(const std::string& category, const std::string& folderName, const std::string& url, int yPos);

	void draw(sf::RenderWindow& window);

	const sf::Sprite& getSprite() const;

	const std::string& getUrl() const;

	~Bookmark();
private:
	sf::Texture previewImg;
	sf::Sprite imgSprite; //img size should be 320 x 230
	std::string title;
	std::string url;

	sf::Font titleFont;
	sf::Text titleText;
};

#endif