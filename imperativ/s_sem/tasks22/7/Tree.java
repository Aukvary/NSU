public class Tree {

	// Native pointer to C tree structure
	private long nativePtr;

	// Load native library
	static {
		System.loadLibrary("rbtree");
	}

	// Native methods
	private native long createTree();

	private native void deleteTree(long ptr);

	private native boolean insert(long ptr, int key, long value);

	private native long find(long ptr, int key);

	private native boolean remove(long ptr, int key);

	private native int size(long ptr);

	private native boolean isEmpty(long ptr);

	private native void clear(long ptr);

	// Constructor
	public Tree() {
		this.nativePtr = createTree();
		if (this.nativePtr == 0) {
			throw new RuntimeException("Failed to create tree");
		}
	}

	// Insert key-value pair (value is stored as a reference)
	public boolean insert(int key, Object value) {
		return insert(nativePtr, key, (long) System.identityHashCode(value));
	}

	// Insert key with long value
	public boolean insert(int key, long value) {
		return insert(nativePtr, key, value);
	}

	// Find value by key
	public Object find(int key) {
		long ref = find(nativePtr, key);
		return ref != 0 ? getObjectByRef(ref) : null;
	}

	// Find long value by key
	public long findLong(int key) {
		return find(nativePtr, key);
	}

	// Remove key-value pair
	public boolean remove(int key) {
		return remove(nativePtr, key);
	}

	// Get tree size
	public int size() {
		return size(nativePtr);
	}

	// Check if tree is empty
	public boolean isEmpty() {
		return isEmpty(nativePtr);
	}

	// Clear tree
	public void clear() {
		clear(nativePtr);
	}

	// Clean up native resources
	public void close() {
		if (nativePtr != 0) {
			deleteTree(nativePtr);
			nativePtr = 0;
		}
	}

	// Helper to get object by reference (simplified - in real app use WeakHashMap)
	private static Object getObjectByRef(long ref) {
		// This is a simplified version. In real implementation,
		// you would maintain a mapping of references to objects
		return null;
	}

	// Inner class for tree traversal
	public interface Visitor {
		void visit(int key, Object value);
	}

	// In-order traversal (would need additional native method)
	// This is left as an exercise to implement

	// Get string representation of the tree
	@Override
	public String toString() {
		return toString(nativePtr);
	}

	private native String toString(long ptr);
}