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
class RenderingPipelineMethod;

// A queue capable of storing rendering commands.
class RenderingQueue : public Object {
	GDCLASS(RenderingQueue, Object);

	enum CullingFlags {
		CULLING_FLAGS_NONE = 0,
		CULLING_FLAGS_OPAQUE = 1 << 0,
		CULLING_FLAGS_TRANSPARENT = 1 << 1,
		CULLING_FLAGS_CANVAS = 1 << 2,
		CULLING_FLAGS_SPATIAL = 1 << 3,
		CULLING_FLAGS_PARTICLE = 1 << 4,
		CULLING_EVERYTHING = 0xFFFFFFFF
	}

	struct CullingSettings {
		CullingFlags flags;
		Plane[6] frustum;
		bool has_frustum;
	};

	struct Command {
		enum {
			COMMAND_CLEAR_COLOR_BUFFER,
			COMMAND_CLEAR_DEPTH_BUFFER,
			COMMAND_CLEAR_STENCIL_BUFFER,
			COMMAND_DRAW_MESH,
			COMMAND_DRAW_MULTIMESH,
		} type;

		union {
			struct {
				Color color;
			}
			clear_color_buffer;
			
			struct {
				float depth;
			}
			clear_depth_buffer;
			
			struct {
				uint32_t stencil;
			}
			clear_stencil_buffer;
			
			struct {
				RID mesh;
				RID custom_material;
			}
			draw_mesh;
			
			struct {
				RID multimesh;
				RID custom_material;
			}
			draw_multimesh;
		}
	};

	RenderingDeviceRD* device;
	List<Command> commands;

protected:
	static void _bind_methods();

public:
	void clear_color_buffer(const Color &p_color);
	void clear_depth_buffer(float p_depth);
	void clear_stencil_buffer(uint32_t p_stencil);

	void draw_mesh(const RID &p_mesh, const RID p_custom_material = RID());
	void draw_multimesh(const RID &p_multimesh, const RID p_custom_material = RID());

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

	friend class RenderingPipelineMethod;

protected:
	static void _bind_methods();

public:
	virtual void render_camera(const Ref<RenderSceneBuffers> &p_render_buffers, RID p_camera, RID p_scenario, RID p_viewport, Size2 p_viewport_size, uint32_t p_jitter_phase_count, float p_mesh_lod_threshold, RID p_shadow_atlas, Ref<XRInterface> &p_xr_interface, RenderInfo *r_render_info = nullptr);
};

// A rendering method that employs a rendering pipeline.
class RenderingPipelineMethod : public RenderingMethod {
	Ref<RenderingPipeline> pipeline;
	HashMap<RID, Ref<RenderingQueue>> queues;

public:
	virtual void render_camera(const Ref<RenderSceneBuffers> &p_render_buffers, RID p_camera, RID p_scenario, RID p_viewport, Size2 p_viewport_size, uint32_t p_jitter_phase_count, float p_mesh_lod_threshold, RID p_shadow_atlas, Ref<XRInterface> &p_xr_interface, RenderInfo *r_render_info = nullptr) override;

	RenderingPipelineMethod(Ref<RenderingPipeline>& p_pipeline);
};

#endif // RENDERING_PIPELINE_H
