#include<iostream>
#include<filesystem>
#include<fcntl.h>
#include<libgen.h>
#include<dirent.h>
#include"../../include/utils/File.hpp"
namespace fs{

bool get_src(std::string &_path, std::string &src) {
    char buffer[256];
    FILE* file;
    file = fopen(_path.c_str(), "r");
    if(file == NULL) {
        // fprintf(stderr, "Error: unable to open file: %s\n", _path.c_str());
        return false;
    }
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        src += buffer;
    }
    
    ///@todo line count

    fclose(file);
    if(src.empty()){
        fprintf(stderr, "error: encountered empty file: %s\n", _path.c_str());
        return false;
    }

    return true;
} 


char* get_dir_name(std::string &path) {
    char *p = (char*)path.c_str();
    return dirname(p);
}

char* get_base_name(std::string &path) {
    char *p = (char*)path.c_str();
    return basename(p);
}


bool get_root_mod_src(std::string &path, std::string &src, std::string &dirp, std::string &modname) {
    dirp = get_dir_name(path);
    modname = get_base_name(path);
    size_t dotpos = modname.find_last_of(".");
    modname = modname.substr(0,dotpos);
    if(dirp.empty()){
        return false;
    }
    if(!get_src(path,src)){
        return false;
    }
    return true;
}



bool get_sub_mod_src(std::string &path, const std::string &modname, std::string &src, std::string &dirp, std::string &absp) {
    //file/
    //file/mod.mt
    std::string modpath1 = path+"/"+modname+"/mod.mt";
    std::string modpath2 = path+"/"+modname+".mt";
    bool f1 = false,f2 = false;
    if(!(f1 = get_src(modpath1, src))&&!(f2 = get_src(modpath2, src))){
        fprintf(stderr, "error: no module find in scope - %s\n", modname.c_str());
        return false;
    }
    if(f1){
        dirp = get_dir_name(modpath1);
        absp = modpath1;
    }else if(f2){
        dirp = get_dir_name(modpath2);
        dirp.append("/"+modname);
        absp = modpath2;
    }
    return true;
}

}