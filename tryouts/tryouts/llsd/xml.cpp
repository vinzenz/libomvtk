#include "stdafx.h"
#include "xml.h"
#include <boost/format.hpp>
#include <iomanip>
#include <boost/math/special_functions/fpclassify.hpp>

#define TIXML_USE_TICPP
#include "../../../3rdparty/tinyxml/ticpp.h"
#include "../base64.h"
#include "../throw.h"
#include "llsd.h"

namespace LLSD
{
	namespace detail
	{
		namespace XML
		{
			Parser::Parser()
			{
				static bool initialized_map = false;
				if(!initialized_map){
					InitLookupTable();
					initialized_map = true;
				}
			}

			std::map<std::string, LLSD::ValueType> Parser::LookupTable;
			void Parser::InitLookupTable()
			{
				LookupTable["string"]	= LLSD::VTID_STRING;
				LookupTable["integer"]	= LLSD::VTID_INTEGER;
				LookupTable["boolean"]	= LLSD::VTID_BOOLEAN;
				LookupTable["binary"]	= LLSD::VTID_BINARY;
				LookupTable["date"]		= LLSD::VTID_DATE;
				LookupTable["uuid"]		= LLSD::VTID_UUID;
				LookupTable["uri"]		= LLSD::VTID_URI;
				LookupTable["real"]		= LLSD::VTID_REAL;
				LookupTable["undef"]	= LLSD::VTID_UNDEFINED;
				LookupTable["map"]		= LLSD::VTID_MAP;		
				LookupTable["array"]	= LLSD::VTID_ARRAY;
			}

			struct CommentNotification{};
			ValuePtr Parser::ParseArray(ticpp::Node * node)
			{
				Array arr;
				ticpp::Iterator<ticpp::Node> elems;
				for(elems = elems.begin(node); elems != elems.end(); ++elems)					
				{
					ValuePtr val;
					while(!(val = Parse(elems.Get(), true)) && ++elems != elems.end());
					if(val)
						arr.push_back(val);
				}
				return arr.ToArray(); // Clone to dynamic
			}

			ValuePtr Parser::ParseMap(ticpp::Node * node)
			{
				Map map;
				ticpp::Iterator<ticpp::Node> elems;
				for(elems = elems.begin(node); elems != elems.end(); ++elems)
				{		
					ticpp::Node * p = elems->FirstChild();

					if(!p)
						LIBVW_THROWS(LLSDXmlParseError);

					std::string key = p->Value();

					++elems;

					if(elems == elems.end())
						LIBVW_THROWS(LLSDXmlParseError);

					ValuePtr val;
					
					while(!(val = Parse(elems.Get(), true)) && ++elems != elems.end());
					
					if(val)
						map[key] = val;

				}
				return map.ToMap(); //Clone a dynamic
			}

			ValuePtr Parser::Parse(ticpp::Node * node, bool returnEmpty)
			{
				if(!node)
					LIBVW_THROWS(LLSDXmlParseError);
				if(node->Type() != TiXmlNode::ELEMENT || node->Type() == TiXmlNode::TEXT)
				{
					if(returnEmpty)
						return ValuePtr();
					return Parse(node->NextSibling());
				}

				std::string nodeN = node->Value();
				if(LookupTable.count(nodeN) > 0)
				{
					ticpp::Node * tmp = node->FirstChild(false);
					switch(LookupTable[nodeN])
					{							
					case VTID_INTEGER:
						if(tmp && tmp->Type() == TiXmlNode::TEXT)					
							return Integer::FromString(tmp->Value());
						return IntegerPtr(new Integer());
					case VTID_REAL:
						if(tmp && tmp->Type() == TiXmlNode::TEXT)
							return Real::FromString(tmp->Value());
						return RealPtr(new Real());
					case VTID_STRING:
						if(tmp && tmp->Type() == TiXmlNode::TEXT)
							return StringPtr(new String(tmp->Value()));
						return StringPtr(new String());
					case VTID_DATE:
						if(tmp && tmp->Type() == TiXmlNode::TEXT)
							return Date::CreateFromISOString(tmp->Value());
						return DatePtr(new Date());
					case VTID_UUID:
						if(tmp && tmp->Type() == TiXmlNode::TEXT)
							return UUIDPtr(new UUID(tmp->Value()));
						return UUIDPtr(new UUID());
					case VTID_BOOLEAN:
						if(tmp && tmp->Type() == TiXmlNode::TEXT)
						{
							std::string value = tmp->Value();
							if(value == "1" || value == "true")
								return BooleanPtr(new Boolean(true));
							else if(value == "0" || value == "false")
								return BooleanPtr(new Boolean(false));							
						}
						return BooleanPtr(new Boolean());
					case VTID_BINARY:
						if(tmp && tmp->Type() == TiXmlNode::TEXT)
							return LLSD::Binary::FromBase64(tmp->Value());
						return LLSD::BinaryPtr(new LLSD::Binary());
					case VTID_URI:
						if(tmp && tmp->Type() == TiXmlNode::TEXT)
							return UriPtr(new Uri(tmp->Value()));
						return UriPtr(new Uri());
					case VTID_MAP:
						return ParseMap(node);
					case VTID_ARRAY:
						return ParseArray(node);
					case VTID_UNDEFINED:
					default:
						return ValuePtr(new Value());
					}

					LIBVW_THROWS(LLSDXmlParseError);
				}

				ticpp::Iterator<ticpp::Node> elems;
				for(elems = elems.begin(node); elems != elems.end(); ++elems)
				{		
					return Parse(elems.Get());
				}

				return ValuePtr();
			}

