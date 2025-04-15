#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <tuple>

struct Logging
{
 	Logging();
 	Logging(const std::tuple<bool, std::string, std::string>& log);
	~Logging() = default;

	// Attributes
	std::tuple<bool, std::string, std::string> _log;

	// Methods
	bool get_status() const;
	std::string fmt_status() const;
	friend std::ostream &operator<<(std::ostream& outstrm, const Logging& output);
};

#endif // LOGGING_H
