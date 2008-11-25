#ifdef _MSC_VER
#	pragma warning(push)
#	pragma warning(disable: 4702)
#	pragma warning(disable: 4512)
#endif

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <cassert>
#include <set>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/format.hpp>
#include <boost/cstdint.hpp>
#include <boost/algorithm/string/trim.hpp>

enum VariableType
{
	VT_Null,			//- no data, 0 bytes wide 
	VT_Fixed,			// - byte array, interpreted depending on Message type, width determined in message definition 
	VT_Variable,		// - first byte determines number of bytes that follow 
	VT_U8,				// - unsigned byte, 1 byte wide 
	VT_U16,			// - unsigned short, 2 bytes wide 
	VT_U32,			// - unsigned int, 4 bytes wide 
	VT_U64,			// - unsigned long, 8 bytes wide 
	VT_S8,				// - signed byte, 1 byte wide 
	VT_S16,			// - signed short, 2 bytes wide 
	VT_S32,			// - signed int, 4 bytes wide 
	VT_S64,			// - signed long, 8 bytes wide 
	VT_F32,			// - float, 4 bytes wide 
	VT_F64,			// - double, 8 bytes wide 
	VT_LLVector3,		// - triplet of floats, 12 bytes wide 
	VT_LLVector3d,		// - triplet of doubles, 24 bytes wide 
	VT_LLVector4,		// - quad of floats, 16 bytes wide 
	VT_LLQuaternion,	// - because it's always a unit quaternion, transmitted in messages as a triplet of floats, 12 bytes wide (represented in memory as a quad of floats, 16 bytes wide) 
	VT_LLUUID,			// - Universal ID, 16 bytes wide 
	VT_BOOL,			// - 0 or 1, 1 byte wide 
	VT_IPADDR,			// - IP Address, one place per byte, 4 bytes wide 
	VT_IPPORT,			// - IP Port, two bytes wide 
	VT_U16Vec3,		// - not used 
	VT_U16Quat,		// - not used 
	VT_S16Array		// - not used
};

struct VariableTypeMapping{
	VariableType type;
	char const * name;
	char const * className;
	bool hasSize;
};

static VariableTypeMapping const VTMAPPING[] = {
	{VT_Null,"Null","NullType",false},
	{VT_Fixed,"Fixed","raw::LLFixed<%u>",true},
	{VT_Variable,"Variable","raw::LLVariable",false},
	{VT_U8,"U8","UInt8",false},
	{VT_U16,"U16","UInt16",false},
	{VT_U32,"U32","UInt32",false},
	{VT_U64,"U64","UInt64",false},
	{VT_S8,"S8","Int8",false},
	{VT_S16,"S16","Int16",false},
	{VT_S32,"S32","Int32",false},
	{VT_S64,"S64","Int64",false},
	{VT_F32,"F32","Real32",false},
	{VT_F64,"F64","Real64",false},
	{VT_LLVector3,"LLVector3","raw::LLVector3",false},
	{VT_LLVector3d,"LLVector3d","raw::LLVector3d",false},
	{VT_LLVector4,"LLVector4","raw::LLVector4",false},
	{VT_LLQuaternion,"LLQuaternion","raw::LLQuaternion",false},
	{VT_LLUUID,"LLUUID","LLUUID",false},
	{VT_BOOL,"BOOL","bool",false},
	{VT_IPADDR,"IPADDR","raw::LLIPAddress",false},
	{VT_IPPORT,"IPPORT","raw::LLIPPort",false},
	{VT_U16Vec3,"U16Vec3",0,false},
	{VT_U16Quat,"U16Quat",0,false},
	{VT_S16Array,"S16Array",0,false}
};

enum RepeatType
{
	RT_Single,
	RT_Multiple,
	RT_Variable
};

enum FrequencyType
{
	FT_Low,
	FT_Medium,
	FT_High,
	FT_Fixed
};

RepeatType StringToRepeatType(std::string const & str)
{
	if(str == "Single")
		return RT_Single;
	if(str.size() >= 8 && str.substr(0,8) == "Multiple")
		return RT_Multiple;
	if(str == "Variable")
		return RT_Variable;
	assert(false);
	return RT_Variable;
}

VariableType StringToVariableType(std::string const & str)
{
	for(size_t i = 0; i < sizeof(VTMAPPING); ++i)
		if(VTMAPPING[i].name == str)
			return VTMAPPING[i].type;
	assert(false);
	return VT_Null;
}

