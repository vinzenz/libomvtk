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

