#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include "core/io/resource.h"
#include "core/object/object.h"

/** A queue of commands for the rendering API. */
class CommandQueue : public Resource {
	GDCLASS(CommandQueue, Resource);

protected:
	static void _bind_methods();
};

#endif // COMMAND_QUEUE_H
