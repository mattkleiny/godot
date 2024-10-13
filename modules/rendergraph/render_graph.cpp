/**************************************************************************/
/*  render_graph.cpp                                                      */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "render_graph.h"

// RenderGraphNode

void RenderGraphNode::render_viewport(Viewport *p_viewport) {
}

void RenderGraphNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_root", "root"), &RenderGraphNode::set_root);
	ClassDB::bind_method(D_METHOD("is_root"), &RenderGraphNode::is_root);

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "root"), "set_root", "is_root");
}

// RenderGraph

int RenderGraph::get_node_count() const {
	return nodes.size();
}

void RenderGraph::add_node(const Ref<RenderGraphNode> &p_node) {
	nodes.push_back(p_node);
}

void RenderGraph::remove_node(const Ref<RenderGraphNode> &p_node) {
	nodes.erase(p_node);
}

Ref<RenderGraphNode> RenderGraph::get_root_node() const {
	for (const Ref<RenderGraphNode> &node : nodes) {
		if (node->is_root()) {
			return node;
		}
	}

	return Ref<RenderGraphNode>();
}

void RenderGraph::render_viewport(Viewport *p_viewport) {
	Ref<RenderGraphNode> root_node = get_root_node();

	if (root_node.is_null()) {
		return;
	}

	root_node->render_viewport(p_viewport);
}

void RenderGraph::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_node_count"), &RenderGraph::get_node_count);
	ClassDB::bind_method(D_METHOD("add_node", "node"), &RenderGraph::add_node);
	ClassDB::bind_method(D_METHOD("remove_node", "index"), &RenderGraph::remove_node);
	ClassDB::bind_method(D_METHOD("get_root_node"), &RenderGraph::get_root_node);
}

// RenderGraphPipeline

void RenderGraphPipeline::set_graph(const Ref<RenderGraph> &p_graph) {
	graph = p_graph;
}

Ref<RenderGraph> RenderGraphPipeline::get_graph() const {
	return graph;
}

void RenderGraphPipeline::render_viewport(Viewport *p_viewport) {
	if (graph.is_null()) {
		return;
	}

	graph->render_viewport(p_viewport);
}

void RenderGraphPipeline::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_graph", "graph"), &RenderGraphPipeline::set_graph);
	ClassDB::bind_method(D_METHOD("get_graph"), &RenderGraphPipeline::get_graph);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "graph", PROPERTY_HINT_RESOURCE_TYPE, "RenderGraph"), "set_graph", "get_graph");
}
