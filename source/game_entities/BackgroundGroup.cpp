#include "BackgroundGroup.h"
#include "../GameInstance.h"

BackgroundGroup::BackgroundGroup(GameInstance* parent) : DrawGroup(parent), mfe(NULL) {
	this->rect = {0,0,0,0};
}

BackgroundGroup::~BackgroundGroup() {
	this->clearGroup();
}

bool BackgroundGroup::exists() {
	return this->elements.size() > 0;
}

int BackgroundGroup::size() {
	return this->elements.size();
}

void BackgroundGroup::clearGroup() {
	this->elements.clear();
}

void BackgroundGroup::add(Point position, const std::string& type) {
	if (this->textures[type] == NULL) {
		this->textures[type] = BackElement::createGroundTexture(this->parent->getRenderer(), type);
		this->textures[type]->normalizeTexture(this->parent->getRenderer());
	}
	this->elements.push_back(std::make_shared<BackElement>(position, type));
	this->elements.back()->setTexture(this->textures[type]);
	
	Point most = position + Point(this->textures[type]->getWidth(), this->textures[type]->getHeight());
	if (most.isReal()) {
		if (most.x > this->rect.w) this->rect.w = (int) most.x;
		if (most.y > this->rect.h) this->rect.h = (int) most.y;
	}
}

// TODO: Make this not god awful
void BackgroundGroup::drawGroup() {
	int x, y;
	SDL_GetRendererOutputSize(this->parent->getRenderer(), &x, &y);
	SDL_Rect temp = {0, 0, x, y};
	SDL_Rect temp2 = {(int)this->parent->getOffset().x, (int)this->parent->getOffset().y, x, y};

	SDL_RenderCopy(this->parent->getRenderer(), this->texture.getRawTexture(), &temp2, &temp);
}

void BackgroundGroup::setParent(GameInstance& parent) {
	this->parent = &parent;
}

void BackgroundGroup::finalize() {
	SDL_Texture* text = SDL_CreateTexture(this->parent->getRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, this->rect.w, this->rect.h);
	SDL_SetRenderTarget(this->parent->getRenderer(), text);
	for (std::shared_ptr<BackElement>& element: this->elements) {
		element->draw(this->parent->getRenderer(), Point(0, 0));
	}
	SDL_SetRenderTarget(this->parent->getRenderer(), NULL);
	this->elements.clear();
	this->texture.getRawTexture() = text;
}
