#ifndef CIRCULAR_HPP
#define CIRCULAR_HPP

#include <memory>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

/* ======== CIRCULAR LIST DECLARATION ======== */

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

/* ======== CIRCULAR LIST IMPLEMENTATION ======== */

template <typename T>
CircularList<T>::Node::Node(const T& value):
    data(value), next(this), prev(this) {}


template <typename T>
void CircularList<T>::clear_nodes()
{
    if (!head) return;
    
    Node* current = head;
    for (size_t i = 0; i < count; ++i)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    count = 0;
}

template <typename T>
void CircularList<T>::copy_nodes(const CircularList& other)
{
    if (!other.head) return;
    
    Node* other_current = other.head;
    for (size_t i = 0; i < other.count; ++i) 
    {
        push_back(other_current->data);
        other_current = other_current->next;
    }
}

template <typename T>
CircularList<T>::CircularList():
    head(nullptr), count(0) {}

template <typename T>
CircularList<T>::CircularList(const CircularList& other):
    head(nullptr), count(0) 
{
    copy_nodes(other);
}

template <typename T>
CircularList<T>::CircularList(CircularList&& other) noexcept:
    head(other.head), count(other.count) 
{
    other.head = nullptr;
    other.count = 0;
}

template <typename T>
CircularList<T>::CircularList(std::initializer_list<T> init)
    : head(nullptr), count(0) 
{
    for (const auto& value : init)
    {
        push_back(value);
    }
}

template <typename T>
CircularList<T>::~CircularList()
{
    clear_nodes();
}

template <typename T>
CircularList<T>& CircularList<T>::operator=(const CircularList& other)
{
    if (this != &other) 
    {
        clear_nodes();
        copy_nodes(other);
    }
    return *this;
}

template <typename T>
CircularList<T>& CircularList<T>::operator=(CircularList&& other) noexcept
{
    if (this != &other) 
    {
        clear_nodes();
        head = other.head;
        count = other.count;
        other.head = nullptr;
        other.count = 0;
    }
    return *this;
}

template <typename T>
CircularList<T>& CircularList<T>::operator=(std::initializer_list<T> init)
{
    clear_nodes();
    for (const auto& value : init) 
    {
        push_back(value);
    }
    return *this;
}

template <typename T>
typename CircularList<T>::iterator CircularList<T>::begin()
{
    return iterator(head, head);
}

template <typename T>
typename CircularList<T>::iterator CircularList<T>::end()
{
    return iterator(nullptr, head);
}

template <typename T>
typename CircularList<T>::const_iterator CircularList<T>::begin() const
{
    return const_iterator(head, head);
}

template <typename T>
typename CircularList<T>::const_iterator CircularList<T>::end() const
{
    return const_iterator(nullptr, head);
}

template <typename T>
typename CircularList<T>::const_iterator CircularList<T>::cbegin() const
{
    return const_iterator(head, head);
}

template <typename T>
typename CircularList<T>::const_iterator CircularList<T>::cend() const
{
    return const_iterator(nullptr, head);
}

template <typename T>
typename CircularList<T>::reverse_iterator CircularList<T>::rbegin()
{
    return reverse_iterator(end());
}

template <typename T>
typename CircularList<T>::reverse_iterator CircularList<T>::rend()
{
    return reverse_iterator(begin());
}

template <typename T>
typename CircularList<T>::const_reverse_iterator CircularList<T>::rbegin() const
{
    return const_reverse_iterator(end());
}

template <typename T>
typename CircularList<T>::const_reverse_iterator CircularList<T>::rend() const
{
    return const_reverse_iterator(begin());
}

template <typename T>
typename CircularList<T>::const_reverse_iterator CircularList<T>::crbegin() const
{
    return const_reverse_iterator(cend());
}

template <typename T>
typename CircularList<T>::const_reverse_iterator CircularList<T>::crend() const
{
    return const_reverse_iterator(cbegin());
}

template <typename T>
size_t CircularList<T>::size() const
{
    return count;
}

