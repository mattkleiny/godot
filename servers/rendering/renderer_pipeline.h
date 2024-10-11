/**************************************************************************/
/*  renderer_pipeline.h                                                   */
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

#ifndef RENDERING_PIPELINE_H
#define RENDERING_PIPELINE_H

#include "core/io/resource.h"

class RenderingDevice;
class Viewport;

// A context for executing render operations.
class RenderContext : public Object {
	GDCLASS(RenderContext, Object);

	enum CullingFlags {
		CULLING_FLAGS_NONE = 0,
		CULLING_FLAGS_OPAQUE = 1 << 0,
		CULLING_FLAGS_TRANSPARENT = 1 << 1,
		CULLING_FLAGS_CANVAS = 1 << 2,
		CULLING_FLAGS_SPATIAL = 1 << 3,
		CULLING_FLAGS_PARTICLE = 1 << 4
	}

	struct CullingSettings {
		CullingFlags flags;
		Plane[6] frustum;
		bool has_frustum;
	};

	struct RenderSettings {
		RID override_material;
	}

	RenderingDevice* device;

protected:
	static void _bind_methods();

public:
	// standard rendering commands
	void set_render_target(const RID p_render_target);
	void set_default_render_target();

	void clear_color_buffer(const Color &p_color);
	void clear_depth_buffer(float p_depth);
	void clear_stencil_buffer(uint32_t p_stencil);

	void draw_canvas_item(const RID p_canvas_item, const RID p_override_material);	
	void draw_instance(const RID p_instance, const RID &p_override_material);
	void draw_mesh(const RID p_mesh, const Ref<Material> &p_override_material);
	void draw_multimesh(const RID p_multimesh, const Ref<Material> &p_override_material);
	void draw_fullscreen_quad(const RID p_material);
	
	void draw_canvas_items(CullingFlags p_flags = CULLING_EVERYTHING, const Ref<Material> &p_override_material);
	void draw_canvas_items_ex(CullingSettings p_culling_settings, RenderSettings p_render_settings);
	void draw_spatial_items(CullingFlags p_flags = CULLING_EVERYTHING, const Ref<Material> &p_override_material);
	void draw_spatial_items_ex(CullingSettings p_culling_settings, RenderSettings p_render_settings);

	RenderContext(RenderingDevice* p_device);
}

// A configurable rendering pipeline.
class RenderPipeline : public Resource {
	GDCLASS(RenderPipeline, Resource);

protected:
	static void _bind_methods();

public:
	virtual void render_viewport(const Viewport& p_viewport) override;
};

// A render pass in a multi-pass rendering pipeline.
class RenderPass : public Resource {
	GDCLASS(RenderPass, Resource);

protected:
	static void _bind_methods();

public:
	virtual bool is_enabled() const { return true; }
	
	virtual void begin_viewport(RID p_viewport, RenderContext& p_context) {}
	virtual void render_viewport(RID p_viewport, RenderContext& p_context) {}
	virtual void end_viewport(RID p_viewport, RenderContext& p_context) {}
};

// A rendering pipeline with support for multiple passes per viewport.
//
// This is useful for rendering techniques that require multiple passes, such as deferred rendering.
class MultiPassRenderPipeline : public RenderPipeline {
	GDCLASS(MultiPassRenderPipeline, RenderPipeline);

	List<Ref<RenderPass>> passes;

protected:
	static void _bind_methods();

public:
	int get_pass_count() const;
	Ref<RenderPass> get_pass(int p_index);
	void add_pass(const Ref<RenderPass> &p_pass);
	void remove_pass(int p_index);

	virtual void render_viewport(Viewport* p_viewport) override;
};

#endif // RENDERING_PIPELINE_H
