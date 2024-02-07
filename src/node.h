#ifndef NODE
#define NODE

struct Node {
    int id;
    double edge;
    bool isPickUp;
    bool isDropOff;
    int destId;

    Node(int ID, double weight, bool isPick, bool isDrop, int destID)
        : id(ID), edge(weight), isPickUp(isPick), isDropOff(isDrop), destId(destID) {
    }

};

#endif