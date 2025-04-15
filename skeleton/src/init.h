#ifndef INIT_H
#define INIT_H

#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <regex>

#include "status.h"
#include "files.h"

namespace fs = std::filesystem;

using Umap = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

class Init
{
  public:
	Init() = delete;
	/**
	 * @brief this constructor take a path to the configuration file
	 *
	 * @param confp A string containing the path to the configuration file (std::string)
	 * @return an instance of Init
	 */
	Init(const std::string& confp, const std::string& prefsp);
	~Init() = default;

    // Attributes
    Status init_status;

    //Methods
    Umap return_config() const;
    Umap return_prefs() const;

  private:
    // Attributes
    //std::string config_path;
    Umap _config;
    Umap _prefs;

    //Methods
    //bool dir_exists(const std::string& dir_path);
    //void get_config();
    void parse_file(const std::string& file, int curmap);
};

#endif // INIT_H
