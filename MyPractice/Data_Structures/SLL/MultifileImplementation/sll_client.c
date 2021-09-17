#include "sll.h"

int main (void){
    sll_list_t *p_list = NULL;
    sll_list_t *p_list1 = NULL, *p_list2 = NULL;
    sll_list_t *p_concat_lists = NULL, *p_merged_list = NULL;
    sll_list_t *p_reversed_list = NULL;
    p_list = create_sll();
    int data;
    status_t s;

    sll_show_list(p_list, "Before insert_end(): ");
    for(data = 1; data <= 5; data++){
        s = sll_insert_end(p_list, data);
        assert(s == SUCCESS);
    }
    sll_show_list(p_list, "After insert_end(): ");
    
    for(data = 6; data <= 10; data++){
        s = sll_insert_beg(p_list, data);
        assert(s == SUCCESS);
    }
    sll_show_list(p_list, "After insert_beg(): ");

    s = sll_insert_after(p_list, 5, 100);
    assert(s == SUCCESS);
    sll_show_list(p_list, "After insert_after(): ");
    
    s = sll_insert_before(p_list, 5, 200);
    assert(s == SUCCESS);
    sll_show_list(p_list, "After insert_before(): ");

    s = sll_get_beg(p_list, &data);
    assert(s == SUCCESS);
    printf("beg_data: %d\n", data);

    s = sll_get_end(p_list, &data);
    assert(s == SUCCESS);
    printf("end_data: %d\n", data);

    s = sll_pop_beg(p_list, &data);
    assert(s == SUCCESS);
    printf("poped begining: %d\n", data);
    sll_show_list(p_list, "After pop_beg(): ");

    s = sll_pop_end(p_list, &data);
    assert(s == SUCCESS);
    printf("poped end: %d\n", data);
    sll_show_list(p_list, "After pop_end(): ");

    s = sll_remove_beg(p_list);
    assert(s == SUCCESS);
    sll_show_list(p_list, "After remove_beg(): ");
    
    s = sll_remove_end(p_list);
    assert(s == SUCCESS);
    sll_show_list(p_list, "After remove_end(): ");

    s = sll_remove_data(p_list, 6);
    assert(s == SUCCESS);
    sll_show_list(p_list, "After remove_data(6): ");

    printf("lenght of p_list = %d\n", sll_get_length(p_list));

    if(sll_contains(p_list, 7)){
        printf("list contains 7\n");
    }

    printf("repeat count of 8 = %d\n", sll_get_repeat_count(p_list, 8));

    p_list1 = create_sll();
    p_list2 = create_sll();
    
    for(data = 1; data <= 10; data++){
        s = sll_insert_end(p_list1, data * 10);
        assert(s == SUCCESS);
        s = sll_insert_end(p_list2, (data * 10) + 5);
        assert(s == SUCCESS);
    }

    sll_show_list(p_list1, "list1: ");
    sll_show_list(p_list2, "list2: ");

    p_concat_lists = sll_concat_lists(p_list1, p_list2);
    sll_show_list(p_concat_lists, "concat version of list1 and list2: ");
    p_merged_list = sll_merge_lists(p_list1, p_list2);
    sll_show_list(p_merged_list, "merged version of list1 and list2: ");

    p_reversed_list = create_sll();
    p_reversed_list = sll_get_reversed_list(p_list1);
    sll_show_list(p_reversed_list, "reversed version of list1: ");

    s = sll_append_list(p_list1, p_list2);
    assert(s == SUCCESS);
    sll_show_list(p_list1, "list2 is appended to list1: ");

    sll_destroy_list(&p_list);
    sll_destroy_list(&p_list1);
    sll_destroy_list(&p_reversed_list);

    return (EXIT_SUCCESS);
}
