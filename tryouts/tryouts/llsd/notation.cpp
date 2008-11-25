#include "stdafx.h"
#include "notation.h"
#include "llsd.h"
#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/foreach.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include "../base64.h"
#include "../throw.h"

namespace LLSD
{	
	namespace detail
	{
		namespace Notation
		{		
			typedef Parser::iterator iterator;
			iterator SkipNumbers(iterator iter, iterator end)
			{
				if(iter != end && *iter == '-')
					++iter;
				while(iter != end)
				{
					if(!(*iter >= '0' && *iter <= '9'))
					{
						return iter;
					}
					++iter;
				}
				return end;
			}

			size_t ParseSize(iterator & iter, iterator end)
			{
				if(iter == end)
					LIBVW_THROWS(LLSDNotationParseError);


				if(*iter != '(')
					LIBVW_THROWS(LLSDNotationParseError);

				iterator start = ++iter;
				iter = SkipNumbers(start, end);

				size_t len = boost::lexical_cast<size_t>(std::string(start, iter));

				if(iter == end || *iter != ')')
					LIBVW_THROWS(LLSDNotationParseError);							

				++iter;

				return len;
			}

			iterator SkipWSC(iterator iter, iterator end, bool mapDelim = false)
			{
				while(iter != end)
				{
					switch(*iter)
					{
					case ':':
						if(!mapDelim)
							return iter;
					case '\r':
					case '\n':
					case '\t':
					case ' ':
					case ',':
						++iter;
						break;
					default:
						return iter;
					}
				}
				return end;
			}

			boost::uint8_t ToHexNibble(char c)
			{
				if(c >= '0' && c <= '9')
					return boost::uint8_t(c -= '0');
				if(c >= 'a' && c <= 'f')
					return boost::uint8_t(c -= 'f');
				return 0;
			}

			iterator ParseString(iterator iter, iterator end, StringPtr & val)
			{
				if(iter == end)
					return end;

				StringPtr str = Value().ToString();
				std::string strVal;
				iterator start = iter+1;
				char first = *iter;
				++iter;
				while(iter != end)
				{
					bool escape = (*iter == '\\');

					if(escape && ++iter == end)
						LIBVW_THROWS(LLSDNotationParseError);

					char c = *iter;

					if(escape)
					{
						if(escape)
						{
							switch(c)
							{
							case 'n':
								strVal += '\n'; break;
							case 'r':
								strVal += '\r'; break;
							case 't':
								strVal += '\t'; break;
							case 'a':
								strVal += '\a'; break;
							case 'f':
								strVal += '\f'; break;
							case 'v':
								strVal += '\v'; break;
							case '\\':
								strVal += '\\'; break;
							case '"':
								strVal += '"'; break;
							case '\'':
								strVal += '\''; break;
							case 'x':
								{
									c = tolower(c);
									if(++iter == end)
										LIBVW_THROWS(LLSDNotationParseError);
									strVal += char(ToHexNibble(c) << 4 | ToHexNibble(*iter));												
								}
								break;
							}
						}
					}
					else 
					{
						if(c == first)
						{
							++iter;
							break;
						}
						strVal += c;
					}
					++iter;
				}

				str->SetValue(strVal);
				val = str;
				return iter;
			}

			iterator Parse(iterator iter, iterator end, ValuePtr & val);
			iterator ParseArray(iterator iter, iterator end, ValuePtr & val)
			{
				ArrayPtr ar = Value().ToArray();
				val = ar;

				iter = SkipWSC(iter+1, end);

				while(iter != end)
				{
					iter = SkipWSC(iter,end);
					
					if(iter == end)
						LIBVW_THROWS(LLSDNotationParseError);

					if(*iter == ']')
						return ++iter;			
					
					ValuePtr next;
					iter = Parse(iter, end, next);					

					if(next)
						ar->push_back(next);
				}
				return iter;
			}
			
			iterator ParseMap(iterator iter, iterator end, ValuePtr & val)
			{
				MapPtr map = Value().ToMap();
				val = map;

				iter = SkipWSC(iter+1, end);

				while(iter != end)
				{
					iter = SkipWSC(iter,end);

					if(iter == end)
						LIBVW_THROWS(LLSDNotationParseError);

					if(*iter == '}')
						return ++iter;			

					StringPtr first;
					iter = ParseString(iter, end, first);					
					
					iter = SkipWSC(iter, end, true);

					ValuePtr second;
					iter = Parse(iter, end, second);
					
					if(!first || !second)
						LIBVW_THROWS(LLSDNotationParseError);
					
					map->insert(first->GetValue(), second);
				}
				return iter;
			}
			
			bool IsNotB64(char c)
			{
				static const char lookup_table[] = {
					-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
					-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
					-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
					52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-1,-1,-1,
					-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
					15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
					-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
					41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1
				};
				return lookup_table[c] == -1;
			}

