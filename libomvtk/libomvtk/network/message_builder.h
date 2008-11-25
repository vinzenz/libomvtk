#ifndef GUARD_LIBOMVTK_NETWORK_MESSAGE_BUILDER_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_MESSAGE_BUILDER_H_INCLUDED

#include "../types/base_types.h"

namespace omvtk
{
	struct Simulator;
	struct Network;
	void build_message(Simulator & sim, Network & net, ByteBuffer & buf, UInt32 id);
}

#endif //GUARD_LIBOMVTK_NETWORK_MESSAGE_BUILDER_H_INCLUDED

