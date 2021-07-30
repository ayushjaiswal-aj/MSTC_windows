#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 1
#define FAILURE 0
#define G_INVALID_VERTEX 2
#define G_INVALID_EDGE 3
#define G_EDGE_EXIT 4
#define F_VERTEX_EXIT 5

/* typedefs */
typedef int vertex_t;
typedef int status_t;
typedef struct hnode hnode_t;
typedef hnode_t hlist_t;
typedef struct vnode vnode_t;
typedef vnode_t vlist_t;
typedef struct graph graph_t;
typedef struct edge edge_t;

struct hnode
{
    vertex_t v;
    struct hnode *next;
    struct hnode *prev;
};

struct vnode
{
    vertex_t v;
    hlist_t *ph_head;
    struct vnode *prev;
    struct vnode *next;
}

struct edge
{
    vertex_t v_start;
    vertex_t v_end;
};

struct graph
{
    vlist_t *pv_head;
    int nr_vertices;
    int nr_edges;
};

/* graph management - interface routines */
graph_t* create_graph();

status_t add_vertex(graph_t *g, vertex_t v);
status_t add_edge(graph_t *g, vertex_t v_start, vertex_t e_vertex);
status_t remove_edge(graph_t *g, vertex_t v_start, vertex_t v_end);
status_t remove_vertex(graph_t *g, vertex_t v);

void show_graph(graph_t *g, const char *msg);

int get_nr_vertices(graph_t *g);
int get_nr_edges(graph_t *g);

status_t destroy_graph(graph_t *g);

/* vlist management - interface */
vlist_t* v_create_list();
status_t v_insert_end(vlist_t *pv_list, vertex_t v);

/* vlist management - internal */
void v_generic_insert(vnode_t *pv_beg, vnode_t *pv_mid, vnode_t *pv_end);
void v_generic_delete(vnode_t *pv_node);
vnode_t* v_search_node(vlist_t *pv_list, vertex_t v);
vnode_t* v_get_node(vertex_t v);

/* hlist management - interface */
hlist_t* h_create_list();
status_t h_insert_end(hlist_t *ph_list, vertex_t v);

/* hlist management - internal */
void h_generic_insert(hnode_t *ph_beg, hnode_t *ph_mid, hnode_t *ph_end);
void h_generic_delete(hnode_t *ph_node);
vnode_t* h_search_node(hlist_t *ph_list, vertex_t v);
vnode_t* h_get_node(vertex_t v);

/* auxillary routines */
void* xcalloc(size_t nr_elements, size_t size_per_elements);

int main(void)
{

}

/* graph management - interface routines */
void show_graph(graph_t *g, const char *msg)
{
    vnode_t *pv_run = NULL;
    hnode_t *ph_run = NULL;

    if(msg)
        puts(msg);
    
    pv_run = g->pv_head->next;
    while(pv_run != g->pv_head)
    {
        printf("[%d]\t", p_run->v);
        ph_run = pv_run->ph_head->next;
        while(ph_run != pv_run->ph->head)
        {
            printf("[%d]<->", ph_run->v);
            ph_run = ph_run->next;
        }
        pv_run = pv_run->next;
    }
}

int get_nr_vertices(graph_t *g)
{
    return (g->nr_vertices);
}

int get_nr_edges(graph_t *g)
{
    return (g->nr_edges);
}

status_t add_vertex(graph_t *g, vertex_t v)
{
    vnode_t *pv_node = NULL;
    pv_node = v_search_node(g->pv_head, v);

    if(pv_node != NULL)
    {
        return (G_VERTEX_EXITS);
    }

    v_insert_end(g->pv_head, v);
    g->nr_vertices ++;

    return (SUCCESS);
}

status_t add_edge(graph_t *g, vertex_t v_start, vertex_t e_vertex)
{
    vnode_t *pv_start = NULL;
    vnode_t *pv_end = NULL;
    hnode_t *ph_start = NULL;
    hnode_t *ph_end = NULL;
    status s;

    pv_start = v_search_node(g->pv_head, v_start);
    if(pv_start == NULL)
        return (G_INVALID_VERTEX);

    pv_end = v_search_node(g->pv_head, v_end);
    if(pv_end == NULL)
        return (G_INVALID_VERTEX);
    
    ph_start = h_search_node(pv_start->ph_head, v_end);
    ph_end = h_search_node(pv_end->ph_head, v_start);

    if(ph_start != NULL && ph_end != NULL)
    {
        return (G_EDGE_EXIT);
    }

    assert(ph_start == NULL && ph_end == NULL);

    s = h_insert_end(pv_start->ph_head, v_end);
    assert(s == SUCCESS);

    s = h_insert_end(pv_end->ph_head, v_start);
    assert(s == SUCCESS);

    g->nr_edges ++;

    return (SUCCESS);
}

status_t remove_edge(graph_t *g, vertex_t v_start, vertex_t v_end)
{
    vnode_t *pv_start = NULL;
    vnode_t *pv_end = NULL;
    hnode_t *ph_start = NULL;
    hnode_t *ph_end = NULL;

    pv_start = v_search_node(g->pv_head, v_start);
    if(pv_start == NULL)
    {
        return (G_INVALID_VERTEX);
    }

    pv_end = v_search_node(g->pv_head, v_end);
    if(pv_end == NULL)
    {
        return (G_INVALID_VERTEX);
    }

    ph_start = h_search_node(pv_start->ph_head, v_end);
    ph_end = h_search_node(pv_end->ph_head, v_start);

    if(ph_end == NULL || ph_start == NULL)
    {
        return (G_INVALID_EDGE);
    }

    h_generic_delete(ph_start);
    h_generic_insert(ph_end);

    g->nr_edges --;

    return (SUCCESS);
}

