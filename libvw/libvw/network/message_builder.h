#ifndef GUARD_LIBVW_NETWORK_MESSAGE_BUILDER_H_INCLUDED
#define GUARD_LIBVW_NETWORK_MESSAGE_BUILDER_H_INCLUDED

#include "../types/base_types.h"

namespace vw
{
	struct Simulator;
	struct Network;
	void build_message(Simulator & sim, Network & net, ByteBuffer & buf, UInt32 id);
}

#endif //GUARD_LIBVW_NETWORK_MESSAGE_BUILDER_H_INCLUDED

