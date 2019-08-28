#include "Entity.h"


//=============================================================================
// constructor
//============================================================================
Entity::Entity():Image()
{
	radius = 1.0f;
	edge.left = -1;
	edge.top = -1;
	edge.right = 1;
	edge.bottom = 1;
	mass = 1.0f;
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	deltaV.x = 0.0f;
	deltaV.y = 0.0f;
	active = true;			// the Entity is active
	rotatedBoxReady = true;
	collisionType = entityNS::CIRCLE;
	health = 100;
	gravity = entityNS::GRAVITY;
}

//=============================================================================
// Initialize the Entity.
// Pre: *gamePtr = pointer to Game object
//      width = width of Image in pixels  (0 = use full texture width)
//      height = height of Image in pixels (0 = use full texture height)
//      ncols = number of columns in texture (1 to n) (0 same as 1)
//      *textureM = pointer to TextureManager object
// Post: returns true if successful, false if failed
//=============================================================================
bool Entity::initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM)
{
	input = gamePtr->getInput();
	return (Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

//=============================================================================
// activate the entity	
//=============================================================================
void Entity::activate()
{
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Entity::update(float frametime)
{
	velocity += deltaV;
	deltaV.x = 0;
	deltaV.y = 0;
	Image::update(frametime);
	rotatedBoxReady = false;	// for rotatedBox collision detection
}

//=============================================================================
// ai (artificial intelligence)
// typically called once per frame
// performs ai calculations, ent is passed for interaction
//=============================================================================
void Entity::ai(float frameTime, Entity& ent)
{}

//=============================================================================
// Perform collision detection between this entity and the other Entity.
// Each entity must use a single collision type. Complex shapes that require
// multiple collision types may be done by treating each part as a separate
// entity.
// Typically called once per frame.
// The collision types: CIRCLE, BOX, or ROTATED_BOX.
// Post: returns true if collision, false otherwise
//       sets collisionVector if collision
//=============================================================================
bool Entity::collidesWith(Entity& ent, D3DXVECTOR2& collisionVector)
{
	// if etheier entity is not active then no collison may occur
	if (!active || ent.getActive())
		return false;

	// if both entities are CIRCLE collision
	if (collisionType == entityNS::CIRCLE && ent.getCollisionType() == entityNS::CIRCLE)
		return collideCircle(ent, collisionVector);
	// if both entities are BOX collision
	if (collisionType == entityNS::BOX && ent.getCollisionType() == entityNS::BOX)
		return collideBox(ent, collisionVector);
	// All other combinations use separating axis test
	// if neither entity uses CIRCLE collision
	if (collisionType != entityNS::CIRCLE && ent.getCollisionType() != entityNS::CIRCLE)
		return collideRotatedBox(ent, collisionVector);
	else // one of the entities is a circle
	{
		if (collisionType == entityNS::CIRCLE) // if this entity uses CIRCLE collision
		{
			// Check for collision from other box with our circle
			bool collide = ent.collideRotatedBoxCircle(*this, collisionVector);
			// Put the collision vector in the proper direction
			collisionVector *= -1;		//reverse collision vector
			return collide;
		}
		else // the other entity uses CIRCLE collsion
			return collideRotatedBoxCircle(ent, collisionVector);
		return false;
	}
}

//=============================================================================
// Circular collision detection method
// Called by collision(), default collision detection method
// Post: returns true if collision, false otherwise
//       sets collisionVector if collision
//=============================================================================
bool Entity::collideCircle(Entity& ent, D3DXVECTOR2& collisionVector)
{
	// different between centers
	distSquared = *getCenter() - *ent.getCenter();
	distSquared.x *= distSquared.x;
	distSquared.y *= distSquared.y;

	// Caculate the sum of the radii (adjusted for scale)
	sumRadiiSquared = radius * getScale() + ent.getRadius() * ent.getScale();
	sumRadiiSquared *= sumRadiiSquared;

	//if entities are colliding
	if (distSquared.x + distSquared.y <= sumRadiiSquared)
	{
		//set collision vector
		collisionVector = *ent.getCenter() - *getCenter();
		return true;
	}
	return false;	// no colliding
}
//=============================================================================
// Rotated Box collision detection method
// Called by collision()
// Post: returns true if collision, false otherwise
//       sets collisionVector if collision
// Uses Separating Axis Test to detect collision. 
// The separating axis test:
//   Two boxes are not colliding if their projections onto a line do not overlap.
//=============================================================================