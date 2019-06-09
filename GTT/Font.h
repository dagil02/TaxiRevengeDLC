#pragma once
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
using namespace std;

class Font {
public:
	Font();
	Font(string fileName, int size);
	virtual ~Font();

	bool load(string fileName, int size);
	void close();
	SDL_Surface* renderText(string text, SDL_Color color) const;

	const int getSize() const;

private:
	TTF_Font *font_;
	int size_;
};