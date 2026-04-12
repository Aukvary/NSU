import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner fin = null;
        PrintWriter fout = null;
        
        try {
            fin = new Scanner(new File("input.txt"));
            fout = new PrintWriter(new FileWriter("output.txt"));
        } catch (FileNotFoundException e) {
            System.err.println("Error: cannot open input.txt");
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Error: cannot create output.txt");
            System.exit(1);
        }

        Tree tree = new Tree();

        while (fin.hasNextLine()) {
            String line = fin.nextLine().trim();
            if (line.isEmpty()) {
                continue;
            }

            String[] parts = line.split("\\s+");
            String cmd = parts[0];

            switch (cmd) {
                case "insert": {
                    int key = Integer.parseInt(parts[1]);
                    long value = Long.parseLong(parts[2]);
                    boolean result = tree.insert(key, value);
                    fout.write("insert " + key + " " + value + " done\n");
                    break;
                }

                case "find": {
                    int key = Integer.parseInt(parts[1]);
                    long value = tree.findLong(key);
                    if (value != 0) {
                        fout.write("find " + key + " = " + value + "\n");
                    } else {
                        fout.write("find " + key + " not found\n");
                    }
                    break;
                }

                case "remove": {
                    int key = Integer.parseInt(parts[1]);
                    boolean result = tree.remove(key);
                    if (result) {
                        fout.write("remove " + key + " done\n");
                    } else {
                        fout.write("remove " + key + " not found\n");
                    }
                    break;
                }

                case "size": {
                    fout.write("size = " + tree.size() + "\n");
                    break;
                }

                case "empty": {
                    fout.write("empty = " + (tree.isEmpty() ? "yes" : "no") + "\n");
                    break;
                }

                case "clear": {
                    tree.clear();
                    fout.write("clear done\n");
                    break;
                }

                case "print": {
                    fout.write(tree.toString() + "\n");
                    break;
                }

                default:
                    fout.write("Unknown command: " + cmd + "\n");
                    break;
            }
        }

        if (fin != null) fin.close();
        if (fout != null) fout.close();
        tree.close();
    }
}
