#ifndef RENDERGRAPH_H
#define RENDERGRAPH_H

#include "core/io/resource.h"
#include "core/object/object.h"

#include "servers/rendering/renderer_pipeline.h"

// A single node in the render graph.
class RenderGraphNode : public Resource {
	GDCLASS(RenderGraphNode, Resource);

protected:
	static void _bind_methods();
};

// A graph that can be used to define a rendering pipeline
class RenderGraph : public Resource {
	GDCLASS(RenderGraph, Resource);

	List<Ref<RenderGraphNode>> nodes;

protected:
	static void _bind_methods();
};

// A render pipeline backed by a render graph resource.
class RenderGraphPipeline : public RenderPipeline {
  GDCLASS(RenderGraphPipeline, RenderPipeline);

	Ref<RenderGraph> graph;

protected:
	static void _bind_methods();

public:
	void set_graph(Ref<RenderGraph>& p_graph);
	Ref<RenderGraph> get_graph() const;

	virtual void render_viewport(const Viewport& p_viewport) override;
};


#endif // RENDERGRAPH_H