template <typename T>
bool CircularList<T>::empty() const
{
    return count == 0;
}

template <typename T>
T& CircularList<T>::front()
{
    if (empty()) throw std::runtime_error("CircularList is empty");
    return head->data;
}

template <typename T>
const T& CircularList<T>::front() const
{
    if (empty()) throw std::runtime_error("CircularList is empty");
    return head->data;
}

template <typename T>
T& CircularList<T>::back()
{
    if (empty()) throw std::runtime_error("CircularList is empty");
    return head->prev->data;
}

template <typename T>
const T& CircularList<T>::back() const
{
    if (empty()) throw std::runtime_error("CircularList is empty");
    return head->prev->data;
}

template <typename T>
void CircularList<T>::push_back(const T& value)
{
    Node* new_node = new Node(value);
    
    if (empty())
    {
        head = new_node;
    }
    else
    {
        new_node->next = head;
        new_node->prev = head->prev;
        head->prev->next = new_node;
        head->prev = new_node;
    }
    count++;
}

template <typename T>
void CircularList<T>::push_front(const T& value)
{
    push_back(value);
    head = head->prev;
}

template <typename T>
void CircularList<T>::pop_back()
{
    if (empty()) throw std::runtime_error("CircularList is empty");
    
    if (count == 1)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Node* last = head->prev;
        last->prev->next = head;
        head->prev = last->prev;
        delete last;
    }
    count--;
}

template <typename T>
void CircularList<T>::pop_front()
{
    if (empty()) throw std::runtime_error("CircularList is empty");
    
    if (count == 1)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Node* old_head = head;
        head = head->next;
        old_head->prev->next = head;
        head->prev = old_head->prev;
        delete old_head;
    }
    count--;
}

template <typename T>
void CircularList<T>::clear()
{
    clear_nodes();
}

template <typename T>
typename CircularList<T>::iterator CircularList<T>::insert(iterator pos, const T& value)
{
    if (pos == end())
    {
        push_back(value);
        return iterator(head->prev, head);
    }
    
    Node* new_node = new Node(value);
    Node* current = pos.node;
    
    new_node->next = current;
    new_node->prev = current->prev;
    current->prev->next = new_node;
    current->prev = new_node;
    
    if (current == head)
    {
        head = new_node;
    }
    
    count++;
    return iterator(new_node, head);
}

template <typename T>
typename CircularList<T>::iterator CircularList<T>::erase(iterator pos)
{
    if (empty() || pos == end())
    {
        return end();
    }
    
    Node* to_delete = pos.node;
    Node* next_node = to_delete->next;
    
    if (count == 1)
    {
        head = nullptr;
    }
    else
    {
        to_delete->prev->next = to_delete->next;
        to_delete->next->prev = to_delete->prev;
        
        if (to_delete == head)
        {
            head = next_node;
        }
    }
    
    delete to_delete;
    count--;
    
    return iterator(next_node == to_delete ? nullptr : next_node, head);
}

template <typename T>
void CircularList<T>::assign(size_t n, const T& value)
{
    clear();
    for (size_t i = 0; i < n; ++i)
    {
        push_back(value);
    }
}

template <typename T>
void CircularList<T>::assign(std::initializer_list<T> init) 
{
    clear();
    for (const auto& value : init) 
    {
        push_back(value);
    }
}

template <typename T>
void CircularList<T>::swap(CircularList& other) noexcept
{
    std::swap(head, other.head);
    std::swap(count, other.count);
}

template <typename T>
bool CircularList<T>::operator==(const CircularList& other) const
{
    if (count != other.count) return false;
    
    auto it1 = begin();
    auto it2 = other.begin();
    
    for (size_t i = 0; i < count; ++i) {
        if (*it1 != *it2) return false;
        ++it1;
        ++it2;
    }
    return true;
}

template <typename T>
bool CircularList<T>::operator!=(const CircularList& other) const
{
    return !(*this == other);
}

