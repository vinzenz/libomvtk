#ifndef GUARD_LIBVW_UTILS_LOCKED_PROPERTY_H_INCLUDED
#define GUARD_LIBVW_UTILS_LOCKED_PROPERTY_H_INCLUDED

#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

namespace vw
{
	template<typename ValueType>
	struct LockedProperty : boost::noncopyable
	{
		typedef boost::mutex Mutex;
		typedef boost::mutex::scoped_lock Lock;

		LockedProperty(Mutex & mutex, ValueType default_value)
		: boost::noncopyable()
		, m_value(default_value)
		, m_mutex(mutex)
		{}

		~LockedProperty()
		{}

		ValueType operator()() const
		{
			Lock lock(m_mutex);
			ValueType value = m_value;
			return value;
		}

		void operator()(ValueType const & value)
		{
			Lock lock(m_mutex);
			m_value = value;
		}	

		operator ValueType () const
		{
			Lock lock(m_mutex);
			ValueType value = m_value;
			return value;
		}

		void operator=(ValueType const & value)
		{
			Lock lock(m_mutex);
			m_value = value;
		}
	protected:
		ValueType m_value;
		Mutex & m_mutex;
	};
}

#endif //GUARD_LIBVW_UTILS_LOCKED_PROPERTY_H_INCLUDED

