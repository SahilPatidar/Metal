#pragma once
#include"lex/lex.hpp"
#include"parser/Ast.hpp"
#define MAX_ERROR 15

namespace err{
    // void out(std::string msg, lex::Lexeme tok);
    // void err_out(Ast *stmt, std::string errmsg);
    // void err_out(const ast::StmtLoc *loc, std::string errmsg);
    // void warn_out(Ast *stmt, std::string errmsg);



inline void appendToString(std::string &dest) {}

template<typename... Args> void appendToString(std::string &dest, std::string_view data, Args... args);
template<typename... Args> void appendToString(std::string &dest, char data, Args... args);
template<typename... Args> void appendToString(std::string &dest, unsigned char data, Args... args);
template<typename... Args> void appendToString(std::string &dest, int data, Args... args);
template<typename... Args> void appendToString(std::string &dest, int64_t data, Args... args);
template<typename... Args> void appendToString(std::string &dest, size_t data, Args... args);
template<typename... Args> void appendToString(std::string &dest, float data, Args... args);
template<typename... Args> void appendToString(std::string &dest, double data, Args... args);

template<typename... Args> void appendToString(std::string &dest, std::string_view data, Args... args)
{
	dest += data;
	appendToString(dest, args...);
}
template<typename... Args> void appendToString(std::string &dest, char data, Args... args)
{
	dest += data;
	appendToString(dest, args...);
}
template<typename... Args> void appendToString(std::string &dest, unsigned char data, Args... args)
{
	dest += std::to_string(data);
	appendToString(dest, args...);
}
template<typename... Args> void appendToString(std::string &dest, int data, Args... args)
{
	dest += std::to_string(data);
	appendToString(dest, args...);
}
template<typename... Args> void appendToString(std::string &dest, int64_t data, Args... args)
{
	dest += std::to_string(data);
	appendToString(dest, args...);
}
template<typename... Args> void appendToString(std::string &dest, size_t data, Args... args)
{
	dest += std::to_string(data);
	appendToString(dest, args...);
}
template<typename... Args> void appendToString(std::string &dest, float data, Args... args)
{
	dest += std::to_string(data);
	appendToString(dest, args...);
}
template<typename... Args> void appendToString(std::string &dest, double data, Args... args)
{
	dest += std::to_string(data);
	appendToString(dest, args...);
}
template<typename T, typename... Args> void appendToString(std::string &dest, Args... args)
{
	int tmp[] = {(appendToString(dest, args))...};
	static_cast<void>(tmp);
}



void outCommonStr(const ast::StmtLoc *loc, bool withloc, const std::string &e);

template<typename... Args>
void outCommon(const ast::StmtLoc *loc, bool withloc, Args &&...args)
{
	std::string res;
	appendToString(res, std::forward<Args>(args)...);
	outCommonStr(loc, withloc, res);
}

template<typename... Args> void err_out(const ast::StmtLoc *loc, Args &&...args)
{
	outCommon(loc, true, std::forward<Args>(args)...);
}
template<typename... Args> void err_out(ast::StmtLoc &&loc, Args &&...args)
{
	outCommon(&loc, true, std::forward<Args>(args)...);
}

template<typename... Args> void err_out(ast::Ast *stmt, Args &&...args)
{
	outCommon(stmt->getStmtLoc(), true, std::forward<Args>(args)...);
}


using Nullptr = nullptr_t;
template<typename... Args> void out(Nullptr, Args &&...args)
{
	out(static_cast<const ast::StmtLoc *>(nullptr), false,  std::forward<Args>(args)...);
}



}

