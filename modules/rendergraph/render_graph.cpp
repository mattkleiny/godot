#include "render_graph.h"

// RenderGraphNode

void RenderGraphNode::_bind_methods() {}

// RenderGraph

void RenderGraph::_bind_methods() {}

// RenderGraphPipeline

void RenderGraphPipeline::_bind_methods() {
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "graph", PROPERTY_HINT_RESOURCE_TYPE, "RenderGraph"), "set_graph", "get_graph");
}

void RenderGraphPipeline::set_graph(Ref<RenderGraph>& p_graph) {
  graph = p_graph;
}

Ref<RenderGraph> RenderGraphPipeline::get_graph() const {
  return graph;
}

void RenderGraphPipeline::render_viewport(const Viewport& p_viewport) {
  if (graph.is_null()) {
    return;
  }

  // TODO: delegate to the render graph
}