#include "stdafx.h"
#include "binary.h"
#include "llsd.h"
#include "../lltypes/byte_order_helper.h"
#include "../throw.h"

namespace LLSD
{
	namespace detail
	{
		namespace Binary
		{
			typedef Parser::iterator iterator;

			template<typename ValT>
			inline ValT MakeVal(iterator iter)
			{
				return detail::to_host(*reinterpret_cast<ValT const*>(&*iter));
			}

			template<typename Ret, typename Cont, typename Val>
			inline Ret MakePtr(iterator iter)
			{				
				return Ret(new Cont(MakeVal<Val>(iter)));
			}

			template<typename Ret>
			inline Ret ParseSizedVal(iterator & iter, iterator end)
			{
				if(end - iter < 4)
					LIBVW_THROWS(LLSDBinaryParseError);
				boost::uint32_t len = MakeVal<boost::uint32_t>(iter);
				iter += 4;
				if(end - iter < len)
					LIBVW_THROWS(LLSDBinaryParseError);
				iterator start = iter;
				iter += len;
				return Ret(start, iter);
			}

			template<typename Ret, typename Cont, typename Val>
			inline Ret ParseSized(iterator & iter, iterator end)
			{
				return Ret(new Cont(ParseSizedVal<Val>(iter, end)));
			}

			inline iterator Parse(iterator iter, iterator end, ValuePtr & val)
			{
				if(iter == end)
					return end;

				switch(*iter)
				{
				case '0':
				case '1':
					val = BooleanPtr(new Boolean(*iter == '1'));
					return ++iter;
				case 'i':
					if(end - iter < 5)
						break;
					val = MakePtr<IntegerPtr,Integer,boost::uint32_t>(iter+1);
					return iter + 5;
				case 'r':		
					if(end - iter < 9)
						break;
					val = MakePtr<RealPtr,Real,double>(iter+1);
					return iter + 9;
				case 's':
					{						
						val = ParseSized<StringPtr, String, std::string>(++iter,end);
						return iter;
					}
				case 'b':
					{						
						val = ParseSized<BinaryPtr, LLSD::Binary, std::vector<boost::uint8_t> >(++iter,end);
						return iter;
					}
					return ++iter;
				case 'u':
					if(end - iter < 17)
						LIBVW_THROWS(LLSDBinaryParseError);
					val = UUIDPtr(new UUID(std::vector<boost::uint8_t>(iter+1,iter+17)));
					return iter + 17;
				case 'd':
					if(end - iter < 9)
						LIBVW_THROWS(LLSDBinaryParseError);
					val = DatePtr(new Date(boost::uint32_t(MakeVal<double>(iter+1))));
					return iter + 9;
				case 'l':
					{						
						val = ParseSized<UriPtr, Uri, std::string>(++iter,end);
						return iter;
					}
				case '[':
					{
						if(end - iter < 6)
							LIBVW_THROWS(LLSDBinaryParseError);
						boost::uint32_t len = MakeVal<boost::uint32_t>(++iter);
						iter += 4;
						ArrayPtr arr = Value().ToArray();
						for(boost::uint32_t i = 0; i < len; ++i)
						{
							if(iter == end)
								LIBVW_THROWS(LLSDBinaryParseError);
							ValuePtr elem;								
							iter = Parse(iter, end, elem);							
							if(!elem)
								LIBVW_THROWS(LLSDBinaryParseError);
							arr->push_back(elem);
						}
						if(iter == end || *iter != ']')
							LIBVW_THROWS(LLSDBinaryParseError);
						val = arr;
						return ++iter;
					}
					return ++iter;
				case '{':
					{
						if(end - iter < 6)
							LIBVW_THROWS(LLSDBinaryParseError);
						boost::uint32_t len = MakeVal<boost::uint32_t>(++iter);
						iter += 4;
						MapPtr map = Value().ToMap();
						for(boost::uint32_t i = 0; i < len; ++i)
						{
							if(iter == end)
								LIBVW_THROWS(LLSDBinaryParseError);
							std::string k = ParseSizedVal<std::string>(iter, end);														
							if(iter == end)
								LIBVW_THROWS(LLSDBinaryParseError);
							ValuePtr elem;								
							iter = Parse(iter, end, elem);							
							if(!elem)
								LIBVW_THROWS(LLSDBinaryParseError);
							map->insert(k, elem);
						}
						if(iter == end || *iter != '}')
							LIBVW_THROWS(LLSDBinaryParseError);
						val = map;
						return ++iter;
					}
					return ++iter;
				case '!':
					val = ValuePtr(new Value());
					return ++iter;
				default:
					break;
				}

				LIBVW_THROWS(LLSDBinaryParseError);
				// Fake. To silence the compilers but it will never be returned
				return iter; 
			}

