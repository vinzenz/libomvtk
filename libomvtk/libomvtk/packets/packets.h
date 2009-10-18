#ifndef GUARD_LIBOMVTK_PACKETS_PACKETS_H_INCLUDED
#define GUARD_LIBOMVTK_PACKETS_PACKETS_H_INCLUDED


#if _MSC_VER > 1200
#    pragma once
#endif

#include "processors.h"
#include "../network/network.h"
namespace omvtk
{
    namespace packets
    {
        struct PacketInitializer {
        omvtk::Network & n_; omvtk::Simulator & s_; omvtk::ByteBuffer & b_;
            PacketInitializer(omvtk::Network & net, omvtk::Simulator & sim, omvtk::ByteBuffer & buf)
            : n_(net), s_(sim), b_(buf)
            {}

            template<typename T>
            void init() {
                std::size_t p = 0;
                T m(b_, p);
                if ( p == b_.size() ) {
                    n_.messages_manager()(m, s_);
                }
            }
        };
        struct TestMessageMessage
            : Message
        {
            static char const * name(){ return "TestMessage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0001ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TestMessageMessage>();
                }
            };


            TestMessageMessage()
            : Message(LowHeader())
            , TestBlock1()
            , NeighborBlock()
            {}

            TestMessageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , TestBlock1()
            , NeighborBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct TestBlock1Block
            {
                UInt32 Test1;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Test1,"Test1");
                }

            };

            struct NeighborBlockBlock
            {
                UInt32 Test0;
                UInt32 Test1;
                UInt32 Test2;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Test0,"Test0");
                    p.process(Test1,"Test1");
                    p.process(Test2,"Test2");
                }

            };


            TestBlock1Block TestBlock1;
            boost::array<NeighborBlockBlock,4> NeighborBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(TestBlock1,"TestBlock1");
                p.process(NeighborBlock,"NeighborBlock");
            }

        };

        struct UseCircuitCodeMessage
            : Message
        {
            static char const * name(){ return "UseCircuitCode"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0003ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UseCircuitCodeMessage>();
                }
            };


            UseCircuitCodeMessage()
            : Message(LowHeader())
            , CircuitCode()
            {}

            UseCircuitCodeMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , CircuitCode()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct CircuitCodeBlock
            {
                UInt32 Code;
                LLUUID SessionID;
                LLUUID ID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Code,"Code");
                    p.process(SessionID,"SessionID");
                    p.process(ID,"ID");
                }

            };


            CircuitCodeBlock CircuitCode;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(CircuitCode,"CircuitCode");
            }

        };

        struct TelehubInfoMessage
            : Message
        {
            static char const * name(){ return "TelehubInfo"; }
            static bool const trusted = false;
            enum { id = 0xFFFF000Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TelehubInfoMessage>();
                }
            };


            TelehubInfoMessage()
            : Message(LowHeader())
            , TelehubBlock()
            , SpawnPointBlock()
            {}

            TelehubInfoMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , TelehubBlock()
            , SpawnPointBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct TelehubBlockBlock
            {
                LLUUID ObjectID;
                raw::LLVariable ObjectName;
                raw::LLVector3 TelehubPos;
                raw::LLQuaternion TelehubRot;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(ObjectName,"ObjectName");
                    p.process(TelehubPos,"TelehubPos");
                    p.process(TelehubRot,"TelehubRot");
                }

            };

            struct SpawnPointBlockBlock
            {
                raw::LLVector3 SpawnPointPos;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SpawnPointPos,"SpawnPointPos");
                }

            };


            TelehubBlockBlock TelehubBlock;
            std::vector<SpawnPointBlockBlock> SpawnPointBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(TelehubBlock,"TelehubBlock");
                p.process(SpawnPointBlock,"SpawnPointBlock");
            }

        };

        struct EconomyDataRequestMessage
            : Message
        {
            static char const * name(){ return "EconomyDataRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0018ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EconomyDataRequestMessage>();
                }
            };


            EconomyDataRequestMessage()
            : Message(LowHeader())
            {}

            EconomyDataRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            



            template<typename Processor>
            void process(Processor & p)
            {
                (void)p; // avoiding unreferenced warnings
            }

        };

        struct EconomyDataMessage
            : Message
        {
            static char const * name(){ return "EconomyData"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0019ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EconomyDataMessage>();
                }
            };


            EconomyDataMessage()
            : Message(LowHeader())
            , Info()
            {}

            EconomyDataMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Info()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct InfoBlock
            {
                Int32 ObjectCapacity;
                Int32 ObjectCount;
                Int32 PriceEnergyUnit;
                Int32 PriceObjectClaim;
                Int32 PricePublicObjectDecay;
                Int32 PricePublicObjectDelete;
                Int32 PriceParcelClaim;
                Real32 PriceParcelClaimFactor;
                Int32 PriceUpload;
                Int32 PriceRentLight;
                Int32 TeleportMinPrice;
                Real32 TeleportPriceExponent;
                Real32 EnergyEfficiency;
                Real32 PriceObjectRent;
                Real32 PriceObjectScaleFactor;
                Int32 PriceParcelRent;
                Int32 PriceGroupCreate;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectCapacity,"ObjectCapacity");
                    p.process(ObjectCount,"ObjectCount");
                    p.process(PriceEnergyUnit,"PriceEnergyUnit");
                    p.process(PriceObjectClaim,"PriceObjectClaim");
                    p.process(PricePublicObjectDecay,"PricePublicObjectDecay");
                    p.process(PricePublicObjectDelete,"PricePublicObjectDelete");
                    p.process(PriceParcelClaim,"PriceParcelClaim");
                    p.process(PriceParcelClaimFactor,"PriceParcelClaimFactor");
                    p.process(PriceUpload,"PriceUpload");
                    p.process(PriceRentLight,"PriceRentLight");
                    p.process(TeleportMinPrice,"TeleportMinPrice");
                    p.process(TeleportPriceExponent,"TeleportPriceExponent");
                    p.process(EnergyEfficiency,"EnergyEfficiency");
                    p.process(PriceObjectRent,"PriceObjectRent");
                    p.process(PriceObjectScaleFactor,"PriceObjectScaleFactor");
                    p.process(PriceParcelRent,"PriceParcelRent");
                    p.process(PriceGroupCreate,"PriceGroupCreate");
                }

            };


            InfoBlock Info;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Info,"Info");
            }

        };

        struct AvatarPickerRequestMessage
            : Message
        {
            static char const * name(){ return "AvatarPickerRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF001Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarPickerRequestMessage>();
                }
            };


            AvatarPickerRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            AvatarPickerRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(QueryID,"QueryID");
                }

            };

            struct DataBlock
            {
                raw::LLVariable Name;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Name,"Name");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct AvatarPickerReplyMessage
            : Message
        {
            static char const * name(){ return "AvatarPickerReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF001Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarPickerReplyMessage>();
                }
            };


            AvatarPickerReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            AvatarPickerReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(QueryID,"QueryID");
                }

            };

            struct DataBlock
            {
                LLUUID AvatarID;
                raw::LLVariable FirstName;
                raw::LLVariable LastName;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AvatarID,"AvatarID");
                    p.process(FirstName,"FirstName");
                    p.process(LastName,"LastName");
                }

            };


            AgentDataBlock AgentData;
            std::vector<DataBlock> Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct PlacesQueryMessage
            : Message
        {
            static char const * name(){ return "PlacesQuery"; }
            static bool const trusted = false;
            enum { id = 0xFFFF001Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<PlacesQueryMessage>();
                }
            };


            PlacesQueryMessage()
            : Message(LowHeader())
            , AgentData()
            , TransactionData()
            , QueryData()
            {}

            PlacesQueryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , TransactionData()
            , QueryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(QueryID,"QueryID");
                }

            };

            struct TransactionDataBlock
            {
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                }

            };

            struct QueryDataBlock
            {
                raw::LLVariable QueryText;
                UInt32 QueryFlags;
                Int8 Category;
                raw::LLVariable SimName;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryText,"QueryText");
                    p.process(QueryFlags,"QueryFlags");
                    p.process(Category,"Category");
                    p.process(SimName,"SimName");
                }

            };


            AgentDataBlock AgentData;
            TransactionDataBlock TransactionData;
            QueryDataBlock QueryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(TransactionData,"TransactionData");
                p.process(QueryData,"QueryData");
            }

        };

        struct PlacesReplyMessage
            : Message
        {
            static char const * name(){ return "PlacesReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF001Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<PlacesReplyMessage>();
                }
            };


            PlacesReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , TransactionData()
            , QueryData()
            {}

            PlacesReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , TransactionData()
            , QueryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(QueryID,"QueryID");
                }

            };

            struct TransactionDataBlock
            {
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID OwnerID;
                raw::LLVariable Name;
                raw::LLVariable Desc;
                Int32 ActualArea;
                Int32 BillableArea;
                UInt8 Flags;
                Real32 GlobalX;
                Real32 GlobalY;
                Real32 GlobalZ;
                raw::LLVariable SimName;
                LLUUID SnapshotID;
                Real32 Dwell;
                Int32 Price;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(OwnerID,"OwnerID");
                    p.process(Name,"Name");
                    p.process(Desc,"Desc");
                    p.process(ActualArea,"ActualArea");
                    p.process(BillableArea,"BillableArea");
                    p.process(Flags,"Flags");
                    p.process(GlobalX,"GlobalX");
                    p.process(GlobalY,"GlobalY");
                    p.process(GlobalZ,"GlobalZ");
                    p.process(SimName,"SimName");
                    p.process(SnapshotID,"SnapshotID");
                    p.process(Dwell,"Dwell");
                    p.process(Price,"Price");
                }

            };


            AgentDataBlock AgentData;
            TransactionDataBlock TransactionData;
            std::vector<QueryDataBlock> QueryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(TransactionData,"TransactionData");
                p.process(QueryData,"QueryData");
            }

        };

        struct DirFindQueryMessage
            : Message
        {
            static char const * name(){ return "DirFindQuery"; }
            static bool const trusted = false;
            enum { id = 0xFFFF001Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DirFindQueryMessage>();
                }
            };


            DirFindQueryMessage()
            : Message(LowHeader())
            , AgentData()
            , QueryData()
            {}

            DirFindQueryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , QueryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;
                raw::LLVariable QueryText;
                UInt32 QueryFlags;
                Int32 QueryStart;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                    p.process(QueryText,"QueryText");
                    p.process(QueryFlags,"QueryFlags");
                    p.process(QueryStart,"QueryStart");
                }

            };


            AgentDataBlock AgentData;
            QueryDataBlock QueryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(QueryData,"QueryData");
            }

        };

        struct DirPlacesQueryMessage
            : Message
        {
            static char const * name(){ return "DirPlacesQuery"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0021ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DirPlacesQueryMessage>();
                }
            };


            DirPlacesQueryMessage()
            : Message(LowHeader())
            , AgentData()
            , QueryData()
            {}

            DirPlacesQueryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , QueryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;
                raw::LLVariable QueryText;
                UInt32 QueryFlags;
                Int8 Category;
                raw::LLVariable SimName;
                Int32 QueryStart;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                    p.process(QueryText,"QueryText");
                    p.process(QueryFlags,"QueryFlags");
                    p.process(Category,"Category");
                    p.process(SimName,"SimName");
                    p.process(QueryStart,"QueryStart");
                }

            };


            AgentDataBlock AgentData;
            QueryDataBlock QueryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(QueryData,"QueryData");
            }

        };

        struct DirPlacesReplyMessage
            : Message
        {
            static char const * name(){ return "DirPlacesReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0023ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DirPlacesReplyMessage>();
                }
            };


            DirPlacesReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , QueryData()
            , QueryReplies()
            {}

            DirPlacesReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , QueryData()
            , QueryReplies()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                }

            };

            struct QueryRepliesBlock
            {
                LLUUID ParcelID;
                raw::LLVariable Name;
                bool ForSale;
                bool Auction;
                Real32 Dwell;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ParcelID,"ParcelID");
                    p.process(Name,"Name");
                    p.process(ForSale,"ForSale");
                    p.process(Auction,"Auction");
                    p.process(Dwell,"Dwell");
                }

            };


            AgentDataBlock AgentData;
            std::vector<QueryDataBlock> QueryData;
            std::vector<QueryRepliesBlock> QueryReplies;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(QueryData,"QueryData");
                p.process(QueryReplies,"QueryReplies");
            }

        };

        struct DirPeopleReplyMessage
            : Message
        {
            static char const * name(){ return "DirPeopleReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0024ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DirPeopleReplyMessage>();
                }
            };


            DirPeopleReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , QueryData()
            , QueryReplies()
            {}

            DirPeopleReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , QueryData()
            , QueryReplies()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                }

            };

            struct QueryRepliesBlock
            {
                LLUUID AgentID;
                raw::LLVariable FirstName;
                raw::LLVariable LastName;
                raw::LLVariable Group;
                bool Online;
                Int32 Reputation;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(FirstName,"FirstName");
                    p.process(LastName,"LastName");
                    p.process(Group,"Group");
                    p.process(Online,"Online");
                    p.process(Reputation,"Reputation");
                }

            };


            AgentDataBlock AgentData;
            QueryDataBlock QueryData;
            std::vector<QueryRepliesBlock> QueryReplies;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(QueryData,"QueryData");
                p.process(QueryReplies,"QueryReplies");
            }

        };

        struct DirEventsReplyMessage
            : Message
        {
            static char const * name(){ return "DirEventsReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0025ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DirEventsReplyMessage>();
                }
            };


            DirEventsReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , QueryData()
            , QueryReplies()
            {}

            DirEventsReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , QueryData()
            , QueryReplies()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                }

            };

            struct QueryRepliesBlock
            {
                LLUUID OwnerID;
                raw::LLVariable Name;
                UInt32 EventID;
                raw::LLVariable Date;
                UInt32 UnixTime;
                UInt32 EventFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(OwnerID,"OwnerID");
                    p.process(Name,"Name");
                    p.process(EventID,"EventID");
                    p.process(Date,"Date");
                    p.process(UnixTime,"UnixTime");
                    p.process(EventFlags,"EventFlags");
                }

            };


            AgentDataBlock AgentData;
            QueryDataBlock QueryData;
            std::vector<QueryRepliesBlock> QueryReplies;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(QueryData,"QueryData");
                p.process(QueryReplies,"QueryReplies");
            }

        };

        struct DirGroupsReplyMessage
            : Message
        {
            static char const * name(){ return "DirGroupsReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0026ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DirGroupsReplyMessage>();
                }
            };


            DirGroupsReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , QueryData()
            , QueryReplies()
            {}

            DirGroupsReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , QueryData()
            , QueryReplies()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                }

            };

            struct QueryRepliesBlock
            {
                LLUUID GroupID;
                raw::LLVariable GroupName;
                Int32 Members;
                Real32 SearchOrder;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(GroupName,"GroupName");
                    p.process(Members,"Members");
                    p.process(SearchOrder,"SearchOrder");
                }

            };


            AgentDataBlock AgentData;
            QueryDataBlock QueryData;
            std::vector<QueryRepliesBlock> QueryReplies;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(QueryData,"QueryData");
                p.process(QueryReplies,"QueryReplies");
            }

        };

        struct DirClassifiedQueryMessage
            : Message
        {
            static char const * name(){ return "DirClassifiedQuery"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0027ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DirClassifiedQueryMessage>();
                }
            };


            DirClassifiedQueryMessage()
            : Message(LowHeader())
            , AgentData()
            , QueryData()
            {}

            DirClassifiedQueryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , QueryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;
                raw::LLVariable QueryText;
                UInt32 QueryFlags;
                UInt32 Category;
                Int32 QueryStart;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                    p.process(QueryText,"QueryText");
                    p.process(QueryFlags,"QueryFlags");
                    p.process(Category,"Category");
                    p.process(QueryStart,"QueryStart");
                }

            };


            AgentDataBlock AgentData;
            QueryDataBlock QueryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(QueryData,"QueryData");
            }

        };

        struct DirClassifiedReplyMessage
            : Message
        {
            static char const * name(){ return "DirClassifiedReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0029ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DirClassifiedReplyMessage>();
                }
            };


            DirClassifiedReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , QueryData()
            , QueryReplies()
            {}

            DirClassifiedReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , QueryData()
            , QueryReplies()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                }

            };

            struct QueryRepliesBlock
            {
                LLUUID ClassifiedID;
                raw::LLVariable Name;
                UInt8 ClassifiedFlags;
                UInt32 CreationDate;
                UInt32 ExpirationDate;
                Int32 PriceForListing;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ClassifiedID,"ClassifiedID");
                    p.process(Name,"Name");
                    p.process(ClassifiedFlags,"ClassifiedFlags");
                    p.process(CreationDate,"CreationDate");
                    p.process(ExpirationDate,"ExpirationDate");
                    p.process(PriceForListing,"PriceForListing");
                }

            };


            AgentDataBlock AgentData;
            QueryDataBlock QueryData;
            std::vector<QueryRepliesBlock> QueryReplies;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(QueryData,"QueryData");
                p.process(QueryReplies,"QueryReplies");
            }

        };

        struct AvatarClassifiedReplyMessage
            : Message
        {
            static char const * name(){ return "AvatarClassifiedReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF002Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarClassifiedReplyMessage>();
                }
            };


            AvatarClassifiedReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            AvatarClassifiedReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID TargetID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(TargetID,"TargetID");
                }

            };

            struct DataBlock
            {
                LLUUID ClassifiedID;
                raw::LLVariable Name;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ClassifiedID,"ClassifiedID");
                    p.process(Name,"Name");
                }

            };


            AgentDataBlock AgentData;
            std::vector<DataBlock> Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ClassifiedInfoRequestMessage
            : Message
        {
            static char const * name(){ return "ClassifiedInfoRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF002Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ClassifiedInfoRequestMessage>();
                }
            };


            ClassifiedInfoRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ClassifiedInfoRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID ClassifiedID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ClassifiedID,"ClassifiedID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ClassifiedInfoReplyMessage
            : Message
        {
            static char const * name(){ return "ClassifiedInfoReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF002Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ClassifiedInfoReplyMessage>();
                }
            };


            ClassifiedInfoReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ClassifiedInfoReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct DataBlock
            {
                LLUUID ClassifiedID;
                LLUUID CreatorID;
                UInt32 CreationDate;
                UInt32 ExpirationDate;
                UInt32 Category;
                raw::LLVariable Name;
                raw::LLVariable Desc;
                LLUUID ParcelID;
                UInt32 ParentEstate;
                LLUUID SnapshotID;
                raw::LLVariable SimName;
                raw::LLVector3d PosGlobal;
                raw::LLVariable ParcelName;
                UInt8 ClassifiedFlags;
                Int32 PriceForListing;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ClassifiedID,"ClassifiedID");
                    p.process(CreatorID,"CreatorID");
                    p.process(CreationDate,"CreationDate");
                    p.process(ExpirationDate,"ExpirationDate");
                    p.process(Category,"Category");
                    p.process(Name,"Name");
                    p.process(Desc,"Desc");
                    p.process(ParcelID,"ParcelID");
                    p.process(ParentEstate,"ParentEstate");
                    p.process(SnapshotID,"SnapshotID");
                    p.process(SimName,"SimName");
                    p.process(PosGlobal,"PosGlobal");
                    p.process(ParcelName,"ParcelName");
                    p.process(ClassifiedFlags,"ClassifiedFlags");
                    p.process(PriceForListing,"PriceForListing");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ClassifiedInfoUpdateMessage
            : Message
        {
            static char const * name(){ return "ClassifiedInfoUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF002Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ClassifiedInfoUpdateMessage>();
                }
            };


            ClassifiedInfoUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ClassifiedInfoUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID ClassifiedID;
                UInt32 Category;
                raw::LLVariable Name;
                raw::LLVariable Desc;
                LLUUID ParcelID;
                UInt32 ParentEstate;
                LLUUID SnapshotID;
                raw::LLVector3d PosGlobal;
                UInt8 ClassifiedFlags;
                Int32 PriceForListing;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ClassifiedID,"ClassifiedID");
                    p.process(Category,"Category");
                    p.process(Name,"Name");
                    p.process(Desc,"Desc");
                    p.process(ParcelID,"ParcelID");
                    p.process(ParentEstate,"ParentEstate");
                    p.process(SnapshotID,"SnapshotID");
                    p.process(PosGlobal,"PosGlobal");
                    p.process(ClassifiedFlags,"ClassifiedFlags");
                    p.process(PriceForListing,"PriceForListing");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ClassifiedDeleteMessage
            : Message
        {
            static char const * name(){ return "ClassifiedDelete"; }
            static bool const trusted = false;
            enum { id = 0xFFFF002Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ClassifiedDeleteMessage>();
                }
            };


            ClassifiedDeleteMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ClassifiedDeleteMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID ClassifiedID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ClassifiedID,"ClassifiedID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ClassifiedGodDeleteMessage
            : Message
        {
            static char const * name(){ return "ClassifiedGodDelete"; }
            static bool const trusted = false;
            enum { id = 0xFFFF002Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ClassifiedGodDeleteMessage>();
                }
            };


            ClassifiedGodDeleteMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ClassifiedGodDeleteMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID ClassifiedID;
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ClassifiedID,"ClassifiedID");
                    p.process(QueryID,"QueryID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct DirLandQueryMessage
            : Message
        {
            static char const * name(){ return "DirLandQuery"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0030ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DirLandQueryMessage>();
                }
            };


            DirLandQueryMessage()
            : Message(LowHeader())
            , AgentData()
            , QueryData()
            {}

            DirLandQueryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , QueryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;
                UInt32 QueryFlags;
                UInt32 SearchType;
                Int32 Price;
                Int32 Area;
                Int32 QueryStart;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                    p.process(QueryFlags,"QueryFlags");
                    p.process(SearchType,"SearchType");
                    p.process(Price,"Price");
                    p.process(Area,"Area");
                    p.process(QueryStart,"QueryStart");
                }

            };


            AgentDataBlock AgentData;
            QueryDataBlock QueryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(QueryData,"QueryData");
            }

        };

        struct DirLandReplyMessage
            : Message
        {
            static char const * name(){ return "DirLandReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0032ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DirLandReplyMessage>();
                }
            };


            DirLandReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , QueryData()
            , QueryReplies()
            {}

            DirLandReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , QueryData()
            , QueryReplies()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                }

            };

            struct QueryRepliesBlock
            {
                LLUUID ParcelID;
                raw::LLVariable Name;
                bool Auction;
                bool ForSale;
                Int32 SalePrice;
                Int32 ActualArea;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ParcelID,"ParcelID");
                    p.process(Name,"Name");
                    p.process(Auction,"Auction");
                    p.process(ForSale,"ForSale");
                    p.process(SalePrice,"SalePrice");
                    p.process(ActualArea,"ActualArea");
                }

            };


            AgentDataBlock AgentData;
            QueryDataBlock QueryData;
            std::vector<QueryRepliesBlock> QueryReplies;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(QueryData,"QueryData");
                p.process(QueryReplies,"QueryReplies");
            }

        };

        struct DirPopularQueryMessage
            : Message
        {
            static char const * name(){ return "DirPopularQuery"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0033ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DirPopularQueryMessage>();
                }
            };


            DirPopularQueryMessage()
            : Message(LowHeader())
            , AgentData()
            , QueryData()
            {}

            DirPopularQueryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , QueryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;
                UInt32 QueryFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                    p.process(QueryFlags,"QueryFlags");
                }

            };


            AgentDataBlock AgentData;
            QueryDataBlock QueryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(QueryData,"QueryData");
            }

        };

        struct DirPopularReplyMessage
            : Message
        {
            static char const * name(){ return "DirPopularReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0035ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DirPopularReplyMessage>();
                }
            };


            DirPopularReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , QueryData()
            , QueryReplies()
            {}

            DirPopularReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , QueryData()
            , QueryReplies()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                }

            };

            struct QueryRepliesBlock
            {
                LLUUID ParcelID;
                raw::LLVariable Name;
                Real32 Dwell;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ParcelID,"ParcelID");
                    p.process(Name,"Name");
                    p.process(Dwell,"Dwell");
                }

            };


            AgentDataBlock AgentData;
            QueryDataBlock QueryData;
            std::vector<QueryRepliesBlock> QueryReplies;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(QueryData,"QueryData");
                p.process(QueryReplies,"QueryReplies");
            }

        };

        struct ParcelInfoRequestMessage
            : Message
        {
            static char const * name(){ return "ParcelInfoRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0036ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelInfoRequestMessage>();
                }
            };


            ParcelInfoRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ParcelInfoRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID ParcelID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ParcelID,"ParcelID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ParcelInfoReplyMessage
            : Message
        {
            static char const * name(){ return "ParcelInfoReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0037ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelInfoReplyMessage>();
                }
            };


            ParcelInfoReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ParcelInfoReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct DataBlock
            {
                LLUUID ParcelID;
                LLUUID OwnerID;
                raw::LLVariable Name;
                raw::LLVariable Desc;
                Int32 ActualArea;
                Int32 BillableArea;
                UInt8 Flags;
                Real32 GlobalX;
                Real32 GlobalY;
                Real32 GlobalZ;
                raw::LLVariable SimName;
                LLUUID SnapshotID;
                Real32 Dwell;
                Int32 SalePrice;
                Int32 AuctionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ParcelID,"ParcelID");
                    p.process(OwnerID,"OwnerID");
                    p.process(Name,"Name");
                    p.process(Desc,"Desc");
                    p.process(ActualArea,"ActualArea");
                    p.process(BillableArea,"BillableArea");
                    p.process(Flags,"Flags");
                    p.process(GlobalX,"GlobalX");
                    p.process(GlobalY,"GlobalY");
                    p.process(GlobalZ,"GlobalZ");
                    p.process(SimName,"SimName");
                    p.process(SnapshotID,"SnapshotID");
                    p.process(Dwell,"Dwell");
                    p.process(SalePrice,"SalePrice");
                    p.process(AuctionID,"AuctionID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ParcelObjectOwnersRequestMessage
            : Message
        {
            static char const * name(){ return "ParcelObjectOwnersRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0038ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelObjectOwnersRequestMessage>();
                }
            };


            ParcelObjectOwnersRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , ParcelData()
            {}

            ParcelObjectOwnersRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Int32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct ParcelObjectOwnersReplyMessage
            : Message
        {
            static char const * name(){ return "ParcelObjectOwnersReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0039ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelObjectOwnersReplyMessage>();
                }
            };


            ParcelObjectOwnersReplyMessage()
            : Message(LowHeader())
            , Data()
            {}

            ParcelObjectOwnersReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlock
            {
                LLUUID OwnerID;
                bool IsGroupOwned;
                Int32 Count;
                bool OnlineStatus;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(OwnerID,"OwnerID");
                    p.process(IsGroupOwned,"IsGroupOwned");
                    p.process(Count,"Count");
                    p.process(OnlineStatus,"OnlineStatus");
                }

            };


            std::vector<DataBlock> Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Data,"Data");
            }

        };

        struct GroupNoticesListRequestMessage
            : Message
        {
            static char const * name(){ return "GroupNoticesListRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF003Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupNoticesListRequestMessage>();
                }
            };


            GroupNoticesListRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            GroupNoticesListRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct GroupNoticesListReplyMessage
            : Message
        {
            static char const * name(){ return "GroupNoticesListReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF003Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupNoticesListReplyMessage>();
                }
            };


            GroupNoticesListReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            GroupNoticesListReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct DataBlock
            {
                LLUUID NoticeID;
                UInt32 Timestamp;
                raw::LLVariable FromName;
                raw::LLVariable Subject;
                bool HasAttachment;
                UInt8 AssetType;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(NoticeID,"NoticeID");
                    p.process(Timestamp,"Timestamp");
                    p.process(FromName,"FromName");
                    p.process(Subject,"Subject");
                    p.process(HasAttachment,"HasAttachment");
                    p.process(AssetType,"AssetType");
                }

            };


            AgentDataBlock AgentData;
            std::vector<DataBlock> Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct GroupNoticeRequestMessage
            : Message
        {
            static char const * name(){ return "GroupNoticeRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF003Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupNoticeRequestMessage>();
                }
            };


            GroupNoticeRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            GroupNoticeRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID GroupNoticeID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupNoticeID,"GroupNoticeID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct TeleportRequestMessage
            : Message
        {
            static char const * name(){ return "TeleportRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF003Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TeleportRequestMessage>();
                }
            };


            TeleportRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , Info()
            {}

            TeleportRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Info()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InfoBlock
            {
                LLUUID RegionID;
                raw::LLVector3 Position;
                raw::LLVector3 LookAt;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionID,"RegionID");
                    p.process(Position,"Position");
                    p.process(LookAt,"LookAt");
                }

            };


            AgentDataBlock AgentData;
            InfoBlock Info;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Info,"Info");
            }

        };

        struct TeleportLocationRequestMessage
            : Message
        {
            static char const * name(){ return "TeleportLocationRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF003Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TeleportLocationRequestMessage>();
                }
            };


            TeleportLocationRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , Info()
            {}

            TeleportLocationRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Info()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InfoBlock
            {
                UInt64 RegionHandle;
                raw::LLVector3 Position;
                raw::LLVector3 LookAt;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionHandle,"RegionHandle");
                    p.process(Position,"Position");
                    p.process(LookAt,"LookAt");
                }

            };


            AgentDataBlock AgentData;
            InfoBlock Info;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Info,"Info");
            }

        };

        struct TeleportLocalMessage
            : Message
        {
            static char const * name(){ return "TeleportLocal"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0040ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TeleportLocalMessage>();
                }
            };


            TeleportLocalMessage()
            : Message(LowHeader())
            , Info()
            {}

            TeleportLocalMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Info()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct InfoBlock
            {
                LLUUID AgentID;
                UInt32 LocationID;
                raw::LLVector3 Position;
                raw::LLVector3 LookAt;
                UInt32 TeleportFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(LocationID,"LocationID");
                    p.process(Position,"Position");
                    p.process(LookAt,"LookAt");
                    p.process(TeleportFlags,"TeleportFlags");
                }

            };


            InfoBlock Info;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Info,"Info");
            }

        };

        struct TeleportLandmarkRequestMessage
            : Message
        {
            static char const * name(){ return "TeleportLandmarkRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0041ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TeleportLandmarkRequestMessage>();
                }
            };


            TeleportLandmarkRequestMessage()
            : Message(LowHeader())
            , Info()
            {}

            TeleportLandmarkRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Info()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct InfoBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID LandmarkID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(LandmarkID,"LandmarkID");
                }

            };


            InfoBlock Info;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Info,"Info");
            }

        };

        struct TeleportProgressMessage
            : Message
        {
            static char const * name(){ return "TeleportProgress"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0042ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TeleportProgressMessage>();
                }
            };


            TeleportProgressMessage()
            : Message(LowHeader())
            , AgentData()
            , Info()
            {}

            TeleportProgressMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Info()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct InfoBlock
            {
                UInt32 TeleportFlags;
                raw::LLVariable Message;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TeleportFlags,"TeleportFlags");
                    p.process(Message,"Message");
                }

            };


            AgentDataBlock AgentData;
            InfoBlock Info;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Info,"Info");
            }

        };

        struct TeleportFinishMessage
            : Message
        {
            static char const * name(){ return "TeleportFinish"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0045ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TeleportFinishMessage>();
                }
            };


            TeleportFinishMessage()
            : Message(LowHeader())
            , Info()
            {}

            TeleportFinishMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Info()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct InfoBlock
            {
                LLUUID AgentID;
                UInt32 LocationID;
                raw::LLIPAddress SimIP;
                raw::LLIPPort SimPort;
                UInt64 RegionHandle;
                raw::LLVariable SeedCapability;
                UInt8 SimAccess;
                UInt32 TeleportFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(LocationID,"LocationID");
                    p.process(SimIP,"SimIP");
                    p.process(SimPort,"SimPort");
                    p.process(RegionHandle,"RegionHandle");
                    p.process(SeedCapability,"SeedCapability");
                    p.process(SimAccess,"SimAccess");
                    p.process(TeleportFlags,"TeleportFlags");
                }

            };


            InfoBlock Info;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Info,"Info");
            }

        };

        struct StartLureMessage
            : Message
        {
            static char const * name(){ return "StartLure"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0046ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<StartLureMessage>();
                }
            };


            StartLureMessage()
            : Message(LowHeader())
            , AgentData()
            , Info()
            , TargetData()
            {}

            StartLureMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Info()
            , TargetData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InfoBlock
            {
                UInt8 LureType;
                raw::LLVariable Message;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LureType,"LureType");
                    p.process(Message,"Message");
                }

            };

            struct TargetDataBlock
            {
                LLUUID TargetID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TargetID,"TargetID");
                }

            };


            AgentDataBlock AgentData;
            InfoBlock Info;
            std::vector<TargetDataBlock> TargetData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Info,"Info");
                p.process(TargetData,"TargetData");
            }

        };

        struct TeleportLureRequestMessage
            : Message
        {
            static char const * name(){ return "TeleportLureRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0047ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TeleportLureRequestMessage>();
                }
            };


            TeleportLureRequestMessage()
            : Message(LowHeader())
            , Info()
            {}

            TeleportLureRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Info()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct InfoBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID LureID;
                UInt32 TeleportFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(LureID,"LureID");
                    p.process(TeleportFlags,"TeleportFlags");
                }

            };


            InfoBlock Info;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Info,"Info");
            }

        };

        struct TeleportCancelMessage
            : Message
        {
            static char const * name(){ return "TeleportCancel"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0048ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TeleportCancelMessage>();
                }
            };


            TeleportCancelMessage()
            : Message(LowHeader())
            , Info()
            {}

            TeleportCancelMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Info()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct InfoBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            InfoBlock Info;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Info,"Info");
            }

        };

        struct TeleportStartMessage
            : Message
        {
            static char const * name(){ return "TeleportStart"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0049ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TeleportStartMessage>();
                }
            };


            TeleportStartMessage()
            : Message(LowHeader())
            , Info()
            {}

            TeleportStartMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Info()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct InfoBlock
            {
                UInt32 TeleportFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TeleportFlags,"TeleportFlags");
                }

            };


            InfoBlock Info;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Info,"Info");
            }

        };

        struct TeleportFailedMessage
            : Message
        {
            static char const * name(){ return "TeleportFailed"; }
            static bool const trusted = false;
            enum { id = 0xFFFF004Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TeleportFailedMessage>();
                }
            };


            TeleportFailedMessage()
            : Message(LowHeader())
            , Info()
            {}

            TeleportFailedMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Info()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct InfoBlock
            {
                LLUUID AgentID;
                raw::LLVariable Reason;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(Reason,"Reason");
                }

            };


            InfoBlock Info;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Info,"Info");
            }

        };

        struct UndoMessage
            : Message
        {
            static char const * name(){ return "Undo"; }
            static bool const trusted = false;
            enum { id = 0xFFFF004Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UndoMessage>();
                }
            };


            UndoMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            UndoMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct ObjectDataBlock
            {
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct RedoMessage
            : Message
        {
            static char const * name(){ return "Redo"; }
            static bool const trusted = false;
            enum { id = 0xFFFF004Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RedoMessage>();
                }
            };


            RedoMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            RedoMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct ObjectDataBlock
            {
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct UndoLandMessage
            : Message
        {
            static char const * name(){ return "UndoLand"; }
            static bool const trusted = false;
            enum { id = 0xFFFF004Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UndoLandMessage>();
                }
            };


            UndoLandMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            UndoLandMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct AgentPauseMessage
            : Message
        {
            static char const * name(){ return "AgentPause"; }
            static bool const trusted = false;
            enum { id = 0xFFFF004Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentPauseMessage>();
                }
            };


            AgentPauseMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            AgentPauseMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 SerialNum;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(SerialNum,"SerialNum");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct AgentResumeMessage
            : Message
        {
            static char const * name(){ return "AgentResume"; }
            static bool const trusted = false;
            enum { id = 0xFFFF004Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentResumeMessage>();
                }
            };


            AgentResumeMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            AgentResumeMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 SerialNum;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(SerialNum,"SerialNum");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct ChatFromViewerMessage
            : Message
        {
            static char const * name(){ return "ChatFromViewer"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0050ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ChatFromViewerMessage>();
                }
            };


            ChatFromViewerMessage()
            : Message(LowHeader())
            , AgentData()
            , ChatData()
            {}

            ChatFromViewerMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ChatData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ChatDataBlock
            {
                raw::LLVariable Message;
                UInt8 Type;
                Int32 Channel;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Message,"Message");
                    p.process(Type,"Type");
                    p.process(Channel,"Channel");
                }

            };


            AgentDataBlock AgentData;
            ChatDataBlock ChatData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ChatData,"ChatData");
            }

        };

        struct AgentThrottleMessage
            : Message
        {
            static char const * name(){ return "AgentThrottle"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0051ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentThrottleMessage>();
                }
            };


            AgentThrottleMessage()
            : Message(LowHeader())
            , AgentData()
            , Throttle()
            {}

            AgentThrottleMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Throttle()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 CircuitCode;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(CircuitCode,"CircuitCode");
                }

            };

            struct ThrottleBlock
            {
                UInt32 GenCounter;
                raw::LLVariable Throttles;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GenCounter,"GenCounter");
                    p.process(Throttles,"Throttles");
                }

            };


            AgentDataBlock AgentData;
            ThrottleBlock Throttle;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Throttle,"Throttle");
            }

        };

        struct AgentFOVMessage
            : Message
        {
            static char const * name(){ return "AgentFOV"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0052ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentFOVMessage>();
                }
            };


            AgentFOVMessage()
            : Message(LowHeader())
            , AgentData()
            , FOVBlock()
            {}

            AgentFOVMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , FOVBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 CircuitCode;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(CircuitCode,"CircuitCode");
                }

            };

            struct FOVBlockBlock
            {
                UInt32 GenCounter;
                Real32 VerticalAngle;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GenCounter,"GenCounter");
                    p.process(VerticalAngle,"VerticalAngle");
                }

            };


            AgentDataBlock AgentData;
            FOVBlockBlock FOVBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(FOVBlock,"FOVBlock");
            }

        };

        struct AgentHeightWidthMessage
            : Message
        {
            static char const * name(){ return "AgentHeightWidth"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0053ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentHeightWidthMessage>();
                }
            };


            AgentHeightWidthMessage()
            : Message(LowHeader())
            , AgentData()
            , HeightWidthBlock()
            {}

            AgentHeightWidthMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , HeightWidthBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 CircuitCode;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(CircuitCode,"CircuitCode");
                }

            };

            struct HeightWidthBlockBlock
            {
                UInt32 GenCounter;
                UInt16 Height;
                UInt16 Width;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GenCounter,"GenCounter");
                    p.process(Height,"Height");
                    p.process(Width,"Width");
                }

            };


            AgentDataBlock AgentData;
            HeightWidthBlockBlock HeightWidthBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(HeightWidthBlock,"HeightWidthBlock");
            }

        };

        struct AgentSetAppearanceMessage
            : Message
        {
            static char const * name(){ return "AgentSetAppearance"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0054ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentSetAppearanceMessage>();
                }
            };


            AgentSetAppearanceMessage()
            : Message(LowHeader())
            , AgentData()
            , WearableData()
            , ObjectData()
            , VisualParam()
            {}

            AgentSetAppearanceMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , WearableData()
            , ObjectData()
            , VisualParam()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 SerialNum;
                raw::LLVector3 Size;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(SerialNum,"SerialNum");
                    p.process(Size,"Size");
                }

            };

            struct WearableDataBlock
            {
                LLUUID CacheID;
                UInt8 TextureIndex;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(CacheID,"CacheID");
                    p.process(TextureIndex,"TextureIndex");
                }

            };

            struct ObjectDataBlock
            {
                raw::LLVariable TextureEntry;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TextureEntry,"TextureEntry");
                }

            };

            struct VisualParamBlock
            {
                UInt8 ParamValue;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ParamValue,"ParamValue");
                }

            };


            AgentDataBlock AgentData;
            std::vector<WearableDataBlock> WearableData;
            ObjectDataBlock ObjectData;
            std::vector<VisualParamBlock> VisualParam;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(WearableData,"WearableData");
                p.process(ObjectData,"ObjectData");
                p.process(VisualParam,"VisualParam");
            }

        };

        struct AgentQuitCopyMessage
            : Message
        {
            static char const * name(){ return "AgentQuitCopy"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0055ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentQuitCopyMessage>();
                }
            };


            AgentQuitCopyMessage()
            : Message(LowHeader())
            , AgentData()
            , FuseBlock()
            {}

            AgentQuitCopyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , FuseBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct FuseBlockBlock
            {
                UInt32 ViewerCircuitCode;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ViewerCircuitCode,"ViewerCircuitCode");
                }

            };


            AgentDataBlock AgentData;
            FuseBlockBlock FuseBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(FuseBlock,"FuseBlock");
            }

        };

        struct ImageNotInDatabaseMessage
            : Message
        {
            static char const * name(){ return "ImageNotInDatabase"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0056ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ImageNotInDatabaseMessage>();
                }
            };


            ImageNotInDatabaseMessage()
            : Message(LowHeader())
            , ImageID()
            {}

            ImageNotInDatabaseMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , ImageID()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ImageIDBlock
            {
                LLUUID ID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                }

            };


            ImageIDBlock ImageID;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ImageID,"ImageID");
            }

        };

        struct RebakeAvatarTexturesMessage
            : Message
        {
            static char const * name(){ return "RebakeAvatarTextures"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0057ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RebakeAvatarTexturesMessage>();
                }
            };


            RebakeAvatarTexturesMessage()
            : Message(LowHeader())
            , TextureData()
            {}

            RebakeAvatarTexturesMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , TextureData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct TextureDataBlock
            {
                LLUUID TextureID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TextureID,"TextureID");
                }

            };


            TextureDataBlock TextureData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(TextureData,"TextureData");
            }

        };

        struct SetAlwaysRunMessage
            : Message
        {
            static char const * name(){ return "SetAlwaysRun"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0058ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SetAlwaysRunMessage>();
                }
            };


            SetAlwaysRunMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            SetAlwaysRunMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                bool AlwaysRun;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(AlwaysRun,"AlwaysRun");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct ObjectDeleteMessage
            : Message
        {
            static char const * name(){ return "ObjectDelete"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0059ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectDeleteMessage>();
                }
            };


            ObjectDeleteMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectDeleteMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                bool Force;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(Force,"Force");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectDuplicateMessage
            : Message
        {
            static char const * name(){ return "ObjectDuplicate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF005Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectDuplicateMessage>();
                }
            };


            ObjectDuplicateMessage()
            : Message(LowHeader())
            , AgentData()
            , SharedData()
            , ObjectData()
            {}

            ObjectDuplicateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , SharedData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct SharedDataBlock
            {
                raw::LLVector3 Offset;
                UInt32 DuplicateFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Offset,"Offset");
                    p.process(DuplicateFlags,"DuplicateFlags");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                }

            };


            AgentDataBlock AgentData;
            SharedDataBlock SharedData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(SharedData,"SharedData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectDuplicateOnRayMessage
            : Message
        {
            static char const * name(){ return "ObjectDuplicateOnRay"; }
            static bool const trusted = false;
            enum { id = 0xFFFF005Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectDuplicateOnRayMessage>();
                }
            };


            ObjectDuplicateOnRayMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectDuplicateOnRayMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;
                raw::LLVector3 RayStart;
                raw::LLVector3 RayEnd;
                bool BypassRaycast;
                bool RayEndIsIntersection;
                bool CopyCenters;
                bool CopyRotates;
                LLUUID RayTargetID;
                UInt32 DuplicateFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                    p.process(RayStart,"RayStart");
                    p.process(RayEnd,"RayEnd");
                    p.process(BypassRaycast,"BypassRaycast");
                    p.process(RayEndIsIntersection,"RayEndIsIntersection");
                    p.process(CopyCenters,"CopyCenters");
                    p.process(CopyRotates,"CopyRotates");
                    p.process(RayTargetID,"RayTargetID");
                    p.process(DuplicateFlags,"DuplicateFlags");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectScaleMessage
            : Message
        {
            static char const * name(){ return "ObjectScale"; }
            static bool const trusted = false;
            enum { id = 0xFFFF005Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectScaleMessage>();
                }
            };


            ObjectScaleMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectScaleMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                raw::LLVector3 Scale;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(Scale,"Scale");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectRotationMessage
            : Message
        {
            static char const * name(){ return "ObjectRotation"; }
            static bool const trusted = false;
            enum { id = 0xFFFF005Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectRotationMessage>();
                }
            };


            ObjectRotationMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectRotationMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                raw::LLQuaternion Rotation;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(Rotation,"Rotation");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectFlagUpdateMessage
            : Message
        {
            static char const * name(){ return "ObjectFlagUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF005Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectFlagUpdateMessage>();
                }
            };


            ObjectFlagUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            ObjectFlagUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 ObjectLocalID;
                bool UsePhysics;
                bool IsTemporary;
                bool IsPhantom;
                bool CastsShadows;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(UsePhysics,"UsePhysics");
                    p.process(IsTemporary,"IsTemporary");
                    p.process(IsPhantom,"IsPhantom");
                    p.process(CastsShadows,"CastsShadows");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct ObjectClickActionMessage
            : Message
        {
            static char const * name(){ return "ObjectClickAction"; }
            static bool const trusted = false;
            enum { id = 0xFFFF005Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectClickActionMessage>();
                }
            };


            ObjectClickActionMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectClickActionMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                UInt8 ClickAction;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(ClickAction,"ClickAction");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectImageMessage
            : Message
        {
            static char const * name(){ return "ObjectImage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0060ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectImageMessage>();
                }
            };


            ObjectImageMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectImageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                raw::LLVariable MediaURL;
                raw::LLVariable TextureEntry;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(MediaURL,"MediaURL");
                    p.process(TextureEntry,"TextureEntry");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectMaterialMessage
            : Message
        {
            static char const * name(){ return "ObjectMaterial"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0061ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectMaterialMessage>();
                }
            };


            ObjectMaterialMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectMaterialMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                UInt8 Material;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(Material,"Material");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectShapeMessage
            : Message
        {
            static char const * name(){ return "ObjectShape"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0062ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectShapeMessage>();
                }
            };


            ObjectShapeMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectShapeMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                UInt8 PathCurve;
                UInt8 ProfileCurve;
                UInt16 PathBegin;
                UInt16 PathEnd;
                UInt8 PathScaleX;
                UInt8 PathScaleY;
                UInt8 PathShearX;
                UInt8 PathShearY;
                Int8 PathTwist;
                Int8 PathTwistBegin;
                Int8 PathRadiusOffset;
                Int8 PathTaperX;
                Int8 PathTaperY;
                UInt8 PathRevolutions;
                Int8 PathSkew;
                UInt16 ProfileBegin;
                UInt16 ProfileEnd;
                UInt16 ProfileHollow;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(PathCurve,"PathCurve");
                    p.process(ProfileCurve,"ProfileCurve");
                    p.process(PathBegin,"PathBegin");
                    p.process(PathEnd,"PathEnd");
                    p.process(PathScaleX,"PathScaleX");
                    p.process(PathScaleY,"PathScaleY");
                    p.process(PathShearX,"PathShearX");
                    p.process(PathShearY,"PathShearY");
                    p.process(PathTwist,"PathTwist");
                    p.process(PathTwistBegin,"PathTwistBegin");
                    p.process(PathRadiusOffset,"PathRadiusOffset");
                    p.process(PathTaperX,"PathTaperX");
                    p.process(PathTaperY,"PathTaperY");
                    p.process(PathRevolutions,"PathRevolutions");
                    p.process(PathSkew,"PathSkew");
                    p.process(ProfileBegin,"ProfileBegin");
                    p.process(ProfileEnd,"ProfileEnd");
                    p.process(ProfileHollow,"ProfileHollow");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectExtraParamsMessage
            : Message
        {
            static char const * name(){ return "ObjectExtraParams"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0063ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectExtraParamsMessage>();
                }
            };


            ObjectExtraParamsMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectExtraParamsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                UInt16 ParamType;
                bool ParamInUse;
                UInt32 ParamSize;
                raw::LLVariable ParamData;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(ParamType,"ParamType");
                    p.process(ParamInUse,"ParamInUse");
                    p.process(ParamSize,"ParamSize");
                    p.process(ParamData,"ParamData");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectOwnerMessage
            : Message
        {
            static char const * name(){ return "ObjectOwner"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0064ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectOwnerMessage>();
                }
            };


            ObjectOwnerMessage()
            : Message(LowHeader())
            , AgentData()
            , HeaderData()
            , ObjectData()
            {}

            ObjectOwnerMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , HeaderData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct HeaderDataBlock
            {
                bool Override;
                LLUUID OwnerID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Override,"Override");
                    p.process(OwnerID,"OwnerID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                }

            };


            AgentDataBlock AgentData;
            HeaderDataBlock HeaderData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(HeaderData,"HeaderData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectGroupMessage
            : Message
        {
            static char const * name(){ return "ObjectGroup"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0065ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectGroupMessage>();
                }
            };


            ObjectGroupMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectGroupMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectBuyMessage
            : Message
        {
            static char const * name(){ return "ObjectBuy"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0066ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectBuyMessage>();
                }
            };


            ObjectBuyMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectBuyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;
                LLUUID CategoryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                    p.process(CategoryID,"CategoryID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                UInt8 SaleType;
                Int32 SalePrice;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(SaleType,"SaleType");
                    p.process(SalePrice,"SalePrice");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct BuyObjectInventoryMessage
            : Message
        {
            static char const * name(){ return "BuyObjectInventory"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0067ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<BuyObjectInventoryMessage>();
                }
            };


            BuyObjectInventoryMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            BuyObjectInventoryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID ObjectID;
                LLUUID ItemID;
                LLUUID FolderID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(ItemID,"ItemID");
                    p.process(FolderID,"FolderID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct DerezContainerMessage
            : Message
        {
            static char const * name(){ return "DerezContainer"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0068ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DerezContainerMessage>();
                }
            };


            DerezContainerMessage()
            : Message(LowHeader())
            , Data()
            {}

            DerezContainerMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlock
            {
                LLUUID ObjectID;
                bool Delete;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(Delete,"Delete");
                }

            };


            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Data,"Data");
            }

        };

        struct ObjectPermissionsMessage
            : Message
        {
            static char const * name(){ return "ObjectPermissions"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0069ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectPermissionsMessage>();
                }
            };


            ObjectPermissionsMessage()
            : Message(LowHeader())
            , AgentData()
            , HeaderData()
            , ObjectData()
            {}

            ObjectPermissionsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , HeaderData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct HeaderDataBlock
            {
                bool Override;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Override,"Override");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                UInt8 Field;
                UInt8 Set;
                UInt32 Mask;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(Field,"Field");
                    p.process(Set,"Set");
                    p.process(Mask,"Mask");
                }

            };


            AgentDataBlock AgentData;
            HeaderDataBlock HeaderData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(HeaderData,"HeaderData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectSaleInfoMessage
            : Message
        {
            static char const * name(){ return "ObjectSaleInfo"; }
            static bool const trusted = false;
            enum { id = 0xFFFF006Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectSaleInfoMessage>();
                }
            };


            ObjectSaleInfoMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectSaleInfoMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 LocalID;
                UInt8 SaleType;
                Int32 SalePrice;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(SaleType,"SaleType");
                    p.process(SalePrice,"SalePrice");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectNameMessage
            : Message
        {
            static char const * name(){ return "ObjectName"; }
            static bool const trusted = false;
            enum { id = 0xFFFF006Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectNameMessage>();
                }
            };


            ObjectNameMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectNameMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 LocalID;
                raw::LLVariable Name;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(Name,"Name");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectDescriptionMessage
            : Message
        {
            static char const * name(){ return "ObjectDescription"; }
            static bool const trusted = false;
            enum { id = 0xFFFF006Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectDescriptionMessage>();
                }
            };


            ObjectDescriptionMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectDescriptionMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 LocalID;
                raw::LLVariable Description;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(Description,"Description");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectCategoryMessage
            : Message
        {
            static char const * name(){ return "ObjectCategory"; }
            static bool const trusted = false;
            enum { id = 0xFFFF006Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectCategoryMessage>();
                }
            };


            ObjectCategoryMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectCategoryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 LocalID;
                UInt32 Category;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(Category,"Category");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectSelectMessage
            : Message
        {
            static char const * name(){ return "ObjectSelect"; }
            static bool const trusted = false;
            enum { id = 0xFFFF006Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectSelectMessage>();
                }
            };


            ObjectSelectMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectSelectMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectDeselectMessage
            : Message
        {
            static char const * name(){ return "ObjectDeselect"; }
            static bool const trusted = false;
            enum { id = 0xFFFF006Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectDeselectMessage>();
                }
            };


            ObjectDeselectMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectDeselectMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectAttachMessage
            : Message
        {
            static char const * name(){ return "ObjectAttach"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0070ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectAttachMessage>();
                }
            };


            ObjectAttachMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectAttachMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt8 AttachmentPoint;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(AttachmentPoint,"AttachmentPoint");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                raw::LLQuaternion Rotation;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(Rotation,"Rotation");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectDetachMessage
            : Message
        {
            static char const * name(){ return "ObjectDetach"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0071ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectDetachMessage>();
                }
            };


            ObjectDetachMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectDetachMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectDropMessage
            : Message
        {
            static char const * name(){ return "ObjectDrop"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0072ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectDropMessage>();
                }
            };


            ObjectDropMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectDropMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectLinkMessage
            : Message
        {
            static char const * name(){ return "ObjectLink"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0073ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectLinkMessage>();
                }
            };


            ObjectLinkMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectLinkMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectDelinkMessage
            : Message
        {
            static char const * name(){ return "ObjectDelink"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0074ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectDelinkMessage>();
                }
            };


            ObjectDelinkMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectDelinkMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectGrabMessage
            : Message
        {
            static char const * name(){ return "ObjectGrab"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0075ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectGrabMessage>();
                }
            };


            ObjectGrabMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectGrabMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 LocalID;
                raw::LLVector3 GrabOffset;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(GrabOffset,"GrabOffset");
                }

            };


            AgentDataBlock AgentData;
            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectGrabUpdateMessage
            : Message
        {
            static char const * name(){ return "ObjectGrabUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0076ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectGrabUpdateMessage>();
                }
            };


            ObjectGrabUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectGrabUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                LLUUID ObjectID;
                raw::LLVector3 GrabOffsetInitial;
                raw::LLVector3 GrabPosition;
                UInt32 TimeSinceLast;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(GrabOffsetInitial,"GrabOffsetInitial");
                    p.process(GrabPosition,"GrabPosition");
                    p.process(TimeSinceLast,"TimeSinceLast");
                }

            };


            AgentDataBlock AgentData;
            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectDeGrabMessage
            : Message
        {
            static char const * name(){ return "ObjectDeGrab"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0077ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectDeGrabMessage>();
                }
            };


            ObjectDeGrabMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectDeGrabMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                }

            };


            AgentDataBlock AgentData;
            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectSpinStartMessage
            : Message
        {
            static char const * name(){ return "ObjectSpinStart"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0078ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectSpinStartMessage>();
                }
            };


            ObjectSpinStartMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectSpinStartMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                }

            };


            AgentDataBlock AgentData;
            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectSpinUpdateMessage
            : Message
        {
            static char const * name(){ return "ObjectSpinUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0079ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectSpinUpdateMessage>();
                }
            };


            ObjectSpinUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectSpinUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                LLUUID ObjectID;
                raw::LLQuaternion Rotation;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(Rotation,"Rotation");
                }

            };


            AgentDataBlock AgentData;
            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectSpinStopMessage
            : Message
        {
            static char const * name(){ return "ObjectSpinStop"; }
            static bool const trusted = false;
            enum { id = 0xFFFF007Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectSpinStopMessage>();
                }
            };


            ObjectSpinStopMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectSpinStopMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                }

            };


            AgentDataBlock AgentData;
            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectExportSelectedMessage
            : Message
        {
            static char const * name(){ return "ObjectExportSelected"; }
            static bool const trusted = false;
            enum { id = 0xFFFF007Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectExportSelectedMessage>();
                }
            };


            ObjectExportSelectedMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectExportSelectedMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID RequestID;
                Int16 VolumeDetail;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(RequestID,"RequestID");
                    p.process(VolumeDetail,"VolumeDetail");
                }

            };

            struct ObjectDataBlock
            {
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ModifyLandMessage
            : Message
        {
            static char const * name(){ return "ModifyLand"; }
            static bool const trusted = false;
            enum { id = 0xFFFF007Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ModifyLandMessage>();
                }
            };


            ModifyLandMessage()
            : Message(LowHeader())
            , AgentData()
            , ModifyBlock()
            , ParcelData()
            {}

            ModifyLandMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ModifyBlock()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ModifyBlockBlock
            {
                UInt8 Action;
                UInt8 BrushSize;
                Real32 Seconds;
                Real32 Height;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Action,"Action");
                    p.process(BrushSize,"BrushSize");
                    p.process(Seconds,"Seconds");
                    p.process(Height,"Height");
                }

            };

            struct ParcelDataBlock
            {
                Int32 LocalID;
                Real32 West;
                Real32 South;
                Real32 East;
                Real32 North;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(West,"West");
                    p.process(South,"South");
                    p.process(East,"East");
                    p.process(North,"North");
                }

            };


            AgentDataBlock AgentData;
            ModifyBlockBlock ModifyBlock;
            std::vector<ParcelDataBlock> ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ModifyBlock,"ModifyBlock");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct VelocityInterpolateOnMessage
            : Message
        {
            static char const * name(){ return "VelocityInterpolateOn"; }
            static bool const trusted = false;
            enum { id = 0xFFFF007Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<VelocityInterpolateOnMessage>();
                }
            };


            VelocityInterpolateOnMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            VelocityInterpolateOnMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct VelocityInterpolateOffMessage
            : Message
        {
            static char const * name(){ return "VelocityInterpolateOff"; }
            static bool const trusted = false;
            enum { id = 0xFFFF007Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<VelocityInterpolateOffMessage>();
                }
            };


            VelocityInterpolateOffMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            VelocityInterpolateOffMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct StateSaveMessage
            : Message
        {
            static char const * name(){ return "StateSave"; }
            static bool const trusted = false;
            enum { id = 0xFFFF007Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<StateSaveMessage>();
                }
            };


            StateSaveMessage()
            : Message(LowHeader())
            , AgentData()
            , DataBlock()
            {}

            StateSaveMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , DataBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlockBlock
            {
                raw::LLVariable Filename;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Filename,"Filename");
                }

            };


            AgentDataBlock AgentData;
            DataBlockBlock DataBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(DataBlock,"DataBlock");
            }

        };

        struct ReportAutosaveCrashMessage
            : Message
        {
            static char const * name(){ return "ReportAutosaveCrash"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0080ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ReportAutosaveCrashMessage>();
                }
            };


            ReportAutosaveCrashMessage()
            : Message(LowHeader())
            , AutosaveData()
            {}

            ReportAutosaveCrashMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AutosaveData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AutosaveDataBlock
            {
                Int32 PID;
                Int32 Status;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(PID,"PID");
                    p.process(Status,"Status");
                }

            };


            AutosaveDataBlock AutosaveData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AutosaveData,"AutosaveData");
            }

        };

        struct SimWideDeletesMessage
            : Message
        {
            static char const * name(){ return "SimWideDeletes"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0081ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SimWideDeletesMessage>();
                }
            };


            SimWideDeletesMessage()
            : Message(LowHeader())
            , AgentData()
            , DataBlock()
            {}

            SimWideDeletesMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , DataBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlockBlock
            {
                LLUUID TargetID;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TargetID,"TargetID");
                    p.process(Flags,"Flags");
                }

            };


            AgentDataBlock AgentData;
            DataBlockBlock DataBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(DataBlock,"DataBlock");
            }

        };

        struct TrackAgentMessage
            : Message
        {
            static char const * name(){ return "TrackAgent"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0082ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TrackAgentMessage>();
                }
            };


            TrackAgentMessage()
            : Message(LowHeader())
            , AgentData()
            , TargetData()
            {}

            TrackAgentMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , TargetData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct TargetDataBlock
            {
                LLUUID PreyID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(PreyID,"PreyID");
                }

            };


            AgentDataBlock AgentData;
            TargetDataBlock TargetData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(TargetData,"TargetData");
            }

        };

        struct ViewerStatsMessage
            : Message
        {
            static char const * name(){ return "ViewerStats"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0083ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ViewerStatsMessage>();
                }
            };


            ViewerStatsMessage()
            : Message(LowHeader())
            , AgentData()
            , DownloadTotals()
            , NetStats()
            , FailStats()
            , MiscStats()
            {}

            ViewerStatsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , DownloadTotals()
            , NetStats()
            , FailStats()
            , MiscStats()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                raw::LLIPAddress IP;
                UInt32 StartTime;
                Real32 RunTime;
                Real32 SimFPS;
                Real32 FPS;
                UInt8 AgentsInView;
                Real32 Ping;
                Real64 MetersTraveled;
                Int32 RegionsVisited;
                UInt32 SysRAM;
                raw::LLVariable SysOS;
                raw::LLVariable SysCPU;
                raw::LLVariable SysGPU;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(IP,"IP");
                    p.process(StartTime,"StartTime");
                    p.process(RunTime,"RunTime");
                    p.process(SimFPS,"SimFPS");
                    p.process(FPS,"FPS");
                    p.process(AgentsInView,"AgentsInView");
                    p.process(Ping,"Ping");
                    p.process(MetersTraveled,"MetersTraveled");
                    p.process(RegionsVisited,"RegionsVisited");
                    p.process(SysRAM,"SysRAM");
                    p.process(SysOS,"SysOS");
                    p.process(SysCPU,"SysCPU");
                    p.process(SysGPU,"SysGPU");
                }

            };

            struct DownloadTotalsBlock
            {
                UInt32 World;
                UInt32 Objects;
                UInt32 Textures;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(World,"World");
                    p.process(Objects,"Objects");
                    p.process(Textures,"Textures");
                }

            };

            struct NetStatsBlock
            {
                UInt32 Bytes;
                UInt32 Packets;
                UInt32 Compressed;
                UInt32 Savings;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Bytes,"Bytes");
                    p.process(Packets,"Packets");
                    p.process(Compressed,"Compressed");
                    p.process(Savings,"Savings");
                }

            };

            struct FailStatsBlock
            {
                UInt32 SendPacket;
                UInt32 Dropped;
                UInt32 Resent;
                UInt32 FailedResends;
                UInt32 OffCircuit;
                UInt32 Invalid;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SendPacket,"SendPacket");
                    p.process(Dropped,"Dropped");
                    p.process(Resent,"Resent");
                    p.process(FailedResends,"FailedResends");
                    p.process(OffCircuit,"OffCircuit");
                    p.process(Invalid,"Invalid");
                }

            };

            struct MiscStatsBlock
            {
                UInt32 Type;
                Real64 Value;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Type,"Type");
                    p.process(Value,"Value");
                }

            };


            AgentDataBlock AgentData;
            DownloadTotalsBlock DownloadTotals;
            boost::array<NetStatsBlock,2> NetStats;
            FailStatsBlock FailStats;
            std::vector<MiscStatsBlock> MiscStats;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(DownloadTotals,"DownloadTotals");
                p.process(NetStats,"NetStats");
                p.process(FailStats,"FailStats");
                p.process(MiscStats,"MiscStats");
            }

        };

        struct ScriptAnswerYesMessage
            : Message
        {
            static char const * name(){ return "ScriptAnswerYes"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0084ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ScriptAnswerYesMessage>();
                }
            };


            ScriptAnswerYesMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ScriptAnswerYesMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID TaskID;
                LLUUID ItemID;
                Int32 Questions;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TaskID,"TaskID");
                    p.process(ItemID,"ItemID");
                    p.process(Questions,"Questions");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct UserReportMessage
            : Message
        {
            static char const * name(){ return "UserReport"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0085ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UserReportMessage>();
                }
            };


            UserReportMessage()
            : Message(LowHeader())
            , AgentData()
            , ReportData()
            {}

            UserReportMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ReportData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ReportDataBlock
            {
                UInt8 ReportType;
                UInt8 Category;
                raw::LLVector3 Position;
                UInt8 CheckFlags;
                LLUUID ScreenshotID;
                LLUUID ObjectID;
                LLUUID AbuserID;
                raw::LLVariable AbuseRegionName;
                LLUUID AbuseRegionID;
                raw::LLVariable Summary;
                raw::LLVariable Details;
                raw::LLVariable VersionString;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ReportType,"ReportType");
                    p.process(Category,"Category");
                    p.process(Position,"Position");
                    p.process(CheckFlags,"CheckFlags");
                    p.process(ScreenshotID,"ScreenshotID");
                    p.process(ObjectID,"ObjectID");
                    p.process(AbuserID,"AbuserID");
                    p.process(AbuseRegionName,"AbuseRegionName");
                    p.process(AbuseRegionID,"AbuseRegionID");
                    p.process(Summary,"Summary");
                    p.process(Details,"Details");
                    p.process(VersionString,"VersionString");
                }

            };


            AgentDataBlock AgentData;
            ReportDataBlock ReportData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ReportData,"ReportData");
            }

        };

        struct AlertMessageMessage
            : Message
        {
            static char const * name(){ return "AlertMessage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0086ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AlertMessageMessage>();
                }
            };


            AlertMessageMessage()
            : Message(LowHeader())
            , AlertData()
            {}

            AlertMessageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AlertData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AlertDataBlock
            {
                raw::LLVariable Message;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Message,"Message");
                }

            };


            AlertDataBlock AlertData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AlertData,"AlertData");
            }

        };

        struct AgentAlertMessageMessage
            : Message
        {
            static char const * name(){ return "AgentAlertMessage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0087ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentAlertMessageMessage>();
                }
            };


            AgentAlertMessageMessage()
            : Message(LowHeader())
            , AgentData()
            , AlertData()
            {}

            AgentAlertMessageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , AlertData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct AlertDataBlock
            {
                bool Modal;
                raw::LLVariable Message;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Modal,"Modal");
                    p.process(Message,"Message");
                }

            };


            AgentDataBlock AgentData;
            AlertDataBlock AlertData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(AlertData,"AlertData");
            }

        };

        struct MeanCollisionAlertMessage
            : Message
        {
            static char const * name(){ return "MeanCollisionAlert"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0088ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MeanCollisionAlertMessage>();
                }
            };


            MeanCollisionAlertMessage()
            : Message(LowHeader())
            , MeanCollision()
            {}

            MeanCollisionAlertMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , MeanCollision()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct MeanCollisionBlock
            {
                LLUUID Victim;
                LLUUID Perp;
                UInt32 Time;
                Real32 Mag;
                UInt8 Type;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Victim,"Victim");
                    p.process(Perp,"Perp");
                    p.process(Time,"Time");
                    p.process(Mag,"Mag");
                    p.process(Type,"Type");
                }

            };


            std::vector<MeanCollisionBlock> MeanCollision;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(MeanCollision,"MeanCollision");
            }

        };

        struct ViewerFrozenMessageMessage
            : Message
        {
            static char const * name(){ return "ViewerFrozenMessage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0089ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ViewerFrozenMessageMessage>();
                }
            };


            ViewerFrozenMessageMessage()
            : Message(LowHeader())
            , FrozenData()
            {}

            ViewerFrozenMessageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , FrozenData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct FrozenDataBlock
            {
                bool Data;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Data,"Data");
                }

            };


            FrozenDataBlock FrozenData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(FrozenData,"FrozenData");
            }

        };

        struct HealthMessageMessage
            : Message
        {
            static char const * name(){ return "HealthMessage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF008Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<HealthMessageMessage>();
                }
            };


            HealthMessageMessage()
            : Message(LowHeader())
            , HealthData()
            {}

            HealthMessageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , HealthData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct HealthDataBlock
            {
                Real32 Health;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Health,"Health");
                }

            };


            HealthDataBlock HealthData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(HealthData,"HealthData");
            }

        };

        struct ChatFromSimulatorMessage
            : Message
        {
            static char const * name(){ return "ChatFromSimulator"; }
            static bool const trusted = false;
            enum { id = 0xFFFF008Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ChatFromSimulatorMessage>();
                }
            };


            ChatFromSimulatorMessage()
            : Message(LowHeader())
            , ChatData()
            {}

            ChatFromSimulatorMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , ChatData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ChatDataBlock
            {
                raw::LLVariable FromName;
                LLUUID SourceID;
                LLUUID OwnerID;
                UInt8 SourceType;
                UInt8 ChatType;
                UInt8 Audible;
                raw::LLVector3 Position;
                raw::LLVariable Message;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FromName,"FromName");
                    p.process(SourceID,"SourceID");
                    p.process(OwnerID,"OwnerID");
                    p.process(SourceType,"SourceType");
                    p.process(ChatType,"ChatType");
                    p.process(Audible,"Audible");
                    p.process(Position,"Position");
                    p.process(Message,"Message");
                }

            };


            ChatDataBlock ChatData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ChatData,"ChatData");
            }

        };

        struct SimStatsMessage
            : Message
        {
            static char const * name(){ return "SimStats"; }
            static bool const trusted = false;
            enum { id = 0xFFFF008Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SimStatsMessage>();
                }
            };


            SimStatsMessage()
            : Message(LowHeader())
            , Region()
            , Stat()
            {}

            SimStatsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Region()
            , Stat()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct RegionBlock
            {
                UInt32 RegionX;
                UInt32 RegionY;
                UInt32 RegionFlags;
                UInt32 ObjectCapacity;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionX,"RegionX");
                    p.process(RegionY,"RegionY");
                    p.process(RegionFlags,"RegionFlags");
                    p.process(ObjectCapacity,"ObjectCapacity");
                }

            };

            struct StatBlock
            {
                UInt32 StatID;
                Real32 StatValue;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(StatID,"StatID");
                    p.process(StatValue,"StatValue");
                }

            };


            RegionBlock Region;
            std::vector<StatBlock> Stat;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Region,"Region");
                p.process(Stat,"Stat");
            }

        };

        struct RequestRegionInfoMessage
            : Message
        {
            static char const * name(){ return "RequestRegionInfo"; }
            static bool const trusted = false;
            enum { id = 0xFFFF008Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RequestRegionInfoMessage>();
                }
            };


            RequestRegionInfoMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            RequestRegionInfoMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct RegionInfoMessage
            : Message
        {
            static char const * name(){ return "RegionInfo"; }
            static bool const trusted = false;
            enum { id = 0xFFFF008Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RegionInfoMessage>();
                }
            };


            RegionInfoMessage()
            : Message(LowHeader())
            , AgentData()
            , RegionInfo()
            {}

            RegionInfoMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , RegionInfo()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct RegionInfoBlock
            {
                raw::LLVariable SimName;
                UInt32 EstateID;
                UInt32 ParentEstateID;
                UInt32 RegionFlags;
                UInt8 SimAccess;
                UInt8 MaxAgents;
                Real32 BillableFactor;
                Real32 ObjectBonusFactor;
                Real32 WaterHeight;
                Real32 TerrainRaiseLimit;
                Real32 TerrainLowerLimit;
                Int32 PricePerMeter;
                Int32 RedirectGridX;
                Int32 RedirectGridY;
                bool UseEstateSun;
                Real32 SunHour;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SimName,"SimName");
                    p.process(EstateID,"EstateID");
                    p.process(ParentEstateID,"ParentEstateID");
                    p.process(RegionFlags,"RegionFlags");
                    p.process(SimAccess,"SimAccess");
                    p.process(MaxAgents,"MaxAgents");
                    p.process(BillableFactor,"BillableFactor");
                    p.process(ObjectBonusFactor,"ObjectBonusFactor");
                    p.process(WaterHeight,"WaterHeight");
                    p.process(TerrainRaiseLimit,"TerrainRaiseLimit");
                    p.process(TerrainLowerLimit,"TerrainLowerLimit");
                    p.process(PricePerMeter,"PricePerMeter");
                    p.process(RedirectGridX,"RedirectGridX");
                    p.process(RedirectGridY,"RedirectGridY");
                    p.process(UseEstateSun,"UseEstateSun");
                    p.process(SunHour,"SunHour");
                }

            };


            AgentDataBlock AgentData;
            RegionInfoBlock RegionInfo;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RegionInfo,"RegionInfo");
            }

        };

        struct GodUpdateRegionInfoMessage
            : Message
        {
            static char const * name(){ return "GodUpdateRegionInfo"; }
            static bool const trusted = false;
            enum { id = 0xFFFF008Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GodUpdateRegionInfoMessage>();
                }
            };


            GodUpdateRegionInfoMessage()
            : Message(LowHeader())
            , AgentData()
            , RegionInfo()
            {}

            GodUpdateRegionInfoMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , RegionInfo()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct RegionInfoBlock
            {
                raw::LLVariable SimName;
                UInt32 EstateID;
                UInt32 ParentEstateID;
                UInt32 RegionFlags;
                Real32 BillableFactor;
                Int32 PricePerMeter;
                Int32 RedirectGridX;
                Int32 RedirectGridY;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SimName,"SimName");
                    p.process(EstateID,"EstateID");
                    p.process(ParentEstateID,"ParentEstateID");
                    p.process(RegionFlags,"RegionFlags");
                    p.process(BillableFactor,"BillableFactor");
                    p.process(PricePerMeter,"PricePerMeter");
                    p.process(RedirectGridX,"RedirectGridX");
                    p.process(RedirectGridY,"RedirectGridY");
                }

            };


            AgentDataBlock AgentData;
            RegionInfoBlock RegionInfo;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RegionInfo,"RegionInfo");
            }

        };

        struct NearestLandingRegionUpdatedMessage
            : Message
        {
            static char const * name(){ return "NearestLandingRegionUpdated"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0092ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<NearestLandingRegionUpdatedMessage>();
                }
            };


            NearestLandingRegionUpdatedMessage()
            : Message(LowHeader())
            , RegionData()
            {}

            NearestLandingRegionUpdatedMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , RegionData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct RegionDataBlock
            {
                UInt64 RegionHandle;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionHandle,"RegionHandle");
                }

            };


            RegionDataBlock RegionData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(RegionData,"RegionData");
            }

        };

        struct RegionHandshakeMessage
            : Message
        {
            static char const * name(){ return "RegionHandshake"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0094ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RegionHandshakeMessage>();
                }
            };


            RegionHandshakeMessage()
            : Message(LowHeader())
            , RegionInfo()
            , RegionInfo2()
            {}

            RegionHandshakeMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , RegionInfo()
            , RegionInfo2()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct RegionInfoBlock
            {
                UInt32 RegionFlags;
                UInt8 SimAccess;
                raw::LLVariable SimName;
                LLUUID SimOwner;
                bool IsEstateManager;
                Real32 WaterHeight;
                Real32 BillableFactor;
                LLUUID CacheID;
                LLUUID TerrainBase0;
                LLUUID TerrainBase1;
                LLUUID TerrainBase2;
                LLUUID TerrainBase3;
                LLUUID TerrainDetail0;
                LLUUID TerrainDetail1;
                LLUUID TerrainDetail2;
                LLUUID TerrainDetail3;
                Real32 TerrainStartHeight00;
                Real32 TerrainStartHeight01;
                Real32 TerrainStartHeight10;
                Real32 TerrainStartHeight11;
                Real32 TerrainHeightRange00;
                Real32 TerrainHeightRange01;
                Real32 TerrainHeightRange10;
                Real32 TerrainHeightRange11;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionFlags,"RegionFlags");
                    p.process(SimAccess,"SimAccess");
                    p.process(SimName,"SimName");
                    p.process(SimOwner,"SimOwner");
                    p.process(IsEstateManager,"IsEstateManager");
                    p.process(WaterHeight,"WaterHeight");
                    p.process(BillableFactor,"BillableFactor");
                    p.process(CacheID,"CacheID");
                    p.process(TerrainBase0,"TerrainBase0");
                    p.process(TerrainBase1,"TerrainBase1");
                    p.process(TerrainBase2,"TerrainBase2");
                    p.process(TerrainBase3,"TerrainBase3");
                    p.process(TerrainDetail0,"TerrainDetail0");
                    p.process(TerrainDetail1,"TerrainDetail1");
                    p.process(TerrainDetail2,"TerrainDetail2");
                    p.process(TerrainDetail3,"TerrainDetail3");
                    p.process(TerrainStartHeight00,"TerrainStartHeight00");
                    p.process(TerrainStartHeight01,"TerrainStartHeight01");
                    p.process(TerrainStartHeight10,"TerrainStartHeight10");
                    p.process(TerrainStartHeight11,"TerrainStartHeight11");
                    p.process(TerrainHeightRange00,"TerrainHeightRange00");
                    p.process(TerrainHeightRange01,"TerrainHeightRange01");
                    p.process(TerrainHeightRange10,"TerrainHeightRange10");
                    p.process(TerrainHeightRange11,"TerrainHeightRange11");
                }

            };

            struct RegionInfo2Block
            {
                LLUUID RegionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionID,"RegionID");
                }

            };


            RegionInfoBlock RegionInfo;
            RegionInfo2Block RegionInfo2;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(RegionInfo,"RegionInfo");
                p.process(RegionInfo2,"RegionInfo2");
            }

        };

        struct RegionHandshakeReplyMessage
            : Message
        {
            static char const * name(){ return "RegionHandshakeReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0095ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RegionHandshakeReplyMessage>();
                }
            };


            RegionHandshakeReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , RegionInfo()
            {}

            RegionHandshakeReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , RegionInfo()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct RegionInfoBlock
            {
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Flags,"Flags");
                }

            };


            AgentDataBlock AgentData;
            RegionInfoBlock RegionInfo;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RegionInfo,"RegionInfo");
            }

        };

        struct SimulatorViewerTimeMessageMessage
            : Message
        {
            static char const * name(){ return "SimulatorViewerTimeMessage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0096ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SimulatorViewerTimeMessageMessage>();
                }
            };


            SimulatorViewerTimeMessageMessage()
            : Message(LowHeader())
            , TimeInfo()
            {}

            SimulatorViewerTimeMessageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , TimeInfo()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct TimeInfoBlock
            {
                UInt64 UsecSinceStart;
                UInt32 SecPerDay;
                UInt32 SecPerYear;
                raw::LLVector3 SunDirection;
                Real32 SunPhase;
                raw::LLVector3 SunAngVelocity;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(UsecSinceStart,"UsecSinceStart");
                    p.process(SecPerDay,"SecPerDay");
                    p.process(SecPerYear,"SecPerYear");
                    p.process(SunDirection,"SunDirection");
                    p.process(SunPhase,"SunPhase");
                    p.process(SunAngVelocity,"SunAngVelocity");
                }

            };


            TimeInfoBlock TimeInfo;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(TimeInfo,"TimeInfo");
            }

        };

        struct EnableSimulatorMessage
            : Message
        {
            static char const * name(){ return "EnableSimulator"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0097ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EnableSimulatorMessage>();
                }
            };


            EnableSimulatorMessage()
            : Message(LowHeader())
            , SimulatorInfo()
            {}

            EnableSimulatorMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , SimulatorInfo()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct SimulatorInfoBlock
            {
                UInt64 Handle;
                raw::LLIPAddress IP;
                raw::LLIPPort Port;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Handle,"Handle");
                    p.process(IP,"IP");
                    p.process(Port,"Port");
                }

            };


            SimulatorInfoBlock SimulatorInfo;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(SimulatorInfo,"SimulatorInfo");
            }

        };

        struct DisableSimulatorMessage
            : Message
        {
            static char const * name(){ return "DisableSimulator"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0098ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DisableSimulatorMessage>();
                }
            };


            DisableSimulatorMessage()
            : Message(LowHeader())
            {}

            DisableSimulatorMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            



            template<typename Processor>
            void process(Processor & p)
            {
                (void)p; // avoiding unreferenced warnings
            }

        };

        struct TransferRequestMessage
            : Message
        {
            static char const * name(){ return "TransferRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0099ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TransferRequestMessage>();
                }
            };


            TransferRequestMessage()
            : Message(LowHeader())
            , TransferInfo()
            {}

            TransferRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , TransferInfo()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct TransferInfoBlock
            {
                LLUUID TransferID;
                Int32 ChannelType;
                Int32 SourceType;
                Real32 Priority;
                raw::LLVariable Params;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransferID,"TransferID");
                    p.process(ChannelType,"ChannelType");
                    p.process(SourceType,"SourceType");
                    p.process(Priority,"Priority");
                    p.process(Params,"Params");
                }

            };


            TransferInfoBlock TransferInfo;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(TransferInfo,"TransferInfo");
            }

        };

        struct TransferInfoMessage
            : Message
        {
            static char const * name(){ return "TransferInfo"; }
            static bool const trusted = false;
            enum { id = 0xFFFF009Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TransferInfoMessage>();
                }
            };


            TransferInfoMessage()
            : Message(LowHeader())
            , TransferInfo()
            {}

            TransferInfoMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , TransferInfo()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct TransferInfoBlock
            {
                LLUUID TransferID;
                Int32 ChannelType;
                Int32 TargetType;
                Int32 Status;
                Int32 Size;
                raw::LLVariable Params;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransferID,"TransferID");
                    p.process(ChannelType,"ChannelType");
                    p.process(TargetType,"TargetType");
                    p.process(Status,"Status");
                    p.process(Size,"Size");
                    p.process(Params,"Params");
                }

            };


            TransferInfoBlock TransferInfo;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(TransferInfo,"TransferInfo");
            }

        };

        struct TransferAbortMessage
            : Message
        {
            static char const * name(){ return "TransferAbort"; }
            static bool const trusted = false;
            enum { id = 0xFFFF009Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TransferAbortMessage>();
                }
            };


            TransferAbortMessage()
            : Message(LowHeader())
            , TransferInfo()
            {}

            TransferAbortMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , TransferInfo()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct TransferInfoBlock
            {
                LLUUID TransferID;
                Int32 ChannelType;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransferID,"TransferID");
                    p.process(ChannelType,"ChannelType");
                }

            };


            TransferInfoBlock TransferInfo;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(TransferInfo,"TransferInfo");
            }

        };

        struct RequestXferMessage
            : Message
        {
            static char const * name(){ return "RequestXfer"; }
            static bool const trusted = false;
            enum { id = 0xFFFF009Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RequestXferMessage>();
                }
            };


            RequestXferMessage()
            : Message(LowHeader())
            , XferID()
            {}

            RequestXferMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , XferID()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct XferIDBlock
            {
                UInt64 ID;
                raw::LLVariable Filename;
                UInt8 FilePath;
                bool DeleteOnCompletion;
                bool UseBigPackets;
                LLUUID VFileID;
                Int16 VFileType;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(Filename,"Filename");
                    p.process(FilePath,"FilePath");
                    p.process(DeleteOnCompletion,"DeleteOnCompletion");
                    p.process(UseBigPackets,"UseBigPackets");
                    p.process(VFileID,"VFileID");
                    p.process(VFileType,"VFileType");
                }

            };


            XferIDBlock XferID;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(XferID,"XferID");
            }

        };

        struct AbortXferMessage
            : Message
        {
            static char const * name(){ return "AbortXfer"; }
            static bool const trusted = false;
            enum { id = 0xFFFF009Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AbortXferMessage>();
                }
            };


            AbortXferMessage()
            : Message(LowHeader())
            , XferID()
            {}

            AbortXferMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , XferID()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct XferIDBlock
            {
                UInt64 ID;
                Int32 Result;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(Result,"Result");
                }

            };


            XferIDBlock XferID;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(XferID,"XferID");
            }

        };

        struct AvatarAppearanceMessage
            : Message
        {
            static char const * name(){ return "AvatarAppearance"; }
            static bool const trusted = false;
            enum { id = 0xFFFF009Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarAppearanceMessage>();
                }
            };


            AvatarAppearanceMessage()
            : Message(LowHeader())
            , Sender()
            , ObjectData()
            , VisualParam()
            {}

            AvatarAppearanceMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Sender()
            , ObjectData()
            , VisualParam()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct SenderBlock
            {
                LLUUID ID;
                bool IsTrial;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(IsTrial,"IsTrial");
                }

            };

            struct ObjectDataBlock
            {
                raw::LLVariable TextureEntry;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TextureEntry,"TextureEntry");
                }

            };

            struct VisualParamBlock
            {
                UInt8 ParamValue;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ParamValue,"ParamValue");
                }

            };


            SenderBlock Sender;
            ObjectDataBlock ObjectData;
            std::vector<VisualParamBlock> VisualParam;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Sender,"Sender");
                p.process(ObjectData,"ObjectData");
                p.process(VisualParam,"VisualParam");
            }

        };

        struct SetFollowCamPropertiesMessage
            : Message
        {
            static char const * name(){ return "SetFollowCamProperties"; }
            static bool const trusted = false;
            enum { id = 0xFFFF009Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SetFollowCamPropertiesMessage>();
                }
            };


            SetFollowCamPropertiesMessage()
            : Message(LowHeader())
            , ObjectData()
            , CameraProperty()
            {}

            SetFollowCamPropertiesMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , ObjectData()
            , CameraProperty()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ObjectDataBlock
            {
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                }

            };

            struct CameraPropertyBlock
            {
                Int32 Type;
                Real32 Value;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Type,"Type");
                    p.process(Value,"Value");
                }

            };


            ObjectDataBlock ObjectData;
            std::vector<CameraPropertyBlock> CameraProperty;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ObjectData,"ObjectData");
                p.process(CameraProperty,"CameraProperty");
            }

        };

        struct ClearFollowCamPropertiesMessage
            : Message
        {
            static char const * name(){ return "ClearFollowCamProperties"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00A0ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ClearFollowCamPropertiesMessage>();
                }
            };


            ClearFollowCamPropertiesMessage()
            : Message(LowHeader())
            , ObjectData()
            {}

            ClearFollowCamPropertiesMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ObjectDataBlock
            {
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                }

            };


            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ObjectData,"ObjectData");
            }

        };

        struct RequestPayPriceMessage
            : Message
        {
            static char const * name(){ return "RequestPayPrice"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00A1ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RequestPayPriceMessage>();
                }
            };


            RequestPayPriceMessage()
            : Message(LowHeader())
            , ObjectData()
            {}

            RequestPayPriceMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ObjectDataBlock
            {
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                }

            };


            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ObjectData,"ObjectData");
            }

        };

        struct PayPriceReplyMessage
            : Message
        {
            static char const * name(){ return "PayPriceReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00A2ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<PayPriceReplyMessage>();
                }
            };


            PayPriceReplyMessage()
            : Message(LowHeader())
            , ObjectData()
            , ButtonData()
            {}

            PayPriceReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , ObjectData()
            , ButtonData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ObjectDataBlock
            {
                LLUUID ObjectID;
                Int32 DefaultPayPrice;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(DefaultPayPrice,"DefaultPayPrice");
                }

            };

            struct ButtonDataBlock
            {
                Int32 PayButton;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(PayButton,"PayButton");
                }

            };


            ObjectDataBlock ObjectData;
            std::vector<ButtonDataBlock> ButtonData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ObjectData,"ObjectData");
                p.process(ButtonData,"ButtonData");
            }

        };

        struct KickUserMessage
            : Message
        {
            static char const * name(){ return "KickUser"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00A3ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<KickUserMessage>();
                }
            };


            KickUserMessage()
            : Message(LowHeader())
            , TargetBlock()
            , UserInfo()
            {}

            KickUserMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , TargetBlock()
            , UserInfo()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct TargetBlockBlock
            {
                raw::LLIPAddress TargetIP;
                raw::LLIPPort TargetPort;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TargetIP,"TargetIP");
                    p.process(TargetPort,"TargetPort");
                }

            };

            struct UserInfoBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                raw::LLVariable Reason;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(Reason,"Reason");
                }

            };


            TargetBlockBlock TargetBlock;
            UserInfoBlock UserInfo;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(TargetBlock,"TargetBlock");
                p.process(UserInfo,"UserInfo");
            }

        };

        struct KickUserAckMessage
            : Message
        {
            static char const * name(){ return "KickUserAck"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00A4ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<KickUserAckMessage>();
                }
            };


            KickUserAckMessage()
            : Message(LowHeader())
            , UserInfo()
            {}

            KickUserAckMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , UserInfo()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct UserInfoBlock
            {
                LLUUID SessionID;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SessionID,"SessionID");
                    p.process(Flags,"Flags");
                }

            };


            UserInfoBlock UserInfo;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(UserInfo,"UserInfo");
            }

        };

        struct GodKickUserMessage
            : Message
        {
            static char const * name(){ return "GodKickUser"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00A5ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GodKickUserMessage>();
                }
            };


            GodKickUserMessage()
            : Message(LowHeader())
            , UserInfo()
            {}

            GodKickUserMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , UserInfo()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct UserInfoBlock
            {
                LLUUID GodID;
                LLUUID GodSessionID;
                LLUUID AgentID;
                UInt32 KickFlags;
                raw::LLVariable Reason;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GodID,"GodID");
                    p.process(GodSessionID,"GodSessionID");
                    p.process(AgentID,"AgentID");
                    p.process(KickFlags,"KickFlags");
                    p.process(Reason,"Reason");
                }

            };


            UserInfoBlock UserInfo;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(UserInfo,"UserInfo");
            }

        };

        struct EjectUserMessage
            : Message
        {
            static char const * name(){ return "EjectUser"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00A7ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EjectUserMessage>();
                }
            };


            EjectUserMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            EjectUserMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID TargetID;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TargetID,"TargetID");
                    p.process(Flags,"Flags");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct FreezeUserMessage
            : Message
        {
            static char const * name(){ return "FreezeUser"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00A8ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<FreezeUserMessage>();
                }
            };


            FreezeUserMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            FreezeUserMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID TargetID;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TargetID,"TargetID");
                    p.process(Flags,"Flags");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct AvatarPropertiesRequestMessage
            : Message
        {
            static char const * name(){ return "AvatarPropertiesRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00A9ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarPropertiesRequestMessage>();
                }
            };


            AvatarPropertiesRequestMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            AvatarPropertiesRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID AvatarID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(AvatarID,"AvatarID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct AvatarPropertiesReplyMessage
            : Message
        {
            static char const * name(){ return "AvatarPropertiesReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00ABul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarPropertiesReplyMessage>();
                }
            };


            AvatarPropertiesReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , PropertiesData()
            {}

            AvatarPropertiesReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , PropertiesData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID AvatarID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(AvatarID,"AvatarID");
                }

            };

            struct PropertiesDataBlock
            {
                LLUUID ImageID;
                LLUUID FLImageID;
                LLUUID PartnerID;
                raw::LLVariable AboutText;
                raw::LLVariable FLAboutText;
                raw::LLVariable BornOn;
                raw::LLVariable ProfileURL;
                raw::LLVariable CharterMember;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ImageID,"ImageID");
                    p.process(FLImageID,"FLImageID");
                    p.process(PartnerID,"PartnerID");
                    p.process(AboutText,"AboutText");
                    p.process(FLAboutText,"FLAboutText");
                    p.process(BornOn,"BornOn");
                    p.process(ProfileURL,"ProfileURL");
                    p.process(CharterMember,"CharterMember");
                    p.process(Flags,"Flags");
                }

            };


            AgentDataBlock AgentData;
            PropertiesDataBlock PropertiesData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(PropertiesData,"PropertiesData");
            }

        };

        struct AvatarInterestsReplyMessage
            : Message
        {
            static char const * name(){ return "AvatarInterestsReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00ACul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarInterestsReplyMessage>();
                }
            };


            AvatarInterestsReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , PropertiesData()
            {}

            AvatarInterestsReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , PropertiesData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID AvatarID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(AvatarID,"AvatarID");
                }

            };

            struct PropertiesDataBlock
            {
                UInt32 WantToMask;
                raw::LLVariable WantToText;
                UInt32 SkillsMask;
                raw::LLVariable SkillsText;
                raw::LLVariable LanguagesText;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(WantToMask,"WantToMask");
                    p.process(WantToText,"WantToText");
                    p.process(SkillsMask,"SkillsMask");
                    p.process(SkillsText,"SkillsText");
                    p.process(LanguagesText,"LanguagesText");
                }

            };


            AgentDataBlock AgentData;
            PropertiesDataBlock PropertiesData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(PropertiesData,"PropertiesData");
            }

        };

        struct AvatarGroupsReplyMessage
            : Message
        {
            static char const * name(){ return "AvatarGroupsReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00ADul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarGroupsReplyMessage>();
                }
            };


            AvatarGroupsReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            , NewGroupData()
            {}

            AvatarGroupsReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            , NewGroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID AvatarID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(AvatarID,"AvatarID");
                }

            };

            struct GroupDataBlock
            {
                UInt64 GroupPowers;
                bool AcceptNotices;
                raw::LLVariable GroupTitle;
                LLUUID GroupID;
                raw::LLVariable GroupName;
                LLUUID GroupInsigniaID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupPowers,"GroupPowers");
                    p.process(AcceptNotices,"AcceptNotices");
                    p.process(GroupTitle,"GroupTitle");
                    p.process(GroupID,"GroupID");
                    p.process(GroupName,"GroupName");
                    p.process(GroupInsigniaID,"GroupInsigniaID");
                }

            };

            struct NewGroupDataBlock
            {
                bool ListInProfile;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ListInProfile,"ListInProfile");
                }

            };


            AgentDataBlock AgentData;
            std::vector<GroupDataBlock> GroupData;
            NewGroupDataBlock NewGroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
                p.process(NewGroupData,"NewGroupData");
            }

        };

        struct AvatarPropertiesUpdateMessage
            : Message
        {
            static char const * name(){ return "AvatarPropertiesUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00AEul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarPropertiesUpdateMessage>();
                }
            };


            AvatarPropertiesUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            , PropertiesData()
            {}

            AvatarPropertiesUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , PropertiesData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct PropertiesDataBlock
            {
                LLUUID ImageID;
                LLUUID FLImageID;
                raw::LLVariable AboutText;
                raw::LLVariable FLAboutText;
                bool AllowPublish;
                bool MaturePublish;
                raw::LLVariable ProfileURL;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ImageID,"ImageID");
                    p.process(FLImageID,"FLImageID");
                    p.process(AboutText,"AboutText");
                    p.process(FLAboutText,"FLAboutText");
                    p.process(AllowPublish,"AllowPublish");
                    p.process(MaturePublish,"MaturePublish");
                    p.process(ProfileURL,"ProfileURL");
                }

            };


            AgentDataBlock AgentData;
            PropertiesDataBlock PropertiesData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(PropertiesData,"PropertiesData");
            }

        };

        struct AvatarInterestsUpdateMessage
            : Message
        {
            static char const * name(){ return "AvatarInterestsUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00AFul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarInterestsUpdateMessage>();
                }
            };


            AvatarInterestsUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            , PropertiesData()
            {}

            AvatarInterestsUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , PropertiesData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct PropertiesDataBlock
            {
                UInt32 WantToMask;
                raw::LLVariable WantToText;
                UInt32 SkillsMask;
                raw::LLVariable SkillsText;
                raw::LLVariable LanguagesText;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(WantToMask,"WantToMask");
                    p.process(WantToText,"WantToText");
                    p.process(SkillsMask,"SkillsMask");
                    p.process(SkillsText,"SkillsText");
                    p.process(LanguagesText,"LanguagesText");
                }

            };


            AgentDataBlock AgentData;
            PropertiesDataBlock PropertiesData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(PropertiesData,"PropertiesData");
            }

        };

        struct AvatarNotesReplyMessage
            : Message
        {
            static char const * name(){ return "AvatarNotesReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00B0ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarNotesReplyMessage>();
                }
            };


            AvatarNotesReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            AvatarNotesReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct DataBlock
            {
                LLUUID TargetID;
                raw::LLVariable Notes;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TargetID,"TargetID");
                    p.process(Notes,"Notes");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct AvatarNotesUpdateMessage
            : Message
        {
            static char const * name(){ return "AvatarNotesUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00B1ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarNotesUpdateMessage>();
                }
            };


            AvatarNotesUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            AvatarNotesUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID TargetID;
                raw::LLVariable Notes;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TargetID,"TargetID");
                    p.process(Notes,"Notes");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct AvatarPicksReplyMessage
            : Message
        {
            static char const * name(){ return "AvatarPicksReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00B2ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarPicksReplyMessage>();
                }
            };


            AvatarPicksReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            AvatarPicksReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID TargetID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(TargetID,"TargetID");
                }

            };

            struct DataBlock
            {
                LLUUID PickID;
                raw::LLVariable PickName;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(PickID,"PickID");
                    p.process(PickName,"PickName");
                }

            };


            AgentDataBlock AgentData;
            std::vector<DataBlock> Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct EventInfoRequestMessage
            : Message
        {
            static char const * name(){ return "EventInfoRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00B3ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EventInfoRequestMessage>();
                }
            };


            EventInfoRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , EventData()
            {}

            EventInfoRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , EventData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct EventDataBlock
            {
                UInt32 EventID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(EventID,"EventID");
                }

            };


            AgentDataBlock AgentData;
            EventDataBlock EventData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(EventData,"EventData");
            }

        };

        struct EventInfoReplyMessage
            : Message
        {
            static char const * name(){ return "EventInfoReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00B4ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EventInfoReplyMessage>();
                }
            };


            EventInfoReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , EventData()
            {}

            EventInfoReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , EventData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct EventDataBlock
            {
                UInt32 EventID;
                raw::LLVariable Creator;
                raw::LLVariable Name;
                raw::LLVariable Category;
                raw::LLVariable Desc;
                raw::LLVariable Date;
                UInt32 DateUTC;
                UInt32 Duration;
                UInt32 Cover;
                UInt32 Amount;
                raw::LLVariable SimName;
                raw::LLVector3d GlobalPos;
                UInt32 EventFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(EventID,"EventID");
                    p.process(Creator,"Creator");
                    p.process(Name,"Name");
                    p.process(Category,"Category");
                    p.process(Desc,"Desc");
                    p.process(Date,"Date");
                    p.process(DateUTC,"DateUTC");
                    p.process(Duration,"Duration");
                    p.process(Cover,"Cover");
                    p.process(Amount,"Amount");
                    p.process(SimName,"SimName");
                    p.process(GlobalPos,"GlobalPos");
                    p.process(EventFlags,"EventFlags");
                }

            };


            AgentDataBlock AgentData;
            EventDataBlock EventData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(EventData,"EventData");
            }

        };

        struct EventNotificationAddRequestMessage
            : Message
        {
            static char const * name(){ return "EventNotificationAddRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00B5ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EventNotificationAddRequestMessage>();
                }
            };


            EventNotificationAddRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , EventData()
            {}

            EventNotificationAddRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , EventData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct EventDataBlock
            {
                UInt32 EventID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(EventID,"EventID");
                }

            };


            AgentDataBlock AgentData;
            EventDataBlock EventData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(EventData,"EventData");
            }

        };

        struct EventNotificationRemoveRequestMessage
            : Message
        {
            static char const * name(){ return "EventNotificationRemoveRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00B6ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EventNotificationRemoveRequestMessage>();
                }
            };


            EventNotificationRemoveRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , EventData()
            {}

            EventNotificationRemoveRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , EventData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct EventDataBlock
            {
                UInt32 EventID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(EventID,"EventID");
                }

            };


            AgentDataBlock AgentData;
            EventDataBlock EventData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(EventData,"EventData");
            }

        };

        struct EventGodDeleteMessage
            : Message
        {
            static char const * name(){ return "EventGodDelete"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00B7ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EventGodDeleteMessage>();
                }
            };


            EventGodDeleteMessage()
            : Message(LowHeader())
            , AgentData()
            , EventData()
            , QueryData()
            {}

            EventGodDeleteMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , EventData()
            , QueryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct EventDataBlock
            {
                UInt32 EventID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(EventID,"EventID");
                }

            };

            struct QueryDataBlock
            {
                LLUUID QueryID;
                raw::LLVariable QueryText;
                UInt32 QueryFlags;
                Int32 QueryStart;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                    p.process(QueryText,"QueryText");
                    p.process(QueryFlags,"QueryFlags");
                    p.process(QueryStart,"QueryStart");
                }

            };


            AgentDataBlock AgentData;
            EventDataBlock EventData;
            QueryDataBlock QueryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(EventData,"EventData");
                p.process(QueryData,"QueryData");
            }

        };

        struct PickInfoReplyMessage
            : Message
        {
            static char const * name(){ return "PickInfoReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00B8ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<PickInfoReplyMessage>();
                }
            };


            PickInfoReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            PickInfoReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct DataBlock
            {
                LLUUID PickID;
                LLUUID CreatorID;
                bool TopPick;
                LLUUID ParcelID;
                raw::LLVariable Name;
                raw::LLVariable Desc;
                LLUUID SnapshotID;
                raw::LLVariable User;
                raw::LLVariable OriginalName;
                raw::LLVariable SimName;
                raw::LLVector3d PosGlobal;
                Int32 SortOrder;
                bool Enabled;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(PickID,"PickID");
                    p.process(CreatorID,"CreatorID");
                    p.process(TopPick,"TopPick");
                    p.process(ParcelID,"ParcelID");
                    p.process(Name,"Name");
                    p.process(Desc,"Desc");
                    p.process(SnapshotID,"SnapshotID");
                    p.process(User,"User");
                    p.process(OriginalName,"OriginalName");
                    p.process(SimName,"SimName");
                    p.process(PosGlobal,"PosGlobal");
                    p.process(SortOrder,"SortOrder");
                    p.process(Enabled,"Enabled");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct PickInfoUpdateMessage
            : Message
        {
            static char const * name(){ return "PickInfoUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00B9ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<PickInfoUpdateMessage>();
                }
            };


            PickInfoUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            PickInfoUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID PickID;
                LLUUID CreatorID;
                bool TopPick;
                LLUUID ParcelID;
                raw::LLVariable Name;
                raw::LLVariable Desc;
                LLUUID SnapshotID;
                raw::LLVector3d PosGlobal;
                Int32 SortOrder;
                bool Enabled;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(PickID,"PickID");
                    p.process(CreatorID,"CreatorID");
                    p.process(TopPick,"TopPick");
                    p.process(ParcelID,"ParcelID");
                    p.process(Name,"Name");
                    p.process(Desc,"Desc");
                    p.process(SnapshotID,"SnapshotID");
                    p.process(PosGlobal,"PosGlobal");
                    p.process(SortOrder,"SortOrder");
                    p.process(Enabled,"Enabled");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct PickDeleteMessage
            : Message
        {
            static char const * name(){ return "PickDelete"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00BAul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<PickDeleteMessage>();
                }
            };


            PickDeleteMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            PickDeleteMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID PickID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(PickID,"PickID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct PickGodDeleteMessage
            : Message
        {
            static char const * name(){ return "PickGodDelete"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00BBul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<PickGodDeleteMessage>();
                }
            };


            PickGodDeleteMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            PickGodDeleteMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID PickID;
                LLUUID QueryID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(PickID,"PickID");
                    p.process(QueryID,"QueryID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ScriptQuestionMessage
            : Message
        {
            static char const * name(){ return "ScriptQuestion"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00BCul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ScriptQuestionMessage>();
                }
            };


            ScriptQuestionMessage()
            : Message(LowHeader())
            , Data()
            {}

            ScriptQuestionMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlock
            {
                LLUUID TaskID;
                LLUUID ItemID;
                raw::LLVariable ObjectName;
                raw::LLVariable ObjectOwner;
                Int32 Questions;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TaskID,"TaskID");
                    p.process(ItemID,"ItemID");
                    p.process(ObjectName,"ObjectName");
                    p.process(ObjectOwner,"ObjectOwner");
                    p.process(Questions,"Questions");
                }

            };


            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Data,"Data");
            }

        };

        struct ScriptControlChangeMessage
            : Message
        {
            static char const * name(){ return "ScriptControlChange"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00BDul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ScriptControlChangeMessage>();
                }
            };


            ScriptControlChangeMessage()
            : Message(LowHeader())
            , Data()
            {}

            ScriptControlChangeMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlock
            {
                bool TakeControls;
                UInt32 Controls;
                bool PassToAgent;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TakeControls,"TakeControls");
                    p.process(Controls,"Controls");
                    p.process(PassToAgent,"PassToAgent");
                }

            };


            std::vector<DataBlock> Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Data,"Data");
            }

        };

        struct ScriptDialogMessage
            : Message
        {
            static char const * name(){ return "ScriptDialog"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00BEul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ScriptDialogMessage>();
                }
            };


            ScriptDialogMessage()
            : Message(LowHeader())
            , Data()
            , Buttons()
            {}

            ScriptDialogMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Data()
            , Buttons()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlock
            {
                LLUUID ObjectID;
                raw::LLVariable FirstName;
                raw::LLVariable LastName;
                raw::LLVariable ObjectName;
                raw::LLVariable Message;
                Int32 ChatChannel;
                LLUUID ImageID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(FirstName,"FirstName");
                    p.process(LastName,"LastName");
                    p.process(ObjectName,"ObjectName");
                    p.process(Message,"Message");
                    p.process(ChatChannel,"ChatChannel");
                    p.process(ImageID,"ImageID");
                }

            };

            struct ButtonsBlock
            {
                raw::LLVariable ButtonLabel;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ButtonLabel,"ButtonLabel");
                }

            };


            DataBlock Data;
            std::vector<ButtonsBlock> Buttons;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Data,"Data");
                p.process(Buttons,"Buttons");
            }

        };

        struct ScriptDialogReplyMessage
            : Message
        {
            static char const * name(){ return "ScriptDialogReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00BFul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ScriptDialogReplyMessage>();
                }
            };


            ScriptDialogReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ScriptDialogReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID ObjectID;
                Int32 ChatChannel;
                Int32 ButtonIndex;
                raw::LLVariable ButtonLabel;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(ChatChannel,"ChatChannel");
                    p.process(ButtonIndex,"ButtonIndex");
                    p.process(ButtonLabel,"ButtonLabel");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ForceScriptControlReleaseMessage
            : Message
        {
            static char const * name(){ return "ForceScriptControlRelease"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00C0ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ForceScriptControlReleaseMessage>();
                }
            };


            ForceScriptControlReleaseMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            ForceScriptControlReleaseMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct RevokePermissionsMessage
            : Message
        {
            static char const * name(){ return "RevokePermissions"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00C1ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RevokePermissionsMessage>();
                }
            };


            RevokePermissionsMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            RevokePermissionsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID ObjectID;
                UInt32 ObjectPermissions;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(ObjectPermissions,"ObjectPermissions");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct LoadURLMessage
            : Message
        {
            static char const * name(){ return "LoadURL"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00C2ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<LoadURLMessage>();
                }
            };


            LoadURLMessage()
            : Message(LowHeader())
            , Data()
            {}

            LoadURLMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlock
            {
                raw::LLVariable ObjectName;
                LLUUID ObjectID;
                LLUUID OwnerID;
                bool OwnerIsGroup;
                raw::LLVariable Message;
                raw::LLVariable URL;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectName,"ObjectName");
                    p.process(ObjectID,"ObjectID");
                    p.process(OwnerID,"OwnerID");
                    p.process(OwnerIsGroup,"OwnerIsGroup");
                    p.process(Message,"Message");
                    p.process(URL,"URL");
                }

            };


            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Data,"Data");
            }

        };

        struct ScriptTeleportRequestMessage
            : Message
        {
            static char const * name(){ return "ScriptTeleportRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00C3ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ScriptTeleportRequestMessage>();
                }
            };


            ScriptTeleportRequestMessage()
            : Message(LowHeader())
            , Data()
            {}

            ScriptTeleportRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlock
            {
                raw::LLVariable ObjectName;
                raw::LLVariable SimName;
                raw::LLVector3 SimPosition;
                raw::LLVector3 LookAt;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectName,"ObjectName");
                    p.process(SimName,"SimName");
                    p.process(SimPosition,"SimPosition");
                    p.process(LookAt,"LookAt");
                }

            };


            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Data,"Data");
            }

        };

        struct ParcelOverlayMessage
            : Message
        {
            static char const * name(){ return "ParcelOverlay"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00C4ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelOverlayMessage>();
                }
            };


            ParcelOverlayMessage()
            : Message(LowHeader())
            , ParcelData()
            {}

            ParcelOverlayMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ParcelDataBlock
            {
                Int32 SequenceID;
                raw::LLVariable Data;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SequenceID,"SequenceID");
                    p.process(Data,"Data");
                }

            };


            ParcelDataBlock ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ParcelData,"ParcelData");
            }

        };

        struct ParcelPropertiesRequestByIDMessage
            : Message
        {
            static char const * name(){ return "ParcelPropertiesRequestByID"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00C5ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelPropertiesRequestByIDMessage>();
                }
            };


            ParcelPropertiesRequestByIDMessage()
            : Message(LowHeader())
            , AgentData()
            , ParcelData()
            {}

            ParcelPropertiesRequestByIDMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Int32 SequenceID;
                Int32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SequenceID,"SequenceID");
                    p.process(LocalID,"LocalID");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct ParcelPropertiesUpdateMessage
            : Message
        {
            static char const * name(){ return "ParcelPropertiesUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00C6ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelPropertiesUpdateMessage>();
                }
            };


            ParcelPropertiesUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            , ParcelData()
            {}

            ParcelPropertiesUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Int32 LocalID;
                UInt32 Flags;
                UInt32 ParcelFlags;
                Int32 SalePrice;
                raw::LLVariable Name;
                raw::LLVariable Desc;
                raw::LLVariable MusicURL;
                raw::LLVariable MediaURL;
                LLUUID MediaID;
                UInt8 MediaAutoScale;
                LLUUID GroupID;
                Int32 PassPrice;
                Real32 PassHours;
                UInt8 Category;
                LLUUID AuthBuyerID;
                LLUUID SnapshotID;
                raw::LLVector3 UserLocation;
                raw::LLVector3 UserLookAt;
                UInt8 LandingType;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(Flags,"Flags");
                    p.process(ParcelFlags,"ParcelFlags");
                    p.process(SalePrice,"SalePrice");
                    p.process(Name,"Name");
                    p.process(Desc,"Desc");
                    p.process(MusicURL,"MusicURL");
                    p.process(MediaURL,"MediaURL");
                    p.process(MediaID,"MediaID");
                    p.process(MediaAutoScale,"MediaAutoScale");
                    p.process(GroupID,"GroupID");
                    p.process(PassPrice,"PassPrice");
                    p.process(PassHours,"PassHours");
                    p.process(Category,"Category");
                    p.process(AuthBuyerID,"AuthBuyerID");
                    p.process(SnapshotID,"SnapshotID");
                    p.process(UserLocation,"UserLocation");
                    p.process(UserLookAt,"UserLookAt");
                    p.process(LandingType,"LandingType");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct ParcelReturnObjectsMessage
            : Message
        {
            static char const * name(){ return "ParcelReturnObjects"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00C7ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelReturnObjectsMessage>();
                }
            };


            ParcelReturnObjectsMessage()
            : Message(LowHeader())
            , AgentData()
            , ParcelData()
            , TaskIDs()
            , OwnerIDs()
            {}

            ParcelReturnObjectsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ParcelData()
            , TaskIDs()
            , OwnerIDs()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Int32 LocalID;
                UInt32 ReturnType;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(ReturnType,"ReturnType");
                }

            };

            struct TaskIDsBlock
            {
                LLUUID TaskID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TaskID,"TaskID");
                }

            };

            struct OwnerIDsBlock
            {
                LLUUID OwnerID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(OwnerID,"OwnerID");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;
            std::vector<TaskIDsBlock> TaskIDs;
            std::vector<OwnerIDsBlock> OwnerIDs;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
                p.process(TaskIDs,"TaskIDs");
                p.process(OwnerIDs,"OwnerIDs");
            }

        };

        struct ParcelSetOtherCleanTimeMessage
            : Message
        {
            static char const * name(){ return "ParcelSetOtherCleanTime"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00C8ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelSetOtherCleanTimeMessage>();
                }
            };


            ParcelSetOtherCleanTimeMessage()
            : Message(LowHeader())
            , AgentData()
            , ParcelData()
            {}

            ParcelSetOtherCleanTimeMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Int32 LocalID;
                Int32 OtherCleanTime;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(OtherCleanTime,"OtherCleanTime");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct ParcelDisableObjectsMessage
            : Message
        {
            static char const * name(){ return "ParcelDisableObjects"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00C9ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelDisableObjectsMessage>();
                }
            };


            ParcelDisableObjectsMessage()
            : Message(LowHeader())
            , AgentData()
            , ParcelData()
            , TaskIDs()
            , OwnerIDs()
            {}

            ParcelDisableObjectsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ParcelData()
            , TaskIDs()
            , OwnerIDs()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Int32 LocalID;
                UInt32 ReturnType;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(ReturnType,"ReturnType");
                }

            };

            struct TaskIDsBlock
            {
                LLUUID TaskID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TaskID,"TaskID");
                }

            };

            struct OwnerIDsBlock
            {
                LLUUID OwnerID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(OwnerID,"OwnerID");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;
            std::vector<TaskIDsBlock> TaskIDs;
            std::vector<OwnerIDsBlock> OwnerIDs;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
                p.process(TaskIDs,"TaskIDs");
                p.process(OwnerIDs,"OwnerIDs");
            }

        };

        struct ParcelSelectObjectsMessage
            : Message
        {
            static char const * name(){ return "ParcelSelectObjects"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00CAul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelSelectObjectsMessage>();
                }
            };


            ParcelSelectObjectsMessage()
            : Message(LowHeader())
            , AgentData()
            , ParcelData()
            , ReturnIDs()
            {}

            ParcelSelectObjectsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ParcelData()
            , ReturnIDs()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Int32 LocalID;
                UInt32 ReturnType;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(ReturnType,"ReturnType");
                }

            };

            struct ReturnIDsBlock
            {
                LLUUID ReturnID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ReturnID,"ReturnID");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;
            std::vector<ReturnIDsBlock> ReturnIDs;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
                p.process(ReturnIDs,"ReturnIDs");
            }

        };

        struct EstateCovenantRequestMessage
            : Message
        {
            static char const * name(){ return "EstateCovenantRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00CBul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EstateCovenantRequestMessage>();
                }
            };


            EstateCovenantRequestMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            EstateCovenantRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct EstateCovenantReplyMessage
            : Message
        {
            static char const * name(){ return "EstateCovenantReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00CCul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EstateCovenantReplyMessage>();
                }
            };


            EstateCovenantReplyMessage()
            : Message(LowHeader())
            , Data()
            {}

            EstateCovenantReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlock
            {
                LLUUID CovenantID;
                UInt32 CovenantTimestamp;
                raw::LLVariable EstateName;
                LLUUID EstateOwnerID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(CovenantID,"CovenantID");
                    p.process(CovenantTimestamp,"CovenantTimestamp");
                    p.process(EstateName,"EstateName");
                    p.process(EstateOwnerID,"EstateOwnerID");
                }

            };


            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Data,"Data");
            }

        };

        struct ForceObjectSelectMessage
            : Message
        {
            static char const * name(){ return "ForceObjectSelect"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00CDul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ForceObjectSelectMessage>();
                }
            };


            ForceObjectSelectMessage()
            : Message(LowHeader())
            , Header()
            , Data()
            {}

            ForceObjectSelectMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Header()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct HeaderBlock
            {
                bool ResetList;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ResetList,"ResetList");
                }

            };

            struct DataBlock
            {
                UInt32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                }

            };


            HeaderBlock Header;
            std::vector<DataBlock> Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Header,"Header");
                p.process(Data,"Data");
            }

        };

        struct ParcelBuyPassMessage
            : Message
        {
            static char const * name(){ return "ParcelBuyPass"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00CEul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelBuyPassMessage>();
                }
            };


            ParcelBuyPassMessage()
            : Message(LowHeader())
            , AgentData()
            , ParcelData()
            {}

            ParcelBuyPassMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Int32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct ParcelDeedToGroupMessage
            : Message
        {
            static char const * name(){ return "ParcelDeedToGroup"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00CFul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelDeedToGroupMessage>();
                }
            };


            ParcelDeedToGroupMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ParcelDeedToGroupMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID GroupID;
                Int32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(LocalID,"LocalID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ParcelReclaimMessage
            : Message
        {
            static char const * name(){ return "ParcelReclaim"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00D0ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelReclaimMessage>();
                }
            };


            ParcelReclaimMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ParcelReclaimMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                Int32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ParcelClaimMessage
            : Message
        {
            static char const * name(){ return "ParcelClaim"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00D1ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelClaimMessage>();
                }
            };


            ParcelClaimMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            , ParcelData()
            {}

            ParcelClaimMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID GroupID;
                bool IsGroupOwned;
                bool Final;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(IsGroupOwned,"IsGroupOwned");
                    p.process(Final,"Final");
                }

            };

            struct ParcelDataBlock
            {
                Real32 West;
                Real32 South;
                Real32 East;
                Real32 North;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(West,"West");
                    p.process(South,"South");
                    p.process(East,"East");
                    p.process(North,"North");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;
            std::vector<ParcelDataBlock> ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct ParcelJoinMessage
            : Message
        {
            static char const * name(){ return "ParcelJoin"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00D2ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelJoinMessage>();
                }
            };


            ParcelJoinMessage()
            : Message(LowHeader())
            , AgentData()
            , ParcelData()
            {}

            ParcelJoinMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Real32 West;
                Real32 South;
                Real32 East;
                Real32 North;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(West,"West");
                    p.process(South,"South");
                    p.process(East,"East");
                    p.process(North,"North");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct ParcelDivideMessage
            : Message
        {
            static char const * name(){ return "ParcelDivide"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00D3ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelDivideMessage>();
                }
            };


            ParcelDivideMessage()
            : Message(LowHeader())
            , AgentData()
            , ParcelData()
            {}

            ParcelDivideMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Real32 West;
                Real32 South;
                Real32 East;
                Real32 North;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(West,"West");
                    p.process(South,"South");
                    p.process(East,"East");
                    p.process(North,"North");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct ParcelReleaseMessage
            : Message
        {
            static char const * name(){ return "ParcelRelease"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00D4ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelReleaseMessage>();
                }
            };


            ParcelReleaseMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ParcelReleaseMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                Int32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ParcelBuyMessage
            : Message
        {
            static char const * name(){ return "ParcelBuy"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00D5ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelBuyMessage>();
                }
            };


            ParcelBuyMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            , ParcelData()
            {}

            ParcelBuyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID GroupID;
                bool IsGroupOwned;
                bool RemoveContribution;
                Int32 LocalID;
                bool Final;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(IsGroupOwned,"IsGroupOwned");
                    p.process(RemoveContribution,"RemoveContribution");
                    p.process(LocalID,"LocalID");
                    p.process(Final,"Final");
                }

            };

            struct ParcelDataBlock
            {
                Int32 Price;
                Int32 Area;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Price,"Price");
                    p.process(Area,"Area");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;
            ParcelDataBlock ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct ParcelGodForceOwnerMessage
            : Message
        {
            static char const * name(){ return "ParcelGodForceOwner"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00D6ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelGodForceOwnerMessage>();
                }
            };


            ParcelGodForceOwnerMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ParcelGodForceOwnerMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID OwnerID;
                Int32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(OwnerID,"OwnerID");
                    p.process(LocalID,"LocalID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ParcelAccessListRequestMessage
            : Message
        {
            static char const * name(){ return "ParcelAccessListRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00D7ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelAccessListRequestMessage>();
                }
            };


            ParcelAccessListRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ParcelAccessListRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                Int32 SequenceID;
                UInt32 Flags;
                Int32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SequenceID,"SequenceID");
                    p.process(Flags,"Flags");
                    p.process(LocalID,"LocalID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ParcelAccessListReplyMessage
            : Message
        {
            static char const * name(){ return "ParcelAccessListReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00D8ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelAccessListReplyMessage>();
                }
            };


            ParcelAccessListReplyMessage()
            : Message(LowHeader())
            , Data()
            , List()
            {}

            ParcelAccessListReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Data()
            , List()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlock
            {
                LLUUID AgentID;
                Int32 SequenceID;
                UInt32 Flags;
                Int32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SequenceID,"SequenceID");
                    p.process(Flags,"Flags");
                    p.process(LocalID,"LocalID");
                }

            };

            struct ListBlock
            {
                LLUUID ID;
                Int32 Time;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(Time,"Time");
                    p.process(Flags,"Flags");
                }

            };


            DataBlock Data;
            std::vector<ListBlock> List;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Data,"Data");
                p.process(List,"List");
            }

        };

        struct ParcelAccessListUpdateMessage
            : Message
        {
            static char const * name(){ return "ParcelAccessListUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00D9ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelAccessListUpdateMessage>();
                }
            };


            ParcelAccessListUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            , List()
            {}

            ParcelAccessListUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            , List()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                UInt32 Flags;
                Int32 LocalID;
                LLUUID TransactionID;
                Int32 SequenceID;
                Int32 Sections;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Flags,"Flags");
                    p.process(LocalID,"LocalID");
                    p.process(TransactionID,"TransactionID");
                    p.process(SequenceID,"SequenceID");
                    p.process(Sections,"Sections");
                }

            };

            struct ListBlock
            {
                LLUUID ID;
                Int32 Time;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(Time,"Time");
                    p.process(Flags,"Flags");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;
            std::vector<ListBlock> List;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
                p.process(List,"List");
            }

        };

        struct ParcelDwellRequestMessage
            : Message
        {
            static char const * name(){ return "ParcelDwellRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00DAul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelDwellRequestMessage>();
                }
            };


            ParcelDwellRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ParcelDwellRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                Int32 LocalID;
                LLUUID ParcelID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(ParcelID,"ParcelID");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ParcelDwellReplyMessage
            : Message
        {
            static char const * name(){ return "ParcelDwellReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00DBul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelDwellReplyMessage>();
                }
            };


            ParcelDwellReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ParcelDwellReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct DataBlock
            {
                Int32 LocalID;
                LLUUID ParcelID;
                Real32 Dwell;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(ParcelID,"ParcelID");
                    p.process(Dwell,"Dwell");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ParcelGodMarkAsContentMessage
            : Message
        {
            static char const * name(){ return "ParcelGodMarkAsContent"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00E3ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelGodMarkAsContentMessage>();
                }
            };


            ParcelGodMarkAsContentMessage()
            : Message(LowHeader())
            , AgentData()
            , ParcelData()
            {}

            ParcelGodMarkAsContentMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Int32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct ViewerStartAuctionMessage
            : Message
        {
            static char const * name(){ return "ViewerStartAuction"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00E4ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ViewerStartAuctionMessage>();
                }
            };


            ViewerStartAuctionMessage()
            : Message(LowHeader())
            , AgentData()
            , ParcelData()
            {}

            ViewerStartAuctionMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Int32 LocalID;
                LLUUID SnapshotID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(SnapshotID,"SnapshotID");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct UUIDNameRequestMessage
            : Message
        {
            static char const * name(){ return "UUIDNameRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00EBul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UUIDNameRequestMessage>();
                }
            };


            UUIDNameRequestMessage()
            : Message(LowHeader())
            , UUIDNameBlock()
            {}

            UUIDNameRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , UUIDNameBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct UUIDNameBlockBlock
            {
                LLUUID ID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                }

            };


            std::vector<UUIDNameBlockBlock> UUIDNameBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(UUIDNameBlock,"UUIDNameBlock");
            }

        };

        struct UUIDNameReplyMessage
            : Message
        {
            static char const * name(){ return "UUIDNameReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00ECul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UUIDNameReplyMessage>();
                }
            };


            UUIDNameReplyMessage()
            : Message(LowHeader())
            , UUIDNameBlock()
            {}

            UUIDNameReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , UUIDNameBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct UUIDNameBlockBlock
            {
                LLUUID ID;
                raw::LLVariable FirstName;
                raw::LLVariable LastName;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(FirstName,"FirstName");
                    p.process(LastName,"LastName");
                }

            };


            std::vector<UUIDNameBlockBlock> UUIDNameBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(UUIDNameBlock,"UUIDNameBlock");
            }

        };

        struct UUIDGroupNameRequestMessage
            : Message
        {
            static char const * name(){ return "UUIDGroupNameRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00EDul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UUIDGroupNameRequestMessage>();
                }
            };


            UUIDGroupNameRequestMessage()
            : Message(LowHeader())
            , UUIDNameBlock()
            {}

            UUIDGroupNameRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , UUIDNameBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct UUIDNameBlockBlock
            {
                LLUUID ID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                }

            };


            std::vector<UUIDNameBlockBlock> UUIDNameBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(UUIDNameBlock,"UUIDNameBlock");
            }

        };

        struct UUIDGroupNameReplyMessage
            : Message
        {
            static char const * name(){ return "UUIDGroupNameReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00EEul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UUIDGroupNameReplyMessage>();
                }
            };


            UUIDGroupNameReplyMessage()
            : Message(LowHeader())
            , UUIDNameBlock()
            {}

            UUIDGroupNameReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , UUIDNameBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct UUIDNameBlockBlock
            {
                LLUUID ID;
                raw::LLVariable GroupName;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(GroupName,"GroupName");
                }

            };


            std::vector<UUIDNameBlockBlock> UUIDNameBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(UUIDNameBlock,"UUIDNameBlock");
            }

        };

        struct ChildAgentDyingMessage
            : Message
        {
            static char const * name(){ return "ChildAgentDying"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00F0ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ChildAgentDyingMessage>();
                }
            };


            ChildAgentDyingMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            ChildAgentDyingMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct ChildAgentUnknownMessage
            : Message
        {
            static char const * name(){ return "ChildAgentUnknown"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00F1ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ChildAgentUnknownMessage>();
                }
            };


            ChildAgentUnknownMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            ChildAgentUnknownMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct GetScriptRunningMessage
            : Message
        {
            static char const * name(){ return "GetScriptRunning"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00F3ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GetScriptRunningMessage>();
                }
            };


            GetScriptRunningMessage()
            : Message(LowHeader())
            , Script()
            {}

            GetScriptRunningMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Script()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ScriptBlock
            {
                LLUUID ObjectID;
                LLUUID ItemID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(ItemID,"ItemID");
                }

            };


            ScriptBlock Script;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Script,"Script");
            }

        };

        struct ScriptRunningReplyMessage
            : Message
        {
            static char const * name(){ return "ScriptRunningReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00F4ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ScriptRunningReplyMessage>();
                }
            };


            ScriptRunningReplyMessage()
            : Message(LowHeader())
            , Script()
            {}

            ScriptRunningReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Script()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ScriptBlock
            {
                LLUUID ObjectID;
                LLUUID ItemID;
                bool Running;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(ItemID,"ItemID");
                    p.process(Running,"Running");
                }

            };


            ScriptBlock Script;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Script,"Script");
            }

        };

        struct SetScriptRunningMessage
            : Message
        {
            static char const * name(){ return "SetScriptRunning"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00F5ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SetScriptRunningMessage>();
                }
            };


            SetScriptRunningMessage()
            : Message(LowHeader())
            , AgentData()
            , Script()
            {}

            SetScriptRunningMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Script()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ScriptBlock
            {
                LLUUID ObjectID;
                LLUUID ItemID;
                bool Running;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(ItemID,"ItemID");
                    p.process(Running,"Running");
                }

            };


            AgentDataBlock AgentData;
            ScriptBlock Script;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Script,"Script");
            }

        };

        struct ScriptResetMessage
            : Message
        {
            static char const * name(){ return "ScriptReset"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00F6ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ScriptResetMessage>();
                }
            };


            ScriptResetMessage()
            : Message(LowHeader())
            , AgentData()
            , Script()
            {}

            ScriptResetMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Script()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ScriptBlock
            {
                LLUUID ObjectID;
                LLUUID ItemID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(ItemID,"ItemID");
                }

            };


            AgentDataBlock AgentData;
            ScriptBlock Script;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Script,"Script");
            }

        };

        struct ScriptSensorRequestMessage
            : Message
        {
            static char const * name(){ return "ScriptSensorRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00F7ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ScriptSensorRequestMessage>();
                }
            };


            ScriptSensorRequestMessage()
            : Message(LowHeader())
            , Requester()
            {}

            ScriptSensorRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Requester()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct RequesterBlock
            {
                LLUUID SourceID;
                LLUUID RequestID;
                LLUUID SearchID;
                raw::LLVector3 SearchPos;
                raw::LLQuaternion SearchDir;
                raw::LLVariable SearchName;
                Int32 Type;
                Real32 Range;
                Real32 Arc;
                UInt64 RegionHandle;
                UInt8 SearchRegions;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SourceID,"SourceID");
                    p.process(RequestID,"RequestID");
                    p.process(SearchID,"SearchID");
                    p.process(SearchPos,"SearchPos");
                    p.process(SearchDir,"SearchDir");
                    p.process(SearchName,"SearchName");
                    p.process(Type,"Type");
                    p.process(Range,"Range");
                    p.process(Arc,"Arc");
                    p.process(RegionHandle,"RegionHandle");
                    p.process(SearchRegions,"SearchRegions");
                }

            };


            RequesterBlock Requester;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Requester,"Requester");
            }

        };

        struct ScriptSensorReplyMessage
            : Message
        {
            static char const * name(){ return "ScriptSensorReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00F8ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ScriptSensorReplyMessage>();
                }
            };


            ScriptSensorReplyMessage()
            : Message(LowHeader())
            , Requester()
            , SensedData()
            {}

            ScriptSensorReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Requester()
            , SensedData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct RequesterBlock
            {
                LLUUID SourceID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SourceID,"SourceID");
                }

            };

            struct SensedDataBlock
            {
                LLUUID ObjectID;
                LLUUID OwnerID;
                LLUUID GroupID;
                raw::LLVector3 Position;
                raw::LLVector3 Velocity;
                raw::LLQuaternion Rotation;
                raw::LLVariable Name;
                Int32 Type;
                Real32 Range;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(OwnerID,"OwnerID");
                    p.process(GroupID,"GroupID");
                    p.process(Position,"Position");
                    p.process(Velocity,"Velocity");
                    p.process(Rotation,"Rotation");
                    p.process(Name,"Name");
                    p.process(Type,"Type");
                    p.process(Range,"Range");
                }

            };


            RequesterBlock Requester;
            std::vector<SensedDataBlock> SensedData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Requester,"Requester");
                p.process(SensedData,"SensedData");
            }

        };

        struct CompleteAgentMovementMessage
            : Message
        {
            static char const * name(){ return "CompleteAgentMovement"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00F9ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CompleteAgentMovementMessage>();
                }
            };


            CompleteAgentMovementMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            CompleteAgentMovementMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 CircuitCode;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(CircuitCode,"CircuitCode");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct AgentMovementCompleteMessage
            : Message
        {
            static char const * name(){ return "AgentMovementComplete"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00FAul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentMovementCompleteMessage>();
                }
            };


            AgentMovementCompleteMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            , SimData()
            {}

            AgentMovementCompleteMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            , SimData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                raw::LLVector3 Position;
                raw::LLVector3 LookAt;
                UInt64 RegionHandle;
                UInt32 Timestamp;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Position,"Position");
                    p.process(LookAt,"LookAt");
                    p.process(RegionHandle,"RegionHandle");
                    p.process(Timestamp,"Timestamp");
                }

            };

            struct SimDataBlock
            {
                raw::LLVariable ChannelVersion;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ChannelVersion,"ChannelVersion");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;
            SimDataBlock SimData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
                p.process(SimData,"SimData");
            }

        };

        struct LogoutRequestMessage
            : Message
        {
            static char const * name(){ return "LogoutRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00FCul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<LogoutRequestMessage>();
                }
            };


            LogoutRequestMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            LogoutRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct LogoutReplyMessage
            : Message
        {
            static char const * name(){ return "LogoutReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00FDul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<LogoutReplyMessage>();
                }
            };


            LogoutReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            LogoutReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID ItemID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<InventoryDataBlock> InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct ImprovedInstantMessageMessage
            : Message
        {
            static char const * name(){ return "ImprovedInstantMessage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00FEul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ImprovedInstantMessageMessage>();
                }
            };


            ImprovedInstantMessageMessage()
            : Message(LowHeader())
            , AgentData()
            , MessageBlock()
            {}

            ImprovedInstantMessageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MessageBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct MessageBlockBlock
            {
                bool FromGroup;
                LLUUID ToAgentID;
                UInt32 ParentEstateID;
                LLUUID RegionID;
                raw::LLVector3 Position;
                UInt8 Offline;
                UInt8 Dialog;
                LLUUID ID;
                UInt32 Timestamp;
                raw::LLVariable FromAgentName;
                raw::LLVariable Message;
                raw::LLVariable BinaryBucket;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FromGroup,"FromGroup");
                    p.process(ToAgentID,"ToAgentID");
                    p.process(ParentEstateID,"ParentEstateID");
                    p.process(RegionID,"RegionID");
                    p.process(Position,"Position");
                    p.process(Offline,"Offline");
                    p.process(Dialog,"Dialog");
                    p.process(ID,"ID");
                    p.process(Timestamp,"Timestamp");
                    p.process(FromAgentName,"FromAgentName");
                    p.process(Message,"Message");
                    p.process(BinaryBucket,"BinaryBucket");
                }

            };


            AgentDataBlock AgentData;
            MessageBlockBlock MessageBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MessageBlock,"MessageBlock");
            }

        };

        struct RetrieveInstantMessagesMessage
            : Message
        {
            static char const * name(){ return "RetrieveInstantMessages"; }
            static bool const trusted = false;
            enum { id = 0xFFFF00FFul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RetrieveInstantMessagesMessage>();
                }
            };


            RetrieveInstantMessagesMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            RetrieveInstantMessagesMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct FindAgentMessage
            : Message
        {
            static char const * name(){ return "FindAgent"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0100ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<FindAgentMessage>();
                }
            };


            FindAgentMessage()
            : Message(LowHeader())
            , AgentBlock()
            , LocationBlock()
            {}

            FindAgentMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentBlock()
            , LocationBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentBlockBlock
            {
                LLUUID Hunter;
                LLUUID Prey;
                raw::LLIPAddress SpaceIP;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Hunter,"Hunter");
                    p.process(Prey,"Prey");
                    p.process(SpaceIP,"SpaceIP");
                }

            };

            struct LocationBlockBlock
            {
                Real64 GlobalX;
                Real64 GlobalY;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GlobalX,"GlobalX");
                    p.process(GlobalY,"GlobalY");
                }

            };


            AgentBlockBlock AgentBlock;
            std::vector<LocationBlockBlock> LocationBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentBlock,"AgentBlock");
                p.process(LocationBlock,"LocationBlock");
            }

        };

        struct RequestGodlikePowersMessage
            : Message
        {
            static char const * name(){ return "RequestGodlikePowers"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0101ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RequestGodlikePowersMessage>();
                }
            };


            RequestGodlikePowersMessage()
            : Message(LowHeader())
            , AgentData()
            , RequestBlock()
            {}

            RequestGodlikePowersMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , RequestBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct RequestBlockBlock
            {
                bool Godlike;
                LLUUID Token;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Godlike,"Godlike");
                    p.process(Token,"Token");
                }

            };


            AgentDataBlock AgentData;
            RequestBlockBlock RequestBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RequestBlock,"RequestBlock");
            }

        };

        struct GrantGodlikePowersMessage
            : Message
        {
            static char const * name(){ return "GrantGodlikePowers"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0102ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GrantGodlikePowersMessage>();
                }
            };


            GrantGodlikePowersMessage()
            : Message(LowHeader())
            , AgentData()
            , GrantData()
            {}

            GrantGodlikePowersMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GrantData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GrantDataBlock
            {
                UInt8 GodLevel;
                LLUUID Token;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GodLevel,"GodLevel");
                    p.process(Token,"Token");
                }

            };


            AgentDataBlock AgentData;
            GrantDataBlock GrantData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GrantData,"GrantData");
            }

        };

        struct GodlikeMessageMessage
            : Message
        {
            static char const * name(){ return "GodlikeMessage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0103ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GodlikeMessageMessage>();
                }
            };


            GodlikeMessageMessage()
            : Message(LowHeader())
            , AgentData()
            , MethodData()
            , ParamList()
            {}

            GodlikeMessageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MethodData()
            , ParamList()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(TransactionID,"TransactionID");
                }

            };

            struct MethodDataBlock
            {
                raw::LLVariable Method;
                LLUUID Invoice;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Method,"Method");
                    p.process(Invoice,"Invoice");
                }

            };

            struct ParamListBlock
            {
                raw::LLVariable Parameter;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Parameter,"Parameter");
                }

            };


            AgentDataBlock AgentData;
            MethodDataBlock MethodData;
            std::vector<ParamListBlock> ParamList;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MethodData,"MethodData");
                p.process(ParamList,"ParamList");
            }

        };

        struct EstateOwnerMessageMessage
            : Message
        {
            static char const * name(){ return "EstateOwnerMessage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0104ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EstateOwnerMessageMessage>();
                }
            };


            EstateOwnerMessageMessage()
            : Message(LowHeader())
            , AgentData()
            , MethodData()
            , ParamList()
            {}

            EstateOwnerMessageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MethodData()
            , ParamList()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(TransactionID,"TransactionID");
                }

            };

            struct MethodDataBlock
            {
                raw::LLVariable Method;
                LLUUID Invoice;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Method,"Method");
                    p.process(Invoice,"Invoice");
                }

            };

            struct ParamListBlock
            {
                raw::LLVariable Parameter;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Parameter,"Parameter");
                }

            };


            AgentDataBlock AgentData;
            MethodDataBlock MethodData;
            std::vector<ParamListBlock> ParamList;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MethodData,"MethodData");
                p.process(ParamList,"ParamList");
            }

        };

        struct GenericMessageMessage
            : Message
        {
            static char const * name(){ return "GenericMessage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0105ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GenericMessageMessage>();
                }
            };


            GenericMessageMessage()
            : Message(LowHeader())
            , AgentData()
            , MethodData()
            , ParamList()
            {}

            GenericMessageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MethodData()
            , ParamList()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(TransactionID,"TransactionID");
                }

            };

            struct MethodDataBlock
            {
                raw::LLVariable Method;
                LLUUID Invoice;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Method,"Method");
                    p.process(Invoice,"Invoice");
                }

            };

            struct ParamListBlock
            {
                raw::LLVariable Parameter;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Parameter,"Parameter");
                }

            };


            AgentDataBlock AgentData;
            MethodDataBlock MethodData;
            std::vector<ParamListBlock> ParamList;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MethodData,"MethodData");
                p.process(ParamList,"ParamList");
            }

        };

        struct MuteListRequestMessage
            : Message
        {
            static char const * name(){ return "MuteListRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0106ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MuteListRequestMessage>();
                }
            };


            MuteListRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , MuteData()
            {}

            MuteListRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MuteData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct MuteDataBlock
            {
                UInt32 MuteCRC;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(MuteCRC,"MuteCRC");
                }

            };


            AgentDataBlock AgentData;
            MuteDataBlock MuteData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MuteData,"MuteData");
            }

        };

        struct UpdateMuteListEntryMessage
            : Message
        {
            static char const * name(){ return "UpdateMuteListEntry"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0107ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UpdateMuteListEntryMessage>();
                }
            };


            UpdateMuteListEntryMessage()
            : Message(LowHeader())
            , AgentData()
            , MuteData()
            {}

            UpdateMuteListEntryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MuteData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct MuteDataBlock
            {
                LLUUID MuteID;
                raw::LLVariable MuteName;
                Int32 MuteType;
                UInt32 MuteFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(MuteID,"MuteID");
                    p.process(MuteName,"MuteName");
                    p.process(MuteType,"MuteType");
                    p.process(MuteFlags,"MuteFlags");
                }

            };


            AgentDataBlock AgentData;
            MuteDataBlock MuteData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MuteData,"MuteData");
            }

        };

        struct RemoveMuteListEntryMessage
            : Message
        {
            static char const * name(){ return "RemoveMuteListEntry"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0108ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RemoveMuteListEntryMessage>();
                }
            };


            RemoveMuteListEntryMessage()
            : Message(LowHeader())
            , AgentData()
            , MuteData()
            {}

            RemoveMuteListEntryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MuteData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct MuteDataBlock
            {
                LLUUID MuteID;
                raw::LLVariable MuteName;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(MuteID,"MuteID");
                    p.process(MuteName,"MuteName");
                }

            };


            AgentDataBlock AgentData;
            MuteDataBlock MuteData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MuteData,"MuteData");
            }

        };

        struct CopyInventoryFromNotecardMessage
            : Message
        {
            static char const * name(){ return "CopyInventoryFromNotecard"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0109ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CopyInventoryFromNotecardMessage>();
                }
            };


            CopyInventoryFromNotecardMessage()
            : Message(LowHeader())
            , AgentData()
            , NotecardData()
            , InventoryData()
            {}

            CopyInventoryFromNotecardMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , NotecardData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct NotecardDataBlock
            {
                LLUUID NotecardItemID;
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(NotecardItemID,"NotecardItemID");
                    p.process(ObjectID,"ObjectID");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID ItemID;
                LLUUID FolderID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(FolderID,"FolderID");
                }

            };


            AgentDataBlock AgentData;
            NotecardDataBlock NotecardData;
            std::vector<InventoryDataBlock> InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(NotecardData,"NotecardData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct UpdateInventoryItemMessage
            : Message
        {
            static char const * name(){ return "UpdateInventoryItem"; }
            static bool const trusted = false;
            enum { id = 0xFFFF010Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UpdateInventoryItemMessage>();
                }
            };


            UpdateInventoryItemMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            UpdateInventoryItemMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(TransactionID,"TransactionID");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID ItemID;
                LLUUID FolderID;
                UInt32 CallbackID;
                LLUUID CreatorID;
                LLUUID OwnerID;
                LLUUID GroupID;
                UInt32 BaseMask;
                UInt32 OwnerMask;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;
                bool GroupOwned;
                LLUUID TransactionID;
                Int8 Type;
                Int8 InvType;
                UInt32 Flags;
                UInt8 SaleType;
                Int32 SalePrice;
                raw::LLVariable Name;
                raw::LLVariable Description;
                Int32 CreationDate;
                UInt32 CRC;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(FolderID,"FolderID");
                    p.process(CallbackID,"CallbackID");
                    p.process(CreatorID,"CreatorID");
                    p.process(OwnerID,"OwnerID");
                    p.process(GroupID,"GroupID");
                    p.process(BaseMask,"BaseMask");
                    p.process(OwnerMask,"OwnerMask");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(GroupOwned,"GroupOwned");
                    p.process(TransactionID,"TransactionID");
                    p.process(Type,"Type");
                    p.process(InvType,"InvType");
                    p.process(Flags,"Flags");
                    p.process(SaleType,"SaleType");
                    p.process(SalePrice,"SalePrice");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                    p.process(CreationDate,"CreationDate");
                    p.process(CRC,"CRC");
                }

            };


            AgentDataBlock AgentData;
            std::vector<InventoryDataBlock> InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct UpdateCreateInventoryItemMessage
            : Message
        {
            static char const * name(){ return "UpdateCreateInventoryItem"; }
            static bool const trusted = false;
            enum { id = 0xFFFF010Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UpdateCreateInventoryItemMessage>();
                }
            };


            UpdateCreateInventoryItemMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            UpdateCreateInventoryItemMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                bool SimApproved;
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SimApproved,"SimApproved");
                    p.process(TransactionID,"TransactionID");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID ItemID;
                LLUUID FolderID;
                UInt32 CallbackID;
                LLUUID CreatorID;
                LLUUID OwnerID;
                LLUUID GroupID;
                UInt32 BaseMask;
                UInt32 OwnerMask;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;
                bool GroupOwned;
                LLUUID AssetID;
                Int8 Type;
                Int8 InvType;
                UInt32 Flags;
                UInt8 SaleType;
                Int32 SalePrice;
                raw::LLVariable Name;
                raw::LLVariable Description;
                Int32 CreationDate;
                UInt32 CRC;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(FolderID,"FolderID");
                    p.process(CallbackID,"CallbackID");
                    p.process(CreatorID,"CreatorID");
                    p.process(OwnerID,"OwnerID");
                    p.process(GroupID,"GroupID");
                    p.process(BaseMask,"BaseMask");
                    p.process(OwnerMask,"OwnerMask");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(GroupOwned,"GroupOwned");
                    p.process(AssetID,"AssetID");
                    p.process(Type,"Type");
                    p.process(InvType,"InvType");
                    p.process(Flags,"Flags");
                    p.process(SaleType,"SaleType");
                    p.process(SalePrice,"SalePrice");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                    p.process(CreationDate,"CreationDate");
                    p.process(CRC,"CRC");
                }

            };


            AgentDataBlock AgentData;
            std::vector<InventoryDataBlock> InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct MoveInventoryItemMessage
            : Message
        {
            static char const * name(){ return "MoveInventoryItem"; }
            static bool const trusted = false;
            enum { id = 0xFFFF010Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MoveInventoryItemMessage>();
                }
            };


            MoveInventoryItemMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            MoveInventoryItemMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                bool Stamp;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(Stamp,"Stamp");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID ItemID;
                LLUUID FolderID;
                raw::LLVariable NewName;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(FolderID,"FolderID");
                    p.process(NewName,"NewName");
                }

            };


            AgentDataBlock AgentData;
            std::vector<InventoryDataBlock> InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct CopyInventoryItemMessage
            : Message
        {
            static char const * name(){ return "CopyInventoryItem"; }
            static bool const trusted = false;
            enum { id = 0xFFFF010Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CopyInventoryItemMessage>();
                }
            };


            CopyInventoryItemMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            CopyInventoryItemMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InventoryDataBlock
            {
                UInt32 CallbackID;
                LLUUID OldAgentID;
                LLUUID OldItemID;
                LLUUID NewFolderID;
                raw::LLVariable NewName;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(CallbackID,"CallbackID");
                    p.process(OldAgentID,"OldAgentID");
                    p.process(OldItemID,"OldItemID");
                    p.process(NewFolderID,"NewFolderID");
                    p.process(NewName,"NewName");
                }

            };


            AgentDataBlock AgentData;
            std::vector<InventoryDataBlock> InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct RemoveInventoryItemMessage
            : Message
        {
            static char const * name(){ return "RemoveInventoryItem"; }
            static bool const trusted = false;
            enum { id = 0xFFFF010Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RemoveInventoryItemMessage>();
                }
            };


            RemoveInventoryItemMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            RemoveInventoryItemMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID ItemID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<InventoryDataBlock> InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct ChangeInventoryItemFlagsMessage
            : Message
        {
            static char const * name(){ return "ChangeInventoryItemFlags"; }
            static bool const trusted = false;
            enum { id = 0xFFFF010Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ChangeInventoryItemFlagsMessage>();
                }
            };


            ChangeInventoryItemFlagsMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            ChangeInventoryItemFlagsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID ItemID;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(Flags,"Flags");
                }

            };


            AgentDataBlock AgentData;
            std::vector<InventoryDataBlock> InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct SaveAssetIntoInventoryMessage
            : Message
        {
            static char const * name(){ return "SaveAssetIntoInventory"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0110ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SaveAssetIntoInventoryMessage>();
                }
            };


            SaveAssetIntoInventoryMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            SaveAssetIntoInventoryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID ItemID;
                LLUUID NewAssetID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(NewAssetID,"NewAssetID");
                }

            };


            AgentDataBlock AgentData;
            InventoryDataBlock InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct CreateInventoryFolderMessage
            : Message
        {
            static char const * name(){ return "CreateInventoryFolder"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0111ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CreateInventoryFolderMessage>();
                }
            };


            CreateInventoryFolderMessage()
            : Message(LowHeader())
            , AgentData()
            , FolderData()
            {}

            CreateInventoryFolderMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , FolderData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct FolderDataBlock
            {
                LLUUID FolderID;
                LLUUID ParentID;
                Int8 Type;
                raw::LLVariable Name;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FolderID,"FolderID");
                    p.process(ParentID,"ParentID");
                    p.process(Type,"Type");
                    p.process(Name,"Name");
                }

            };


            AgentDataBlock AgentData;
            FolderDataBlock FolderData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(FolderData,"FolderData");
            }

        };

        struct UpdateInventoryFolderMessage
            : Message
        {
            static char const * name(){ return "UpdateInventoryFolder"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0112ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UpdateInventoryFolderMessage>();
                }
            };


            UpdateInventoryFolderMessage()
            : Message(LowHeader())
            , AgentData()
            , FolderData()
            {}

            UpdateInventoryFolderMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , FolderData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct FolderDataBlock
            {
                LLUUID FolderID;
                LLUUID ParentID;
                Int8 Type;
                raw::LLVariable Name;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FolderID,"FolderID");
                    p.process(ParentID,"ParentID");
                    p.process(Type,"Type");
                    p.process(Name,"Name");
                }

            };


            AgentDataBlock AgentData;
            std::vector<FolderDataBlock> FolderData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(FolderData,"FolderData");
            }

        };

        struct MoveInventoryFolderMessage
            : Message
        {
            static char const * name(){ return "MoveInventoryFolder"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0113ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MoveInventoryFolderMessage>();
                }
            };


            MoveInventoryFolderMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            MoveInventoryFolderMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                bool Stamp;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(Stamp,"Stamp");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID FolderID;
                LLUUID ParentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FolderID,"FolderID");
                    p.process(ParentID,"ParentID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<InventoryDataBlock> InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct RemoveInventoryFolderMessage
            : Message
        {
            static char const * name(){ return "RemoveInventoryFolder"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0114ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RemoveInventoryFolderMessage>();
                }
            };


            RemoveInventoryFolderMessage()
            : Message(LowHeader())
            , AgentData()
            , FolderData()
            {}

            RemoveInventoryFolderMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , FolderData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct FolderDataBlock
            {
                LLUUID FolderID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FolderID,"FolderID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<FolderDataBlock> FolderData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(FolderData,"FolderData");
            }

        };

        struct FetchInventoryDescendentsMessage
            : Message
        {
            static char const * name(){ return "FetchInventoryDescendents"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0115ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<FetchInventoryDescendentsMessage>();
                }
            };


            FetchInventoryDescendentsMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            FetchInventoryDescendentsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID FolderID;
                LLUUID OwnerID;
                Int32 SortOrder;
                bool FetchFolders;
                bool FetchItems;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FolderID,"FolderID");
                    p.process(OwnerID,"OwnerID");
                    p.process(SortOrder,"SortOrder");
                    p.process(FetchFolders,"FetchFolders");
                    p.process(FetchItems,"FetchItems");
                }

            };


            AgentDataBlock AgentData;
            InventoryDataBlock InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct InventoryDescendentsMessage
            : Message
        {
            static char const * name(){ return "InventoryDescendents"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0116ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<InventoryDescendentsMessage>();
                }
            };


            InventoryDescendentsMessage()
            : Message(LowHeader())
            , AgentData()
            , FolderData()
            , ItemData()
            {}

            InventoryDescendentsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , FolderData()
            , ItemData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID FolderID;
                LLUUID OwnerID;
                Int32 Version;
                Int32 Descendents;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(FolderID,"FolderID");
                    p.process(OwnerID,"OwnerID");
                    p.process(Version,"Version");
                    p.process(Descendents,"Descendents");
                }

            };

            struct FolderDataBlock
            {
                LLUUID FolderID;
                LLUUID ParentID;
                Int8 Type;
                raw::LLVariable Name;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FolderID,"FolderID");
                    p.process(ParentID,"ParentID");
                    p.process(Type,"Type");
                    p.process(Name,"Name");
                }

            };

            struct ItemDataBlock
            {
                LLUUID ItemID;
                LLUUID FolderID;
                LLUUID CreatorID;
                LLUUID OwnerID;
                LLUUID GroupID;
                UInt32 BaseMask;
                UInt32 OwnerMask;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;
                bool GroupOwned;
                LLUUID AssetID;
                Int8 Type;
                Int8 InvType;
                UInt32 Flags;
                UInt8 SaleType;
                Int32 SalePrice;
                raw::LLVariable Name;
                raw::LLVariable Description;
                Int32 CreationDate;
                UInt32 CRC;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(FolderID,"FolderID");
                    p.process(CreatorID,"CreatorID");
                    p.process(OwnerID,"OwnerID");
                    p.process(GroupID,"GroupID");
                    p.process(BaseMask,"BaseMask");
                    p.process(OwnerMask,"OwnerMask");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(GroupOwned,"GroupOwned");
                    p.process(AssetID,"AssetID");
                    p.process(Type,"Type");
                    p.process(InvType,"InvType");
                    p.process(Flags,"Flags");
                    p.process(SaleType,"SaleType");
                    p.process(SalePrice,"SalePrice");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                    p.process(CreationDate,"CreationDate");
                    p.process(CRC,"CRC");
                }

            };


            AgentDataBlock AgentData;
            std::vector<FolderDataBlock> FolderData;
            std::vector<ItemDataBlock> ItemData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(FolderData,"FolderData");
                p.process(ItemData,"ItemData");
            }

        };

        struct FetchInventoryMessage
            : Message
        {
            static char const * name(){ return "FetchInventory"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0117ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<FetchInventoryMessage>();
                }
            };


            FetchInventoryMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            FetchInventoryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID OwnerID;
                LLUUID ItemID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(OwnerID,"OwnerID");
                    p.process(ItemID,"ItemID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<InventoryDataBlock> InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct FetchInventoryReplyMessage
            : Message
        {
            static char const * name(){ return "FetchInventoryReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0118ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<FetchInventoryReplyMessage>();
                }
            };


            FetchInventoryReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            FetchInventoryReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID ItemID;
                LLUUID FolderID;
                LLUUID CreatorID;
                LLUUID OwnerID;
                LLUUID GroupID;
                UInt32 BaseMask;
                UInt32 OwnerMask;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;
                bool GroupOwned;
                LLUUID AssetID;
                Int8 Type;
                Int8 InvType;
                UInt32 Flags;
                UInt8 SaleType;
                Int32 SalePrice;
                raw::LLVariable Name;
                raw::LLVariable Description;
                Int32 CreationDate;
                UInt32 CRC;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(FolderID,"FolderID");
                    p.process(CreatorID,"CreatorID");
                    p.process(OwnerID,"OwnerID");
                    p.process(GroupID,"GroupID");
                    p.process(BaseMask,"BaseMask");
                    p.process(OwnerMask,"OwnerMask");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(GroupOwned,"GroupOwned");
                    p.process(AssetID,"AssetID");
                    p.process(Type,"Type");
                    p.process(InvType,"InvType");
                    p.process(Flags,"Flags");
                    p.process(SaleType,"SaleType");
                    p.process(SalePrice,"SalePrice");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                    p.process(CreationDate,"CreationDate");
                    p.process(CRC,"CRC");
                }

            };


            AgentDataBlock AgentData;
            std::vector<InventoryDataBlock> InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct BulkUpdateInventoryMessage
            : Message
        {
            static char const * name(){ return "BulkUpdateInventory"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0119ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<BulkUpdateInventoryMessage>();
                }
            };


            BulkUpdateInventoryMessage()
            : Message(LowHeader())
            , AgentData()
            , FolderData()
            , ItemData()
            {}

            BulkUpdateInventoryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , FolderData()
            , ItemData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(TransactionID,"TransactionID");
                }

            };

            struct FolderDataBlock
            {
                LLUUID FolderID;
                LLUUID ParentID;
                Int8 Type;
                raw::LLVariable Name;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FolderID,"FolderID");
                    p.process(ParentID,"ParentID");
                    p.process(Type,"Type");
                    p.process(Name,"Name");
                }

            };

            struct ItemDataBlock
            {
                LLUUID ItemID;
                UInt32 CallbackID;
                LLUUID FolderID;
                LLUUID CreatorID;
                LLUUID OwnerID;
                LLUUID GroupID;
                UInt32 BaseMask;
                UInt32 OwnerMask;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;
                bool GroupOwned;
                LLUUID AssetID;
                Int8 Type;
                Int8 InvType;
                UInt32 Flags;
                UInt8 SaleType;
                Int32 SalePrice;
                raw::LLVariable Name;
                raw::LLVariable Description;
                Int32 CreationDate;
                UInt32 CRC;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(CallbackID,"CallbackID");
                    p.process(FolderID,"FolderID");
                    p.process(CreatorID,"CreatorID");
                    p.process(OwnerID,"OwnerID");
                    p.process(GroupID,"GroupID");
                    p.process(BaseMask,"BaseMask");
                    p.process(OwnerMask,"OwnerMask");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(GroupOwned,"GroupOwned");
                    p.process(AssetID,"AssetID");
                    p.process(Type,"Type");
                    p.process(InvType,"InvType");
                    p.process(Flags,"Flags");
                    p.process(SaleType,"SaleType");
                    p.process(SalePrice,"SalePrice");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                    p.process(CreationDate,"CreationDate");
                    p.process(CRC,"CRC");
                }

            };


            AgentDataBlock AgentData;
            std::vector<FolderDataBlock> FolderData;
            std::vector<ItemDataBlock> ItemData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(FolderData,"FolderData");
                p.process(ItemData,"ItemData");
            }

        };

        struct RequestInventoryAssetMessage
            : Message
        {
            static char const * name(){ return "RequestInventoryAsset"; }
            static bool const trusted = false;
            enum { id = 0xFFFF011Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RequestInventoryAssetMessage>();
                }
            };


            RequestInventoryAssetMessage()
            : Message(LowHeader())
            , QueryData()
            {}

            RequestInventoryAssetMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , QueryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct QueryDataBlock
            {
                LLUUID QueryID;
                LLUUID AgentID;
                LLUUID OwnerID;
                LLUUID ItemID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                    p.process(AgentID,"AgentID");
                    p.process(OwnerID,"OwnerID");
                    p.process(ItemID,"ItemID");
                }

            };


            QueryDataBlock QueryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(QueryData,"QueryData");
            }

        };

        struct InventoryAssetResponseMessage
            : Message
        {
            static char const * name(){ return "InventoryAssetResponse"; }
            static bool const trusted = false;
            enum { id = 0xFFFF011Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<InventoryAssetResponseMessage>();
                }
            };


            InventoryAssetResponseMessage()
            : Message(LowHeader())
            , QueryData()
            {}

            InventoryAssetResponseMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , QueryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct QueryDataBlock
            {
                LLUUID QueryID;
                LLUUID AssetID;
                bool IsReadable;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(QueryID,"QueryID");
                    p.process(AssetID,"AssetID");
                    p.process(IsReadable,"IsReadable");
                }

            };


            QueryDataBlock QueryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(QueryData,"QueryData");
            }

        };

        struct RemoveInventoryObjectsMessage
            : Message
        {
            static char const * name(){ return "RemoveInventoryObjects"; }
            static bool const trusted = false;
            enum { id = 0xFFFF011Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RemoveInventoryObjectsMessage>();
                }
            };


            RemoveInventoryObjectsMessage()
            : Message(LowHeader())
            , AgentData()
            , FolderData()
            , ItemData()
            {}

            RemoveInventoryObjectsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , FolderData()
            , ItemData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct FolderDataBlock
            {
                LLUUID FolderID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FolderID,"FolderID");
                }

            };

            struct ItemDataBlock
            {
                LLUUID ItemID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<FolderDataBlock> FolderData;
            std::vector<ItemDataBlock> ItemData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(FolderData,"FolderData");
                p.process(ItemData,"ItemData");
            }

        };

        struct PurgeInventoryDescendentsMessage
            : Message
        {
            static char const * name(){ return "PurgeInventoryDescendents"; }
            static bool const trusted = false;
            enum { id = 0xFFFF011Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<PurgeInventoryDescendentsMessage>();
                }
            };


            PurgeInventoryDescendentsMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            PurgeInventoryDescendentsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID FolderID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FolderID,"FolderID");
                }

            };


            AgentDataBlock AgentData;
            InventoryDataBlock InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct UpdateTaskInventoryMessage
            : Message
        {
            static char const * name(){ return "UpdateTaskInventory"; }
            static bool const trusted = false;
            enum { id = 0xFFFF011Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UpdateTaskInventoryMessage>();
                }
            };


            UpdateTaskInventoryMessage()
            : Message(LowHeader())
            , AgentData()
            , UpdateData()
            , InventoryData()
            {}

            UpdateTaskInventoryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , UpdateData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct UpdateDataBlock
            {
                UInt32 LocalID;
                UInt8 Key;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(Key,"Key");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID ItemID;
                LLUUID FolderID;
                LLUUID CreatorID;
                LLUUID OwnerID;
                LLUUID GroupID;
                UInt32 BaseMask;
                UInt32 OwnerMask;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;
                bool GroupOwned;
                LLUUID TransactionID;
                Int8 Type;
                Int8 InvType;
                UInt32 Flags;
                UInt8 SaleType;
                Int32 SalePrice;
                raw::LLVariable Name;
                raw::LLVariable Description;
                Int32 CreationDate;
                UInt32 CRC;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(FolderID,"FolderID");
                    p.process(CreatorID,"CreatorID");
                    p.process(OwnerID,"OwnerID");
                    p.process(GroupID,"GroupID");
                    p.process(BaseMask,"BaseMask");
                    p.process(OwnerMask,"OwnerMask");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(GroupOwned,"GroupOwned");
                    p.process(TransactionID,"TransactionID");
                    p.process(Type,"Type");
                    p.process(InvType,"InvType");
                    p.process(Flags,"Flags");
                    p.process(SaleType,"SaleType");
                    p.process(SalePrice,"SalePrice");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                    p.process(CreationDate,"CreationDate");
                    p.process(CRC,"CRC");
                }

            };


            AgentDataBlock AgentData;
            UpdateDataBlock UpdateData;
            InventoryDataBlock InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(UpdateData,"UpdateData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct RemoveTaskInventoryMessage
            : Message
        {
            static char const * name(){ return "RemoveTaskInventory"; }
            static bool const trusted = false;
            enum { id = 0xFFFF011Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RemoveTaskInventoryMessage>();
                }
            };


            RemoveTaskInventoryMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            RemoveTaskInventoryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InventoryDataBlock
            {
                UInt32 LocalID;
                LLUUID ItemID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(ItemID,"ItemID");
                }

            };


            AgentDataBlock AgentData;
            InventoryDataBlock InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct MoveTaskInventoryMessage
            : Message
        {
            static char const * name(){ return "MoveTaskInventory"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0120ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MoveTaskInventoryMessage>();
                }
            };


            MoveTaskInventoryMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            MoveTaskInventoryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID FolderID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(FolderID,"FolderID");
                }

            };

            struct InventoryDataBlock
            {
                UInt32 LocalID;
                LLUUID ItemID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                    p.process(ItemID,"ItemID");
                }

            };


            AgentDataBlock AgentData;
            InventoryDataBlock InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct RequestTaskInventoryMessage
            : Message
        {
            static char const * name(){ return "RequestTaskInventory"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0121ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RequestTaskInventoryMessage>();
                }
            };


            RequestTaskInventoryMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryData()
            {}

            RequestTaskInventoryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InventoryDataBlock
            {
                UInt32 LocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(LocalID,"LocalID");
                }

            };


            AgentDataBlock AgentData;
            InventoryDataBlock InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct ReplyTaskInventoryMessage
            : Message
        {
            static char const * name(){ return "ReplyTaskInventory"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0122ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ReplyTaskInventoryMessage>();
                }
            };


            ReplyTaskInventoryMessage()
            : Message(LowHeader())
            , InventoryData()
            {}

            ReplyTaskInventoryMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct InventoryDataBlock
            {
                LLUUID TaskID;
                Int16 Serial;
                raw::LLVariable Filename;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TaskID,"TaskID");
                    p.process(Serial,"Serial");
                    p.process(Filename,"Filename");
                }

            };


            InventoryDataBlock InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(InventoryData,"InventoryData");
            }

        };

        struct DeRezObjectMessage
            : Message
        {
            static char const * name(){ return "DeRezObject"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0123ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DeRezObjectMessage>();
                }
            };


            DeRezObjectMessage()
            : Message(LowHeader())
            , AgentData()
            , AgentBlock()
            , ObjectData()
            {}

            DeRezObjectMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , AgentBlock()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct AgentBlockBlock
            {
                LLUUID GroupID;
                UInt8 Destination;
                LLUUID DestinationID;
                LLUUID TransactionID;
                UInt8 PacketCount;
                UInt8 PacketNumber;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(Destination,"Destination");
                    p.process(DestinationID,"DestinationID");
                    p.process(TransactionID,"TransactionID");
                    p.process(PacketCount,"PacketCount");
                    p.process(PacketNumber,"PacketNumber");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                }

            };


            AgentDataBlock AgentData;
            AgentBlockBlock AgentBlock;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(AgentBlock,"AgentBlock");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct DeRezAckMessage
            : Message
        {
            static char const * name(){ return "DeRezAck"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0124ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DeRezAckMessage>();
                }
            };


            DeRezAckMessage()
            : Message(LowHeader())
            , TransactionData()
            {}

            DeRezAckMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , TransactionData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct TransactionDataBlock
            {
                LLUUID TransactionID;
                bool Success;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                    p.process(Success,"Success");
                }

            };


            TransactionDataBlock TransactionData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(TransactionData,"TransactionData");
            }

        };

        struct RezObjectMessage
            : Message
        {
            static char const * name(){ return "RezObject"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0125ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RezObjectMessage>();
                }
            };


            RezObjectMessage()
            : Message(LowHeader())
            , AgentData()
            , RezData()
            , InventoryData()
            {}

            RezObjectMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , RezData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct RezDataBlock
            {
                LLUUID FromTaskID;
                UInt8 BypassRaycast;
                raw::LLVector3 RayStart;
                raw::LLVector3 RayEnd;
                LLUUID RayTargetID;
                bool RayEndIsIntersection;
                bool RezSelected;
                bool RemoveItem;
                UInt32 ItemFlags;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FromTaskID,"FromTaskID");
                    p.process(BypassRaycast,"BypassRaycast");
                    p.process(RayStart,"RayStart");
                    p.process(RayEnd,"RayEnd");
                    p.process(RayTargetID,"RayTargetID");
                    p.process(RayEndIsIntersection,"RayEndIsIntersection");
                    p.process(RezSelected,"RezSelected");
                    p.process(RemoveItem,"RemoveItem");
                    p.process(ItemFlags,"ItemFlags");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID ItemID;
                LLUUID FolderID;
                LLUUID CreatorID;
                LLUUID OwnerID;
                LLUUID GroupID;
                UInt32 BaseMask;
                UInt32 OwnerMask;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;
                bool GroupOwned;
                LLUUID TransactionID;
                Int8 Type;
                Int8 InvType;
                UInt32 Flags;
                UInt8 SaleType;
                Int32 SalePrice;
                raw::LLVariable Name;
                raw::LLVariable Description;
                Int32 CreationDate;
                UInt32 CRC;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(FolderID,"FolderID");
                    p.process(CreatorID,"CreatorID");
                    p.process(OwnerID,"OwnerID");
                    p.process(GroupID,"GroupID");
                    p.process(BaseMask,"BaseMask");
                    p.process(OwnerMask,"OwnerMask");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(GroupOwned,"GroupOwned");
                    p.process(TransactionID,"TransactionID");
                    p.process(Type,"Type");
                    p.process(InvType,"InvType");
                    p.process(Flags,"Flags");
                    p.process(SaleType,"SaleType");
                    p.process(SalePrice,"SalePrice");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                    p.process(CreationDate,"CreationDate");
                    p.process(CRC,"CRC");
                }

            };


            AgentDataBlock AgentData;
            RezDataBlock RezData;
            InventoryDataBlock InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RezData,"RezData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct RezObjectFromNotecardMessage
            : Message
        {
            static char const * name(){ return "RezObjectFromNotecard"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0126ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RezObjectFromNotecardMessage>();
                }
            };


            RezObjectFromNotecardMessage()
            : Message(LowHeader())
            , AgentData()
            , RezData()
            , NotecardData()
            , InventoryData()
            {}

            RezObjectFromNotecardMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , RezData()
            , NotecardData()
            , InventoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct RezDataBlock
            {
                LLUUID FromTaskID;
                UInt8 BypassRaycast;
                raw::LLVector3 RayStart;
                raw::LLVector3 RayEnd;
                LLUUID RayTargetID;
                bool RayEndIsIntersection;
                bool RezSelected;
                bool RemoveItem;
                UInt32 ItemFlags;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FromTaskID,"FromTaskID");
                    p.process(BypassRaycast,"BypassRaycast");
                    p.process(RayStart,"RayStart");
                    p.process(RayEnd,"RayEnd");
                    p.process(RayTargetID,"RayTargetID");
                    p.process(RayEndIsIntersection,"RayEndIsIntersection");
                    p.process(RezSelected,"RezSelected");
                    p.process(RemoveItem,"RemoveItem");
                    p.process(ItemFlags,"ItemFlags");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                }

            };

            struct NotecardDataBlock
            {
                LLUUID NotecardItemID;
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(NotecardItemID,"NotecardItemID");
                    p.process(ObjectID,"ObjectID");
                }

            };

            struct InventoryDataBlock
            {
                LLUUID ItemID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                }

            };


            AgentDataBlock AgentData;
            RezDataBlock RezData;
            NotecardDataBlock NotecardData;
            std::vector<InventoryDataBlock> InventoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RezData,"RezData");
                p.process(NotecardData,"NotecardData");
                p.process(InventoryData,"InventoryData");
            }

        };

        struct AcceptFriendshipMessage
            : Message
        {
            static char const * name(){ return "AcceptFriendship"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0129ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AcceptFriendshipMessage>();
                }
            };


            AcceptFriendshipMessage()
            : Message(LowHeader())
            , AgentData()
            , TransactionBlock()
            , FolderData()
            {}

            AcceptFriendshipMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , TransactionBlock()
            , FolderData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct TransactionBlockBlock
            {
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                }

            };

            struct FolderDataBlock
            {
                LLUUID FolderID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FolderID,"FolderID");
                }

            };


            AgentDataBlock AgentData;
            TransactionBlockBlock TransactionBlock;
            std::vector<FolderDataBlock> FolderData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(TransactionBlock,"TransactionBlock");
                p.process(FolderData,"FolderData");
            }

        };

        struct DeclineFriendshipMessage
            : Message
        {
            static char const * name(){ return "DeclineFriendship"; }
            static bool const trusted = false;
            enum { id = 0xFFFF012Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DeclineFriendshipMessage>();
                }
            };


            DeclineFriendshipMessage()
            : Message(LowHeader())
            , AgentData()
            , TransactionBlock()
            {}

            DeclineFriendshipMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , TransactionBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct TransactionBlockBlock
            {
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                }

            };


            AgentDataBlock AgentData;
            TransactionBlockBlock TransactionBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(TransactionBlock,"TransactionBlock");
            }

        };

        struct FormFriendshipMessage
            : Message
        {
            static char const * name(){ return "FormFriendship"; }
            static bool const trusted = false;
            enum { id = 0xFFFF012Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<FormFriendshipMessage>();
                }
            };


            FormFriendshipMessage()
            : Message(LowHeader())
            , AgentBlock()
            {}

            FormFriendshipMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentBlockBlock
            {
                LLUUID SourceID;
                LLUUID DestID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SourceID,"SourceID");
                    p.process(DestID,"DestID");
                }

            };


            AgentBlockBlock AgentBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentBlock,"AgentBlock");
            }

        };

        struct TerminateFriendshipMessage
            : Message
        {
            static char const * name(){ return "TerminateFriendship"; }
            static bool const trusted = false;
            enum { id = 0xFFFF012Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TerminateFriendshipMessage>();
                }
            };


            TerminateFriendshipMessage()
            : Message(LowHeader())
            , AgentData()
            , ExBlock()
            {}

            TerminateFriendshipMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ExBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ExBlockBlock
            {
                LLUUID OtherID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(OtherID,"OtherID");
                }

            };


            AgentDataBlock AgentData;
            ExBlockBlock ExBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ExBlock,"ExBlock");
            }

        };

        struct OfferCallingCardMessage
            : Message
        {
            static char const * name(){ return "OfferCallingCard"; }
            static bool const trusted = false;
            enum { id = 0xFFFF012Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<OfferCallingCardMessage>();
                }
            };


            OfferCallingCardMessage()
            : Message(LowHeader())
            , AgentData()
            , AgentBlock()
            {}

            OfferCallingCardMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , AgentBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct AgentBlockBlock
            {
                LLUUID DestID;
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(DestID,"DestID");
                    p.process(TransactionID,"TransactionID");
                }

            };


            AgentDataBlock AgentData;
            AgentBlockBlock AgentBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(AgentBlock,"AgentBlock");
            }

        };

        struct AcceptCallingCardMessage
            : Message
        {
            static char const * name(){ return "AcceptCallingCard"; }
            static bool const trusted = false;
            enum { id = 0xFFFF012Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AcceptCallingCardMessage>();
                }
            };


            AcceptCallingCardMessage()
            : Message(LowHeader())
            , AgentData()
            , TransactionBlock()
            , FolderData()
            {}

            AcceptCallingCardMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , TransactionBlock()
            , FolderData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct TransactionBlockBlock
            {
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                }

            };

            struct FolderDataBlock
            {
                LLUUID FolderID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FolderID,"FolderID");
                }

            };


            AgentDataBlock AgentData;
            TransactionBlockBlock TransactionBlock;
            std::vector<FolderDataBlock> FolderData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(TransactionBlock,"TransactionBlock");
                p.process(FolderData,"FolderData");
            }

        };

        struct DeclineCallingCardMessage
            : Message
        {
            static char const * name(){ return "DeclineCallingCard"; }
            static bool const trusted = false;
            enum { id = 0xFFFF012Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DeclineCallingCardMessage>();
                }
            };


            DeclineCallingCardMessage()
            : Message(LowHeader())
            , AgentData()
            , TransactionBlock()
            {}

            DeclineCallingCardMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , TransactionBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct TransactionBlockBlock
            {
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                }

            };


            AgentDataBlock AgentData;
            TransactionBlockBlock TransactionBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(TransactionBlock,"TransactionBlock");
            }

        };

        struct RezScriptMessage
            : Message
        {
            static char const * name(){ return "RezScript"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0130ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RezScriptMessage>();
                }
            };


            RezScriptMessage()
            : Message(LowHeader())
            , AgentData()
            , UpdateBlock()
            , InventoryBlock()
            {}

            RezScriptMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , UpdateBlock()
            , InventoryBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct UpdateBlockBlock
            {
                UInt32 ObjectLocalID;
                bool Enabled;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(Enabled,"Enabled");
                }

            };

            struct InventoryBlockBlock
            {
                LLUUID ItemID;
                LLUUID FolderID;
                LLUUID CreatorID;
                LLUUID OwnerID;
                LLUUID GroupID;
                UInt32 BaseMask;
                UInt32 OwnerMask;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;
                bool GroupOwned;
                LLUUID TransactionID;
                Int8 Type;
                Int8 InvType;
                UInt32 Flags;
                UInt8 SaleType;
                Int32 SalePrice;
                raw::LLVariable Name;
                raw::LLVariable Description;
                Int32 CreationDate;
                UInt32 CRC;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(FolderID,"FolderID");
                    p.process(CreatorID,"CreatorID");
                    p.process(OwnerID,"OwnerID");
                    p.process(GroupID,"GroupID");
                    p.process(BaseMask,"BaseMask");
                    p.process(OwnerMask,"OwnerMask");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(GroupOwned,"GroupOwned");
                    p.process(TransactionID,"TransactionID");
                    p.process(Type,"Type");
                    p.process(InvType,"InvType");
                    p.process(Flags,"Flags");
                    p.process(SaleType,"SaleType");
                    p.process(SalePrice,"SalePrice");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                    p.process(CreationDate,"CreationDate");
                    p.process(CRC,"CRC");
                }

            };


            AgentDataBlock AgentData;
            UpdateBlockBlock UpdateBlock;
            InventoryBlockBlock InventoryBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(UpdateBlock,"UpdateBlock");
                p.process(InventoryBlock,"InventoryBlock");
            }

        };

        struct CreateInventoryItemMessage
            : Message
        {
            static char const * name(){ return "CreateInventoryItem"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0131ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CreateInventoryItemMessage>();
                }
            };


            CreateInventoryItemMessage()
            : Message(LowHeader())
            , AgentData()
            , InventoryBlock()
            {}

            CreateInventoryItemMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , InventoryBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct InventoryBlockBlock
            {
                UInt32 CallbackID;
                LLUUID FolderID;
                LLUUID TransactionID;
                UInt32 NextOwnerMask;
                Int8 Type;
                Int8 InvType;
                UInt8 WearableType;
                raw::LLVariable Name;
                raw::LLVariable Description;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(CallbackID,"CallbackID");
                    p.process(FolderID,"FolderID");
                    p.process(TransactionID,"TransactionID");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(Type,"Type");
                    p.process(InvType,"InvType");
                    p.process(WearableType,"WearableType");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                }

            };


            AgentDataBlock AgentData;
            InventoryBlockBlock InventoryBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(InventoryBlock,"InventoryBlock");
            }

        };

        struct CreateLandmarkForEventMessage
            : Message
        {
            static char const * name(){ return "CreateLandmarkForEvent"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0132ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CreateLandmarkForEventMessage>();
                }
            };


            CreateLandmarkForEventMessage()
            : Message(LowHeader())
            , AgentData()
            , EventData()
            , InventoryBlock()
            {}

            CreateLandmarkForEventMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , EventData()
            , InventoryBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct EventDataBlock
            {
                UInt32 EventID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(EventID,"EventID");
                }

            };

            struct InventoryBlockBlock
            {
                LLUUID FolderID;
                raw::LLVariable Name;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(FolderID,"FolderID");
                    p.process(Name,"Name");
                }

            };


            AgentDataBlock AgentData;
            EventDataBlock EventData;
            InventoryBlockBlock InventoryBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(EventData,"EventData");
                p.process(InventoryBlock,"InventoryBlock");
            }

        };

        struct RegionHandleRequestMessage
            : Message
        {
            static char const * name(){ return "RegionHandleRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0135ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RegionHandleRequestMessage>();
                }
            };


            RegionHandleRequestMessage()
            : Message(LowHeader())
            , RequestBlock()
            {}

            RegionHandleRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , RequestBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct RequestBlockBlock
            {
                LLUUID RegionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionID,"RegionID");
                }

            };


            RequestBlockBlock RequestBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(RequestBlock,"RequestBlock");
            }

        };

        struct RegionIDAndHandleReplyMessage
            : Message
        {
            static char const * name(){ return "RegionIDAndHandleReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0136ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RegionIDAndHandleReplyMessage>();
                }
            };


            RegionIDAndHandleReplyMessage()
            : Message(LowHeader())
            , ReplyBlock()
            {}

            RegionIDAndHandleReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , ReplyBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ReplyBlockBlock
            {
                LLUUID RegionID;
                UInt64 RegionHandle;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionID,"RegionID");
                    p.process(RegionHandle,"RegionHandle");
                }

            };


            ReplyBlockBlock ReplyBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ReplyBlock,"ReplyBlock");
            }

        };

        struct MoneyTransferRequestMessage
            : Message
        {
            static char const * name(){ return "MoneyTransferRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0137ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MoneyTransferRequestMessage>();
                }
            };


            MoneyTransferRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , MoneyData()
            {}

            MoneyTransferRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MoneyData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct MoneyDataBlock
            {
                LLUUID SourceID;
                LLUUID DestID;
                UInt8 Flags;
                Int32 Amount;
                UInt8 AggregatePermNextOwner;
                UInt8 AggregatePermInventory;
                Int32 TransactionType;
                raw::LLVariable Description;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SourceID,"SourceID");
                    p.process(DestID,"DestID");
                    p.process(Flags,"Flags");
                    p.process(Amount,"Amount");
                    p.process(AggregatePermNextOwner,"AggregatePermNextOwner");
                    p.process(AggregatePermInventory,"AggregatePermInventory");
                    p.process(TransactionType,"TransactionType");
                    p.process(Description,"Description");
                }

            };


            AgentDataBlock AgentData;
            MoneyDataBlock MoneyData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MoneyData,"MoneyData");
            }

        };

        struct MoneyBalanceRequestMessage
            : Message
        {
            static char const * name(){ return "MoneyBalanceRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0139ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MoneyBalanceRequestMessage>();
                }
            };


            MoneyBalanceRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , MoneyData()
            {}

            MoneyBalanceRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MoneyData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct MoneyDataBlock
            {
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                }

            };


            AgentDataBlock AgentData;
            MoneyDataBlock MoneyData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MoneyData,"MoneyData");
            }

        };

        struct MoneyBalanceReplyMessage
            : Message
        {
            static char const * name(){ return "MoneyBalanceReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF013Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MoneyBalanceReplyMessage>();
                }
            };


            MoneyBalanceReplyMessage()
            : Message(LowHeader())
            , MoneyData()
            {}

            MoneyBalanceReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , MoneyData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct MoneyDataBlock
            {
                LLUUID AgentID;
                LLUUID TransactionID;
                bool TransactionSuccess;
                Int32 MoneyBalance;
                Int32 SquareMetersCredit;
                Int32 SquareMetersCommitted;
                raw::LLVariable Description;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(TransactionID,"TransactionID");
                    p.process(TransactionSuccess,"TransactionSuccess");
                    p.process(MoneyBalance,"MoneyBalance");
                    p.process(SquareMetersCredit,"SquareMetersCredit");
                    p.process(SquareMetersCommitted,"SquareMetersCommitted");
                    p.process(Description,"Description");
                }

            };


            MoneyDataBlock MoneyData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(MoneyData,"MoneyData");
            }

        };

        struct RoutedMoneyBalanceReplyMessage
            : Message
        {
            static char const * name(){ return "RoutedMoneyBalanceReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF013Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RoutedMoneyBalanceReplyMessage>();
                }
            };


            RoutedMoneyBalanceReplyMessage()
            : Message(LowHeader())
            , TargetBlock()
            , MoneyData()
            {}

            RoutedMoneyBalanceReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , TargetBlock()
            , MoneyData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct TargetBlockBlock
            {
                raw::LLIPAddress TargetIP;
                raw::LLIPPort TargetPort;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TargetIP,"TargetIP");
                    p.process(TargetPort,"TargetPort");
                }

            };

            struct MoneyDataBlock
            {
                LLUUID AgentID;
                LLUUID TransactionID;
                bool TransactionSuccess;
                Int32 MoneyBalance;
                Int32 SquareMetersCredit;
                Int32 SquareMetersCommitted;
                raw::LLVariable Description;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(TransactionID,"TransactionID");
                    p.process(TransactionSuccess,"TransactionSuccess");
                    p.process(MoneyBalance,"MoneyBalance");
                    p.process(SquareMetersCredit,"SquareMetersCredit");
                    p.process(SquareMetersCommitted,"SquareMetersCommitted");
                    p.process(Description,"Description");
                }

            };


            TargetBlockBlock TargetBlock;
            MoneyDataBlock MoneyData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(TargetBlock,"TargetBlock");
                p.process(MoneyData,"MoneyData");
            }

        };

        struct ActivateGesturesMessage
            : Message
        {
            static char const * name(){ return "ActivateGestures"; }
            static bool const trusted = false;
            enum { id = 0xFFFF013Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ActivateGesturesMessage>();
                }
            };


            ActivateGesturesMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ActivateGesturesMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(Flags,"Flags");
                }

            };

            struct DataBlock
            {
                LLUUID ItemID;
                LLUUID AssetID;
                UInt32 GestureFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(AssetID,"AssetID");
                    p.process(GestureFlags,"GestureFlags");
                }

            };


            AgentDataBlock AgentData;
            std::vector<DataBlock> Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct DeactivateGesturesMessage
            : Message
        {
            static char const * name(){ return "DeactivateGestures"; }
            static bool const trusted = false;
            enum { id = 0xFFFF013Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DeactivateGesturesMessage>();
                }
            };


            DeactivateGesturesMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            DeactivateGesturesMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(Flags,"Flags");
                }

            };

            struct DataBlock
            {
                LLUUID ItemID;
                UInt32 GestureFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(GestureFlags,"GestureFlags");
                }

            };


            AgentDataBlock AgentData;
            std::vector<DataBlock> Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct MuteListUpdateMessage
            : Message
        {
            static char const * name(){ return "MuteListUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF013Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MuteListUpdateMessage>();
                }
            };


            MuteListUpdateMessage()
            : Message(LowHeader())
            , MuteData()
            {}

            MuteListUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , MuteData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct MuteDataBlock
            {
                LLUUID AgentID;
                raw::LLVariable Filename;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(Filename,"Filename");
                }

            };


            MuteDataBlock MuteData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(MuteData,"MuteData");
            }

        };

        struct UseCachedMuteListMessage
            : Message
        {
            static char const * name(){ return "UseCachedMuteList"; }
            static bool const trusted = false;
            enum { id = 0xFFFF013Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UseCachedMuteListMessage>();
                }
            };


            UseCachedMuteListMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            UseCachedMuteListMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct GrantUserRightsMessage
            : Message
        {
            static char const * name(){ return "GrantUserRights"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0140ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GrantUserRightsMessage>();
                }
            };


            GrantUserRightsMessage()
            : Message(LowHeader())
            , AgentData()
            , Rights()
            {}

            GrantUserRightsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Rights()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct RightsBlock
            {
                LLUUID AgentRelated;
                Int32 RelatedRights;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentRelated,"AgentRelated");
                    p.process(RelatedRights,"RelatedRights");
                }

            };


            AgentDataBlock AgentData;
            std::vector<RightsBlock> Rights;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Rights,"Rights");
            }

        };

        struct ChangeUserRightsMessage
            : Message
        {
            static char const * name(){ return "ChangeUserRights"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0141ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ChangeUserRightsMessage>();
                }
            };


            ChangeUserRightsMessage()
            : Message(LowHeader())
            , AgentData()
            , Rights()
            {}

            ChangeUserRightsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Rights()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct RightsBlock
            {
                LLUUID AgentRelated;
                Int32 RelatedRights;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentRelated,"AgentRelated");
                    p.process(RelatedRights,"RelatedRights");
                }

            };


            AgentDataBlock AgentData;
            std::vector<RightsBlock> Rights;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Rights,"Rights");
            }

        };

        struct OnlineNotificationMessage
            : Message
        {
            static char const * name(){ return "OnlineNotification"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0142ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<OnlineNotificationMessage>();
                }
            };


            OnlineNotificationMessage()
            : Message(LowHeader())
            , AgentBlock()
            {}

            OnlineNotificationMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentBlockBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };


            std::vector<AgentBlockBlock> AgentBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentBlock,"AgentBlock");
            }

        };

        struct OfflineNotificationMessage
            : Message
        {
            static char const * name(){ return "OfflineNotification"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0143ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<OfflineNotificationMessage>();
                }
            };


            OfflineNotificationMessage()
            : Message(LowHeader())
            , AgentBlock()
            {}

            OfflineNotificationMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentBlockBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };


            std::vector<AgentBlockBlock> AgentBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentBlock,"AgentBlock");
            }

        };

        struct SetStartLocationRequestMessage
            : Message
        {
            static char const * name(){ return "SetStartLocationRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0144ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SetStartLocationRequestMessage>();
                }
            };


            SetStartLocationRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , StartLocationData()
            {}

            SetStartLocationRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , StartLocationData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct StartLocationDataBlock
            {
                raw::LLVariable SimName;
                UInt32 LocationID;
                raw::LLVector3 LocationPos;
                raw::LLVector3 LocationLookAt;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SimName,"SimName");
                    p.process(LocationID,"LocationID");
                    p.process(LocationPos,"LocationPos");
                    p.process(LocationLookAt,"LocationLookAt");
                }

            };


            AgentDataBlock AgentData;
            StartLocationDataBlock StartLocationData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(StartLocationData,"StartLocationData");
            }

        };

        struct AssetUploadRequestMessage
            : Message
        {
            static char const * name(){ return "AssetUploadRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF014Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AssetUploadRequestMessage>();
                }
            };


            AssetUploadRequestMessage()
            : Message(LowHeader())
            , AssetBlock()
            {}

            AssetUploadRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AssetBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AssetBlockBlock
            {
                LLUUID TransactionID;
                Int8 Type;
                bool Tempfile;
                bool StoreLocal;
                raw::LLVariable AssetData;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                    p.process(Type,"Type");
                    p.process(Tempfile,"Tempfile");
                    p.process(StoreLocal,"StoreLocal");
                    p.process(AssetData,"AssetData");
                }

            };


            AssetBlockBlock AssetBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AssetBlock,"AssetBlock");
            }

        };

        struct AssetUploadCompleteMessage
            : Message
        {
            static char const * name(){ return "AssetUploadComplete"; }
            static bool const trusted = false;
            enum { id = 0xFFFF014Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AssetUploadCompleteMessage>();
                }
            };


            AssetUploadCompleteMessage()
            : Message(LowHeader())
            , AssetBlock()
            {}

            AssetUploadCompleteMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AssetBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AssetBlockBlock
            {
                LLUUID UUID;
                Int8 Type;
                bool Success;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(UUID,"UUID");
                    p.process(Type,"Type");
                    p.process(Success,"Success");
                }

            };


            AssetBlockBlock AssetBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AssetBlock,"AssetBlock");
            }

        };

        struct CreateGroupRequestMessage
            : Message
        {
            static char const * name(){ return "CreateGroupRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0153ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CreateGroupRequestMessage>();
                }
            };


            CreateGroupRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            CreateGroupRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GroupDataBlock
            {
                raw::LLVariable Name;
                raw::LLVariable Charter;
                bool ShowInList;
                LLUUID InsigniaID;
                Int32 MembershipFee;
                bool OpenEnrollment;
                bool AllowPublish;
                bool MaturePublish;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Name,"Name");
                    p.process(Charter,"Charter");
                    p.process(ShowInList,"ShowInList");
                    p.process(InsigniaID,"InsigniaID");
                    p.process(MembershipFee,"MembershipFee");
                    p.process(OpenEnrollment,"OpenEnrollment");
                    p.process(AllowPublish,"AllowPublish");
                    p.process(MaturePublish,"MaturePublish");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct CreateGroupReplyMessage
            : Message
        {
            static char const * name(){ return "CreateGroupReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0154ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CreateGroupReplyMessage>();
                }
            };


            CreateGroupReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , ReplyData()
            {}

            CreateGroupReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ReplyData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct ReplyDataBlock
            {
                LLUUID GroupID;
                bool Success;
                raw::LLVariable Message;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(Success,"Success");
                    p.process(Message,"Message");
                }

            };


            AgentDataBlock AgentData;
            ReplyDataBlock ReplyData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ReplyData,"ReplyData");
            }

        };

        struct UpdateGroupInfoMessage
            : Message
        {
            static char const * name(){ return "UpdateGroupInfo"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0155ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UpdateGroupInfoMessage>();
                }
            };


            UpdateGroupInfoMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            UpdateGroupInfoMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;
                raw::LLVariable Charter;
                bool ShowInList;
                LLUUID InsigniaID;
                Int32 MembershipFee;
                bool OpenEnrollment;
                bool AllowPublish;
                bool MaturePublish;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(Charter,"Charter");
                    p.process(ShowInList,"ShowInList");
                    p.process(InsigniaID,"InsigniaID");
                    p.process(MembershipFee,"MembershipFee");
                    p.process(OpenEnrollment,"OpenEnrollment");
                    p.process(AllowPublish,"AllowPublish");
                    p.process(MaturePublish,"MaturePublish");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct GroupRoleChangesMessage
            : Message
        {
            static char const * name(){ return "GroupRoleChanges"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0156ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupRoleChangesMessage>();
                }
            };


            GroupRoleChangesMessage()
            : Message(LowHeader())
            , AgentData()
            , RoleChange()
            {}

            GroupRoleChangesMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , RoleChange()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct RoleChangeBlock
            {
                LLUUID RoleID;
                LLUUID MemberID;
                UInt32 Change;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RoleID,"RoleID");
                    p.process(MemberID,"MemberID");
                    p.process(Change,"Change");
                }

            };


            AgentDataBlock AgentData;
            std::vector<RoleChangeBlock> RoleChange;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RoleChange,"RoleChange");
            }

        };

        struct JoinGroupRequestMessage
            : Message
        {
            static char const * name(){ return "JoinGroupRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0157ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<JoinGroupRequestMessage>();
                }
            };


            JoinGroupRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            JoinGroupRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct JoinGroupReplyMessage
            : Message
        {
            static char const * name(){ return "JoinGroupReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0158ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<JoinGroupReplyMessage>();
                }
            };


            JoinGroupReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            JoinGroupReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;
                bool Success;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(Success,"Success");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct EjectGroupMemberRequestMessage
            : Message
        {
            static char const * name(){ return "EjectGroupMemberRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0159ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EjectGroupMemberRequestMessage>();
                }
            };


            EjectGroupMemberRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            , EjectData()
            {}

            EjectGroupMemberRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            , EjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                }

            };

            struct EjectDataBlock
            {
                LLUUID EjecteeID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(EjecteeID,"EjecteeID");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;
            std::vector<EjectDataBlock> EjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
                p.process(EjectData,"EjectData");
            }

        };

        struct EjectGroupMemberReplyMessage
            : Message
        {
            static char const * name(){ return "EjectGroupMemberReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF015Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<EjectGroupMemberReplyMessage>();
                }
            };


            EjectGroupMemberReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            , EjectData()
            {}

            EjectGroupMemberReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            , EjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                }

            };

            struct EjectDataBlock
            {
                bool Success;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Success,"Success");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;
            EjectDataBlock EjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
                p.process(EjectData,"EjectData");
            }

        };

        struct LeaveGroupRequestMessage
            : Message
        {
            static char const * name(){ return "LeaveGroupRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF015Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<LeaveGroupRequestMessage>();
                }
            };


            LeaveGroupRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            LeaveGroupRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct LeaveGroupReplyMessage
            : Message
        {
            static char const * name(){ return "LeaveGroupReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF015Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<LeaveGroupReplyMessage>();
                }
            };


            LeaveGroupReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            LeaveGroupReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;
                bool Success;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(Success,"Success");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct InviteGroupRequestMessage
            : Message
        {
            static char const * name(){ return "InviteGroupRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF015Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<InviteGroupRequestMessage>();
                }
            };


            InviteGroupRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            , InviteData()
            {}

            InviteGroupRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            , InviteData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                }

            };

            struct InviteDataBlock
            {
                LLUUID InviteeID;
                LLUUID RoleID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(InviteeID,"InviteeID");
                    p.process(RoleID,"RoleID");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;
            std::vector<InviteDataBlock> InviteData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
                p.process(InviteData,"InviteData");
            }

        };

        struct GroupProfileRequestMessage
            : Message
        {
            static char const * name(){ return "GroupProfileRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF015Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupProfileRequestMessage>();
                }
            };


            GroupProfileRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            GroupProfileRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct GroupProfileReplyMessage
            : Message
        {
            static char const * name(){ return "GroupProfileReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0160ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupProfileReplyMessage>();
                }
            };


            GroupProfileReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            GroupProfileReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;
                raw::LLVariable Name;
                raw::LLVariable Charter;
                bool ShowInList;
                raw::LLVariable MemberTitle;
                UInt64 PowersMask;
                LLUUID InsigniaID;
                LLUUID FounderID;
                Int32 MembershipFee;
                bool OpenEnrollment;
                Int32 Money;
                Int32 GroupMembershipCount;
                Int32 GroupRolesCount;
                bool AllowPublish;
                bool MaturePublish;
                LLUUID OwnerRole;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(Name,"Name");
                    p.process(Charter,"Charter");
                    p.process(ShowInList,"ShowInList");
                    p.process(MemberTitle,"MemberTitle");
                    p.process(PowersMask,"PowersMask");
                    p.process(InsigniaID,"InsigniaID");
                    p.process(FounderID,"FounderID");
                    p.process(MembershipFee,"MembershipFee");
                    p.process(OpenEnrollment,"OpenEnrollment");
                    p.process(Money,"Money");
                    p.process(GroupMembershipCount,"GroupMembershipCount");
                    p.process(GroupRolesCount,"GroupRolesCount");
                    p.process(AllowPublish,"AllowPublish");
                    p.process(MaturePublish,"MaturePublish");
                    p.process(OwnerRole,"OwnerRole");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct GroupAccountSummaryRequestMessage
            : Message
        {
            static char const * name(){ return "GroupAccountSummaryRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0161ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupAccountSummaryRequestMessage>();
                }
            };


            GroupAccountSummaryRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , MoneyData()
            {}

            GroupAccountSummaryRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MoneyData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct MoneyDataBlock
            {
                LLUUID RequestID;
                Int32 IntervalDays;
                Int32 CurrentInterval;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RequestID,"RequestID");
                    p.process(IntervalDays,"IntervalDays");
                    p.process(CurrentInterval,"CurrentInterval");
                }

            };


            AgentDataBlock AgentData;
            MoneyDataBlock MoneyData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MoneyData,"MoneyData");
            }

        };

        struct GroupAccountSummaryReplyMessage
            : Message
        {
            static char const * name(){ return "GroupAccountSummaryReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0162ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupAccountSummaryReplyMessage>();
                }
            };


            GroupAccountSummaryReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , MoneyData()
            {}

            GroupAccountSummaryReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MoneyData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct MoneyDataBlock
            {
                LLUUID RequestID;
                Int32 IntervalDays;
                Int32 CurrentInterval;
                raw::LLVariable StartDate;
                Int32 Balance;
                Int32 TotalCredits;
                Int32 TotalDebits;
                Int32 ObjectTaxCurrent;
                Int32 LightTaxCurrent;
                Int32 LandTaxCurrent;
                Int32 GroupTaxCurrent;
                Int32 ParcelDirFeeCurrent;
                Int32 ObjectTaxEstimate;
                Int32 LightTaxEstimate;
                Int32 LandTaxEstimate;
                Int32 GroupTaxEstimate;
                Int32 ParcelDirFeeEstimate;
                Int32 NonExemptMembers;
                raw::LLVariable LastTaxDate;
                raw::LLVariable TaxDate;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RequestID,"RequestID");
                    p.process(IntervalDays,"IntervalDays");
                    p.process(CurrentInterval,"CurrentInterval");
                    p.process(StartDate,"StartDate");
                    p.process(Balance,"Balance");
                    p.process(TotalCredits,"TotalCredits");
                    p.process(TotalDebits,"TotalDebits");
                    p.process(ObjectTaxCurrent,"ObjectTaxCurrent");
                    p.process(LightTaxCurrent,"LightTaxCurrent");
                    p.process(LandTaxCurrent,"LandTaxCurrent");
                    p.process(GroupTaxCurrent,"GroupTaxCurrent");
                    p.process(ParcelDirFeeCurrent,"ParcelDirFeeCurrent");
                    p.process(ObjectTaxEstimate,"ObjectTaxEstimate");
                    p.process(LightTaxEstimate,"LightTaxEstimate");
                    p.process(LandTaxEstimate,"LandTaxEstimate");
                    p.process(GroupTaxEstimate,"GroupTaxEstimate");
                    p.process(ParcelDirFeeEstimate,"ParcelDirFeeEstimate");
                    p.process(NonExemptMembers,"NonExemptMembers");
                    p.process(LastTaxDate,"LastTaxDate");
                    p.process(TaxDate,"TaxDate");
                }

            };


            AgentDataBlock AgentData;
            MoneyDataBlock MoneyData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MoneyData,"MoneyData");
            }

        };

        struct GroupAccountDetailsRequestMessage
            : Message
        {
            static char const * name(){ return "GroupAccountDetailsRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0163ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupAccountDetailsRequestMessage>();
                }
            };


            GroupAccountDetailsRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , MoneyData()
            {}

            GroupAccountDetailsRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MoneyData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct MoneyDataBlock
            {
                LLUUID RequestID;
                Int32 IntervalDays;
                Int32 CurrentInterval;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RequestID,"RequestID");
                    p.process(IntervalDays,"IntervalDays");
                    p.process(CurrentInterval,"CurrentInterval");
                }

            };


            AgentDataBlock AgentData;
            MoneyDataBlock MoneyData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MoneyData,"MoneyData");
            }

        };

        struct GroupAccountDetailsReplyMessage
            : Message
        {
            static char const * name(){ return "GroupAccountDetailsReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0164ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupAccountDetailsReplyMessage>();
                }
            };


            GroupAccountDetailsReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , MoneyData()
            , HistoryData()
            {}

            GroupAccountDetailsReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MoneyData()
            , HistoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct MoneyDataBlock
            {
                LLUUID RequestID;
                Int32 IntervalDays;
                Int32 CurrentInterval;
                raw::LLVariable StartDate;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RequestID,"RequestID");
                    p.process(IntervalDays,"IntervalDays");
                    p.process(CurrentInterval,"CurrentInterval");
                    p.process(StartDate,"StartDate");
                }

            };

            struct HistoryDataBlock
            {
                raw::LLVariable Description;
                Int32 Amount;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Description,"Description");
                    p.process(Amount,"Amount");
                }

            };


            AgentDataBlock AgentData;
            MoneyDataBlock MoneyData;
            std::vector<HistoryDataBlock> HistoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MoneyData,"MoneyData");
                p.process(HistoryData,"HistoryData");
            }

        };

        struct GroupAccountTransactionsRequestMessage
            : Message
        {
            static char const * name(){ return "GroupAccountTransactionsRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0165ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupAccountTransactionsRequestMessage>();
                }
            };


            GroupAccountTransactionsRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , MoneyData()
            {}

            GroupAccountTransactionsRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MoneyData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct MoneyDataBlock
            {
                LLUUID RequestID;
                Int32 IntervalDays;
                Int32 CurrentInterval;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RequestID,"RequestID");
                    p.process(IntervalDays,"IntervalDays");
                    p.process(CurrentInterval,"CurrentInterval");
                }

            };


            AgentDataBlock AgentData;
            MoneyDataBlock MoneyData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MoneyData,"MoneyData");
            }

        };

        struct GroupAccountTransactionsReplyMessage
            : Message
        {
            static char const * name(){ return "GroupAccountTransactionsReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0166ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupAccountTransactionsReplyMessage>();
                }
            };


            GroupAccountTransactionsReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , MoneyData()
            , HistoryData()
            {}

            GroupAccountTransactionsReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MoneyData()
            , HistoryData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct MoneyDataBlock
            {
                LLUUID RequestID;
                Int32 IntervalDays;
                Int32 CurrentInterval;
                raw::LLVariable StartDate;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RequestID,"RequestID");
                    p.process(IntervalDays,"IntervalDays");
                    p.process(CurrentInterval,"CurrentInterval");
                    p.process(StartDate,"StartDate");
                }

            };

            struct HistoryDataBlock
            {
                raw::LLVariable Time;
                raw::LLVariable User;
                Int32 Type;
                raw::LLVariable Item;
                Int32 Amount;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Time,"Time");
                    p.process(User,"User");
                    p.process(Type,"Type");
                    p.process(Item,"Item");
                    p.process(Amount,"Amount");
                }

            };


            AgentDataBlock AgentData;
            MoneyDataBlock MoneyData;
            std::vector<HistoryDataBlock> HistoryData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MoneyData,"MoneyData");
                p.process(HistoryData,"HistoryData");
            }

        };

        struct GroupActiveProposalsRequestMessage
            : Message
        {
            static char const * name(){ return "GroupActiveProposalsRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0167ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupActiveProposalsRequestMessage>();
                }
            };


            GroupActiveProposalsRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            , TransactionData()
            {}

            GroupActiveProposalsRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            , TransactionData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                }

            };

            struct TransactionDataBlock
            {
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;
            TransactionDataBlock TransactionData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
                p.process(TransactionData,"TransactionData");
            }

        };

        struct GroupActiveProposalItemReplyMessage
            : Message
        {
            static char const * name(){ return "GroupActiveProposalItemReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0168ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupActiveProposalItemReplyMessage>();
                }
            };


            GroupActiveProposalItemReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , TransactionData()
            , ProposalData()
            {}

            GroupActiveProposalItemReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , TransactionData()
            , ProposalData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct TransactionDataBlock
            {
                LLUUID TransactionID;
                UInt32 TotalNumItems;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                    p.process(TotalNumItems,"TotalNumItems");
                }

            };

            struct ProposalDataBlock
            {
                LLUUID VoteID;
                LLUUID VoteInitiator;
                raw::LLVariable TerseDateID;
                raw::LLVariable StartDateTime;
                raw::LLVariable EndDateTime;
                bool AlreadyVoted;
                raw::LLVariable VoteCast;
                Real32 Majority;
                Int32 Quorum;
                raw::LLVariable ProposalText;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(VoteID,"VoteID");
                    p.process(VoteInitiator,"VoteInitiator");
                    p.process(TerseDateID,"TerseDateID");
                    p.process(StartDateTime,"StartDateTime");
                    p.process(EndDateTime,"EndDateTime");
                    p.process(AlreadyVoted,"AlreadyVoted");
                    p.process(VoteCast,"VoteCast");
                    p.process(Majority,"Majority");
                    p.process(Quorum,"Quorum");
                    p.process(ProposalText,"ProposalText");
                }

            };


            AgentDataBlock AgentData;
            TransactionDataBlock TransactionData;
            std::vector<ProposalDataBlock> ProposalData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(TransactionData,"TransactionData");
                p.process(ProposalData,"ProposalData");
            }

        };

        struct GroupVoteHistoryRequestMessage
            : Message
        {
            static char const * name(){ return "GroupVoteHistoryRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0169ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupVoteHistoryRequestMessage>();
                }
            };


            GroupVoteHistoryRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            , TransactionData()
            {}

            GroupVoteHistoryRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            , TransactionData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                }

            };

            struct TransactionDataBlock
            {
                LLUUID TransactionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;
            TransactionDataBlock TransactionData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
                p.process(TransactionData,"TransactionData");
            }

        };

        struct GroupVoteHistoryItemReplyMessage
            : Message
        {
            static char const * name(){ return "GroupVoteHistoryItemReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF016Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupVoteHistoryItemReplyMessage>();
                }
            };


            GroupVoteHistoryItemReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , TransactionData()
            , HistoryItemData()
            , VoteItem()
            {}

            GroupVoteHistoryItemReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , TransactionData()
            , HistoryItemData()
            , VoteItem()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct TransactionDataBlock
            {
                LLUUID TransactionID;
                UInt32 TotalNumItems;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransactionID,"TransactionID");
                    p.process(TotalNumItems,"TotalNumItems");
                }

            };

            struct HistoryItemDataBlock
            {
                LLUUID VoteID;
                raw::LLVariable TerseDateID;
                raw::LLVariable StartDateTime;
                raw::LLVariable EndDateTime;
                LLUUID VoteInitiator;
                raw::LLVariable VoteType;
                raw::LLVariable VoteResult;
                Real32 Majority;
                Int32 Quorum;
                raw::LLVariable ProposalText;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(VoteID,"VoteID");
                    p.process(TerseDateID,"TerseDateID");
                    p.process(StartDateTime,"StartDateTime");
                    p.process(EndDateTime,"EndDateTime");
                    p.process(VoteInitiator,"VoteInitiator");
                    p.process(VoteType,"VoteType");
                    p.process(VoteResult,"VoteResult");
                    p.process(Majority,"Majority");
                    p.process(Quorum,"Quorum");
                    p.process(ProposalText,"ProposalText");
                }

            };

            struct VoteItemBlock
            {
                LLUUID CandidateID;
                raw::LLVariable VoteCast;
                Int32 NumVotes;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(CandidateID,"CandidateID");
                    p.process(VoteCast,"VoteCast");
                    p.process(NumVotes,"NumVotes");
                }

            };


            AgentDataBlock AgentData;
            TransactionDataBlock TransactionData;
            HistoryItemDataBlock HistoryItemData;
            std::vector<VoteItemBlock> VoteItem;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(TransactionData,"TransactionData");
                p.process(HistoryItemData,"HistoryItemData");
                p.process(VoteItem,"VoteItem");
            }

        };

        struct StartGroupProposalMessage
            : Message
        {
            static char const * name(){ return "StartGroupProposal"; }
            static bool const trusted = false;
            enum { id = 0xFFFF016Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<StartGroupProposalMessage>();
                }
            };


            StartGroupProposalMessage()
            : Message(LowHeader())
            , AgentData()
            , ProposalData()
            {}

            StartGroupProposalMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ProposalData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ProposalDataBlock
            {
                LLUUID GroupID;
                Int32 Quorum;
                Real32 Majority;
                Int32 Duration;
                raw::LLVariable ProposalText;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(Quorum,"Quorum");
                    p.process(Majority,"Majority");
                    p.process(Duration,"Duration");
                    p.process(ProposalText,"ProposalText");
                }

            };


            AgentDataBlock AgentData;
            ProposalDataBlock ProposalData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ProposalData,"ProposalData");
            }

        };

        struct GroupProposalBallotMessage
            : Message
        {
            static char const * name(){ return "GroupProposalBallot"; }
            static bool const trusted = false;
            enum { id = 0xFFFF016Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupProposalBallotMessage>();
                }
            };


            GroupProposalBallotMessage()
            : Message(LowHeader())
            , AgentData()
            , ProposalData()
            {}

            GroupProposalBallotMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ProposalData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ProposalDataBlock
            {
                LLUUID ProposalID;
                LLUUID GroupID;
                raw::LLVariable VoteCast;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ProposalID,"ProposalID");
                    p.process(GroupID,"GroupID");
                    p.process(VoteCast,"VoteCast");
                }

            };


            AgentDataBlock AgentData;
            ProposalDataBlock ProposalData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ProposalData,"ProposalData");
            }

        };

        struct GroupMembersRequestMessage
            : Message
        {
            static char const * name(){ return "GroupMembersRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF016Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupMembersRequestMessage>();
                }
            };


            GroupMembersRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            GroupMembersRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;
                LLUUID RequestID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(RequestID,"RequestID");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct GroupMembersReplyMessage
            : Message
        {
            static char const * name(){ return "GroupMembersReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF016Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupMembersReplyMessage>();
                }
            };


            GroupMembersReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            , MemberData()
            {}

            GroupMembersReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            , MemberData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;
                LLUUID RequestID;
                Int32 MemberCount;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(RequestID,"RequestID");
                    p.process(MemberCount,"MemberCount");
                }

            };

            struct MemberDataBlock
            {
                LLUUID AgentID;
                Int32 Contribution;
                raw::LLVariable OnlineStatus;
                UInt64 AgentPowers;
                raw::LLVariable Title;
                bool IsOwner;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(Contribution,"Contribution");
                    p.process(OnlineStatus,"OnlineStatus");
                    p.process(AgentPowers,"AgentPowers");
                    p.process(Title,"Title");
                    p.process(IsOwner,"IsOwner");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;
            std::vector<MemberDataBlock> MemberData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
                p.process(MemberData,"MemberData");
            }

        };

        struct ActivateGroupMessage
            : Message
        {
            static char const * name(){ return "ActivateGroup"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0170ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ActivateGroupMessage>();
                }
            };


            ActivateGroupMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            ActivateGroupMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct SetGroupContributionMessage
            : Message
        {
            static char const * name(){ return "SetGroupContribution"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0171ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SetGroupContributionMessage>();
                }
            };


            SetGroupContributionMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            SetGroupContributionMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID GroupID;
                Int32 Contribution;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(Contribution,"Contribution");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct SetGroupAcceptNoticesMessage
            : Message
        {
            static char const * name(){ return "SetGroupAcceptNotices"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0172ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SetGroupAcceptNoticesMessage>();
                }
            };


            SetGroupAcceptNoticesMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            , NewData()
            {}

            SetGroupAcceptNoticesMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            , NewData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct DataBlock
            {
                LLUUID GroupID;
                bool AcceptNotices;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(AcceptNotices,"AcceptNotices");
                }

            };

            struct NewDataBlock
            {
                bool ListInProfile;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ListInProfile,"ListInProfile");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;
            NewDataBlock NewData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
                p.process(NewData,"NewData");
            }

        };

        struct GroupRoleDataRequestMessage
            : Message
        {
            static char const * name(){ return "GroupRoleDataRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0173ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupRoleDataRequestMessage>();
                }
            };


            GroupRoleDataRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            GroupRoleDataRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;
                LLUUID RequestID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(RequestID,"RequestID");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct GroupRoleDataReplyMessage
            : Message
        {
            static char const * name(){ return "GroupRoleDataReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0174ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupRoleDataReplyMessage>();
                }
            };


            GroupRoleDataReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            , RoleData()
            {}

            GroupRoleDataReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            , RoleData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;
                LLUUID RequestID;
                Int32 RoleCount;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(RequestID,"RequestID");
                    p.process(RoleCount,"RoleCount");
                }

            };

            struct RoleDataBlock
            {
                LLUUID RoleID;
                raw::LLVariable Name;
                raw::LLVariable Title;
                raw::LLVariable Description;
                UInt64 Powers;
                UInt32 Members;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RoleID,"RoleID");
                    p.process(Name,"Name");
                    p.process(Title,"Title");
                    p.process(Description,"Description");
                    p.process(Powers,"Powers");
                    p.process(Members,"Members");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;
            std::vector<RoleDataBlock> RoleData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
                p.process(RoleData,"RoleData");
            }

        };

        struct GroupRoleMembersRequestMessage
            : Message
        {
            static char const * name(){ return "GroupRoleMembersRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0175ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupRoleMembersRequestMessage>();
                }
            };


            GroupRoleMembersRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            GroupRoleMembersRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;
                LLUUID RequestID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(RequestID,"RequestID");
                }

            };


            AgentDataBlock AgentData;
            GroupDataBlock GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct GroupRoleMembersReplyMessage
            : Message
        {
            static char const * name(){ return "GroupRoleMembersReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0176ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupRoleMembersReplyMessage>();
                }
            };


            GroupRoleMembersReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , MemberData()
            {}

            GroupRoleMembersReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , MemberData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID GroupID;
                LLUUID RequestID;
                UInt32 TotalPairs;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(GroupID,"GroupID");
                    p.process(RequestID,"RequestID");
                    p.process(TotalPairs,"TotalPairs");
                }

            };

            struct MemberDataBlock
            {
                LLUUID RoleID;
                LLUUID MemberID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RoleID,"RoleID");
                    p.process(MemberID,"MemberID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<MemberDataBlock> MemberData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(MemberData,"MemberData");
            }

        };

        struct GroupTitlesRequestMessage
            : Message
        {
            static char const * name(){ return "GroupTitlesRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0177ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupTitlesRequestMessage>();
                }
            };


            GroupTitlesRequestMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            GroupTitlesRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;
                LLUUID RequestID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                    p.process(RequestID,"RequestID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct GroupTitlesReplyMessage
            : Message
        {
            static char const * name(){ return "GroupTitlesReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0178ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupTitlesReplyMessage>();
                }
            };


            GroupTitlesReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            GroupTitlesReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID GroupID;
                LLUUID RequestID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(GroupID,"GroupID");
                    p.process(RequestID,"RequestID");
                }

            };

            struct GroupDataBlock
            {
                raw::LLVariable Title;
                LLUUID RoleID;
                bool Selected;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Title,"Title");
                    p.process(RoleID,"RoleID");
                    p.process(Selected,"Selected");
                }

            };


            AgentDataBlock AgentData;
            std::vector<GroupDataBlock> GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct GroupTitleUpdateMessage
            : Message
        {
            static char const * name(){ return "GroupTitleUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0179ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupTitleUpdateMessage>();
                }
            };


            GroupTitleUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            GroupTitleUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;
                LLUUID TitleRoleID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                    p.process(TitleRoleID,"TitleRoleID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct GroupRoleUpdateMessage
            : Message
        {
            static char const * name(){ return "GroupRoleUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF017Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupRoleUpdateMessage>();
                }
            };


            GroupRoleUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            , RoleData()
            {}

            GroupRoleUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , RoleData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct RoleDataBlock
            {
                LLUUID RoleID;
                raw::LLVariable Name;
                raw::LLVariable Description;
                raw::LLVariable Title;
                UInt64 Powers;
                UInt8 UpdateType;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RoleID,"RoleID");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                    p.process(Title,"Title");
                    p.process(Powers,"Powers");
                    p.process(UpdateType,"UpdateType");
                }

            };


            AgentDataBlock AgentData;
            std::vector<RoleDataBlock> RoleData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RoleData,"RoleData");
            }

        };

        struct LiveHelpGroupRequestMessage
            : Message
        {
            static char const * name(){ return "LiveHelpGroupRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF017Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<LiveHelpGroupRequestMessage>();
                }
            };


            LiveHelpGroupRequestMessage()
            : Message(LowHeader())
            , RequestData()
            {}

            LiveHelpGroupRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , RequestData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct RequestDataBlock
            {
                LLUUID RequestID;
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RequestID,"RequestID");
                    p.process(AgentID,"AgentID");
                }

            };


            RequestDataBlock RequestData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(RequestData,"RequestData");
            }

        };

        struct LiveHelpGroupReplyMessage
            : Message
        {
            static char const * name(){ return "LiveHelpGroupReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF017Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<LiveHelpGroupReplyMessage>();
                }
            };


            LiveHelpGroupReplyMessage()
            : Message(LowHeader())
            , ReplyData()
            {}

            LiveHelpGroupReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , ReplyData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ReplyDataBlock
            {
                LLUUID RequestID;
                LLUUID GroupID;
                raw::LLVariable Selection;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RequestID,"RequestID");
                    p.process(GroupID,"GroupID");
                    p.process(Selection,"Selection");
                }

            };


            ReplyDataBlock ReplyData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ReplyData,"ReplyData");
            }

        };

        struct AgentWearablesRequestMessage
            : Message
        {
            static char const * name(){ return "AgentWearablesRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF017Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentWearablesRequestMessage>();
                }
            };


            AgentWearablesRequestMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            AgentWearablesRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct AgentWearablesUpdateMessage
            : Message
        {
            static char const * name(){ return "AgentWearablesUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF017Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentWearablesUpdateMessage>();
                }
            };


            AgentWearablesUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            , WearableData()
            {}

            AgentWearablesUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , WearableData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 SerialNum;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(SerialNum,"SerialNum");
                }

            };

            struct WearableDataBlock
            {
                LLUUID ItemID;
                LLUUID AssetID;
                UInt8 WearableType;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(AssetID,"AssetID");
                    p.process(WearableType,"WearableType");
                }

            };


            AgentDataBlock AgentData;
            std::vector<WearableDataBlock> WearableData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(WearableData,"WearableData");
            }

        };

        struct AgentIsNowWearingMessage
            : Message
        {
            static char const * name(){ return "AgentIsNowWearing"; }
            static bool const trusted = false;
            enum { id = 0xFFFF017Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentIsNowWearingMessage>();
                }
            };


            AgentIsNowWearingMessage()
            : Message(LowHeader())
            , AgentData()
            , WearableData()
            {}

            AgentIsNowWearingMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , WearableData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct WearableDataBlock
            {
                LLUUID ItemID;
                UInt8 WearableType;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(WearableType,"WearableType");
                }

            };


            AgentDataBlock AgentData;
            std::vector<WearableDataBlock> WearableData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(WearableData,"WearableData");
            }

        };

        struct AgentCachedTextureMessage
            : Message
        {
            static char const * name(){ return "AgentCachedTexture"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0180ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentCachedTextureMessage>();
                }
            };


            AgentCachedTextureMessage()
            : Message(LowHeader())
            , AgentData()
            , WearableData()
            {}

            AgentCachedTextureMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , WearableData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                Int32 SerialNum;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(SerialNum,"SerialNum");
                }

            };

            struct WearableDataBlock
            {
                LLUUID ID;
                UInt8 TextureIndex;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(TextureIndex,"TextureIndex");
                }

            };


            AgentDataBlock AgentData;
            std::vector<WearableDataBlock> WearableData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(WearableData,"WearableData");
            }

        };

        struct AgentCachedTextureResponseMessage
            : Message
        {
            static char const * name(){ return "AgentCachedTextureResponse"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0181ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentCachedTextureResponseMessage>();
                }
            };


            AgentCachedTextureResponseMessage()
            : Message(LowHeader())
            , AgentData()
            , WearableData()
            {}

            AgentCachedTextureResponseMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , WearableData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                Int32 SerialNum;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(SerialNum,"SerialNum");
                }

            };

            struct WearableDataBlock
            {
                LLUUID TextureID;
                UInt8 TextureIndex;
                raw::LLVariable HostName;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TextureID,"TextureID");
                    p.process(TextureIndex,"TextureIndex");
                    p.process(HostName,"HostName");
                }

            };


            AgentDataBlock AgentData;
            std::vector<WearableDataBlock> WearableData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(WearableData,"WearableData");
            }

        };

        struct AgentDataUpdateRequestMessage
            : Message
        {
            static char const * name(){ return "AgentDataUpdateRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0182ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentDataUpdateRequestMessage>();
                }
            };


            AgentDataUpdateRequestMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            AgentDataUpdateRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct AgentDataUpdateMessage
            : Message
        {
            static char const * name(){ return "AgentDataUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0183ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentDataUpdateMessage>();
                }
            };


            AgentDataUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            AgentDataUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                raw::LLVariable FirstName;
                raw::LLVariable LastName;
                raw::LLVariable GroupTitle;
                LLUUID ActiveGroupID;
                UInt64 GroupPowers;
                raw::LLVariable GroupName;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(FirstName,"FirstName");
                    p.process(LastName,"LastName");
                    p.process(GroupTitle,"GroupTitle");
                    p.process(ActiveGroupID,"ActiveGroupID");
                    p.process(GroupPowers,"GroupPowers");
                    p.process(GroupName,"GroupName");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct GroupDataUpdateMessage
            : Message
        {
            static char const * name(){ return "GroupDataUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0184ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<GroupDataUpdateMessage>();
                }
            };


            GroupDataUpdateMessage()
            : Message(LowHeader())
            , AgentGroupData()
            {}

            GroupDataUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentGroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentGroupDataBlock
            {
                LLUUID AgentID;
                LLUUID GroupID;
                UInt64 AgentPowers;
                raw::LLVariable GroupTitle;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(GroupID,"GroupID");
                    p.process(AgentPowers,"AgentPowers");
                    p.process(GroupTitle,"GroupTitle");
                }

            };


            std::vector<AgentGroupDataBlock> AgentGroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentGroupData,"AgentGroupData");
            }

        };

        struct AgentGroupDataUpdateMessage
            : Message
        {
            static char const * name(){ return "AgentGroupDataUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0185ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentGroupDataUpdateMessage>();
                }
            };


            AgentGroupDataUpdateMessage()
            : Message(LowHeader())
            , AgentData()
            , GroupData()
            {}

            AgentGroupDataUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , GroupData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;
                UInt64 GroupPowers;
                bool AcceptNotices;
                LLUUID GroupInsigniaID;
                Int32 Contribution;
                raw::LLVariable GroupName;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(GroupPowers,"GroupPowers");
                    p.process(AcceptNotices,"AcceptNotices");
                    p.process(GroupInsigniaID,"GroupInsigniaID");
                    p.process(Contribution,"Contribution");
                    p.process(GroupName,"GroupName");
                }

            };


            AgentDataBlock AgentData;
            std::vector<GroupDataBlock> GroupData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
            }

        };

        struct AgentDropGroupMessage
            : Message
        {
            static char const * name(){ return "AgentDropGroup"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0186ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentDropGroupMessage>();
                }
            };


            AgentDropGroupMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            AgentDropGroupMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(GroupID,"GroupID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct CreateTrustedCircuitMessage
            : Message
        {
            static char const * name(){ return "CreateTrustedCircuit"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0188ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CreateTrustedCircuitMessage>();
                }
            };


            CreateTrustedCircuitMessage()
            : Message(LowHeader())
            , DataBlock()
            {}

            CreateTrustedCircuitMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , DataBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlockBlock
            {
                LLUUID EndPointID;
                raw::LLFixed<32> Digest;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(EndPointID,"EndPointID");
                    p.process(Digest,"Digest");
                }

            };


            DataBlockBlock DataBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(DataBlock,"DataBlock");
            }

        };

        struct DenyTrustedCircuitMessage
            : Message
        {
            static char const * name(){ return "DenyTrustedCircuit"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0189ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DenyTrustedCircuitMessage>();
                }
            };


            DenyTrustedCircuitMessage()
            : Message(LowHeader())
            , DataBlock()
            {}

            DenyTrustedCircuitMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , DataBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlockBlock
            {
                LLUUID EndPointID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(EndPointID,"EndPointID");
                }

            };


            DataBlockBlock DataBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(DataBlock,"DataBlock");
            }

        };

        struct RequestTrustedCircuitMessage
            : Message
        {
            static char const * name(){ return "RequestTrustedCircuit"; }
            static bool const trusted = false;
            enum { id = 0xFFFF018Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RequestTrustedCircuitMessage>();
                }
            };


            RequestTrustedCircuitMessage()
            : Message(LowHeader())
            {}

            RequestTrustedCircuitMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            



            template<typename Processor>
            void process(Processor & p)
            {
                (void)p; // avoiding unreferenced warnings
            }

        };

        struct RezSingleAttachmentFromInvMessage
            : Message
        {
            static char const * name(){ return "RezSingleAttachmentFromInv"; }
            static bool const trusted = false;
            enum { id = 0xFFFF018Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RezSingleAttachmentFromInvMessage>();
                }
            };


            RezSingleAttachmentFromInvMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            RezSingleAttachmentFromInvMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                LLUUID ItemID;
                LLUUID OwnerID;
                UInt8 AttachmentPt;
                UInt32 ItemFlags;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;
                raw::LLVariable Name;
                raw::LLVariable Description;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(OwnerID,"OwnerID");
                    p.process(AttachmentPt,"AttachmentPt");
                    p.process(ItemFlags,"ItemFlags");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                }

            };


            AgentDataBlock AgentData;
            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct RezMultipleAttachmentsFromInvMessage
            : Message
        {
            static char const * name(){ return "RezMultipleAttachmentsFromInv"; }
            static bool const trusted = false;
            enum { id = 0xFFFF018Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RezMultipleAttachmentsFromInvMessage>();
                }
            };


            RezMultipleAttachmentsFromInvMessage()
            : Message(LowHeader())
            , AgentData()
            , HeaderData()
            , ObjectData()
            {}

            RezMultipleAttachmentsFromInvMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , HeaderData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct HeaderDataBlock
            {
                LLUUID CompoundMsgID;
                UInt8 TotalObjects;
                bool FirstDetachAll;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(CompoundMsgID,"CompoundMsgID");
                    p.process(TotalObjects,"TotalObjects");
                    p.process(FirstDetachAll,"FirstDetachAll");
                }

            };

            struct ObjectDataBlock
            {
                LLUUID ItemID;
                LLUUID OwnerID;
                UInt8 AttachmentPt;
                UInt32 ItemFlags;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;
                raw::LLVariable Name;
                raw::LLVariable Description;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemID,"ItemID");
                    p.process(OwnerID,"OwnerID");
                    p.process(AttachmentPt,"AttachmentPt");
                    p.process(ItemFlags,"ItemFlags");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                }

            };


            AgentDataBlock AgentData;
            HeaderDataBlock HeaderData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(HeaderData,"HeaderData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct DetachAttachmentIntoInvMessage
            : Message
        {
            static char const * name(){ return "DetachAttachmentIntoInv"; }
            static bool const trusted = false;
            enum { id = 0xFFFF018Dul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<DetachAttachmentIntoInvMessage>();
                }
            };


            DetachAttachmentIntoInvMessage()
            : Message(LowHeader())
            , ObjectData()
            {}

            DetachAttachmentIntoInvMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ObjectDataBlock
            {
                LLUUID AgentID;
                LLUUID ItemID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(ItemID,"ItemID");
                }

            };


            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ObjectData,"ObjectData");
            }

        };

        struct CreateNewOutfitAttachmentsMessage
            : Message
        {
            static char const * name(){ return "CreateNewOutfitAttachments"; }
            static bool const trusted = false;
            enum { id = 0xFFFF018Eul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CreateNewOutfitAttachmentsMessage>();
                }
            };


            CreateNewOutfitAttachmentsMessage()
            : Message(LowHeader())
            , AgentData()
            , HeaderData()
            , ObjectData()
            {}

            CreateNewOutfitAttachmentsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , HeaderData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct HeaderDataBlock
            {
                LLUUID NewFolderID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(NewFolderID,"NewFolderID");
                }

            };

            struct ObjectDataBlock
            {
                LLUUID OldItemID;
                LLUUID OldFolderID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(OldItemID,"OldItemID");
                    p.process(OldFolderID,"OldFolderID");
                }

            };


            AgentDataBlock AgentData;
            HeaderDataBlock HeaderData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(HeaderData,"HeaderData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct UserInfoRequestMessage
            : Message
        {
            static char const * name(){ return "UserInfoRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF018Ful };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UserInfoRequestMessage>();
                }
            };


            UserInfoRequestMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            UserInfoRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct UserInfoReplyMessage
            : Message
        {
            static char const * name(){ return "UserInfoReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0190ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UserInfoReplyMessage>();
                }
            };


            UserInfoReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , UserData()
            {}

            UserInfoReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , UserData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct UserDataBlock
            {
                bool IMViaEMail;
                raw::LLVariable DirectoryVisibility;
                raw::LLVariable EMail;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(IMViaEMail,"IMViaEMail");
                    p.process(DirectoryVisibility,"DirectoryVisibility");
                    p.process(EMail,"EMail");
                }

            };


            AgentDataBlock AgentData;
            UserDataBlock UserData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(UserData,"UserData");
            }

        };

        struct UpdateUserInfoMessage
            : Message
        {
            static char const * name(){ return "UpdateUserInfo"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0191ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<UpdateUserInfoMessage>();
                }
            };


            UpdateUserInfoMessage()
            : Message(LowHeader())
            , AgentData()
            , UserData()
            {}

            UpdateUserInfoMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , UserData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct UserDataBlock
            {
                bool IMViaEMail;
                raw::LLVariable DirectoryVisibility;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(IMViaEMail,"IMViaEMail");
                    p.process(DirectoryVisibility,"DirectoryVisibility");
                }

            };


            AgentDataBlock AgentData;
            UserDataBlock UserData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(UserData,"UserData");
            }

        };

        struct InitiateDownloadMessage
            : Message
        {
            static char const * name(){ return "InitiateDownload"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0193ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<InitiateDownloadMessage>();
                }
            };


            InitiateDownloadMessage()
            : Message(LowHeader())
            , AgentData()
            , FileData()
            {}

            InitiateDownloadMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , FileData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct FileDataBlock
            {
                raw::LLVariable SimFilename;
                raw::LLVariable ViewerFilename;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SimFilename,"SimFilename");
                    p.process(ViewerFilename,"ViewerFilename");
                }

            };


            AgentDataBlock AgentData;
            FileDataBlock FileData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(FileData,"FileData");
            }

        };

        struct SystemMessageMessage
            : Message
        {
            static char const * name(){ return "SystemMessage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0194ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SystemMessageMessage>();
                }
            };


            SystemMessageMessage()
            : Message(LowHeader())
            , MethodData()
            , ParamList()
            {}

            SystemMessageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , MethodData()
            , ParamList()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct MethodDataBlock
            {
                raw::LLVariable Method;
                LLUUID Invoice;
                raw::LLFixed<32> Digest;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Method,"Method");
                    p.process(Invoice,"Invoice");
                    p.process(Digest,"Digest");
                }

            };

            struct ParamListBlock
            {
                raw::LLVariable Parameter;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Parameter,"Parameter");
                }

            };


            MethodDataBlock MethodData;
            std::vector<ParamListBlock> ParamList;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(MethodData,"MethodData");
                p.process(ParamList,"ParamList");
            }

        };

        struct MapLayerRequestMessage
            : Message
        {
            static char const * name(){ return "MapLayerRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0195ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MapLayerRequestMessage>();
                }
            };


            MapLayerRequestMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            MapLayerRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 Flags;
                UInt32 EstateID;
                bool Godlike;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(Flags,"Flags");
                    p.process(EstateID,"EstateID");
                    p.process(Godlike,"Godlike");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct MapLayerReplyMessage
            : Message
        {
            static char const * name(){ return "MapLayerReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0196ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MapLayerReplyMessage>();
                }
            };


            MapLayerReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , LayerData()
            {}

            MapLayerReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , LayerData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(Flags,"Flags");
                }

            };

            struct LayerDataBlock
            {
                UInt32 Left;
                UInt32 Right;
                UInt32 Top;
                UInt32 Bottom;
                LLUUID ImageID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Left,"Left");
                    p.process(Right,"Right");
                    p.process(Top,"Top");
                    p.process(Bottom,"Bottom");
                    p.process(ImageID,"ImageID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<LayerDataBlock> LayerData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(LayerData,"LayerData");
            }

        };

        struct MapBlockRequestMessage
            : Message
        {
            static char const * name(){ return "MapBlockRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0197ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MapBlockRequestMessage>();
                }
            };


            MapBlockRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , PositionData()
            {}

            MapBlockRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , PositionData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 Flags;
                UInt32 EstateID;
                bool Godlike;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(Flags,"Flags");
                    p.process(EstateID,"EstateID");
                    p.process(Godlike,"Godlike");
                }

            };

            struct PositionDataBlock
            {
                UInt16 MinX;
                UInt16 MaxX;
                UInt16 MinY;
                UInt16 MaxY;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(MinX,"MinX");
                    p.process(MaxX,"MaxX");
                    p.process(MinY,"MinY");
                    p.process(MaxY,"MaxY");
                }

            };


            AgentDataBlock AgentData;
            PositionDataBlock PositionData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(PositionData,"PositionData");
            }

        };

        struct MapNameRequestMessage
            : Message
        {
            static char const * name(){ return "MapNameRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0198ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MapNameRequestMessage>();
                }
            };


            MapNameRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , NameData()
            {}

            MapNameRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , NameData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 Flags;
                UInt32 EstateID;
                bool Godlike;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(Flags,"Flags");
                    p.process(EstateID,"EstateID");
                    p.process(Godlike,"Godlike");
                }

            };

            struct NameDataBlock
            {
                raw::LLVariable Name;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Name,"Name");
                }

            };


            AgentDataBlock AgentData;
            NameDataBlock NameData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(NameData,"NameData");
            }

        };

        struct MapBlockReplyMessage
            : Message
        {
            static char const * name(){ return "MapBlockReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF0199ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MapBlockReplyMessage>();
                }
            };


            MapBlockReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            MapBlockReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(Flags,"Flags");
                }

            };

            struct DataBlock
            {
                UInt16 X;
                UInt16 Y;
                raw::LLVariable Name;
                UInt8 Access;
                UInt32 RegionFlags;
                UInt8 WaterHeight;
                UInt8 Agents;
                LLUUID MapImageID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(X,"X");
                    p.process(Y,"Y");
                    p.process(Name,"Name");
                    p.process(Access,"Access");
                    p.process(RegionFlags,"RegionFlags");
                    p.process(WaterHeight,"WaterHeight");
                    p.process(Agents,"Agents");
                    p.process(MapImageID,"MapImageID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<DataBlock> Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct MapItemRequestMessage
            : Message
        {
            static char const * name(){ return "MapItemRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF019Aul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MapItemRequestMessage>();
                }
            };


            MapItemRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , RequestData()
            {}

            MapItemRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , RequestData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                UInt32 Flags;
                UInt32 EstateID;
                bool Godlike;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(Flags,"Flags");
                    p.process(EstateID,"EstateID");
                    p.process(Godlike,"Godlike");
                }

            };

            struct RequestDataBlock
            {
                UInt32 ItemType;
                UInt64 RegionHandle;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemType,"ItemType");
                    p.process(RegionHandle,"RegionHandle");
                }

            };


            AgentDataBlock AgentData;
            RequestDataBlock RequestData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RequestData,"RequestData");
            }

        };

        struct MapItemReplyMessage
            : Message
        {
            static char const * name(){ return "MapItemReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF019Bul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MapItemReplyMessage>();
                }
            };


            MapItemReplyMessage()
            : Message(LowHeader())
            , AgentData()
            , RequestData()
            , Data()
            {}

            MapItemReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , RequestData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                UInt32 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(Flags,"Flags");
                }

            };

            struct RequestDataBlock
            {
                UInt32 ItemType;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ItemType,"ItemType");
                }

            };

            struct DataBlock
            {
                UInt32 X;
                UInt32 Y;
                LLUUID ID;
                Int32 Extra;
                Int32 Extra2;
                raw::LLVariable Name;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(X,"X");
                    p.process(Y,"Y");
                    p.process(ID,"ID");
                    p.process(Extra,"Extra");
                    p.process(Extra2,"Extra2");
                    p.process(Name,"Name");
                }

            };


            AgentDataBlock AgentData;
            RequestDataBlock RequestData;
            std::vector<DataBlock> Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RequestData,"RequestData");
                p.process(Data,"Data");
            }

        };

        struct SendPostcardMessage
            : Message
        {
            static char const * name(){ return "SendPostcard"; }
            static bool const trusted = false;
            enum { id = 0xFFFF019Cul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SendPostcardMessage>();
                }
            };


            SendPostcardMessage()
            : Message(LowHeader())
            , AgentData()
            {}

            SendPostcardMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID AssetID;
                raw::LLVector3d PosGlobal;
                raw::LLVariable To;
                raw::LLVariable From;
                raw::LLVariable Name;
                raw::LLVariable Subject;
                raw::LLVariable Msg;
                bool AllowPublish;
                bool MaturePublish;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(AssetID,"AssetID");
                    p.process(PosGlobal,"PosGlobal");
                    p.process(To,"To");
                    p.process(From,"From");
                    p.process(Name,"Name");
                    p.process(Subject,"Subject");
                    p.process(Msg,"Msg");
                    p.process(AllowPublish,"AllowPublish");
                    p.process(MaturePublish,"MaturePublish");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct ParcelMediaCommandMessageMessage
            : Message
        {
            static char const * name(){ return "ParcelMediaCommandMessage"; }
            static bool const trusted = false;
            enum { id = 0xFFFF01A3ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelMediaCommandMessageMessage>();
                }
            };


            ParcelMediaCommandMessageMessage()
            : Message(LowHeader())
            , CommandBlock()
            {}

            ParcelMediaCommandMessageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , CommandBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct CommandBlockBlock
            {
                UInt32 Flags;
                UInt32 Command;
                Real32 Time;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Flags,"Flags");
                    p.process(Command,"Command");
                    p.process(Time,"Time");
                }

            };


            CommandBlockBlock CommandBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(CommandBlock,"CommandBlock");
            }

        };

        struct ParcelMediaUpdateMessage
            : Message
        {
            static char const * name(){ return "ParcelMediaUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFFFF01A4ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelMediaUpdateMessage>();
                }
            };


            ParcelMediaUpdateMessage()
            : Message(LowHeader())
            , DataBlock()
            , DataBlockExtended()
            {}

            ParcelMediaUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , DataBlock()
            , DataBlockExtended()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlockBlock
            {
                raw::LLVariable MediaURL;
                LLUUID MediaID;
                UInt8 MediaAutoScale;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(MediaURL,"MediaURL");
                    p.process(MediaID,"MediaID");
                    p.process(MediaAutoScale,"MediaAutoScale");
                }

            };

            struct DataBlockExtendedBlock
            {
                raw::LLVariable MediaType;
                raw::LLVariable MediaDesc;
                Int32 MediaWidth;
                Int32 MediaHeight;
                UInt8 MediaLoop;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(MediaType,"MediaType");
                    p.process(MediaDesc,"MediaDesc");
                    p.process(MediaWidth,"MediaWidth");
                    p.process(MediaHeight,"MediaHeight");
                    p.process(MediaLoop,"MediaLoop");
                }

            };


            DataBlockBlock DataBlock;
            DataBlockExtendedBlock DataBlockExtended;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(DataBlock,"DataBlock");
                p.process(DataBlockExtended,"DataBlockExtended");
            }

        };

        struct LandStatRequestMessage
            : Message
        {
            static char const * name(){ return "LandStatRequest"; }
            static bool const trusted = false;
            enum { id = 0xFFFF01A5ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<LandStatRequestMessage>();
                }
            };


            LandStatRequestMessage()
            : Message(LowHeader())
            , AgentData()
            , RequestData()
            {}

            LandStatRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , RequestData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct RequestDataBlock
            {
                UInt32 ReportType;
                UInt32 RequestFlags;
                raw::LLVariable Filter;
                Int32 ParcelLocalID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ReportType,"ReportType");
                    p.process(RequestFlags,"RequestFlags");
                    p.process(Filter,"Filter");
                    p.process(ParcelLocalID,"ParcelLocalID");
                }

            };


            AgentDataBlock AgentData;
            RequestDataBlock RequestData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RequestData,"RequestData");
            }

        };

        struct LandStatReplyMessage
            : Message
        {
            static char const * name(){ return "LandStatReply"; }
            static bool const trusted = false;
            enum { id = 0xFFFF01A6ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<LandStatReplyMessage>();
                }
            };


            LandStatReplyMessage()
            : Message(LowHeader())
            , RequestData()
            , ReportData()
            {}

            LandStatReplyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , RequestData()
            , ReportData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct RequestDataBlock
            {
                UInt32 ReportType;
                UInt32 RequestFlags;
                UInt32 TotalObjectCount;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ReportType,"ReportType");
                    p.process(RequestFlags,"RequestFlags");
                    p.process(TotalObjectCount,"TotalObjectCount");
                }

            };

            struct ReportDataBlock
            {
                UInt32 TaskLocalID;
                LLUUID TaskID;
                Real32 LocationX;
                Real32 LocationY;
                Real32 LocationZ;
                Real32 Score;
                raw::LLVariable TaskName;
                raw::LLVariable OwnerName;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TaskLocalID,"TaskLocalID");
                    p.process(TaskID,"TaskID");
                    p.process(LocationX,"LocationX");
                    p.process(LocationY,"LocationY");
                    p.process(LocationZ,"LocationZ");
                    p.process(Score,"Score");
                    p.process(TaskName,"TaskName");
                    p.process(OwnerName,"OwnerName");
                }

            };


            RequestDataBlock RequestData;
            std::vector<ReportDataBlock> ReportData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(RequestData,"RequestData");
                p.process(ReportData,"ReportData");
            }

        };

        struct ErrorMessage
            : Message
        {
            static char const * name(){ return "Error"; }
            static bool const trusted = false;
            enum { id = 0xFFFF01A7ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ErrorMessage>();
                }
            };


            ErrorMessage()
            : Message(LowHeader())
            , AgentData()
            , Data()
            {}

            ErrorMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , Data()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };

            struct DataBlock
            {
                Int32 Code;
                raw::LLVariable Token;
                LLUUID ID;
                raw::LLVariable System;
                raw::LLVariable Message;
                raw::LLVariable Data;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Code,"Code");
                    p.process(Token,"Token");
                    p.process(ID,"ID");
                    p.process(System,"System");
                    p.process(Message,"Message");
                    p.process(Data,"Data");
                }

            };


            AgentDataBlock AgentData;
            DataBlock Data;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Data,"Data");
            }

        };

        struct ObjectIncludeInSearchMessage
            : Message
        {
            static char const * name(){ return "ObjectIncludeInSearch"; }
            static bool const trusted = false;
            enum { id = 0xFFFF01A8ul };
            static FrequencyType const frequency = FT_LOW;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectIncludeInSearchMessage>();
                }
            };


            ObjectIncludeInSearchMessage()
            : Message(LowHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectIncludeInSearchMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                bool IncludeInSearch;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(IncludeInSearch,"IncludeInSearch");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct PacketAckMessage
            : Message
        {
            static char const * name(){ return "PacketAck"; }
            static bool const trusted = false;
            enum { id = 0xFFFFFFFBul };
            static FrequencyType const frequency = FT_FIXED;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<PacketAckMessage>();
                }
            };


            PacketAckMessage()
            : Message(LowHeader())
            , Packets()
            {}

            PacketAckMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , Packets()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct PacketsBlock
            {
                UInt32 ID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                }

            };


            std::vector<PacketsBlock> Packets;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Packets,"Packets");
            }

        };

        struct OpenCircuitMessage
            : Message
        {
            static char const * name(){ return "OpenCircuit"; }
            static bool const trusted = false;
            enum { id = 0xFFFFFFFCul };
            static FrequencyType const frequency = FT_FIXED;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<OpenCircuitMessage>();
                }
            };


            OpenCircuitMessage()
            : Message(LowHeader())
            , CircuitInfo()
            {}

            OpenCircuitMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            , CircuitInfo()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct CircuitInfoBlock
            {
                raw::LLIPAddress IP;
                raw::LLIPPort Port;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(IP,"IP");
                    p.process(Port,"Port");
                }

            };


            CircuitInfoBlock CircuitInfo;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(CircuitInfo,"CircuitInfo");
            }

        };

        struct CloseCircuitMessage
            : Message
        {
            static char const * name(){ return "CloseCircuit"; }
            static bool const trusted = false;
            enum { id = 0xFFFFFFFDul };
            static FrequencyType const frequency = FT_FIXED;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CloseCircuitMessage>();
                }
            };


            CloseCircuitMessage()
            : Message(LowHeader())
            {}

            CloseCircuitMessage(ByteBuffer & data, std::size_t & pos)
            : Message(LowHeader(data, pos))
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            



            template<typename Processor>
            void process(Processor & p)
            {
                (void)p; // avoiding unreferenced warnings
            }

        };

        struct ObjectAddMessage
            : Message
        {
            static char const * name(){ return "ObjectAdd"; }
            static bool const trusted = false;
            enum { id = 0xFF000001ul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectAddMessage>();
                }
            };


            ObjectAddMessage()
            : Message(MediumHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectAddMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                LLUUID GroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(GroupID,"GroupID");
                }

            };

            struct ObjectDataBlock
            {
                UInt8 PCode;
                UInt8 Material;
                UInt32 AddFlags;
                UInt8 PathCurve;
                UInt8 ProfileCurve;
                UInt16 PathBegin;
                UInt16 PathEnd;
                UInt8 PathScaleX;
                UInt8 PathScaleY;
                UInt8 PathShearX;
                UInt8 PathShearY;
                Int8 PathTwist;
                Int8 PathTwistBegin;
                Int8 PathRadiusOffset;
                Int8 PathTaperX;
                Int8 PathTaperY;
                UInt8 PathRevolutions;
                Int8 PathSkew;
                UInt16 ProfileBegin;
                UInt16 ProfileEnd;
                UInt16 ProfileHollow;
                UInt8 BypassRaycast;
                raw::LLVector3 RayStart;
                raw::LLVector3 RayEnd;
                LLUUID RayTargetID;
                UInt8 RayEndIsIntersection;
                raw::LLVector3 Scale;
                raw::LLQuaternion Rotation;
                UInt8 State;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(PCode,"PCode");
                    p.process(Material,"Material");
                    p.process(AddFlags,"AddFlags");
                    p.process(PathCurve,"PathCurve");
                    p.process(ProfileCurve,"ProfileCurve");
                    p.process(PathBegin,"PathBegin");
                    p.process(PathEnd,"PathEnd");
                    p.process(PathScaleX,"PathScaleX");
                    p.process(PathScaleY,"PathScaleY");
                    p.process(PathShearX,"PathShearX");
                    p.process(PathShearY,"PathShearY");
                    p.process(PathTwist,"PathTwist");
                    p.process(PathTwistBegin,"PathTwistBegin");
                    p.process(PathRadiusOffset,"PathRadiusOffset");
                    p.process(PathTaperX,"PathTaperX");
                    p.process(PathTaperY,"PathTaperY");
                    p.process(PathRevolutions,"PathRevolutions");
                    p.process(PathSkew,"PathSkew");
                    p.process(ProfileBegin,"ProfileBegin");
                    p.process(ProfileEnd,"ProfileEnd");
                    p.process(ProfileHollow,"ProfileHollow");
                    p.process(BypassRaycast,"BypassRaycast");
                    p.process(RayStart,"RayStart");
                    p.process(RayEnd,"RayEnd");
                    p.process(RayTargetID,"RayTargetID");
                    p.process(RayEndIsIntersection,"RayEndIsIntersection");
                    p.process(Scale,"Scale");
                    p.process(Rotation,"Rotation");
                    p.process(State,"State");
                }

            };


            AgentDataBlock AgentData;
            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct MultipleObjectUpdateMessage
            : Message
        {
            static char const * name(){ return "MultipleObjectUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFF000002ul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<MultipleObjectUpdateMessage>();
                }
            };


            MultipleObjectUpdateMessage()
            : Message(MediumHeader())
            , AgentData()
            , ObjectData()
            {}

            MultipleObjectUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                UInt8 Type;
                raw::LLVariable Data;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(Type,"Type");
                    p.process(Data,"Data");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct RequestMultipleObjectsMessage
            : Message
        {
            static char const * name(){ return "RequestMultipleObjects"; }
            static bool const trusted = false;
            enum { id = 0xFF000003ul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RequestMultipleObjectsMessage>();
                }
            };


            RequestMultipleObjectsMessage()
            : Message(MediumHeader())
            , AgentData()
            , ObjectData()
            {}

            RequestMultipleObjectsMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt8 CacheMissType;
                UInt32 ID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(CacheMissType,"CacheMissType");
                    p.process(ID,"ID");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectPositionMessage
            : Message
        {
            static char const * name(){ return "ObjectPosition"; }
            static bool const trusted = false;
            enum { id = 0xFF000004ul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectPositionMessage>();
                }
            };


            ObjectPositionMessage()
            : Message(MediumHeader())
            , AgentData()
            , ObjectData()
            {}

            ObjectPositionMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ObjectLocalID;
                raw::LLVector3 Position;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectLocalID,"ObjectLocalID");
                    p.process(Position,"Position");
                }

            };


            AgentDataBlock AgentData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct RequestObjectPropertiesFamilyMessage
            : Message
        {
            static char const * name(){ return "RequestObjectPropertiesFamily"; }
            static bool const trusted = false;
            enum { id = 0xFF000005ul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RequestObjectPropertiesFamilyMessage>();
                }
            };


            RequestObjectPropertiesFamilyMessage()
            : Message(MediumHeader())
            , AgentData()
            , ObjectData()
            {}

            RequestObjectPropertiesFamilyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , AgentData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 RequestFlags;
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RequestFlags,"RequestFlags");
                    p.process(ObjectID,"ObjectID");
                }

            };


            AgentDataBlock AgentData;
            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct CoarseLocationUpdateMessage
            : Message
        {
            static char const * name(){ return "CoarseLocationUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFF000006ul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CoarseLocationUpdateMessage>();
                }
            };


            CoarseLocationUpdateMessage()
            : Message(MediumHeader())
            , Location()
            , Index()
            , AgentData()
            {}

            CoarseLocationUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , Location()
            , Index()
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct LocationBlock
            {
                UInt8 X;
                UInt8 Y;
                UInt8 Z;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(X,"X");
                    p.process(Y,"Y");
                    p.process(Z,"Z");
                }

            };

            struct IndexBlock
            {
                Int16 You;
                Int16 Prey;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(You,"You");
                    p.process(Prey,"Prey");
                }

            };

            struct AgentDataBlock
            {
                LLUUID AgentID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                }

            };


            std::vector<LocationBlock> Location;
            IndexBlock Index;
            std::vector<AgentDataBlock> AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Location,"Location");
                p.process(Index,"Index");
                p.process(AgentData,"AgentData");
            }

        };

        struct CrossedRegionMessage
            : Message
        {
            static char const * name(){ return "CrossedRegion"; }
            static bool const trusted = false;
            enum { id = 0xFF000007ul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CrossedRegionMessage>();
                }
            };


            CrossedRegionMessage()
            : Message(MediumHeader())
            , AgentData()
            , RegionData()
            , Info()
            {}

            CrossedRegionMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , AgentData()
            , RegionData()
            , Info()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct RegionDataBlock
            {
                raw::LLIPAddress SimIP;
                raw::LLIPPort SimPort;
                UInt64 RegionHandle;
                raw::LLVariable SeedCapability;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SimIP,"SimIP");
                    p.process(SimPort,"SimPort");
                    p.process(RegionHandle,"RegionHandle");
                    p.process(SeedCapability,"SeedCapability");
                }

            };

            struct InfoBlock
            {
                raw::LLVector3 Position;
                raw::LLVector3 LookAt;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Position,"Position");
                    p.process(LookAt,"LookAt");
                }

            };


            AgentDataBlock AgentData;
            RegionDataBlock RegionData;
            InfoBlock Info;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RegionData,"RegionData");
                p.process(Info,"Info");
            }

        };

        struct ConfirmEnableSimulatorMessage
            : Message
        {
            static char const * name(){ return "ConfirmEnableSimulator"; }
            static bool const trusted = false;
            enum { id = 0xFF000008ul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ConfirmEnableSimulatorMessage>();
                }
            };


            ConfirmEnableSimulatorMessage()
            : Message(MediumHeader())
            , AgentData()
            {}

            ConfirmEnableSimulatorMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct ObjectPropertiesMessage
            : Message
        {
            static char const * name(){ return "ObjectProperties"; }
            static bool const trusted = false;
            enum { id = 0xFF000009ul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectPropertiesMessage>();
                }
            };


            ObjectPropertiesMessage()
            : Message(MediumHeader())
            , ObjectData()
            {}

            ObjectPropertiesMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ObjectDataBlock
            {
                LLUUID ObjectID;
                LLUUID CreatorID;
                LLUUID OwnerID;
                LLUUID GroupID;
                UInt64 CreationDate;
                UInt32 BaseMask;
                UInt32 OwnerMask;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;
                Int32 OwnershipCost;
                UInt8 SaleType;
                Int32 SalePrice;
                UInt8 AggregatePerms;
                UInt8 AggregatePermTextures;
                UInt8 AggregatePermTexturesOwner;
                UInt32 Category;
                Int16 InventorySerial;
                LLUUID ItemID;
                LLUUID FolderID;
                LLUUID FromTaskID;
                LLUUID LastOwnerID;
                raw::LLVariable Name;
                raw::LLVariable Description;
                raw::LLVariable TouchName;
                raw::LLVariable SitName;
                raw::LLVariable TextureID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(CreatorID,"CreatorID");
                    p.process(OwnerID,"OwnerID");
                    p.process(GroupID,"GroupID");
                    p.process(CreationDate,"CreationDate");
                    p.process(BaseMask,"BaseMask");
                    p.process(OwnerMask,"OwnerMask");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(OwnershipCost,"OwnershipCost");
                    p.process(SaleType,"SaleType");
                    p.process(SalePrice,"SalePrice");
                    p.process(AggregatePerms,"AggregatePerms");
                    p.process(AggregatePermTextures,"AggregatePermTextures");
                    p.process(AggregatePermTexturesOwner,"AggregatePermTexturesOwner");
                    p.process(Category,"Category");
                    p.process(InventorySerial,"InventorySerial");
                    p.process(ItemID,"ItemID");
                    p.process(FolderID,"FolderID");
                    p.process(FromTaskID,"FromTaskID");
                    p.process(LastOwnerID,"LastOwnerID");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                    p.process(TouchName,"TouchName");
                    p.process(SitName,"SitName");
                    p.process(TextureID,"TextureID");
                }

            };


            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectPropertiesFamilyMessage
            : Message
        {
            static char const * name(){ return "ObjectPropertiesFamily"; }
            static bool const trusted = false;
            enum { id = 0xFF00000Aul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectPropertiesFamilyMessage>();
                }
            };


            ObjectPropertiesFamilyMessage()
            : Message(MediumHeader())
            , ObjectData()
            {}

            ObjectPropertiesFamilyMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ObjectDataBlock
            {
                UInt32 RequestFlags;
                LLUUID ObjectID;
                LLUUID OwnerID;
                LLUUID GroupID;
                UInt32 BaseMask;
                UInt32 OwnerMask;
                UInt32 GroupMask;
                UInt32 EveryoneMask;
                UInt32 NextOwnerMask;
                Int32 OwnershipCost;
                UInt8 SaleType;
                Int32 SalePrice;
                UInt32 Category;
                LLUUID LastOwnerID;
                raw::LLVariable Name;
                raw::LLVariable Description;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RequestFlags,"RequestFlags");
                    p.process(ObjectID,"ObjectID");
                    p.process(OwnerID,"OwnerID");
                    p.process(GroupID,"GroupID");
                    p.process(BaseMask,"BaseMask");
                    p.process(OwnerMask,"OwnerMask");
                    p.process(GroupMask,"GroupMask");
                    p.process(EveryoneMask,"EveryoneMask");
                    p.process(NextOwnerMask,"NextOwnerMask");
                    p.process(OwnershipCost,"OwnershipCost");
                    p.process(SaleType,"SaleType");
                    p.process(SalePrice,"SalePrice");
                    p.process(Category,"Category");
                    p.process(LastOwnerID,"LastOwnerID");
                    p.process(Name,"Name");
                    p.process(Description,"Description");
                }

            };


            ObjectDataBlock ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ParcelPropertiesRequestMessage
            : Message
        {
            static char const * name(){ return "ParcelPropertiesRequest"; }
            static bool const trusted = false;
            enum { id = 0xFF00000Bul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelPropertiesRequestMessage>();
                }
            };


            ParcelPropertiesRequestMessage()
            : Message(MediumHeader())
            , AgentData()
            , ParcelData()
            {}

            ParcelPropertiesRequestMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , AgentData()
            , ParcelData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct ParcelDataBlock
            {
                Int32 SequenceID;
                Real32 West;
                Real32 South;
                Real32 East;
                Real32 North;
                bool SnapSelection;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SequenceID,"SequenceID");
                    p.process(West,"West");
                    p.process(South,"South");
                    p.process(East,"East");
                    p.process(North,"North");
                    p.process(SnapSelection,"SnapSelection");
                }

            };


            AgentDataBlock AgentData;
            ParcelDataBlock ParcelData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(ParcelData,"ParcelData");
            }

        };

        struct AttachedSoundMessage
            : Message
        {
            static char const * name(){ return "AttachedSound"; }
            static bool const trusted = false;
            enum { id = 0xFF00000Dul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AttachedSoundMessage>();
                }
            };


            AttachedSoundMessage()
            : Message(MediumHeader())
            , DataBlock()
            {}

            AttachedSoundMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , DataBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlockBlock
            {
                LLUUID SoundID;
                LLUUID ObjectID;
                LLUUID OwnerID;
                Real32 Gain;
                UInt8 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SoundID,"SoundID");
                    p.process(ObjectID,"ObjectID");
                    p.process(OwnerID,"OwnerID");
                    p.process(Gain,"Gain");
                    p.process(Flags,"Flags");
                }

            };


            DataBlockBlock DataBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(DataBlock,"DataBlock");
            }

        };

        struct AttachedSoundGainChangeMessage
            : Message
        {
            static char const * name(){ return "AttachedSoundGainChange"; }
            static bool const trusted = false;
            enum { id = 0xFF00000Eul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AttachedSoundGainChangeMessage>();
                }
            };


            AttachedSoundGainChangeMessage()
            : Message(MediumHeader())
            , DataBlock()
            {}

            AttachedSoundGainChangeMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , DataBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlockBlock
            {
                LLUUID ObjectID;
                Real32 Gain;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(Gain,"Gain");
                }

            };


            DataBlockBlock DataBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(DataBlock,"DataBlock");
            }

        };

        struct PreloadSoundMessage
            : Message
        {
            static char const * name(){ return "PreloadSound"; }
            static bool const trusted = false;
            enum { id = 0xFF00000Ful };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<PreloadSoundMessage>();
                }
            };


            PreloadSoundMessage()
            : Message(MediumHeader())
            , DataBlock()
            {}

            PreloadSoundMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , DataBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct DataBlockBlock
            {
                LLUUID ObjectID;
                LLUUID OwnerID;
                LLUUID SoundID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                    p.process(OwnerID,"OwnerID");
                    p.process(SoundID,"SoundID");
                }

            };


            std::vector<DataBlockBlock> DataBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(DataBlock,"DataBlock");
            }

        };

        struct ViewerEffectMessage
            : Message
        {
            static char const * name(){ return "ViewerEffect"; }
            static bool const trusted = false;
            enum { id = 0xFF000011ul };
            static FrequencyType const frequency = FT_MEDIUM;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ViewerEffectMessage>();
                }
            };


            ViewerEffectMessage()
            : Message(MediumHeader())
            , AgentData()
            , Effect()
            {}

            ViewerEffectMessage(ByteBuffer & data, std::size_t & pos)
            : Message(MediumHeader(data, pos))
            , AgentData()
            , Effect()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct EffectBlock
            {
                LLUUID ID;
                LLUUID AgentID;
                UInt8 Type;
                Real32 Duration;
                raw::LLFixed<4> Color;
                raw::LLVariable TypeData;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(AgentID,"AgentID");
                    p.process(Type,"Type");
                    p.process(Duration,"Duration");
                    p.process(Color,"Color");
                    p.process(TypeData,"TypeData");
                }

            };


            AgentDataBlock AgentData;
            std::vector<EffectBlock> Effect;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(Effect,"Effect");
            }

        };

        struct StartPingCheckMessage
            : Message
        {
            static char const * name(){ return "StartPingCheck"; }
            static bool const trusted = false;
            enum { id = 0x1ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<StartPingCheckMessage>();
                }
            };


            StartPingCheckMessage()
            : Message(HighHeader())
            , PingID()
            {}

            StartPingCheckMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , PingID()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct PingIDBlock
            {
                UInt8 PingID;
                UInt32 OldestUnacked;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(PingID,"PingID");
                    p.process(OldestUnacked,"OldestUnacked");
                }

            };


            PingIDBlock PingID;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(PingID,"PingID");
            }

        };

        struct CompletePingCheckMessage
            : Message
        {
            static char const * name(){ return "CompletePingCheck"; }
            static bool const trusted = false;
            enum { id = 0x2ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CompletePingCheckMessage>();
                }
            };


            CompletePingCheckMessage()
            : Message(HighHeader())
            , PingID()
            {}

            CompletePingCheckMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , PingID()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct PingIDBlock
            {
                UInt8 PingID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(PingID,"PingID");
                }

            };


            PingIDBlock PingID;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(PingID,"PingID");
            }

        };

        struct AgentUpdateMessage
            : Message
        {
            static char const * name(){ return "AgentUpdate"; }
            static bool const trusted = false;
            enum { id = 0x4ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentUpdateMessage>();
                }
            };


            AgentUpdateMessage()
            : Message(HighHeader())
            , AgentData()
            {}

            AgentUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;
                raw::LLQuaternion BodyRotation;
                raw::LLQuaternion HeadRotation;
                UInt8 State;
                raw::LLVector3 CameraCenter;
                raw::LLVector3 CameraAtAxis;
                raw::LLVector3 CameraLeftAxis;
                raw::LLVector3 CameraUpAxis;
                Real32 Far;
                UInt32 ControlFlags;
                UInt8 Flags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(BodyRotation,"BodyRotation");
                    p.process(HeadRotation,"HeadRotation");
                    p.process(State,"State");
                    p.process(CameraCenter,"CameraCenter");
                    p.process(CameraAtAxis,"CameraAtAxis");
                    p.process(CameraLeftAxis,"CameraLeftAxis");
                    p.process(CameraUpAxis,"CameraUpAxis");
                    p.process(Far,"Far");
                    p.process(ControlFlags,"ControlFlags");
                    p.process(Flags,"Flags");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct AgentAnimationMessage
            : Message
        {
            static char const * name(){ return "AgentAnimation"; }
            static bool const trusted = false;
            enum { id = 0x5ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentAnimationMessage>();
                }
            };


            AgentAnimationMessage()
            : Message(HighHeader())
            , AgentData()
            , AnimationList()
            , PhysicalAvatarEventList()
            {}

            AgentAnimationMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , AgentData()
            , AnimationList()
            , PhysicalAvatarEventList()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct AnimationListBlock
            {
                LLUUID AnimID;
                bool StartAnim;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AnimID,"AnimID");
                    p.process(StartAnim,"StartAnim");
                }

            };

            struct PhysicalAvatarEventListBlock
            {
                raw::LLVariable TypeData;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TypeData,"TypeData");
                }

            };


            AgentDataBlock AgentData;
            std::vector<AnimationListBlock> AnimationList;
            std::vector<PhysicalAvatarEventListBlock> PhysicalAvatarEventList;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(AnimationList,"AnimationList");
                p.process(PhysicalAvatarEventList,"PhysicalAvatarEventList");
            }

        };

        struct AgentRequestSitMessage
            : Message
        {
            static char const * name(){ return "AgentRequestSit"; }
            static bool const trusted = false;
            enum { id = 0x6ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentRequestSitMessage>();
                }
            };


            AgentRequestSitMessage()
            : Message(HighHeader())
            , AgentData()
            , TargetObject()
            {}

            AgentRequestSitMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , AgentData()
            , TargetObject()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct TargetObjectBlock
            {
                LLUUID TargetID;
                raw::LLVector3 Offset;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TargetID,"TargetID");
                    p.process(Offset,"Offset");
                }

            };


            AgentDataBlock AgentData;
            TargetObjectBlock TargetObject;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(TargetObject,"TargetObject");
            }

        };

        struct AgentSitMessage
            : Message
        {
            static char const * name(){ return "AgentSit"; }
            static bool const trusted = false;
            enum { id = 0x7ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AgentSitMessage>();
                }
            };


            AgentSitMessage()
            : Message(HighHeader())
            , AgentData()
            {}

            AgentSitMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct RequestImageMessage
            : Message
        {
            static char const * name(){ return "RequestImage"; }
            static bool const trusted = false;
            enum { id = 0x8ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<RequestImageMessage>();
                }
            };


            RequestImageMessage()
            : Message(HighHeader())
            , AgentData()
            , RequestImage()
            {}

            RequestImageMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , AgentData()
            , RequestImage()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };

            struct RequestImageBlock
            {
                LLUUID Image;
                Int8 DiscardLevel;
                Real32 DownloadPriority;
                UInt32 Packet;
                UInt8 Type;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Image,"Image");
                    p.process(DiscardLevel,"DiscardLevel");
                    p.process(DownloadPriority,"DownloadPriority");
                    p.process(Packet,"Packet");
                    p.process(Type,"Type");
                }

            };


            AgentDataBlock AgentData;
            std::vector<RequestImageBlock> RequestImage;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(RequestImage,"RequestImage");
            }

        };

        struct ImageDataMessage
            : Message
        {
            static char const * name(){ return "ImageData"; }
            static bool const trusted = false;
            enum { id = 0x9ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ImageDataMessage>();
                }
            };


            ImageDataMessage()
            : Message(HighHeader())
            , ImageID()
            , ImageData()
            {}

            ImageDataMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , ImageID()
            , ImageData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ImageIDBlock
            {
                LLUUID ID;
                UInt8 Codec;
                UInt32 Size;
                UInt16 Packets;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(Codec,"Codec");
                    p.process(Size,"Size");
                    p.process(Packets,"Packets");
                }

            };

            struct ImageDataBlock
            {
                raw::LLVariable Data;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Data,"Data");
                }

            };


            ImageIDBlock ImageID;
            ImageDataBlock ImageData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ImageID,"ImageID");
                p.process(ImageData,"ImageData");
            }

        };

        struct ImagePacketMessage
            : Message
        {
            static char const * name(){ return "ImagePacket"; }
            static bool const trusted = false;
            enum { id = 0xAul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ImagePacketMessage>();
                }
            };


            ImagePacketMessage()
            : Message(HighHeader())
            , ImageID()
            , ImageData()
            {}

            ImagePacketMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , ImageID()
            , ImageData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ImageIDBlock
            {
                LLUUID ID;
                UInt16 Packet;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(Packet,"Packet");
                }

            };

            struct ImageDataBlock
            {
                raw::LLVariable Data;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Data,"Data");
                }

            };


            ImageIDBlock ImageID;
            ImageDataBlock ImageData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ImageID,"ImageID");
                p.process(ImageData,"ImageData");
            }

        };

        struct LayerDataMessage
            : Message
        {
            static char const * name(){ return "LayerData"; }
            static bool const trusted = false;
            enum { id = 0xBul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<LayerDataMessage>();
                }
            };


            LayerDataMessage()
            : Message(HighHeader())
            , LayerID()
            , LayerData()
            {}

            LayerDataMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , LayerID()
            , LayerData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct LayerIDBlock
            {
                UInt8 Type;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Type,"Type");
                }

            };

            struct LayerDataBlock
            {
                raw::LLVariable Data;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Data,"Data");
                }

            };


            LayerIDBlock LayerID;
            LayerDataBlock LayerData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(LayerID,"LayerID");
                p.process(LayerData,"LayerData");
            }

        };

        struct ObjectUpdateMessage
            : Message
        {
            static char const * name(){ return "ObjectUpdate"; }
            static bool const trusted = false;
            enum { id = 0xCul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectUpdateMessage>();
                }
            };


            ObjectUpdateMessage()
            : Message(HighHeader())
            , RegionData()
            , ObjectData()
            {}

            ObjectUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , RegionData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct RegionDataBlock
            {
                UInt64 RegionHandle;
                UInt16 TimeDilation;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionHandle,"RegionHandle");
                    p.process(TimeDilation,"TimeDilation");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ID;
                UInt8 State;
                LLUUID FullID;
                UInt32 CRC;
                UInt8 PCode;
                UInt8 Material;
                UInt8 ClickAction;
                raw::LLVector3 Scale;
                raw::LLVariable ObjectData;
                UInt32 ParentID;
                UInt32 UpdateFlags;
                UInt8 PathCurve;
                UInt8 ProfileCurve;
                UInt16 PathBegin;
                UInt16 PathEnd;
                UInt8 PathScaleX;
                UInt8 PathScaleY;
                UInt8 PathShearX;
                UInt8 PathShearY;
                Int8 PathTwist;
                Int8 PathTwistBegin;
                Int8 PathRadiusOffset;
                Int8 PathTaperX;
                Int8 PathTaperY;
                UInt8 PathRevolutions;
                Int8 PathSkew;
                UInt16 ProfileBegin;
                UInt16 ProfileEnd;
                UInt16 ProfileHollow;
                raw::LLVariable TextureEntry;
                raw::LLVariable TextureAnim;
                raw::LLVariable NameValue;
                raw::LLVariable Data;
                raw::LLVariable Text;
                raw::LLFixed<4> TextColor;
                raw::LLVariable MediaURL;
                raw::LLVariable PSBlock;
                raw::LLVariable ExtraParams;
                LLUUID Sound;
                LLUUID OwnerID;
                Real32 Gain;
                UInt8 Flags;
                Real32 Radius;
                UInt8 JointType;
                raw::LLVector3 JointPivot;
                raw::LLVector3 JointAxisOrAnchor;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(State,"State");
                    p.process(FullID,"FullID");
                    p.process(CRC,"CRC");
                    p.process(PCode,"PCode");
                    p.process(Material,"Material");
                    p.process(ClickAction,"ClickAction");
                    p.process(Scale,"Scale");
                    p.process(ObjectData,"ObjectData");
                    p.process(ParentID,"ParentID");
                    p.process(UpdateFlags,"UpdateFlags");
                    p.process(PathCurve,"PathCurve");
                    p.process(ProfileCurve,"ProfileCurve");
                    p.process(PathBegin,"PathBegin");
                    p.process(PathEnd,"PathEnd");
                    p.process(PathScaleX,"PathScaleX");
                    p.process(PathScaleY,"PathScaleY");
                    p.process(PathShearX,"PathShearX");
                    p.process(PathShearY,"PathShearY");
                    p.process(PathTwist,"PathTwist");
                    p.process(PathTwistBegin,"PathTwistBegin");
                    p.process(PathRadiusOffset,"PathRadiusOffset");
                    p.process(PathTaperX,"PathTaperX");
                    p.process(PathTaperY,"PathTaperY");
                    p.process(PathRevolutions,"PathRevolutions");
                    p.process(PathSkew,"PathSkew");
                    p.process(ProfileBegin,"ProfileBegin");
                    p.process(ProfileEnd,"ProfileEnd");
                    p.process(ProfileHollow,"ProfileHollow");
                    p.process(TextureEntry,"TextureEntry");
                    p.process(TextureAnim,"TextureAnim");
                    p.process(NameValue,"NameValue");
                    p.process(Data,"Data");
                    p.process(Text,"Text");
                    p.process(TextColor,"TextColor");
                    p.process(MediaURL,"MediaURL");
                    p.process(PSBlock,"PSBlock");
                    p.process(ExtraParams,"ExtraParams");
                    p.process(Sound,"Sound");
                    p.process(OwnerID,"OwnerID");
                    p.process(Gain,"Gain");
                    p.process(Flags,"Flags");
                    p.process(Radius,"Radius");
                    p.process(JointType,"JointType");
                    p.process(JointPivot,"JointPivot");
                    p.process(JointAxisOrAnchor,"JointAxisOrAnchor");
                }

            };


            RegionDataBlock RegionData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(RegionData,"RegionData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectUpdateCompressedMessage
            : Message
        {
            static char const * name(){ return "ObjectUpdateCompressed"; }
            static bool const trusted = false;
            enum { id = 0xDul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectUpdateCompressedMessage>();
                }
            };


            ObjectUpdateCompressedMessage()
            : Message(HighHeader())
            , RegionData()
            , ObjectData()
            {}

            ObjectUpdateCompressedMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , RegionData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct RegionDataBlock
            {
                UInt64 RegionHandle;
                UInt16 TimeDilation;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionHandle,"RegionHandle");
                    p.process(TimeDilation,"TimeDilation");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 UpdateFlags;
                raw::LLVariable Data;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(UpdateFlags,"UpdateFlags");
                    p.process(Data,"Data");
                }

            };


            RegionDataBlock RegionData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(RegionData,"RegionData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ObjectUpdateCachedMessage
            : Message
        {
            static char const * name(){ return "ObjectUpdateCached"; }
            static bool const trusted = false;
            enum { id = 0xEul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ObjectUpdateCachedMessage>();
                }
            };


            ObjectUpdateCachedMessage()
            : Message(HighHeader())
            , RegionData()
            , ObjectData()
            {}

            ObjectUpdateCachedMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , RegionData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct RegionDataBlock
            {
                UInt64 RegionHandle;
                UInt16 TimeDilation;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionHandle,"RegionHandle");
                    p.process(TimeDilation,"TimeDilation");
                }

            };

            struct ObjectDataBlock
            {
                UInt32 ID;
                UInt32 CRC;
                UInt32 UpdateFlags;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(CRC,"CRC");
                    p.process(UpdateFlags,"UpdateFlags");
                }

            };


            RegionDataBlock RegionData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(RegionData,"RegionData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct ImprovedTerseObjectUpdateMessage
            : Message
        {
            static char const * name(){ return "ImprovedTerseObjectUpdate"; }
            static bool const trusted = false;
            enum { id = 0xFul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ImprovedTerseObjectUpdateMessage>();
                }
            };


            ImprovedTerseObjectUpdateMessage()
            : Message(HighHeader())
            , RegionData()
            , ObjectData()
            {}

            ImprovedTerseObjectUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , RegionData()
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct RegionDataBlock
            {
                UInt64 RegionHandle;
                UInt16 TimeDilation;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionHandle,"RegionHandle");
                    p.process(TimeDilation,"TimeDilation");
                }

            };

            struct ObjectDataBlock
            {
                raw::LLVariable Data;
                raw::LLVariable TextureEntry;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Data,"Data");
                    p.process(TextureEntry,"TextureEntry");
                }

            };


            RegionDataBlock RegionData;
            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(RegionData,"RegionData");
                p.process(ObjectData,"ObjectData");
            }

        };

        struct KillObjectMessage
            : Message
        {
            static char const * name(){ return "KillObject"; }
            static bool const trusted = false;
            enum { id = 0x10ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<KillObjectMessage>();
                }
            };


            KillObjectMessage()
            : Message(HighHeader())
            , ObjectData()
            {}

            KillObjectMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , ObjectData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ObjectDataBlock
            {
                UInt32 ID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                }

            };


            std::vector<ObjectDataBlock> ObjectData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ObjectData,"ObjectData");
            }

        };

        struct TransferPacketMessage
            : Message
        {
            static char const * name(){ return "TransferPacket"; }
            static bool const trusted = false;
            enum { id = 0x11ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<TransferPacketMessage>();
                }
            };


            TransferPacketMessage()
            : Message(HighHeader())
            , TransferData()
            {}

            TransferPacketMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , TransferData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct TransferDataBlock
            {
                LLUUID TransferID;
                Int32 ChannelType;
                Int32 Packet;
                Int32 Status;
                raw::LLVariable Data;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TransferID,"TransferID");
                    p.process(ChannelType,"ChannelType");
                    p.process(Packet,"Packet");
                    p.process(Status,"Status");
                    p.process(Data,"Data");
                }

            };


            TransferDataBlock TransferData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(TransferData,"TransferData");
            }

        };

        struct SendXferPacketMessage
            : Message
        {
            static char const * name(){ return "SendXferPacket"; }
            static bool const trusted = false;
            enum { id = 0x12ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SendXferPacketMessage>();
                }
            };


            SendXferPacketMessage()
            : Message(HighHeader())
            , XferID()
            , DataPacket()
            {}

            SendXferPacketMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , XferID()
            , DataPacket()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct XferIDBlock
            {
                UInt64 ID;
                UInt32 Packet;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(Packet,"Packet");
                }

            };

            struct DataPacketBlock
            {
                raw::LLVariable Data;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Data,"Data");
                }

            };


            XferIDBlock XferID;
            DataPacketBlock DataPacket;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(XferID,"XferID");
                p.process(DataPacket,"DataPacket");
            }

        };

        struct ConfirmXferPacketMessage
            : Message
        {
            static char const * name(){ return "ConfirmXferPacket"; }
            static bool const trusted = false;
            enum { id = 0x13ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ConfirmXferPacketMessage>();
                }
            };


            ConfirmXferPacketMessage()
            : Message(HighHeader())
            , XferID()
            {}

            ConfirmXferPacketMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , XferID()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct XferIDBlock
            {
                UInt64 ID;
                UInt32 Packet;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                    p.process(Packet,"Packet");
                }

            };


            XferIDBlock XferID;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(XferID,"XferID");
            }

        };

        struct AvatarAnimationMessage
            : Message
        {
            static char const * name(){ return "AvatarAnimation"; }
            static bool const trusted = false;
            enum { id = 0x14ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarAnimationMessage>();
                }
            };


            AvatarAnimationMessage()
            : Message(HighHeader())
            , Sender()
            , AnimationList()
            , AnimationSourceList()
            , PhysicalAvatarEventList()
            {}

            AvatarAnimationMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , Sender()
            , AnimationList()
            , AnimationSourceList()
            , PhysicalAvatarEventList()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct SenderBlock
            {
                LLUUID ID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                }

            };

            struct AnimationListBlock
            {
                LLUUID AnimID;
                Int32 AnimSequenceID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AnimID,"AnimID");
                    p.process(AnimSequenceID,"AnimSequenceID");
                }

            };

            struct AnimationSourceListBlock
            {
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ObjectID,"ObjectID");
                }

            };

            struct PhysicalAvatarEventListBlock
            {
                raw::LLVariable TypeData;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(TypeData,"TypeData");
                }

            };


            SenderBlock Sender;
            std::vector<AnimationListBlock> AnimationList;
            std::vector<AnimationSourceListBlock> AnimationSourceList;
            std::vector<PhysicalAvatarEventListBlock> PhysicalAvatarEventList;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(Sender,"Sender");
                p.process(AnimationList,"AnimationList");
                p.process(AnimationSourceList,"AnimationSourceList");
                p.process(PhysicalAvatarEventList,"PhysicalAvatarEventList");
            }

        };

        struct AvatarSitResponseMessage
            : Message
        {
            static char const * name(){ return "AvatarSitResponse"; }
            static bool const trusted = false;
            enum { id = 0x15ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<AvatarSitResponseMessage>();
                }
            };


            AvatarSitResponseMessage()
            : Message(HighHeader())
            , SitObject()
            , SitTransform()
            {}

            AvatarSitResponseMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , SitObject()
            , SitTransform()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct SitObjectBlock
            {
                LLUUID ID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ID,"ID");
                }

            };

            struct SitTransformBlock
            {
                bool AutoPilot;
                raw::LLVector3 SitPosition;
                raw::LLQuaternion SitRotation;
                raw::LLVector3 CameraEyeOffset;
                raw::LLVector3 CameraAtOffset;
                bool ForceMouselook;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(AutoPilot,"AutoPilot");
                    p.process(SitPosition,"SitPosition");
                    p.process(SitRotation,"SitRotation");
                    p.process(CameraEyeOffset,"CameraEyeOffset");
                    p.process(CameraAtOffset,"CameraAtOffset");
                    p.process(ForceMouselook,"ForceMouselook");
                }

            };


            SitObjectBlock SitObject;
            SitTransformBlock SitTransform;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(SitObject,"SitObject");
                p.process(SitTransform,"SitTransform");
            }

        };

        struct CameraConstraintMessage
            : Message
        {
            static char const * name(){ return "CameraConstraint"; }
            static bool const trusted = false;
            enum { id = 0x16ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<CameraConstraintMessage>();
                }
            };


            CameraConstraintMessage()
            : Message(HighHeader())
            , CameraCollidePlane()
            {}

            CameraConstraintMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , CameraCollidePlane()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct CameraCollidePlaneBlock
            {
                raw::LLVector4 Plane;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Plane,"Plane");
                }

            };


            CameraCollidePlaneBlock CameraCollidePlane;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(CameraCollidePlane,"CameraCollidePlane");
            }

        };

        struct ParcelPropertiesMessage
            : Message
        {
            static char const * name(){ return "ParcelProperties"; }
            static bool const trusted = false;
            enum { id = 0x17ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ParcelPropertiesMessage>();
                }
            };


            ParcelPropertiesMessage()
            : Message(HighHeader())
            , ParcelData()
            , AgeVerificationBlock()
            {}

            ParcelPropertiesMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , ParcelData()
            , AgeVerificationBlock()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct ParcelDataBlock
            {
                Int32 RequestResult;
                Int32 SequenceID;
                bool SnapSelection;
                Int32 SelfCount;
                Int32 OtherCount;
                Int32 PublicCount;
                Int32 LocalID;
                LLUUID OwnerID;
                bool IsGroupOwned;
                UInt32 AuctionID;
                Int32 ClaimDate;
                Int32 ClaimPrice;
                Int32 RentPrice;
                raw::LLVector3 AABBMin;
                raw::LLVector3 AABBMax;
                raw::LLVariable Bitmap;
                Int32 Area;
                UInt8 Status;
                Int32 SimWideMaxPrims;
                Int32 SimWideTotalPrims;
                Int32 MaxPrims;
                Int32 TotalPrims;
                Int32 OwnerPrims;
                Int32 GroupPrims;
                Int32 OtherPrims;
                Int32 SelectedPrims;
                Real32 ParcelPrimBonus;
                Int32 OtherCleanTime;
                UInt32 ParcelFlags;
                Int32 SalePrice;
                raw::LLVariable Name;
                raw::LLVariable Desc;
                raw::LLVariable MusicURL;
                raw::LLVariable MediaURL;
                LLUUID MediaID;
                UInt8 MediaAutoScale;
                LLUUID GroupID;
                Int32 PassPrice;
                Real32 PassHours;
                UInt8 Category;
                LLUUID AuthBuyerID;
                LLUUID SnapshotID;
                raw::LLVector3 UserLocation;
                raw::LLVector3 UserLookAt;
                UInt8 LandingType;
                bool RegionPushOverride;
                bool RegionDenyAnonymous;
                bool RegionDenyIdentified;
                bool RegionDenyTransacted;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RequestResult,"RequestResult");
                    p.process(SequenceID,"SequenceID");
                    p.process(SnapSelection,"SnapSelection");
                    p.process(SelfCount,"SelfCount");
                    p.process(OtherCount,"OtherCount");
                    p.process(PublicCount,"PublicCount");
                    p.process(LocalID,"LocalID");
                    p.process(OwnerID,"OwnerID");
                    p.process(IsGroupOwned,"IsGroupOwned");
                    p.process(AuctionID,"AuctionID");
                    p.process(ClaimDate,"ClaimDate");
                    p.process(ClaimPrice,"ClaimPrice");
                    p.process(RentPrice,"RentPrice");
                    p.process(AABBMin,"AABBMin");
                    p.process(AABBMax,"AABBMax");
                    p.process(Bitmap,"Bitmap");
                    p.process(Area,"Area");
                    p.process(Status,"Status");
                    p.process(SimWideMaxPrims,"SimWideMaxPrims");
                    p.process(SimWideTotalPrims,"SimWideTotalPrims");
                    p.process(MaxPrims,"MaxPrims");
                    p.process(TotalPrims,"TotalPrims");
                    p.process(OwnerPrims,"OwnerPrims");
                    p.process(GroupPrims,"GroupPrims");
                    p.process(OtherPrims,"OtherPrims");
                    p.process(SelectedPrims,"SelectedPrims");
                    p.process(ParcelPrimBonus,"ParcelPrimBonus");
                    p.process(OtherCleanTime,"OtherCleanTime");
                    p.process(ParcelFlags,"ParcelFlags");
                    p.process(SalePrice,"SalePrice");
                    p.process(Name,"Name");
                    p.process(Desc,"Desc");
                    p.process(MusicURL,"MusicURL");
                    p.process(MediaURL,"MediaURL");
                    p.process(MediaID,"MediaID");
                    p.process(MediaAutoScale,"MediaAutoScale");
                    p.process(GroupID,"GroupID");
                    p.process(PassPrice,"PassPrice");
                    p.process(PassHours,"PassHours");
                    p.process(Category,"Category");
                    p.process(AuthBuyerID,"AuthBuyerID");
                    p.process(SnapshotID,"SnapshotID");
                    p.process(UserLocation,"UserLocation");
                    p.process(UserLookAt,"UserLookAt");
                    p.process(LandingType,"LandingType");
                    p.process(RegionPushOverride,"RegionPushOverride");
                    p.process(RegionDenyAnonymous,"RegionDenyAnonymous");
                    p.process(RegionDenyIdentified,"RegionDenyIdentified");
                    p.process(RegionDenyTransacted,"RegionDenyTransacted");
                }

            };

            struct AgeVerificationBlockBlock
            {
                bool RegionDenyAgeUnverified;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionDenyAgeUnverified,"RegionDenyAgeUnverified");
                }

            };


            ParcelDataBlock ParcelData;
            AgeVerificationBlockBlock AgeVerificationBlock;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(ParcelData,"ParcelData");
                p.process(AgeVerificationBlock,"AgeVerificationBlock");
            }

        };

        struct ChildAgentUpdateMessage
            : Message
        {
            static char const * name(){ return "ChildAgentUpdate"; }
            static bool const trusted = false;
            enum { id = 0x19ul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ChildAgentUpdateMessage>();
                }
            };


            ChildAgentUpdateMessage()
            : Message(HighHeader())
            , AgentData()
            , GroupData()
            , AnimationData()
            , GranterBlock()
            , NVPairData()
            , VisualParam()
            {}

            ChildAgentUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , AgentData()
            , GroupData()
            , AnimationData()
            , GranterBlock()
            , NVPairData()
            , VisualParam()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                UInt64 RegionHandle;
                UInt32 ViewerCircuitCode;
                LLUUID AgentID;
                LLUUID SessionID;
                raw::LLVector3 AgentPos;
                raw::LLVector3 AgentVel;
                raw::LLVector3 Center;
                raw::LLVector3 Size;
                raw::LLVector3 AtAxis;
                raw::LLVector3 LeftAxis;
                raw::LLVector3 UpAxis;
                bool ChangedGrid;
                Real32 Far;
                Real32 Aspect;
                raw::LLVariable Throttles;
                UInt32 LocomotionState;
                raw::LLQuaternion HeadRotation;
                raw::LLQuaternion BodyRotation;
                UInt32 ControlFlags;
                Real32 EnergyLevel;
                UInt8 GodLevel;
                bool AlwaysRun;
                LLUUID PreyAgent;
                UInt8 AgentAccess;
                raw::LLVariable AgentTextures;
                LLUUID ActiveGroupID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionHandle,"RegionHandle");
                    p.process(ViewerCircuitCode,"ViewerCircuitCode");
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(AgentPos,"AgentPos");
                    p.process(AgentVel,"AgentVel");
                    p.process(Center,"Center");
                    p.process(Size,"Size");
                    p.process(AtAxis,"AtAxis");
                    p.process(LeftAxis,"LeftAxis");
                    p.process(UpAxis,"UpAxis");
                    p.process(ChangedGrid,"ChangedGrid");
                    p.process(Far,"Far");
                    p.process(Aspect,"Aspect");
                    p.process(Throttles,"Throttles");
                    p.process(LocomotionState,"LocomotionState");
                    p.process(HeadRotation,"HeadRotation");
                    p.process(BodyRotation,"BodyRotation");
                    p.process(ControlFlags,"ControlFlags");
                    p.process(EnergyLevel,"EnergyLevel");
                    p.process(GodLevel,"GodLevel");
                    p.process(AlwaysRun,"AlwaysRun");
                    p.process(PreyAgent,"PreyAgent");
                    p.process(AgentAccess,"AgentAccess");
                    p.process(AgentTextures,"AgentTextures");
                    p.process(ActiveGroupID,"ActiveGroupID");
                }

            };

            struct GroupDataBlock
            {
                LLUUID GroupID;
                UInt64 GroupPowers;
                bool AcceptNotices;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GroupID,"GroupID");
                    p.process(GroupPowers,"GroupPowers");
                    p.process(AcceptNotices,"AcceptNotices");
                }

            };

            struct AnimationDataBlock
            {
                LLUUID Animation;
                LLUUID ObjectID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(Animation,"Animation");
                    p.process(ObjectID,"ObjectID");
                }

            };

            struct GranterBlockBlock
            {
                LLUUID GranterID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(GranterID,"GranterID");
                }

            };

            struct NVPairDataBlock
            {
                raw::LLVariable NVPairs;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(NVPairs,"NVPairs");
                }

            };

            struct VisualParamBlock
            {
                UInt8 ParamValue;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(ParamValue,"ParamValue");
                }

            };


            AgentDataBlock AgentData;
            std::vector<GroupDataBlock> GroupData;
            std::vector<AnimationDataBlock> AnimationData;
            std::vector<GranterBlockBlock> GranterBlock;
            std::vector<NVPairDataBlock> NVPairData;
            std::vector<VisualParamBlock> VisualParam;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
                p.process(GroupData,"GroupData");
                p.process(AnimationData,"AnimationData");
                p.process(GranterBlock,"GranterBlock");
                p.process(NVPairData,"NVPairData");
                p.process(VisualParam,"VisualParam");
            }

        };

        struct ChildAgentAliveMessage
            : Message
        {
            static char const * name(){ return "ChildAgentAlive"; }
            static bool const trusted = false;
            enum { id = 0x1Aul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ChildAgentAliveMessage>();
                }
            };


            ChildAgentAliveMessage()
            : Message(HighHeader())
            , AgentData()
            {}

            ChildAgentAliveMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                UInt64 RegionHandle;
                UInt32 ViewerCircuitCode;
                LLUUID AgentID;
                LLUUID SessionID;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionHandle,"RegionHandle");
                    p.process(ViewerCircuitCode,"ViewerCircuitCode");
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct ChildAgentPositionUpdateMessage
            : Message
        {
            static char const * name(){ return "ChildAgentPositionUpdate"; }
            static bool const trusted = false;
            enum { id = 0x1Bul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<ChildAgentPositionUpdateMessage>();
                }
            };


            ChildAgentPositionUpdateMessage()
            : Message(HighHeader())
            , AgentData()
            {}

            ChildAgentPositionUpdateMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , AgentData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct AgentDataBlock
            {
                UInt64 RegionHandle;
                UInt32 ViewerCircuitCode;
                LLUUID AgentID;
                LLUUID SessionID;
                raw::LLVector3 AgentPos;
                raw::LLVector3 AgentVel;
                raw::LLVector3 Center;
                raw::LLVector3 Size;
                raw::LLVector3 AtAxis;
                raw::LLVector3 LeftAxis;
                raw::LLVector3 UpAxis;
                bool ChangedGrid;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(RegionHandle,"RegionHandle");
                    p.process(ViewerCircuitCode,"ViewerCircuitCode");
                    p.process(AgentID,"AgentID");
                    p.process(SessionID,"SessionID");
                    p.process(AgentPos,"AgentPos");
                    p.process(AgentVel,"AgentVel");
                    p.process(Center,"Center");
                    p.process(Size,"Size");
                    p.process(AtAxis,"AtAxis");
                    p.process(LeftAxis,"LeftAxis");
                    p.process(UpAxis,"UpAxis");
                    p.process(ChangedGrid,"ChangedGrid");
                }

            };


            AgentDataBlock AgentData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(AgentData,"AgentData");
            }

        };

        struct SoundTriggerMessage
            : Message
        {
            static char const * name(){ return "SoundTrigger"; }
            static bool const trusted = false;
            enum { id = 0x1Dul };
            static FrequencyType const frequency = FT_HIGH;
            static bool const encoded = false;


            struct apply {
                apply( PacketInitializer & initializer ) {
                    initializer.init<SoundTriggerMessage>();
                }
            };


            SoundTriggerMessage()
            : Message(HighHeader())
            , SoundData()
            {}

            SoundTriggerMessage(ByteBuffer & data, std::size_t & pos)
            : Message(HighHeader(data, pos))
            , SoundData()
            {
                Deserializer deserializer(data, pos);
                deserialize(deserializer, *this);
            }
            

            struct SoundDataBlock
            {
                LLUUID SoundID;
                LLUUID OwnerID;
                LLUUID ObjectID;
                LLUUID ParentID;
                UInt64 Handle;
                raw::LLVector3 Position;
                Real32 Gain;

                template<typename Processor>
                void process(Processor & p)
                {
                    p.process(SoundID,"SoundID");
                    p.process(OwnerID,"OwnerID");
                    p.process(ObjectID,"ObjectID");
                    p.process(ParentID,"ParentID");
                    p.process(Handle,"Handle");
                    p.process(Position,"Position");
                    p.process(Gain,"Gain");
                }

            };


            SoundDataBlock SoundData;

            template<typename Processor>
            void process(Processor & p)
            {
                p.process(SoundData,"SoundData");
            }

        };

        inline bool Lookup(UInt32 msg_id, PacketInitializer & initializer)
        {
            switch(msg_id)
            {
            case StartPingCheckMessage::id:
                { StartPingCheckMessage::apply a_(initializer); }
                return true;

            case CompletePingCheckMessage::id:
                { CompletePingCheckMessage::apply a_(initializer); }
                return true;

            case AgentUpdateMessage::id:
                { AgentUpdateMessage::apply a_(initializer); }
                return true;

            case AgentAnimationMessage::id:
                { AgentAnimationMessage::apply a_(initializer); }
                return true;

            case AgentRequestSitMessage::id:
                { AgentRequestSitMessage::apply a_(initializer); }
                return true;

            case AgentSitMessage::id:
                { AgentSitMessage::apply a_(initializer); }
                return true;

            case RequestImageMessage::id:
                { RequestImageMessage::apply a_(initializer); }
                return true;

            case ImageDataMessage::id:
                { ImageDataMessage::apply a_(initializer); }
                return true;

            case ImagePacketMessage::id:
                { ImagePacketMessage::apply a_(initializer); }
                return true;

            case LayerDataMessage::id:
                { LayerDataMessage::apply a_(initializer); }
                return true;

            case ObjectUpdateMessage::id:
                { ObjectUpdateMessage::apply a_(initializer); }
                return true;

            case ObjectUpdateCompressedMessage::id:
                { ObjectUpdateCompressedMessage::apply a_(initializer); }
                return true;

            case ObjectUpdateCachedMessage::id:
                { ObjectUpdateCachedMessage::apply a_(initializer); }
                return true;

            case ImprovedTerseObjectUpdateMessage::id:
                { ImprovedTerseObjectUpdateMessage::apply a_(initializer); }
                return true;

            case KillObjectMessage::id:
                { KillObjectMessage::apply a_(initializer); }
                return true;

            case TransferPacketMessage::id:
                { TransferPacketMessage::apply a_(initializer); }
                return true;

            case SendXferPacketMessage::id:
                { SendXferPacketMessage::apply a_(initializer); }
                return true;

            case ConfirmXferPacketMessage::id:
                { ConfirmXferPacketMessage::apply a_(initializer); }
                return true;

            case AvatarAnimationMessage::id:
                { AvatarAnimationMessage::apply a_(initializer); }
                return true;

            case AvatarSitResponseMessage::id:
                { AvatarSitResponseMessage::apply a_(initializer); }
                return true;

            case CameraConstraintMessage::id:
                { CameraConstraintMessage::apply a_(initializer); }
                return true;

            case ParcelPropertiesMessage::id:
                { ParcelPropertiesMessage::apply a_(initializer); }
                return true;

            case ChildAgentUpdateMessage::id:
                { ChildAgentUpdateMessage::apply a_(initializer); }
                return true;

            case ChildAgentAliveMessage::id:
                { ChildAgentAliveMessage::apply a_(initializer); }
                return true;

            case ChildAgentPositionUpdateMessage::id:
                { ChildAgentPositionUpdateMessage::apply a_(initializer); }
                return true;

            case SoundTriggerMessage::id:
                { SoundTriggerMessage::apply a_(initializer); }
                return true;

            case ObjectAddMessage::id:
                { ObjectAddMessage::apply a_(initializer); }
                return true;

            case MultipleObjectUpdateMessage::id:
                { MultipleObjectUpdateMessage::apply a_(initializer); }
                return true;

            case RequestMultipleObjectsMessage::id:
                { RequestMultipleObjectsMessage::apply a_(initializer); }
                return true;

            case ObjectPositionMessage::id:
                { ObjectPositionMessage::apply a_(initializer); }
                return true;

            case RequestObjectPropertiesFamilyMessage::id:
                { RequestObjectPropertiesFamilyMessage::apply a_(initializer); }
                return true;

            case CoarseLocationUpdateMessage::id:
                { CoarseLocationUpdateMessage::apply a_(initializer); }
                return true;

            case CrossedRegionMessage::id:
                { CrossedRegionMessage::apply a_(initializer); }
                return true;

            case ConfirmEnableSimulatorMessage::id:
                { ConfirmEnableSimulatorMessage::apply a_(initializer); }
                return true;

            case ObjectPropertiesMessage::id:
                { ObjectPropertiesMessage::apply a_(initializer); }
                return true;

            case ObjectPropertiesFamilyMessage::id:
                { ObjectPropertiesFamilyMessage::apply a_(initializer); }
                return true;

            case ParcelPropertiesRequestMessage::id:
                { ParcelPropertiesRequestMessage::apply a_(initializer); }
                return true;

            case AttachedSoundMessage::id:
                { AttachedSoundMessage::apply a_(initializer); }
                return true;

            case AttachedSoundGainChangeMessage::id:
                { AttachedSoundGainChangeMessage::apply a_(initializer); }
                return true;

            case PreloadSoundMessage::id:
                { PreloadSoundMessage::apply a_(initializer); }
                return true;

            case ViewerEffectMessage::id:
                { ViewerEffectMessage::apply a_(initializer); }
                return true;

            case TestMessageMessage::id:
                { TestMessageMessage::apply a_(initializer); }
                return true;

            case UseCircuitCodeMessage::id:
                { UseCircuitCodeMessage::apply a_(initializer); }
                return true;

            case TelehubInfoMessage::id:
                { TelehubInfoMessage::apply a_(initializer); }
                return true;

            case EconomyDataRequestMessage::id:
                { EconomyDataRequestMessage::apply a_(initializer); }
                return true;

            case EconomyDataMessage::id:
                { EconomyDataMessage::apply a_(initializer); }
                return true;

            case AvatarPickerRequestMessage::id:
                { AvatarPickerRequestMessage::apply a_(initializer); }
                return true;

            case AvatarPickerReplyMessage::id:
                { AvatarPickerReplyMessage::apply a_(initializer); }
                return true;

            case PlacesQueryMessage::id:
                { PlacesQueryMessage::apply a_(initializer); }
                return true;

            case PlacesReplyMessage::id:
                { PlacesReplyMessage::apply a_(initializer); }
                return true;

            case DirFindQueryMessage::id:
                { DirFindQueryMessage::apply a_(initializer); }
                return true;

            case DirPlacesQueryMessage::id:
                { DirPlacesQueryMessage::apply a_(initializer); }
                return true;

            case DirPlacesReplyMessage::id:
                { DirPlacesReplyMessage::apply a_(initializer); }
                return true;

            case DirPeopleReplyMessage::id:
                { DirPeopleReplyMessage::apply a_(initializer); }
                return true;

            case DirEventsReplyMessage::id:
                { DirEventsReplyMessage::apply a_(initializer); }
                return true;

            case DirGroupsReplyMessage::id:
                { DirGroupsReplyMessage::apply a_(initializer); }
                return true;

            case DirClassifiedQueryMessage::id:
                { DirClassifiedQueryMessage::apply a_(initializer); }
                return true;

            case DirClassifiedReplyMessage::id:
                { DirClassifiedReplyMessage::apply a_(initializer); }
                return true;

            case AvatarClassifiedReplyMessage::id:
                { AvatarClassifiedReplyMessage::apply a_(initializer); }
                return true;

            case ClassifiedInfoRequestMessage::id:
                { ClassifiedInfoRequestMessage::apply a_(initializer); }
                return true;

            case ClassifiedInfoReplyMessage::id:
                { ClassifiedInfoReplyMessage::apply a_(initializer); }
                return true;

            case ClassifiedInfoUpdateMessage::id:
                { ClassifiedInfoUpdateMessage::apply a_(initializer); }
                return true;

            case ClassifiedDeleteMessage::id:
                { ClassifiedDeleteMessage::apply a_(initializer); }
                return true;

            case ClassifiedGodDeleteMessage::id:
                { ClassifiedGodDeleteMessage::apply a_(initializer); }
                return true;

            case DirLandQueryMessage::id:
                { DirLandQueryMessage::apply a_(initializer); }
                return true;

            case DirLandReplyMessage::id:
                { DirLandReplyMessage::apply a_(initializer); }
                return true;

            case DirPopularQueryMessage::id:
                { DirPopularQueryMessage::apply a_(initializer); }
                return true;

            case DirPopularReplyMessage::id:
                { DirPopularReplyMessage::apply a_(initializer); }
                return true;

            case ParcelInfoRequestMessage::id:
                { ParcelInfoRequestMessage::apply a_(initializer); }
                return true;

            case ParcelInfoReplyMessage::id:
                { ParcelInfoReplyMessage::apply a_(initializer); }
                return true;

            case ParcelObjectOwnersRequestMessage::id:
                { ParcelObjectOwnersRequestMessage::apply a_(initializer); }
                return true;

            case ParcelObjectOwnersReplyMessage::id:
                { ParcelObjectOwnersReplyMessage::apply a_(initializer); }
                return true;

            case GroupNoticesListRequestMessage::id:
                { GroupNoticesListRequestMessage::apply a_(initializer); }
                return true;

            case GroupNoticesListReplyMessage::id:
                { GroupNoticesListReplyMessage::apply a_(initializer); }
                return true;

            case GroupNoticeRequestMessage::id:
                { GroupNoticeRequestMessage::apply a_(initializer); }
                return true;

            case TeleportRequestMessage::id:
                { TeleportRequestMessage::apply a_(initializer); }
                return true;

            case TeleportLocationRequestMessage::id:
                { TeleportLocationRequestMessage::apply a_(initializer); }
                return true;

            case TeleportLocalMessage::id:
                { TeleportLocalMessage::apply a_(initializer); }
                return true;

            case TeleportLandmarkRequestMessage::id:
                { TeleportLandmarkRequestMessage::apply a_(initializer); }
                return true;

            case TeleportProgressMessage::id:
                { TeleportProgressMessage::apply a_(initializer); }
                return true;

            case TeleportFinishMessage::id:
                { TeleportFinishMessage::apply a_(initializer); }
                return true;

            case StartLureMessage::id:
                { StartLureMessage::apply a_(initializer); }
                return true;

            case TeleportLureRequestMessage::id:
                { TeleportLureRequestMessage::apply a_(initializer); }
                return true;

            case TeleportCancelMessage::id:
                { TeleportCancelMessage::apply a_(initializer); }
                return true;

            case TeleportStartMessage::id:
                { TeleportStartMessage::apply a_(initializer); }
                return true;

            case TeleportFailedMessage::id:
                { TeleportFailedMessage::apply a_(initializer); }
                return true;

            case UndoMessage::id:
                { UndoMessage::apply a_(initializer); }
                return true;

            case RedoMessage::id:
                { RedoMessage::apply a_(initializer); }
                return true;

            case UndoLandMessage::id:
                { UndoLandMessage::apply a_(initializer); }
                return true;

            case AgentPauseMessage::id:
                { AgentPauseMessage::apply a_(initializer); }
                return true;

            case AgentResumeMessage::id:
                { AgentResumeMessage::apply a_(initializer); }
                return true;

            case ChatFromViewerMessage::id:
                { ChatFromViewerMessage::apply a_(initializer); }
                return true;

            case AgentThrottleMessage::id:
                { AgentThrottleMessage::apply a_(initializer); }
                return true;

            case AgentFOVMessage::id:
                { AgentFOVMessage::apply a_(initializer); }
                return true;

            case AgentHeightWidthMessage::id:
                { AgentHeightWidthMessage::apply a_(initializer); }
                return true;

            case AgentSetAppearanceMessage::id:
                { AgentSetAppearanceMessage::apply a_(initializer); }
                return true;

            case AgentQuitCopyMessage::id:
                { AgentQuitCopyMessage::apply a_(initializer); }
                return true;

            case ImageNotInDatabaseMessage::id:
                { ImageNotInDatabaseMessage::apply a_(initializer); }
                return true;

            case RebakeAvatarTexturesMessage::id:
                { RebakeAvatarTexturesMessage::apply a_(initializer); }
                return true;

            case SetAlwaysRunMessage::id:
                { SetAlwaysRunMessage::apply a_(initializer); }
                return true;

            case ObjectDeleteMessage::id:
                { ObjectDeleteMessage::apply a_(initializer); }
                return true;

            case ObjectDuplicateMessage::id:
                { ObjectDuplicateMessage::apply a_(initializer); }
                return true;

            case ObjectDuplicateOnRayMessage::id:
                { ObjectDuplicateOnRayMessage::apply a_(initializer); }
                return true;

            case ObjectScaleMessage::id:
                { ObjectScaleMessage::apply a_(initializer); }
                return true;

            case ObjectRotationMessage::id:
                { ObjectRotationMessage::apply a_(initializer); }
                return true;

            case ObjectFlagUpdateMessage::id:
                { ObjectFlagUpdateMessage::apply a_(initializer); }
                return true;

            case ObjectClickActionMessage::id:
                { ObjectClickActionMessage::apply a_(initializer); }
                return true;

            case ObjectImageMessage::id:
                { ObjectImageMessage::apply a_(initializer); }
                return true;

            case ObjectMaterialMessage::id:
                { ObjectMaterialMessage::apply a_(initializer); }
                return true;

            case ObjectShapeMessage::id:
                { ObjectShapeMessage::apply a_(initializer); }
                return true;

            case ObjectExtraParamsMessage::id:
                { ObjectExtraParamsMessage::apply a_(initializer); }
                return true;

            case ObjectOwnerMessage::id:
                { ObjectOwnerMessage::apply a_(initializer); }
                return true;

            case ObjectGroupMessage::id:
                { ObjectGroupMessage::apply a_(initializer); }
                return true;

            case ObjectBuyMessage::id:
                { ObjectBuyMessage::apply a_(initializer); }
                return true;

            case BuyObjectInventoryMessage::id:
                { BuyObjectInventoryMessage::apply a_(initializer); }
                return true;

            case DerezContainerMessage::id:
                { DerezContainerMessage::apply a_(initializer); }
                return true;

            case ObjectPermissionsMessage::id:
                { ObjectPermissionsMessage::apply a_(initializer); }
                return true;

            case ObjectSaleInfoMessage::id:
                { ObjectSaleInfoMessage::apply a_(initializer); }
                return true;

            case ObjectNameMessage::id:
                { ObjectNameMessage::apply a_(initializer); }
                return true;

            case ObjectDescriptionMessage::id:
                { ObjectDescriptionMessage::apply a_(initializer); }
                return true;

            case ObjectCategoryMessage::id:
                { ObjectCategoryMessage::apply a_(initializer); }
                return true;

            case ObjectSelectMessage::id:
                { ObjectSelectMessage::apply a_(initializer); }
                return true;

            case ObjectDeselectMessage::id:
                { ObjectDeselectMessage::apply a_(initializer); }
                return true;

            case ObjectAttachMessage::id:
                { ObjectAttachMessage::apply a_(initializer); }
                return true;

            case ObjectDetachMessage::id:
                { ObjectDetachMessage::apply a_(initializer); }
                return true;

            case ObjectDropMessage::id:
                { ObjectDropMessage::apply a_(initializer); }
                return true;

            case ObjectLinkMessage::id:
                { ObjectLinkMessage::apply a_(initializer); }
                return true;

            case ObjectDelinkMessage::id:
                { ObjectDelinkMessage::apply a_(initializer); }
                return true;

            case ObjectGrabMessage::id:
                { ObjectGrabMessage::apply a_(initializer); }
                return true;

            case ObjectGrabUpdateMessage::id:
                { ObjectGrabUpdateMessage::apply a_(initializer); }
                return true;

            case ObjectDeGrabMessage::id:
                { ObjectDeGrabMessage::apply a_(initializer); }
                return true;

            case ObjectSpinStartMessage::id:
                { ObjectSpinStartMessage::apply a_(initializer); }
                return true;

            case ObjectSpinUpdateMessage::id:
                { ObjectSpinUpdateMessage::apply a_(initializer); }
                return true;

            case ObjectSpinStopMessage::id:
                { ObjectSpinStopMessage::apply a_(initializer); }
                return true;

            case ObjectExportSelectedMessage::id:
                { ObjectExportSelectedMessage::apply a_(initializer); }
                return true;

            case ModifyLandMessage::id:
                { ModifyLandMessage::apply a_(initializer); }
                return true;

            case VelocityInterpolateOnMessage::id:
                { VelocityInterpolateOnMessage::apply a_(initializer); }
                return true;

            case VelocityInterpolateOffMessage::id:
                { VelocityInterpolateOffMessage::apply a_(initializer); }
                return true;

            case StateSaveMessage::id:
                { StateSaveMessage::apply a_(initializer); }
                return true;

            case ReportAutosaveCrashMessage::id:
                { ReportAutosaveCrashMessage::apply a_(initializer); }
                return true;

            case SimWideDeletesMessage::id:
                { SimWideDeletesMessage::apply a_(initializer); }
                return true;

            case TrackAgentMessage::id:
                { TrackAgentMessage::apply a_(initializer); }
                return true;

            case ViewerStatsMessage::id:
                { ViewerStatsMessage::apply a_(initializer); }
                return true;

            case ScriptAnswerYesMessage::id:
                { ScriptAnswerYesMessage::apply a_(initializer); }
                return true;

            case UserReportMessage::id:
                { UserReportMessage::apply a_(initializer); }
                return true;

            case AlertMessageMessage::id:
                { AlertMessageMessage::apply a_(initializer); }
                return true;

            case AgentAlertMessageMessage::id:
                { AgentAlertMessageMessage::apply a_(initializer); }
                return true;

            case MeanCollisionAlertMessage::id:
                { MeanCollisionAlertMessage::apply a_(initializer); }
                return true;

            case ViewerFrozenMessageMessage::id:
                { ViewerFrozenMessageMessage::apply a_(initializer); }
                return true;

            case HealthMessageMessage::id:
                { HealthMessageMessage::apply a_(initializer); }
                return true;

            case ChatFromSimulatorMessage::id:
                { ChatFromSimulatorMessage::apply a_(initializer); }
                return true;

            case SimStatsMessage::id:
                { SimStatsMessage::apply a_(initializer); }
                return true;

            case RequestRegionInfoMessage::id:
                { RequestRegionInfoMessage::apply a_(initializer); }
                return true;

            case RegionInfoMessage::id:
                { RegionInfoMessage::apply a_(initializer); }
                return true;

            case GodUpdateRegionInfoMessage::id:
                { GodUpdateRegionInfoMessage::apply a_(initializer); }
                return true;

            case NearestLandingRegionUpdatedMessage::id:
                { NearestLandingRegionUpdatedMessage::apply a_(initializer); }
                return true;

            case RegionHandshakeMessage::id:
                { RegionHandshakeMessage::apply a_(initializer); }
                return true;

            case RegionHandshakeReplyMessage::id:
                { RegionHandshakeReplyMessage::apply a_(initializer); }
                return true;

            case SimulatorViewerTimeMessageMessage::id:
                { SimulatorViewerTimeMessageMessage::apply a_(initializer); }
                return true;

            case EnableSimulatorMessage::id:
                { EnableSimulatorMessage::apply a_(initializer); }
                return true;

            case DisableSimulatorMessage::id:
                { DisableSimulatorMessage::apply a_(initializer); }
                return true;

            case TransferRequestMessage::id:
                { TransferRequestMessage::apply a_(initializer); }
                return true;

            case TransferInfoMessage::id:
                { TransferInfoMessage::apply a_(initializer); }
                return true;

            case TransferAbortMessage::id:
                { TransferAbortMessage::apply a_(initializer); }
                return true;

            case RequestXferMessage::id:
                { RequestXferMessage::apply a_(initializer); }
                return true;

            case AbortXferMessage::id:
                { AbortXferMessage::apply a_(initializer); }
                return true;

            case AvatarAppearanceMessage::id:
                { AvatarAppearanceMessage::apply a_(initializer); }
                return true;

            case SetFollowCamPropertiesMessage::id:
                { SetFollowCamPropertiesMessage::apply a_(initializer); }
                return true;

            case ClearFollowCamPropertiesMessage::id:
                { ClearFollowCamPropertiesMessage::apply a_(initializer); }
                return true;

            case RequestPayPriceMessage::id:
                { RequestPayPriceMessage::apply a_(initializer); }
                return true;

            case PayPriceReplyMessage::id:
                { PayPriceReplyMessage::apply a_(initializer); }
                return true;

            case KickUserMessage::id:
                { KickUserMessage::apply a_(initializer); }
                return true;

            case KickUserAckMessage::id:
                { KickUserAckMessage::apply a_(initializer); }
                return true;

            case GodKickUserMessage::id:
                { GodKickUserMessage::apply a_(initializer); }
                return true;

            case EjectUserMessage::id:
                { EjectUserMessage::apply a_(initializer); }
                return true;

            case FreezeUserMessage::id:
                { FreezeUserMessage::apply a_(initializer); }
                return true;

            case AvatarPropertiesRequestMessage::id:
                { AvatarPropertiesRequestMessage::apply a_(initializer); }
                return true;

            case AvatarPropertiesReplyMessage::id:
                { AvatarPropertiesReplyMessage::apply a_(initializer); }
                return true;

            case AvatarInterestsReplyMessage::id:
                { AvatarInterestsReplyMessage::apply a_(initializer); }
                return true;

            case AvatarGroupsReplyMessage::id:
                { AvatarGroupsReplyMessage::apply a_(initializer); }
                return true;

            case AvatarPropertiesUpdateMessage::id:
                { AvatarPropertiesUpdateMessage::apply a_(initializer); }
                return true;

            case AvatarInterestsUpdateMessage::id:
                { AvatarInterestsUpdateMessage::apply a_(initializer); }
                return true;

            case AvatarNotesReplyMessage::id:
                { AvatarNotesReplyMessage::apply a_(initializer); }
                return true;

            case AvatarNotesUpdateMessage::id:
                { AvatarNotesUpdateMessage::apply a_(initializer); }
                return true;

            case AvatarPicksReplyMessage::id:
                { AvatarPicksReplyMessage::apply a_(initializer); }
                return true;

            case EventInfoRequestMessage::id:
                { EventInfoRequestMessage::apply a_(initializer); }
                return true;

            case EventInfoReplyMessage::id:
                { EventInfoReplyMessage::apply a_(initializer); }
                return true;

            case EventNotificationAddRequestMessage::id:
                { EventNotificationAddRequestMessage::apply a_(initializer); }
                return true;

            case EventNotificationRemoveRequestMessage::id:
                { EventNotificationRemoveRequestMessage::apply a_(initializer); }
                return true;

            case EventGodDeleteMessage::id:
                { EventGodDeleteMessage::apply a_(initializer); }
                return true;

            case PickInfoReplyMessage::id:
                { PickInfoReplyMessage::apply a_(initializer); }
                return true;

            case PickInfoUpdateMessage::id:
                { PickInfoUpdateMessage::apply a_(initializer); }
                return true;

            case PickDeleteMessage::id:
                { PickDeleteMessage::apply a_(initializer); }
                return true;

            case PickGodDeleteMessage::id:
                { PickGodDeleteMessage::apply a_(initializer); }
                return true;

            case ScriptQuestionMessage::id:
                { ScriptQuestionMessage::apply a_(initializer); }
                return true;

            case ScriptControlChangeMessage::id:
                { ScriptControlChangeMessage::apply a_(initializer); }
                return true;

            case ScriptDialogMessage::id:
                { ScriptDialogMessage::apply a_(initializer); }
                return true;

            case ScriptDialogReplyMessage::id:
                { ScriptDialogReplyMessage::apply a_(initializer); }
                return true;

            case ForceScriptControlReleaseMessage::id:
                { ForceScriptControlReleaseMessage::apply a_(initializer); }
                return true;

            case RevokePermissionsMessage::id:
                { RevokePermissionsMessage::apply a_(initializer); }
                return true;

            case LoadURLMessage::id:
                { LoadURLMessage::apply a_(initializer); }
                return true;

            case ScriptTeleportRequestMessage::id:
                { ScriptTeleportRequestMessage::apply a_(initializer); }
                return true;

            case ParcelOverlayMessage::id:
                { ParcelOverlayMessage::apply a_(initializer); }
                return true;

            case ParcelPropertiesRequestByIDMessage::id:
                { ParcelPropertiesRequestByIDMessage::apply a_(initializer); }
                return true;

            case ParcelPropertiesUpdateMessage::id:
                { ParcelPropertiesUpdateMessage::apply a_(initializer); }
                return true;

            case ParcelReturnObjectsMessage::id:
                { ParcelReturnObjectsMessage::apply a_(initializer); }
                return true;

            case ParcelSetOtherCleanTimeMessage::id:
                { ParcelSetOtherCleanTimeMessage::apply a_(initializer); }
                return true;

            case ParcelDisableObjectsMessage::id:
                { ParcelDisableObjectsMessage::apply a_(initializer); }
                return true;

            case ParcelSelectObjectsMessage::id:
                { ParcelSelectObjectsMessage::apply a_(initializer); }
                return true;

            case EstateCovenantRequestMessage::id:
                { EstateCovenantRequestMessage::apply a_(initializer); }
                return true;

            case EstateCovenantReplyMessage::id:
                { EstateCovenantReplyMessage::apply a_(initializer); }
                return true;

            case ForceObjectSelectMessage::id:
                { ForceObjectSelectMessage::apply a_(initializer); }
                return true;

            case ParcelBuyPassMessage::id:
                { ParcelBuyPassMessage::apply a_(initializer); }
                return true;

            case ParcelDeedToGroupMessage::id:
                { ParcelDeedToGroupMessage::apply a_(initializer); }
                return true;

            case ParcelReclaimMessage::id:
                { ParcelReclaimMessage::apply a_(initializer); }
                return true;

            case ParcelClaimMessage::id:
                { ParcelClaimMessage::apply a_(initializer); }
                return true;

            case ParcelJoinMessage::id:
                { ParcelJoinMessage::apply a_(initializer); }
                return true;

            case ParcelDivideMessage::id:
                { ParcelDivideMessage::apply a_(initializer); }
                return true;

            case ParcelReleaseMessage::id:
                { ParcelReleaseMessage::apply a_(initializer); }
                return true;

            case ParcelBuyMessage::id:
                { ParcelBuyMessage::apply a_(initializer); }
                return true;

            case ParcelGodForceOwnerMessage::id:
                { ParcelGodForceOwnerMessage::apply a_(initializer); }
                return true;

            case ParcelAccessListRequestMessage::id:
                { ParcelAccessListRequestMessage::apply a_(initializer); }
                return true;

            case ParcelAccessListReplyMessage::id:
                { ParcelAccessListReplyMessage::apply a_(initializer); }
                return true;

            case ParcelAccessListUpdateMessage::id:
                { ParcelAccessListUpdateMessage::apply a_(initializer); }
                return true;

            case ParcelDwellRequestMessage::id:
                { ParcelDwellRequestMessage::apply a_(initializer); }
                return true;

            case ParcelDwellReplyMessage::id:
                { ParcelDwellReplyMessage::apply a_(initializer); }
                return true;

            case ParcelGodMarkAsContentMessage::id:
                { ParcelGodMarkAsContentMessage::apply a_(initializer); }
                return true;

            case ViewerStartAuctionMessage::id:
                { ViewerStartAuctionMessage::apply a_(initializer); }
                return true;

            case UUIDNameRequestMessage::id:
                { UUIDNameRequestMessage::apply a_(initializer); }
                return true;

            case UUIDNameReplyMessage::id:
                { UUIDNameReplyMessage::apply a_(initializer); }
                return true;

            case UUIDGroupNameRequestMessage::id:
                { UUIDGroupNameRequestMessage::apply a_(initializer); }
                return true;

            case UUIDGroupNameReplyMessage::id:
                { UUIDGroupNameReplyMessage::apply a_(initializer); }
                return true;

            case ChildAgentDyingMessage::id:
                { ChildAgentDyingMessage::apply a_(initializer); }
                return true;

            case ChildAgentUnknownMessage::id:
                { ChildAgentUnknownMessage::apply a_(initializer); }
                return true;

            case GetScriptRunningMessage::id:
                { GetScriptRunningMessage::apply a_(initializer); }
                return true;

            case ScriptRunningReplyMessage::id:
                { ScriptRunningReplyMessage::apply a_(initializer); }
                return true;

            case SetScriptRunningMessage::id:
                { SetScriptRunningMessage::apply a_(initializer); }
                return true;

            case ScriptResetMessage::id:
                { ScriptResetMessage::apply a_(initializer); }
                return true;

            case ScriptSensorRequestMessage::id:
                { ScriptSensorRequestMessage::apply a_(initializer); }
                return true;

            case ScriptSensorReplyMessage::id:
                { ScriptSensorReplyMessage::apply a_(initializer); }
                return true;

            case CompleteAgentMovementMessage::id:
                { CompleteAgentMovementMessage::apply a_(initializer); }
                return true;

            case AgentMovementCompleteMessage::id:
                { AgentMovementCompleteMessage::apply a_(initializer); }
                return true;

            case LogoutRequestMessage::id:
                { LogoutRequestMessage::apply a_(initializer); }
                return true;

            case LogoutReplyMessage::id:
                { LogoutReplyMessage::apply a_(initializer); }
                return true;

            case ImprovedInstantMessageMessage::id:
                { ImprovedInstantMessageMessage::apply a_(initializer); }
                return true;

            case RetrieveInstantMessagesMessage::id:
                { RetrieveInstantMessagesMessage::apply a_(initializer); }
                return true;

            case FindAgentMessage::id:
                { FindAgentMessage::apply a_(initializer); }
                return true;

            case RequestGodlikePowersMessage::id:
                { RequestGodlikePowersMessage::apply a_(initializer); }
                return true;

            case GrantGodlikePowersMessage::id:
                { GrantGodlikePowersMessage::apply a_(initializer); }
                return true;

            case GodlikeMessageMessage::id:
                { GodlikeMessageMessage::apply a_(initializer); }
                return true;

            case EstateOwnerMessageMessage::id:
                { EstateOwnerMessageMessage::apply a_(initializer); }
                return true;

            case GenericMessageMessage::id:
                { GenericMessageMessage::apply a_(initializer); }
                return true;

            case MuteListRequestMessage::id:
                { MuteListRequestMessage::apply a_(initializer); }
                return true;

            case UpdateMuteListEntryMessage::id:
                { UpdateMuteListEntryMessage::apply a_(initializer); }
                return true;

            case RemoveMuteListEntryMessage::id:
                { RemoveMuteListEntryMessage::apply a_(initializer); }
                return true;

            case CopyInventoryFromNotecardMessage::id:
                { CopyInventoryFromNotecardMessage::apply a_(initializer); }
                return true;

            case UpdateInventoryItemMessage::id:
                { UpdateInventoryItemMessage::apply a_(initializer); }
                return true;

            case UpdateCreateInventoryItemMessage::id:
                { UpdateCreateInventoryItemMessage::apply a_(initializer); }
                return true;

            case MoveInventoryItemMessage::id:
                { MoveInventoryItemMessage::apply a_(initializer); }
                return true;

            case CopyInventoryItemMessage::id:
                { CopyInventoryItemMessage::apply a_(initializer); }
                return true;

            case RemoveInventoryItemMessage::id:
                { RemoveInventoryItemMessage::apply a_(initializer); }
                return true;

            case ChangeInventoryItemFlagsMessage::id:
                { ChangeInventoryItemFlagsMessage::apply a_(initializer); }
                return true;

            case SaveAssetIntoInventoryMessage::id:
                { SaveAssetIntoInventoryMessage::apply a_(initializer); }
                return true;

            case CreateInventoryFolderMessage::id:
                { CreateInventoryFolderMessage::apply a_(initializer); }
                return true;

            case UpdateInventoryFolderMessage::id:
                { UpdateInventoryFolderMessage::apply a_(initializer); }
                return true;

            case MoveInventoryFolderMessage::id:
                { MoveInventoryFolderMessage::apply a_(initializer); }
                return true;

            case RemoveInventoryFolderMessage::id:
                { RemoveInventoryFolderMessage::apply a_(initializer); }
                return true;

            case FetchInventoryDescendentsMessage::id:
                { FetchInventoryDescendentsMessage::apply a_(initializer); }
                return true;

            case InventoryDescendentsMessage::id:
                { InventoryDescendentsMessage::apply a_(initializer); }
                return true;

            case FetchInventoryMessage::id:
                { FetchInventoryMessage::apply a_(initializer); }
                return true;

            case FetchInventoryReplyMessage::id:
                { FetchInventoryReplyMessage::apply a_(initializer); }
                return true;

            case BulkUpdateInventoryMessage::id:
                { BulkUpdateInventoryMessage::apply a_(initializer); }
                return true;

            case RequestInventoryAssetMessage::id:
                { RequestInventoryAssetMessage::apply a_(initializer); }
                return true;

            case InventoryAssetResponseMessage::id:
                { InventoryAssetResponseMessage::apply a_(initializer); }
                return true;

            case RemoveInventoryObjectsMessage::id:
                { RemoveInventoryObjectsMessage::apply a_(initializer); }
                return true;

            case PurgeInventoryDescendentsMessage::id:
                { PurgeInventoryDescendentsMessage::apply a_(initializer); }
                return true;

            case UpdateTaskInventoryMessage::id:
                { UpdateTaskInventoryMessage::apply a_(initializer); }
                return true;

            case RemoveTaskInventoryMessage::id:
                { RemoveTaskInventoryMessage::apply a_(initializer); }
                return true;

            case MoveTaskInventoryMessage::id:
                { MoveTaskInventoryMessage::apply a_(initializer); }
                return true;

            case RequestTaskInventoryMessage::id:
                { RequestTaskInventoryMessage::apply a_(initializer); }
                return true;

            case ReplyTaskInventoryMessage::id:
                { ReplyTaskInventoryMessage::apply a_(initializer); }
                return true;

            case DeRezObjectMessage::id:
                { DeRezObjectMessage::apply a_(initializer); }
                return true;

            case DeRezAckMessage::id:
                { DeRezAckMessage::apply a_(initializer); }
                return true;

            case RezObjectMessage::id:
                { RezObjectMessage::apply a_(initializer); }
                return true;

            case RezObjectFromNotecardMessage::id:
                { RezObjectFromNotecardMessage::apply a_(initializer); }
                return true;

            case AcceptFriendshipMessage::id:
                { AcceptFriendshipMessage::apply a_(initializer); }
                return true;

            case DeclineFriendshipMessage::id:
                { DeclineFriendshipMessage::apply a_(initializer); }
                return true;

            case FormFriendshipMessage::id:
                { FormFriendshipMessage::apply a_(initializer); }
                return true;

            case TerminateFriendshipMessage::id:
                { TerminateFriendshipMessage::apply a_(initializer); }
                return true;

            case OfferCallingCardMessage::id:
                { OfferCallingCardMessage::apply a_(initializer); }
                return true;

            case AcceptCallingCardMessage::id:
                { AcceptCallingCardMessage::apply a_(initializer); }
                return true;

            case DeclineCallingCardMessage::id:
                { DeclineCallingCardMessage::apply a_(initializer); }
                return true;

            case RezScriptMessage::id:
                { RezScriptMessage::apply a_(initializer); }
                return true;

            case CreateInventoryItemMessage::id:
                { CreateInventoryItemMessage::apply a_(initializer); }
                return true;

            case CreateLandmarkForEventMessage::id:
                { CreateLandmarkForEventMessage::apply a_(initializer); }
                return true;

            case RegionHandleRequestMessage::id:
                { RegionHandleRequestMessage::apply a_(initializer); }
                return true;

            case RegionIDAndHandleReplyMessage::id:
                { RegionIDAndHandleReplyMessage::apply a_(initializer); }
                return true;

            case MoneyTransferRequestMessage::id:
                { MoneyTransferRequestMessage::apply a_(initializer); }
                return true;

            case MoneyBalanceRequestMessage::id:
                { MoneyBalanceRequestMessage::apply a_(initializer); }
                return true;

            case MoneyBalanceReplyMessage::id:
                { MoneyBalanceReplyMessage::apply a_(initializer); }
                return true;

            case RoutedMoneyBalanceReplyMessage::id:
                { RoutedMoneyBalanceReplyMessage::apply a_(initializer); }
                return true;

            case ActivateGesturesMessage::id:
                { ActivateGesturesMessage::apply a_(initializer); }
                return true;

            case DeactivateGesturesMessage::id:
                { DeactivateGesturesMessage::apply a_(initializer); }
                return true;

            case MuteListUpdateMessage::id:
                { MuteListUpdateMessage::apply a_(initializer); }
                return true;

            case UseCachedMuteListMessage::id:
                { UseCachedMuteListMessage::apply a_(initializer); }
                return true;

            case GrantUserRightsMessage::id:
                { GrantUserRightsMessage::apply a_(initializer); }
                return true;

            case ChangeUserRightsMessage::id:
                { ChangeUserRightsMessage::apply a_(initializer); }
                return true;

            case OnlineNotificationMessage::id:
                { OnlineNotificationMessage::apply a_(initializer); }
                return true;

            case OfflineNotificationMessage::id:
                { OfflineNotificationMessage::apply a_(initializer); }
                return true;

            case SetStartLocationRequestMessage::id:
                { SetStartLocationRequestMessage::apply a_(initializer); }
                return true;

            case AssetUploadRequestMessage::id:
                { AssetUploadRequestMessage::apply a_(initializer); }
                return true;

            case AssetUploadCompleteMessage::id:
                { AssetUploadCompleteMessage::apply a_(initializer); }
                return true;

            case CreateGroupRequestMessage::id:
                { CreateGroupRequestMessage::apply a_(initializer); }
                return true;

            case CreateGroupReplyMessage::id:
                { CreateGroupReplyMessage::apply a_(initializer); }
                return true;

            case UpdateGroupInfoMessage::id:
                { UpdateGroupInfoMessage::apply a_(initializer); }
                return true;

            case GroupRoleChangesMessage::id:
                { GroupRoleChangesMessage::apply a_(initializer); }
                return true;

            case JoinGroupRequestMessage::id:
                { JoinGroupRequestMessage::apply a_(initializer); }
                return true;

            case JoinGroupReplyMessage::id:
                { JoinGroupReplyMessage::apply a_(initializer); }
                return true;

            case EjectGroupMemberRequestMessage::id:
                { EjectGroupMemberRequestMessage::apply a_(initializer); }
                return true;

            case EjectGroupMemberReplyMessage::id:
                { EjectGroupMemberReplyMessage::apply a_(initializer); }
                return true;

            case LeaveGroupRequestMessage::id:
                { LeaveGroupRequestMessage::apply a_(initializer); }
                return true;

            case LeaveGroupReplyMessage::id:
                { LeaveGroupReplyMessage::apply a_(initializer); }
                return true;

            case InviteGroupRequestMessage::id:
                { InviteGroupRequestMessage::apply a_(initializer); }
                return true;

            case GroupProfileRequestMessage::id:
                { GroupProfileRequestMessage::apply a_(initializer); }
                return true;

            case GroupProfileReplyMessage::id:
                { GroupProfileReplyMessage::apply a_(initializer); }
                return true;

            case GroupAccountSummaryRequestMessage::id:
                { GroupAccountSummaryRequestMessage::apply a_(initializer); }
                return true;

            case GroupAccountSummaryReplyMessage::id:
                { GroupAccountSummaryReplyMessage::apply a_(initializer); }
                return true;

            case GroupAccountDetailsRequestMessage::id:
                { GroupAccountDetailsRequestMessage::apply a_(initializer); }
                return true;

            case GroupAccountDetailsReplyMessage::id:
                { GroupAccountDetailsReplyMessage::apply a_(initializer); }
                return true;

            case GroupAccountTransactionsRequestMessage::id:
                { GroupAccountTransactionsRequestMessage::apply a_(initializer); }
                return true;

            case GroupAccountTransactionsReplyMessage::id:
                { GroupAccountTransactionsReplyMessage::apply a_(initializer); }
                return true;

            case GroupActiveProposalsRequestMessage::id:
                { GroupActiveProposalsRequestMessage::apply a_(initializer); }
                return true;

            case GroupActiveProposalItemReplyMessage::id:
                { GroupActiveProposalItemReplyMessage::apply a_(initializer); }
                return true;

            case GroupVoteHistoryRequestMessage::id:
                { GroupVoteHistoryRequestMessage::apply a_(initializer); }
                return true;

            case GroupVoteHistoryItemReplyMessage::id:
                { GroupVoteHistoryItemReplyMessage::apply a_(initializer); }
                return true;

            case StartGroupProposalMessage::id:
                { StartGroupProposalMessage::apply a_(initializer); }
                return true;

            case GroupProposalBallotMessage::id:
                { GroupProposalBallotMessage::apply a_(initializer); }
                return true;

            case GroupMembersRequestMessage::id:
                { GroupMembersRequestMessage::apply a_(initializer); }
                return true;

            case GroupMembersReplyMessage::id:
                { GroupMembersReplyMessage::apply a_(initializer); }
                return true;

            case ActivateGroupMessage::id:
                { ActivateGroupMessage::apply a_(initializer); }
                return true;

            case SetGroupContributionMessage::id:
                { SetGroupContributionMessage::apply a_(initializer); }
                return true;

            case SetGroupAcceptNoticesMessage::id:
                { SetGroupAcceptNoticesMessage::apply a_(initializer); }
                return true;

            case GroupRoleDataRequestMessage::id:
                { GroupRoleDataRequestMessage::apply a_(initializer); }
                return true;

            case GroupRoleDataReplyMessage::id:
                { GroupRoleDataReplyMessage::apply a_(initializer); }
                return true;

            case GroupRoleMembersRequestMessage::id:
                { GroupRoleMembersRequestMessage::apply a_(initializer); }
                return true;

            case GroupRoleMembersReplyMessage::id:
                { GroupRoleMembersReplyMessage::apply a_(initializer); }
                return true;

            case GroupTitlesRequestMessage::id:
                { GroupTitlesRequestMessage::apply a_(initializer); }
                return true;

            case GroupTitlesReplyMessage::id:
                { GroupTitlesReplyMessage::apply a_(initializer); }
                return true;

            case GroupTitleUpdateMessage::id:
                { GroupTitleUpdateMessage::apply a_(initializer); }
                return true;

            case GroupRoleUpdateMessage::id:
                { GroupRoleUpdateMessage::apply a_(initializer); }
                return true;

            case LiveHelpGroupRequestMessage::id:
                { LiveHelpGroupRequestMessage::apply a_(initializer); }
                return true;

            case LiveHelpGroupReplyMessage::id:
                { LiveHelpGroupReplyMessage::apply a_(initializer); }
                return true;

            case AgentWearablesRequestMessage::id:
                { AgentWearablesRequestMessage::apply a_(initializer); }
                return true;

            case AgentWearablesUpdateMessage::id:
                { AgentWearablesUpdateMessage::apply a_(initializer); }
                return true;

            case AgentIsNowWearingMessage::id:
                { AgentIsNowWearingMessage::apply a_(initializer); }
                return true;

            case AgentCachedTextureMessage::id:
                { AgentCachedTextureMessage::apply a_(initializer); }
                return true;

            case AgentCachedTextureResponseMessage::id:
                { AgentCachedTextureResponseMessage::apply a_(initializer); }
                return true;

            case AgentDataUpdateRequestMessage::id:
                { AgentDataUpdateRequestMessage::apply a_(initializer); }
                return true;

            case AgentDataUpdateMessage::id:
                { AgentDataUpdateMessage::apply a_(initializer); }
                return true;

            case GroupDataUpdateMessage::id:
                { GroupDataUpdateMessage::apply a_(initializer); }
                return true;

            case AgentGroupDataUpdateMessage::id:
                { AgentGroupDataUpdateMessage::apply a_(initializer); }
                return true;

            case AgentDropGroupMessage::id:
                { AgentDropGroupMessage::apply a_(initializer); }
                return true;

            case CreateTrustedCircuitMessage::id:
                { CreateTrustedCircuitMessage::apply a_(initializer); }
                return true;

            case DenyTrustedCircuitMessage::id:
                { DenyTrustedCircuitMessage::apply a_(initializer); }
                return true;

            case RequestTrustedCircuitMessage::id:
                { RequestTrustedCircuitMessage::apply a_(initializer); }
                return true;

            case RezSingleAttachmentFromInvMessage::id:
                { RezSingleAttachmentFromInvMessage::apply a_(initializer); }
                return true;

            case RezMultipleAttachmentsFromInvMessage::id:
                { RezMultipleAttachmentsFromInvMessage::apply a_(initializer); }
                return true;

            case DetachAttachmentIntoInvMessage::id:
                { DetachAttachmentIntoInvMessage::apply a_(initializer); }
                return true;

            case CreateNewOutfitAttachmentsMessage::id:
                { CreateNewOutfitAttachmentsMessage::apply a_(initializer); }
                return true;

            case UserInfoRequestMessage::id:
                { UserInfoRequestMessage::apply a_(initializer); }
                return true;

            case UserInfoReplyMessage::id:
                { UserInfoReplyMessage::apply a_(initializer); }
                return true;

            case UpdateUserInfoMessage::id:
                { UpdateUserInfoMessage::apply a_(initializer); }
                return true;

            case InitiateDownloadMessage::id:
                { InitiateDownloadMessage::apply a_(initializer); }
                return true;

            case SystemMessageMessage::id:
                { SystemMessageMessage::apply a_(initializer); }
                return true;

            case MapLayerRequestMessage::id:
                { MapLayerRequestMessage::apply a_(initializer); }
                return true;

            case MapLayerReplyMessage::id:
                { MapLayerReplyMessage::apply a_(initializer); }
                return true;

            case MapBlockRequestMessage::id:
                { MapBlockRequestMessage::apply a_(initializer); }
                return true;

            case MapNameRequestMessage::id:
                { MapNameRequestMessage::apply a_(initializer); }
                return true;

            case MapBlockReplyMessage::id:
                { MapBlockReplyMessage::apply a_(initializer); }
                return true;

            case MapItemRequestMessage::id:
                { MapItemRequestMessage::apply a_(initializer); }
                return true;

            case MapItemReplyMessage::id:
                { MapItemReplyMessage::apply a_(initializer); }
                return true;

            case SendPostcardMessage::id:
                { SendPostcardMessage::apply a_(initializer); }
                return true;

            case ParcelMediaCommandMessageMessage::id:
                { ParcelMediaCommandMessageMessage::apply a_(initializer); }
                return true;

            case ParcelMediaUpdateMessage::id:
                { ParcelMediaUpdateMessage::apply a_(initializer); }
                return true;

            case LandStatRequestMessage::id:
                { LandStatRequestMessage::apply a_(initializer); }
                return true;

            case LandStatReplyMessage::id:
                { LandStatReplyMessage::apply a_(initializer); }
                return true;

            case ErrorMessage::id:
                { ErrorMessage::apply a_(initializer); }
                return true;

            case ObjectIncludeInSearchMessage::id:
                { ObjectIncludeInSearchMessage::apply a_(initializer); }
                return true;

            case PacketAckMessage::id:
                { PacketAckMessage::apply a_(initializer); }
                return true;

            case OpenCircuitMessage::id:
                { OpenCircuitMessage::apply a_(initializer); }
                return true;

            case CloseCircuitMessage::id:
                { CloseCircuitMessage::apply a_(initializer); }
                return true;

            default: break;
            }
            return false;
        }
    }//namespace packets
}//namespace omvtk
#endif //GUARD_LIBOMVTK_PACKETS_PACKETS_H_INCLUDED
