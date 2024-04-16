#include <iostream>
#include <unordered_set>
#include <queue>

using namespace std;

// Function to find page faults using FIFO
int pageFaults(int pages[], int n, int capacity) {
    unordered_set<int> s;
    queue<int> indexes;

    int page_faults = 0;
    for (int i = 0; i < n; i++) {
        if (s.size() < capacity) {
            if (s.find(pages[i]) == s.end()) {
                s.insert(pages[i]);
                page_faults++;
                indexes.push(pages[i]);
            }
        } else {
            if (s.find(pages[i]) == s.end()) {
                int val = indexes.front();
                indexes.pop();
                s.erase(val);
                s.insert(pages[i]);
                indexes.push(pages[i]);
                page_faults++;
            }
        }
    }

    return page_faults;
}

int main() {
    int pages[] = {7, 5, 1, 2, 4, 5, 0, 9, 1, 1, 2, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 9;
    cout << pageFaults(pages, n, capacity);
    return 0;
}
