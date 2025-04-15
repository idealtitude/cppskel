#ifndef ARGS_H
#define ARGS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "status.h"

class Args
{
  public:
	Args() = delete;
	Args(std::vector<std::string>&& args_);
	~Args() = default;

    // Attributes
	Status args_status;
    std::string action;
    std::unique_ptr<std::unordered_map<std::string, std::string>> arguments;

    //Methods

  private:
    // Attributes
    std::vector<std::string> args_input;

    //Methods
	void initialize_map();
	void add_args(const std::string& key, const std::string& value);
    void parse_args();
};

#endif // ARGS_H
