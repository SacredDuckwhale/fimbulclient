/*	This file is part of YA3DE.

	YA3DE is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	YA3DE is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with YA3DE.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef YA3DE_CONTENTMANAGER_H
#define YA3DE_CONTENTMANAGER_H

#include <mutex>
#include <unordered_map>

#include <YA3DE/Content/Resource.h>
#include <YA3DE/Content/Dispatcher.h>
#include <YA3DE/Content/ContentName.h>

namespace YADE
{
	class ContentManager
	{
	public:
		ContentManager()
		{
			if (_Instance != nullptr)
				throw std::exception("YA3DE::Content::ContentManager must have only one instance.");

			_Instance = this;
		}

		template<class T>
		std::shared_ptr<T> Load(const std::string &name, bool async = false)
		{
			//async = false;

			_Guard.lock();
			CacheMap::iterator it = _Cache.find(name);
			_Guard.unlock();

			if (it != _Cache.end())
			{
				if (!it->second.expired())
				{
					return std::static_pointer_cast<T, Resource>(it->second.lock());
				}
				else
				{
					_Guard.lock();
					_Cache.erase(it);
					_Guard.unlock();
				}
			}

			return LoadNew<T>(name, async);
		}
			
		template<class T>
		void CacheObject(const std::string &name, const std::shared_ptr<T> &ptr)
		{
			_Guard.lock();
			_Cache[name] = std::weak_ptr<Resource>(ptr);
			_Guard.unlock();
		}

		template<class T>
		std::shared_ptr<T> LoadNew(const std::string &name, bool async);

		static ContentManager *Instance()
		{
			if (_Instance == nullptr)
				new ContentManager();

			return _Instance;
		}

		DEFPROP_P_RO_NR(public, FunctionDispatcher, Dispatcher);

	private:
		static ContentManager *_Instance;
		typedef ContentHashTable<std::weak_ptr<Resource> > CacheMap;

		CacheMap _Cache;
		std::recursive_mutex _Guard;
	};
}

#define CONTENT_LOADER(type) \
namespace YADE { template<> std::shared_ptr<type> ContentManager::LoadNew(const std::string &name, bool async); } \
template<> std::shared_ptr<type> YADE::ContentManager::LoadNew(const std::string &name, bool async)

#endif
