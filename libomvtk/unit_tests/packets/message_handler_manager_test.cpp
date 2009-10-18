#include "../test_suite.h"
#include "../../libomvtk/packets/message_handler_manager.h"
#include "../../libomvtk/packets/packets.h"
#define UNIT_TEST
#include "../../libomvtk/network/simulator.h"
#include <boost/bind.hpp>

namespace tut
{    
    using namespace omvtk;
    using omvtk::packets::ParcelAccessListReplyMessage;


    struct message_handler_manager_data
    {
        MessageHandlerManager manager;
        Simulator sim;
    };

    DEFINE_TEST_GROUP(message_handler_manager_data, "MessageHandlerManager test");

    void AccessListHandler(ParcelAccessListReplyMessage const &, Simulator &, bool * called = 0)
    {        
        if(called)
        {
            *called = true;
        }
    }

    DEF_TEST(1)
    {
        ensure(manager.empty());
    }

    DEF_TEST(2)
    {
        ensure(manager.empty());
        ensure_equals(manager.count<ParcelAccessListReplyMessage>(),0u);
        manager(ParcelAccessListReplyMessage(), sim);
    }

    DEF_TEST(3)
    {
        MessageHandler<ParcelAccessListReplyMessage> access_list_handler;
        bool called = false;
        access_list_handler.set(boost::bind(AccessListHandler, _1, _2, &called));

        manager.connect(access_list_handler);
        ensure_not(manager.empty());
        ensure_equals(manager.count<ParcelAccessListReplyMessage>(),1u);
        ensure_not(called);
        manager(ParcelAccessListReplyMessage(), sim);
        ensure(called);
    }

    DEF_TEST(4)
    {
        MessageHandler<ParcelAccessListReplyMessage> access_list_handler;
        bool called = false;
        access_list_handler.set(boost::bind(AccessListHandler, _1, _2, &called));

        manager.connect(access_list_handler);
        ensure_not(manager.empty());
        ensure_equals(manager.count<ParcelAccessListReplyMessage>(),1u);
        ensure_not(called);
        manager.disconnect(access_list_handler);
        ensure(manager.empty());
        ensure_equals(manager.count<ParcelAccessListReplyMessage>(),0u);
        manager(ParcelAccessListReplyMessage(), sim);
        ensure_not(called);
    }

    DEF_TEST(5)
    {
        MessageHandler<ParcelAccessListReplyMessage> access_list_handler;
        bool called = false;
        access_list_handler.set(boost::bind(AccessListHandler, _1, _2, &called));

        manager.connect(access_list_handler);
        ensure_not(manager.empty());
        ensure_equals(manager.count<ParcelAccessListReplyMessage>(),1u);
        ensure_not(called);
        access_list_handler.disconnect();
        ensure(manager.empty());
        ensure_equals(manager.count<ParcelAccessListReplyMessage>(),0u);
        manager(ParcelAccessListReplyMessage(), sim);
        ensure_not(called);
    }
}

