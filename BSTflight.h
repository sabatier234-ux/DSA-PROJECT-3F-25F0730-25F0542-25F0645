// BSTflight.h - Module 4: binary search tree keyed by callsign 
#ifndef BSTFLIGHT_H
#define BSTFLIGHT_H
#include "Common.h"

struct BSTNode {
    Flight*  flight;
    BSTNode* left;
    BSTNode* right;
};

class BSTflight {
private:
    BSTNode* root;

    BSTNode* insertHelper(BSTNode* node, Flight* flight);
    Flight*  searchHelper(BSTNode* node, const string& callsign);
    BSTNode* removeHelper(BSTNode* node, const string& callsign);
    BSTNode* findMin(BSTNode* node);
    void     inorderHelper(BSTNode* node);
    int      heightHelper(BSTNode* node);
    void     destroyHelper(BSTNode* node);

public:
    BSTflight();
    ~BSTflight();

    void    insert(Flight* flight);
    Flight* search(const string& callsign);     // nullptr if not found
    void    remove(const string& callsign);     // needed when a flight lands
    void    inorderTraversal();                 // alphabetical print
    int     height();
    void    destroyTree();
};

#endif
