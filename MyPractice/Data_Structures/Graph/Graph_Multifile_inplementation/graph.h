#ifndef _GRAPH_H
#define _GRAPH_H

/* symbolic constants */

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0

#define HLIST_DATA_NOT_FOUND 2
#define VLIST_DATA_NOT_FOUND HLIST_DATA_NOT_FOUND

#define G_VERTEX_EXIST 3
#define G_EDGE_EXISTS 4
#define G_INVALID_VERTEX 5
#define G_INVALID_EDGE 6

#define V_LIST_EMPTY 7
#define V_QUEUE_EMPTY V_LIST_EMPTY

/* typedefs */

typedef int ret_t;
typedef int status_t;
typedef int vertex_t;
typedef int bool;

typedef struct graph graph_t;
typedef struct hnode hnode_t;
typedef struct vnode vnode_t;
typedef struct edge edge_t;
typedef struct vnodeptr_node vnodeptr_node_t;

typedef hnode_t hlist_t;
typedef vnode_t vlist_t;
typedef vnodeptr_node_t vnodeptr_list_t;
typedef vnodeptr_list_t vnodeptr_queue_t;

typedef enum color color_t;

/* internal layout */

/* color enumeration */
enum color 
{
    WHITE = 0,
    GREY,
    BLACK
};

/* a node in horizontal list -> connections of vertex in vertex list */
struct hnode 
{
    vertex_t v;
    double w;
    struct hnode *next;
    struct hnode *prev;
};

/* a node in vertical list -> list of vertex */
struct vnode
{
    vertex_t v;
    hlist_t *ph_list;
    color_t c;

    struct vnode *next;
    struct vnode *prev;
};

struct graph
{
    vlist_t *pv_list;
    int nr_vertices;
    int nr_edges;
};

struct vnodeptr_node
{
    vnode_t *pv_node;
    struct vnodeptr_node *prev;
    struct vnodeptr_node *next;
}

/* Graph management */
/* Graph interface routines */
graph_t* create_graph(void);
ret_t add_vertex(graph_t *g, vertex_t v);
ret_t remove_vertex(graph_t *g, vertex_t v);
ret_t add_edge(graph_t *g, vertex_t v_start, vertex_t v_end);
ret_t remove_edge(graph_t *g, vertex_t v_start, vertex_t v_end);
void print_graph(graph_t *g, const char *msg);
int get_nr_vertices(graph_t *g);
int get_nr_edges(graph_t *g);
ret_t destroy_graph(graph_t **pp_g);

ret_t dfs(graph_t *g);
ret_t bfs(graph_t *g, vertex_t v);

/* graph - auxillary routines for traversal algorithms */

void reset(graph_t *g);
void dfs_visit(graph_t *g, vnode_t *pv_node);

/* graph - auxillary routines - part 1 vertical list management */

vlist_t *create_list_v(void);
ret_t insert_end_v(vlist_t *pv_list, vertex_t v_new);
ret_t remove_vertex_v(vlist_t *pv_list, vertex_t r_vertex);
ret_t destroy_list_v(vlist_t **pp_list);

/* vertical list - auxillary routines */
void generic_insert_v(vnode_t *pv_beg, vnode_t *pv_mid, vnode_t *pv_end);
void generic_delete_v(vnode_t *p_delete_node);
vnode_t* search_node_v(vlist_t *pv_list, vertex_t v_search);
vnode_t* get_node_v(vertex_t v_new);

/* graph auxillary routines part - 2 horizontal list management */

hlist_t* create_list_h(void);
ret_t insert_end_h(hlist_t *ph_list, vertex_t v_new, double w);
ret_t remove_vertex_h(hlist_t *ph_list, vertex_t r_vertex);
ret)t destroy_list_h(hlist_t **pp_list);

/* horizontal list auxillary */
void generic_insert_h(hnode_t *ph_beg, hnode_t *ph_mid, hnode_t *ph_end);
void generic_delete_t(hnode_t *ph_node);
hnode_t* search_node_h(hlist_t *ph_list, vertex_t v_search);
hnode_t* get_node_h(vertex_t v_new, double w);

/* graph auxillary routines - BFS queue */
vnodeptr_queue_t create_vnodeptr_queue();
ret_t enqueue_vnodeptr(vnodeptr_queue_t *pv_queue, vnode_t *pv_new_node);
ret_t dequeue_vnodeptr(vnodeptr_queue_t *pv_queue, vnode_t **ppv_beg_node);
bool is_vnodeptr_queue_empty(vnodeptr_queue_t *p_vnodeptr_queue);
ret_t destroy_vnodeptr_queue(vnodeptr_queue_t **pp_vnodeptr_queue);

/* Graph - BFS Queue - list */
vnodeptr_list_t create_vnodeptr_list();
ret_t insert_end_vnodeptr(vnodeptr_list_t *pvnodeptr_list, vnode_t *pv_new_node);
ret_t remove_beg_vnodeptr(vnodeptr_list_t *pvnodeptr_list, vnode_t **ppv_beg_node);
bool is_vnodeptr_list_empty(vnodeptr_list_t *pvnodeptr_list);
ret_t destroy_vnodeptr_list(vnodeptr_list_t **ppvnodeptr_list);

/* Graph - BFS Queue - List Auxillary */
void generic_insert_vnodeptr(vnodeptr_node_t *pvnodeptr_node_beg, vnodeptr_node_t *pvnodeptr_node_mid, vnodeptr_node_t *pnodeptr_node_end);
void generic_delete_vnodeptr(vnodeptr_node_t *pvnodeptr_delete_node);
vnodeptr_node_t* get_vnodeptr_node(vnode_t *pv_new_node);

/* graph - auxillary routines - memory management */
void* xcalloc(size_t nr_elements, size_t size_per_element);

#endif