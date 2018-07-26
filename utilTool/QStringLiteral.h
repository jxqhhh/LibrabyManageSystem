#if defined(QT_UNICODE_LITERAL_II)
// QT_UNICODE_LITERAL needed because of macro expension rules
# define QT_UNICODE_LITERAL(str) QT_UNICODE_LITERAL_II(str)
# if defined(Q_COMPILER_LAMBDA)
#  define QStringLiteral(str) \
([]() ->  QString   { \
         enum   { Size =  sizeof ( QT_UNICODE_LITERAL (str))/ 2   -  1   }; \
         static   const   QStaticStringData <Size> qstring_literal = { \
             Q_STATIC_STRING_DATA_HEADER_INITIALIZER(Size), \
             QT_UNICODE_LITERAL (str) }; \
         QStringDataPtr   holder = { &qstring_literal.str }; \
         const   QString   s(holder); \
         return   s; \
     }()) \
# elif defined(Q_CC_GNU)
// 使用GCC的 __extension__ ({ }) 技巧代替lambda
// ... <skiped> ...
# endif
#endif
#ifndef QStringLiteral
// 不支持lambdas, 不是GCC，或者GCC为C++98模式，使用4字节wchar_t
// fallback, 返回一个临时的QString
// 默认认为源码为utf-8编码
#define QStringLiteral(str) QString::fromUtf8(str, sizeof(str) - 1)
#endif
#ifndef Q_OBJECT
#define Q_OBJETC(str) str
#endif



