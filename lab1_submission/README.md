# Written answers

Exercise 1: Memory Scaling Analysis
The experiments show that adjacency matrix memory usage grows quadratically with the number of nodes. Because the matrix must reserve space for every possible connection, the memory requirement scales as O(V²), even when the graph is sparse. In contrast, adjacency lists scale roughly with the number of edges, making them significantly more memory-efficient for large sparse networks.
The matrix becomes impractical once node counts reach tens of thousands because memory requirements increase rapidly. At around 50,000 nodes the matrix already consumes roughly 20GB, leaving little room for the operating system or other processes. Estamating this growth suggests a 200,000 node matrix would require about 320GB, which clearly does not fit into a 32GB system.

Exercise 2: Edge Query Benchmark
Matrix edge lookup is much faster because checking whether an edge exists is a direct array access which runs in constant time O(1). The adjacency list must scan through neighbors of a node to find a match, resulting in Odegree performance. This difference becomes obvious when running many random edge queries where the matrix consistently provides large speedups. The list representation is slower because it relies on iteration and pointer traversal which introduces additional CPU overhead and poor cache locality. Fast edge lookups matter most in applications that repeatedly ask whether two nodes are connected such as real time simulation systems, recommendation engines or dense graph algorithms that test adjacency frequently.

Exercise 3: Algorithm Performance
Even though matrices offer constant time edge checks matrix-based Dijkstra is slower on sparse graphs. The reason is that the algorithm must inspect all possible neighbors of a node, and with a matrix this means scanning an entire row every time. Adjacency lists only iterate through actual neighbors so they avoid unnecessary work when most connections do not exist. The slowdown occurs in the neighbor traversal loop where edge relaxations are performed. For sparse graphs scanning all vertices wastes time checking nonexistent edges. A matrix becomes competitive only when graphs are very dense, where most possible edges exist and scanning a full row closely matches the number of real neighbors.

Exercise 4: Breaking Point
When attempting to load the huge network using the matrix representation memory usage quickly rose from normal system levels to nearly full RAM capacity. As allocation continued, the system began swapping heavily adn performance degraded and the process eventually terminates due to memory exhaustion. This clearly demonstrated the practical limitation of O(V²) storage. This experiment highlights how theoretical complexity directly affects real systems. Even if an algorithm is logically correct hardware limits make certain representations impossible at scale. The adjacency matrix simply does not scale for large sparse networks on machines.

Exercise 5 — Real World Decision Making
For Google Maps routing, social networks and circuit graphs, adjacency lists are clearly the better choice because each node connects to only a small subset of all possible nodes. The sparse nature of these systems makes list storage efficient in both memory and traversal performance. Matrices would waste massive amounts of space representing nonexistent edges.

The dense communication matrix is the opposite case. Since nearly every node connects to every other node, matrix storage becomes reasonable and offers extremely fast edge lookups. This demonstrates that representation choice depends mainly on graph density, scale, and the dominant operations performed on the graph.

# Analysis

Adjacency List: 
. Large sparse graphs
. Memory constrained environments
. Traversal heavy algorithms (BFS, DFS, Dijkstra on sparse graphs)
. Real world networks where average degree is small

Adjacency Matrix:
. Small to medium dense graphs
. Frequent edge existence queries
. Situations requiring predictable O(1) lookup
. Cases where memory cost is acceptable

Hybrid Approach:
. Graphs with mixed density
. Systems containing dense clusters inside otherwise sparse structures
. Dynamic workloads where locality varies

# Reflection

The most surprising result was how quickly adjacency matrices become unusable as graph size increases. Even though the representation feels simple and efficient the memory explosion happened far earlier than expected. Watching system memory rapidly fill during the large experiment made the theoretical O(V²) cost very real. Another unexpected observation was that faster edge lookup did not translate into faster algorithms overall. I initially expected matrix based Dijkstra to perform better but the experiments showed that scanning unnecessary edges dominates runtime on sparse graphs. This shows the importance of understanding not only data structure operations but also how algorithms interact with those structures in practice.