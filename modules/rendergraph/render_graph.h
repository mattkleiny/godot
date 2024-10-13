/**************************************************************************/
/*  render_graph.h                                                        */
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

#ifndef RENDER_GRAPH_H
#define RENDER_GRAPH_H

#include "core/io/resource.h"
#include "core/object/object.h"

#include "servers/rendering/renderer_pipeline.h"

// A single node in the render graph.
class RenderGraphNode : public Resource {
	GDCLASS(RenderGraphNode, Resource);

	bool is_root_node;

protected:
	static void _bind_methods();

public:
	bool is_root() const { return is_root_node; }
	void set_root(bool p_root) { is_root_node = p_root; }

	virtual void render_viewport(RID p_viewport);
};

// A graph that can be used to define a rendering pipeline
class RenderGraph : public Resource {
	GDCLASS(RenderGraph, Resource);

	List<Ref<RenderGraphNode>> nodes;

protected:
	static void _bind_methods();

public:
	int get_node_count() const;
	void add_node(const Ref<RenderGraphNode> &p_node);
	void remove_node(const Ref<RenderGraphNode> &p_node);
	Ref<RenderGraphNode> get_root_node() const;

	virtual void render_viewport(RID p_viewport);
};

// A render pipeline backed by a render graph resource.
class RenderGraphPipeline : public RenderPipeline {
	GDCLASS(RenderGraphPipeline, RenderPipeline);

	Ref<RenderGraph> graph;

protected:
	static void _bind_methods();

public:
	void set_graph(const Ref<RenderGraph> &p_graph);
	Ref<RenderGraph> get_graph() const;

	virtual void render_viewport(RID p_viewport) override;
};

#endif // RENDER_GRAPH_H
