#ifndef RENDER_PIPELINE_H
#define RENDER_PIPELINE_H

#include "core/io/resource.h"
#include "core/object/object.h"

class RenderPass;

/** A rendering pipeline. */
class RenderPipeline : public Resource {
	GDCLASS(RenderPipeline, Resource);

protected:
	static void _bind_methods();
};

/** A single pass in a rendering pipeline. */
class RenderPass : public Object {
	GDCLASS(RenderPass, Object);

protected:
	static void _bind_methods();
};

#endif // RENDER_PIPELINE_H
