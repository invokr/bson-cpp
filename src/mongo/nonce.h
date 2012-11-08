// @file nonce.h

/*    Copyright 2009 10gen Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef NONCE_H
#define NONCE_H

#include <iosfwd>
#include <boost/noncopyable.hpp>

#include "mongo/assert_util.h"

namespace mongo {

    typedef unsigned long long nonce64;

    struct Security {
        Security();
        static nonce64 getNonce();
        static nonce64 getNonceDuringInit(); // use this version during global var constructors
    private:
        nonce64 _getNonce();
        nonce64 __getNonce();
        std::ifstream *_devrandom;
        bool _initialized;
        void init(); // can call more than once
    };
    
    class StaticObserver : boost::noncopyable {
    public:
        static bool _destroyingStatics;
        ~StaticObserver() { _destroyingStatics = true; }
    };
    
   /** The concept with SimpleMutex is that it is a basic lock/unlock with no 
       special functionality (such as try and try timeout).  Thus it can be 
       implemented using OS-specific facilities in all environments (if desired).
       On Windows, the implementation below is faster than boost mutex.
    */
#if defined(_WIN32)
    class SimpleMutex : boost::noncopyable {
    public:
        SimpleMutex( const char * ) { InitializeCriticalSection( &_cs ); }
        void dassertLocked() const { }
        void lock() { EnterCriticalSection( &_cs ); }
        void unlock() { LeaveCriticalSection( &_cs ); }
        class scoped_lock {
            SimpleMutex& _m;
        public:
            scoped_lock( SimpleMutex &m ) : _m(m) { _m.lock(); }
            ~scoped_lock() { _m.unlock(); }
            const SimpleMutex& m() const { return _m; }
        };

    private:
        CRITICAL_SECTION _cs;
    };
#else
    class SimpleMutex : boost::noncopyable {
    public:
        void dassertLocked() const { }
        SimpleMutex(const char* name) { verify( pthread_mutex_init(&_lock,0) == 0 ); }
        ~SimpleMutex(){ 
            if ( ! StaticObserver::_destroyingStatics ) { 
                verify( pthread_mutex_destroy(&_lock) == 0 ); 
            }
        }

        void lock() { verify( pthread_mutex_lock(&_lock) == 0 ); }
        void unlock() { verify( pthread_mutex_unlock(&_lock) == 0 ); }
    public:
        class scoped_lock : boost::noncopyable {
            SimpleMutex& _m;
        public:
            scoped_lock( SimpleMutex &m ) : _m(m) { _m.lock(); }
            ~scoped_lock() { _m.unlock(); }
            const SimpleMutex& m() const { return _m; }
        };

    private:
        pthread_mutex_t _lock;
    };
#endif


} // namespace mongo

#endif
