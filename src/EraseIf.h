#pragma once
namespace std {

    // for std::string
    template <class charT, class traits, class A, class Predicate>
    void erase_if(basic_string<charT, traits, A>& c, Predicate pred);

    // for std::deque
    template <class T, class A, class Predicate>
    void erase_if(deque<T, A>& c, Predicate pred);

    // for std::vector
    template <class T, class A, class Predicate>
    void erase_if(vector<T, A>& c, Predicate pred);

    // for std::list
    template <class T, class A, class Predicate>
    void erase_if(list<T, A>& c, Predicate pred);

    // for std::forward_list
    template <class T, class A, class Predicate>
    void erase_if(forward_list<T, A>& c, Predicate pred);
    // for std::map
    template <class K, class T, class C, class A, class Predicate>
    void erase_if(map<K, T, C, A>& c, Predicate pred);

    // for std::multimap
    template <class K, class T, class C, class A, class Predicate>
    void erase_if(multimap<K, T, C, A>& c, Predicate pred);

    // for std::set
    template <class K, class C, class A, class Predicate>
    void erase_if(set<K, C, A>& c, Predicate pred);

    // for std::multiset
    template <class K, class C, class A, class Predicate>
    void erase_if(multiset<K, C, A>& c, Predicate pred);

    // for std::unordered_map
    template <class K, class T, class H, class P, class A, class Predicate>
    void erase_if(unordered_map<K, T, H, P, A>& c, Predicate pred);

    // for std::unordered_multimap
    template <class K, class T, class H, class P, class A, class Predicate>
    void erase_if(unordered_multimap<K, T, H, P, A>& c, Predicate pred);
    // for std::unordered_set
    template <class K, class H, class P, class A, class Predicate>
    void erase_if(unordered_set<K, H, P, A>& c, Predicate pred);

    // for std::unordered_multiset
    template <class K, class H, class P, class A, class Predicate>
    void erase_if(unordered_multiset<K, H, P, A>& c, Predicate pred);

} // namespace std	