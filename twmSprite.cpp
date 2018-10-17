#include "twmSprite.h"
#include <iostream>
#include "gameData.h"
#include "imageFactory.h"

void TWMSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
		currentFrame = (currentFrame + 1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

TWMSprite::TWMSprite(const std::string& name) :
	Drawable(name,
		Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
			Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
		Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
			Gamedata::getInstance().getXmlInt(name+"/speedY"))),
		images(ImageFactory::getInstance().getImages(name)),
		currentFrame(0),
		numberOfFrames(Gamedata::getInstance().getXmlInt(name+"/frames")),
		frameInterval(Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
		timeSinceLastFrame(0),
		worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
		worldHeight(Gamedata::getInstance().getXmlInt("world/height")) {}

TWMSprite::TWMSprite(const TWMSprite& t) :
	Drawable(t), images(t.images), currentFrame(t.currentFrame),
		numberOfFrames(t.numberOfFrames), frameInterval(t.frameInterval),
		timeSinceLastFrame(t.timeSinceLastFrame), worldWidth(t.worldWidth),
		worldHeight(t.worldHeight) {}

TWMSprite& TWMSprite::operator=(const TWMSprite& t) {
	Drawable::operator=(t);
	images = t.images;
	currentFrame = t.currentFrame;
	numberOfFrames = t.numberOfFrames;
	frameInterval = t.frameInterval;
	timeSinceLastFrame = t.timeSinceLastFrame;
	worldWidth = t.worldWidth;
	worldHeight = t.worldHeight;
	return *this;
}

void TWMSprite::draw() const {
	if (getVelocityX() < 0) {
		images[currentFrame % (numberOfFrames/2)]->draw(getX(), getY(), getScale());
	} else if (getVelocityX() >= 0) {
		images[(currentFrame % (numberOfFrames/2)) + (numberOfFrames/2)]->draw(getX(), getY(), getScale());
	}
}

void TWMSprite::update(Uint32 ticks) {
	advanceFrame(ticks);

	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);

	if (getY() < 0) {
		setVelocityY(fabs(getVelocityY()));
	}
	if (getY() > worldHeight - getScaledHeight()) {
		setVelocityY(-fabs(getVelocityY()));
	}
	if (getX() < 0) {
		setVelocityX(fabs(getVelocityX()));
	}
	if (getX() > worldWidth - getScaledHeight()) {
		setVelocityX(-fabs(getVelocityX()));
	}
}

const Image* TWMSprite::getImage() const {
	if (getVelocityX() < 0) {
		return images[currentFrame % (numberOfFrames/2)];
	} else if (getVelocityX() >= 0) {
		return images[(currentFrame % (numberOfFrames/2)) + (numberOfFrames/2)];
	}
	return nullptr;
}

const SDL_Surface* TWMSprite::getSurface() const {
	if (getVelocityX() < 0) {
		return images[currentFrame % (numberOfFrames/2)]->getSurface();
	} else if (getVelocityX() >= 0) {
		return images[(currentFrame % (numberOfFrames/2)) + (numberOfFrames/2)]->getSurface();
	}
	return nullptr;
}

