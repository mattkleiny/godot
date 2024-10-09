#ifndef RENDERGRAPH_H
#define RENDERGRAPH_H

#include "core/io/resource.h"
#include "core/object/object.h"

class RenderPass;
class RenderPassNode;
class RenderGraphNode;

/** A render graph that can be used to define a rendering pipeline. */
class RenderGraph : public Resource {
	GDCLASS(RenderGraph, Resource);

protected:
	static void _bind_methods();
};

/** A single node in the render graph. */
class RenderGraphNode : public Resource {
	GDCLASS(RenderGraphNode, Resource);

protected:
	static void _bind_methods();
};

/** A node that represents a render pass in the render graph. */
class RenderPassNode : public RenderGraphNode {
	GDCLASS(RenderPassNode, RenderGraphNode);

protected:
	static void _bind_methods();
};

#endif // RENDERGRAPH_H
