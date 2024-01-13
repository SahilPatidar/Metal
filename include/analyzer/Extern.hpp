#pragma once
#include"../Context.hpp"
#include"../parser/Ast.hpp"
namespace ast { 

class ExternHandler{

public:
    ExternHandler(){}
    ~ExternHandler(){}
    typedef void (*ExternStmt)(Context &Mgr, const StmtLoc *Loc, Ast **Base);
    #define EXTERN(name) \
        void Extern_##name(Context &Mgr, const StmtLoc *Loc, Ast **Base)

    EXTERN(printf);
    EXTERN(scanf);
    EXTERN(fflush);
    EXTERN(getline);
    EXTERN(exit);
    // EXTERN(relloc);
    // EXTERN(calloc);
    // EXTERN(FILE);
    // EXTERN(DIR);
    // EXTERN(dirent);
    // EXTERN(malloc);
    // EXTERN(relloc);
    // EXTERN(read);
    // EXTERN(write);
    // EXTERN(open);
    // EXTERN(close);
    // EXTERN(grp);
    // EXTERN(pwd);
    // EXTERN(stat);
    // EXTERN(time);
    // EXTERN(ioctl);
    // EXTERN(dirent);
    // EXTERN(unistd);
    EXTERN(FILE);
    EXTERN(__sbuf);
    EXTERN(__sFILEX);
    // EXTERN(stdin);
    // EXTERN(stdout);
    // EXTERN(stderr);
    // EXTERN(errno);
    // EXTERN(popen);
    // EXTERN(pclose);
    EXTERN(read);
    EXTERN(write);
    EXTERN(open);
    EXTERN(close);
    EXTERN(fopen);
    EXTERN(creat);
    EXTERN(fclose);
    
    // EXTERN(fputs);
    // EXTERN(fprintf);
    // EXTERN(putc);
    // EXTERN(fputc);
    // EXTERN(puts);
    // EXTERN(snprintf);
    EXTERN(strlen);
    // EXTERN(strcmp);
    // EXTERN(strcpy);
    // EXTERN(strncmp);
    // EXTERN(strncpy);
    // EXTERN(getenv);
    // EXTERN(setenv);
    // EXTERN(system);
    // EXTERN(isspace);
    // EXTERN(strerror);
    // EXTERN(dirname);
    // EXTERN(basename);
    // EXTERN(atoll);
    // EXTERN(atoull);
    // EXTERN(ctype);
    // EXTERN(opendir);
    // EXTERN(closedir);
    // EXTERN(readdir);
    // EXTERN(rewinddir);
    // EXTERN(seekdir);
    // EXTERN(telldir);
    // EXTERN(free);
    // EXTERN(malloc);
    // EXTERN(calloc);
    // EXTERN(realloc);
    // EXTERN(memccpy);
    // EXTERN(memcpy);
    // EXTERN(memcmp);
    // EXTERN(memset);
    // EXTERN(free);
    EXTERN(malloc);
    EXTERN(calloc);
    EXTERN(realloc);
    EXTERN(memccpy);
    EXTERN(memcpy);
    EXTERN(memcmp);
    EXTERN(memset);
    EXTERN(free);

};

}