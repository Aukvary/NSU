#include <fstream>
#include <string>
#include "vector.h"

enum Command
{
    CMD_PUSH,
    CMD_POP,
    CMD_SIZE,
    CMD_CAPACITY,
    CMD_AT,
    CMD_FRONT,
    CMD_BACK,
    CMD_RESIZE,
    CMD_CLEAR,
    CMD_EMPTY,
    CMD_PRINT,
    CMD_RESERVE,
    CMD_DESTROY,
    CMD_UNKNOWN
};

Command parseCommand(const std::string &cmd)
{
    if (cmd == "push")
        return CMD_PUSH;
    else if (cmd == "pop")
        return CMD_POP;
    else if (cmd == "size")
        return CMD_SIZE;
    else if (cmd == "capacity")
        return CMD_CAPACITY;
    else if (cmd == "at")
        return CMD_AT;
    else if (cmd == "front")
        return CMD_FRONT;
    else if (cmd == "back")
        return CMD_BACK;
    else if (cmd == "resize")
        return CMD_RESIZE;
    else if (cmd == "clear")
        return CMD_CLEAR;
    else if (cmd == "empty")
        return CMD_EMPTY;
    else if (cmd == "print")
        return CMD_PRINT;
    else if (cmd == "reserve")
        return CMD_RESERVE;
    else if (cmd == "destroy")
        return CMD_DESTROY;
    else
        return CMD_UNKNOWN;
}

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    if (!fin.is_open())
    {
        fout << "Error: cannot open input.txt" << std::endl;
        return 1;
    }

    vector_t *vec = vector_create();
    std::string cmd;
    int arg;

    while (fin >> cmd)
    {
        Command c = parseCommand(cmd);

        switch (c)
        {
        case CMD_PUSH:
            fin >> arg;
            vector_push_back(vec, arg);
            fout << "push " << arg << " done" << std::endl;
            break;

        case CMD_POP:
            vector_pop_back(vec);
            fout << "pop done" << std::endl;
            break;

        case CMD_SIZE:
            fout << "Size: " << vector_size(vec) << std::endl;
            break;

        case CMD_CAPACITY:
            fout << "Capacity: " << vector_capacity(vec) << std::endl;
            break;

        case CMD_AT:
            fin >> arg;
            {
                int val;
                if (vector_at(vec, arg, &val))
                {
                    fout << "vec[" << arg << "] = " << val << std::endl;
                }
                else
                {
                    fout << "vec[" << arg << "] - index out of range" << std::endl;
                }
            }
            break;

        case CMD_FRONT:
            {
                int val;
                if (vector_front(vec, &val))
                {
                    fout << "Front: " << val << std::endl;
                }
                else
                {
                    fout << "Front: vector is empty" << std::endl;
                }
            }
            break;

        case CMD_BACK:
            {
                int val;
                if (vector_back(vec, &val))
                {
                    fout << "Back: " << val << std::endl;
                }
                else
                {
                    fout << "Back: vector is empty" << std::endl;
                }
            }
            break;

        case CMD_RESIZE:
            fin >> arg;
            {
                int default_val;
                fin >> default_val;
                vector_resize(vec, arg, default_val);
                fout << "resize to " << arg << " with default " << default_val << " done" << std::endl;
            }
            break;

        case CMD_CLEAR:
            vector_clear(vec);
            fout << "clear done" << std::endl;
            break;

        case CMD_EMPTY:
            fout << "Empty: " << (vector_empty(vec) ? "yes" : "no") << std::endl;
            break;

        case CMD_PRINT:
            {
                const int *data = vector_data(vec);
                size_t sz = vector_size(vec);
                fout << "[";
                for (size_t i = 0; i < sz; ++i)
                {
                    fout << data[i];
                    if (i < sz - 1)
                        fout << ", ";
                }
                fout << "]" << std::endl;
            }
            break;

        case CMD_RESERVE:
            {
                size_t new_cap;
                fin >> new_cap;
                vector_reserve(vec, new_cap);
                fout << "reserve " << new_cap << " done" << std::endl;
            }
            break;

        case CMD_DESTROY:
            vector_destroy(vec);
            fout << "destroy done" << std::endl;
            vec = nullptr;
            break;

        case CMD_UNKNOWN:
        default:
            fout << "Unknown command: " << cmd << std::endl;
            break;
        }
    }

    if (vec != nullptr)
    {
        vector_destroy(vec);
    }

    fin.close();
    fout.close();
    return 0;
}