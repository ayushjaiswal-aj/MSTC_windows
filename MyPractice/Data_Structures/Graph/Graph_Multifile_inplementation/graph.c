#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

/* Graph management */
/* Graph interface routines */
graph_t* create_graph(void)
{
    graph_t *g = (graph_t*)xcalloc(1, sizeof(graph_t));
    g->pv_list = (vnode_t*)xcalloc(1, sizeof(vnode_t));

    g->pv_list->v = -1;

    g->pv_list->ph_list = NULL;
    g->pv_list->prev = g->pv_list;
    g->pv_list->next = g->pv_list;

    g->nr_vertices = 0;
    g->nr_edges = 0;

    return (g);
}

ret_t add_vertex(graph_t *g, vertex_t v)
{
    vnode_t *pv_node = search_node_v(g->pv_list, v);
    if(pv_node != NULL)
    {
        return (G_VERTEX_EXIST);
    }

    insert_end_v(g->pv_list, v);
    g->nr_vertices ++;

    return (SUCCESS);
}

ret_t remove_vertex(graph_t *g, vertex_t v)
{
    vnode_t *pv_node = NULL;
    vnode_t *pv_node_of_hv = NULL;
    hnode_t *ph_run = NULL;
    hnode_t *ph_run_next = NULL;
    ret_t ret;

    pv_node = pv_node->ph_list->next;
    while(ph_run != pv_node->ph_list)
    {
        ph_run_next = ph_run->next;
        pv_node_of_hv = search_node_v(g->pv_list, ph_run->v);
        ret = remove_vertex_h(pv_node_of_hv->ph_list, v);
        assert(ret == SUCCESS);
        free(ph_run);
        g->nr_edges __;
        ph_run = ph_run_next;
    }

    free(pv_node->ph_list);
    generic_delete_h(pv_node);
    g->nr_vertices --;

    return (SUCCESS);
}

ret_t add_edge(graph_t *g, vertex_t v_start, vertex_t v_end)
{
    vnode_t *pv_node_start = NULL;
    vnode_t *pv_node_end = NULL;
    hnode_t *ph_node = NULL;

    pv_node_start = search_node_v(g->pv_list, v_start);
    pv_node_end = search_node_v(g->pv_list, v_end);
    if(pv_node_start == NULL || pv_node_end == NULL)
    {
        return (G_EDGE_EXIST);
    }

    ph_node = search_node_h(pv_node_start->ph_list, v_end);
    if(ph_node != NULL)
    {
        return (G_EDGE_EXIST);
    }

    assert(insert_end_h(pv_node_start->ph_list, v_end, w) == SUCCESS);
    assert(insert_end_h(pv_node_end->ph_list, v_start, w) == SUCCESS);

    g->nr_edges ++;
    return (SUCCESS);
}

ret_t remove_edge(graph_t *g, vertex_t v_start, vertex_t v_end)
{
    vnode_t *pv_start = NULL;
    vnode_t *pv_end = NULL;
    ret_t ret;

    pv_start = search_node_v(g->pv_list, v_start);
    pv_end = search_node_v(g->pv_list, v_end);

    if(pv_start == NULL || pv_end == NULL)
    {
        return (G_INVALID_VERTEX);
    }

    ret = remove_vertex_h(pv_start->ph_list, v_end);
    if(ret == HLIST_DATA_NOT_FOUND)
    {
        return (G_INVALID_EDGE);
    }

    ret = remove_vertex_h(pv_end->ph_list, v_start);
    if(ret == HLIST_DATA_NOT_FOUND)
    {
        return (G_INVALID_EDGE);
    }

    g->nr_edges --;
    return (SUCCESS);
}

