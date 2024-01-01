#include"../../include/Module.hpp"
#include"../../include/analyzer/Extern.hpp"
#include"../../include/Error.hpp"

namespace ast {
    
    void ExternHandler::Extern_printf(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        std::vector<VarStmt *>Params;
        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        PremitiveType *Char = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i8", I8));
        PrefixExpr *PtrChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Char, true, true);

        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__msg", IDEN), PtrChar, nullptr, 0));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "printf", IDEN), Params, Int);
        Fn->setVariadic();
        Fn->setExtern();
        *Base = Fn;
    }


    void ExternHandler::Extern_scanf(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        std::vector<VarStmt *>Params;
        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        PremitiveType *Char = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i8", I8));
        PrefixExpr *PtrChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Char, true, true);

        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__msg", IDEN), PtrChar, nullptr, 0));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "scanf", IDEN), Params, Int);
        Fn->setVariadic();
        Fn->setExtern();
        *Base = Fn;
    }


    void ExternHandler::Extern_fflush(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        std::vector<VarStmt *>Params;
        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        Identifier *_FILE = Identifier::Create(Mgr, Loc, Lexeme(Loc, "FILE", IDEN));
        PrefixExpr *PtrFILE = PrefixExpr::Create(Mgr, Loc, STAR, _FILE, true, true);
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__file", IDEN), PtrFILE, nullptr, 0));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "printf", IDEN), Params, Int);
        Fn->setExtern();
        *Base = Fn;
    }


    void ExternHandler::Extern_getline(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        std::vector<VarStmt *>Params;
        // ssize_t getline(char **__linep, size_t *__linecapp, FILE *__stream)
        PremitiveType *Ssize_t = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i64", I64));
        PremitiveType *Size_t = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64));
        PrefixExpr *PtrSize_t = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Size_t, true, true);
        
        PremitiveType *Char = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i8", I8));
        PrefixExpr *PtrChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Char, true, true);
        PrefixExpr *PtrPtrChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), PtrChar, true, true);

        Identifier *_FILE = Identifier::Create(Mgr, Loc, Lexeme(Loc, "FILE", IDEN));
        PrefixExpr *PtrFILE = PrefixExpr::Create(Mgr, Loc, STAR, _FILE, true, true);

        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__linep", IDEN), PtrPtrChar, nullptr, 0));
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__linecapp", IDEN), PtrSize_t, nullptr, 0));
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__stream", IDEN), PtrFILE, nullptr, 0));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "printf", IDEN), Params, Ssize_t);
        Fn->setExtern();
        *Base = Fn;
    }


    void ExternHandler::Extern_strlen(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        std::vector<VarStmt *>Params;
        PremitiveType *Size_t = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64));

        PremitiveType *Char = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i8", I8));
        PrefixExpr *PtrChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Char, false, true);

        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__s", IDEN), PtrChar, nullptr, 0));

        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "strlen", IDEN), Params, Size_t);
        Fn->setExtern();
        *Base = Fn;
    }

    void ExternHandler::Extern_exit(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        std::vector<VarStmt *>Params;
        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        VarStmt *Var = VarStmt::Create(Mgr, Loc, Lexeme(Loc, "status", IDEN), Int, nullptr, _MUT);
        Params.push_back(Var);
        Void *Vd = Void::Create(Mgr, Loc);
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "exit", IDEN), Params, Vd);
        Fn->setExtern();
        *Base = Fn;
    }



//     EXTERN(grp);
//     EXTERN(pwd);
//     EXTERN(stat);
    // EXTERN(time);
