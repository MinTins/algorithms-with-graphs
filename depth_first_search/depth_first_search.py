import networkx as nx
import matplotlib.pyplot as plt

# зчитуємо граф з файлу
with open('graph.txt', 'r') as f:
    n,m,start_node = map(int, f.readline().split())
    edges = [list(int(x) for  x in line.strip().split() ) for line in f.readlines()]


# створюємо граф
G = nx.Graph()
G.add_nodes_from(range(n))
G.add_edges_from(edges)

# рекурсивна функція для обходу графа в глибину
def dfs(v, visited, stack):
    visited[v] = True
    for u in G.neighbors(v):
        if not visited[u]:
            stack.append((v, u))
            dfs(u, visited, stack)


# обходимо граф в глибину
visited = [False] * n
stack = []
dfs(start_node, visited, stack)


pos = nx.spring_layout(G)
nx.draw_networkx_nodes(G, pos, node_color='lightblue')
nx.draw_networkx_nodes(G, pos, nodelist=[start_node], node_color='blue')
nx.draw_networkx_edges(G, pos, edgelist=[(x,y) for x,y in G.edges() if x!=y], edge_color='black', width=1)    
nx.draw_networkx_labels(G, pos, font_size=10, font_family="sans-serif")
plt.axis('off')

plt.savefig('temp0.png')
# виводимо послідовність ребер
step = 1

result = []
stack.reverse()
while stack:
    result.append(stack.pop())
    nx.draw_networkx_edges(G, pos, edgelist=result, edge_color='r', width=3)
    plt.savefig(f'temp{step}.png')
    step+=1

plt.savefig(f'temp{step}.png')

# об'єднуємо всі зображення у гіфку
import imageio.v2 as imageio

images = []
for i in range(step+1):
    filename = f'temp{i}.png'
    images.append(imageio.imread(filename))

duration = 5 / len(images)  
imageio.mimsave('result.gif', images, duration=duration)


import os

for i in range(step+1):
    filename = f'temp{i}.png'
    os.remove(filename)