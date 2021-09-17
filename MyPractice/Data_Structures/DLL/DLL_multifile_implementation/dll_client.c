#include "dll.h"

int main(void){
    dll_list_t *p_list = NULL, *p_list1 = NULL, *p_list2 = NULL;
    dll_list_t *p_concat_list = NULL, *p_reversed_list = NULL, *p_merged_list = NULL, *p_array_to_list = NULL;
    p_list = create_dll();
    status_t s;
    data_t data;

    dll_show_list(p_list, "After create list: ");
    for(data = 1; data <= 10; data++){
        s = dll_insert_beg(p_list, data);
        assert(s == SUCCESS);
    }
    dll_show_list(p_list, "after insert_beg(): ");

    for(data = 11; data <= 20; data++){
        s = dll_insert_end(p_list, data);
        assert(s == SUCCESS);
    }
    dll_show_list(p_list, "After insert end(): ");

    s = dll_insert_after(p_list, 20, 100);
    assert(s == SUCCESS);
    dll_show_list(p_list, "after insert_after(): ");

    s = dll_insert_before(p_list, 10, 200);
    assert(s  == SUCCESS);
    dll_show_list(p_list, "after insert_before(): ");

    s = dll_get_beg(p_list, &data);
    assert(s == SUCCESS);
    printf("beg data of p_list = %d\n", data);

    s = dll_get_end(p_list, &data);
    assert(s == SUCCESS);
    printf("end data of p_list = %d\n", data);

    s = dll_pop_beg(p_list, &data);
    assert(s == SUCCESS);
    printf("begining poped data: %d\n", data);
    dll_show_list(p_list, "pop_bed(): ");

    s = dll_pop_end(p_list, &data);
    assert(s == SUCCESS);
    printf("end poped data: %d\n", data);
    dll_show_list(p_list, "after pop_end(): ");

    printf("length of p_list = %d\n", dll_get_length(p_list));

    printf("repeat count of 8 is: %d\n", dll_get_repeat_count(p_list, 8));

    p_list1 = create_dll();
    p_list2 = create_dll();

    dll_show_list(p_list1, "p_list1: ");
    dll_show_list(p_list2, "p_list2: ");

    for(data = 1; data < 10; data ++){
        s = dll_insert_end(p_list1, (data * 10));
        assert(s == SUCCESS);
        s = dll_insert_end(p_list2, (data * 10) + 5);
        assert(s == SUCCESS);
    }

    dll_show_list(p_list1, "list1: ");
    dll_show_list(p_list2, "list2: ");

    p_concat_list = dll_concat_lists(p_list1, p_list2);
    dll_show_list(p_concat_list, "list1 and list2 are concatinated: ");

    p_merged_list = dll_merge_lists(p_list1, p_list2);
    dll_show_list(p_merged_list, "list1 and list2 are merged: ");

    dll_show_list(p_list, "list p_list: ");
    p_reversed_list = dll_reversed_list(p_list);
    dll_show_list(p_reversed_list, "reversed version of p_list: ");

    s = dll_append_lists(p_list1, p_list2);
    assert(s == SUCCESS);
    dll_show_list(p_list1, "list2 is appended to list1: ");

    s = dll_reverse_list(p_list1);
    assert(s == SUCCESS);
    dll_show_list(p_list1, "after reversing p_list1: ");

    return (EXIT_SUCCESS);
}