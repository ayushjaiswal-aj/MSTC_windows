#include "scll.h"

int main(void){
    scll_list_t *p_list = NULL, *p_list1 = NULL, *p_list2 = NULL;
    scll_list_t *p_concat_list = NULL, *p_reversed_list = NULL, *p_merged_list = NULL, *p_array_to_list = NULL;
    p_list = create_scll();
    status_t s;
    data_t data;

    scll_show_list(p_list, "After create list: ");
    for(data = 1; data <= 10; data++){
        s = scll_insert_beg(p_list, data);
        assert(s == SUCCESS);
    }
    scll_show_list(p_list, "after insert_beg(): ");

    for(data = 11; data <= 20; data++){
        s = scll_insert_end(p_list, data);
        assert(s == SUCCESS);
    }
    scll_show_list(p_list, "After insert end(): ");

    s = scll_insert_after(p_list, 20, 100);
    assert(s == SUCCESS);
    scll_show_list(p_list, "after insert_after(): ");

    s = scll_insert_before(p_list, 10, 200);
    assert(s  == SUCCESS);
    scll_show_list(p_list, "after insert_before(): ");

    s = scll_get_beg(p_list, &data);
    assert(s == SUCCESS);
    printf("beg data of p_list = %d\n", data);

    s = scll_get_end(p_list, &data);
    assert(s == SUCCESS);
    printf("end data of p_list = %d\n", data);

    s = scll_pop_beg(p_list, &data);
    assert(s == SUCCESS);
    printf("begining poped data: %d\n", data);
    scll_show_list(p_list, "pop_bed(): ");

    s = scll_pop_end(p_list, &data);
    assert(s == SUCCESS);
    printf("end poped data: %d\n", data);
    scll_show_list(p_list, "after pop_end(): ");

    printf("length of p_list = %d\n", scll_get_length(p_list));

    printf("repeat count of 8 is: %d\n", scll_get_repeat_count(p_list, 8));

    p_list1 = create_scll();
    p_list2 = create_scll();
    for(data = 1; data < 10; data ++){
        scll_insert_end(p_list1, (data * 10));
        scll_insert_end(p_list2, (data * 10) + 5);
    }

    scll_show_list(p_list1, "list1: ");
    scll_show_list(p_list2, "list2: ");

    p_concat_list = scll_concat_lists(p_list1, p_list2);
    scll_show_list(p_concat_list, "list1 and list2 are concatinated: ");

    p_merged_list = scll_merge_lists(p_list1, p_list2);
    scll_show_list(p_merged_list, "list1 and list2 are merged: ");

    scll_show_list(p_list, "list p_list: ");
    p_reversed_list = scll_reversed_list(p_list);
    scll_show_list(p_reversed_list, "reversed version of p_list: ");

    s = scll_append_list(p_list1, p_list2);
    assert(s == SUCCESS);
    scll_show_list(p_list1, "list2 is appended to list1: ");

    s = scll_reverse_list(p_list1);
    assert(s == SUCCESS);
    scll_show_list(p_list1, "after reversing p_list1: ");

    return (EXIT_SUCCESS);
}