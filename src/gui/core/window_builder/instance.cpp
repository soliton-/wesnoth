/*
	Copyright (C) 2012 - 2025
	by Mark de Wever <koraq@xs4all.nl>
	Part of the Battle for Wesnoth Project https://www.wesnoth.org/

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY.

	See the COPYING file for more details.
*/

#define GETTEXT_DOMAIN "wesnoth-lib"

#include "gui/core/window_builder/instance.hpp"

#include "gui/widgets/spacer.hpp"

namespace gui2
{

namespace implementation
{

builder_instance::builder_instance(const config& cfg)
	: builder_widget(cfg), configuration(cfg)
{
}

std::unique_ptr<widget> builder_instance::build() const
{
	return build(replacements_map());
}

std::unique_ptr<widget> builder_instance::build(const replacements_map& replacements) const
{
	const replacements_map::const_iterator itor = replacements.find(id);
	if(itor != replacements.end()) {
		return itor->second->build();
	} else {
		implementation::builder_spacer builder(configuration);
		return builder.build();
	}
}

} // namespace implementation

} // namespace gui2
