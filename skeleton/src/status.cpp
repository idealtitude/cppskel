#include "status.h"

Status::Status() : _status(std::make_tuple(false, "", ""))
{}

Status::Status(const Status& other) : _status(other._status)
{}

Status::Status(Status&& other) noexcept : _status(std::move(other._status)) {}

Status& Status::operator=(const Status& other)
{
	if (this != &other)
	{
		_status = other._status;
	}
	return *this;
}

Status& Status::operator=(Status&& other) noexcept
{
	if (this != &other)
	{
		_status = std::move(other._status);
	}
	return *this;
}

bool Status::status_val() const
{
	return std::get<0>(_status);
}

std::string Status::status_type() const
{
	return std::get<1>(_status);
}

std::string Status::status_msg() const
{
	return std::get<2>(_status);
}

void Status::set_status(bool val_, const std::string& lvl_, const std::string& msg_)
{
	std::get<0>(_status) = val_;
	std::get<1>(_status) = lvl_;
	std::get<2>(_status) = msg_;
}
