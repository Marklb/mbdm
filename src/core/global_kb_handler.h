#ifndef __GLOBAL_KB_HANDLER_H__
#define __GLOBAL_KB_HANDLER_H__

#include <windows.h>

#include "../common.h"


// class GlobalKbHandler
// {
// public:
//     GlobalKbHandler(void);
//     ~GlobalKbHandler(void);
//
// private:
//     bool m_Hooked;
//     HHOOK m_HookKb;
//
// public:
//     void Hook(void);
//     void UnHook(void);
//     LRESULT CALLBACK KbHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
//
// };


#endif // __GLOBAL_KB_HANDLER_H__


// class S
// {
//     public:
//         static S& getInstance()
//         {
//             static S    instance; // Guaranteed to be destroyed.
//                                   // Instantiated on first use.
//             return instance;
//         }
//     private:
//         S() {}                    // Constructor? (the {} brackets) are needed here.
//
//         // C++ 03
//         // ========
//         // Dont forget to declare these two. You want to make sure they
//         // are unacceptable otherwise you may accidentally get copies of
//         // your singleton appearing.
//         S(S const&);              // Don't Implement
//         void operator=(S const&); // Don't implement
//
//         // C++ 11
//         // =======
//         // We can use the better technique of deleting the methods
//         // we don't want.
//     public:
//         S(S const&)               = delete;
//         void operator=(S const&)  = delete;
//
//         // Note: Scott Meyers mentions in his Effective Modern
//         //       C++ book, that deleted functions should generally
//         //       be public as it results in better error messages
//         //       due to the compilers behavior to check accessibility
//         //       before deleted status
// };
