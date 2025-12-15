class Array {
    const int dim;  // 몇 차원 배열인지
    int *size;  // size[0] * size[1] * ... * size[dim - 1]짜리 배열이다.

    struct Address {
        int level;
        // 맨 마지막 레벨(dim - 1 레벨) 은 데이터 배열을 가리키고, 그 위 상위 레벨에서는 다음 Address 배열을 가리킨다.
        void *next;
    };
    Address *top;

public:
    void initialize_address(Address *current) {
        if (!current) return;
        if (current->level == dim - 1) {
            current->next = new int[size[current->level]];
            return;
        }
        current->next = new Address[size[current->level]];
        for (int i = 0; i != size[current->level]; i++) {
            (static_cast<Address *>(current->next) + i)->level = current->level + i;

            initialize_address(static_cast<Address *>(current->next) + i);
        }
    }

    void delete_address(Address *current) {
        if (!current) return;
        for (int i = 0; current->level < dim - 1 && i < size[current->level]; i++) {
            delete_address(static_cast<Address *>(current->next) + i);
        }
        if (current -> level == dim - 1) {
            delete[] static_cast<int *>(current->next);
        }
        delete[] static_cast<Address *>(current->next);
    }

    Array(int dim, int *array_size) : dim(dim) {
        size = new int[dim];
        for (int i = 0; i < dim; i++) size[i] = array_size[i];

        top = new Address;
        top->level = 0;

        initialize_address(top);
    }
    Array(const Array &arr) : dim(arr.dim) {
        size = new int[dim];
        for (int i = 0; i < dim; i++) size[i] = arr.size[i];

        top = new Address;
        top->level = 0;

        copy_address(top, arr.top);
    }

    void copy_address(Address *dst, Address *src) {
        if (dst->level == dim - 1) {
            for (int i = 0; i < size[dst->level]; ++i)
                static_cast<int *>(dst->next)[i] = static_cast<int *>(src->next)[i];
            return;
        }
        for (int i = 0; i != size[dst->level]; i++) {
            Address *new_dst = static_cast<Address *>(dst->next) + i;
            Address *new_src = static_cast<Address *>(src->next) + i;
            copy_address(new_dst, new_src);
        }
    }

    ~Array() {
        delete_address(top);
        delete[] size;
    }

    
    Address& operator[](int index) {

    }
}