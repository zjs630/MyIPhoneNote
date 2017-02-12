
判断单链表是否存在环，判断两个链表是否相交
<编程之美>3.6
摘要：有一个单链表，其中可能有一个环，也就是某个节点的next指向的是链表中在它之前的节点，这样的链表的尾部形成一环。1、如何判断一个链表是否存在环？2、如果链表存在环，如何找到环的 入口点？扩展：3如何判断两个单链表是否相交？4如果相交，给出相交的第一个节点。
解答：
问题1、判断链表是否存在环。
设置两个指针fast和slow，初始值都指向头指针，slow每次前进一步，fast每次前进两步。如果存在环，则fast必先进入环，而slow后进入环，两个指针必定相遇（见下面的证明1）。（当然，fast先到达尾部为NULL，则为无环链表）。程序如下：
bool isExitsLoop(Node* head)
Node *slow = head, *fast = head;
//fast && fast->next保证了fast可以接着向下移动
while(fast && fast->next)
slow = slow->next
fast = fast->next->next;
if(slow == fast)
break;
return !(fast==NULL || fast->next == NULL)

证明1：两个指针fast和slow，fast一次递增两步，slow一次递增一步。如果有环的话两者必然重合，反之亦然。
因为fast每次走2步，而slow每次走一步，所以它们之间的差距是一步一步缩小的。当slow进入环入口点后，fast和slow之间的差距将会一步步缩小，如4,3,2,1,0。到0的时候就重合了。
根据此方式，可以证明，fast每次走三步以上，并不总能加快检测速度，反而有可能判别不出环。

2、若链表存在环，找到环的入口点
如果fast和slow相遇，那么在相遇时，slow肯定没有遍历完链表，而fast已经在环内循环了n圈（n>=1）（见下面的证明2）。假设slow走了s步，则fast走了2s步（fast的步数还等于s加上在环上多转的n圈），设环长为r，则：
2s=s+nr
s=nr
设整个链表长L，入口环与相遇点距离为x，起点到环入口点的距离为a，则
a+x=s=nr
a+x=(n-1)r+r=(n-1)r+L-a
a=(n-1)r+(L-a-x)
(L-a-x)为相遇点到环入口点的距离。由此可知，从链表头到环入口点等于(n-1)循环内环+相遇点到环入口点。于是可以从链表头和相遇点分别设一个指针，每次各走一步，两个指针必定相遇，且相遇第一点为环入口点。程序描述如下：
Node* findLoopPort(Node *head)
Node *slow = head, *fast=head;
//找到相遇点
while(fast && fast->next)
slow = slow->next
fast=fast->next->next
if(fast=slow)
break
if(fast==NULL || fast->next==NULL)
return NULL

//此时，fast和slow都指向相遇点
slow=head   //slow指向头节点
while(slow != fast)
slow=slow->next
fast=fast->next
return slow


扩展问题3、判断两个单链表是否相交？
法1、对链表1中的每个节点p1，判断链表2中是否有一个节点p2指向p1
loop:p1从head1到最后一个节点
loop:p2从head2到最后一个节点
if(p2是否指向p1)
相交
break
时间复杂度：O(list1.length * list2.length)
空间复杂度：O(1)
法2、使用hash表
loop：p1从head1到最后一个节点
把p1放入hash表table中
loop:p2从head2到最后一个节点
if(p2在hash表中)
相交
时间复杂度:O(list1.length + list2.length)
空间复杂度：O(list1.length)
法3、将其中一个链表首尾相连，检测另一个链表是否存在环，如果存在，则两个链表相交，而检测出来的依赖环入口点即为相交的第一个点。程序描述如下：
找到list1的最后一个节点tail1
tail1->next=head1
判断head2是否存在环
tail1->next=NULL; //恢复tail1

法4、如果两个链表相交，那么两个链表从相交点到链表结束都是相同的节点。可以先分别遍历找出两个链表的尾节点，如果连个尾节点相同，则两个链表相交。程序描述如下：
//找到list1的最后一个节点p1
p1=head1
while(p1->next不是NULL)
p1=p1->next
找出list2的最后一个节点p2
if(p1==p2)
相交
else
不相交
时间复杂度:O(list1.length + list2.length)
空间复杂度：O(1)

扩展问题4、如果两个链表相交，找出相交的第一个节点？
在判断相交的过程中要分别遍历两个链表，同时记下各自的长度。然后再遍历一次：长链表节点先从头节点出发前进(lengthMax-lenghMin)步，之后两个链表同时前进，每次一步，相遇的第一个节点即为两个链表相交的第一个节点。程序描述如下：
Node *intersection(Node *head1, Node *head2)
if(!head1 || !head2)
return NULL;
int len1 = 1;
int len2 = 1;
bool result = false;
//判断两个链表是否相交，同时记下各个链表的长度
Node *p = head1;
while(p->next)
pLen++; p=p->next
q=head2
while(q->next)
len2++; q=q->next
result=(p==q)
if(result)
int steps = abs(len1 – len2)
Node *head = len1 > len2 ? head1 : head2;
while(steps)
head = head->next
steps –-
len1 > len2 ? p = head,q=head2 ? q = head,p=head1
while(p!=q)
p=p->next
q=q->next
return p
return NULL

补充5、判断两个链表带有环的链表是否相交？
情况一、两个链表在环上相交：

