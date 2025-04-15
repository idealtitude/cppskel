#ifndef STATUS_H
#define STATUS_H

#include <string>
#include <tuple>
#include <utility>

struct Status
{
 	Status();
	Status(const Status& other); // Copy constructor
	Status(Status&& other) noexcept;
	~Status() = default;

	// Attributes
	std::tuple<bool, std::string, std::string> _status;

	Status& operator=(const Status& other); // Copy assignment
	Status& operator=(Status&& other) noexcept; // Move assignment

	bool status_val() const;
	std::string status_type() const;
	std::string status_msg() const;

	// Methods
	void set_status(bool val_, const std::string& lvl_, const std::string& msg_);
};

#endif // STATUS_H
