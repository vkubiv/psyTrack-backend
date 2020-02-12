#pragma once

#include <http/Async.h>

#include "AuthErrors.h"

namespace auth {
template<class T>
struct AuthResult
{
  T value;
  AuthErrorCode errorCode;

  explicit AuthResult(T v)
    : value(std::move(v))
    , errorCode(AuthErrorCode::Ok)
  {}

  explicit AuthResult(AuthErrorCode ec)
    : value(T())
    , errorCode(ec)
  {}
};

template<class T>
using AuthAsyncResult = Async::Promise<AuthResult<T>>;

template<class T>
inline AuthAsyncResult<T>
makeAuthAsyncResult(T v)
{
  return AuthAsyncResult<T>::resolved(AuthResult<T>(std::move(v)));
}

template<class T>
inline AuthAsyncResult<T>
makeAsyncResultError(AuthErrorCode ec)
{
  return AuthAsyncResult<T>::resolved(AuthResult<T>(ec));
}

}