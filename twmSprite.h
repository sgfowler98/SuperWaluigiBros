#ifndef TWMSPRITE__H
#define TWMSPRITE__H
#include <string>
#include "drawable.h"
#include <vector>

class TWMSprite : public Drawable {
public:
	TWMSprite(const std::string&);
	TWMSprite(const TWMSprite&);
	virtual ~TWMSprite() {}
	TWMSprite& operator=(const TWMSprite&);

	virtual void draw() const;
	virtual void update(Uint32 ticks);
	virtual const Image* getImage() const;
	virtual const SDL_Surface* getSurface() const;

	int getScaledWidth() const { return getScale()*images[currentFrame]->getWidth(); }
	int getScaledHeight() const { return getScale()*images[currentFrame]->getHeight(); }

protected:
	std::vector<Image*> images;
	unsigned currentFrame;
	unsigned numberOfFrames;
	unsigned frameInterval;
	float timeSinceLastFrame;
	int worldWidth;
	int worldHeight;

	void advanceFrame(Uint32 ticks);
};
#endif
