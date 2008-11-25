//
// DOMImplementation.cpp
//
// $Id: //poco/1.3/XML/src/DOMImplementation.cpp#1 $
//
// Library: XML
// Package: DOM
// Module:  DOM
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/DOM/DOMImplementation.h"
#include "Poco/DOM/DocumentType.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/String.h"
#include "Poco/SingletonHolder.h"


namespace Poco {
namespace XML {


const XMLString DOMImplementation::FEATURE_XML            = toXMLString("xml");
const XMLString DOMImplementation::FEATURE_CORE           = toXMLString("core");
const XMLString DOMImplementation::FEATURE_EVENTS         = toXMLString("events");
const XMLString DOMImplementation::FEATURE_MUTATIONEVENTS = toXMLString("mutationevents");
const XMLString DOMImplementation::FEATURE_TRAVERSAL      = toXMLString("traversal");
const XMLString DOMImplementation::VERSION_1_0            = toXMLString("1.0");
const XMLString DOMImplementation::VERSION_2_0            = toXMLString("2.0");


DOMImplementation::DOMImplementation()
{
}


DOMImplementation::~DOMImplementation()
{
}


bool DOMImplementation::hasFeature(const XMLString& feature, const XMLString& version) const
{
	XMLString lcFeature = Poco::toLower(feature);
	return lcFeature == FEATURE_XML && version == VERSION_1_0 ||
	       lcFeature == FEATURE_CORE && version == VERSION_2_0 ||
	       lcFeature == FEATURE_EVENTS && version == VERSION_2_0 ||
	       lcFeature == FEATURE_MUTATIONEVENTS && version == VERSION_2_0 ||
	       lcFeature == FEATURE_TRAVERSAL && version == VERSION_2_0;
}

		
DocumentType* DOMImplementation::createDocumentType(const XMLString& name, const XMLString& publicId, const XMLString& systemId) const
{
	return new DocumentType(0, name, publicId, systemId);
}


Document* DOMImplementation::createDocument(const XMLString& namespaceURI, const XMLString& qualifiedName, DocumentType* doctype) const
{
	Document* pDoc = new Document(doctype);
	if (namespaceURI.empty())
		pDoc->appendChild(pDoc->createElement(qualifiedName))->release();
	else
		pDoc->appendChild(pDoc->createElementNS(namespaceURI, qualifiedName))->release();
	return pDoc;
}


const DOMImplementation& DOMImplementation::instance()
{
	static Poco::SingletonHolder<DOMImplementation> sh;
	return *sh.get();
}


} } // namespace Poco::XML
