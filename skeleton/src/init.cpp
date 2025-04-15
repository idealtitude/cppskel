#include "init.h"

Init::Init(const std::string& confp, const std::string& prefsp):
    _config(), _prefs()
{
    parse_file(confp, 0);
	parse_file(prefsp, 1);
}

Umap Init::return_config() const
{
    return _config;
}

Umap Init::return_prefs() const
{
    return _prefs;
}

void Init::parse_file(const std::string& file, int curmap)
{
	std::regex section_ptn{R"(^\[([a-z0-9_]+)\]$)"};
	std::regex keyval_ptn{R"(^([a-z0-9_]+) ?= ?\"([^"]+)\"$)"};
	std::smatch _m;
	std::string current_section;
	Umap& current_map = (curmap == 0) ? _config : _prefs;

	File current_file(file, File::Mode::READ);

	std::vector<std::string> current_file_content = current_file.read_file();

	if (current_file.file_status.status_type() != "error")
	{
       for (const std::string& line: current_file_content)
		{
			if (line.starts_with("#"))
			{
				// Skipping comments
				continue;
			}

			if (std::regex_search(line, _m, section_ptn))
			{
				current_section = _m[1];
				current_map[current_section] = {};
				continue;
			}

			if (std::regex_search(line, _m, keyval_ptn))
            {
                if (_m.size() < 3) // ignore ill formated lines
                {
					std::string errmsg = "unknown or ill formatted key/value pair: " + line;
					init_status.set_status(true, "warning", errmsg);
                    continue;
                }

                std::string key = _m[1];
				std::string val = _m[2];
				current_map[current_section][key] = val;
            }
		}
	}
	else
	{
		// TODO: use copy constructor?
		init_status.set_status(true, current_file.file_status.status_type(), current_file.file_status.status_msg());
	}
}
