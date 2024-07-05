#ifndef LINKLIST_H
#define LINKLIST_H

template <class T>
class Node {
private:
    T data;
    Node<T>* nextNode;
    Node<T> * previousNode;

public:
    Node(T data){
        nextNode = nullptr;
        previousNode = nullptr;
        this->data = data;
    }

    /// Setters
    void setData(T data) {
        this->data = data;
    }
    void setNextNode(Node<T> * nextNode){
        this->nextNode = nextNode;
    }
    void setPreviousNode(Node<T> * previousNode){
        this->previousNode = previousNode;
    }

    /// Getters
    T getData(){
        return data;
    }
    Node* getNextNode(){
        return nextNode;
    }
    Node * getPreviousNode(){
        return previousNode;
    }

};

template <class T>
class LinkList {
private:
    Node<T> * headNode;
    Node<T> * tailNode;
    int size;

public:
    LinkList<T>() {
        size = 0;
        headNode = nullptr;
        tailNode = nullptr;
    }
    // LinkList<T>(LinkList const& d) {

    //     this->size = 0;
    //     this->headNode = nullptr;
    //     this->tailNode = nullptr;

    //     Node<T> *tmp = d.tailNode;

    //     while (tmp != nullptr) {
    //         this->pushBack(tmp->getData());
    //         tmp = tmp->getNextNode();
    //     }

    // }

    /// Push Back
    void pushBack(T data){
        Node<T> *tmp = new Node<T> (data);
        tmp->setPreviousNode(tailNode);

        if (tailNode != nullptr)
            tailNode->setNextNode(tmp);

        tmp->setNextNode(nullptr);
        tailNode = tmp;
        size++;

        if (headNode == nullptr)
            headNode = tmp;

    }

    ///Pop Back
    bool popBack(){
        if (size != 0) {
            Node<T> * tmp = tailNode;

            if (tmp->getPreviousNode() != nullptr) {
                tailNode = tmp->getPreviousNode();
                tailNode->setNextNode(nullptr);

            } else {
                headNode = nullptr;
                tailNode = nullptr;
            }
            delete tmp;
            size --;
            return true;
        }

        return false;
    }

    /// Getter
    Node<T> * getTailNode(){
        return tailNode;
    }
    Node<T> * getHeadNode(){
        return headNode;
    }
    int getSize() {
        return size;
    }

    /// Setters
    void setHeadNode(Node<T>* data){
        headNode = data;
    }

    bool find(T data) {
        Node<T> *tmp = getHeadNode();
        while (tmp) {
            if (tmp->data == data)
                return true;
            tmp = tmp->getNextNode();
        }
        return false ;
    }

    void operator << (T data) {
        this->pushBack(data);
    }
};


#endif // LINKLIST_H
