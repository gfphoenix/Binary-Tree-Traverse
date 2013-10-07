#ifndef  BINARY_TREE_TRAVERSE_H
#define  BINARY_TREE_TRAVERSE_H

// use my existing code about avl
struct avl_node {
        struct avl_node *l;   // left child
        struct avl_node *r;  // right child
        struct avl_node *p;  // parent
        int balance;  		// balance : -1, 0 or 1, 
        int val;  //key for demo
};
struct avl_root {
        struct avl_node *root;
};
/// 
void pre_r(struct avl_root *r, void (*fn)(const struct avl_node *,void *arg),void *arg);
void mid_r(struct avl_root *r, void (*fn)(const struct avl_node *,void *arg),void *arg);
void post_r(struct avl_root *r, void (*fn)(const struct avl_node *,void *arg),void *arg);

void pre_iter(struct avl_root *r, void (*fn)(const struct avl_node *,void *a),void *arg);
void mid_iter(struct avl_root *r, void (*fn)(const struct avl_node *,void *a),void *arg);
void post_iter(struct avl_root *r, void (*fn)(const struct avl_node *,void *a),void *arg);

void pre_s(struct avl_root *r, void (*fn)(const struct avl_node *,void *a),void *arg);
void mid_s(struct avl_root *r, void (*fn)(const struct avl_node *, void*a),void*arg);
void post_s(struct avl_root *r, void (*fn)(const struct avl_node *, void*a),void*arg);

#endif
