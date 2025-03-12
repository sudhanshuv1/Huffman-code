#include<iostream>
#include<iterator>


template<typename T>
class LinkedList
{
protected:
    T *head;
public:
    LinkedList() : head(NULL) {}
    virtual void insertNode(T*);
    virtual T* removeNode();
    int sz();
    void reverseList();
    T *getHead();
    void setHead(T*);
};

template<typename T>
void LinkedList<T>::insertNode(T* t)
{
    if(head == NULL)
        head = t;
    else{
        T *temp = head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = t;
    }
    return;
}

template<typename T>
void LinkedList<T>::reverseList()
{
    T *current = head, *previous = NULL, *temp = head;
    while(current != NULL)
    {
        temp = current->next;
        current->next = previous;
        previous = current;
        current = temp;
    }
    head = previous;
    return;
}

template<typename T>
int LinkedList<T>::sz()
{
    int counter = 0;
    T* nd = head;
    while(nd != NULL)
    {
        ++counter;
        nd = nd->next;
    }
    return counter;
}

template<typename T>
T* LinkedList<T>::getHead()
{
    return head;
}

template<typename T>
void LinkedList<T>::setHead(T *nd)
{
    head = nd;
    return;
}

template<typename T>
T* LinkedList<T>::removeNode()
{
    T *nd = head, *previous = head;
    while(nd->next != NULL)
        {
            previous = nd;
            nd = nd->next;
        }
    T *temp = nd;
    if(previous == nd)
        head = NULL;
    else
        previous->next = NULL;
    return nd;
}


struct codeType
{
    char info = '\0';
    codeType *next = NULL;
};

codeType* getCode()
{
    codeType *ct = new codeType;
    return ct;
}

void freeCode(codeType *ct)
{
    delete ct;
    return;
}

LinkedList<codeType> tempList;


template<typename T>
struct charType
{
    char symbol = '\0';
    LinkedList<codeType> code;
    double frequency = 0.0;
    charType *next = NULL;
    T *treeNode = NULL;
};


class Node
{
private:
    charType<Node> *ct;
    Node *parent, *left, *right;
public:
    Node *next;
    bool isLeft;
    double relFrequency;
    Node(): ct(NULL), parent(NULL), left(NULL),
            right(NULL), isLeft(false), relFrequency(0.0), next(NULL) {}
    ~Node();
    void setLeft(Node*);
    void setRight(Node*);
    bool isLeaf();
    Node *accessParent();
    void setParent(Node*);
    void setCharType(charType<Node>*);
};

void Node::setLeft(Node *nd)
{
    left = nd;
    nd->isLeft = true;
    nd->setParent(this);
}

void Node::setRight(Node *nd)
{
    right = nd;
    nd->setParent(this);
}

Node* Node::accessParent()
{
    return parent;
}

void Node::setParent(Node *nd)
{
    parent = nd;
    return;
}

bool Node::isLeaf()
{
    return ct != NULL;
}

void Node::setCharType(charType<Node> *symb)
{
    ct = symb;
    return;
}

Node *getNode()
{
    Node* nd = new Node;
    return nd;
}


LinkedList<charType<Node>> charList;

charType<Node> *getCharType()
{
    charType<Node> *c = new charType<Node>;
    return c;
}

template<typename T>
class PriorityQueue : public LinkedList<T>
{
public:
    PriorityQueue () {}
    void insertNode(T*);
    T* removeNode();

};

template<typename T>
void PriorityQueue<T>::insertNode(T *nd)
{
    if(this->head == NULL)
        this->head = nd;
    else{
        T *temp = this->head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = nd;
    }
    return;
}

template<typename T>
T *PriorityQueue<T>::removeNode()
{
    T *nd = this->head, *temp = this->head, *before = this->head, *previous = this->head;
    double small = nd->relFrequency;
    while(temp != NULL)
    {
        if(temp->relFrequency < small)
        {
            small = temp->relFrequency;
            nd = temp;
            before = previous;
        }
        previous = temp;
        temp = temp->next;
    }
    if(nd == this->head)
        this->head = this->head->next;
    else
        before->next = nd->next;
    return nd;
}

