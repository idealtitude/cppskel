# C++ Project Skeleton

## What is this?

This utility copy a C++ skeleton folder and set it up with the name you choose.

![cppskel logo](./cppskel_logo-512x512.png "cppskel logo")

### Presentation

As I often reuse or redo the same kind of classes, functionalities, and/or logic, in my C++ project, I've created this C++ Project Skeleton to avoid any tedious and repetitive tasks that occure each time.
This `skeleton` is tailored to suits my need, it may not be what you need or want; still you can modify the skeleton folder and adapt it to your needs.

The Python script that comes with this repository, does a copy of the C++ `skeleton` folder, and also does template string replacements in several of the files of the newly created project folder, which files are listed in [./data/files.txt](./data/files.txt), and you can of course modify and adpat it as you want.

**Imporant:**

* the script requires a name for the copy of the project folder destnation, passed as a command line argument, this name is going to be used to rename some files and in the template string substitutions, so choose the name with this in mind
* if the name contains characters other than ASCII letters, digits, dash `-`, and underscore `_`, or if it contains spaces, they're going to be removed in the case of non authorized characters, or replaced by underscores in the case of spaces
* the new project folder is copied in your current working directory!

### Installation

As "CPP Project Skeleton" can simply be used out of the box, it does not require an installation. That being said you can use the provided `Makefile`:

```bash
git clone https://github.com/idealtitude/cppskel.git
# Or download the zip file and:
# unzip cppskel.zip
cd cppskel
make install
```

And then you can simply invoke directly the command `cppskel` from any directory where you want to create a copy of the C++ skeleton...

Or if your prefer to do it manually, make the Python script utility accessible from your path by linking it in your `/$HOME/bin` or `/$HOME/.local/bin` folders; simply as follow:

```bash
# In this example I've named the link `cppskel`
ln -s "/$HOME/<path to>/skeleton.py" "/$HOME/.local/bin/cppskel"
# Then you just have to do:
cd any/location/you/want
cppskel <project name> # name of your project
```

#### Python Script Usage

**Imporant:** the copy is made in your current woeking directory!

So `cd` in the directory where you want to create your new project, then call the script:

```bash
# Instantiate (copy) the skeleton in current working directory
/path/to/skeleton_setup.py <ProjectName>
```

## C++ Skeleton Usage

### Documentation

The documentation explains the C++ code...

*TODO:*  complete this section

**Note:** the `skeleton` directory is still a work in progress! The informations provided below may not be applicable for the moment

The documentation is located in the `./doc/` folder; additionally you can generate the [Doxygen](https://www.doxygen.nl/ "Doxygen Website"),
as well as the `man` pages, with respectively:

```bash
# Generate Doxygen documentation
make doc
# Generate and install man pages
make man
```
