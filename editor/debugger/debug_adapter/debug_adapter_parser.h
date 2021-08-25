/*************************************************************************/
/*  debug_adapter_parser.h                                               */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef DEBUG_ADAPTER_PARSER_H
#define DEBUG_ADAPTER_PARSER_H

#include "core/config/project_settings.h"
#include "debug_adapter_protocol.h"
#include "debug_adapter_types.h"

struct DAPeer;
class DebugAdapterProtocol;

class DebugAdapterParser : public Object {
	GDCLASS(DebugAdapterParser, Object);

private:
	friend DebugAdapterProtocol;

	_FORCE_INLINE_ bool is_valid_path(const String &p_path) {
		return p_path.begins_with(ProjectSettings::get_singleton()->get_resource_path());
	}

protected:
	static void _bind_methods();

	Dictionary prepare_base_event() const;
	Dictionary prepare_success_response(const Dictionary &p_params) const;
	Dictionary prepare_error_response(const Dictionary &p_params, DAP::ErrorType err_type, const Dictionary &variables = Dictionary()) const;

	Dictionary ev_stopped() const;

public:
	// Requests
	Dictionary req_initialize(const Dictionary &p_params) const;
	Dictionary req_launch(const Dictionary &p_params);
	Dictionary req_terminate(const Dictionary &p_params) const;
	Dictionary req_pause(const Dictionary &p_params) const;
	Dictionary req_continue(const Dictionary &p_params) const;
	Dictionary req_threads(const Dictionary &p_params) const;
	Dictionary req_stackTrace(const Dictionary &p_params) const;
	Dictionary req_setBreakpoints(const Dictionary &p_params);
	Dictionary req_scopes(const Dictionary &p_params);
	Dictionary req_variables(const Dictionary &p_params) const;
	Dictionary req_next(const Dictionary &p_params) const;
	Dictionary req_stepIn(const Dictionary &p_params) const;

	// Events
	Dictionary ev_initialized() const;
	Dictionary ev_process(const String &p_command) const;
	Dictionary ev_terminated() const;
	Dictionary ev_exited(const int &p_exitcode) const;
	Dictionary ev_stopped_paused() const;
	Dictionary ev_stopped_exception(const String &p_error) const;
	Dictionary ev_stopped_breakpoint(const int &p_id) const;
	Dictionary ev_stopped_step() const;
	Dictionary ev_continued() const;
	Dictionary ev_output(const String &p_message) const;
};

#endif