			iterator Parse(iterator iter, iterator end, ValuePtr & val)
			{
				iter = SkipWSC(iter, end);
				while(iter != end)
				{
					switch(*iter)
					{
					case '[':
						return ParseArray(iter, end, val);
					case '{':
						return ParseMap(iter, end, val);
					case '!':
						val = ValuePtr(new Value());
						return ++iter;
					case 'r':
						// parse real
						{
							iterator start = ++iter;
							iter = SkipNumbers(iter, end);
							if(iter != end && *iter == '.')
								iter = SkipNumbers(++iter, end);
							val = Real::FromString(std::string(start, iter));								
							return iter;
						}
						break;
					case 'u':
						// parse uuid
						if((end - iter) >= 37) // we need at least 37 characters u + 36uuid
						{														
							val = UUIDPtr(new UUID(std::string(iter+1, iter + 37)));
							return iter + 37;
						}
						LIBVW_THROWS(LLSDNotationParseError);
						break;
					case 'i':
						//parse integer 
						{
							iterator start = ++iter;
							iter = SkipNumbers(start, end);
							if(iter != end)
								val = IntegerPtr(new Integer(boost::lexical_cast<boost::uint32_t>(std::string(start,iter))));
							else 
								LIBVW_THROWS(LLSDNotationParseError);
							return iter;
						}
						break;
					case '"':
					case '\'':
						{
							StringPtr str;
							iter = ParseString(iter, end, str);
							val = str;
							return iter;
						}
					case 's':
						//parse raw string
						{
							
							size_t len = ParseSize(++iter, end);

							StringPtr strVal;														
							iter = ParseString(iter, end, strVal);
							
							if(!strVal || strVal->GetValue().size() != len)
								LIBVW_THROWS(LLSDNotationParseError);
							
							val = strVal;
							return iter;
						}
						break;
					case 'b':
						//parse binary
						{
							++iter;
							if(iter == end)
								LIBVW_THROWS(LLSDNotationParseError);
							BinaryPtr bin;
							if(*iter == '(')
							{
								size_t len = ParseSize(iter, end);
								size_t diff = std::distance(iter,end);
								if(diff >= len)
								{
									if(*iter != '"')
										LIBVW_THROWS(LLSDNotationParseError);
									iterator bend = iter + len;
									bin.reset(new Binary(iter+1,bend-1));
									iter += len;
									if(*iter != '"')
										LIBVW_THROWS(LLSDNotationParseError);
									val = bin;
									return ++iter;
								}
								LIBVW_THROWS(LLSDNotationParseError);
							}
							else if(end - iter >= 4)
							{
								bool escape = *iter == '6' && *(++iter) == '4';
								iter += 2;
								iterator bend = std::find(iter, end, '\"');
								std::string buf(iter,bend);								
								if(escape)
								{

									buf.erase(std::remove_if(buf.begin(), buf.end(), IsNotB64), buf.end());
									bin.reset(new Binary(encoding::base64_decode<Binary>(buf)));
								}
								else
								{
									bin.reset(new Binary(buf.begin(), buf.end()));
								}
								val = bin;
								return bend+1;
							}
							LIBVW_THROWS(LLSDNotationParseError);
						}
						break;
					case 'l':
						//parse uri
						{
							StringPtr str;
							iter = ParseString(++iter, end, str);							
							if(!str)
								LIBVW_THROWS(LLSDNotationParseError);
							val = UriPtr(new Uri(str->GetValue()));
							return iter;
						}
						break;
					case 'd':
						//parse date
						{
							++iter;
							if(!(iter != end && *iter == '"'))
								LIBVW_THROWS(LLSDNotationParseError);
							iterator dend = std::find(++iter, end, '"');
							std::string dateStr(iter, dend);
							val = Date::CreateFromISOString(dateStr);																					
							return dend+1;
						}
						break;
					case '0':
					case 'f':
					case 'F':
						// parse false
						{
							val = BooleanPtr(new Boolean(false));
							if(end - iter >= 5)
							{
								std::string fstr(iter,iter+5);
								boost::to_lower(fstr);
								if(fstr == "false")
									iter += 5;
								else 
									++iter;
							}
							return iter;							
						}
					case '1':
					case 'T':
					case 't':
						// parse true
						{
							val = BooleanPtr(new Boolean(true));
							if(end - iter >= 4)
							{
								std::string fstr(iter,iter+4);
								boost::to_lower(fstr);
								if(fstr == "true")
									iter += 4;
								else 
									++iter;
							}							
							return iter;							
						}
						break;
					default:
						LIBVW_THROWS(LLSDNotationParseError);
					}
					LIBVW_THROWS(LLSDNotationParseError);
				}
				return end;
			}

			ValuePtr Parser::Parse(iterator iter, iterator end)
			{
				ValuePtr val;
				Notation::Parse(SkipWSC(iter, end), end, val);
				return val;
			}

