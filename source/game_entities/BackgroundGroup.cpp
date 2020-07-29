#include "BackgroundGroup.h"
#include "../GameInstance.h"

BackgroundGroup::BackgroundGroup(GameInstance* parent) : DrawGroup(parent), fullyRendered(false) {}

BackgroundGroup::~BackgroundGroup() {}

bool BackgroundGroup::exists() {
	return true;
}

int BackgroundGroup::size() {
	return 1;
}

void BackgroundGroup::clearGroup() {
	this->elements.clear();
}

void BackgroundGroup::add(Point position, const std::string& type) {
	this->elements.push_back(std::make_shared<BackElement>(position, type));
}

void BackgroundGroup::drawGroup() {
	if (!this->fullyRendered) this->finalize();
	this->texture.draw(this->parent->getRenderer(), -this->parent->getOffset());
}

void BackgroundGroup::setParent(GameInstance& parent) {
	this->parent = &parent;
}

void BackgroundGroup::finalize() {
	#ifndef NDEBUG
	Uint32 tick = SDL_GetTicks();
	#endif
	
	int width = 0, height = 0;
	std::map<std::string, std::shared_ptr<Texture>> textures;
	
	for (std::shared_ptr<BackElement>& element: this->elements) {
		if (textures[element->type] == NULL) {
			textures[element->type] = BackElement::createGroundTexture(this->parent->getRenderer(), element->type);
			textures[element->type]->normalizeTexture(this->parent->getRenderer());
		}
		Point most = element->position + Point(textures[element->type]->getWidth(), textures[element->type]->getHeight());
		if (most.isReal()) {
			if (most.x > width) width = (int) most.x;
			if (most.y > height) height = (int) most.y;
		}
	}
	this->texture = SDL_CreateTexture(this->parent->getRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);
	
	SDL_SetRenderTarget(this->parent->getRenderer(), this->texture);
	for (std::shared_ptr<BackElement>& element: this->elements) textures[element->type]->draw(this->parent->getRenderer(), element->position);
	SDL_SetRenderTarget(this->parent->getRenderer(), NULL);
	
	this->elements.clear();
	this->fullyRendered = true;
	
	#ifndef NDEBUG
	LOG("Took %i ms to internally render the background. ", (int) (SDL_GetTicks() - tick));
	#endif
}
