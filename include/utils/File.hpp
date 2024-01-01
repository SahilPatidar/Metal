#ifndef FILE_H
#define FILE_H
#include<iostream>


namespace fs{

bool get_src(std::string &_path, std::string &src);

char* get_dir_name(std::string &path);

char* get_base_name(std::string &path);

bool get_root_mod_src(std::string &path, std::string &src, std::string &dirp, std::string &modname);

bool get_sub_mod_src(std::string &path, const std::string &modname, std::string &src, std::string &dirp, std::string &absp);

bool find_mod(std::string path, std::string modname, std::string &fdpath, std::string &modmtfile);

}
#endif