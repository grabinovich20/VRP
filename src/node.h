#ifndef NODE
#define NODE

//Each vertex is a node
struct Node {
    double id;
    double edge;
    bool isPickUp;
    bool isDropOff;
    bool isStart;
    int destId;
    double x;
    double y;
    double parentDist;

    Node(double ID, double weight, bool isPick, bool isDrop, int destID, bool start, double xC, double yC, double dist)
        : id(ID), edge(weight), isPickUp(isPick), isDropOff(isDrop), isStart(start), destId(destID), x(xC), y(yC), parentDist(dist) {
    }

    Node(double ID) {
        id = ID;
    }

    Node() {

    }
    
    bool operator==(const Node& other) const {
        return id == other.id;
    }

};

#endif