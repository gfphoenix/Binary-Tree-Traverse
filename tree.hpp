#ifndef _TREE_HXX
#define _TREE_HXX

#include <functional>

class BtreeNode {
    protected:
        BtreeNode *_l; // left child
        BtreeNode *_r; // right child
        BtreeNode *_p; // parent

    public:
        inline BtreeNode *getLeft(){return _l;}
        inline const BtreeNode *getLeft() const { return _l;}
        inline BtreeNode *getRight() { return _r;}
        inline const BtreeNode *getRight() const {return _r;}
        inline BtreeNode *getParent() { return _p;}
        inline const BtreeNode *getParent() const {return _p;}
        inline bool hasChild()const{ return _l || _r; }

        // add some method to construct binary tree
    protected:
        void for_level(const std::function<void(const BtreeNode *)> &fn)const;

        void for_preTraverse(const std::function<void(const BtreeNode *)> &fn)const;
        void for_midTraverse(const std::function<void(const BtreeNode *)> &fn)const;
        void for_postTraverse(const std::function<void(const BtreeNode *)> &fn)const;

        void for_preStack(const std::function<void(const BtreeNode *)> &fn)const;
        void for_midStack(const std::function<void(const BtreeNode *)> &fn)const;
        void for_postStack(const std::function<void(const BtreeNode *)> &fn)const;

        void for_preIter(const std::function<void(const BtreeNode *)> &fn)const;
        void for_midIter(const std::function<void(const BtreeNode *)> &fn)const;
        void for_postIter(const std::function<void(const BtreeNode *)> &fn)const;

        const BtreeNode *preFirst()const;
        const BtreeNode *preNext()const;

        const BtreeNode *midFirst()const;
        const BtreeNode *midNext()const;

        const BtreeNode *postFirst()const;
        const BtreeNode *postNext()const;

    public:

        BtreeNode():_l(nullptr), _r(nullptr), _p(nullptr){}
        virtual ~BtreeNode(){}
        friend class Btree;
};


class Btree {
    protected:
        BtreeNode *_root;
    public:
        Btree():_root(nullptr){}
        virtual ~Btree(){}
        void for_preTraverse(const std::function<void(const BtreeNode *)> &fn)const;
        void for_midTraverse(const std::function<void(const BtreeNode *)> &fn)const;
        void for_postTraverse(const std::function<void(const BtreeNode *)> &fn)const;

        void for_preStack(const std::function<void(const BtreeNode *)> &fn)const;
        void for_midStack(const std::function<void(const BtreeNode *)> &fn)const;
        void for_postStack(const std::function<void(const BtreeNode *)> &fn)const;

        void for_preIter(const std::function<void(const BtreeNode *)> &fn)const;
        void for_midIter(const std::function<void(const BtreeNode *)> &fn)const;
        void for_postIter(const std::function<void(const BtreeNode *)> &fn)const;

        void for_level(const std::function<void(const BtreeNode *)> &fn)const;

};

#endif
