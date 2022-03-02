#pragma once

#include <iostream>

using namespace std;

template <class T>
class List
{
protected:
    class Node
    {
    public:
        T data;
        Node* next;

        Node() : data(), next(nullptr) {};
        Node(const T& data_, Node* next_ = nullptr) : data(data_), next(next_) { };
    };

    Node* head;
    Node* last;

public:
    class Iter
    {
    private:
        Node* it;
    public:
        Iter(Node* it_) : it(it_) { };

        bool operator==(const Iter& other) const
        {
            if (this != &other)
            {
                return it == other.it;
            }
            else
            {
                return true;
            }
        }

        bool operator!=(const Iter& other) const
        {
            return !operator==(other);
        }

        T& operator*()
        {
            if (it)
            {
                return it->data;
            }
            else
            {
                throw "nullptr";
            }
        }

        Iter next() const
        {
            return Iter(it->next);
        }

        void operator++()
        {
            if (it)
            {
                it = it->next;
            }
            else
            {
                throw "nullptr";
            }
        }
    };

    List() : head(new Node()), last(head) {};

    List(const List& other) : head(new Node()), last(head)
    {
        for (List::Iter it = other.begin(); it != other.end(); ++it)
        {
            add(*it);
        }
    }

    ~List()
    {
        while (head->next != nullptr)
        {
            remove();
        }
        delete head;
    }

    List& operator=(const List& other)
    {
        List temp(other);
        swap(head, temp.head);
        return(*this);
    }

    size_t size() const
    {
        size_t s = 0;
        for (Iter it = begin(); it != end(); ++it)
        {
            s++;
        }
        return s;
    }

    void add(const T& data_)
    {
        Node* temp = new Node(data_);
        last->next = temp;
        last = temp;
    }

    void remove()
    {
        Node* temp = head->next;
        if (temp == last)
        {
            last = head;
        }
        head->next = head->next->next;
        delete temp;
    }

    void erase()
    {
        while (head->next != nullptr)
        {
            remove();
        }
    }

    Node* begin() const
    {
        return head->next;
    }

    Node* end() const
    {
        return nullptr;
    }

    friend ostream& operator<<(ostream& out, const List& other)
    {
        for (List::Iter it = other.begin(); it != other.end(); ++it)
        {
            out << *it << ' ';
        }
        return out;
    }
    
    friend Iter Get_Middle(const List& other)
    {
        Iter slow = other.begin();
        Iter fast = other.begin();

        while (fast != nullptr && fast.next() != nullptr)
        {
            ++slow;
            ++fast;
            ++fast;
        }

        return slow;
    }

    friend List Merge(const List& L1, const List& L2)
    {
        List temp;

        Iter it1 = L1.begin();
        Iter it2 = L2.begin();

        while (it1 != nullptr || it2 != nullptr)
        {
            if (it1 == nullptr)
            {
                temp.add(*it2);
                ++it2;
                continue;
            }

            if (it2 == nullptr || (*it1) >= (*it2))
            {
                temp.add(*it1);
                ++it1;
                continue;
            }

            if ((*it2) >= (*it1))
            {
                temp.add(*it2);
                ++it2;
                continue;
            }
        }

        return temp;
    }

    friend List Merge_Sort(const List& L)
    {
        if (L.size() < 2)
        {
            List temp(L);
            return temp;
        }

        Iter mid = Get_Middle(L);

        List left_list;
        List right_list;
        Iter it = L.begin();

        while (it != mid)
        {
            left_list.add(*it);
            ++it;
        }
        while (it != nullptr)
        {
            right_list.add(*it);
            ++it;
        }

        left_list = Merge_Sort(left_list);
        right_list = Merge_Sort(right_list);

        return Merge(left_list, right_list);
    }
};