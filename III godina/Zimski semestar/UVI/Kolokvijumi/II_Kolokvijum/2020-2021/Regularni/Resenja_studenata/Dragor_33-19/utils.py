# Univerzalna klasa za Queue

class Queue:
    def __init__(self, sort_fn = None):
        self.sort_fn = sort_fn
        self.queue = []
    
    def append(self, element):
        n = len(self.queue)
        pos = n
        
        if self.sort_fn != None:
            for i in range(n):
                if self.sort_fn(element) < self.sort_fn(self.queue[i]):
                    pos = i; break
        
        self.queue.insert(pos, element)

    def pop(self):
        return self.queue.pop(0)

    def remove(self, el):
        self.queue.remove(el)

    def find(self, find_fn):
        for e in self.queue:
            if find_fn(e):
                return e

    def index(self, element):
        for i in range(len(self.queue)):
            if element == self.queue[i]:
                return i
        return None

    def __len__(self):
        return len(self.queue)


# Kopiranje stanja (format: Lista listi)
def clone_state(state):
    clone = []
    for t in state:
        clone.append([x for x in t])
    return clone

# Lepsi ispis resenja
def print_solution(sol):
    for s in sol:
        for t in s:
            i = 4
            for x in t:
                print(x, end=' ')
                i -= 1
            while i > 0:
                print(' ', end=' ')
                i -= 1
            
            print('', end='   ')
        print()
    print('broj koraka:', len(sol))