			std::string EscapeString(std::string const & str)
			{
				static const char* EncodingChars[256] =
				{
					"\\x00","\\x01","\\x02","\\x03","\\x04",
					"\\x05","\\x06","\\a","\\b","\\t","\\n",
					"\\v","\\f","\\r","\\x0e","\\x0f","\\x10",
					"\\x11","\\x12","\\x13","\\x14","\\x15",
					"\\x16","\\x17","\\x18","\\x19","\\x1a",
					"\\x1b","\\x1c","\\x1d","\\x1e","\\x1f",
					" ","!","\"","#","$","%","&","\\'","(",
					")","*","+",",","-",".","/","0","1","2",
					"3","4","5","6","7","8","9",":",";","<",
					"=",">","?","@","A","B","C","D","E","F",
					"G","H","I","J","K","L","M","N","O","P",
					"Q","R","S","T","U","V","W","X","Y","Z",
					"[","\\\\","]","^","_","`","a","b","c",
					"d","e","f","g","h","i","j","k","l","m",
					"n","o","p","q","r","s","t","u","v","w",
					"x","y","z","{","|","}","~","\\x7f","\\x80",
					"\\x81","\\x82","\\x83","\\x84","\\x85",
					"\\x86","\\x87","\\x88","\\x89","\\x8a",
					"\\x8b","\\x8c","\\x8d","\\x8e","\\x8f",
					"\\x90","\\x91","\\x92","\\x93","\\x94",
					"\\x95","\\x96","\\x97","\\x98","\\x99",
					"\\x9a","\\x9b","\\x9c","\\x9d","\\x9e",
					"\\x9f","\\xa0","\\xa1","\\xa2","\\xa3",
					"\\xa4","\\xa5","\\xa6","\\xa7","\\xa8",
					"\\xa9","\\xaa","\\xab","\\xac","\\xad",
					"\\xae","\\xaf","\\xb0","\\xb1","\\xb2",
					"\\xb3","\\xb4","\\xb5","\\xb6","\\xb7",
					"\\xb8","\\xb9","\\xba","\\xbb","\\xbc",
					"\\xbd","\\xbe","\\xbf","\\xc0","\\xc1",
					"\\xc2","\\xc3","\\xc4","\\xc5","\\xc6",
					"\\xc7","\\xc8","\\xc9","\\xca","\\xcb",
					"\\xcc","\\xcd","\\xce","\\xcf","\\xd0",
					"\\xd1","\\xd2","\\xd3","\\xd4","\\xd5",
					"\\xd6","\\xd7","\\xd8","\\xd9","\\xda",
					"\\xdb","\\xdc","\\xdd","\\xde","\\xdf",
					"\\xe0","\\xe1","\\xe2","\\xe3","\\xe4",
					"\\xe5","\\xe6","\\xe7","\\xe8","\\xe9",
					"\\xea","\\xeb","\\xec","\\xed","\\xee",
					"\\xef","\\xf0","\\xf1","\\xf2","\\xf3",
					"\\xf4","\\xf5","\\xf6","\\xf7","\\xf8",
					"\\xf9","\\xfa","\\xfb","\\xfc","\\xfd",
					"\\xfe","\\xff"		
				};
				std::string ret;
				BOOST_FOREACH(char const & c, str)
				{
					ret += EncodingChars[c];
				}
				return ret;
			}

			std::string Build(LLSD::ValuePtr data)
			{
				if(data)
				{
					switch(data->GetType())
					{
					case VTID_INTEGER:
						return "i" + boost::lexical_cast<std::string>(Value::AsInteger(data)->GetValue());
					case VTID_REAL:
						{
							RealPtr ptr = LLSD::Value::AsReal(data);
							double val = ptr->GetValue();					
							std::string result = "nan";
							if(!boost::math::isnan(val))
							{
								std::ostringstream tmp;
								tmp.precision(10);
								tmp << val;
								result = tmp.str();
							}
							return "r" + result;
						}
					case VTID_STRING:
						return "\'" + EscapeString(Value::AsString(data)->GetValue()) + "\'";
					case VTID_DATE:
						return "d\"" +  Date::MakeIso(Value::AsDate(data)) + "\"";
					case VTID_UUID:
						return "u" + UUID::ToString(Value::AsUUID(data));
					case VTID_BOOLEAN:
						return Value::AsBoolean(data)->GetValue() ? "1" : "0";
					case VTID_BINARY:
						{
							BinaryPtr bin = Value::AsBinary(data);
							return "b64\""  + encoding::base64_encode<std::string>(bin->GetValue()) + "\"";
						}
					case VTID_URI:
						return "u\"" + Value::AsUri(data)->GetValue().toString() + "\"";
					case VTID_MAP:
						{
							MapPtr map = Value::AsMap(data);
							bool first = true;
							std::string result = "{";
							BOOST_FOREACH(Map::PairType const & p, *map)
							{
								if(!first)
									result.push_back(',');
								result += "'" + EscapeString(p.first) + "'";
								result.push_back(':');
								result += Build(p.second);
								first = false;
							}
							return result + "}";
						}
						
					case VTID_ARRAY:
						{
							ArrayPtr ar = Value::AsArray(data);
							bool first = true;
							std::string result = "[";
							BOOST_FOREACH(ValuePtr & val, *ar)
							{
								if(!first)
									result.push_back(',');
								result += Build(val);
								first = false;
							}	
							return result + "]";
						}
					case VTID_UNDEFINED:
					default:
						// No good neither nor
						return "!";
					}
				}
				return "[]";
			}
		}
	}	
}