			ValuePtr Parser::Parse(iterator it, iterator end)
			{
				Parser parser;
				try
				{
					ticpp::Document doc;
					doc.Parse(std::string(it, end), true, TIXML_ENCODING_UTF8);
					return parser.Parse(doc.FirstChild());
				}
				catch(std::exception const & e)
				{
					std::cout << "Exception caught: (std::exception) " << e.what() << std::endl;
				}	
				catch(...)
				{
					std::cout << "Exception caught: (unknown)" << std::endl;
				}	
				return ValuePtr();
			}

			std::string SerializeType(LLSD::ValuePtr value)
			{
				boost::format general_format("<%1%>%2%</%1%>");

				if(!value) return "";
				switch(value->GetType())
				{
				case VTID_INTEGER:
					{
						IntegerPtr ptr = LLSD::Value::AsInteger(value);
						general_format % "integer" % ptr->GetValue();
						return general_format.str();
					}
				case VTID_REAL:
					{
						RealPtr ptr = LLSD::Value::AsReal(value);
						double val = ptr->GetValue();					
						if(boost::math::isnan(val))
						{
							 general_format % "real" % "nan";
						}
						else
						{
							std::ostringstream tmp;
							tmp.precision(10);
							tmp << val;
							general_format % "real" % tmp.str();
						}
						return general_format.str();
					}
				case VTID_STRING:
					{
						StringPtr ptr = LLSD::Value::AsString(value);
						general_format % "string" % ptr->GetValue();
						return general_format.str();
					}
				case VTID_DATE:
					{
						DatePtr ptr = LLSD::Value::AsDate(value);
						general_format % "date" % LLSD::Date::MakeIso(ptr);
						return general_format.str();
					}
				case VTID_UUID:
					{
						LLSD::UUIDPtr ptr = LLSD::Value::AsUUID(value);
						general_format % "uuid" % LLSD::UUID::ToString(*ptr);
						return general_format.str();
					}
				case VTID_BOOLEAN:
					{
						BooleanPtr ptr = LLSD::Value::AsBoolean(value);
						general_format % "boolean" % (ptr->GetValue() ? "true" : "false");
						return general_format.str();
					}
				case VTID_BINARY:
					{
						BinaryPtr ptr = LLSD::Value::AsBinary(value);
						general_format % "binary" % encoding::base64_encode<std::string>(ptr->GetValue());
						return general_format.str();
					}
				case VTID_URI:
					{						
						UriPtr ptr = LLSD::Value::AsUri(value);
						general_format % "uri" % ptr->GetValue().toString();
						return general_format.str();
					}
				case VTID_MAP:
					{
						MapPtr map = LLSD::Value::AsMap(value);
						std::string tmp = "<map>";
						typedef LLSD::Map::const_iterator iterator;
						for(iterator iter = map->begin(); iter != map->end(); ++iter)
						{
							tmp += "<key>" + iter->first + "</key>";
							tmp += SerializeType(iter->second);
						}
						return tmp + "</map>";
					}
				case VTID_ARRAY:
					{
						ArrayPtr arr = LLSD::Value::AsArray(value);
						std::string tmp = "<array>";
						for(size_t i = 0; i < arr->size(); ++i)
							tmp += SerializeType(arr->at(i));
						return tmp + "</array>";
					}
				case VTID_UNDEFINED:
				default:
					break;
				}
				return "";
			}

			std::string Build(LLSD::ValuePtr map)
			{
				try
				{
					if(!map || map->GetType() == VTID_UNDEFINED) 
						return "<llsd></llsd>";
					return "<llsd>" + SerializeType(map) + "</llsd>";
				}
				catch(LIBVWException const & e)
				{
					std::cout << "LIBVWException occoured: [" << e.what() 
							  << "] FILE: " << e.location().file() 
							  << " Line: " << e.location().line() 
							  << std::endl;
				}
				catch (std::exception const & e)
				{	
					std::cout << "Exception occoured: [" << e.what() << "] << FILE: " << __FILE__ << " Line: " << __LINE__ << std::endl;
				}
				catch(...)
				{
					std::cout << "Unknown Exception occurred. FILE: " << __FILE__ << " Line: " << __LINE__ << std::endl;
				}
				return "<llsd></llsd>";
			}
		}
	}
}