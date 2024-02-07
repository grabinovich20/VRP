#ifndef NODE
#define NODE

struct Node {
    double id;
    double edge;
    bool isPickUp;
    bool isDropOff;
    bool isStart;
    int destId;
    double x;
    double y;

    Node(double ID, double weight, bool isPick, bool isDrop, int destID, bool start, double xC, double yC)
        : id(ID), edge(weight), isPickUp(isPick), isDropOff(isDrop), isStart(start), destId(destID), x(xC), y(yC) {
    }
    

};

#endif