void print_graph(graph_t *g, const char *msg)
{
    vnode_t *pv_node = NULL;
    hnode_t *ph_node = NULL;

    puts("msg");

    for(pv_node = g->pv_list->next; pv_node != g->pv_list; pv_node = pv_node->next)
    {
        printf("[%d]\t --->\t", pv_node->v);
        for(ph_node = pv_node->ph_list->next; ph_node != pv_node->ph_list; ph_node = ph_node->next)
        {
            printf("[%d]<->", ph_node->v);
        }
        puts("[end]\n");
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

ret_t destroy_graph(graph_t **pp_g)
{
    graph_t *g = NULL;
    vnode_t *pv_node = NULL;
    vnode_t *pv_node_next = NULL;
    g = *pp_g;

    for(ph_node = g->pv_list->next; pv_node != g->pv_list; pv_node = pv_node_next)
    {
        pv_node_next = pv_node->next;
        destroy_list_h(&pv_node->ph_list);
        free(pv_node);
    }

    free(g->pv_list);
    free(g);

    return (SUCCESS);
}

ret_t dfs(graph_t *g)
{
    vnode_t *pv_run;

    reset(g);
    printf("[BEGINING]<->");
    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
    {
        if(pv_run->c == WHITE)
        {
            dfs_visit(g, pv_run);
        }
    }
    puts("[END]\n");
    return (SUCCESS);
}

ret_t bfs(graph_t *g, vertex_t v)
{
    vnode_t *pv_source;
    vnode_t *u = NULL;
    vnode_t *pv_of_ph;
    hnode_t *ph_run;

    vnodeptr_queue_t *q = NULL;
    
    reset(g);

    pv_source = search_node_v(g->pv_list, v);
    if(pv_source == NULL)
    {
        return (G_INVALID_VERTEX);
    }
    pv_sourse->c = GREY;
    
    q = create_vnodeptr_queue();
    assert(enqueue_vnodeptr(q, pv_source));
    printf("[BEGGINING]<->");
    while(is_vnodeptr_queue_empty(q) != TRUE)
    {
        assert(dequeue_vnodeptr(q, &u) == SUCCESS);
        printf("[%d]<->", u->v);
        ph_run = u->ph_list->next;
        while(ph_run != ph_list)
        {
            pv_of_ph = search_node_v(g->pv_list, ph_run->v);
            if(pv_of_ph->c == WHITE)
            {
                pv_of_ph->c = GREY;
                assert(enqueue_vnodeptr(q, pv_of_ph) == SUCCESS);
            }
            ph_run = ph_run->next;
        }
        u->c = BLACK;
    }
    puts("[END]");
    assert(v_destroy_vnodeptr_queue(&q) == SUCCESS && Q == NULL);

    return (SUCCESS);
}

/* graph - auxillary routines for traversal algorithms */

void reset(graph_t *g)
{
    vnode_t *pv_run;
    for(pv_run = g->pv_list->next; ph_run != pv_node; pv_run = pv_run->next)
    {
        pv_run->c = WHITE;
    }
}

void dfs_visit(graph_t *g, vnode_t *pv_node)
{
    hnode_t *ph_run = NULL;
    vnode_t *pv_of_hnode = NULL;

    printf("[%d]<->", pv_node->v);
    pv_node->c = GREV;

    for(ph_run = pv_node->ph_list->next; ph_run != pv_node->ph_list; ph_run = ph_run->next)
    {
        pv_of_hnode = search_node_v(g->pv_list, ph_run->v);
        if(pv_of_hnode->c == WHITE)
        {
            dfs_visit(g, pv_of_hnode);
        }
    }
    pv_node->c = BLACK;
}

/* graph - auxillary routines - part 1 vertical list management */

vlist_t *create_list_v(void)
{
    vnode_t *pv_list = NULL;
    pv_list = get_node_v(-1);
    pv_list->prev = pv_list;
    pv_list->next = pv_list;

    return (pv_list);
}

ret_t insert_end_v(vlist_t *pv_list, vertex_t v_new)
{
    generic_insert_v(pv_list->prev, get_node_v(v_new), pv_list);
    return (SUCCESS);
}

ret_t remove_vertex_v(vlist_t *pv_list, vertex_t r_vertex)
{
    vnode_t *pv_node = search_node_v(pv_list, r_vertex);
    if(pv_node == NULL)
    {
        return (VLIST_DATA_NOT_FOUND);
    }
    generic_delete_v(pv_node);
    return (SUCCESS);
}

ret_t destroy_list_v(vlist_t **pp_list)
{
    vlist_t *p_list = NULL;
    p_list = *pp_list;
    vnode_t *p_run = NULL;
    vnode_t *p_run_next = NULL;
    p_run = p_list->next;
    while(p_run != p_list)
    {
        p_run_next = p_run->next;
        free(p_run);
        p_run = p_run_next;
    }
    free(p_list);
    *pp_list = NULL;
    return (SUCCESS);
}

/* vertical list - auxillary routines */
void generic_insert_v(vnode_t *pv_beg, vnode_t *pv_mid, vnode_t *pv_end)
{
    pv_beg->next = pv_mid;
    pv_mid->next = pv_end;
    pv_end->prev = pv_mid;
    pv_mid->prev = pv_beg;
}

void generic_delete_v(vnode_t *p_delete_node)
{
    p_delete_node->next->prev = p_delete_node->prev;
    p_delete_node->prev->next = p_delete_node->next;
    free(p_delete_node);
    p_delete_node = NULL;
}

vnode_t* search_node_v(vlist_t *pv_list, vertex_t v_search)
{
    vnode_t *pv_run = NULL;
    pv_run = pv_list->next;
    while(pv_run != pv_list)
    {
        if(pv_run->v  == v_search)
        {
            return (pv_run);
        }
        pv_run = pv_run->next;
    }
    return (NULL);
}

vnode_t* get_node_v(vertex_t v_new)
{
    vnode_t *pv_new_node = (vnode_t *)xcalloc(1, sizeof(vnode_t));
    pv_new_node->v = v+new;
    pv_new_node->ph_list = create_list_h();
    pv_new_node->c = WHITE;
    return (pv_new_node);
}

/* graph auxillary routines part - 2 horizontal list management */

hlist_t* create_list_h(void)
{
    hnode_t *ph_head_node = NULL;
    ph_head_node = get_node_h(1, sizeof(vnode_t));
    ph_head_node->prev = ph_head_node;
    ph_head_node->next = ph_head_node;

    return ph_head_node;
}

ret_t insert_end_h(hlist_t *ph_list, vertex_t v_new, double w)
{
    generic_insert_h(ph_list->prev, get_node_h(v_new, w), ph_list);
    return (SUCCESS);
}

ret_t remove_vertex_h(hlist_t *ph_list, vertex_t r_vertex)
{
    hnode_t *ph_node = search_node_h(ph_list, r_vertex);
    if(ph_node == NULL)
    {
        return (HLIST_DATA_NOT_FOUND);
    }
    generic_delete_h(ph_node);
    return (SUCCESS);
}

ret_t destroy_list_h(hlist_t **pp_list)
{
    hlist_t *ph_list = **pp_list;
    hnode_t *ph_run = NULL;
    hnode_t *ph_run_next = NULL;

    for(ph_run = ph_list->next; ph_run != ph_list; ph_run = ph_run_next)
    {
        ph_run_next = ph_run->next;
        free(ph_run);
    }
    free(ph_run);
    *pp_list = NULL;
    return (SUCCESS);
}

/* horizontal list auxillary */
void generic_insert_h(hnode_t *ph_beg, hnode_t *ph_mid, hnode_t *ph_end)
{
    ph_beg->next = ph_mid;
    ph_mid->next = ph_end;
    ph_end->prev = ph_mid;
    ph_mid->prev = ph_beg;
}

void generic_delete_h(hnode_t *ph_node)
{
    ph_node->next->prev = ph_node->prev;
    ph_node->prev->next = ph_node->next;
    free(ph_node);
    ph_node = NULL;
}

hnode_t* search_node_h(hlist_t *ph_list, vertex_t v_search)
{
    hnode_t *p_hrun = NULL;
    p_hrun = ph_list->next;
    while(p_hrun == ph_list)
    {
        if(p_hrun->v == v_search)
        {
            return (p_hrun);
        }
        p_hrun = p_hrun->next;
    }
    return (NULL);
}

hnode_t* get_node_h(vertex_t v_new, double w)
{
    hnode_t *p_new_node = NULL;
    p_new_node = get_node_h(v_new);
    p_new_node->w = w;
    p_new_node->prev = NULL;
    p_new_node->next = NULL;

    return p_new_node;
}

/* graph auxillary routines - BFS queue */
vnodeptr_queue_t create_vnodeptr_queue()
{
    return create_vnodeptr_list();
}

ret_t enqueue_vnodeptr(vnodeptr_queue_t *pv_queue, vnode_t *pv_new_node)
{
    return enqueue_vnodeptr(pv_queue, pv_new_node);
}

ret_t dequeue_vnodeptr(vnodeptr_queue_t *pv_queue, vnode_t **ppv_beg_node)
{
    return remove_beg_vnodeptr(pv_queue, ppv_beg_node);
}

bool is_vnodeptr_queue_empty(vnodeptr_queue_t *p_vnodeptr_queue)
{
    return (is_vnodeptr_list_empty(p_vnodeptr_queue));
}

ret_t v_destroy_vnodeptr_queue(vnodeptr_queue_t **pp_vnodeptr_queue)
{
    return (destroy_vnodeptr_queue(pp_vnodeptr_queue));
}

/* Graph - BFS Queue - list */
vnodeptr_list_t create_vnodeptr_list()
{
    vnodeptr_list_t *p_new_list = NULL;
    p_new_list = get_vnodeptr_node(NULL);
    p_new_list->prev = p_new_list;
    p_new_list->next = p_new_list;
    
    return (p_new_list);
}

ret_t insert_end_vnodeptr(vnodeptr_list_t *pvnodeptr_list, vnode_t *pv_new_node)
{
    generic_insert_vnodeptr(pvnodeptr_list->prev, get_vnodeptr_node(pv_new_node), pvnodeptr_list);
    return (SUCCESS);
}

ret_t remove_beg_vnodeptr(vnodeptr_list_t *pvnodeptr_list, vnode_t **ppv_beg_node)
{
    if(is_vnodeptr_list_empty(pvnodeptr_list))
    {
        return (V_LIST_EMPTY);
    }
    *ppv_beg_node = pvnodeptr_list->next->pv_node;
    generic_delete_vnodeptr(pvnodeptr_list->next);
    return (SUCCESS);
}

bool is_vnodeptr_list_empty(vnodeptr_list_t *pvnodeptr_list)
{
    if(pvnodeptr_list->next == pvnodeptr_list && pvnodeptr_list->prev == pvnodeptr_list);
        return (TRUE);
    
    return (FALSE);
}

ret_t destroy_vnodeptr_list(vnodeptr_list_t **ppvnodeptr_list)
{
    vnodeptr_list_t *p_list = NULL;
    vnodeptr_node_t *p_run = NULL;
    vnodeptr_node_t *p_run_next = NULL;
    p_list = *ppvnodeptr_list;
    p_run = p_list->next;
    while(p_run != p_list)
    {
        p_run_next = p_run->next;
        free(p_run);
        p_run = p_run_next;
    }
    free(p_list);
    *ppvnodeptptr_list = NULL;
    return (SUCCESS);
}

/* Graph - BFS Queue - List Auxillary */
void generic_insert_vnodeptr(vnodeptr_node_t *pvnodeptr_node_beg, vnodeptr_node_t *pvnodeptr_node_mid, vnodeptr_node_t *pnodeptr_node_end)
{
    pvnodeptr_node_beg->next = pvnodeptr_node_mid;
    pvnodeptr_node_mid->next = pvnodeptr_node_end;
    pvnodeptr_node_end->prev = pvnodeptr_node_mid;
    pvnodeptr_node_mid->prev = pvnodeptr_node_beg;
}

void generic_delete_vnodeptr(vnodeptr_node_t *pvnodeptr_delete_node)
{
    pvnodeptr_delete_node->next->prev = pvnodeptr_delete_node->prev;
    pvnodeptr_delte_node->prev->next = pvnodeptr_delelte_node->next;
    free(pvnodeptr_delete_node);
    pnodeptr_delelte_node = NULL;
}

vnodeptr_node_t* get_vnodeptr_node(vnode_t *pv_new_node)
{
    vnodeptr_node_t *p_vnodeptr = NULL;
    p_vnodeptr = (vnodeptr_node_t*)xcalloc(1, sizeof(vnodeptr_node_t));
    p_vnodeptr->pv_node = pv_new_node;
    return (p_vnodeptr);
}

/* graph - auxillary routines - memory management */
void* xcalloc(size_t nr_elements, size_t size_per_element)
{
    void *p = NULL;
    p = calloc(nr_elements, size_per_element);
    assert(p);
    return (p);
}