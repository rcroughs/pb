/**
 * Copyright (c) 2024 Romain Croughs (romain.croughs@gmail.com)
 *
 * Distributed under the MIT License.
 * (See accompanying file LICENSE or copy at https://opensource.org/licenses/MIT)
 *
 * See GitHub repository: https://www.github.com/rcroughs/pb
 * For any issues, please submit on GitHub at https://www.github.com/rcroughs/pb/issues
 *
 * pb.hpp
 */

#include <iostream>
#include <functional>

class pb_style {
public:
    pb_style(std::string left, std::string right, std::string fill, std::string empty, std::string pointer, int size = 100, bool percents = true, std::string desc = "") : _left(left), _right(right), _fill(fill), _empty(empty), _pointer(pointer), _size(size), _percents{percents}, _desc{desc} {};

    std::string left() { return _left; }
    std::string right() { return _right; }
    std::string fill() { return _fill; }
    std::string empty() { return _empty; }
    std::string pointer() { return _pointer; }

    void print(int current, int end) {
        float progress = (float)current / end * 100;
        int pos = _size * progress / 100;
        if (_last_position == pos) return;
        _desc != "" ? std::cout << _desc << " " : std::cout << "";
        std::cout << left();
        for (int i = 0; i < _size; ++i) {
            std::cout << _color(progress);
            if (i < pos) std::cout << fill();
            else if (i == pos) std::cout << pointer();
            else std::cout << empty();
            std::cout << "\033[0m";
        }
        std::cout << right();
        if (_percents)
            std::cout << int(progress) << " %";
        std::cout << "\r";
        std::cout.flush();
        _last_position = pos;  
    }

private:
    bool _percents;
    int _last_position = 0;
    int _size;
    std::string _left;
    std::string _right;
    std::string _fill;
    std::string _empty;
    std::string _pointer;
    std::function<std::string(float)> _color = [](float progress) -> std::string {
        if (progress < 33) return "\033[31m";
        else if (progress < 66) return "\033[33m";
        else return "\033[32m";
    };
    std::string _desc;
};

template <class T>
class pb {
public:
    pb(T item, pb_style style) : _item(item), _style(style) {
        _steps  = std::distance(_item.begin(), _item.end());
    };

    pb(T item) : pb(item, pb_style("[", "]", "=", " ", ">", 70, false)) {};

    class iterator {
    public:
        iterator(typename T::iterator iterator, int current, int size, pb_style& style) : _iterator(iterator), _step{current}, _size{size}, _style{style} {};
        typename T::iterator& operator*() { return _iterator; }
        iterator& operator++ () { 
            _iterator++; 
            _step++;
            _style.print(_step, _size);
            return *this;
        }
        bool operator!= (const iterator& other) { return _iterator != other._iterator; }
    private:
        typename T::iterator _iterator;
        int _step;
        int _size;
        pb_style& _style;
    };

    iterator begin() { return iterator(_item.begin(), 0, _steps, _style); }
    iterator end() { return iterator(_item.end(), _steps, _steps, _style); }
    iterator rbegin() { return iterator(_item.rbegin(), 0, _steps, _style); }
    iterator rend() { return iterator(_item.rend(), _steps, _steps, _style); }

private:
    T _item;
    int _steps;
    pb_style _style;
};