FrequencyType StringToFrequencyType(std::string const & str)
{
	if(str == "Low")
		return FT_Low;
	if(str == "Medium")
		return FT_Medium;
	if(str == "High")
		return FT_High;
	if(str == "Fixed")
		return FT_Fixed;
	assert(false);
	return FT_Fixed;
}

char const * FrequencyTypeToString(FrequencyType ft)
{
	switch(ft)
	{
	case FT_Low:	return "FT_LOW";
	case FT_Medium: return "FT_MEDIUM";
	case FT_High:	return "FT_HIGH";
	case FT_Fixed:	return "FT_FIXED";
	}
	return "";
}


struct VariableField
{
	VariableField(std::string const & n, VariableType vt, boost::uint32_t s = 0)
	: name(n), type(vt), size(s)
	{}	

	std::string name;
	VariableType type;
	boost::uint32_t size;
};

struct Block
{
	Block(std::string const & n, RepeatType rt, std::size_t cnt = 0)
	: name(n), repeat(rt), repeat_count(cnt), variables()
	{}
	
	std::string name;
	RepeatType repeat;
	std::size_t repeat_count;

	std::vector<VariableField> variables;
};

typedef boost::shared_ptr<Block> BlockPtr;

struct Message
{
	Message(std::string const & n, FrequencyType ft, boost::uint16_t i, bool t = false, bool enc = false)
	: name(n), frequencyType(ft), id(i), encoded(enc), trusted(t), blocks()
	{}

	std::string name;
	FrequencyType frequencyType;
	boost::uint32_t id;
	bool encoded;
	bool trusted;
	std::vector< BlockPtr > blocks;
};

typedef boost::shared_ptr<Message> MessagePtr;

struct Parser
{
	boost::array<MessagePtr, 0xFFFF> LowMessages;
	boost::array<MessagePtr, 0xFF>   MedMessages;
	boost::array<MessagePtr, 0xFF>   HigMessages;

	typedef std::vector<std::string> lines_t;
	std::set<std::string> & m_unused;
	Parser(std::set<std::string> & unused, lines_t & lines)
		: LowMessages()
		, MedMessages()
		, HigMessages()
		, m_unused(unused)
	{
		Parse(lines);
	}

	void Split(std::string const & data, std::vector<std::string> & parts)
	{
		std::istringstream 	istr(data);
		do 
		{
			std::string part;
			istr >> part;
			if(istr)
			{
				parts.push_back(part);
				if(parts.back().size() >= 2 && parts.back().substr(0,2) == "//")
				{
					parts.pop_back();
					return;
				}
			}
		} while(istr);		
	}		

	void Parse(lines_t & lines)
	{	
		int depth = 0;
		MessagePtr currentMessage;
		BlockPtr currentBlock;
		BOOST_FOREACH(std::string & line, lines)
		{
			lines_t parts;
			Split(line, parts);

			if(line == "{")
			{
				++depth;
			}
			else if(line == "}")
			{
				--depth;
			}
			else if(depth == 1)
			{
				// Packet				
				FrequencyType freq = StringToFrequencyType(parts[1]);
				bool trusted = parts[2 + (freq == FT_Fixed)] == "Trusted";
				bool encoded = parts[3 + (freq == FT_Fixed)] == "Zerocoded";
				boost::uint16_t id = 0;
				if(parts[2].size() > 2 && parts[2].substr(0,2) == "0x")
				{
					std::istringstream istr(parts[2].substr(2));
					boost::uint32_t tmpId = 0;
					istr >> std::hex >> tmpId;
					if(!istr)
						throw boost::bad_lexical_cast();
					id = boost::uint16_t(tmpId & 0xFFFF);
				}
				else
				{
					id = boost::lexical_cast<boost::uint16_t>(parts[2]);
				}
				
				currentMessage.reset(new Message(parts[0], freq, id, trusted, encoded));
				switch(freq)
				{
				case FT_Fixed:
				case FT_Low:
					LowMessages[id] = currentMessage;
					break;
				case FT_Medium:
					MedMessages[id] = currentMessage;
					break;
				case FT_High:
					HigMessages[id] = currentMessage;
					break;
				}

			}
			else if(depth == 2)
			{
				if(parts.size() >= 4 && parts.front() == "{")
				{
					//Variable
					VariableType varType = StringToVariableType(parts[2]);
					currentBlock->variables.push_back(VariableField(parts[1],varType, 1));
					if(parts.size() == 5)
						currentBlock->variables.back().size = boost::lexical_cast<size_t>(parts[3]);
				}
				else
				{
					// New block
					RepeatType rt = StringToRepeatType(parts[1]);
					currentBlock.reset(new Block(parts[0], rt, rt == RT_Single ? 1 : -1));
					if(rt == RT_Multiple)
						currentBlock->repeat_count = boost::lexical_cast<size_t>(parts[2]);
					currentMessage->blocks.push_back(currentBlock);
				}
			}
		}
	}
};