情况二、两个链表从非环处开始相交：

无论是哪种情况，对于环上的任意一个节点，都可以通过head1或者head2到达。

源代码如下：
#include <iostream>

using namespace std;

class Node{
public:
    Node(int d):data(d), next(NULL){}
    
    int data;
    Node *next;
};

void displayLinkList(Node *head, int n){
    n = n + 2;
    for (int i = 0; i < n && head; i ++, head = head->next)
        cout << head->data << " ";
    cout << endl;
}

bool isExitsLoop(Node *head){
    Node *fast = head;
    Node *slow = head;
    
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow)
            break;
    }
    
    if (fast && fast->next)
        return true;
    else
        return false;
}

Node *findLoopPort(Node *head){
    Node *fast = head;
    Node *slow = head;
    
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            break;
    }
    
    bool result;
    if (fast && fast->next)
        result = true;
    else
        result = false;
    
    if (result)
    {
        slow = head;
        while (slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
    return NULL;
}

void testIsExitLopp(Node *head, int n){
    displayLinkList(head, n);
    if (isExitsLoop(head))
        cout << "head has loop" << endl;
    else
        cout << "head does not have loop" << endl;
    
    Node *result = findLoopPort(head);
    if (result)
        cout << "head has loop, loop port is " << result->data << endl;
    else
        cout << "head does not have loop" << endl;
}

//
bool intersect3(Node *head1, Node *head2){
    Node *tail2 = head2;
    while (tail2->next)
        tail2 = tail2->next;
    tail2->next = head2;
    
    bool result = isExitsLoop(head1);
    tail2->next = NULL;
    return result;
}

void testIntersect3(Node *head1, Node *head2){
    if (intersect3(head1, head2))
        cout << "intersect" << endl;
    else
        cout << "not intersect" << endl;
}

bool intersect4(Node *head1, Node *head2){
    Node *tail1 = head1;
    Node *tail2 = head2;
    while (tail1->next)
        tail1 = tail1->next;
    while (tail2->next)
        tail2 = tail2->next;
    
    return tail1 == tail2;
}

void testIntersect4(Node *head1, Node *head2){
    if (intersect4(head1, head2))
        cout << "intersect" << endl;
    else
        cout << "not intersect" << endl;
}

//
Node *findFirstIntersection(Node *head1, Node *head2){
    if (head1 == NULL|| head2 == NULL)
        return NULL;
    int len1 = 1;
    int len2 = 1;
    bool result = false;
    Node *p = head1;
    Node *q = head2;
    while (p->next)
    {
        len1 ++;
        p = p->next;
    }
    while (q->next)
    {
        len2 ++;
        q = q->next;
    }
    result = (p == q);
    if (result)
    {
        int steps = abs(len1 - len2);
        Node *head = (len1 > len2) ? head1 : head2;
        while (steps)
        {
            head = head->next;
            steps --;
        }
        
        (len1 > len2) ? (p = head, q = head2) : (p = head1, q = head);
        while (p != q)
        {
            p = p->next;
            q = q->next;
        }
        return p;
    }
    return NULL;
}

void testFindFirstIntersection(Node *head1, Node *head2){
    Node *result = findFirstIntersection(head1, head2);
    if (result == NULL)
        cout << "no intersection" << endl;
    else
        cout << "first intersection is " << result->data << endl;
}

void main(){
    Node *head1 = NULL;   //hasLoop
    Node *head2 = NULL;   //noLoop
    
    //construct head1
    Node *tail = NULL;
    for (int i = 0; i < 10; i ++)
    {
        Node *p = new Node(i + 1);
        if (head1 == NULL)
        {
            head1 = p;
            tail = head1;
        }
        else
        {
            tail->next = p;
            tail = p;
        }
    }
    Node *p = head1;
    for (i = 1; i < 5; i ++)
        p = p->next;
    tail->next = p;
    
    //consruct head2
    tail = NULL;
    for (i = 0; i < 10; i ++)
    {
        Node *p = new Node(i + 1);
        if (head2 == NULL)
        {
            head2 = p;
            tail = p;
        }else{
            tail->next = p;
            tail = p;
        }
    }
    
    testIsExitLopp(head1, 10);
    testIsExitLopp(head2, 10);
    
    cout << "test two link list insert or not" << endl;
    Node *head3 = NULL;
    Node *head4 = NULL;
    Node *p1 = new Node(1);
    Node *p2 = new Node(2);
    Node *p3 = new Node(3);
    Node *p4 = new Node(4);
    Node *p5 = new Node(5);
    Node *p11 = new Node(11);
    Node *p12 = new Node(12);
    Node *p13 = new Node(13);
    Node *p14 = new Node(14);
    Node *p15 = new Node(15);
    head3 = p1;
    p1->next = p2;
    p2->next = p3;
    p3->next = p4;
    p4->next = p5;
    head4 = p11;
    p11->next = p12;
    p12->next = p13;
    p13->next = p14;
    p14->next = p15;
    p15->next = p3;
    
    testIntersect3(head3, head4);
    testIntersect4(head3, head4);
    testFindFirstIntersection(head3, head4);
    
    p15->next = NULL;
    testIntersect3(head3, head4);
    testIntersect4(head3, head4);
    testFindFirstIntersection(head3, head4);
}