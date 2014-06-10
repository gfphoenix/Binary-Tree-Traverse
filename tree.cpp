#include "tree.hpp"
#include <queue>
#include <stack>

void BtreeNode::for_preTraverse(const std::function<void(const BtreeNode *)> &fn)const
{
    if(_l)
        _l->for_preTraverse(fn);
    fn(this);
    if(_r)
        _r->for_preTraverse(fn);
}
void BtreeNode::for_midTraverse(const std::function<void(const BtreeNode *)> &fn)const
{
    fn(this);
    if(_l)
        _l->for_midTraverse(fn);
    if(_r)
        _r->for_midTraverse(fn);
}

void BtreeNode::for_postTraverse(const std::function<void(const BtreeNode *)> &fn)const
{
    if(_l)
        _l->for_postTraverse(fn);
    if(_r)
        _r->for_postTraverse(fn);
    fn(this);
}

void BtreeNode::for_preStack(const std::function<void(const BtreeNode *)> &fn)const
{
    std::stack<const BtreeNode *> s;
    s.push(this);
    while(!s.empty()){
        const auto x = s.top();
        s.pop();
        fn(x);
        if(_r)
            s.push(_r);
        if(_l)
            s.push(_l);
    }
}

void BtreeNode::for_midStack(const std::function<void(const BtreeNode *)> &fn)const
{
    std::stack<const BtreeNode *> s;
    const BtreeNode *x;
    for(x=this; x; x=x->_l)
        s.push(x);
    while(!s.empty()){
        const auto top = s.top();
        s.pop();
        fn(top);
        for(x=top->_r; x; x=x->_l)
            s.push(x);
    }
}

void BtreeNode::for_postStack(const std::function<void(const BtreeNode *)> &fn)const
{
    std::stack<const BtreeNode *> s;
    const BtreeNode *x;

    for(x=this; x; x=x->_l ? x->_l : x->_r)
        s.push(x);

    while(!s.empty()){
        const auto p = s.top(); s.pop();
        fn(p);
        if(!s.empty() && (x=s.top()) && (x->_l==p)){
            for(x = x->_r; x; x = x->_l ? x->_l : x->_r)
                s.push(x);
        }
    }
}

void BtreeNode::for_level(const std::function<void(const BtreeNode *)> &fn)const
{
    const BtreeNode *x;
    std::queue<const BtreeNode*>q;
    x = this;
    q.push(x);
    while(!q.empty()){
        x = q.front();
        q.pop();
        fn(x);
        if(x->_l)
            q.push(x->_l);
        if(x->_r)
            q.push(x->_r);
    }
}
const BtreeNode *BtreeNode::preFirst()const
{
    return this;
}
const BtreeNode *BtreeNode::preNext()const
{
    const BtreeNode *p;
    const BtreeNode *x=this;
	if(_l)
		return _l;
	if(_r)
		return _r;

	while((p=x->_p) && (p->_r == x || !p->_r))
		x = p;
	if(!p)
		return nullptr;
	return p->_r;
}

const BtreeNode *BtreeNode::midFirst()const
{
    auto x = this;
    while(x->_l)
        x = x->_l;
    return x;
}
const BtreeNode *BtreeNode::midNext()const
{
    const BtreeNode *x = this;
    const BtreeNode *p;
    if(_r){
        for(x = _r; x->_l; x=x->_l)
            ;
        return x;
    }
    while((p=x->_p) && p->_r == x)
        x = p;
    return p;
}

const BtreeNode *BtreeNode::postFirst()const
{
    const BtreeNode *x = this;
    while(x->_l || x->_r)
        x = x->_l ? x->_l : x->_r;
    return x;
}
const BtreeNode *BtreeNode::postNext()const
{
    if(!_p)
        return nullptr;
    const BtreeNode *p = _p;
    if(p->_r == this || !p->_r)
        return p;
    p = p->_r;
    while(p->_l || p->_r)
        p = p->_l ? p->_l : p->_r;
    return p;
}

void BtreeNode::for_preIter(const std::function<void(const BtreeNode *)> &fn)const
{
    for(const BtreeNode *x = preFirst(); x; x=preNext())
        fn(x);
}

void BtreeNode::for_midIter(const std::function<void(const BtreeNode *)> &fn)const
{
    for(const BtreeNode *x = midFirst(); x; x=midNext())
        fn(x);
}

void BtreeNode::for_postIter(const std::function<void(const BtreeNode *)> &fn)const
{
    for(const BtreeNode *x = postFirst(); x; x=postNext())
        fn(x);
}

void Btree::for_level(const std::function<void(const BtreeNode *)> &fn)const
{
    if(_root)
        _root->for_level(fn);
}
void Btree::for_preTraverse(const std::function<void(const BtreeNode *)> &fn)const
{
    if(_root)
        _root->for_preTraverse(fn);
}
void Btree::for_midTraverse(const std::function<void(const BtreeNode *)> &fn)const
{
    if(_root)
        _root->for_midTraverse(fn);
}

void Btree::for_postTraverse(const std::function<void(const BtreeNode *)> &fn)const
{
    if(_root)
        _root->for_postTraverse(fn);
}

void Btree::for_preStack(const std::function<void(const BtreeNode *)> &fn)const
{
    if(_root)
        _root->for_preStack(fn);
}
void Btree::for_midStack(const std::function<void(const BtreeNode *)> &fn)const
{
    if(_root)
        _root->for_midStack(fn);
}

void Btree::for_postStack(const std::function<void(const BtreeNode *)> &fn)const
{
    if(_root)
        _root->for_postStack(fn);
}

void Btree::for_preIter(const std::function<void(const BtreeNode *)> &fn)const
{
    if(_root)
        _root->for_preIter(fn);
}
void Btree::for_midIter(const std::function<void(const BtreeNode *)> &fn)const
{
    if(_root)
        _root->for_midIter(fn);
}

void Btree::for_postIter(const std::function<void(const BtreeNode *)> &fn)const
{
    if(_root)
        _root->for_postIter(fn);
}