//     EXTERN(ioctl);
//     EXTERN(unistd);
//     EXTERN(FILE);
//     EXTERN(stderr);
//     EXTERN(errno);
//     EXTERN(popen);
//     EXTERN(pclose);
//     EXTERN(fopen);
//     EXTERN(fclose);
//     EXTERN(fflush);
//     EXTERN(fputs);
//     EXTERN(fprintf);
//     EXTERN(getline);
//     EXTERN(putc);
//     EXTERN(fputc);
//     EXTERN(puts);
//     EXTERN(snprintf);
//     EXTERN(strcmp);
//     EXTERN(strcpy);
//     EXTERN(strncmp);
//     EXTERN(strncpy);
//     EXTERN(getenv);
//     EXTERN(setenv);
//     EXTERN(system);
//     EXTERN(isspace);
//     EXTERN(strerror);
//     EXTERN(dirname);
//     EXTERN(basename);
//     EXTERN(atoll);
//     EXTERN(atoull);
//     EXTERN(ctype);
//     EXTERN(opendir);
//     EXTERN(closedir);
//     EXTERN(readdir);
//     EXTERN(rewinddir);
//     EXTERN(seekdir);
//     EXTERN(telldir);

    void ExternHandler::Extern_open(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        std::vector<VarStmt *>Params;
        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        PremitiveType *Char = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i8", I8));
        PrefixExpr *PtrChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Char, true, true);
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__filename", IDEN), PtrChar, nullptr, _CONST));
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__mode", IDEN), Int, nullptr, _CONST));
        // *Base = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "open", IDEN), Params, FPtr);
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "open", IDEN), Params, Int);
        Fn->setVariadic();
        Fn->setExtern();
        *Base = Fn;
    }


    void ExternHandler::Extern_read(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        std::vector<VarStmt *>Params;
        //int __fd, const void *__buf, size_t __nbyte
        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        PremitiveType *Size_t = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64));
        PremitiveType *Ssize_t = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i64", UI64));
        PrefixExpr *VoidPtr = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Void::Create(Mgr, Loc), true, true);
       

        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__fd", IDEN), Int, nullptr, 0));
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__buf", IDEN), VoidPtr, nullptr, 0));
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__size", IDEN), Size_t, nullptr, 0));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "read", IDEN), Params, Ssize_t);
        Fn->setExtern();
        *Base = Fn;
    }


    void ExternHandler::Extern_write(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        std::vector<VarStmt *>Params;
        //int __fd, const void *__buf, size_t __nbyte
        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        PremitiveType *Size_t = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64));
        PremitiveType *Ssize_t = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i64", UI64));
        PrefixExpr *VoidPtr = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Void::Create(Mgr, Loc), true, true);
       

        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__fd", IDEN), Int, nullptr, _CONST));
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__buf", IDEN), VoidPtr, nullptr, _CONST));
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__nbyte", IDEN), Size_t, nullptr, _CONST));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "write", IDEN), Params, Ssize_t);
        Fn->setExtern();
        *Base = Fn;
    }



    void ExternHandler::Extern_close(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        VarStmt *P = VarStmt::Create(Mgr, Loc, Lexeme(Loc, "_fd", IDEN), Int, nullptr, _CONST);
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "close", IDEN), {P}, Int);
        Fn->setExtern();
        *Base = Fn;
    }



    void ExternHandler::Extern_fopen(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        std::vector<VarStmt *>Params;
        PrefixExpr *FPtr = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Identifier::Create(Mgr, Loc, Lexeme(Loc, "FILE", IDEN)), true, true);
        PremitiveType *Char = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i8", I8));
        PrefixExpr *PtrChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Char, true, true);
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__filename", IDEN), PtrChar, nullptr, _CONST));
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__mode", IDEN), PtrChar, nullptr, _CONST));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "fopen", IDEN), Params, FPtr);
        Fn->setExtern();
        *Base = Fn;
    }

    void ExternHandler::Extern_fclose(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        std::vector<VarStmt *>Params;
        PrefixExpr *FPtr = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Identifier::Create(Mgr, Loc, Lexeme(Loc, "FILE", IDEN)), true, true);
        VarStmt *Param = VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__file", IDEN), FPtr, nullptr, _CONST);
        Params.push_back(Param);
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "fclose", IDEN), Params, PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32)));
        Fn->setExtern();
        *Base = Fn;
    }


    void ExternHandler::Extern___sbuf(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        /* stdio buffers */
        // struct __sbuf {
        //     unsigned char	*_base;
        //     int		_size;
        // };
        PremitiveType *UsignChar = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui8", UI8));
        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        PrefixExpr *PtrUsignChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), UsignChar, true, true);
        
        Lexeme _Sbuf(Loc, "__sbuf", IDEN);
        std::vector<VarStmt *>_SbufField;
        Lexeme _Base(Loc, "_base", IDEN);
        Lexeme _Size(Loc, "_size", IDEN);
        _SbufField.push_back(VarStmt::Create(Mgr, Loc, _Base, PtrUsignChar, nullptr, _MUT));
        _SbufField.push_back(VarStmt::Create(Mgr, Loc, _Size, Int, nullptr, _MUT));
        *Base = StructStmt::Create(Mgr, Loc, _Sbuf, _SbufField);
    }

    void ExternHandler::Extern___sFILEX(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        Lexeme __SFILEX(Loc, "__sFILEX", IDEN);
        std::vector<VarStmt *>_SbufField;
        *Base = StructStmt::Create(Mgr, Loc, __SFILEX, _SbufField);
    }

    void ExternHandler::Extern_FILE(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        std::vector<VarStmt *>Vars;

        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        PremitiveType *UsignChar = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui8", UI8));
        PremitiveType *Char = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i8", I8));
        PremitiveType *Short = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i16", I16));
        PremitiveType *LongLong = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i64", I64));
        PrefixExpr *PtrUsignChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), UsignChar, true, true);
        PrefixExpr *PtrChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Char, true, true);
        PrefixExpr *VoidPtr = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Void::Create(Mgr, Loc), true, true);
        // unsigned char *_p;	/* current position in (some) buffer */
        Lexeme _P(Loc, "_p", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _P, PtrUsignChar, nullptr, _MUT));

        // int	_r;		/* read space left for getc() */
        Lexeme _R(Loc, "_r", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _R, Int, nullptr, _MUT));

        // int	_w;		/* write space left for putc() */
        Lexeme _W(Loc, "_w", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _W, Int, nullptr, _MUT));

        // short	_flags;		/* flags, below; this FILE is free if 0 */
        Lexeme _Flags(Loc, "_flags", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Flags, Short, nullptr, _MUT));
       
        // short	_file;		/* fileno, if Unix descriptor, else -1 */
        Lexeme _File(Loc, "_file", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _File, Short, nullptr, _MUT));
	
        // struct	__sbuf _bf;	/* the buffer (at least 1 byte, if !NULL) */
        Lexeme _Bf(Loc, "_bf", IDEN);
        Identifier *__Sbuf = Identifier::Create(Mgr, Loc, Lexeme(Loc, "__sbuf", IDEN));
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Bf, __Sbuf, nullptr, _MUT));

        // int	_lbfsize;	/* 0 or -_bf._size, for inline putc */
        Lexeme _Lbfsize(Loc, "_lbfsize", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Lbfsize, Int, nullptr, _MUT));

        // void	*_cookie;	/* cookie passed to io functions */
        Lexeme _Cookie(Loc, "_cookie", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Cookie, VoidPtr, nullptr, _MUT));


        // int	(* _Nullable _close)(void *);
        Lexeme _Close(Loc, "_close", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Close, FnType::Create(Mgr, Loc, {VoidPtr}, Int), nullptr, _MUT));
        
        
        // int	(* _Nullable _read) (void *, char *, int);
        Lexeme _Read(Loc, "_read", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Read, FnType::Create(Mgr, Loc, {VoidPtr, PtrChar, Int}, Int), nullptr, _MUT));
        

        // fpos_t	(* _Nullable _seek) (void *, fpos_t, int);
        Lexeme _Seek(Loc, "_seek", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Seek, FnType::Create(Mgr, Loc, {VoidPtr, LongLong, Int}, LongLong), nullptr, _MUT));
        
        
        // int	(* _Nullable _write)(void *, const char *, int);
        Lexeme _Write(Loc, "_write", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Write, FnType::Create(Mgr, Loc, {VoidPtr, PtrChar, Int}, Int), nullptr, _MUT));

        // struct	__sbuf _ub;	/* ungetc buffer */
        Lexeme _Ub(Loc, "_ub", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Ub, __Sbuf, nullptr, _MUT));

        // struct __sFILEX *_extra; /* additions to FILE to not break ABI */
        Lexeme _Extra(Loc, "_extra", IDEN);
        Identifier *SFILEX = Identifier::Create(Mgr, Loc, Lexeme(Loc, "__sFILEX", IDEN));
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Extra, SFILEX, nullptr, _MUT));
        
        // int	_ur;		/* saved _r when _r is counting ungetc data */
        Lexeme _Ur(Loc, "_ur", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Ur, Int, nullptr, _MUT));

        // unsigned char _ubuf[3];	/* guarantee an ungetc() buffer */
        Lexeme _Ubuf(Loc, "_ubuf", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Ubuf, Array::Create(Mgr, Loc, NumericLiteral::Create(Mgr, Loc, Lexeme(Loc, (int64_t)3, INT)), UsignChar), nullptr, _MUT));

        // unsigned char _nbuf[1];	/* guarantee a getc() buffer */
        Lexeme _Nbuf(Loc, "_nbuf", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Nbuf, Array::Create(Mgr, Loc, NumericLiteral::Create(Mgr, Loc, Lexeme(Loc, (int64_t)1, INT)), UsignChar), nullptr, _MUT));

        // struct	__sbuf _lb;	/* buffer for fgetln() */
        Lexeme _Lb(Loc, "_lb", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Lb, __Sbuf, nullptr, _MUT));

        // int	_blksize;	/* stat.st_blksize (may be != _bf._size) */
        Lexeme _Blksize(Loc, "_blksize", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Blksize, Int, nullptr, _MUT));

        //fpos_t	_offset;
        Lexeme _Offset(Loc, "_offset", IDEN);
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Offset, LongLong, nullptr, _MUT));

        *Base = StructStmt::Create(Mgr, Loc, Lexeme(Loc, "FILE", IDEN), Vars);
    }

    void ExternHandler::Extern_free(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base){
        Void *VPtr = Void::Create(Mgr, Loc);
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "free", IDEN), 
                            {VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__ptr", IDEN), PrefixExpr::Create(Mgr, Loc, Tok(STAR), VPtr, true, true), nullptr, 0)}, 
                             VPtr);
        Fn->setExtern();
        *Base = Fn;
    }

    void ExternHandler::Extern_realloc(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base){
        Void *VPtr = Void::Create(Mgr, Loc);
        PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "realloc", IDEN), 
                            {VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__ptr", IDEN), PrefixExpr::Create(Mgr, Loc, STAR, VPtr, true, true), nullptr, 0),
                             VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__size", IDEN), PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64)), nullptr, 0)}, 
                             PrefixExpr::Create(Mgr, Loc, Tok(STAR), VPtr, true, true));
        Fn->setExtern();
        *Base = Fn;
    }


    void ExternHandler::Extern_creat(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base) {
        PremitiveType *Char = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i8", I8));
        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        PremitiveType *USort = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui16", UI16));
        PrefixExpr *PtrChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Char, true, true);
        std::vector<VarStmt *>Params;
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__buf", IDEN), PtrChar, nullptr, 0));
        Params.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__mod", IDEN), USort, nullptr, 0));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "creat", IDEN), Params, Int);
        Fn->setExtern();
        *Base = Fn;
    }

    void ExternHandler::Extern_calloc(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base){
        Void *VPtr = Void::Create(Mgr, Loc);
        PremitiveType *Size_T = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "calloc", IDEN), 
                            {VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__count", IDEN), Size_T, nullptr, 0),
                             VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__size", IDEN), Size_T, nullptr, 0)}, PrefixExpr::Create(Mgr, Loc, Tok(STAR), VPtr, true, true));
        Fn->setExtern();
        *Base = Fn;
    }

    void ExternHandler::Extern_malloc(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base){
        Void *VPtr = Void::Create(Mgr, Loc);
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "malloc", IDEN),
                             {VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__size", IDEN), PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64)), nullptr, 0)}, 
                             PrefixExpr::Create(Mgr, Loc, Tok(STAR), VPtr, true, true));
        Fn->setExtern();
        *Base = Fn;
    }


    void ExternHandler::Extern_memset(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base){
        Void *VPtr = Void::Create(Mgr, Loc);
        PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "memset", IDEN),
                             {VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__b", IDEN), PrefixExpr::Create(Mgr, Loc, STAR, VPtr, true, true), nullptr, _MUT),
                             VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__c", IDEN), PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", UI64)), nullptr, _MUT), 
                             VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__len", IDEN), PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64)), nullptr, _MUT)}, 
                             PrefixExpr::Create(Mgr, Loc, Tok(STAR), VPtr, true, true));
        Fn->setExtern();
        *Base = Fn;
    }

    void ExternHandler::Extern_memcpy(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base){
        Void *VPtr = Void::Create(Mgr, Loc);
        PrefixExpr *Ptr = PrefixExpr::Create(Mgr, Loc, STAR, VPtr, true, true);
        PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "memcpy", IDEN),
                             {VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__dst", IDEN), Ptr, nullptr, _MUT),
                             VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__src", IDEN), Ptr, nullptr, _MUT), 
                             VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__n", IDEN), PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64)), nullptr, _MUT)}, 
                             PrefixExpr::Create(Mgr, Loc, Tok(STAR), VPtr, true, true));
        Fn->setExtern();
        *Base = Fn;
    }

    void ExternHandler::Extern_memccpy(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base){
        Void *VPtr = Void::Create(Mgr, Loc);
        PrefixExpr *Ptr = PrefixExpr::Create(Mgr, Loc, STAR, VPtr, true, true);
        PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "memset", IDEN),
                             {VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__dst", IDEN), Ptr, nullptr, _MUT),
                             VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__src", IDEN), Ptr, nullptr, _MUT), 
                             VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__c", IDEN), PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", UI64)), nullptr, _MUT), 
                             VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__n", IDEN), PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64)), nullptr, _MUT)}, 
                             PrefixExpr::Create(Mgr, Loc, Tok(STAR), VPtr, true, true));
        Fn->setExtern();
        *Base = Fn;
    }

    void ExternHandler::Extern_memcmp(ResourceMgr &Mgr, const StmtLoc *Loc, Ast **Base){
        Void *VPtr = Void::Create(Mgr, Loc);
        PrefixExpr *Ptr = PrefixExpr::Create(Mgr, Loc, STAR, VPtr, true, true);
        PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64));
        FunctionProto *Fn = FunctionProto::Create(Mgr, Loc, Lexeme(Loc, "memcmp", IDEN),
                             {VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__s1", IDEN), Ptr, nullptr, _CONST),
                             VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__s2", IDEN), Ptr, nullptr, _CONST), 
                             VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__n", IDEN), PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui64", UI64)), nullptr, _MUT)}, 
                             PrefixExpr::Create(Mgr, Loc, Tok(STAR), VPtr, true, true));
        Fn->setExtern();
        *Base = Fn;
    }
}