status_t remove_vertex(graph_t *g, vertex_t v)
{
    vnode_t *pv_node = NULL;
    vnode_t *pv_of_hvertex = NULL;
    hnode_t *ph_node = NULL;
    hnode_t *ph_run = NULL;
    hnode_t *ph_run_next = NULL;

    pv_node = v_search_node(g->pv_head, v);
    if(pv_node == NULL)
    {
        return (G_INVALID_VERTEX);
    }

    ph_run = pv_node->ph_head->next;
    while(ph_run != pv_node->ph_head)
    {
        ph_run_next = ph_run->next;
        pv_of_hvertex = v_search_node(g->pv_head, ph_run->v);
        ph_node = h_search_node(pv_of_hvertex->ph_head, v);

        h_generic_delete(ph_node);
        h_generic_delete(ph_run);

        g->nr_edged --;
        ph_run = ph_run_next;
    }
    free(pv_node->ph_head);
    v_generic_delete(pv_node);

    g->nr_vertices --;

    return (SUCCESS);
}

status_t destroy_graph(graph_t *g)
{
    vnode_t* pv_run = NULL;
    vnode_t* pv_run_next = NULL;
    hnode_t* ph_run = NULL;
    hnode_t* ph_run_next = NULL;

    pv_run = g->pv_head->next;
    while(pv_run != g->pv_head)
    {
        pv_run_next = pv_run->next;
        ph_run = pv_run->ph_head->next;
        while(ph_run != pv_run->ph_head)
        {
            ph_run_next = ph_run->next;
            free(ph_run);
            ph_run = ph_run_next;
        }
        free(pv_run->ph_head);
        free(pv_run);
        pv_run = pv_run_next;
    }
    free(g->pv_head);
    free(g);
    g = NULL;

    return(SUCCESS);
}

graph_t* create_graph()
{
    graph_t *g = NULL;
    g = (graph_t*)xcalloc(1, sizeof(graph_t));
    g->pv_head = v_create_list();
    g->nr_vertices = 0;
    g->nr_edges = 0;

    return (g);
}

/* vlist management - interface */
vlist_t* v_create_list()
{
    vlist_t *pv_list = NULL;
    pv_list = v_get_node(0);
    pv_list->next = pv_list;
    pv_list->prev = pv_list;

    return (pv_list);
}

status_t v_insert_end(vlist_t *pv_list, vertex_t v)
{
    v_generic_insert(pv_list->prev, v_get_node(v), pv_list);
    return (SUCCESS);
}

/* vlist management - internal */
void v_generic_insert(vnode_t *pv_beg, vnode_t *pv_mid, vnode_t *pv_end)
{
    pv_beg->next = pv_mid;
    pv_mid->next = pv_end;
    pv_end->prev = pv_mid;
    pv_mid->prev = pv_beg;
}

void v_generic_delete(vnode_t *pv_node)
{
    pv_node->next->prev = pv_node->prev;
    pv_node->prev->next = pv_node->next;
    free(pv_node);
    pv_node = NULL;
}

vnode_t* v_search_node(vlist_t *pv_list, vertex_t v)
{
    vnode_t *pv_run = NULL;
    pv_run = pv_list->next;
    while(pv_run != pv_list)
    {
        if(pv_run->v == v)
        {
            return (pv_run);
        }
        pv_run = pv_run->next;
    }
    return (NULL);
}

vnode_t* v_get_node(vertex_t v)
{
    vnode_t *pv_node = NULL;
    pv_node = (vnode_t*)xcalloc(1, sizeof(vnode_t));
    pv_node->v = v;
    pv_node->ph_head = h_create_list();
    pn_node->next = NULL;
    pn_node->prev = NULL;
}

/* hlist management - interface */
hlist_t* h_create_list()
{
    hlist_t *ph_list = NULL;
    ph_list = h_get_node(0);
    ph_list->next = ph_list;
    ph_list->prev = ph_list;

    return (ph_list);
}

status_t h_insert_end(hlist_t *ph_list, vertex_t v)
{
    h_generic_insert(ph_list->prev, h_get_node(v), ph_list);
    return (SUCCESS);
}

/* hlist management - internal */
void h_generic_insert(hnode_t *ph_beg, hnode_t *ph_mid, hnode_t *ph_end)
{
    ph_beg->next = ph_mid;
    ph_mid->next = ph_end;
    ph_end->prev = ph_mid;
    ph_mid->prev = ph_beg;
}

void h_generic_delete(hnode_t *ph_node)
{
    ph_node->next->prev = ph_node->prev;
    ph_node->prev->next = ph_node->next;
    free(ph_node);
    ph_node = NULL;
}

hnode_t* h_search_node(hlist_t *ph_list, vertex_t v)
{
    hnode_t* ph_run = NULL;
    ph_run = ph_list->next;
    while(ph_run != ph_list)
    {
        if(ph_run->v == v)
        {
            return (ph_run);
        }
        ph_run = ph_run->next;
    }

    return (NULL);
}

hnode_t* h_get_node(vertex_t v)
{
    hnode_t *ph_node = NULL;
    ph_node = (hnode_t *)xcalloc(1, sizeof(hnode_t));
    ph_node->v = v;
    ph_node->next = NULL;
    ph_node->prev = NULL;

    return (ph_node);
}

/* auxillary routines */
void* xcalloc(size_t nr_elements, size_t size_per_elements)
{
    void *p = NULL;
    p = calloc(nr_elements, size_per_elements);
    assert(p != NULL);
    return (p);
}
