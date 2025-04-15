#include "files.h"

namespace fs = std::filesystem;

File::File(const std::string& filepath, Mode mode)
    : file_status(), filepath(filepath), mode(mode)
{
    check_permissions();

    std::ios::openmode open_mode = (mode == Mode::READ) ? std::ios::in : std::ios::out;

    file.open(filepath, open_mode);

    if (!file.is_open())
	{
        file_status.set_status(true, "error", "failed to open file: " + filepath);
    }
	else
	{
        file_status.set_status(true, "success", "file opened successfully.");
    }
}

File::~File()
{
    if (file.is_open())
	{
        file.close();
    }
}

void File::check_permissions()
{
    if (!fs::exists(filepath) && !fs::is_regular_file(filepath))
	{
        if (mode == Mode::READ)
		{
            file_status.set_status(true, "error", "file does not exist -> " + filepath);
        }
    }
	else
	{
        fs::perms permissions = fs::status(filepath).permissions();
        bool readable = (permissions & fs::perms::owner_read) != fs::perms::none;
        bool writable = (permissions & fs::perms::owner_write) != fs::perms::none;

        if (mode == Mode::READ && !readable)
		{
            file_status.set_status(true, "error", "read permission denied: " + filepath);
        }
		else if (mode == Mode::WRITE && !writable)
		{
            file_status.set_status(true, "error", "write permission denied: " + filepath);
        }
    }
}

std::vector<std::string> File::read_file()
{
	std::vector<std::string> file_content;
	std::string line;
	while (std::getline(file, line))
	{
		file_content.push_back(line);
	}

	return file_content;
}

void File::write_file(const std::vector<std::string>& note_content)
{
	for (const auto& line: note_content)
	{
		file << line << '\n';
	}
}
