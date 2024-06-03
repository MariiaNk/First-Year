#include <iostream>
#include <cassert>

struct Node
{
    int value;
    Node *next;

    Node(int value, Node *next = nullptr) : value(value), next(next) {}
};
// вузол для стисло-зв'язного зберігання
struct SparseNode
{
    int value;
    int position;
    SparseNode *prev;
    SparseNode *next;

    SparseNode(int value, int position, SparseNode *prev = nullptr, SparseNode *next = nullptr)
        : value(value), position(position), prev(prev), next(next) {}
};

// список у стисло-звязному зберіганні 
struct SparseList
{
    SparseNode *start;
    SparseNode *end;
    int total_size;
    int default_value;

    SparseList(SparseNode *start = nullptr, SparseNode *end = nullptr, int total_size = 0, int default_value = 0)
        : start(start), end(end), total_size(total_size), default_value(default_value) {}
};

void push_back(SparseList &list, int value, int position)
{
    assert(position >= 0);
    assert(position >= list.total_size);
    if (list.end != nullptr)
    {
        assert(list.end->position < position);
    }
    list.total_size = position + 1;
    if (value == list.default_value)
    {
        return;
    }
    SparseNode *new_node = new SparseNode(value, position, list.end);
    if (list.end == nullptr)
    {
        assert(new_node->prev == nullptr);
        list.start = new_node;
    }
    else
    {
        list.end->next = new_node;
    }
    list.end = new_node;
}
/*Список F з цілих чисел, більшість якого дорівнюють 0, представлений своїм зв’язним зберіганням. 
Написати функцію для представлення F стислим зв’язним зберіганням*/
SparseList list_to_sparse_list(Node *input_head, int input_size, int default_value = 0)
{
    SparseList result;
    result.default_value = default_value;

    Node *current = input_head;
    int current_position = 0;

    while (current != nullptr)
    {
        if (current->value != default_value)
        {
            push_back(result, current->value, current_position);
        }
        current_position++;
        current = current->next;
    }

    result.total_size = input_size;
    return result;
}

/*До лінійного списку F з m цілих чисел, більшість з яких дорівнюють 0, застосовано стисле зв’язне зберігання. 
Написати функцію для визначення номера першого за порядком елемента зі значенням 0.*/
int find_first_default(SparseList list)
{
    SparseNode *current = list.start;
    if (current != nullptr && current->position != 0)
        return 0;

    int prev_position = (current != nullptr) ? current->position : -1;
    if (current != nullptr)
        current = current->next;

    while (current)
    {
        if (current->position - prev_position != 1)
        {
            return prev_position + 1;
        }
        prev_position = current->position;
        current = current->next;
    }

    if (prev_position + 1 == list.total_size)
        return -1;

    return prev_position + 1;
}

void print(SparseList list)
{
    SparseNode *current = list.start;
    int index = 0;
    while (current)
    {
        while (current->position > index)
        {
            std::cout << list.default_value << " ";
            index++;
        }
        std::cout << current->value << " ";
        current = current->next;
        index++;
    }
    for (int i = index; i < list.total_size; i++)
    {
        std::cout << list.default_value << " ";
    }
    std::cout << std::endl;
}


/*До лінійного списку F з m цілих чисел, більшість з яких дорівнюють 0, застосовано стисле зв’язне зберігання.
Написати функцію для визначення кількості елементів із значенням 0, номери яких належать інтервалу [i,j].*/
int count_default_in_range(SparseList list, int st, int fn)
{
    if(st < 0 || fn < 0 || st >= list.total_size || fn >= list.total_size || st > fn) return 0;

    SparseNode* current = list.start;
    int count = fn - st + 1;

    while(current && current->position <= fn)
    {
        if(current->position >= st)
            count--;
        current = current->next;
    }

    return count;
}

void print_as_linked_list(SparseList list)
{
    SparseNode *current = list.start;
    while (current)
    {
        std::cout << current->value << "[" << current->position << "] ";
        current = current->next;
    }
    std::cout << "total_size = " << list.total_size << std::endl;
}

Node *create_input_linked_list_from_array(int *arr, int size)
{
    if (size == 0)
        return nullptr;

    Node *head = new Node(arr[0]);
    Node *current = head;
    for (int i = 1; i < size; ++i)
    {
        Node *new_node = new Node(arr[i]);
        current->next = new_node;
        current = new_node;
    }
    return head;
}

int main()
{
    SparseList list;

    push_back(list, 1, 1);
    push_back(list, 2, 4);
    push_back(list, 3, 6);
    push_back(list, 5, 12);

    print(list);

    int arr[] = {0, 1, 0, 0, 2, 0, 3, 0, 0, 0, 0, 0, 5, 0, 0};
    Node *input_head = create_input_linked_list_from_array(arr, sizeof(arr) / sizeof(arr[0]));
    SparseList list2 = list_to_sparse_list(input_head, sizeof(arr) / sizeof(arr[0]));
    print(list2);
    print_as_linked_list(list2);

    int count = count_default_in_range(list2, 13, 14);
    std::cout << "Count 0 in range 13 to 14: " << count << std::endl;
    /*std::cout << "First default at position " << find_first_default(list2) << std::endl;

    int arr_in_middle[] = {1, 1, 0, 2, 0};
    Node *input_head_in_middle = create_input_linked_list_from_array(arr_in_middle, sizeof(arr_in_middle) / sizeof(arr_in_middle[0]));
    SparseList in_middle = list_to_sparse_list(input_head_in_middle, sizeof(arr_in_middle) / sizeof(arr_in_middle[0]));
    print(in_middle);
    std::cout << "First default at position " << find_first_default(in_middle) << std::endl;

    int arr_at_end[] = {1, 1, -1, 2, 0, 0};
    Node *input_head_at_end = create_input_linked_list_from_array(arr_at_end, sizeof(arr_at_end) / sizeof(arr_at_end[0]));
    SparseList at_end = list_to_sparse_list(input_head_at_end, sizeof(arr_at_end) / sizeof(arr_at_end[0]));
    print(at_end);
    std::cout << "First default at position " << find_first_default(at_end) << std::endl;

    int arr_no_defaults[] = {1, 1, 2};
    Node *input_head_no_defaults = create_input_linked_list_from_array(arr_no_defaults, sizeof(arr_no_defaults) / sizeof(arr_no_defaults[0]));
    SparseList no_defaults = list_to_sparse_list(input_head_no_defaults, sizeof(arr_no_defaults) / sizeof(arr_no_defaults[0]));
    print(no_defaults);
    std::cout << "First default at position " << find_first_default(no_defaults) << std::endl;*/

    return 0;
}
