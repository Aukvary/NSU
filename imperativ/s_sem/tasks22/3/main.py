from list import List
import sys


def main():
    try:
        fin = open("input.txt", "r")
        fout = open("output.txt", "w")
    except FileNotFoundError:
        print("Error: cannot open input.txt", file=sys.stderr)
        return 1

    lst = List()

    for line in fin:
        parts = line.strip().split()
        if not parts:
            continue

        cmd = parts[0]

        if cmd == "push_front":
            val = int(parts[1])
            lst.push_front(val)
            fout.write(f"push_front {val} done\n")

        elif cmd == "push_back":
            val = int(parts[1])
            lst.push_back(val)
            fout.write(f"push_back {val} done\n")

        elif cmd == "pop_front":
            val = lst.pop_front()
            if val is not None:
                fout.write(f"pop_front = {val}\n")
            else:
                fout.write("pop_front: list is empty\n")

        elif cmd == "pop_back":
            val = lst.pop_back()
            if val is not None:
                fout.write(f"pop_back = {val}\n")
            else:
                fout.write("pop_back: list is empty\n")

        elif cmd == "front":
            val = lst.front()
            if val is not None:
                fout.write(f"front = {val}\n")
            else:
                fout.write("front: list is empty\n")

        elif cmd == "back":
            val = lst.back()
            if val is not None:
                fout.write(f"back = {val}\n")
            else:
                fout.write("back: list is empty\n")

        elif cmd == "size":
            fout.write(f"size = {len(lst)}\n")

        elif cmd == "empty":
            fout.write(f"empty = {'yes' if not lst else 'no'}\n")

        elif cmd == "clear":
            lst.clear()
            fout.write("clear done\n")

        elif cmd == "at":
            idx = int(parts[1])
            try:
                val = lst[idx]
                fout.write(f"lst[{idx}] = {val}\n")
            except IndexError:
                fout.write(f"lst[{idx}] - index out of range\n")

        elif cmd == "insert":
            idx = int(parts[1])
            val = int(parts[2])
            if lst.insert(idx, val):
                fout.write(f"insert {val} at {idx} done\n")
            else:
                fout.write(f"insert at {idx} failed\n")

        elif cmd == "remove":
            val = int(parts[1])
            if lst.remove(val):
                fout.write(f"remove {val} done\n")
            else:
                fout.write(f"remove {val} not found\n")

        elif cmd == "pop":
            if len(parts) > 1:
                idx = int(parts[1])
            else:
                idx = -1
            val = lst.pop(idx)
            if val is not None:
                fout.write(f"pop({idx}) = {val}\n")
            else:
                fout.write(f"pop({idx}) - index out of range\n")

        elif cmd == "index":
            val = int(parts[1])
            idx = lst.index(val)
            if idx != -1:
                fout.write(f"index of {val} = {idx}\n")
            else:
                fout.write(f"index of {val} not found\n")

        elif cmd == "contains":
            val = int(parts[1])
            fout.write(f"contains {val} = {'yes' if val in lst else 'no'}\n")

        elif cmd == "sort":
            lst.sort()
            fout.write("sort done\n")

        elif cmd == "print":
            fout.write(f"{lst}\n")

        elif cmd == "destroy":
            del lst
            lst = List()
            fout.write("destroy done\n")

        else:
            fout.write(f"Unknown command: {cmd}\n")

    fin.close()
    fout.close()
    return 0


if __name__ == "__main__":
    sys.exit(main())