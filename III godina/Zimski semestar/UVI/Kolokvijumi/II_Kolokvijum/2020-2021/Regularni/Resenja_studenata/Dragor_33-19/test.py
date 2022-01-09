from search import *

problem = Problem()

# BFS
print('\nBFS')
sol = bfs(problem)
print_solution(sol)

# A-Star
def heuristics(node):
    n = 0
    for t in node.state:
        if len(set(t)) > 1:
            n += 1
    return n

print('\nA-Star')
sol = a_star(problem, heuristics)
print_solution(sol)
