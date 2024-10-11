/**************************************************************************/
/*  rendering_pipeline.cpp                                                */
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

#include "rendering_pipeline.h"

// RenderingCommandQueue

void RenderingCommandQueue::clear_color_buffer(const Color &p_color) {
  Command command;

  command.type = COMMAND_CLEAR_COLOR_BUFFER;
  command.clear_color_op.color = p_color;

  commands.push_back(command);
}

void RenderingCommandQueue::clear_depth_buffer(float p_depth) {
  Command command;

  command.type = Command::COMMAND_CLEAR_DEPTH_BUFFER;
  command.clear_depth_op.depth = p_depth;

  commands.push_back(command);
}

void RenderingCommandQueue::clear_stencil_buffer(uint32_t p_stencil) {
  Command command;

  command.type = Command::COMMAND_CLEAR_STENCIL_BUFFER;
  command.clear_stencil_op.stencil = p_stencil;

  commands.push_back(command);
}

void RenderingCommandQueue::draw_mesh(const Ref<Mesh> &p_mesh, const Ref<Material> &p_override_material) {
  Command command;

  command.type = Command::COMMAND_DRAW_MESH;
  command.draw_mesh.instance = p_mesh;
  command.draw_mesh.override_material = p_override_material;

  commands.push_back(command);
}

void RenderingCommandQueue::draw_multimesh(const Ref<MultiMesh> &p_multimesh, const Ref<Material> &p_override_material) {
  Command command;

  command.type = Command::COMMAND_DRAW_MULTIMESH;
  command.draw_op.instance = p_multimesh;
  command.draw_op.override_material = p_override_material;

  commands.push_back(command);
}

void RenderingCommandQueue::draw_canvas_items(RenderingCommandQueue::CullingFlags p_flags, const Ref<Material> &p_override_material) {
  // TODO: implement me
}

void RenderingCommandQueue::draw_canvas_items_ex(RenderingCommandQueue::CullingSettings p_culling_settings, RenderingCommandQueue::RenderSettings p_render_settings) {
  // TODO: implement me
}

void RenderingCommandQueue::draw_spatial_items(RenderingCommandQueue::CullingFlags p_flags, const Ref<Material> &p_override_material) {
  // TODO: implement me
}

void RenderingCommandQueue::draw_spatial_items_ex(RenderingCommandQueue::CullingSettings p_culling_settings, RenderingCommandQueue::RenderSettings p_render_settings) {
  // TODO: implement me
}

void RenderingCommandQueue::draw_fullscreen_quad(const Ref<Material> &p_material) {
  // TODO: implement me
}

void RenderingCommandQueue::set_render_target(const Ref<RenderTarget> &p_render_target) {
  // TODO: implement me
}

void RenderingCommandQueue::set_default_render_target() {
  // TODO: implement me
}

void RenderingCommandQueue::reset() {
  commands.clear();
}

void RenderingCommandQueue::flush() {
  for (int i = 0; i < commands.size(); i++) {
    Command &command = commands[i];

    switch (command.type) {
      case Command::COMMAND_CLEAR_COLOR_BUFFER:
        break;
      case Command::COMMAND_CLEAR_DEPTH_BUFFER:
        break;
      case Command::COMMAND_CLEAR_STENCIL_BUFFER:
        break;
      case Command::COMMAND_DRAW_MESH:
        break;
      case Command::COMMAND_DRAW_MULTIMESH:
        break;
    }
  }

  reset();
}

void RenderingCommandQueue::_bind_methods() {
  ClassDB::bind_method(D_METHOD("clear_color_buffer", "color"), &RenderingCommandQueue::clear_color_buffer);
  ClassDB::bind_method(D_METHOD("clear_depth_buffer", "depth"), &RenderingCommandQueue::clear_depth_buffer);
  ClassDB::bind_method(D_METHOD("clear_stencil_buffer", "stencil"), &RenderingCommandQueue::clear_stencil_buffer);

  ClassDB::bind_method(D_METHOD("draw_mesh", "mesh", "override_material"), &RenderingCommandQueue::draw_mesh);
  ClassDB::bind_method(D_METHOD("draw_multimesh", "multimesh", "override_material"), &RenderingCommandQueue::draw_multimesh);
  ClassDB::bind_method(D_METHOD("draw_sprite", "sprite", "override_material"), &RenderingCommandQueue::draw_multimesh);
  ClassDB::bind_method(D_METHOD("draw_particles", "particesl", "override_material"), &RenderingCommandQueue::draw_multimesh);

  ClassDB::bind_method(D_METHOD("flush"), &RenderingCommandQueue::flush);
  ClassDB::bind_method(D_METHOD("reset"), &RenderingCommandQueue::reset);
}

RenderingCommandQueue::RenderingCommandQueue(RenderingDeviceRD* p_device) {
  device = p_device;
}

// RenderingPipeline
void RenderingPipeline::render_viewport(RID p_viewport, RenderingCommandQueue& p_queue) {
  // TODO: invoke the script
}

void RenderingPipeline::_bind_methods() {
}

// RenderingPipelineMethod

void RenderingPipelineMethod::render_camera(const Ref<RenderSceneBuffers> &p_render_buffers, RID p_camera, RID p_scenario, RID p_viewport, Size2 p_viewport_size, uint32_t p_jitter_phase_count, float p_mesh_lod_threshold, RID p_shadow_atlas, Ref<XRInterface> &p_xr_interface, RenderInfo *r_render_info = nullptr) {
  // no pipeline, no rendering
  if (!pipeline.is_valid()) {
    return;
  }

  // create a queue per camera
  if (!queues.has(p_camera)) {
    queues[p_camera] = RenderingQueue(pipeline->device);
  }
  RenderingQueue &queue = queues[p_camera];
  queue->clear();

  // TODO: render the camera
}

RenderingPipelineMethod::RenderingPipelineMethod(Ref<RenderingPipeline>& p_pipeline) {
  pipeline = p_pipeline;
}
