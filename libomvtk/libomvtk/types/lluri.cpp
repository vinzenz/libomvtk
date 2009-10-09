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
#include "lluri.h"

namespace omvtk
{
	LLURI::LLURI()
	{
	}

	LLURI::LLURI(LLURI const & o)
		: m_data(o.m_data)
	{
	}

	LLURI::LLURI(byte_sub_range const & sr)
		: m_data(String(sr.begin(), sr.end()))
	{
	}

	LLURI::LLURI(String const & str)
		: m_data(str)
	{
	}

	LLURI::~LLURI()
	{
	}

	LLURI & LLURI::operator=(LLURI o)
	{
		swap(o);
		return *this;
	}


	bool LLURI::operator==(LLURI const & o) const
	{
		return m_data == o.m_data;
	}

	bool LLURI::operator!=(LLURI const & o) const
	{
		return m_data != o.m_data;
	}

	bool LLURI::operator==(String const & s) const
	{
		return m_data == s;
	}

	bool LLURI::operator!=(String const & s) const
	{
		return m_data != s;
	}
	
	void LLURI::swap(LLURI & o)
	{
		m_data.swap(o.m_data);
	}

	String LLURI::to_string() const
	{
		// return m_data.toString();
        return m_data;
	}

	ByteBuffer LLURI::to_binary() const
	{
		std::string tmp = to_string();
		return ByteBuffer(tmp.begin(), tmp.end());
	}


	LLURI::value_type const & LLURI::get() const
	{
		return m_data;
	}

	LLURI::value_type & LLURI::get()
	{
		return m_data;
	}

}

