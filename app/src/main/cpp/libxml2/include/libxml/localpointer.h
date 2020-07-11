// © 2016 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html
/*
*******************************************************************************
*
*   Copyright (C) 2009-2016, International Business Machines
*   Corporation and others.  All Rights Reserved.
*
*******************************************************************************
*   file name:  localpointer.h
*   encoding:   UTF-8
*   tab size:   8 (not used)
*   indentation:4
*
*   created on: 2009nov13
*   created by: Markus W. Scherer
*/

#ifndef __LOCALPOINTER_H__
#define __LOCALPOINTER_H__

#include "utypes.h"

#if U_SHOW_CPLUSPLUS_API

#include <memory>

 U_NAMESPACE_BEGIN

 template<typename T>
 class LocalPointerBase {
 public:
     // No heap allocation. Use only on the stack.
     static void* U_EXPORT2 operator new(size_t) = delete;
     static void* U_EXPORT2 operator new[](size_t) = delete;
 #if U_HAVE_PLACEMENT_NEW
     static void* U_EXPORT2 operator new(size_t, void*) = delete;
 #endif

     explicit LocalPointerBase(T *p=NULL) : ptr(p) {}
     ~LocalPointerBase() { /* delete ptr; */ }
     UBool isNull() const { return ptr==NULL; }
     UBool isValid() const { return ptr!=NULL; }
     bool operator==(const T *other) const { return ptr==other; }
     bool operator!=(const T *other) const { return ptr!=other; }
     T *getAlias() const { return ptr; }
     T &operator*() const { return *ptr; }
     T *operator->() const { return ptr; }
     T *orphan() {
         T *p=ptr;
         ptr=NULL;
         return p;
     }
     void adoptInstead(T *p) {
         // delete ptr;
         ptr=p;
     }
 protected:
     T *ptr;
 private:
     // No comparison operators with other LocalPointerBases.
     bool operator==(const LocalPointerBase<T> &other);
     bool operator!=(const LocalPointerBase<T> &other);
     // No ownership sharing: No copy constructor, no assignment operator.
     LocalPointerBase(const LocalPointerBase<T> &other);
     void operator=(const LocalPointerBase<T> &other);
 };

 template<typename T>
 class LocalPointer : public LocalPointerBase<T> {
 public:
     using LocalPointerBase<T>::operator*;
     using LocalPointerBase<T>::operator->;
     explicit LocalPointer(T *p=NULL) : LocalPointerBase<T>(p) {}
     LocalPointer(T *p, UErrorCode &errorCode) : LocalPointerBase<T>(p) {
         if(p==NULL && U_SUCCESS(errorCode)) {
             errorCode=U_MEMORY_ALLOCATION_ERROR;
         }
     }
     LocalPointer(LocalPointer<T> &&src) U_NOEXCEPT : LocalPointerBase<T>(src.ptr) {
         src.ptr=NULL;
     }

     explicit LocalPointer(std::unique_ptr<T> &&p)
         : LocalPointerBase<T>(p.release()) {}

     ~LocalPointer() {
         delete LocalPointerBase<T>::ptr;
     }
     LocalPointer<T> &operator=(LocalPointer<T> &&src) U_NOEXCEPT {
         delete LocalPointerBase<T>::ptr;
         LocalPointerBase<T>::ptr=src.ptr;
         src.ptr=NULL;
         return *this;
     }

     LocalPointer<T> &operator=(std::unique_ptr<T> &&p) U_NOEXCEPT {
         adoptInstead(p.release());
         return *this;
     }

     void swap(LocalPointer<T> &other) U_NOEXCEPT {
         T *temp=LocalPointerBase<T>::ptr;
         LocalPointerBase<T>::ptr=other.ptr;
         other.ptr=temp;
     }
     friend inline void swap(LocalPointer<T> &p1, LocalPointer<T> &p2) U_NOEXCEPT {
         p1.swap(p2);
     }
     void adoptInstead(T *p) {
         delete LocalPointerBase<T>::ptr;
         LocalPointerBase<T>::ptr=p;
     }
     void adoptInsteadAndCheckErrorCode(T *p, UErrorCode &errorCode) {
         if(U_SUCCESS(errorCode)) {
             delete LocalPointerBase<T>::ptr;
             LocalPointerBase<T>::ptr=p;
             if(p==NULL) {
                 errorCode=U_MEMORY_ALLOCATION_ERROR;
             }
         } else {
             delete p;
         }
     }

     operator std::unique_ptr<T> () && {
         return std::unique_ptr<T>(LocalPointerBase<T>::orphan());
     }
 };

 template<typename T>
 class LocalArray : public LocalPointerBase<T> {
 public:
     using LocalPointerBase<T>::operator*;
     using LocalPointerBase<T>::operator->;
     explicit LocalArray(T *p=NULL) : LocalPointerBase<T>(p) {}
     LocalArray(T *p, UErrorCode &errorCode) : LocalPointerBase<T>(p) {
         if(p==NULL && U_SUCCESS(errorCode)) {
             errorCode=U_MEMORY_ALLOCATION_ERROR;
         }
     }
     LocalArray(LocalArray<T> &&src) U_NOEXCEPT : LocalPointerBase<T>(src.ptr) {
         src.ptr=NULL;
     }

     explicit LocalArray(std::unique_ptr<T[]> &&p)
         : LocalPointerBase<T>(p.release()) {}

     ~LocalArray() {
         delete[] LocalPointerBase<T>::ptr;
     }
     LocalArray<T> &operator=(LocalArray<T> &&src) U_NOEXCEPT {
         delete[] LocalPointerBase<T>::ptr;
         LocalPointerBase<T>::ptr=src.ptr;
         src.ptr=NULL;
         return *this;
     }

     LocalArray<T> &operator=(std::unique_ptr<T[]> &&p) U_NOEXCEPT {
         adoptInstead(p.release());
         return *this;
     }

     void swap(LocalArray<T> &other) U_NOEXCEPT {
         T *temp=LocalPointerBase<T>::ptr;
         LocalPointerBase<T>::ptr=other.ptr;
         other.ptr=temp;
     }
     friend inline void swap(LocalArray<T> &p1, LocalArray<T> &p2) U_NOEXCEPT {
         p1.swap(p2);
     }
     void adoptInstead(T *p) {
         delete[] LocalPointerBase<T>::ptr;
         LocalPointerBase<T>::ptr=p;
     }
     void adoptInsteadAndCheckErrorCode(T *p, UErrorCode &errorCode) {
         if(U_SUCCESS(errorCode)) {
             delete[] LocalPointerBase<T>::ptr;
             LocalPointerBase<T>::ptr=p;
             if(p==NULL) {
                 errorCode=U_MEMORY_ALLOCATION_ERROR;
             }
         } else {
             delete[] p;
         }
     }
     T &operator[](ptrdiff_t i) const { return LocalPointerBase<T>::ptr[i]; }

     operator std::unique_ptr<T[]> () && {
         return std::unique_ptr<T[]>(LocalPointerBase<T>::orphan());
     }
 };

 #define U_DEFINE_LOCAL_OPEN_POINTER(LocalPointerClassName, Type, closeFunction) \
     class LocalPointerClassName : public LocalPointerBase<Type> { \
     public: \
         using LocalPointerBase<Type>::operator*; \
         using LocalPointerBase<Type>::operator->; \
         explicit LocalPointerClassName(Type *p=NULL) : LocalPointerBase<Type>(p) {} \
         LocalPointerClassName(LocalPointerClassName &&src) U_NOEXCEPT \
                 : LocalPointerBase<Type>(src.ptr) { \
             src.ptr=NULL; \
         } \
         /* TODO: Be agnostic of the deleter function signature from the user-provided std::unique_ptr? */ \
         explicit LocalPointerClassName(std::unique_ptr<Type, decltype(&closeFunction)> &&p) \
                 : LocalPointerBase<Type>(p.release()) {} \
         ~LocalPointerClassName() { if (ptr != NULL) { closeFunction(ptr); } } \
         LocalPointerClassName &operator=(LocalPointerClassName &&src) U_NOEXCEPT { \
             if (ptr != NULL) { closeFunction(ptr); } \
             LocalPointerBase<Type>::ptr=src.ptr; \
             src.ptr=NULL; \
             return *this; \
         } \
         /* TODO: Be agnostic of the deleter function signature from the user-provided std::unique_ptr? */ \
         LocalPointerClassName &operator=(std::unique_ptr<Type, decltype(&closeFunction)> &&p) { \
             adoptInstead(p.release()); \
             return *this; \
         } \
         void swap(LocalPointerClassName &other) U_NOEXCEPT { \
             Type *temp=LocalPointerBase<Type>::ptr; \
             LocalPointerBase<Type>::ptr=other.ptr; \
             other.ptr=temp; \
         } \
         friend inline void swap(LocalPointerClassName &p1, LocalPointerClassName &p2) U_NOEXCEPT { \
             p1.swap(p2); \
         } \
         void adoptInstead(Type *p) { \
             if (ptr != NULL) { closeFunction(ptr); } \
             ptr=p; \
         } \
         operator std::unique_ptr<Type, decltype(&closeFunction)> () && { \
             return std::unique_ptr<Type, decltype(&closeFunction)>(LocalPointerBase<Type>::orphan(), closeFunction); \
         } \
     }

 U_NAMESPACE_END

#endif  /* U_SHOW_CPLUSPLUS_API */
#endif  /* __LOCALPOINTER_H__ */
