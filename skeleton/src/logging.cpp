#include <iostream>

#include "logging.h"

Logging::Logging()
{
	_log = std::make_tuple(true, "", "");
}

Logging::Logging(const std::tuple<bool, std::string, std::string>& log)
{
	_log = log;
}

bool Logging::get_status() const
{
	if (std::get<0>(_log))
	{
		return true;
	}

	return false;
}

std::string Logging::fmt_status() const
{
	std::string lvl_ = std::get<1>(_log);
	std::string msg_ = std::get<2>(_log);

	std::string msg;

	if (lvl_ == "error")
	{
		msg = "\x1b[91mError:\x1b[0m " + msg_;
	}
	else if (lvl_ == "success")
	{
		msg = "\x1b[92mSuccess:\x1b[0m " + msg_;
	}
	else if (lvl_ == "warning")
	{
		msg = "\x1b[93mWarning:\x1b[0m " + msg_;
	}
	else if (lvl_ == "info")
	{
		msg = "\x1b[94mInfo:\x1b[0m " + msg_;
	}
	else
	{
		msg = "\x1b[1mStatus:\x1b[0m everythin seems fine...";
	}

	return msg;
}

std::ostream &operator<<(std::ostream& outstrm, const Logging& output)
{
	outstrm << output.fmt_status();
	return outstrm;
}
