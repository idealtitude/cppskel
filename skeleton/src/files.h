#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <fstream>
#include <filesystem>
#include <vector>
#include "status.h"

class File
{
  public:
	// TODO: add `append` mode
    enum class Mode { READ, WRITE };

	File() = delete;
    File(const std::string& filepath, Mode mode);
    ~File();

	Status file_status;

	std::vector<std::string> read_file();
	void write_file(const std::vector<std::string>& note_content);

  private:
    std::string filepath;
    Mode mode;
    std::fstream file;

    void check_permissions();
};

#endif // FILE_HANDLER_H
