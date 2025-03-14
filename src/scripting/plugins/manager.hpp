/*
	Copyright (C) 2014 - 2025
	by Chris Beck <render787@gmail.com>
	Part of the Battle for Wesnoth Project https://www.wesnoth.org/

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY.

	See the COPYING file for more details.
*/

/**
 * Manages a collection of lua kernels containing plugin modules running
 * as coroutines, running in various engine contexts.
 */

#pragma once

#include "config.hpp"
#include "scripting/plugin_manager_status.hpp"

#include <string>

struct plugin;

class plugins_context;
class lua_kernel_base;
class application_lua_kernel;

class plugins_manager {
public:
	plugins_manager(application_lua_kernel *);
	~plugins_manager();

	static plugins_manager * get();	//this class is a singleton
	lua_kernel_base * get_kernel_base(); // just to mess around with lua console and debug stuff

	void play_slice(const plugins_context &);
	void notify_event(const std::string & name, const config & data);

	std::size_t size();

	plugin_manager_status::type get_status(std::size_t idx);
	std::string get_detailed_status(std::size_t idx);
	std::string get_name (std::size_t idx);

	bool any_running();

	std::size_t load_plugin(const std::string & name, const std::string & filename); 	//throws exceptions in case of failure
	std::size_t add_plugin(const std::string & name, const std::string & prog);		//throws exceptions in case of failure

	void start_plugin(std::size_t idx);							//throws exceptions in case of failure

	struct event {
		std::string name;
		config data;
	};

private:
	// TODO: this used to use boost::ptr_vector. Need to consider if there are some performance implications to not doing so
	std::vector<plugin> plugins_;
	std::shared_ptr<bool> playing_;
	std::unique_ptr<application_lua_kernel> kernel_;
};