struct Builder
{
	Parser & m_parser;
	Builder(Parser & parser)
		: m_parser(parser)
	{
	}

	void write(std::string const & outfile)
	{
		std::ofstream ofs(outfile.c_str());
		write(ofs);
	}	

	void write()
	{
		write(std::cout);		
	}	

	void write(std::ostream & os)
	{
		os << "#ifndef GUARD_LIBOMVTK_PACKETS_PACKETS_H_INCLUDED\n#define GUARD_LIBOMVTK_PACKETS_PACKETS_H_INCLUDED\n";
		os << "\n\n#if _MSC_VER > 1200\n#	pragma once\n#endif\n\n";
		os << "#include \"../packets/processors.h\"\n";
		os << "namespace omvtk\n{\n";
		os << "\tnamespace packets\n\t{\n";
		std::map<boost::uint32_t, std::string> message_types;
		write(os,m_parser.LowMessages,message_types);		
		write(os,m_parser.MedMessages,message_types);		
		write(os,m_parser.HigMessages,message_types);		
//		os << "\t\tMessagePtr MessageFactory(UInt32 id, ByteBuffer & data, std::size_t & pos)\n\t\t{";
//		os << "\t\t\tswitch(id)\n";
//		os << "\t\t\t{\n";
		typedef std::pair<boost::uint32_t, std::string> msgpair;
		os << "\t\ttemplate<typename Func>\n";
		os << "\t\tinline bool Lookup(UInt32 msg_id, Func & fn)\n";
		os << "\t\t{\n";
		os << "\t\t\tswitch(msg_id)\n";
		os << "\t\t\t{\n";
		BOOST_FOREACH(msgpair p, message_types)
		{
			os << "\t\t\tcase " << p.second << "Message::id:\n";
			os << "\t\t\t\tfn.template apply<" << p.second <<  "Message>();\n";
			os << "\t\t\t\treturn true;\n\n";
		}
		os << "\t\t\tdefault: break;\n";
		os << "\t\t\t}\n";
		os << "\t\t\treturn false;\n";
		os << "\t\t}\n";
		os << "\t}//namespace packets\n";
		os << "}//namespace omvtk\n";
		os << "#endif //GUARD_LIBOMVTK_PACKETS_PACKETS_H_INCLUDED\n";
	}

	template<size_t N>
	void write(std::ostream & os, boost::array<MessagePtr, N> & messages, std::map<boost::uint32_t, std::string> & message_types)
	{
		BOOST_FOREACH(MessagePtr ptr, messages)
		{
			if(ptr && m_parser.m_unused.count(std::string(ptr->name)) == 0)
			{
				if(ptr->frequencyType == FT_Low || ptr->frequencyType == FT_Fixed)
					ptr->id |= 0xFFFF0000;
				if(ptr->frequencyType == FT_Medium)
					ptr->id |= 0xFF000000;
				message_types[ptr->id] = ptr->name;
				write_message(os, *ptr);
			}
		}
	}

