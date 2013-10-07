#include "binary_tree_traverse.h"
#include <cstdio>
#include <stack>
#include <queue>
static void __pre(struct avl_node *x, void (*fn)(const struct avl_node *, void *arg),void *arg)
{
	fn(x,arg);
	if(x->l)
		__pre(x->l, fn, arg);
	if(x->r)
		__pre(x->r, fn, arg);
}
void pre_r(struct avl_root *r, void (*fn)(const struct avl_node *,void *arg),void *arg)
{
	if(!r || !r->root)
		return;
	__pre(r->root, fn, arg);
}

//x is not null
static void __mid(struct avl_node *x, void (*fn)(const struct avl_node *, void *arg),void *arg)
{
	if(x->l)
		__mid(x->l, fn,arg);
	fn(x, arg);
	if(x->r)
		__mid(x->r, fn,arg);
}
void mid_r(struct avl_root *r, void (*fn)(const struct avl_node *,void *arg),void *arg)
{
	if(!r || !r->root)
		return;
	__mid(r->root, fn,arg);
}
static void __post(struct avl_node *x, void (*fn)(const struct avl_node *, void *arg),void *arg)
{
	if(x->l)
		__post(x->l, fn, arg);
	if(x->r)
		__post(x->r, fn, arg);
	fn(x, arg);
}

void post_r(struct avl_root *r, void (*fn)(const struct avl_node *,void *arg),void *arg)
{
	if(!r || !r->root)
		return;
	__post(r->root, fn, arg);
}

//// iterator  traverse
static struct avl_node *pre_first(struct avl_root *r)
{
	if(!r)
		return NULL;
	return r->root;
}

static struct avl_node *pre_next(struct avl_node *x)
{
	struct avl_node *p;
	if(x->l)
		return x->l;
	if(x->r)
		return x->r;

	while((p=x->p) && (p->r == x || !p->r))
		x = p;
	if(!p)
		return NULL;
	return p->r;
}
void pre_iter(struct avl_root *r, void (*fn)(const struct avl_node *,void *a),void *arg)
{
	struct avl_node *x ;
	for(x= pre_first(r); x; x = pre_next(x))
		fn(x,arg);
}

static struct avl_node *mid_first(struct avl_root *r)
{
	struct avl_node *p;
	if(!r || !r->root)
		return NULL;
	p = r->root;
	while(p->l)
		p = p->l;
	return p;
}
static struct avl_node *mid_next(struct avl_node *x)
{
	struct avl_node *p;
	if(x->r){
		p = x->r;
		while(p->l)
			p = p->l;
		return p;
	}
	while((p=x->p) && p->r == x)
		x = p;
	return p;
}
void mid_iter(struct avl_root *r, void (*fn)(const struct avl_node *,void *a),void *arg)
{
	struct avl_node *x ;
	for(x= mid_first(r); x; x = mid_next(x))
		fn(x,arg);
}
static struct avl_node *post_first(struct avl_root *r)
{
	struct avl_node *x;
	if(!r || !r->root)
		return NULL;
	x = r->root;
	while(x->l || x->r)
		x = x->l ? x->l : x->r;
	return x;
}
static struct avl_node *post_next(struct avl_node *x)
{
	struct avl_node *p = x->p;
	if(!p)
		return NULL;
	if(p->r == x || !p->r)
		return p;
	p = p->r;
	while(p->l || p->r)
		p = p->l ? p->l : p->r;
	return p;
}
void post_iter(struct avl_root *r, void (*fn)(const struct avl_node *,void *a),void *arg)
{
	struct avl_node *x;
	for(x=post_first(r); x; x = post_next(x))
		fn(x,arg);
}


//stack traverse

void pre_s(struct avl_root *r, void (*fn)(const struct avl_node *,void *a),void *arg)
{
	struct avl_node *p;
	std::stack<struct avl_node *> s;
	if(!r || !r->root)
		return ;
	s.push(r->root);
	while(!s.empty()){
		p = s.top();
		fn(p,arg);
		s.pop();
		if(p->r)
			s.push(p->r);
		if(p->l)
			s.push(p->l);
	}
}
void mid_s(struct avl_root *r, void (*fn)(const struct avl_node *, void*a),void*arg)
{
	struct avl_node *p;
	struct avl_node *n;
	std::stack<struct avl_node *> s;
	if(!r || !r->root)
		return;
	for(p=r->root; p; p=p->l)
		s.push(p);
	
	while(!s.empty()){
		p = s.top();
		fn(p,arg);
		s.pop();
		for((n = p->r); n; n=n->l)
			s.push(n);
	}
}
void post_s(struct avl_root *r, void (*fn)(const struct avl_node *, void*a),void*arg)
{
	if(!r || !r->root)
		return;
	std::stack<struct avl_node *> s;
	struct avl_node *p = r->root;
	for(; p; p = p->l ? p->l : p->r)
		s.push(p);

	while(!s.empty()){
		p = s.top();
		fn(p,arg);
		s.pop();
		if (!s.empty()){
			struct avl_node *n = s.top();
			if(n->l == p && n->r)
				for(n = n->r; n; n = n->l ? n->l : n->r)
					s.push(n);
		}
	}
}


void level(struct avl_root *r, void (*fn)(const struct avl_node *))
{
	struct avl_node *x;
	std::queue<struct avl_node *>q;
	if(!r || !r->root)
		return;
	x = r->root;
	q.push(x);
	while(!q.empty()){
		x = q.front();
		q.pop();
		fn(x);
		if(x->l)
			q.push(x->l);
		if(x->r)
			q.push(x->r);
	}
}
