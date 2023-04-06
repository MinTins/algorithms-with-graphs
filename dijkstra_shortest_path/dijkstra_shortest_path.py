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

# використовуємо алгоритм Дейкстри
dist = {node: float('inf') for node in G.nodes()}
dist[start_node] = 0
prev = {node: None for node in G.nodes()}
visited = set()

step = 1
while len(visited) < n:
    # знаходимо найближчу невідвідану вершину
    u = min((node for node in G.nodes() if node not in visited), key=lambda node: dist[node])
    visited.add(u)

    # оновлюємо відстані до сусідніх вершин
    for v in G.neighbors(u):
        if v not in visited:
            alt = dist[u] + G[u][v]['weight']
            if alt < dist[v]:
                dist[v] = alt
                prev[v] = u


            # візуалізація
            nx.draw_networkx_nodes(G, pos, nodelist=[u,v], node_color='r')
            nx.draw_networkx_nodes(G, pos, nodelist=visited, node_color='g')
            nx.draw_networkx_edges(G, pos, edgelist=[(prev[v], v) for v in prev if prev[v] is not None], edge_color='r', width=3)
            plt.savefig(f'temp{step}.png')
            step += 1


#final view
nx.draw_networkx_nodes(G, pos, nodelist=visited, node_color='g')
nx.draw_networkx_edges(G, pos, edgelist=[(prev[v], v) for v in prev if prev[v] is not None], edge_color='green', width=3)
plt.savefig(f'temp{step}.png')

# об'єднуємо всі зображення у гіфку
import imageio.v2 as imageio

images = []
for i in range(step+1):
    filename = f'temp{i}.png'
    images.append(imageio.imread(filename))

duration = 10 / len(images)  
imageio.mimsave('result.gif', images, duration=duration)

# видаляємо тимчасові файли
import os

for i in range(step+1):
    filename = f'temp{i}.png'
    os.remove(filename)