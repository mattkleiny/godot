/**************************************************************************/
/*  rendering_pipeline.h                                                  */
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

class RenderingDeviceRD;

// A queue capable of storing rendering commands.
class RenderingCommandQueue : public Object {
	GDCLASS(RenderingCommandQueue, Object);

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

		static CullingSettings DEFAULT = { CULLING_FLAGS_NONE, {}, false };
	};

	struct RenderSettings {
		RID override_material;
	}

	struct Command {
		enum {
			COMMAND_CLEAR_COLOR_BUFFER,
			COMMAND_CLEAR_DEPTH_BUFFER,
			COMMAND_CLEAR_STENCIL_BUFFER,
			COMMAND_DRAW_MESH,
			COMMAND_DRAW_MULTIMESH,
			COMMAND_DRAW_SPRITE,
			COMMAND_DRAW_PARTICLES,
		} 
		type;

		union {
			struct { Color color; } clear_color_op;
			struct { float depth; } clear_depth_op;
			struct { uint32_t stencil; } clear_stencil_op;
			struct { RID instance; RID override_material; } draw_op;
		}
	};

	RenderingDeviceRD* device;
	List<Command> commands;

protected:
	static void _bind_methods();

public:
	// standard rendering commands
	void clear_color_buffer(const Color &p_color);
	void clear_depth_buffer(float p_depth);
	void clear_stencil_buffer(uint32_t p_stencil);
	
	void draw_mesh(const Ref<Mesh> &p_mesh, const Ref<Material> &p_override_material);
	void draw_multimesh(const Ref<MultiMesh> &p_multimesh, const Ref<Material> &p_override_material);
	
	void set_render_target(const Ref<RenderTarget> &p_render_target);
	void set_default_render_target();

	// delegation operations, with customizations for overrides
	void draw_canvas_items(CullingFlags p_flags = CULLING_EVERYTHING, const Ref<Material> &p_override_material);
	void draw_canvas_items_ex(CullingSettings p_culling_settings, RenderSettings p_render_settings);
	void draw_spatial_items(CullingFlags p_flags = CULLING_EVERYTHING, const Ref<Material> &p_override_material);
	void draw_spatial_items_ex(CullingSettings p_culling_settings, RenderSettings p_render_settings);
	void draw_fullscreen_quad(const Ref<Material> &p_material);

	// general operations
	void reset();
	void flush();

	RenderingQueue(RenderingDeviceRD* p_device);
}


// A configurable rendering pipeline.
//
// This pipeline is used to define the stages of the renderer using Script or GDExtension.
// The pipeline only works with the RenderingDeviceRD architecture via the RenderingQueue interface.
class RenderingPipeline : public Resource {
	GDCLASS(RenderingPipeline, Resource);

protected:
	static void _bind_methods();

public:
	virtual void render_viewport(RID p_viewport, RenderingCommandQueue& p_queue);
};

// A rendering method that employs a rendering pipeline.
class RenderingPipelineMethod : public RenderingMethod {
	Ref<RenderingPipeline> pipeline;
	HashMap<RID, Ref<RenderingQueue>> queues;

public:
	virtual void render_viewport(const Ref<RenderSceneBuffers> &p_render_buffers, RID p_camera, RID p_scenario, RID p_viewport, Size2 p_viewport_size, uint32_t p_jitter_phase_count, float p_mesh_lod_threshold, RID p_shadow_atlas, Ref<XRInterface> &p_xr_interface, RenderInfo *r_render_info = nullptr) override;

	RenderingPipelineMethod(Ref<RenderingPipeline>& p_pipeline);
};

#endif // RENDERING_PIPELINE_H