template <typename T>
bool CircularList<T>::operator<(const CircularList& other) const
{
    return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
}

template <typename T>
bool CircularList<T>::operator>(const CircularList& other) const
{
    return other < *this;
}

template <typename T>
bool CircularList<T>::operator<=(const CircularList& other) const
{
    return !(other < *this);
}

template <typename T>
bool CircularList<T>::operator>=(const CircularList& other) const
{
    return !(*this < other);
}

/* ======== ITERATOR IMPLEMENTATION ======== */
template <typename T>
CircularList<T>::iterator::iterator(Node* n, Node* h):
    node(n), head(h) {}

template <typename T>
typename CircularList<T>::iterator::reference 
CircularList<T>::iterator::operator*() const
{
    if (!node) throw std::runtime_error("Dereferencing end iterator");
    return node->data;
}

template <typename T>
typename CircularList<T>::iterator::pointer 
CircularList<T>::iterator::operator->() const
{
    if (!node) throw std::runtime_error("Dereferencing end iterator");
    return &node->data;
}

template <typename T>
typename CircularList<T>::iterator& 
CircularList<T>::iterator::operator++()
{
    if (!node) throw std::runtime_error("Incrementing end iterator");
    node = node->next;
    if (node == head) node = nullptr;
    return *this;
}

template <typename T>
typename CircularList<T>::iterator 
CircularList<T>::iterator::operator++(int)
{
    iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename CircularList<T>::iterator& 
CircularList<T>::iterator::operator--()
{
    if (!node)
    {
        if (!head) throw std::runtime_error("Decrementing end iterator of empty list");
        node = head->prev;
    }
    else
    {
        node = node->prev;
        if (node == head->prev) node = nullptr;
    }
    return *this;
}

template <typename T>
typename CircularList<T>::iterator 
CircularList<T>::iterator::operator--(int)
{
    iterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
bool CircularList<T>::iterator::operator==(const iterator& other) const
{
    return node == other.node;
}

template <typename T>
bool CircularList<T>::iterator::operator!=(const iterator& other) const
{
    return !(*this == other);
}

/* ======== CONST_ITERATOR IMPLEMENTATION ======== */

template <typename T>
CircularList<T>::const_iterator::const_iterator(Node* n, Node* h):
    node(n), head(h) {}

template <typename T>
CircularList<T>::const_iterator::const_iterator(const iterator& it):
    node(it.node), head(it.head) {}

template <typename T>
typename CircularList<T>::const_iterator::reference 
CircularList<T>::const_iterator::operator*() const
{
    if (!node) throw std::runtime_error("Dereferencing end iterator");
    return node->data;
}

template <typename T>
typename CircularList<T>::const_iterator::pointer 
CircularList<T>::const_iterator::operator->() const
{
    if (!node) throw std::runtime_error("Dereferencing end iterator");
    return &node->data;
}

template <typename T>
typename CircularList<T>::const_iterator& 
CircularList<T>::const_iterator::operator++()
{
    if (!node) throw std::runtime_error("Incrementing end iterator");
    node = node->next;
    if (node == head) node = nullptr;
    return *this;
}

template <typename T>
typename CircularList<T>::const_iterator 
CircularList<T>::const_iterator::operator++(int)
{
    const_iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename CircularList<T>::const_iterator& 
CircularList<T>::const_iterator::operator--()
{
    if (!node) {
        if (!head) throw std::runtime_error("Decrementing end iterator of empty list");
        node = head->prev;
    } else {
        node = node->prev;
        if (node == head->prev) node = nullptr;
    }
    return *this;
}

template <typename T>
typename CircularList<T>::const_iterator 
CircularList<T>::const_iterator::operator--(int)
{
    const_iterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
bool CircularList<T>::const_iterator::operator==(const const_iterator& other) const
{
    return node == other.node;
}

template <typename T>
bool CircularList<T>::const_iterator::operator!=(const const_iterator& other) const
{
    return !(*this == other);
}
#endif
