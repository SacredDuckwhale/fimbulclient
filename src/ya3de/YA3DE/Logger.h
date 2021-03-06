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

#ifndef YA3DE_LOGGER_H
#define YA3DE_LOGGER_H

#include <mutex>
#include <string>
#include <fstream>

#define LOG(format, ...) YADE::Logger::Instance()->Log(format, __VA_ARGS__);

namespace YADE
{
	class Logger
	{
	public:
		Logger();
		~Logger();

		void Log(const char *format, ...);
		void Log(const std::string &s);

		static Logger *Instance()
		{
			if (_Instance == nullptr)
				new Logger();

			return _Instance;
		}
	private:
		static Logger *_Instance;

		void Open();

		bool _UseStdout;
		std::string _Filename;
		std::fstream _File;
		std::mutex _Mutex;
	};
}

#endif
