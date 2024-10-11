/**************************************************************************/
/*  renderer_pipeline.cpp                                                 */
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

// RenderContext

void RenderContext::clear_color_buffer(const Color &p_color) {
}

void RenderContext::clear_depth_buffer(float p_depth) {
}

void RenderContext::clear_stencil_buffer(uint32_t p_stencil) {
}

void RenderContext::draw_mesh(const Ref<Mesh> &p_mesh, const Ref<Material> &p_override_material) {
}

void RenderContext::draw_multimesh(const Ref<MultiMesh> &p_multimesh, const Ref<Material> &p_override_material) {
}

void RenderContext::draw_canvas_items(RenderContext::CullingFlags p_flags, const Ref<Material> &p_override_material) {
  CullingSettings culling_settings;

  culling_settings.flags = p_flags;
  culling_settings.has_frustum = false;

  RenderSettings render_settings;

  render_settings.override_material = p_override_material;

  draw_canvas_items_ex(culling_settings, render_settings);
}

void RenderContext::draw_canvas_items_ex(RenderContext::CullingSettings p_culling_settings, RenderContext::RenderSettings p_render_settings) {
  // TODO: implement me
}

void RenderContext::draw_spatial_items(RenderContext::CullingFlags p_flags, const Ref<Material> &p_override_material) {
  CullingSettings culling_settings;

  culling_settings.flags = p_flags;
  culling_settings.has_frustum = false;

  RenderSettings render_settings;

  render_settings.override_material = p_override_material;

  draw_spatial_items_ex(culling_settings, render_settings);
}

void RenderContext::draw_spatial_items_ex(RenderContext::CullingSettings p_culling_settings, RenderContext::RenderSettings p_render_settings) {
  // TODO: implement me
}

void RenderContext::draw_fullscreen_quad(const Ref<Material> &p_material) {
  // TODO: implement me
}

void RenderContext::set_render_target(const Ref<RenderTarget> &p_render_target) {
  // TODO: implement me
}

void RenderContext::set_default_render_target() {
  // TODO: implement me
}

void RenderContext::_bind_methods() {
  ClassDB::bind_method(D_METHOD("set_render_target", "render_target"), &RenderContext::set_render_target);
  ClassDB::bind_method(D_METHOD("set_default_render_target"), &RenderContext::set_default_render_target);

  ClassDB::bind_method(D_METHOD("clear_color_buffer", "color"), &RenderContext::clear_color_buffer);
  ClassDB::bind_method(D_METHOD("clear_depth_buffer", "depth"), &RenderContext::clear_depth_buffer);
  ClassDB::bind_method(D_METHOD("clear_stencil_buffer", "stencil"), &RenderContext::clear_stencil_buffer);

  ClassDB::bind_method(D_METHOD("draw_canvas_item", "canvas_item", "override_material"), &RenderContext::draw_canvas_item);
  ClassDB::bind_method(D_METHOD("draw_instance", "instance", "override_material"), &RenderContext::draw_instance);
  ClassDB::bind_method(D_METHOD("draw_mesh", "mesh", "override_material"), &RenderContext::draw_mesh);
  ClassDB::bind_method(D_METHOD("draw_multimesh", "multimesh", "override_material"), &RenderContext::draw_multimesh);
  ClassDB::bind_method(D_METHOD("draw_fullscreen_quad", "material"), &RenderContext::draw_fullscreen_quad);

  ClassDB::bind_method(D_METHOD("draw_canvas_items", "flags", "override_material"), &RenderContext::draw_canvas_items);
  ClassDB::bind_method(D_METHOD("draw_spatial_items", "flags", "override_material"), &RenderContext::draw_spatial_items);
}

RenderContext::RenderContext(RenderingDevice* p_device) {
  device = p_device;
}

// RenderPipeline

void RenderPipeline::render_viewport(RID p_viewport, RenderContext& p_context) {
  // TODO: invoke the script
}

void RenderPipeline::_bind_methods() {
}

// RenderPass

void RenderPass::_bind_methods() {
}

// MultiPassRenderPipeline

int MultiPassRenderPipeline::get_pass_count() const {
  return passes.size();
}

Ref<RenderPass> MultiPassRenderPipeline::get_pass(int p_index) {
  ERR_FAIL_INDEX_V(p_index, passes.size(), Ref<RenderPass>());
  return passes[p_index];
}

void MultiPassRenderPipeline::add_pass(const Ref<RenderPass> &p_pass) {
  passes.push_back(p_pass);
}

void MultiPassRenderPipeline::remove_pass(int p_index) {
  ERR_FAIL_INDEX(p_index, passes.size());
  passes.remove(p_index);
}

void MultiPassRenderPipeline::render_viewport(RID p_viewport, RenderContext& p_context) {
  ERR_FAIL_COND(p_viewport == RID());

  for (int i = 0; i < passes.size(); i++) {
    RenderPass& pass = &passes[i];
    
    if (pass.is_valid() && pass->is_enabled()) {
      pass->begin_viewport(p_viewport, p_context);
    }
  }

  for (int i = 0; i < passes.size(); i++) {
    RenderPass& pass = &passes[i];
    
    if (pass.is_valid() && pass->is_enabled()) {
      pass->render_viewport(p_viewport, p_context);
    }
  }

  for (int i = 0; i < passes.size(); i++) {
    RenderPass& pass = &passes[i];
    
    if (pass.is_valid() && pass->is_enabled()) {
      pass->end_viewport(p_viewport, p_context);
    }
  }
}

void MultiPassRenderPipeline::_bind_methods() {
  ClassDB::bind_method(D_METHOD("get_pass_count"), &MultiPassRenderPipeline::get_pass_count);
  ClassDB::bind_method(D_METHOD("get_pass", "index"), &MultiPassRenderPipeline::get_pass);
  ClassDB::bind_method(D_METHOD("add_pass", "pass"), &MultiPassRenderPipeline::add_pass);
  ClassDB::bind_method(D_METHOD("remove_pass", "index"), &MultiPassRenderPipeline::remove_pass);
}
