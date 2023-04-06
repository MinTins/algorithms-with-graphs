import networkx as nx
import matplotlib.pyplot as plt

# зчитуємо граф з файлу
with open('graph.txt', 'r') as f:
    n, m, start_node = map(int, f.readline().split())
    edges = []
    for x in f.readlines():
        u, v, w = map(int, x.split())
        edges.append((u, v, w))

# створюємо граф
G = nx.Graph()
G.add_weighted_edges_from(edges)

# налаштування побудови
pos = nx.spring_layout(G)
nx.draw_networkx_nodes(G, pos, node_color='lightblue')
nx.draw_networkx_nodes(G, pos, nodelist=[start_node], node_color='blue')
nx.draw_networkx_labels(G, pos, font_size=10, font_family="sans-serif")
plt.axis('off')

# побудова початкового графа
real_edges = [(x,y) for x,y,w in edges if x!=y and w>0]

nx.draw_networkx_edges(G, pos, edgelist=real_edges, edge_color='black', width=1)    
edge_labels = nx.get_edge_attributes(G, "weight")
nx.draw_networkx_edge_labels(G, pos, {k:x for k,x in edge_labels.items() if k in real_edges})


# збереження початкового варіанту
plt.savefig(f'temp0.png')


# визначаємо стартову вершину
# start_node = 0 # визначили попередньо

# створюємо множину відвіданих вершин та множину ребер мінімального кістяка
visited = set([start_node])
mst = []

# кількість кроків алгоритму
step = 1

while len(visited) != n:
    # знаходимо всі ребра, що з'єднують відвідані та невідвідані вершини
    candidate_edges = []
    for u in visited:
        for u, v, w in G.edges(u, data=True):
            if v not in visited and w['weight'] > 0:
                candidate_edges.append((u, v, w['weight']))
    
    # знаходимо ребро з мінімальною вагою
    u, v, w = sorted(candidate_edges, key=lambda x: x[2])[0]
    
    # додаємо вершину до множини відвіданих та ребро до множини ребер мінімального кістяка
    visited.add(v)
    mst.append((u, v, w))
    
    # малюємо граф
    nx.draw_networkx_nodes(G, pos, nodelist=visited, node_color='g')
    nx.draw_networkx_nodes(G, pos, nodelist=[u,v], node_color='r')

    nx.draw_networkx_edges(G, pos, edgelist=mst, edge_color='g', width=3)    
    nx.draw_networkx_edges(G, pos, edgelist=[(u, v)], edge_color='r', width=3)

    plt.savefig(f'temp{step}.png')
    step += 1

# фінальний стан
nx.draw_networkx_nodes(G, pos, nodelist=visited, node_color='g')
nx.draw_networkx_edges(G, pos, edgelist=mst, edge_color='green', width=3)    
plt.savefig(f'temp{step}.png')

# об'єднуємо всі зображення у гіфку
import imageio.v2 as imageio

images = []
for i in range(step+1):
    filename = f'temp{i}.png'
    images.append(imageio.imread(filename))

duration = 10 / len(images)  
imageio.mimsave('result.gif', images, duration=duration)

import os

for i in range(step+1):
    filename = f'temp{i}.png'
    os.remove(filename)