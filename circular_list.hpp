#ifndef CIRCULAR_HPP
#define CIRCULAR_HPP

#include <memory>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

template <typename T>
class CircularList 
{
    private:
        struct Node 
        {
            T data;
            Node* next;
            Node* prev;
            Node(const T& value);
        };

        Node* head;
        size_t count;

        void clear_nodes();
        void copy_nodes(const CircularList& other);

    public:
        CircularList();
        CircularList(const CircularList& other);
        CircularList(CircularList&& other) noexcept;
        CircularList(std::initializer_list<T> init);
        explicit CircularList(size_t n, const T& value = T());
        template<typename InputIterator>
        CircularList(InputIterator first, InputIterator last);
        ~CircularList();

        CircularList& operator=(const CircularList& other);
        CircularList& operator=(CircularList&& other) noexcept;
        CircularList& operator=(std::initializer_list<T> init);

        class iterator;
        class const_iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;
        const_reverse_iterator crbegin() const;
        const_reverse_iterator crend() const;

        size_t size() const;
        bool empty() const;

        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        void push_back(const T& value);
        void push_front(const T& value);
        void pop_back();
        void pop_front();
        void clear();
        iterator insert(iterator pos, const T& value);
        iterator erase(iterator pos);
        void assign(size_t n, const T& value);
    
        template<typename InputIterator>
        void assign(InputIterator first, InputIterator last);
    
        void assign(std::initializer_list<T> init);
        void swap(CircularList& other) noexcept;

        bool operator==(const CircularList& other) const;
        bool operator!=(const CircularList& other) const;
        bool operator<(const CircularList& other) const;
        bool operator>(const CircularList& other) const;
        bool operator<=(const CircularList& other) const;
        bool operator>=(const CircularList& other) const;

        class iterator 
        {
            public:
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type = T;
                using difference_type = std::ptrdiff_t;
                using pointer = T*;
                using reference = T&;

                iterator(Node* n = nullptr, Node* h = nullptr);
                reference operator*() const;
                pointer operator->() const;
                iterator& operator++();
                iterator operator++(int);
                iterator& operator--();
                iterator operator--(int);
                bool operator==(const iterator& other) const;
                bool operator!=(const iterator& other) const;
        
            private:
                Node* node;
                Node* head;
                friend class CircularList;
        };

        class const_iterator 
        {
            public:
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type = const T;
                using difference_type = std::ptrdiff_t;
                using pointer = const T*;
                using reference = const T&;

                const_iterator(Node* n = nullptr, Node* h = nullptr);
                const_iterator(const iterator& it);
                reference operator*() const;
                pointer operator->() const;
                const_iterator& operator++();
                const_iterator operator++(int);
                const_iterator& operator--();
                const_iterator operator--(int);
                bool operator==(const const_iterator& other) const;
                bool operator!=(const const_iterator& other) const;

            private:
                const Node* node;
                const Node* head;
                friend class CircularList;
        };
};

#endif
