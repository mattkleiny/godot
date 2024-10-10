#ifndef RENDER_PIPELINE_H
#define RENDER_PIPELINE_H

#include "core/io/resource.h"

class RenderPipeline : public Resource {
	GDCLASS(RenderPipeline, Resource);

protected:
	static void _bind_methods();
};

#endif // RENDER_PIPELINE_H
