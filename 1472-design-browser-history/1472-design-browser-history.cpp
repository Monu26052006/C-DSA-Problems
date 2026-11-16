class Node{
    public:
    string data;
    Node* prev;
    Node* next;
    Node(string x){
        data = x;
        next = NULL;
        prev= NULL;
    }
};


class BrowserHistory {
public:
    Node* current ;
    BrowserHistory(string homepage) {
        current = new Node(homepage);
    }
    
    void visit(string url) {
        Node* urlNode = new Node(url);
        urlNode->prev = current;
        current->next = urlNode;
        current = urlNode;
    }
    
    string back(int steps) {
        Node* trav = current;
        while(trav->prev != NULL && steps > 0){
            trav = trav->prev;
            steps--;
        }
        current = trav;
        return current->data;
    }
    
    string forward(int steps) {
        Node* trav = current;
        while(trav->next != NULL && steps>0){
            trav = trav->next;
            steps--;
        }
        current = trav;
        return current->data;
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */