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

// RenderingQueue

void RenderingQueue::clear_color_buffer(const Color &p_color) {
  Command command;

  command.type = COMMAND_CLEAR_COLOR_BUFFER;
  command.clear_color_buffer.color = p_color;

  commands.push_back(command);
}

void RenderingQueue::clear_depth_buffer(float p_depth) {
  Command command;

  command.type = COMMAND_CLEAR_DEPTH_BUFFER;
  command.clear_depth_buffer.depth = p_depth;

  commands.push_back(command);
}

void RenderingQueue::clear_stencil_buffer(uint32_t p_stencil) {
  Command command;

  command.type = COMMAND_CLEAR_STENCIL_BUFFER;
  command.clear_stencil_buffer.stencil = p_stencil;

  commands.push_back(command);
}
void RenderingQueue::draw_mesh(const Ref<Mesh> &p_mesh, const Ref<Material> &p_custom_material) {
  Command command;

  command.type = COMMAND_DRAW_MESH;
  command.draw_mesh.CommandType = p_mesh;
  command.draw_mesh.custom_material = p_custom_material;

  commands.push_back(command);
}

void RenderingQueue::draw_multimesh(const Ref<MultiMesh> &p_multimesh, const Ref<Material> &p_custom_material) {
  Command command;

  command.type = COMMAND_DRAW_MULTIMESH;
  command.draw_multimesh.multimesh = p_multimesh;
  command.draw_multimesh.custom_material = p_custom_material;

  commands.push_back(command);
}

void RenderingQueue::reset() {
  commands.clear();
}

void RenderingQueue::flush() {
  for (int i = 0; i < commands.size(); i++) {
    Command &command = commands[i];

    switch (command.type) {
      case CommandType::COMMAND_CLEAR_COLOR_BUFFER:
        break;
      case CommandType::COMMAND_CLEAR_DEPTH_BUFFER:
        break;
      case CommandType::COMMAND_CLEAR_STENCIL_BUFFER:
        break;
      case CommandType::COMMAND_DRAW_MESH:
        break;
      case CommandType::COMMAND_DRAW_MULTIMESH:
        break;
    }
  }

  reset();
}

void RenderingQueue::_bind_methods() {
  ClassDB::bind_method(D_METHOD("clear_color_buffer", "color"), &RenderingQueue::clear_color_buffer);
  ClassDB::bind_method(D_METHOD("clear_depth_buffer", "depth"), &RenderingQueue::clear_depth_buffer);
  ClassDB::bind_method(D_METHOD("clear_stencil_buffer", "stencil"), &RenderingQueue::clear_stencil_buffer);

  ClassDB::bind_method(D_METHOD("draw_mesh", "mesh", "custom_material"), &RenderingQueue::draw_mesh);
  ClassDB::bind_method(D_METHOD("draw_multimesh", "multimesh", "custom_material"), &RenderingQueue::draw_multimesh);
}

RenderingQueue::RenderingQueue(RenderingDeviceRD* p_device) {
  device = p_device;
}

// RenderingPipeline

void RenderingPipeline::render_camera(const Ref<RenderSceneBuffers> &p_render_buffers, RID p_camera, RID p_scenario, RID p_viewport, Size2 p_viewport_size, uint32_t p_jitter_phase_count, float p_mesh_lod_threshold, RID p_shadow_atlas, Ref<XRInterface> &p_xr_interface, RenderInfo *r_render_info = nullptr) {
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

  // render the camera
  pipeline->render_camera(queue, p_render_buffers, p_camera, p_scenario, p_viewport, p_viewport_size, p_jitter_phase_count, p_mesh_lod_threshold, p_shadow_atlas, p_xr_interface, r_render_info);
}

RenderingPipelineMethod::RenderingPipelineMethod(Ref<RenderingPipeline>& p_pipeline) {
  pipeline = p_pipeline;
}
