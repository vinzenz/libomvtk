#ifndef GUARD_LIBVW_SETTINGS_H_INCLUDED
#define GUARD_LIBVW_SETTINGS_H_INCLUDED

#include "utils/locked_property.h"
#include "types/base_types.h"

namespace vw
{
	struct GridClient;
	struct Settings
		: boost::noncopyable
	{		
		typedef boost::mutex Mutex;
		typedef LockedProperty<String> StringProp;
		typedef LockedProperty<UInt32> UInt32Prop;
		typedef LockedProperty<Int32>  Int32Prop;
		typedef LockedProperty<bool>   BoolProp;

	protected:

		GridClient & m_client;
		Mutex m_mutex;
	
	public:
		
		Settings(GridClient & gc);

	// Settings from here to the end 
		StringProp const login_uri;
		StringProp const agni_uri;
		StringProp const aditi_uri;
		StringProp const resource_directory;
		StringProp const cache_directory;
	};
}

#endif //GUARD_LIBVW_SETTINGS_H_INCLUDED

