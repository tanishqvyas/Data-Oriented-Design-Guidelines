#include<iostream>

using namespace std;

class node {
    public:
    node(int val): val{val} {}
    void set_next(node* n) {
        next = n;
    }
    bool is_next() {
        return next != nullptr;
    }
    node* next_ele() {
        return next;
    }
    int get_val() {
        return val;
    }
    private:
    int val;
    node *next;
};

class linked_list {
    public:
    linked_list() : head{nullptr} {}
    void insert(int val) {
        auto obj = new node(val);
        if (head == nullptr) {
            head = obj;
        }
        else {
            auto temp = head;
            while (temp -> is_next()) {
                temp = temp -> next_ele();
            }
            temp -> set_next(obj);
        }
    }

    void iterate() {
        auto temp = head;
        while (temp -> is_next()) {
            cout << temp -> get_val() << " ";
            temp = temp -> next_ele();
        }
        cout << endl;
    }

    private:
    node *head;
};

int main() {
    auto a = new int[1000];
    // linked_list obj;
    // for  (int i = 0; i < 1000; ++i) {
    //     obj.insert(i);
    // }
    // obj.iterate();

    for (int i = 0; i < 1000; ++i) 
    {
        cout << a[i] << " ";
    }
    cout << endl;
    // delete[] a;
    return 0;
}
