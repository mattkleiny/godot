#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "core/node.h"
#include "core/resource.h"

class GameMode : public Resource {
	GDCLASS(GameMode, Resource);

protected:
	static void _bind_methods() {}
};

class Pawn : public Node {
	GDCLASS(Pawn, Node);

protected:
	static void _bind_methods() {}
};

class PawnController : public Object {
	GDCLASS(PawnController, Object);

protected:
	static void _bind_methods() {}
};

#endif // GAMEPLAY_H