			ValuePtr Parser::Parse(iterator iter, iterator end)
			{
				ValuePtr ptr;
				if(detail::Binary::Parse(iter, end, ptr) != end || !ptr)
					LIBVW_THROWS(LLSDBinaryParseError);
				return ptr;
			}

			template<typename T>
			inline void BuildType(T val, std::vector<boost::uint8_t> & buf)
			{
				val = detail::to_network(val);
				boost::uint8_t const * pV = reinterpret_cast<boost::uint8_t const*>(&val);
				std::copy(pV,pV+sizeof(T),std::back_inserter(buf));
			}

			template<typename SizeType>
			inline void BuildSize(SizeType size, std::vector<boost::uint8_t> & buf)
			{
				boost::uint32_t len = boost::uint32_t(size);
				BuildType(len,buf);
			}

			template<typename ValueType>
			inline void BuildSizedValue(ValueType & val, std::vector<boost::uint8_t> & buf)
			{
				BuildSize(val.size(), buf);
				std::copy(val.begin(),val.end(),std::back_inserter(buf));
			}

			inline void Build(LLSD::ValuePtr data, std::vector<boost::uint8_t> & buf)
			{
				if(!data)
					LIBVW_THROWS(LLSDBinaryBuildError);
				switch(data->GetType())
				{
				case VTID_INTEGER:
					{
						buf.push_back(boost::uint8_t('i'));
						IntegerPtr val = Value::AsInteger(data);
						BuildType(val->GetValue(), buf);
					}
					break;
				case VTID_REAL:
					{
						buf.push_back(boost::uint8_t('r'));
						RealPtr val = Value::AsReal(data);
						BuildType(val->GetValue(), buf);
					}
					break;
				case VTID_STRING:
					{
						buf.push_back(boost::uint8_t('s'));
						StringPtr val = Value::AsString(data);
						BuildSizedValue(val->GetValue(), buf);
					}
					break;
				case VTID_DATE:
					{
						buf.push_back(boost::uint8_t('d'));
						DatePtr date = Value::AsDate(data);
						BuildType(double(date->GetSeconds()), buf);
					}
					break;
				case VTID_UUID:
					{
						buf.push_back(boost::uint8_t('u'));
						UUIDPtr val = Value::AsUUID(data);
						size_t idx = buf.size();
						buf.insert(buf.end(), 16, 0);
						val->GetValue().copyTo(reinterpret_cast<char*>(&buf[idx]));
					}
					break;
				case VTID_BOOLEAN:
					{
						BooleanPtr b = Value::AsBoolean(data);
						buf.push_back(boost::uint8_t('0' + b->GetValue()));
					}
					break;
				case VTID_BINARY:
					{
						buf.push_back(boost::uint8_t('b'));
						BinaryPtr bin = Value::AsBinary(data);
						BuildSizedValue(bin->GetValue(), buf);
					}
					break;
				case VTID_URI:
					{
						UriPtr uri = Value::AsUri(data);
						buf.push_back(boost::uint8_t('l'));
						BuildSizedValue(uri->GetValue().toString(), buf);
					}
					break;
				case VTID_MAP:
					{
						MapPtr map = Value::AsMap(data);
						buf.push_back(boost::uint8_t('{'));
						BuildSize(map->size(), buf);
						for(Map::const_iterator it = map->begin(); it != map->end(); ++it)
						{
							BuildSizedValue(it->first, buf);
							Build(it->second, buf);	
						}
						buf.push_back(boost::uint8_t('}'));
					}
					break;
				case VTID_ARRAY:
					{
						ArrayPtr arr = Value::AsArray(data);
						buf.push_back(boost::uint8_t('['));
						BuildSize(arr->size(), buf);
						for(Array::const_iterator it = arr->begin(); it != arr->end(); ++it)
						{
							Build(*it, buf);	
						}
						buf.push_back(boost::uint8_t(']'));
					}
					break;
				case VTID_UNDEFINED:
					buf.push_back(boost::uint8_t('!'));
					break;
				default:
					LIBVW_THROWS(LLSDBinaryBuildError);
					break;
				}
			}

			std::vector<boost::uint8_t> Build(LLSD::ValuePtr data)
			{
				std::vector<boost::uint8_t> buf;
				Build(data, buf);
				return buf;
			}
		}
	}
}