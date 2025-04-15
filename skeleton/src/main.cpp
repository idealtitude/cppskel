#include <iostream>
#include <string>
//#include <utility>
#include <tuple>
#include <filesystem>
#include <cstdlib>

#include "args.h"
#include "logging.h"
#include "files.h"
#include "init.h"

const std::string APP_NAME = "{{app}}";

#ifndef INSTALLING
const bool APP_LOCAL = true;
const std::string APP_VERSION = "VERSION";
const std::string APP_HELP = "data/help.txt";
const std::string APP_CONF = "data/" + APP_NAME + ".conf";
const std::string APP_PREFS = "data/preferences.conf";
#else
const bool APP_LOCAL = false;
const std::string APP_VERSION = ".local/share/" + APP_NAME + "/version.txt";
const std::string APP_HELP = ".local/share/" + APP_NAME + "/help.txt";
const std::string APP_CONF = ".local/share/" + APP_NAME + "/" + APP_NAME + ".conf";
const std::string APP_PREFS = ".config/" + APP_NAME + "/preferences.conf";
#endif

std::string define_path(const std::string& relative_path)
{
	static const char* home_dir = std::getenv("HOME");
	//static const char* prefix_dir = std::getenv("PREFIX");
	//static const std::filesystem::path local_path = std::filesystem::current_path();

	if (APP_LOCAL)
	{
		//std::string path = std::string(local_path) + "/" + relative_path;
		return std::string(std::filesystem::absolute(relative_path));
	}

	return std::string(home_dir) + "/" + relative_path;
}

void print_help()
{
	File help_file(define_path(APP_HELP), File::Mode::READ);

	bool file_status = help_file.file_status.status_val();
	std::string status_type = help_file.file_status.status_type();

	if (file_status)
	{
		Logging file_log(help_file.file_status._status);

		if (status_type == "error" || status_type == "warning")
		{
			std::cerr << file_log << '\n';
		}
	}

	for (const auto& line: help_file.read_file())
	{
		std::cout << line << '\n';
	}
}

void print_version()
{
   File version_file(define_path(APP_VERSION), File::Mode::READ);

   bool file_status = version_file.file_status.status_val();
   std::string status_type = version_file.file_status.status_type();

   if (file_status)
   {
	   Logging file_log(version_file.file_status._status);

	   if (status_type == "error" || status_type == "warning")
	   {
		   std::cerr << file_log << '\n';
	   }
   }

   for (const auto& line: version_file.read_file())
   {
	   std::cout << line << '\n';
   }
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
        print_help();
		return 0;
	}

	Args args(std::vector<std::string>(argv + 1, argv + argc));

	bool args_status = args.args_status.status_val();

	if (args_status)
	{
		Logging args_log(args.args_status._status);
		std::cout << args_log << '\n';
	}

	if (args.action == "help")
	{
		print_help();
		return 0;
	}

	if (args.action == "version")
	{
		print_version();
		return 0;
	}

	if (args.action == "none")
	{
		std::cerr << "Couldn't parse the arguments... Exiting now.\n";
		return 1;
	}

	auto& args_map = *args.arguments;
	std::cout << "Arguments:\n";
	for (const auto& [key, value]: args_map)
	{
		std::cout << "key: " << key << "\nvalue: " << value << "\n\n";
	}

	Init init(define_path(APP_CONF), define_path(APP_PREFS));

	if (init.init_status.status_val())
	{
		Logging init_log(init.init_status._status);
		std::cout << init_log << '\n';

		if (init.init_status.status_type() == "error")
		{
			return 1;
		}
	}

	std::cout << "Config:\n";
	for (const auto& section: init.return_config())
	{
		std::cout << "section: " << section.first << '\n';
		for (const auto& [k, v]: section.second)
		{
			std::cout << "k: " << k << ", v: " << v << '\n';
		}
	}

	std::cout << "\nPrefs:\n";
	for (const auto& section: init.return_prefs())
	{
		std::cout << "section: " << section.first << '\n';
		for (const auto& [k, v]: section.second)
		{
			std::cout << "k: " << k << ", v: " << v << '\n';
		}
	}

	if (init.init_status.status_val())
	{
		Logging init_log(init.init_status._status);
		std::cout << init_log << '\n';

		if (init.init_status.status_type() == "error")
		{
			return 1;
		}
	}

	std::cout << "Done\n";

    return 0;
}
