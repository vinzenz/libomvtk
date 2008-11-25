#ifndef GUARD_LIBOMVTK_GRID_CLIENT_H_INCLUDED
#define GUARD_LIBOMVTK_GRID_CLIENT_H_INCLUDED

#include "types/base_types.h"
#include "network/network.h"
#include "settings.h"
#include "library.h"

namespace omvtk
{

	struct GridClient
	{
		GridClient();
		~GridClient();

		Network & network();
		Network const & network() const;
		Settings & settings();		
		Settings const & settings() const;		
		Library & library();
		Library const & library() const;
	protected:
		Library m_library;
		Settings m_settings;
		Network m_network;
	};
}

#endif //GUARD_LIBOMVTK_GRID_CLIENT_H_INCLUDED

