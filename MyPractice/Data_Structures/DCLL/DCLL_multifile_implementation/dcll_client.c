#include "dcll.h"

int main(void){
    dcll_list_t *p_list = NULL, *p_list1 = NULL, *p_list2 = NULL;
    dcll_list_t *p_merge_lists = NULL, *p_concat_lists = NULL, *p_reversed_list = NULL;
    int i;
    data_t data;
    status_t s;

    p_list = create_dcll();
    
    for(i = 1; i<=10; i++){
        s = dcll_insert_beg(p_list, i);
        assert(s == SUCCESS);
    }
    dcll_show_list(p_list, "p_list after insert_beg(): ");

    for(i = 11; i<=20; i++){
        s = dcll_insert_end(p_list, i);
        assert(s == SUCCESS);
    }
    dcll_show_list(p_list, "p_list after insert_end(): ");

    s = dcll_insert_beg(p_list, 100);
    assert(s == SUCCESS);
    dcll_show_list(p_list, "p_list after insert_beg(): ");

    s = dcll_insert_end(p_list, 200);
    assert(s == SUCCESS);
    dcll_show_list(p_list, "p_list after insert_end(): ");

    s = dcll_insert_after(p_list, 1, 100);
    assert(s == SUCCESS);
    dcll_show_list(p_list, "p_list after insert_after(): ");

    s = dcll_insert_before(p_list, 1, 200);
    assert(s == SUCCESS);
    dcll_show_list(p_list, "p_list after insert_before(): ");

    s = dcll_get_beg(p_list, &data);
    assert(s == SUCCESS);
    printf("beg: %d\n", data);

    s = dcll_get_end(p_list, &data);
    assert(s == SUCCESS);
    printf("end: %d\n", data);

    s = dcll_pop_beg(p_list, &data);
    assert(s == SUCCESS);
    printf("poped beg: %d\n", data);

    s = dcll_pop_end(p_list, &data);
    assert(s == SUCCESS);
    printf("poped end: %d\n", data);

    s = dcll_remove_beg(p_list);
    assert(s == SUCCESS);

    s = dcll_remove_end(p_list);
    assert(s == SUCCESS);

    s = dcll_remove_data(p_list, 1);
    assert(s == SUCCESS);

    dcll_show_list(p_list, "p_list after remove beg, end, 1: ");
    
    p_list1 = create_dcll();
    p_list2 = create_dcll();

    for(i = 0; i<10; i++){
        s = dcll_insert_end(p_list1, i*10);
        assert(s == SUCCESS);
        s = dcll_insert_end(p_list2, (i*10)+5);
        assert(s == SUCCESS);
    }

    dcll_show_list(p_list1, "p_list1: ");
    dcll_show_list(p_list2, "p_list2: ");

    p_merge_lists = dcll_merge_lists(p_list1, p_list2);
    dcll_show_list(p_merge_lists, "p_merge_lists: ");

    p_concat_lists = dcll_concat_lists(p_list1, p_list2);
    dcll_show_list(p_concat_lists, "p_concat_lists: ");

    p_reversed_list = dcll_reversed_list(p_list);
    dcll_show_list(p_reversed_list, "p_reversed_list: ");

    s = dcll_append_lists(p_list1, p_list2);
    assert(s == SUCCESS);
    dcll_show_list(p_list1, "list2 is appended to list1: ");

    s = dcll_reverse_list(p_list1);
    assert(s == SUCCESS);
    dcll_show_list(p_list1, "after reversing list1: ");

    return EXIT_SUCCESS;
}