#pragma once

// Implements the REI rules of the RAII standard
#define IMPLEMENT_REI(on_class)\
on_class(const on_class&) = delete;\
on_class& operator=(const on_class&) = delete;\
on_class(on_class&&) = delete;\
on_class& operator=(on_class&&) = delete