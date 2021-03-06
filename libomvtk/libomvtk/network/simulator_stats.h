// vim:et:st=4:ts=4:sts=4:
// Copyright (c) 2008,2009 by the OpenMetaverse Toolkit Library Team
// All rights reserved.
//
// - Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// - Neither the name of the OpenMetaverse Toolkit Library Team nor the names
//   of its contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE
#ifndef GUARD_LIBOMVTK_NETWORK_SIMULATOR_STATS_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_SIMULATOR_STATS_H_INCLUDED

#include "../types/base_types.h"

namespace omvtk
{
	struct SimulatorStats
	{
		UInt64 SentPackets;
		UInt64 RecvPackets;
		UInt64 SentBytes;
		UInt64 RecvBytes;
		Int32 ConnectTime;
		Int32 ResentPackets;
		Int32 ReceivedResends;
		Int32 SentPings;
		Int32 ReceivedPongs;
		Int32 IncomingBPS;
		Int32 OutgoingBPS;
		Int32 LastPingSent;
		UInt8 LastPingID;
		Int32 LastLag;
		Int32 MissedPings;
        Real32 Dilation;
		Int32 FPS;
		Real32 PhysicsFPS;
		Real32 AgentUpdates;
		Real32 FrameTime;
		Real32 NetTime;
		Real32 PhysicsTime;
		Real32 ImageTime;
		Real32 ScriptTime;
		Real32 AgentTime;
		Real32 OtherTime;
		Int32 Objects;
		Int32 ScriptedObjects;
		Int32 Agents;
		Int32 ChildAgents;
		Int32 ActiveScripts;
		Int32 LSLIPS;
		Int32 INPPS;
		Int32 OUTPPS;
		Int32 PendingDownloads;
		Int32 PendingUploads;
		Int32 VirtualSize;
		Int32 ResidentSize;
		Int32 PendingLocalUploads;
		Int32 UnackedBytes;
	};
}

#endif // GUARD_LIBOMVTK_NETWORK_SIMULATOR_STATS_H_INCLUDED