	void write_message(std::ostream & os, Message & msg)
	{
		std::string msg_fmt = 
		"\t\tstruct %sMessage\n"
		"\t\t\t: Message\n"
		"\t\t{\n"
		"\t\t\tstatic char const * name(){ return \"%s\"; }\n"
		"\t\t\tstatic bool const trusted = %s;\n"
		"\t\t\tstatic UInt32 const id = 0x%.08X;\n"
		"\t\t\tstatic FrequencyType const frequency = %s;\n"
		"\t\t\tstatic bool const encoded = %s;\n"
		"\t\t\t\n\n"
		"\t\t\t%sMessage()\n"
		"\t\t\t: Message(%sHeader())\n"
		"%s"
		"\t\t\t{}\n\n"
		"\t\t\t%sMessage(ByteBuffer & data, std::size_t & pos)\n"
		"\t\t\t: Message(%sHeader(data, pos))\n"
		"%s"
		"\t\t\t{\n"
		"\t\t\t\tDeserializer deserializer(data, pos);\n"
		"\t\t\t\tdeserialize(deserializer, *this);\n"
		"\t\t\t}\n"
		"\t\t\t\n\n"
		"%s\n"
		"\t\t\ttemplate<typename Processor>\n"
		"\t\t\tvoid process(Processor & p)\n"
		"\t\t\t{\n"
		"%s"
		"\t\t\t}\n\n"
		"\t\t};\n\n";
		
		boost::format msg_format(msg_fmt);

		msg_format % msg.name;
		msg_format % msg.name;
		msg_format % (msg.trusted ? "true" : "false");
		msg_format % msg.id;
		msg_format % FrequencyTypeToString(msg.frequencyType);
		msg_format % (msg.encoded ? "true" : "false");

		std::string header_prefix;
		if(msg.frequencyType == FT_Low || msg.frequencyType == FT_Fixed)
			header_prefix = "Low";
		else if(msg.frequencyType == FT_Medium)
			header_prefix = "Medium";
		else
			header_prefix = "High";
		
		std::string blk_fmt = 
			"\t\t\tstruct %sBlock\n"
			"\t\t\t{\n"
			"%s\n"
			"\t\t\t\ttemplate<typename Processor>\n"
			"\t\t\t\tvoid process(Processor & p)\n"
			"\t\t\t\t{\n"
			"%s"
			"\t\t\t\t}\n\n"
			"\t\t\t};\n\n";

		std::string block_defs;
		std::string block_vars;
		std::string block_ser;
		std::string block_init;

		std::ostringstream block_stream;
		BOOST_FOREACH(BlockPtr blkptr, msg.blocks)
		{
			Block & blk = *blkptr;
			std::string var_ser;
			std::string variables;
		
			BOOST_FOREACH(VariableField & var,blk.variables)
			{
				boost::format varfmt("\t\t\t\t%s %s;\n");				
				if(var.type == VT_Fixed && VTMAPPING[var.type].hasSize)
				{
					varfmt % (boost::format(VTMAPPING[var.type].className) % var.size);					
				}
				else
				{
					varfmt % VTMAPPING[var.type].className;
				}
				variables += (varfmt % var.name).str();
				var_ser  += (boost::format("\t\t\t\t\tp.process(%s,\"%s\");\n") % var.name % var.name).str();
			}
			
			if(var_ser.empty())
			{
				var_ser = "\t\t\t\t\t(void)p; // avoiding unreferenced warnings\n"; 
			}

			block_init += (boost::format("\t\t\t, %s()\n") % blk.name).str();
			block_defs += (boost::format(blk_fmt) % blk.name % variables % var_ser).str();

			if(blk.repeat == RT_Single)
			{
				block_vars	+= (boost::format("\t\t\t%sBlock %s;\n") % blk.name % blk.name).str();
				block_ser	+= (boost::format("\t\t\t\tp.process(%s,\"%s\");\n") % blk.name % blk.name).str();				
			}
			if(blk.repeat == RT_Multiple)
			{
				block_vars	+= (boost::format("\t\t\tboost::array<%sBlock,%i> %s;\n") % blk.name % blk.repeat_count % blk.name).str();
				block_ser	+= (boost::format("\t\t\t\tp.process(%s,\"%s\");\n") % blk.name % blk.name).str();
			}
			if(blk.repeat == RT_Variable)
			{
				block_vars	+= (boost::format("\t\t\tstd::vector<%sBlock> %s;\n") % blk.name % blk.name ).str();
				block_ser	+= (boost::format("\t\t\t\tp.process(%s,\"%s\");\n") % blk.name %  blk.name).str();
			}
		}

		if(block_ser.empty())
		{
			block_ser = "\t\t\t\t(void)p; // avoiding unreferenced warnings\n"; 
		}

		msg_format % msg.name;
		msg_format % header_prefix;
		msg_format % block_init;
		msg_format % msg.name;
		msg_format % header_prefix;
		msg_format % block_init;

		msg_format % (block_defs + "\n" + block_vars) % block_ser;

		os << msg_format.str();
	}	
};

int main()
{
	std::set<std::string> unused_packets;
	std::ifstream unused_in("unusedpackets.txt");
	std::string line;
	while(std::getline(unused_in, line))
	{
		boost::trim(line);
		unused_packets.insert(line);
	}
	std::ifstream ifs("message_template.msg");

	std::vector<std::string> lines;
	while(std::getline(ifs, line))
	{
		line = boost::trim_copy(line);
		if(line.empty())
			continue;
		if(line.size() >= 2 && line.substr(0,2) == "//")
			continue;
		if(!line.empty())
			lines.push_back(line);
	}
	Parser parser(unused_packets, lines);	
	Builder(parser).write("packets.h");
}

