#pragma once

#include <SFML/Graphics.hpp>
#include<string>
#include <map>

//TODO make load from file


class TextureManager
{
private:

	/* Array of textures used */
	std::map<std::string, sf::Texture> textures;

public:

	/* Add a texture from a file */
	void loadTexture(const std::string& name, const std::string& filename);

	/* Translate an id into a reference */
	sf::Texture& getRef(const std::string& texture); // returns texture by name

	/* Constructor */
	TextureManager()
	{
	}
};
