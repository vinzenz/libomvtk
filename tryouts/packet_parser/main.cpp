#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cassert>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
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
};

static VariableTypeMapping const VTMAPPING[] = {
	{VT_Null,"Null"},
	{VT_Fixed,"Fixed"},
	{VT_Variable,"Variable"},
	{VT_U8,"U8"},
	{VT_U16,"U16"},
	{VT_U32,"U32"},
	{VT_U64,"U64"},
	{VT_S8,"S8"},
	{VT_S16,"S16"},
	{VT_S32,"S32"},
	{VT_S64,"S64"},
	{VT_F32,"F32"},
	{VT_F64,"F64"},
	{VT_LLVector3,"LLVector3"},
	{VT_LLVector3d,"LLVector3d"},
	{VT_LLVector4,"LLVector4"},
	{VT_LLQuaternion,"LLQuaternion"},
	{VT_LLUUID,"LLUUID"},
	{VT_BOOL,"BOOL"},
	{VT_IPADDR,"IPADDR"},
	{VT_IPPORT,"IPPORT"},
	{VT_U16Vec3,"U16Vec3"},
	{VT_U16Quat,"U16Quat"},
	{VT_S16Array,"S16Array"}
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
	boost::uint16_t id;
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
	Parser(lines_t & lines)
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

int main()
{
	std::ifstream ifs("message_template.msg");

	std::string line;
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
	Parser parser(lines);

}


