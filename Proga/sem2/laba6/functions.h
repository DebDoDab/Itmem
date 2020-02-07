//
// Created by vadim on 7.02.20.
//
#include <bits/stdc++.h>

using namespace std;

#pragma once

template <typename container>
bool allOf(const container& c, bool (&f)(int));

template <typename container>
bool anyOf(const container& c, bool (&f)(int));

template <typename container>
bool noneOf(const container& c, bool (&f)(int));

template <typename container>
bool oneOf(const container& c, bool (&f)(int));

template <typename container>
bool isSorted(const container& c, bool (&f)(int));

template <typename container>
bool isPartitioned(const container& c, bool (&f)(int));

template <class InputIterator, class object>
object findNot(InputIterator begin, InputIterator end, object value);

template <class InputIterator, class object>
object findBackward(InputIterator begin, InputIterator end, object value);

template <typename container>
bool isPalindrom(const container& c, bool (&f)(int));

#include "functions.tpp"