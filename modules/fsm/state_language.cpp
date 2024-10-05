/**************************************************************************/
/*  state_language.cpp                                                    */
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

#include "state_language.h"

String StateMachineScriptLanguage::get_name() const {
	return "State Machine";
}

void StateMachineScriptLanguage::init() {
}

String StateMachineScriptLanguage::get_type() const {
	return String();
}

String StateMachineScriptLanguage::get_extension() const {
	return "fsm";
}

void StateMachineScriptLanguage::finish() {
}

void StateMachineScriptLanguage::get_reserved_words(List<String> *p_words) const {
}

bool StateMachineScriptLanguage::is_control_flow_keyword(const String &p_string) const {
	return false;
}

void StateMachineScriptLanguage::get_comment_delimiters(List<String> *p_delimiters) const {
}

void StateMachineScriptLanguage::get_doc_comment_delimiters(List<String> *p_delimiters) const {
}

void StateMachineScriptLanguage::get_string_delimiters(List<String> *p_delimiters) const {
}

bool StateMachineScriptLanguage::validate(const String &p_script, const String &p_path, List<String> *r_functions, List<ScriptLanguage::ScriptError> *r_errors, List<ScriptLanguage::Warning> *r_warnings, HashSet<int> *r_safe_lines) const {
	return false;
}

Script *StateMachineScriptLanguage::create_script() const {
	return nullptr;
}

bool StateMachineScriptLanguage::has_named_classes() const {
	return false;
}

bool StateMachineScriptLanguage::supports_builtin_mode() const {
	return false;
}

int StateMachineScriptLanguage::find_function(const String &p_function, const String &p_code) const {
	return 0;
}

String StateMachineScriptLanguage::make_function(const String &p_class, const String &p_name, const PackedStringArray &p_args) const {
	return String();
}

void StateMachineScriptLanguage::auto_indent_code(String &p_code, int p_from_line, int p_to_line) const {
}

void StateMachineScriptLanguage::add_global_constant(const StringName &p_variable, const Variant &p_value) {
}

String StateMachineScriptLanguage::debug_get_error() const {
	return String();
}

int StateMachineScriptLanguage::debug_get_stack_level_count() const {
	return 0;
}

int StateMachineScriptLanguage::debug_get_stack_level_line(int p_level) const {
	return 0;
}

String StateMachineScriptLanguage::debug_get_stack_level_function(int p_level) const {
	return String();
}

String StateMachineScriptLanguage::debug_get_stack_level_source(int p_level) const {
	return String();
}

void StateMachineScriptLanguage::debug_get_stack_level_locals(int p_level, List<String> *p_locals, List<Variant> *p_values, int p_max_subitems, int p_max_depth) {
}

void StateMachineScriptLanguage::debug_get_stack_level_members(int p_level, List<String> *p_members, List<Variant> *p_values, int p_max_subitems, int p_max_depth) {
}

void StateMachineScriptLanguage::debug_get_globals(List<String> *p_globals, List<Variant> *p_values, int p_max_subitems, int p_max_depth) {
}

String StateMachineScriptLanguage::debug_parse_stack_level_expression(int p_level, const String &p_expression, int p_max_subitems, int p_max_depth) {
	return String();
}

void StateMachineScriptLanguage::reload_all_scripts() {
}

void StateMachineScriptLanguage::reload_scripts(const Array &p_scripts, bool p_soft_reload) {
}

void StateMachineScriptLanguage::reload_tool_script(const Ref<Script> &p_script, bool p_soft_reload) {
}

void StateMachineScriptLanguage::get_recognized_extensions(List<String> *p_extensions) const {
}

void StateMachineScriptLanguage::get_public_functions(List<MethodInfo> *p_functions) const {
}

void StateMachineScriptLanguage::get_public_constants(List<Pair<String, Variant>> *p_constants) const {
}

void StateMachineScriptLanguage::get_public_annotations(List<MethodInfo> *p_annotations) const {
}

void StateMachineScriptLanguage::profiling_start() {
}

void StateMachineScriptLanguage::profiling_stop() {
}

void StateMachineScriptLanguage::profiling_set_save_native_calls(bool p_enable) {
}

int StateMachineScriptLanguage::profiling_get_accumulated_data(ScriptLanguage::ProfilingInfo *p_info_arr, int p_info_max) {
	return 0;
}

int StateMachineScriptLanguage::profiling_get_frame_data(ScriptLanguage::ProfilingInfo *p_info_arr, int p_info_max) {
	return 0;
}
