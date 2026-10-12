int compute() { return 5; }
int& base() { static int b = compute(); return b; }
