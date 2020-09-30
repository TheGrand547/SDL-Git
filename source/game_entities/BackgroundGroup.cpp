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
	this->texture.draw(this->parent->getTrueRenderer(), -this->parent->getOffset());
}

void BackgroundGroup::setParent(GameInstance& parent) {
	this->parent = &parent;
}

void BackgroundGroup::finalize() {
	Uint32 tick = SDL_GetTicks();

	int width = 0, height = 0;
	std::map<std::string, std::shared_ptr<Surface>> textures;
	SDL_Renderer* renderer = this->parent->getRenderer().renderer;
	for (std::shared_ptr<BackElement>& element: this->elements) {
		if (textures[element->type] == NULL) {
			textures[element->type] = BackElement::createGroundSurface(element->type);
			textures[element->type]->finalize(renderer);
		}
		Point most = element->position + textures[element->type]->getSize();
		if (most.isReal()) {
			if (most.x > width) width = (int) most.x;
			if (most.y > height) height = (int) most.y;
		}
	}
	this->texture = SDL_CreateTexture(this->parent->getTrueRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);

	SDL_SetRenderTarget(renderer, this->texture);
	for (std::shared_ptr<BackElement>& element: this->elements) textures[element->type]->draw(renderer, element->position);
	SDL_SetRenderTarget(renderer, NULL);

	this->elements.clear();
	this->fullyRendered = true;

	if (this->parent->gameState["verbose"]) LOG("Took %i ms to internally render the background. ", (int) (SDL_GetTicks() - tick));
}
