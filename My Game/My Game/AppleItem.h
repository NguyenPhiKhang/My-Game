#ifndef  _APPLE_ITEM_H
#define _APPLE_ITEM_H

#include "Entity.h"

namespace appleItemNS {
	const int WIDTH = 11;
	const int HEIGHT = 12;

	const int APPLE_START_FRAME = 0;
	const int APPLE_END_FRAME = 0;
	const int TEXTURE_COLS = 1;
}


class AppleItem : public Entity {
private:
public:
	AppleItem(float x, float y);
	~AppleItem();
};

#endif // ! _APPLE_ITEM_H
