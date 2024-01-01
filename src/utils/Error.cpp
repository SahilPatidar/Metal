#include"../../include/Error.hpp"
#include"../../include/Module.hpp"

namespace err{
// class StmtLoc;
// void out(std::string msg, lex::Lexeme tok){
//     std::string red = "\033[0;31m"; 
//     std::string green = "\033[0;32m"; 
//     std::string y = "\033[0;33m"; 
//     std::string b = "\033[0;34m"; 
//     std::cerr<<"\033[0;31m error:: "<<tok.getLine()+1<<":"<<tok.getPos()<<" { "<<msg<<" \' "<<tok.getStr()<<" \'"<<" } "<<std::endl;
//     //exit(1);
// }


void outCommonStr(const ast::StmtLoc *loc, bool withloc, const std::string &e) {
    if(withloc)
        std::cerr<<"\x1b[3m\033[0;33m in file "<<loc->getMod()->getPath()<<"\n \x1b[1m\033[0;31m --> error "<<loc->getString()<<" :: "<<e<<"\x1b]0m\033]0m"<<std::endl;
    else 
        std::cerr<<"\x1b[1m\033[0;31m --> error "<<" :: "<<e<<"\x1b]0m\033]0m"<<std::endl;
}

}