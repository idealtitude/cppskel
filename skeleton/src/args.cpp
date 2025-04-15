#include "args.h"
#include <bitset>

// Constructor implementation
Args::Args(std::vector<std::string>&& args_):
	args_status(), action("none"), args_input(args_)
{
	//arguments = std::make_unique<std::unordered_map<std::string, std::string>>();
	parse_args();
}

// initialize_map implementaion
void Args::initialize_map()
{
	if (!arguments)
	{
		arguments = std::make_unique<std::unordered_map<std::string, std::string>>();
	}
}

// build_map implementation
void Args::add_args(const std::string& key, const std::string& value)
{
	auto& args_map = *arguments;
	args_map.insert(std::pair<std::string, std::string>(key, value));
}

// TODO : better handling of arguments, check for unknown arguments, for missing values for flags, etc.
// parse_args implementation; adjust to what is needed
void Args::parse_args()
{
	std::bitset<4> valid_args; // Adjust to the number of arguments to check!

	bool map_initialized{false};
	bool skip_arg{false};
	std::size_t args_counter{0};

	for (const auto& arg: args_input) // Unrolling `argv`
	{
		// Action help
		if (arg == "-h" ||  arg == "--help")
		{
			valid_args[0] = true;
			action = "help";
			break;
		}

		// Action version
		if (arg == "-v" ||  arg == "--version")
		{
			valid_args[0] = true;
			action = "version";
			break;
		}

		// Positional argument
		if (args_counter == 0)
		{
			valid_args[0] = true;
			action = "app";
			initialize_map();
			map_initialized = true;
			add_args("app", arg);
			args_counter++;
		}

		// Skipping arg previously handled
		if (skip_arg)
		{
			skip_arg = false;
			args_counter++;
			continue;
		}

		// Argument example: option + value
		if (arg == "-i" ||  arg == "--input")
		{
			if (args_counter + 1 < args_input.size())
			{
				if (!map_initialized)
				{
					initialize_map();
					map_initialized = true;
				}

				add_args("input", args_input.at(args_counter + 1));
				//action = (action != "none") ? action + ":input" : "input"; // String will be parse to get actions
				valid_args[1] = true;
				args_counter++;
				skip_arg = true;
				continue;
			}
			else
			{
				args_status.set_status(true, "error", "missing value for option " + arg);
			}
		}
	}

	// Final arguments parsing check
	if (!valid_args.any())
	{
		args_status.set_status(true, "error", "command line arguments is ill formed, could not parse it");
		action = "none"; // Parse failed, or unknown argument(s) found
	}
}
