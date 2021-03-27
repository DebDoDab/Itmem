//
// Created by vadim on 7.02.20.
//
#include <bits/stdc++.h>

using namespace std;

#pragma once

template <typename container, class object>
bool allOf(const container& c, bool (&f)(object));

template <typename container, class object>
bool anyOf(const container& c, bool (&f)(object));

template <typename container, class object>
bool noneOf(const container& c, bool (&f)(object));

template <typename container, class object>
bool oneOf(const container& c, bool (&f)(object));

template <class InputIterator, class object>
bool isSorted(const InputIterator& begin, const InputIterator& end, bool (&f)(object, object));

template <typename container, class object>
bool isPartitioned(const container& c, bool (&f)(object));

template <class InputIterator, class object>
object findNot(const InputIterator& begin, const InputIterator& end, object value);

template <class InputIterator, class object>
object findBackward(const InputIterator& begin, const InputIterator& end, object value);

template <typename container, class object>
bool isPalindrome(const container& c, bool (&f)(object));

#include "functions.tpp"