#if !defined(__MUNKRES_CPP_UTILS_H__)
#define __MUNKRES_CPP_UTILS_H__

// Macro for trivial support of Design By Contract.
#define DBC_MODE_NONE       0
#define DBC_MODE_MESSAGE    1
#define DBC_MODE_ASSERT     2

#ifndef DEBUG_WITH_DBC
#define DEBUG_WITH_DBC DBC_MODE_NONE
#endif//DEBUG_WITH_DBC

#ifdef  DEBUG_WITH_DBC

#ifdef  STRINGIFICATION
#error  STRINGIFICATION macro already defined!
#endif//STRINGIFICATION
#define STRINGIFICATION(x) #x

#if DEBUG_WITH_DBC == DBC_MODE_ASSERT
    #define REQUIRE(CONDITION, MESSAGE)\
        do {\
            if (!(CONDITION) ) {\
                throw std::runtime_error (\
                    "Precondition error: "\
                   + std::string (STRINGIFICATION (CONDITION) ) + " at "\
                   + std::string (__FILE__) + ":" + std::to_string (__LINE__) + ". "\
                   + std::string (MESSAGE) );\
            }\
        } while (0);

    #define ENSURE(CONDITION, MESSAGE)\
        do {\
            if (!(CONDITION) ) {\
                throw std::runtime_error (\
                    "Postcondition error: "\
                   + std::string (STRINGIFICATION (CONDITION) ) + " at "\
                   + std::string (__FILE__) + ":" + std::to_string (__LINE__) + ". "\
                   + std::string (MESSAGE) );\
            }\
        } while (0);

    #define INVARIANT(CONDITION, MESSAGE)\
        do {\
            if (!(CONDITION) ) {\
                throw std::runtime_error (\
                    "Invariant error: "\
                   + std::string (STRINGIFICATION (CONDITION) ) + " at "\
                   + std::string (__FILE__) + ":" + std::to_string (__LINE__) + ". "\
                   + std::string (MESSAGE) );\
            }\
        } while (0);

#elif DEBUG_WITH_DBC == DBC_MODE_MESSAGE
    #define STRINGIFICATION(x) #x
    #define REQUIRE(CONDITION, MESSAGE)\
        do {\
            if (!(CONDITION) ) {\
                std::cout\
                << "Precondition error: "\
                << std::string (STRINGIFICATION (CONDITION) ) + " at "\
                << std::string (__FILE__) << ":" << std::to_string (__LINE__) << ". "\
                << std::string (MESSAGE)\
                << std::endl;\
            }\
        } while (0);

    #define ENSURE(CONDITION, MESSAGE)\
        do {\
            if (!(CONDITION) ) {\
                std::cout\
                << "Postcondition error: "\
                << std::string (STRINGIFICATION (CONDITION) ) + " at "\
                << std::string (__FILE__) << ":" << std::to_string (__LINE__) << ". "\
                << std::string (MESSAGE)\
                << std::endl;\
            }\
        } while (0);

    #define INVARIANT(CONDITION, MESSAGE)\
        do {\
            if (!(CONDITION) ) {\
                std::cout\
                << "Invariant error: "\
                << std::string (STRINGIFICATION (CONDITION) ) + " at "\
                << std::string (__FILE__) << ":" << std::to_string (__LINE__) << ". "\
                << std::string (MESSAGE)\
                << std::endl;\
            }\
        } while (0);

#else //DEBUG_WITH_DBC || DEBUG_WITH_DBC_ASSERT
    #define REQUIRE(CONDITION, MESSAGE);
    #define ENSURE(CONDITION, MESSAGE);
    #define INVARIANT(CONDITION, MESSAGE);
#endif//DEBUG_WITH_DBC || DEBUG_WITH_DBC_ASSERT

#endif//DEBUG_WITH_DBC

#endif /* !defined(__MUNKRES_CPP_UTILS_H__) */
