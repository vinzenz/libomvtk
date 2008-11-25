#ifdef _MSC_VER
#	pragma warning(push)
#	pragma warning(disable: 4702)
#	pragma warning(disable: 4512)
#endif

#include "notation.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/foreach.hpp>
#include "traits.h"
#include "../types/exceptions.h"
#include "../types/assert.h"

namespace omvtk
{	
	namespace detail
	{
		namespace Notation
		{		
			void ThrowParseError()
			{
				boost::throw_exception(SyntaxException("LLSD Notation ERROR"));
			}

			typedef Parser::iterator iterator;
			iterator SkipNumbers(iterator iter, iterator end)
			{
				if(iter != end && *iter == '-')
				{
					++iter;
				}
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
				if(iter == end || *iter != '(')
				{
					ThrowParseError();
				}

				iterator start = ++iter;
				iter = SkipNumbers(start, end);

				size_t len = boost::lexical_cast<size_t>(std::string(start, iter));

				if(iter == end || *iter != ')')
				{
					ThrowParseError();							
				}

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
						{
							return iter;
						}
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

			UInt8 ToHexNibble(char c)
			{
				if(c >= '0' && c <= '9')
				{
					return UInt8(c -= '0');
				}
				if(c >= 'a' && c <= 'f')
				{
					return UInt8(c -= 'f');
				}
				return 0;
			}

			iterator ParseString(iterator iter, iterator end, LLSDValue & val)
			{
				if(iter == end)
				{
					return end;
				}

				std::string strVal;
				iterator start = iter+1;
				char first = *iter;
				++iter;
				while(iter != end)
				{
					bool escape = (*iter == '\\');

					if(escape && ++iter == end)
					{
						ThrowParseError();
					}
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
									c = char(tolower(c));
									if(++iter == end)
									{
										ThrowParseError();
									}
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
				
				val = strVal;
				return iter;
			}

			iterator Parse(iterator iter, iterator end, LLSDValue & val);
			iterator ParseArray(iterator iter, iterator end, LLSDValue & val)
			{
				val.notation_decode(LLSDValue::VT_ARRAY,byte_sub_range());
				LLSDValue::Array & arr = val.array();
				iter = SkipWSC(iter+1, end);

				while(iter != end)
				{
					iter = SkipWSC(iter,end);
					
					if(iter == end)
					{
						ThrowParseError();
					}

					if(*iter == ']')
					{
						return ++iter;			
					}

					LLSDValue next;
					iter = Parse(iter, end, next);					

					if(next)
					{
						arr.push_back(next);
					}
				}
				return iter;
			}
			
			iterator ParseMap(iterator iter, iterator end, LLSDValue & val)
			{
				val.notation_decode(LLSDValue::VT_MAP,byte_sub_range());
				LLSDValue::Map & map = val.map();

				iter = SkipWSC(iter+1, end);

				while(iter != end)
				{
					iter = SkipWSC(iter,end);

					if(iter == end)
					{
						ThrowParseError();
					}

					if(*iter == '}')
					{
						return ++iter;			
					}
					
					LLSDValue first;
					iter = ParseString(iter, end, first);					
					
					iter = SkipWSC(iter, end, true);

					LLSDValue second;
					iter = Parse(iter, end, second);
					
					if(!first || !second)
					{
						ThrowParseError();
					}
					map[first.string()].swap(second);
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
				return lookup_table[UInt16(c)] == -1;
			}

			iterator Parse(iterator iter, iterator end, LLSDValue & val)
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
						val = LLSDValue();
						return ++iter;
					case 'r':
						// parse real
						{
							iterator start = ++iter;
							iter = SkipNumbers(iter, end);
							if(iter != end && *iter == '.')
							{
								iter = SkipNumbers(++iter, end);
							}
							val.notation_decode(LLSDValue::VT_REAL,start, iter);
							return iter;
						}
						break;
					case 'u':
						// parse uuid
						if((end - iter) >= 37) // we need at least 37 characters u + 36uuid
						{		
							val.notation_decode(LLSDValue::VT_UUID,iter+1, iter + 37);
							return iter + 37;
						}
						ThrowParseError();
						break;
					case 'i':
						//parse integer 
						{
							iterator start = ++iter;
							iter = SkipNumbers(start, end);
							if(iter != end)
							{
								val.notation_decode(LLSDValue::VT_INTEGER,start,iter);
							}
							else 
							{
								ThrowParseError();
							}
							return iter;
						}
						break;
					case '"':
					case '\'':
						{
							return iter = ParseString(iter, end, val);
						}
					case 's':
						//parse raw string
						{							
							size_t len = ParseSize(++iter, end);

							iter = ParseString(iter, end, val);
							
							if(!val || val.string().size() != len)
							{
								ThrowParseError();
							}
							return iter;
						}
						break;
					case 'b':
						//parse binary
						{
							++iter;
							if(iter == end)
							{
								ThrowParseError();
							}
							if(*iter == '(')
							{
								size_t len = ParseSize(iter, end);
								size_t diff = std::distance(iter,end);
								if(diff >= len)
								{
									if(*iter != '"')
									{
										ThrowParseError();
									}
									iterator bend = iter + len;
									iterator start = iter + 1;
									iter += len;
									if(*iter != '"')
									{
										ThrowParseError();
									}
									val.notation_decode(LLSDValue::VT_BINARY,start,bend-1);
									return ++iter;
								}
								ThrowParseError();
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
									val = base64_decode<LLSDValue::Binary>(buf);
								}
								else
								{
									val = LLSDValue::Binary(buf.begin(),buf.end());
								}
								return bend+1;
							}
							ThrowParseError();
						}
						break;
					case 'l':
						//parse uri
						{
							iter = ParseString(++iter, end, val);							
							if(!val)
							{
								ThrowParseError();
							}
							val = val.to_uri();
							return iter;
						}
						break;
					case 'd':
						//parse date
						{
							++iter;
							if(!(iter != end && *iter == '"'))
							{
								ThrowParseError();
							}
							iterator dend = std::find(++iter, end, '"');
							val.notation_decode(LLSDValue::VT_DATE,iter, dend);
							return dend+1;
						}
						break;
					case '0':
					case 'f':
					case 'F':
						// parse false
						{
							val = false;
							if(end - iter >= 5)
							{
								std::string fstr(iter,iter+5);
								boost::to_lower(fstr);
								if(fstr == "false")
								{
									iter += 5;
								}
								else 
								{
									++iter;
								}
							}
							return iter;							
						}
					case '1':
					case 'T':
					case 't':
						// parse true
						{
							val = true;
							if(end - iter >= 4)
							{
								std::string fstr(iter,iter+4);
								boost::to_lower(fstr);
								if(fstr == "true")
								{
									iter += 4;
								}
								else 
								{
									++iter;
								}
							}							
							return iter;							
						}
						break;
					default:
						ThrowParseError();
					}
					ThrowParseError();
				}
				return end;
			}

			LLSDValue Parser::Parse(iterator iter, iterator end)
			{
				LLSDValue val;
				Notation::Parse(SkipWSC(iter, end), end, val);
				return val;
			}
		}
	}	
}

#ifdef _MSC_VER
#	pragma warning(pop)
#endif
