
#include <iostream>
using namespace std;

// Class for song with title, artist, and duration
class Song {

public:
    string title;
    string artist;
    int duration;

    Song(string t = "", string a = "", int d = 0) : title(t), artist(a), duration(d) {}

};

// Node structure for Doubly Linked List
struct DNode {

    Song data;

    DNode* prev;
    DNode* next;

    DNode(Song s) : data(s), prev(nullptr), next(nullptr) {}

};


// Playlist class using Doubly Linked List
class Playlist {

private:
    DNode* head;
    DNode* tail;

    int size;


public:


    Playlist() : head(nullptr), tail(nullptr), size(0) {}

    // Add song to end of playlist
    void addSong(Song s) {
        DNode* newNode = new DNode(s);

        if (!head) head = tail = newNode;

        else {
            tail->next = newNode;
            
            newNode->prev = tail;
            tail = newNode;

        }
        size++;


    }

    // Remove song by title
    bool removeSong(string title) {


        DNode* current = head;
        while (current) {


            if (current->data.title == title) {

                if (current->prev) current->prev->next = current->next;

                else head = current->next;

                if (current->next) current->next->prev = current->prev;

                else tail = current->prev;
                delete current;

                size--;

                return true;
            }
            current = current->next;
        }
        return false;

    }


    // Display all songs in playlist

    void display() {
        DNode* current = head;

        while (current) {
            cout << "Title: " << current->data.title << "\nArtist: " << current->data.artist

                      << "\nDuration: " << current->data.duration << "s\n\n";
            current = current->next;
        }

    }


    DNode* getHead() { return head; }

    int getSize() { return size; }

    // Merge Sort


    void mergeSort() {
        head = mergeSortRec(head);

        DNode* temp = head;

        while (temp && temp->next) temp = temp->next;
        tail = temp;

    }


private:
    // Recursive merge sort helper

    DNode* mergeSortRec(DNode* h) {
        if (!h || !h->next) return h;


        DNode* mid = split(h);

        DNode* left = mergeSortRec(h);

        DNode* right = mergeSortRec(mid);


        return merge(left, right);
    }

    // Split the list into two halves
    DNode* split(DNode* h) {
        DNode* fast = h->next;

        DNode* slow = h;

        while (fast && fast->next) {

            fast = fast->next->next;

            slow = slow->next;
        }
        DNode* mid = slow->next;

        slow->next = nullptr;
        return mid;
    }

    // Merge two sorted lists
    DNode* merge(DNode* left, DNode* right) {
        if (!left) return right;

        if (!right) return left;

        if (left->data.title <= right->data.title) {

            left->next = merge(left->next, right);


            left->next->prev = left;
            left->prev = nullptr;

            return left;
        } else {
            right->next = merge(left, right->next);


            right->next->prev = right;
            right->prev = nullptr;

            return right;

        }
    }


public:
    // Bubble Sort implementation (Sorting Algorithm 2)
    void bubbleSort() {
        if (!head) return;

        bool swapped;
        DNode* ptr;

        DNode* lptr = nullptr;
        do {

            swapped = false;
            ptr = head;
            while (ptr->next != lptr) {


                if (ptr->data.duration > ptr->next->data.duration) {
                    swap(ptr->data, ptr->next->data);

                    swapped = true;

                }
                ptr = ptr->next;
            }
            lptr = ptr;
        } while (swapped);
    }

};


// Stack implementation using Singly Linked List for recent songs

struct SNode {

    Song data;

    SNode* next;

    SNode(Song s) : data(s), next(nullptr) {}
};

class RecentSongs {

private:
    SNode* top;


public:
    RecentSongs() : top(nullptr) {}


    // Add song to top of stack

    void push(Song s) {
        SNode* newNode = new SNode(s);


        newNode->next = top;
        top = newNode;
    }

    // Remove song from top of stack

    Song pop() {
        if (!top) throw runtime_error("Stack is empty");

        SNode* temp = top;

        Song s = temp->data;

        top = top->next;


        delete temp;
        return s;
    }

    bool isEmpty() { return top == nullptr; }



    // Display recent songs

    void display() {
        SNode* current = top;

        while (current) {
            cout << "Title: " << current->data.title << "\nArtist: " << current->data.artist


                      << "\nDuration: " << current->data.duration << "s\n\n";

            current = current->next;

        }
    }
};


// Double-Ended Queue (Deque) implementation using Doubly Linked List
struct QNode {

    Song data;

    QNode* prev;

    QNode* next;

    QNode(Song s) : data(s), prev(nullptr), next(nullptr) {}
};


class Deque {
private:
    QNode* front;

    QNode* rear;

public:
    Deque() : front(nullptr), rear(nullptr) {}

    // Add to front of deque

    void addFront(Song s) {

        QNode* newNode = new QNode(s);

        if (!front) front = rear = newNode;
        else {
            newNode->next = front;

            front->prev = newNode;

            front = newNode;
        }
    }


    // Add to rear of deque

    void addRear(Song s) {
        QNode* newNode = new QNode(s);

        if (!rear) front = rear = newNode;

        else {
            rear->next = newNode;

            newNode->prev = rear;

            rear = newNode;
        }
    }

