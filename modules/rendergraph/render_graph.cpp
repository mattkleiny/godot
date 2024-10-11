#include "render_graph.h"

// RenderGraphNode

void RenderGraphNode::_bind_methods() {}

void RenderGraphNode::render_viewport(const Viewport& p_viewport) {
}

// RenderGraph

void RenderGraph::_bind_methods() {}

int RenderGraph::get_node_count() const {
  return nodes.size();
}

void RenderGraph::add_node(const Ref<RenderGraphNode>& p_node) {
  nodes.push_back(p_node);
}

void RenderGraph::remove_node(int p_index) {
  ERR_FAIL_INDEX(p_index, nodes.size());
  nodes.remove(p_index);
}

Ref<RenderGraphNode> RenderGraph::get_node(int p_index) const {
  ERR_FAIL_INDEX_V(p_index, nodes.size(), Ref<RenderGraphNode>());
  return nodes[p_index];
}

Ref<RenderGraphNode> RenderGraph::get_root_node() const {
  for (int i = 0; i < nodes.size(); i++) {
    Ref<RenderGraphNode> node = nodes[i];
    
    if (node->is_root()) {
      return node;
    }
  }

  return Ref<RenderGraphNode>();
}

void RenderGraph::render_viewport(const Viewport& p_viewport) {
  Ref<RenderGraphNode> root_node = get_root_node();

  if (root_node.is_null()) {
    return;
  }

  root_node->render_viewport(p_viewport);
}

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

  graph->render_viewport(p_viewport);
}