void calculateFrequency(char *message, int sz)
{
    for(int i=0; i<sz; ++i)
    {
        charType<Node> *ch =  charList.getHead();
        bool flag = true;
        while(ch != NULL && flag)
        {
            if(ch->symbol == message[i])
                flag = false;
            ch = ch->next;
        }
        if(flag)
        {
            int counter = 0;
            for(int j=i; j<sz; ++j)
                if(message[j] == message[i])
                    ++counter;
            charType<Node> *chTypePtr = getCharType();
            chTypePtr->symbol = message[i];
            chTypePtr->frequency = static_cast<double>(counter);
            charList.insertNode(chTypePtr);
        }
    }
    return;
}

void makeCode(int messageSize)
{
    PriorityQueue<Node> apq;
    charType<Node> *ch = charList.getHead();
    while(ch != NULL)
    {
        Node *nd = getNode();
        nd->setCharType(ch);
        nd->relFrequency = ch->frequency/static_cast<double>(messageSize);
        ch->treeNode = nd;
        apq.insertNode(nd);
        ch = ch->next;
    }
    int num = apq.sz();
    while(num > 1)
    {
        Node *n1 = apq.removeNode();
        Node *n2 = apq.removeNode();
        Node *nd = getNode();
        nd->relFrequency = n1->relFrequency + n2->relFrequency;
        nd->setLeft(n1);
        nd->setRight(n2);
        apq.insertNode(nd);
        num = apq.sz();
    }
    Node *root = apq.removeNode();
    ch = charList.getHead();
    while(ch != NULL)
    {
        Node *nd = ch->treeNode;
        while(nd != root)
        {
            codeType *ct = getCode();
            if(nd->isLeft)
                ct->info = '0';
            else
                ct->info = '1';
            ch->code.insertNode(ct);
            nd = nd->accessParent();
        }
        ch->code.reverseList();
        ch = ch->next;
    }
    return;
}

char *compare()
{
    charType<Node> *ct = charList.getHead();
    while(ct != NULL)
    {
        codeType *cd1 = ct->code.getHead();
        codeType *cd2 = tempList.getHead();
        bool isEqual = true;
        while(isEqual && (cd1 != NULL && cd2 != NULL))
        {
            if(cd1->info != cd2->info)
                isEqual = false;
            cd1 = cd1->next;
            cd2 = cd2->next;
        }
        if(isEqual && (cd1 == NULL && cd2 == NULL))
            return &(ct->symbol);
        ct = ct->next;
    }
    return NULL;
}

void encode(char *encodedString, char *message, int sz)
{
    int position = 0;
    for(int i=0; i<sz; ++i)
    {
        charType<Node> *ct = charList.getHead();
        bool flag = true;
        while(flag)
        {
            if(message[i] == ct->symbol)
                flag = false;
            if(flag)
                ct = ct->next;
        }
        codeType *cd = ct->code.getHead();
        while(cd != NULL)
        {
            encodedString[position++] = cd->info;
            cd = cd->next;
        }
    }
    encodedString[position] = '\0';
    return;
}

void decode(char *encodedString, char *decodedString)
{
    int position = 0;
    for(int i=0; encodedString[i] != '\0'; ++i)
    {
        codeType *ct = getCode();
        ct->info = encodedString[i];
        tempList.insertNode(ct);
        char *ch = compare();
        if(ch != NULL)
        {
            ct = tempList.getHead();
            while(ct != NULL)
            {
                codeType *temp = ct;
                ct = ct->next;
                freeCode(temp);
            }
            tempList.setHead(NULL);
            decodedString[position++] = *ch;
        }
    }
    decodedString[position] = '\0';
    return;
}

int main()
{
    char message[] = "The quick brown fox jumps right over the lazy little dog.";
    char encodedString[5000], decodedString[5000];
    int length = std::distance(std::begin(message), std::end(message));
    std::cout<<"The original message is: \n"<<message<<std::endl;
    calculateFrequency(message,length);
    makeCode(length);
    encode(encodedString,message,length);
    std::cout<<"\nThe encoded message is: \n"<<encodedString<<std::endl;
    decode(encodedString,decodedString);
    std::cout<<"\nThe decoded message is: \n"<<decodedString<<std::endl;
    return 0;
}








