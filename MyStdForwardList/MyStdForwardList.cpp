#include <iostream>

namespace my_std {
    template<typename T>
    class MyForwardList {
    private:
        T* head;
    public:
        struct Node {
            T data;
            Node* next = nullptr;
        };

        MyForwardList() {
            //data = static_cast<T*>(operator new(sizeof(T)));
        }
        ~MyForwardList() {
            //operator delete (data);
        }

        void push_front() {

        }
        void insertAtBeginning() {

        }
        void insertAfter() {

        }
        void deleteAtBeginning() {

        }
        void deleteAtEnd() {

        }
        void display() {

        }
        bool isEmpty() {
            
        }
        T* getHead() {

        }
    };
}

int main()
{
    //my_std::MyForwardList<int> forward_list;

    return 0;
}
