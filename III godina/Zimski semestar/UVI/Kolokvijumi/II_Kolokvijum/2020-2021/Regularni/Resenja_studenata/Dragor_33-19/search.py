from utils import *

class Problem:
    def __init__(self):
        # self.initial = [['p','z','c','p'],['z','z','c','p'],['c','p','z','c'],[],[]]
        # self.initial = [['p','z','c','p'],['z','z','c','p'],['c','p'],['c'],['z']]
        self.initial = [['c','z','p'],['z','c','p'],['p','c','z'],['p','z','c'],[]]

    def is_move_valid(self, old_state, move):
        old_i, new_i = move
        old_n = len(old_state[old_i])
        new_n = len(old_state[new_i])

        if old_n == 0 or new_n == 4 or old_i == new_i:
            return False

        if new_n == 0 or old_state[old_i][old_n-1] == old_state[new_i][new_n-1]:
            return True
        
        return False

    def actions(self, state):
        succ = []
        for old_i in range(len(state)):
            for new_i in range(len(state)):
                if self.is_move_valid(state, (old_i, new_i)):
                    new_state = clone_state(state)
                    new_state[new_i].append(new_state[old_i].pop())
                    succ.append(new_state)
        return succ

    def is_goal(self, state):
        for tube in state:
            unique = set(tube)
            if len(unique) > 1:
                return False
        return True


class Node:
    def __init__(self, state, parent = None, path_cost = 0):
        self.state = state
        self.parent = parent
        self.path_cost = path_cost
        self.depth = 0 if parent == None else parent.depth

    def expand(self, problem):
        successors = []
        for s in problem.actions(self.state):
            successors.append(Node(s, self, path_cost=self.path_cost+1))
        return successors

    def solution(self):
        path = []
        node = self
        while node != None:
            path = [node.state] + path
            node = node.parent
        return path



# Search algorithms
    
def graph_search(problem, open_nodes, optimize = False):
    
    explored_states = [problem.initial]
    open_nodes.append(Node(problem.initial))
    
    while len(open_nodes) > 0:
        node = open_nodes.pop()

        # Pronadjeno ciljno stanje
        if problem.is_goal(node.state):
            return node.solution()
        
        # Razvijanje trenutnog cvora
        for new_node in node.expand(problem):

            # Novo stanje
            if new_node.state not in explored_states:
                open_nodes.append(new_node)
                explored_states.append(new_node.state)

            # Postojece stanje, optimizacija puta
            elif optimize:
                open_nodes.append(new_node)
                old_node = open_nodes.find(lambda x: x.state == new_node.state)

                if open_nodes.index(new_node) < open_nodes.index(old_node):
                    open_nodes.remove(old_node)
                else:
                    open_nodes.remove(new_node)
    
    return None


def bfs(problem):
    return graph_search(problem, Queue())

def a_star(problem, h):
    return graph_search(problem, Queue(lambda x: x.path_cost + h(x)), optimize=True)