    // Remove from front of deque

    Song removeFront() {


        if (!front) throw runtime_error("Deque is empty");
        QNode* temp = front;

        Song s = temp->data;

        front = front->next;
        if (front) front->prev = nullptr;

        else rear = nullptr;

        delete temp;

        return s;
    }

    // Remove from rear of deque
    Song removeRear() {
        if (!rear) throw runtime_error("Deque is empty");

        QNode* temp = rear;


        Song s = temp->data;

        rear = rear->prev;

        if (rear) rear->next = nullptr;

        else front = nullptr;
        delete temp;

        return s;
    }


    bool isEmpty() { return front == nullptr; }


    // Display deque contents

    void display() {

        QNode* current = front;

        while (current) {

            cout << "Title: " << current->data.title << "\nArtist: " << current->data.artist

                      << "\nDuration: " << current->data.duration << "s\n\n";

            current = current->next;
        }
    }
};


// Linear Search implementation (Searching Algorithm 1)

Song* linearSearch(Playlist& p, string title) {

    DNode* current = p.getHead();

    while (current) {


        if (current->data.title == title) return &(current->data);

        current = current->next;

    }
    return nullptr;
}

// Binary Search implementation (Searching Algorithm 2)

Song* binarySearch(Playlist& p, string title) {

    int size = p.getSize();

    Song* arr = new Song[size];

    DNode* current = p.getHead();

    for (int i = 0; i < size; i++) {

        arr[i] = current->data;

        current = current->next;
    }

    int left = 0, right = size - 1;

    while (left <= right) {

        int mid = left + (right - left) / 2;
        if (arr[mid].title == title) {


            Song* result = new Song(arr[mid]);

            delete[] arr;
            return result;
        }
        if (arr[mid].title < title) left = mid + 1;

        else right = mid - 1;
    }

    delete[] arr;
    return nullptr;
}


int main() {

    Playlist playlist;

    RecentSongs recent;

    Deque playQueue;
    int choice;

    do {
        cout << "\nMusic Playlist Manager\n1. Add Song\n2. Remove Song\n3. Display Playlist\n4. Play Next (Deque)\n5. Undo Play (Stack)\n6. Merge Sort by Title\n7. Bubble Sort by Duration\n8. Linear Search\n9. Binary Search\n10. Recent Songs\n11. Add to Queue Front\n12. Add to Queue Rear\n13. Display Queue\n14. Exit\nEnter choice: ";

        
        cin >> choice;

        cin.ignore();


        switch (choice) {
            case 1: {
                string t, a;

                int d;
                cout << "Title: ";
                getline(cin, t);

                cout << "Artist: ";
                getline(cin, a);

                cout << "Duration (s): ";
                cin >> d;

                playlist.addSong(Song(t, a, d));

                break;
            }
            case 2: {
                string t;

                cout << "Title to remove: ";
                getline(cin, t);

                if (playlist.removeSong(t)) cout << "Song removed.\n";

                else cout << "Song not found.\n";
                break;

            }
            case 3:
                playlist.display();
                break;
            case 4:
                if (!playQueue.isEmpty()) {

                    Song s = playQueue.removeFront();

                    recent.push(s);
                    cout << "Playing: " << s.title << "\n";
                } else cout << "Queue is empty.\n";
                break;
            case 5:
                if (!recent.isEmpty()) {
                    Song s = recent.pop();

                    playQueue.addFront(s);
                    cout << "Playing previous: " << s.title << "\n";
                } else cout << "No recent songs.\n";

                break;

            case 6:
                playlist.mergeSort();

                cout << "Playlist sorted by title.\n";
                break;

            case 7:

                playlist.bubbleSort();

                cout << "Playlist sorted by duration.\n";
                break;

            case 8: {
                string t;
                cout << "Title to search: ";
                getline(cin, t);


                Song* s = linearSearch(playlist, t);
                if (s) cout << "Found: " << s->title << " by " << s->artist << "\n";
                else cout << "Not found.\n";

                break;
            }

            case 9: {
                string t;
                cout << "Title to search: ";
                getline(cin, t);

                Song* s = binarySearch(playlist, t);

                if (s) {
                    cout << "Found: " << s->title << " by " << s->artist << "\n";
                    delete s;


                } else cout << "Not found.\n";
                break;
            }

            case 10:

                recent.display();
                break;

            case 11: {

                string t;
                cout << "Title to queue front: ";

                getline(cin, t);

                Song* s = linearSearch(playlist, t);

                if (s) playQueue.addFront(*s);

                else cout << "Song not found.\n";

                break;
            }
            case 12: {

                string t;
                cout << "Title to queue rear: ";

                getline(cin, t);
                Song* s = linearSearch(playlist, t);

                if (s) playQueue.addRear(*s);

                else cout << "Song not found.\n";
                break;
            }
            case 13:

                playQueue.display();

                break;
            case 14:

                cout << "Exiting...\n";
                break;

            default:

                cout << "Invalid choice.\n";
        }
    } while (choice != 14);

    return 0;
}
