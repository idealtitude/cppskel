#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
@brief This utility copy a C++ skeleton folder and set it up with the name you choose.

@description This Python script that comes with this repository, does a copy of the C++ `skeleton` folder, 
and also does template string replacements in several of the files of the newly created project folder.

@notice
* the script requires a name for the copy of the project folder, passed as a command line argument,
  this name is going to be used to rename some files and in the template string substitutions, so
  choose the name with this in mind; also note that if the name contains non ASCII characters or spaces,
  they're going to be removed in the case of non ASCII characters, aor replaced by an underscore in the 
  case of spaces
* the new roject folder is copied in your current working directory!
"""

import sys
import os
import shutil
import string
import subprocess

from typing import Any
import argparse


# App version
__app_name__	 : str = "skeleton_setup"
__app_version__	  : str = "0.1.0"


# Constants
EXIT_SUCCESS: int = 0
EXIT_FAILURE: int = 1
APP_PATH   : str = os.path.dirname(os.path.realpath(__file__))
APP_CWD	: str = os.getcwd()
APP_SKELETON :str = os.path.join(APP_PATH, "skeleton")


# Command line arguments
def get_args() -> Any:
	"""Parsing command line arguments"""
	parser: Any = argparse.ArgumentParser(
		prog=f"{__app_name__}", description="skeleton_setup sets up the file and variables in the C++ skeleton folder", epilog="Documentation is in doc/documentation.md"
	)

	parser.add_argument("name", nargs=1, help="Project name")
	parser.add_argument(
		"-v", "--version", action="version", version=f"%(prog)s {__app_version__}"
	)

	return parser.parse_args()

# Check file exists
def file_exists(file_path: str) -> bool:
	"""
	@brief A simple routine to check if any given file exists, notifies the user in case the file is not found
	
	@param file_path  {string} the file to check
	@return           {bool}   True on succes, False on error
	"""
	if os.path.exists(file_path):
		return True
	print(f"033[31mError:\033[0m File not found, skipping: {file_path}")
	return False


def setup_files(files: list[str], project_name: str) -> None:
	"""
	@brief This function replace all occurences of the string `{{app}} found in the list of files given in argument,
	it replaces it with the name of the prject

	@param files        {list[str]} A list containing all the files to parse and to perform the string substitution
	@param project_name {str}       This is the string used as the name for the copy of the skeleton folder, as well as for the string substitions (see param above)
	@return             {None}       It returns `None` as there's no need to interupt the execution of the program in case any file is not found, just simply skips, and notifies the users about it
	"""
	project_path: str = os.path.join(APP_CWD, project_name)

	for elem in files:
		new_elem: str = os.path.join(project_path, elem)
		# Replace all occurences of {{app}}
		if not file_exists(new_elem):
			#print(f"033[93Warning:\033[0m Skipping not found file, expected at location:\n{new_elem}")
			continue

		sub_str: str = "s/{{app}}/" + project_name + "/g"
		update_file = subprocess.call(["sed", "-i", sub_str, new_elem])
		if update_file != 0:
			print(f"033[93mWarning:\033[0m Could not process substition in the following file:\n{new_elem}")

		# Move 'app.conf' to <project_name>.conf
		if os.path.basename(new_elem) == "app.conf":
			new_new_elem = new_elem.replace("app.conf", f"{project_name}.conf")
			shutil.move(new_elem, new_new_elem)


def copy_skeleton(project_name: str) -> bool:
	"""
	@brief Simply copy the `skeleton` folder, ffrom its source the current woking directory, and the copy is named with `project_name`  param
	
	@param project_name {string} the name of the new project to create from the skeleton
	@return             {bool}   return True on success
	"""
	project_path: str = os.path.join(APP_CWD, project_name)
	if os.path.exists(project_path):
		print(f"033[93mWarning:\033[0m A folder with that name already exists, at Location:\n{project_path}\nExiting now...")
		return False

	check_op: bool = False
	try:
		shutil.copytree(APP_SKELETON, project_path)
		check_op = True
	except (OSError, Exception) as ex:
		print(f"033[31mError:\033[0m An error occured: {ex}")
	
	if check_op:
		return check_op


def setup_skeleton(project_name: str) -> bool:
	"""
	@brief Initialize the list of files that will later be processed to subsitute template sub strings in them
	
	@param project_name {string} the name of the new project to create from the skeleton
	@return             {bool}   return True on success
	"""
	files_list: list[str] | None = None 
	files_list_loc: str = os.path.join(APP_PATH, "data/files.txt")
	final_check: bool = False
	
	try:
		with open(files_list_loc, 'r', encoding="utf-8") as fd:
			files_list = fd.readlines()
			files_list = [f.strip() for f in files_list]
			if len(files_list) == 0:
				print(f"033[93mWarning:\033[0m The files list is empty; file location:\n{files_list_loc}\nExiting now...")
			else:
				if copy_skeleton(project_name):
					final_check = True
					setup_files(files_list, project_name)
	except FileNotFoundError:
		print(f"033[91mError:\033[0m The configuration file was not found at the expected location:\n{files_list_loc}\nExiting now...")
	
	return final_check
	

def main(arguments: list[str]) -> int:
	"""
	@brief Entry point, main function
	@description The main function process the command line arguments, then create the new project by doing a copy
	of the `skeleton` folder, in the current working directory where the user execute the script.
	To create the copy it calls the `setup_skeleton` function, which function calls other functions to perform
	the various task related to the copying: string subsitutions to update the copy with the project name, and 
	changing the name of the `app.conf` file to `<project name>.conf`.
	
	@param arguments {sys.argv} The command line arguments
	@return          {int}      Returns 0 on succes, 1 on failure
	"""
	if len(arguments) == 1:
		print(f"\033[91mError:\033[0m Missing argument(s); do `{__app_name__}` --help to display the help message")
		return EXIT_FAILURE

	args: Any = get_args()
	
	if args.name:
		clean_name: str = args.name[0]
		clean_name = clean_name.strip()
		clean_name = clean_name.replace(' ', '_')
		for letter in clean_name:
			if letter not in string.ascii_letters or letter not in string.digits:
				clean_name.replace(letter, '')
		if setup_skeleton(clean_name):
			print(f"033[92mSuccess:\033[0m Skeleton setup done with name \"{clean_name}\", in location:\n{os.path.join(APP_CWD, clean_name)}")

	return EXIT_SUCCESS

if __name__ == "__main__":
	sys.exit(main(sys.argv))
