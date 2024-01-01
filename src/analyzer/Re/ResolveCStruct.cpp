#include"../../include/analyzer/Resolve.hpp"
#include"../../include/parser/type.hpp"
#include"../../include/analyzer/symbol_table.hpp"
#include"../../include/Module.hpp"
#include"../../include/Error.hpp"
#include"../ResMgr.hpp"
#include"../parser/Ast.hpp"

namespace ast {
    EXTERN(sbuf) {
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
        StructStmt::Create(Mgr, Loc, _Sbuf, _SbufField);
    }

    EXTERN(FILE) {
        std::vector<VarStmt *>Vars;

        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        PremitiveType *UsignChar = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui8", UI8));
        PremitiveType *Char = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i8", UI8));
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
        Vars.push_back(VarStmt::Create(Mgr, Loc, _R, Int, nullptr, _MUT));

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
        Vars.push_back(VarStmt::Create(Mgr, Loc, _Bf, Int, nullptr, _MUT));
        
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

        StructStmt::Create(Mgr, Loc, Lexeme(Loc, "FILE", IDEN), Vars);
    }

    EXTERN(DIR) {
        std::vector<VarStmt *>Vars;
        PremitiveType *Int = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i32", I32));
        PremitiveType *UsignChar = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "ui8", UI8));
        PremitiveType *Char = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i8", UI8));
        PremitiveType *Short = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i16", I16));
        PremitiveType *Long = PremitiveType::Create(Mgr, Loc, Lexeme(Loc, "i64", I64));
        PrefixExpr *PtrUsignChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), UsignChar, true, true);
        PrefixExpr *PtrChar = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Char, true, true);
        PrefixExpr *VoidPtr = PrefixExpr::Create(Mgr, Loc, Tok(STAR), Void::Create(Mgr, Loc), true, true);
        
        // int	__dd_fd;	/* file descriptor associated with directory */
        Vars.push_back(VarStmt::Create(Mgr, Loc, Lexeme(Loc, "__dd_fd", IDEN), Int, nullptr, _MUT));
        // long	__dd_loc;	/* offset in current buffer */
        
        // long	__dd_size;	/* amount of data returned */
        
        // char	*__dd_buf;	/* data buffer */
        
        // int	__dd_len;	/* size of data buffer */
        
        // long	__dd_seek;	/* magic cookie returned */
        
        // __unused long	__padding; /* (__dd_rewind space left for bincompat) */
        
        // int	__dd_flags;	/* flags for readdir */
        
        // __darwin_pthread_mutex_t __dd_lock; /* for thread locking */
        
        // struct _telldir *__dd_td; /* telldir position recording */

    }

    EXTERN(dirent) {
        __uint64_t  d_ino;      /* file number of entry */ \
	__uint64_t  d_seekoff;  /* seek offset (optional, used by servers) */ \
	__uint16_t  d_reclen;   /* length of this record */ \
	__uint16_t  d_namlen;   /* length of string in d_name */ \
	__uint8_t   d_type;     /* file type, see below */ \
	char      d_name[__DARWIN_MAXPATHLEN]; /* entry name (up to MAXPATHLEN bytes) */ \

    }

    

}