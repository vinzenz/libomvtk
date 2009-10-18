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
#ifdef _MSC_VER
#    pragma warning(push)
#    pragma warning(disable: 4702)
#    pragma warning(disable: 4512)
#endif

#include "xml.h"
#include <boost/format.hpp>
#include <iomanip>
#include <boost/math/special_functions/fpclassify.hpp>

#define TIXML_USE_TICPP
#include "../../3rdparty/tinyxml/ticpp.h"
#include "../types/exceptions.h"
#include "../types/assert.h"
#include "traits.h"
#include "value.h"

namespace omvtk
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

            std::map<std::string, LLSDValue::Types> Parser::LookupTable;
            void Parser::InitLookupTable()
            {
                LookupTable["string"]    = LLSDValue::VT_STRING;
                LookupTable["integer"]    = LLSDValue::VT_INTEGER;
                LookupTable["boolean"]    = LLSDValue::VT_BOOLEAN;
                LookupTable["binary"]    = LLSDValue::VT_BINARY;
                LookupTable["date"]        = LLSDValue::VT_DATE;
                LookupTable["uuid"]        = LLSDValue::VT_UUID;
                LookupTable["uri"]        = LLSDValue::VT_URI;
                LookupTable["real"]        = LLSDValue::VT_REAL;
                LookupTable["undef"]    = LLSDValue::VT_UNDEF;
                LookupTable["map"]        = LLSDValue::VT_MAP;        
                LookupTable["array"]    = LLSDValue::VT_ARRAY;
            }

            struct CommentNotification{};
            LLSDValue Parser::ParseArray(ticpp::Node * node)
            {
                LLSDValue arr = LLSDValue::Array();
                ticpp::Iterator<ticpp::Node> elems;
                for(elems = elems.begin(node); elems != elems.end(); ++elems)                    
                {
                    LLSDValue val;
                    while(!(val = Parse(elems.Get(), true)) && ++elems != elems.end())
                    {}                    
                    if(val)
                    {
                        arr.array().push_back(val);
                    }
                }
                return arr; 
            }

            LLSDValue Parser::ParseMap(ticpp::Node * node)
            {
                LLSDValue map = LLSDValue::Map();
                ticpp::Iterator<ticpp::Node> elems;
                for(elems = elems.begin(node); elems != elems.end(); ++elems)
                {        
                    ticpp::Node * p = elems->FirstChild();

                    if(!p)
                    {
                        boost::throw_exception(SyntaxException("LLSD XML ERROR"));
                    }
                    std::string key = p->Value();

                    ++elems;

                    if(elems == elems.end())
                    {
                        boost::throw_exception(SyntaxException("LLSD XML ERROR"));
                    }

                    LLSDValue val;
                    while(!(val = Parse(elems.Get(), true)) && ++elems != elems.end())
                    {}
                    
                    if(map)
                    {
                        map.map()[key] = val;
                    }
                }
                return map;
            }

            LLSDValue Parser::Parse(ticpp::Node * node, bool returnEmpty)
            {
                if(!node)
                {
                    boost::throw_exception(SyntaxException("LLSD XML ERROR"));
                }

                if(node->Type() != TiXmlNode::ELEMENT || node->Type() == TiXmlNode::TEXT)
                {
                    if(returnEmpty)
                    {
                        return LLSDValue();
                    }
                    return Parse(node->NextSibling());
                }

                std::string nodeN = node->Value();
                if(LookupTable.count(nodeN) > 0)
                {
                    LLSDValue result;
                    ticpp::Node * tmp = node->FirstChild(false);
                    switch(LookupTable[nodeN])
                    {                            
                    case LLSDValue::VT_INTEGER:
                        if(tmp && tmp->Type() == TiXmlNode::TEXT)
                        {                            
                            result.xml_decode(LLSDValue::VT_INTEGER, tmp->Value());
                        }
                        else
                        {
                            result = Int32(0);
                        }
                        return result;
                    case LLSDValue::VT_REAL:
                        if(tmp && tmp->Type() == TiXmlNode::TEXT)
                        {
                            result.xml_decode(LLSDValue::VT_REAL, tmp->Value());
                        }
                        else
                        {
                            result = Real64(0);
                        }
                        return result;
                    case LLSDValue::VT_STRING:
                        if(tmp && tmp->Type() == TiXmlNode::TEXT)
                        {
                            result.xml_decode(LLSDValue::VT_STRING, tmp->Value());
                        }
                        else
                        {
                            result = "";
                        }
                        return result;
                    case LLSDValue::VT_DATE:
                        if(tmp && tmp->Type() == TiXmlNode::TEXT)
                        {
                            result.xml_decode(LLSDValue::VT_DATE, tmp->Value());
                        }
                        else
                        {
                            result = LLDate();
                        }
                        return result;
                    case LLSDValue::VT_UUID:
                        if(tmp && tmp->Type() == TiXmlNode::TEXT)
                        {
                            result.xml_decode(LLSDValue::VT_UUID, tmp->Value());
                        }
                        else
                        {
                            result = LLUUID::Zero;
                        }
                        return result;
                    case LLSDValue::VT_BOOLEAN:
                        if(tmp && tmp->Type() == TiXmlNode::TEXT)
                        {
                            result.xml_decode(LLSDValue::VT_BOOLEAN, tmp->Value());
                        }
                        else
                        {
                            result = false;
                        }
                        return result;
                    case LLSDValue::VT_BINARY:
                        if(tmp && tmp->Type() == TiXmlNode::TEXT)
                        {
                            result = base64_decode<LLSDValue::Binary>(tmp->Value());
                        }
                        else
                        {
                            result = LLSDValue::Binary();
                        }
                        return result;
                    case LLSDValue::VT_URI:
                        if(tmp && tmp->Type() == TiXmlNode::TEXT)
                        {
                            result = LLURI(tmp->Value());
                        }
                        else
                        {
                            result = LLURI();
                        }
                        return result;
                    case LLSDValue::VT_MAP:
                        return ParseMap(node);
                    case LLSDValue::VT_ARRAY:
                        return ParseArray(node);
                    case LLSDValue::VT_UNDEF:
                    default:
                        return result;
                    }
                }

                ticpp::Iterator<ticpp::Node> elems;
                for(elems = elems.begin(node); elems != elems.end(); ++elems)
                {        
                    return Parse(elems.Get());
                }

                return LLSDValue();
            }

            LLSDValue Parser::Parse(iterator it, iterator end)
            {
                Parser parser;
                try
                {
                    ticpp::Document doc;
                    doc.Parse(std::string(it, end), true, TIXML_ENCODING_UTF8);
                    return parser.Parse(doc.FirstChildElement());
                }
                catch(...)
                {
                }    
                return LLSDValue();
            }
        }
    }
}

#ifdef _MSC_VER
#    pragma warning(pop)
#endif
